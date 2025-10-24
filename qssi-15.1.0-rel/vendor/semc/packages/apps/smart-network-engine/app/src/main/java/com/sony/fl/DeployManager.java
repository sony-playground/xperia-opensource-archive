package com.sony.fl;
/**
 * @author Masanobu Jimbo
 */

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Stream;

import com.sony.fl.algorithm.LinearFedHLCRClient;
import com.sony.fl.algorithm.NNFedHLCRClient;
import com.sony.fl.db.DBFactory;
import com.sony.fl.db.DBForPredictManager;
import com.sony.fl.db.DBForTrainManager;
import com.sony.fl.exception.FLException;
import com.sony.fl.logger.FLLogger;
import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.DataSerializer;
import com.sony.fl.pb.*;
import com.sony.fl.utils.*;
import org.apache.commons.io.file.PathUtils;

public class DeployManager {
    private final DBForTrainManager mDBForTrain;
    private final DBForPredictManager mDBForPredict;
    private final Path mTrainRootPath;
    private final Path mPredictRootPath;

    /**
     * Create DeployManager instance
     * @param trainBackUpPath : root path for TrainManager
     * @param predictBackUpPath : root path for PredictManager
     * @exception FLException : Throw exception if @{trainBackUpPath} or @{predictBackUpPath} was invalid or creating database was failed.
     */
    public DeployManager(Path trainBackUpPath, Path predictBackUpPath) 
            throws FLException {
        try {
            mDBForTrain = new DBForTrainManager((DBFactory)Class.forName(
                    Configuration.DB_FACTORY_FQCN).newInstance(), trainBackUpPath);
            mDBForPredict = new DBForPredictManager((DBFactory)Class.forName(
                Configuration.DB_FACTORY_FQCN).newInstance(), predictBackUpPath);
        } catch (InstantiationException | IllegalAccessException | ClassNotFoundException e) {
            FLLogger.e(e.toString());
            throw new FLException("Invalid DB type.");
        }
        mTrainRootPath = trainBackUpPath;
        mPredictRootPath = predictBackUpPath;
    }

    /**
     *
     * Copy FL model in TrainBackup to PredictBackup
     *
     * <pre>{@code
     *   // DeployManager オブジェクトを生成する
     *   DeployManager manager = new DeployManager(Paths.get(...), Paths.get(...));
     *
     *   // テンソル・マップに `x` テンソルや `グループ・ラベル` などの Cluster Mapping の更新に必要なテンソルを格納する
     *   DataSerializer dataSerializer = DataSerializer.createFor(Paths.get(...), Paths.get(...));
     *   for (x: [...]) {
     *       String groupLabel = ...;
     *       int y = ...;
     *       float[][] x = ...;
     *       int m = x.length;
     *       int n = x[0].length;;
     *       TensorMap tensorMap = TensorMap.newInstance();
     *       tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(n));
     *       tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));
     *       tensorMap.set(NNFedHLCRClient.TENSOR_Y, Tensor.newTensor(y));
     *       tensorMap.set(NNFedHLCRClient.TENSOR_X, Tensor.newTensor(TensorShape.getShape(m, n), Tensor.toDoubleArrayFrom(x)));
     *       // NOTE:
     *       // - ファイルへの保存に失敗すると、後続の DeployManager#deploy() において失敗したことを検出してエラーが応答される
     *       dataSerializer.save(tensorMap);
     *   }
     *   DataMetadata metaData = dataSerializer.getMetadata();
     *
     *   // テンソル・マップに格納された `フィーチャー数`, `シーケンス・データ`, `グループ・ラベル` テンソルに基づいて Cluster Mapping を更新する
     *   int result = manager.deploy(FLID, taskID, metaData, deployInfo, inputPath);
     * }</pre>
     *
     * @param FLID : FL ID
     * @param taskID : taskID
     * @param metaData : テンソルマップ・メタデータ<br>テンソルマップが保存されていない場合(データがゼロ件の場合)は Cluster Mapping を更新しません。
     * @param deployInfo : protobuf about deployment
     * @param inputPath : path of directory for input
     * @return : protobuf about training results if this funcition succeeds, @{null} otherwise
     */
    public int deploy(String FLID, String taskID, DataMetadata metaData,
            TaskInfo.PBDeployInfo deployInfo, Path inputPath) {
        String key = "";
        int ret = 1;
        if (metaData != null) {
            if (DataSerializer.wasSaved(metaData)) {
                if (!(DataSerializer.wasSuccess(metaData))) {
                    FLLogger.e("Failed to create TensorMap File.");
                    return 1;
                } else {
                    FLLogger.d("TensorMap file is saved.");
                }
            } else {
                FLLogger.d("TensorMap file is not saved.");
                metaData = null;
            }
        } else {
            FLLogger.d("No metadata specified. Cluster-Map file will not be updated.");
        }
        if (!PathChecker.checkFolderPath(inputPath, true, false, false)) {
            FLLogger.e(inputPath.toString() + " is an invalid path.");
            return 1;
        }
        try {
            key = ClientTaskController.getTaskFlag();
            if (key.length() == 0) {
                FLLogger.e("This task could not be started because another task is running.");
                return 2;
            }
            ret = _deploy(FLID, taskID, metaData, deployInfo, inputPath);
        } catch (RuntimeException e) {
            FLLogger.e(e.toString());
        } finally {
            ClientTaskController.releaseTaskFlag(key);
        }
        return ret;
    }

    /**
     *
     * Copy FL model in TrainBackup to PredictBackup
     *
     * <pre>{@code
     *   // DeployManager オブジェクトを生成する
     *   DeployManager manager = new DeployManager(Paths.get(...), Paths.get(...));
     *
     *   // デプロイする
     *   int result = manager.deploy(FLID, taskID, deployInfo, inputPath);
     * }</pre>
     *
     * @param FLID : FL ID
     * @param taskID : taskID
     * @param deployInfo : protobuf about deployment
     * @param inputPath : path of directory for input
     * @return : protobuf about training results if this funcition succeeds, @{null} otherwise
     */
    public int deploy(String FLID, String taskID,
            TaskInfo.PBDeployInfo deployInfo, Path inputPath) {
        return deploy(FLID, taskID, null, deployInfo, inputPath);
    }

    private int _deploy(String FLID, String taskID, DataMetadata metaData,
            TaskInfo.PBDeployInfo deployInfo, Path inputPath) {
        String appID = deployInfo.getAppID();
        Path deployTargetPath = createFolderForPrediction(appID, taskID);
        if (deployTargetPath == null) {
            FLLogger.e("Creating a new folder for the new backup was faild.");
            return 1;
        }
        String currentDeployPath = mDBForPredict.searchForBackUpPathFromDB(appID);
        if (currentDeployPath != null && currentDeployPath.equals(deployTargetPath.toString())) {
            FLLogger.e("This task was already completed.");
            return 1;
        }
        if (copyModelFile(inputPath, deployTargetPath, taskID, deployInfo) != 0) {
            FLLogger.e("Copying models was failed.");
            return 1;
        }
        // If model type is HLCR, we need to update cluster mapping.
        // TODO : return if the model type is not LCR.
        String oldBackUpPathStr = mDBForTrain.searchForBackUpPathFromDB(FLID);
        Path oldBackUpPath = null;
        if (oldBackUpPathStr != null) {
            FLLogger.i("oldBackUpPathStr is " + oldBackUpPathStr);
            oldBackUpPath = Paths.get(oldBackUpPathStr);
            if (!Files.exists(oldBackUpPath)) {
                FLLogger.w(oldBackUpPathStr.toString() + 
                        " is not found. Backup may be deleted.");
                oldBackUpPath = null;
            }
        }
        Path tmpBackUpPath = getNewBackUpFolder(FLID, taskID);
        if (tmpBackUpPath == null) {
            FLLogger.e("Creating a new folder for the backup was faild.");
            return 1;
        }
        if (oldBackUpPath == null || tmpBackUpPath.compareTo(oldBackUpPath) != 0) { 
            int ret = 1;
            switch(deployInfo.getModelType()) {
                case LinerHLCR:
                    LinearFedHLCRClient linearFedHLCRClient;
                    try {
                        linearFedHLCRClient = 
                                new LinearFedHLCRClient(deployInfo.getLinearHLCRGlobalModel(), 
                                oldBackUpPath, inputPath);
                    } catch (FLException e) {
                        FLLogger.e(e.toString());
                        return 1;
                    }
                    try {
                        if (metaData != null) {
                            ret = linearFedHLCRClient
                                    .updateClusterMapping(deployInfo, metaData, inputPath, inputPath, tmpBackUpPath);
                        } else {
                            FLLogger.d("Cluster-Map file was not updated.");
                            ret = 0;
                        }
                    } catch (RuntimeException e) {
                        FLLogger.e(e.toString());
                        ret = 1;
                    } finally {
                        linearFedHLCRClient.finalize();
                    }
                    break;
                case NNHLCR:
                    NNFedHLCRClient nnFedHLCRClient;
                    try {
                        nnFedHLCRClient = 
                                new NNFedHLCRClient(deployInfo.getNNHLCRModel(), 
                                oldBackUpPath, inputPath);
                    } catch (FLException e) {
                        FLLogger.e(e.toString());
                        deleteDir(tmpBackUpPath);
                        return 1;
                    }
                    try {
                        if (metaData != null) {
                            ret = nnFedHLCRClient
                                    .updateClusterMapping(deployInfo, metaData, inputPath, inputPath, tmpBackUpPath);
                        } else {
                            FLLogger.d("Cluster-Map file was not updated.");
                            ret = 0;
                        }
                    } catch (RuntimeException e) {
                        FLLogger.e(e.toString());
                        ret = 1;
                    } finally {
                        nnFedHLCRClient.finalize();
                    }
                    break;
                default:
                    FLLogger.e(deployInfo.getModelType().toString() + " is an invalid model type.");
                    deleteDir(tmpBackUpPath);
                    return 1;
            }
            if (ret != 0) {
                FLLogger.e("Update cluster mapping was failed.");
                deleteDir(tmpBackUpPath);
                return 1;
            }
        } else {
            FLLogger.i("Update cluster mapping is skipped because this was already executed.");
        }
        if (copyBackUpFile(tmpBackUpPath, deployTargetPath) != 0) {
            FLLogger.e("Copying backup was failed.");
            deleteDir(tmpBackUpPath);
            return 1;
        }
        if (deleteDir(tmpBackUpPath) != 0) {
            FLLogger.e("Deleteing backup was failed.");
            return 1;
        }
        Set<Path> savePathSet = new HashSet<Path>();
        savePathSet.add(deployTargetPath);
        if (currentDeployPath !=  null) {
            savePathSet.add(Paths.get(currentDeployPath));
        }
        if (cleanAppFolder(appID, savePathSet) != 0) {
            FLLogger.e("Clearning a floder for an App was failed.");
            return 1;
        }
        if (mDBForPredict.updateAppInfoOnDB(appID, deployTargetPath.toString(), deployInfo.toByteArray()) != 0) {
            FLLogger.e("Updating Database was failed.");
            return 1;
        }
        return 0;
    }

     /**
     * Stop using a deployed model
     * @param stopInfo : stop info
     * @return : @{0} if this funcition succeeds, @{1} otherwise
     */
    public int stop(TaskInfo.PBStopInfo stopInfo) {
        String key = "";
        int ret = 1;
        try {
            key = ClientTaskController.getTaskFlag();
            if (key.length() == 0) {
                FLLogger.e("This task could not be started because another task is running.");
                return 2;
            }
            ret = _stop(stopInfo);
        } catch (RuntimeException e) {
            FLLogger.e(e.toString());
        } finally {
            ClientTaskController.releaseTaskFlag(key);
        }
        return ret;
    }

    public int stop(String appID) {
        TaskInfo.PBStopInfo.Builder builder = TaskInfo.PBStopInfo.newBuilder();
        builder.setAppID(appID);
        TaskInfo.PBStopInfo stopInfo = builder.build();
        if (PBChecker.checkPBStopInfo(stopInfo) != 0) {
            FLLogger.e(appID + " is invalid appID.");
            return 1;
        }
        return stop(stopInfo);
    }

    private int _stop(TaskInfo.PBStopInfo stopInfo) {
        Path backUpPath = mPredictRootPath.resolve(stopInfo.getAppID());
        if (Files.exists(backUpPath)) {
            if (deleteDir(backUpPath) != 0) {
                FLLogger.e("Deleting a directory for backup was failed.");
                return 1;
            }
        }
        return mDBForPredict.deleteBackUpFromDB(stopInfo.getAppID());
    }

    private Path createFolderForPrediction(String appID, String taskID) {
        if (!PBChecker.isValidID(appID) || !PBChecker.isValidID(taskID)) {
            FLLogger.e("Input ID is invalid");
            return null;
        }
        Path path = mPredictRootPath.resolve(appID).resolve(taskID);
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

    // TODO : fix
    private int copyModelFile(Path sourcePath, Path targetPath, 
            String taskID, TaskInfo.PBDeployInfo deployInfo) {
        int ret = 0;
        try {
            try (Stream<Path> stream = Files.list(sourcePath)) {
                for (Path p : stream.toArray(Path[]::new)) {
                    String s = p.toString();
                    if (!(s.indexOf("Data.dat") != -1)) { // This is tentative : We need to copy all files except data file.
                        PathUtils.copyFileToDirectory(p, targetPath, StandardCopyOption.REPLACE_EXISTING);
                    }
                }
            }
            byte[] bytes = deployInfo.toByteArray();
            try (FileOutputStream fos = new FileOutputStream(targetPath.resolve(taskID + ".protobuf").toString())) {
                fos.write(bytes);
            }
        } catch(IOException e) {
            FLLogger.e(e.toString());
            ret = 1;
        }
        return ret;
    }

    private int copyBackUpFile(Path sourcePath, Path targetPath) {
        int ret = 0;
        try {
            try (Stream<Path> stream = Files.list(sourcePath)) {
                for (Path p : stream.toArray(Path[]::new)) {
                    PathUtils.copyFileToDirectory(p, targetPath, StandardCopyOption.REPLACE_EXISTING);
                }
            }
        } catch(IOException e) {
            FLLogger.e(e.toString());
            ret = 1;
        }
        return ret;
    }

    private int deleteDir(Path dirPath) {
        int ret = 0;
        try {
            PathUtils.deleteDirectory(dirPath);
        } catch (IOException e) {
            FLLogger.w("Deleting " + dirPath.toString() + " was failed.");
            ret = 1;
        }
        return ret;
    }

    private Path getNewBackUpFolder(String FLID, String taskID) {
        if (!PBChecker.isValidID(FLID) || !PBChecker.isValidID(taskID)) {
            FLLogger.e("Input ID is invalid");
            return null;
        }
        Path path = mTrainRootPath.resolve(FLID).resolve(taskID);
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

    private int cleanAppFolder(String appID, Set<Path> savePathSet) {
        File appFolder = mPredictRootPath.resolve(appID).toFile();
        for (File file : appFolder.listFiles()) {
            if (savePathSet.contains(file.toPath())) {
                continue;
            }
            int ret = deleteDir(file.toPath());
            if (ret != 0) {
                FLLogger.e("cleanPredictManagerRoot failed due to the fail of deleteDir.");
                return 1;
            }
        }
        return 0;
    }
}
