package com.sony.fl.algorithm;

import java.nio.file.Files;
import java.nio.file.Path;

import com.sony.fl.PredictManager;
import com.sony.fl.TrainManager;
import com.sony.fl.exception.FLException;
import com.sony.fl.jni.NNHLCRNativeJNI;
import com.sony.fl.logger.FLLogger;
import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.Tensor;
import com.sony.fl.tensor.TensorMap;

/**
 * @author Masanobu Jimbo
 */

import com.sony.fl.pb.*;
import com.sony.fl.tensor.DataMetadata;

public class NNFedHLCRClient extends FedHLCRClient {
    public static final String CLUSTER_MAP_FILE_NAME = "ClusterMap.dat";
    public static final String UPDATE_PARAM_FILE_NAME = "CalibrateParams.dat";
    private NNHLCRNativeJNI mNNHLCRJni;
    private final long mNativePointer;
    private boolean isFinalized;

    /**
     * 非線形LCR用テンソル名：フィーチャー数
     */
    public static final String TENSOR_NUM_OF_FEATURES = "num_of_features";
    /**
     * 非線形LCR用テンソル名：グループ・ラベル
     */
    public static final String TENSOR_GROUP_LABEL = "group_label";
    /**
     * 非線形LCR用テンソル名：Y
     */
    public static final String TENSOR_Y = "y";
    /**
     * 非線形LCR用テンソル名：X
     */
    public static final String TENSOR_X = "x";
    /**
     * 非線形LCR用テンソル名：シーケンス・データ
     */
    public static final String TENSOR_SEQUENCE_DATA = "sequence_data";
    /**
     * 非線形LCR用テンソル名：推論結果
     */
    public static final String TENSOR_Y_PRED = "y_pred";

    public NNFedHLCRClient(NNHLCR.PBNNHLCRModel modelInfo, 
            Path backUpPath, Path modelPath) throws FLException {
        mNNHLCRJni = new NNHLCRNativeJNI();
        String modelInfoStr = createModelInfoStr(modelInfo, backUpPath, modelPath);
        if (modelInfoStr == null) {
            FLLogger.e("Input is invalid");
            throw new FLException("Input is invalid");
        }
        FLLogger.d("Call native Initialize.");
        mNativePointer = mNNHLCRJni.Initialize(modelInfoStr);
        FLLogger.d("Result of native Initialize = " + mNativePointer);
        if (this.isFailedOrNot(mNativePointer)) {
            FLLogger.e("Native intialize is failed.");
            throw new FLException("Native intialize is failed.");
        }
        isFinalized = false;
    }

    public TaskResult.PBTrainResult train(DataMetadata metaData, TaskInfo.PBTrainInfo trainInfo,
            Path dataPath, Path trainParamPath, Path newBackUpPath, Path outputPath) {
        String metaDataStr = metaData.toJsonString();
        String trainInfoStr = createTrainInfoStr(trainInfo, trainParamPath, newBackUpPath, outputPath);
        if (isFinalized) {
            FLLogger.e("Naive object is finalized.");
            return null;
        }
        if (trainInfoStr == null) {
            FLLogger.e("Input is invalid");
            return null;
        }
        FLLogger.d("Call native Training.");
        String trainResultStr = mNNHLCRJni.Training(mNativePointer, metaDataStr, trainInfoStr);
        FLLogger.d(trainResultStr);
        return parseTrainResult(trainResultStr, newBackUpPath, outputPath);
    }

    public TaskResult.PBEvaluationResult evaluate(
            DataMetadata metaData, TaskInfo.PBEvaluationInfo evaluationInfo,
            Path dataPath, Path preprocessParamPath, Path outputPath) {
        if (isFinalized) {
            FLLogger.e("Naive object is finalized.");
            return null;
        }
        String metaDataStr = metaData.toJsonString();
        String evaluationInfoStr = createEvaluationInfoStr(evaluationInfo, preprocessParamPath, outputPath);
        if (evaluationInfoStr == null) {
            FLLogger.e("Input is invalid");
            return null;
        }
        FLLogger.d("Call native Evaluation.");
        String evaluationResultStr = mNNHLCRJni.Evaluation(mNativePointer, metaDataStr, evaluationInfoStr);
        FLLogger.d(evaluationResultStr);
        return parseEvaluationResult(evaluationResultStr, outputPath);
    }

    public TensorMap predict(TensorMap input) {
        if (isFinalized) {
            FLLogger.e("Naive object is finalized.");
            return null;
        }
        if (input.get(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES) == null) {
            FLLogger.e("num of features is empty.");
            return null;
        }
        if (input.get(NNFedHLCRClient.TENSOR_SEQUENCE_DATA) == null) {
            FLLogger.e("data sequence is empty.");
            return null;
        }
        FLLogger.d("Call native Prediction.");
        String predictResultStr = mNNHLCRJni.Prediction(mNativePointer, input.toJsonString());
        FLLogger.d("Predicted result is " + predictResultStr);
        return TensorMap.fromJsonString(predictResultStr);
    }

    public int updateClusterMapping(TaskInfo.PBDeployInfo deployInfo, DataMetadata metaData, 
            Path preprocessParamPath, Path calibrateInfoDirPath, Path newBackUpPath) {
        if (isFinalized) {
            FLLogger.e("Naive object is finalized.");
            return 1;
        }
        String updateInfoStr = createUpdateInfoStr(deployInfo, metaData,
                preprocessParamPath, calibrateInfoDirPath, newBackUpPath);
        if (updateInfoStr == null) {
            FLLogger.e("Input is invalid");
            return 1;
        }
        FLLogger.d("Call native Update cluaster mapping.");
        String updateInfoResultStr = mNNHLCRJni.UpdateInfo(mNativePointer, metaData.toJsonString(), updateInfoStr);
        FLLogger.d(updateInfoResultStr);
        return parseUpdateInfoResult(updateInfoResultStr, newBackUpPath);
    }

    public void finalize() {
        if (isFinalized) {
            FLLogger.d("already finalized.");
            return;
        }
        if (this.isFailedOrNot(mNativePointer)) {
            FLLogger.d("not initialized.");
            return;
        }
        FLLogger.d("Call native finalize.");
        mNNHLCRJni.Finalize(mNativePointer);
        isFinalized = true;
    }

    private String createModelInfoStr(NNHLCR.PBNNHLCRModel modelInfo, 
            Path backUpPath, Path modelPath) {
        StringBuilder sb = new StringBuilder();
        int K = modelInfo.getNNWeightsFileNamesCount();
        sb.append(K).append(System.getProperty("line.separator"));
        for (String s : modelInfo.getNNGraphFileNamesList()) {
            Path modelFilePath = modelPath.resolve(s).toAbsolutePath();
            if (!Files.exists(modelFilePath)) {
                FLLogger.e(modelFilePath.toString() + " is not found.");
                return null;
            }
            sb.append(modelFilePath).append(System.getProperty("line.separator"));
        }
        for (String s : modelInfo.getNNWeightsFileNamesList()) {
            Path modelFilePath = modelPath.resolve(s).toAbsolutePath();
            if (!Files.exists(modelFilePath)) {
                FLLogger.e(modelFilePath.toString() + " is not found.");
                return null;
            }
            sb.append(modelFilePath).append(System.getProperty("line.separator"));
        }
        Path hlcrParamFilePath = modelPath.resolve(
                modelInfo.getHLCRParamsFileName()).toAbsolutePath();
        if (!Files.exists(hlcrParamFilePath)) {
            FLLogger.e(hlcrParamFilePath.toString() + " is not found.");
            return null;
        }
        sb.append(hlcrParamFilePath).append(System.getProperty("line.separator"));
        if (backUpPath == null) {
            return sb.toString();
        }
        Path clusterMapFilePath = backUpPath.resolve(CLUSTER_MAP_FILE_NAME).toAbsolutePath();
        if (!Files.exists(clusterMapFilePath)) {
            FLLogger.w(clusterMapFilePath.toString() + " is not found.");
        } else {
            sb.append(clusterMapFilePath);
        }
        return sb.toString();
    }

    private String createTrainInfoStr(TaskInfo.PBTrainInfo trainInfo,
            Path trainParamPath, Path newBackUpPath, Path outputPath) {
        StringBuilder sb = new StringBuilder();
        Path trainParamFilePath = trainParamPath.resolve(
                trainInfo.getNNHLCRTrainInfo().getHyperparamsFileName()).toAbsolutePath();
        if (!Files.exists(trainParamFilePath)) {
            FLLogger.e(trainParamFilePath.toString() + " is not found.");
            return null;
        }
        sb.append(trainParamFilePath).append(System.getProperty("line.separator"));
        Path preprocessParamPath = trainParamPath.resolve(
                trainInfo.getDataInfo().getPreprocessParamsFileName()).toAbsolutePath();
        if (!Files.exists(preprocessParamPath)) {
            FLLogger.e(preprocessParamPath.toString() + " is not found.");
            return null;
        }
        sb.append(preprocessParamPath).append(System.getProperty("line.separator"));
        sb.append(outputPath.toAbsolutePath())
                .append(System.getProperty("line.separator"))
                .append(newBackUpPath.toAbsolutePath());
        return sb.toString();
    }

    private String createEvaluationInfoStr(TaskInfo.PBEvaluationInfo evaluationInfo,
            Path preprocessParamPath, Path outputPath) {
        StringBuilder sb = new StringBuilder();
        Path preprocessParamFilePath = preprocessParamPath.resolve(
                evaluationInfo.getDataInfo().getPreprocessParamsFileName()).toAbsolutePath();
        if (!Files.exists(preprocessParamFilePath)) {
            FLLogger.e(preprocessParamFilePath.toString() + " is not found.");
            return null;
        }
        sb.append(preprocessParamFilePath).append(System.getProperty("line.separator"));
        sb.append(outputPath.toAbsolutePath());
        return sb.toString();
    }
    
    private String createUpdateInfoStr(TaskInfo.PBDeployInfo deployInfo, DataMetadata metaData,
            Path preprocessParamPath, Path calibrateInfoDirPath, Path newBackUpPath) {
        StringBuilder sb = new StringBuilder();
        Path preprocessParamFilePath = preprocessParamPath.resolve(
                deployInfo.getDataInfo().getPreprocessParamsFileName()).toAbsolutePath();
        if (!Files.exists(preprocessParamFilePath)) {
            FLLogger.e(preprocessParamFilePath.toString() + " is not found.");
            return null;
        }
        sb.append(preprocessParamFilePath).append(System.getProperty("line.separator"));
        Path updateParamFilePath = calibrateInfoDirPath.resolve(
                UPDATE_PARAM_FILE_NAME).toAbsolutePath();
        if (!Files.exists(updateParamFilePath)) {
            FLLogger.e(updateParamFilePath.toString() + " is not found.");
            return null;
        }
        sb.append(updateParamFilePath).append(System.getProperty("line.separator"));
        sb.append(newBackUpPath.toAbsolutePath());
        return sb.toString();
    }

    private TaskResult.PBTrainResult parseTrainResult(String trainResultStr, 
            Path backUpPath, Path outputPath) {
        if (trainResultStr == null || trainResultStr.length() == 0) {
            FLLogger.e("trainResultStr is null");
            return null;
        }
        String[] strs = trainResultStr.split(System.getProperty("line.separator"));
        int K = 0;
        try {
            K = Integer.parseInt(strs[0]);
        } catch (NumberFormatException e) {
            FLLogger.e(e.toString());
        }
        if (K <= 0) {
            FLLogger.e(K + "is invalid length.");
            return null;
        }
        if (strs.length != K+4) {
            FLLogger.e("trainResultStr is invalid format.");
            return null;
        }
        TaskResult.PBTrainResult.Builder trainResultBuilder = TaskResult.PBTrainResult.newBuilder();
        NNHLCR.PBNNHLCRModel.Builder nnHLCRBuilder = NNHLCR.PBNNHLCRModel.newBuilder();
        for (int i = 0; i < K; i++) {
            Path nnFile = outputPath.resolve(strs[i+1]);
            if (!Files.exists(nnFile)) {
                FLLogger.e(nnFile.toString() + " is not found.");
                return null;
            }
            nnHLCRBuilder.addNNWeightsFileNames(strs[i+1]);
        }
        Path hlcrParamFile = outputPath.resolve(strs[K+1]);
        if (!Files.exists(hlcrParamFile)) {
            FLLogger.e(hlcrParamFile.toString() + "is not found.");
            return null;
        }
        nnHLCRBuilder.setHLCRParamsFileName(strs[K+1]);
        Path validationMetrixFile = outputPath.resolve(strs[K+2]);
        if (!Files.exists(validationMetrixFile)) {
            FLLogger.e(validationMetrixFile.toString() + " is not found.");
            return null;
        }
        trainResultBuilder.setNNHLCRModel(nnHLCRBuilder)
                .setValidationMetrixFileName(strs[K+2]);
        Path clusterMappingFile = backUpPath.resolve(strs[K+3]);
        if (!(strs[K+3].equals(CLUSTER_MAP_FILE_NAME))) {
            FLLogger.e(strs[K+3] + " is invalid cluster mapping file name");
            return null;
        }
        if (!Files.exists(clusterMappingFile)) {
            FLLogger.e(clusterMappingFile.toString() + "is not found.");
            return null;
        }
        return trainResultBuilder.build();
    }

    private TaskResult.PBEvaluationResult parseEvaluationResult(String evaluationResultStr, 
            Path outputPath) {
        if (evaluationResultStr == null || evaluationResultStr.length() == 0) {
            FLLogger.e("evaluationResultStr is null");
            return null;
        }
        Path evaluationResultFilePath = outputPath.resolve(evaluationResultStr);
        if (!Files.exists(evaluationResultFilePath)) {
            FLLogger.e(evaluationResultFilePath.toString() + " is not found.");
            return null;
        }
        TaskResult.PBEvaluationResult.Builder builder = TaskResult.PBEvaluationResult.newBuilder();
        builder.setEvaluationResultFileName(evaluationResultStr);
        return builder.build();
    }

    private int parseUpdateInfoResult(String updateInfoResultStr, 
            Path backUpPath) {
        if (updateInfoResultStr == null || updateInfoResultStr.length() == 0) {
            FLLogger.e("updateInfoResultStr is null.");
            return 1;
        }
        Path clusterMappingFile = backUpPath.resolve(updateInfoResultStr);
        if (!(updateInfoResultStr.equals(CLUSTER_MAP_FILE_NAME))) {
            FLLogger.e(updateInfoResultStr + " is invalid cluster mapping file name");
            return 1;
        }
        if (!Files.exists(clusterMappingFile)) {
            FLLogger.e(clusterMappingFile.toString() + "is not found.");
            return 1;
        }
        return 0;
    }

}
