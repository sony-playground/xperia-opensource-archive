package com.sony.fl;
/**
 * @author Masanobu Jimbo
 */
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import com.sony.fl.algorithm.*;
import com.sony.fl.db.*;
import com.sony.fl.exception.FLException;
import com.sony.fl.logger.FLLogger;
import com.sony.fl.pb.*;
import com.sony.fl.pb.TaskInfo.PBDeleteInfo;
import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.DataSerializer;
import com.sony.fl.utils.PBChecker;
import com.sony.fl.utils.PathChecker;
import org.apache.commons.io.file.PathUtils;

public class TrainManager {
    private final DBForTrainManager mDatabase;
    private final Path mRoot;

    /**
     * Create TrainManager instance
     * @param dirPath : root path for this instance
     * @throws FLException : Throw exception if @{dirpath} was invalid or creating database was failed.
     */
    public TrainManager(Path dirPath) throws FLException {
        mRoot = dirPath;
        if (!PathChecker.checkFolderPath(dirPath, true, true, true)) {
            FLLogger.e(dirPath.toString() + " is an invalid path.");
            throw new FLException("Creating TrainManager was failed due to invalid input.");
        }
        try {
            mDatabase = new DBForTrainManager((DBFactory)Class.forName(
                    Configuration.DB_FACTORY_FQCN).newInstance(), mRoot);
        } catch (InstantiationException | IllegalAccessException | ClassNotFoundException e) {
            FLLogger.e(e.toString());
            throw new FLException("Invalid DB type.");
        }
    }

    /**
     * Retrieves information for training from a database and passes it to FLClient train method
     *
     * <pre>{@code
     *   // TrainManager オブジェクトを生成する
     *   TrainManager manager = new TrainManager(Paths.get(...));
     *
     *   // テンソル・マップに `x` テンソルや `グループ・ラベル` などの学習に必要なテンソルを格納する
     *   DataSerializer dataSerializer = DataSerializer.createFor(Paths.get(...), Paths.get(...));
     *   for (x: [...]) {
     *       String groupLabel = ...;
     *       int y = ...;
     *       float[][] x = ...;
     *       int m = x.length;
     *       int n = x[0].length;
     *       TensorMap tensorMap = TensorMap.newInstance();
     *       tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(n));
     *       tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));
     *       tensorMap.set(NNFedHLCRClient.TENSOR_Y, Tensor.newTensor(y));
     *       tensorMap.set(NNFedHLCRClient.TENSOR_X, Tensor.newTensor(TensorShape.getShape(m, n), Tensor.toDoubleArrayFrom(x)));
     *       // NOTE:
     *       // - ファイルへの保存に失敗すると、後続の TrainManager#train() において失敗したことを検出してエラーが応答される
     *       dataSerializer.save(tensorMap);
     *   }
     *   DataMetadata metaData = dataSerializer.getMetadata();
     *
     *   // テンソル・マップに格納された `フィーチャー数`, `シーケンス・データ`, `グループ・ラベル` テンソルに基づいて学習する
     *   TrainResult result = manager.train(FLID, taskID, metaData, trainInfo, inputPath, outputPath);
     * }</pre>
     *
     * @param FLID : FL ID
     * @param taskID : Task ID
     * @param metaData : テンソルマップ・メタデータ
     * @param trainInfo : protobuf about train info e.g. modeltype, hyper parameters
     * @param inputPath : path of directory for input e.g. model weights, training data
     * @param outputPath : path of directory for output
     * @return : status code and protobuf about training results
     */
    public TrainResult train(String FLID, String taskID,
            DataMetadata metaData,
            TaskInfo.PBTrainInfo trainInfo,
            Path inputPath, Path outputPath) {
        String key = "";
        TaskResult.PBTrainResult ret = null;
        if (DataSerializer.wasSaved(metaData)) {
            if (!DataSerializer.wasSuccess(metaData)) {
                FLLogger.e("Failed to create TensorMap File.");
                return new TrainResult(1, null);
            } else {
                FLLogger.d("TensorMap file is saved.");
            }
        } else {
            FLLogger.d("TensorMap file is not saved.");
            // metaData = null;     // Pass 'metaData' to the Native layer
        }
        if (!PathChecker.checkFolderPath(inputPath, true, false, false)) {
            FLLogger.e(inputPath.toString() + " is an invalid path.");
            return new TrainResult(1, null);
        }
        if (!PathChecker.checkFolderPath(outputPath, true, true, true)) {
            FLLogger.e(outputPath.toString() + " is an invalid path.");
            return new TrainResult(1, null);
        }
        try {
            key = ClientTaskController.getTaskFlag();
            if (key.length() == 0) {
                FLLogger.e("This task could not be started because another task is running.");
                return new TrainResult(2, null);
            }
            ret = _train(FLID, taskID, metaData, trainInfo, inputPath, outputPath);
        } catch (RuntimeException e) {
            FLLogger.e(e.toString());
        } finally {
            ClientTaskController.releaseTaskFlag(key);
        }
        if (ret == null) {
            return new TrainResult(1, null);
        }
        return new TrainResult(0, ret);
    }

    private TaskResult.PBTrainResult _train(String FLID, String taskID,
            DataMetadata metaData,
            TaskInfo.PBTrainInfo trainInfo, 
            Path inputPath, Path outputPath) {
        String oldBackUpPathStr = mDatabase.searchForBackUpPathFromDB(FLID);
        Path oldBackUpPath = null;
        if (oldBackUpPathStr != null) {
            oldBackUpPath = Paths.get(oldBackUpPathStr);
            if (!Files.exists(oldBackUpPath)) {
                FLLogger.w(oldBackUpPath.toString() + 
                        " is not found. Backup may be deleted.");
                oldBackUpPath = null;
            }
        }
        Path newBackUpPath = getNewBackUpFolder(FLID, taskID);
        if (newBackUpPath == null) {
            FLLogger.e("Creating a new folder for the new backup was faild.");
            return null;
        }
        if (oldBackUpPath != null && oldBackUpPath.compareTo(newBackUpPath) == 0) {
            FLLogger.e("This task was already completed");
            return null;
        }
        TaskResult.PBTrainResult trainResult = null;
        switch(trainInfo.getModelType()) {
            case LinerHLCR:
                LinearFedHLCRClient linearFedHLCRClient;
                try {
                    linearFedHLCRClient = 
                            new LinearFedHLCRClient(trainInfo.getLinearHLCRGlobalModel(), 
                            oldBackUpPath, inputPath);
                } catch (FLException e) {
                    FLLogger.e(e.toString());
                    deleteDir(newBackUpPath);
                    return null;
                }
                try {
                    trainResult = 
                            linearFedHLCRClient.train(metaData, trainInfo, inputPath, 
                            inputPath, newBackUpPath, outputPath);
                } catch (RuntimeException e) {
                    FLLogger.e(e.toString());
                } finally {
                    linearFedHLCRClient.finalize();
                }
                break;
            case NNHLCR:
                NNFedHLCRClient nnFedHLCRClient;
                try {
                    nnFedHLCRClient = 
                            new NNFedHLCRClient(trainInfo.getNNHLCRModel(), oldBackUpPath, inputPath);
                } catch (FLException e) {
                    FLLogger.e(e.toString());
                    deleteDir(newBackUpPath);
                    return null;
                }
                try {
                    trainResult = 
                            nnFedHLCRClient.train(metaData, trainInfo, inputPath, 
                            inputPath, newBackUpPath, outputPath);
                } catch (RuntimeException e) {
                    FLLogger.e(e.toString());
                } finally {
                    nnFedHLCRClient.finalize();
                }
                break;
            default:
                FLLogger.e(trainInfo.getModelType().toString() + " is not supported.");
                deleteDir(newBackUpPath);
                return null;
        }
        if (trainResult == null) {
            FLLogger.e("train result is null.");
            deleteDir(newBackUpPath);
            return null;
        }
        if (oldBackUpPath != null && deleteDir(oldBackUpPath) != 0) {
            FLLogger.e("Deleting back up is failed.");
            deleteDir(newBackUpPath);
            return null;
        }
        if (mDatabase.updateBackUpPathOnDB(FLID, newBackUpPath.toString()) != 0) {
            FLLogger.e("Updating backup path in Database was failed.");
            return null;
        }
        return trainResult;
    }

    /**
     * Retrieves information for evaluation from a database and passes it to FLClient evaluation method
     *
     * <pre>{@code
     *   // TrainManager オブジェクトを生成する
     *   TrainManager manager = new TrainManager(Paths.get(...));
     *
     *   // テンソル・マップに `x` テンソルや `グループ・ラベル` などの評価に必要なテンソルを格納する
     *   DataSerializer dataSerializer = DataSerializer.createFor(Paths.get(...), Paths.get(...));
     *   for (x: [...]) {
     *       String groupLabel = ...;
     *       int y = ...;
     *       float[][] x = ...;
     *       int m = x.length;
     *       int n = x[0].length;
     *       TensorMap tensorMap = TensorMap.newInstance();
     *       tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(n));
     *       tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));
     *       tensorMap.set(NNFedHLCRClient.TENSOR_Y, Tensor.newTensor(y));
     *       tensorMap.set(NNFedHLCRClient.TENSOR_X, Tensor.newTensor(TensorShape.getShape(m, n), Tensor.toDoubleArrayFrom(x)));
     *       // NOTE:
     *       // - ファイルへの保存に失敗すると、後続の TrainManager#evaluation() において失敗したことを検出してエラーが応答される
     *       dataSerializer.save(tensorMap);
     *   }
     *   DataMetadata metaData = dataSerializer.getMetadata();
     *
     *   // テンソル・マップに格納された `フィーチャー数`, `シーケンス・データ`, `グループ・ラベル` テンソルに基づいて評価する
     *   EvaluationResult result = manager.evaluation(FLID, metaData, evaluationInfo, inputPath, outputPath);
     * }</pre>
     *
     * @param FLID : FL ID
     * @param metaData : テンソルマップ・メタデータ
     * @param evaluationInfo : protobuf about evaluation method
     * @param inputPath : path of directory for input e.g. model weights, training data
     * @param outputPath : output path
     * @return : protobuf about evaluation results if this funcition succeeds, @{null} otherwise
     */
    public EvaluationResult evaluation(String FLID, 
           DataMetadata metaData,
           TaskInfo.PBEvaluationInfo evaluationInfo, 
            Path inputPath, Path outputPath) {
        String key = "";
        TaskResult.PBEvaluationResult ret = null;
        if (DataSerializer.wasSaved(metaData)) {
            if (!DataSerializer.wasSuccess(metaData)) {
                FLLogger.e("Failed to create TensorMap File.");
                return new EvaluationResult(1, null);
            } else {
                FLLogger.d("TensorMap file is saved.");
            }
        } else {
            FLLogger.d("TensorMap file is not saved.");
            // metaData = null;     // Pass 'metaData' to the Native layer
        }
        if (!PathChecker.checkFolderPath(inputPath, true, false, false)) {
            FLLogger.e(inputPath.toString() + " is an invalid path.");
            return new EvaluationResult(1, null);
        }
        if (!PathChecker.checkFolderPath(outputPath, true, true, true)) {
            FLLogger.e(outputPath.toString() + " is an invalid path.");
            return new EvaluationResult(1, null);
        }
        try {
            key = ClientTaskController.getTaskFlag();
            if (key.length() == 0) {
                FLLogger.e("This task could not be started because another task is running.");
                return new EvaluationResult(2, null);
            }
            ret = _evaluation(FLID, metaData, evaluationInfo, inputPath, outputPath);
        } catch (RuntimeException e) {
            FLLogger.e(e.toString());
        } finally {
            ClientTaskController.releaseTaskFlag(key);
        }
        if (ret == null) {
            return new EvaluationResult(1, null);
        }
        return new EvaluationResult(0, ret);
    }

    private TaskResult.PBEvaluationResult _evaluation(String FLID, 
            DataMetadata metaData,
            TaskInfo.PBEvaluationInfo evaluationInfo, 
            Path inputPath, Path outputPath) {
        String backUpPathStr = mDatabase.searchForBackUpPathFromDB(FLID);
        Path backUpPath = null;
        if (backUpPathStr != null) {
            backUpPath = Paths.get(backUpPathStr);
            if (!Files.exists(backUpPath)) {
                FLLogger.w(backUpPathStr.toString() + 
                        " is not found. Backup may be deleted.");
                backUpPath = null;
            }
        }
        TaskResult.PBEvaluationResult evaluationResult = null;
        switch(evaluationInfo.getModelType()) {
            case LinerHLCR:
            LinearFedHLCRClient linearFedHLCRClient;
            try {
                    linearFedHLCRClient = 
                            new LinearFedHLCRClient(evaluationInfo.getLinearHLCRGlobalModel(), 
                            backUpPath, inputPath);
                } catch (FLException e) {
                    FLLogger.e(e.toString());
                    return null;
                }
            try {
                    evaluationResult = 
                            linearFedHLCRClient.evaluate(metaData, evaluationInfo, inputPath, inputPath, outputPath);
                } catch (RuntimeException e) {
                    FLLogger.e(e.toString());
                } finally {
                    linearFedHLCRClient.finalize();
                }
                break;
            case NNHLCR:
                NNFedHLCRClient nnFedHLCRClient;
                try {
                    nnFedHLCRClient = 
                            new NNFedHLCRClient(evaluationInfo.getNNHLCRModel(),
                            backUpPath, inputPath);
                } catch (FLException e) {
                    FLLogger.e(e.toString());
                    return null;
                }
                try {
                    evaluationResult = nnFedHLCRClient.evaluate(
                            metaData, evaluationInfo, inputPath, inputPath, outputPath);
                } catch (RuntimeException e) {
                    FLLogger.e(e.toString());
                } finally {
                    nnFedHLCRClient.finalize();
                }
                break;
            default:
                FLLogger.e(evaluationInfo.getModelType().toString() + " is not supported.");
                break;
        }
        return evaluationResult;
    }


    /**
     * Delete all information related to FLID
     * @param FLID : FL ID
     * @param deleteInfo : delet info
     * @return : @{0} if success, @{1} otherwise
     */
    public int delete(String FLID, PBDeleteInfo deleteInfo) {
        String key = "";
        int ret = 1;
        try {
            key = ClientTaskController.getTaskFlag();
            if (key.length() == 0) {
                FLLogger.e("This task could not be started because another task is running.");
                return 2;
            }
            ret = _delete(FLID);
        } catch (RuntimeException e) {
            FLLogger.e(e.toString());
        } finally {
            ClientTaskController.releaseTaskFlag(key);
        }
        return ret;
    }

    private int _delete(String FLID) {
        Path backUpPath = mRoot.resolve(FLID);
        if (Files.exists(backUpPath)) {
            if (deleteDir(backUpPath) != 0) {
                FLLogger.e("Deleting a directory for backup was failed.");
                return 1;
            }
        }
        if (mDatabase.deleteBackUpFromDB(FLID) != 0) {
            FLLogger.e("Deleting backup path in Database was failed.");
            return 1;
        }
        return 0;
    }

    private Path getNewBackUpFolder(String FLID, String taskID) {
        Path path = mRoot.resolve(FLID).resolve(taskID);
        FLLogger.d(path.toString());
        if (!PBChecker.isValidID(FLID) || !PBChecker.isValidID(taskID)) {
            FLLogger.e("Input ID is invalid");
            return null;
        }
        try {
            Files.createDirectories(path);
        } catch (IOException e) {
            FLLogger.e("Creating " + path.toString() + " was failed.");
            path = null;
        }
        if (!PathChecker.checkFolderPath(path, true, true, true)) {
            FLLogger.e(path.toString() + " is invalid folder.");
            return null;
        }
        return path;
    }

    private int deleteDir(Path dirPath) {
        if (dirPath == null) {
            FLLogger.w("dirPath is null");
            return 1;
        }
        int ret = 0;
        try {
            PathUtils.deleteDirectory(dirPath);
        } catch (IOException e) {
            FLLogger.w(e.toString());
            ret = 1;
        }
        return ret;
    }

    public static class TrainResult {
        private int status;
        private TaskResult.PBTrainResult trainResult;
        private TrainResult(int status, TaskResult.PBTrainResult trainResult) {
            this.status = status;
            this.trainResult = trainResult;
        }
        public int getStatus() {
            return status;
        }
        public TaskResult.PBTrainResult getTrainResult() {
            return trainResult;
        }
    }

    public static class EvaluationResult {
        private int status;
        private TaskResult.PBEvaluationResult evaluationResult;
        private EvaluationResult(int status, TaskResult.PBEvaluationResult evaluationResult) {
            this.status = status;
            this.evaluationResult = evaluationResult;
        }
        public int getStatus() {
            return status;
        }
        public TaskResult.PBEvaluationResult getEvaluationResult() {
            return evaluationResult;
        }
    }
}
