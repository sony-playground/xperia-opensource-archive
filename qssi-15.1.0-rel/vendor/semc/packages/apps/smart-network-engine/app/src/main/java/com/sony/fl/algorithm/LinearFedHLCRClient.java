package com.sony.fl.algorithm;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;

import com.sony.fl.exception.FLException;
import com.sony.fl.jni.LinearHLCRNativeJNI;
import com.sony.fl.json.Json;
import com.sony.fl.logger.FLLogger;

/**
 * @author Masanobu Jimbo
 */

import com.sony.fl.pb.*;
import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.TensorMap;

public class LinearFedHLCRClient extends FedHLCRClient {
    public static final String CLUSTER_MAP_FILE_NAME = "cluster_map.json";
    public static final String HYPER_PARAM_FILE_NAME = "LinearHLCRUpdateHyperParams.json";
    private LinearHLCRNativeJNI mLinearHLCRJni;
    private final long mNativePointer;
    private boolean isFinalized;

    /**
     * 線形LCR用テンソル名：グループ・ラベル
     */
    public static final String TENSOR_GROUP_LABEL = "g";
    /**
     * 線形LCR用テンソル名：Y
     */
    public static final String TENSOR_Y = "y";
    /**
     * 線形LCR用テンソル名：X
     */
    public static final String TENSOR_X = "x";
    /**
     * 線形LCR用テンソル名：推論結果
     */
    public static final String TENSOR_Y_PRED = "y_pred";

    public LinearFedHLCRClient(LinearHLCR.PBLinearHLCRGlobalModel modelInfo, 
            Path backUpPath, Path modelPath) throws FLException {
        // Shoud we check if it is success?
        mLinearHLCRJni = new LinearHLCRNativeJNI();
        String modelInfoJsonStr = createModelInfoStr(modelInfo, backUpPath, modelPath);
        if (modelInfoJsonStr == null) {
            FLLogger.e("Input is invalid");
            throw new FLException("Input is invalid");
        }
        FLLogger.d("Call native Initialize.");
        mNativePointer = mLinearHLCRJni.Initialize(modelInfoJsonStr);
        FLLogger.d("Result of native Initialize = " + mNativePointer);
        if (this.isFailedOrNot(mNativePointer)) {
            FLLogger.e("Native intialize is failed.");
            throw new FLException("Native intialize is failed.");
        }
        isFinalized = false;
    }

    public TaskResult.PBTrainResult train(DataMetadata metaData, TaskInfo.PBTrainInfo trainInfo,
            Path dataPath, Path trainParamPath, Path newBackUpPath, Path outputPath) {
        if (isFinalized) {
            FLLogger.e("Naive object is finalized.");
            return null;
        }
        String trainInfoJsonStr = createTrainInfoStr(metaData, trainInfo, trainParamPath, newBackUpPath, outputPath);
        if (trainInfoJsonStr == null) {
            FLLogger.e("Input is invalid");
            return null;
        }
        FLLogger.d("Call native Training.");
        String trainingResultJson = mLinearHLCRJni.Training(mNativePointer, trainInfoJsonStr);
        FLLogger.d(trainingResultJson);
        return parseTrainResult(trainingResultJson, newBackUpPath, outputPath);
    }

    public TaskResult.PBEvaluationResult evaluate(
            DataMetadata metaData,
            TaskInfo.PBEvaluationInfo evaluationInfo,
            Path dataPath, Path evaluvationPath, Path outputPath) {
        if (isFinalized) {
            FLLogger.e("Naive object is finalized.");
            return null;
        }
        String evaluationInfoStr = createEvaluationInfoStr(metaData, evaluationInfo, outputPath);
        if (evaluationInfoStr == null) {
            FLLogger.e("Input is invalid");
            return null;
        }
        FLLogger.d("Call native Evaluation.");
        String evaluationResultJson = mLinearHLCRJni.Evaluation(mNativePointer, evaluationInfoStr);
        FLLogger.d(evaluationResultJson);
        return parseEvaluationResult(evaluationResultJson, outputPath);
    }

    public TensorMap predict(TensorMap input) {
        if (isFinalized) {
            FLLogger.e("Naive object is finalized.");
            return null;
        }
        String predictInfoJsonStr = createPredictInfoStr(input);
        if (predictInfoJsonStr == null) {
            FLLogger.e("Input is invalid");
            return null;
        }
        FLLogger.d("Call native Prediction.");
        String predictResultJsonStr = mLinearHLCRJni.Prediction(mNativePointer, predictInfoJsonStr);
        String predictResultStr = parsePredictionResult(predictResultJsonStr);
        FLLogger.d("Predicted result is " + predictResultStr);
        return TensorMap.fromJsonString(predictResultStr);
    }

    public int updateClusterMapping(TaskInfo.PBDeployInfo deployInfo, DataMetadata metaData,
            Path preprocessParamPath, Path calibrateInfoDirPath, Path newBackUpPath) {
        if (isFinalized) {
            FLLogger.e("Naive object is finalized.");
            return 1;
        }
        String updateInfoJsonStr = createUpdateInfoStr(deployInfo, metaData, preprocessParamPath, calibrateInfoDirPath, newBackUpPath);
        if (updateInfoJsonStr == null) {
            FLLogger.e("Input is invalid");
            return 1;
        }
        FLLogger.d("Call native Update cluaster mapping.");
        String updateInfoResultJson = mLinearHLCRJni.UpdateInfo(mNativePointer, updateInfoJsonStr);
        FLLogger.d(updateInfoResultJson);
        return parseUpdateInfoResult(updateInfoResultJson, newBackUpPath);
    }

    private String createModelInfoStr(LinearHLCR.PBLinearHLCRGlobalModel modelInfo, Path backUpPath, Path modelPath) {
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize modelInfoJson = com.sony.fl.json.LinearFedHLCR.parameters.Initialize.newInstance();
        for (String s : modelInfo.getLinearRegressionFileNamesList()) {
            Path modelFilePath = modelPath.resolve(s).toAbsolutePath();
            if (!Files.exists(modelFilePath)) {
                FLLogger.e(modelFilePath.toString() + " is not found.");
                return null;
            }
            modelInfoJson.parameters.server.linearModels.add(modelFilePath.toString());
        }

        Path hlcrParamFilePath = modelPath.resolve(
                modelInfo.getHLCRParamsFileName()).toAbsolutePath();
        if (!Files.exists(hlcrParamFilePath)) {
            FLLogger.e(hlcrParamFilePath.toString() + " is not found.");
            return null;
        }
        modelInfoJson.parameters.server.globalWeight = hlcrParamFilePath.toString();

        if (backUpPath == null) {
            FLLogger.d("backUpPath is null.");
            return Json.serialize(modelInfoJson);
        }
        Path clusterMapFilePath = backUpPath.resolve(CLUSTER_MAP_FILE_NAME).toAbsolutePath();
        if (!Files.exists(clusterMapFilePath)) {
            FLLogger.w(clusterMapFilePath.toString() + " is not found.");
        } else {
            modelInfoJson.parameters.internal.clusterMap = clusterMapFilePath.toString();
        }
        return Json.serialize(modelInfoJson);
    }

    private String createTrainInfoStr(DataMetadata metaData, TaskInfo.PBTrainInfo trainInfo, Path trainParamPath, Path newBackUpPath, Path outputPath) {
        Path trainParamFilePath = trainParamPath.resolve(trainInfo.getLinearHLCRTrainInfo().getHyperparamsFileName()).toAbsolutePath();
        if (!Files.exists(trainParamFilePath)) {
            FLLogger.e(trainParamFilePath.toString() + " is not found.");
            return null;
        }
        com.sony.fl.json.LinearFedHLCR.parameters.Training trainingJson = com.sony.fl.json.LinearFedHLCR.parameters.Training.newInstance();
        trainingJson.parameters.server.hyperParams = trainParamFilePath.toString();
        trainingJson.parameters.client.dataSet = metaData.toJsonString();
        trainingJson.parameters.server.output = outputPath.toAbsolutePath().toString();
        trainingJson.parameters.client.output = newBackUpPath.toAbsolutePath().toString();
        return Json.serialize(trainingJson);
    }

    private String createEvaluationInfoStr(DataMetadata metaData, TaskInfo.PBEvaluationInfo evaluationInfo, Path outputPath) {
        com.sony.fl.json.LinearFedHLCR.parameters.Evaluation evaluationJson = com.sony.fl.json.LinearFedHLCR.parameters.Evaluation.newInstance();
        evaluationJson.parameters.server.output = outputPath.toAbsolutePath().toString();
        evaluationJson.parameters.client.dataSet = metaData.toJsonString();
        return Json.serialize(evaluationJson);
    }

    private String createPredictInfoStr(TensorMap input) {
        com.sony.fl.json.LinearFedHLCR.parameters.Prediction predictionJson = com.sony.fl.json.LinearFedHLCR.parameters.Prediction.newInstance();
        predictionJson.parameters.application.data = input.toJsonString();
        return Json.serialize(predictionJson);
    }

    private String createUpdateInfoStr(
        TaskInfo.PBDeployInfo deployInfo, DataMetadata metaData,
        Path preprocessParamPath, Path calibrateInfoDirPath, Path newBackUpPath) {
        Path updateParamFilePath = calibrateInfoDirPath.resolve(
                HYPER_PARAM_FILE_NAME).toAbsolutePath();
        if (!Files.exists(updateParamFilePath)) {
            FLLogger.e(updateParamFilePath.toString() + " is not found.");
            return null;
        }
        com.sony.fl.json.LinearFedHLCR.parameters.UpdateInfo updateInfoJson = com.sony.fl.json.LinearFedHLCR.parameters.UpdateInfo.newInstance();
        updateInfoJson.parameters.server.hyperParams = updateParamFilePath.toString();
        updateInfoJson.parameters.client.dataSet = metaData.toJsonString();
        updateInfoJson.parameters.client.output = newBackUpPath.toAbsolutePath().toString();
        return Json.serialize(updateInfoJson);
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
        mLinearHLCRJni.Finalize(mNativePointer);
        isFinalized = true;
    }

    private TaskResult.PBTrainResult parseTrainResult(String trainResultJson, Path backUpPath, Path outputPath) {
        // if (trainResultJson == null || trainResultJson.isEmpty()) {
        //     FLLogger.e("updateInfoResultStr is null.");
        //     return null;
        // }
        if (trainResultJson == null) {
            FLLogger.e("trainResultJson is null.");
            return null;
        }
        FLLogger.d("### trainResultJson" + System.lineSeparator() + trainResultJson);
        com.sony.fl.json.LinearFedHLCR.results.Training trainResult = Json.deserialize(trainResultJson, com.sony.fl.json.LinearFedHLCR.results.Training.class);
        if (trainResult == null) {
            FLLogger.e("\""+ trainResultJson +"\" can not be JSON deserialized.");
            return null;
        }
        if (trainResult.results.state == null) {
            FLLogger.e("Training.results.state is null.");
            return null;
        }
        if (trainResult.results.state != 0) {
            FLLogger.e("Training failed with state " + trainResult.results.state + ". (" + trainResult.results.description + ")");
            return null;
        }
        if (trainResult.results.server.linearModels == null) {
            FLLogger.e("Training.results.server.linearModels is null.");
            return null;
        }
        if (trainResult.results.server.localCount == null) {
            FLLogger.e("Training.results.server.localCount is null.");
            return null;
        }
        if (trainResult.results.server.validationMetrix == null) {
            FLLogger.e("Training.results.server.validationMetrix is null.");
            return null;
        }
        if (trainResult.results.client.clusterMap == null) {
            FLLogger.e("Training.results.client.clusterMap is null.");
            return null;
        }

        List<String> linearModels = trainResult.results.server.linearModels;
        int K = linearModels.size();
        if (K <= 0) {
            FLLogger.e(K + " is invalid length.");
            return null;
        }

        TaskResult.PBTrainResult.Builder trainResultBuilder = TaskResult.PBTrainResult.newBuilder();
        LinearHLCR.PBLinearHLCRLocalModel.Builder linearHLCRBuilder = LinearHLCR.PBLinearHLCRLocalModel.newBuilder();
        for (String linearModel : linearModels) {
            Path linearFile = Paths.get(linearModel);
            FLLogger.d("linearFile:" + linearFile.toString());
            if (!Files.exists(linearFile)) {
                FLLogger.e(linearFile.toString() + " is not found.");
                return null;
            }
            linearHLCRBuilder.addLinearRegressionFileNames(parseFileName(outputPath, linearFile.toString()));
        }

        Path hlcrParamFile = Paths.get(trainResult.results.server.localCount);
        FLLogger.d("hlcrParamFile:" + hlcrParamFile.toString());
        if (!Files.exists(hlcrParamFile)) {
            FLLogger.e(hlcrParamFile.toString() + " is not found.");
            return null;
        }
        linearHLCRBuilder.setHLCRParamsFileName(parseFileName(outputPath, trainResult.results.server.localCount));

        Path validationMetrixFile = Paths.get(trainResult.results.server.validationMetrix);
        FLLogger.d("validationMetrixFile:" + validationMetrixFile.toString());
        if (!Files.exists(validationMetrixFile)) {
            FLLogger.e(validationMetrixFile.toString() + " is not found.");
            return null;
        }
        trainResultBuilder.setLinearHLCRLocalModel(linearHLCRBuilder)
                .setValidationMetrixFileName(parseFileName(outputPath, trainResult.results.server.validationMetrix));

        FLLogger.d("clisterMap:" + trainResult.results.client.clusterMap);
        FLLogger.d("CLUSTER_MAP_FILE_NAME:" + CLUSTER_MAP_FILE_NAME);
        FLLogger.d(String.valueOf(Paths.get(trainResult.results.client.clusterMap).endsWith(CLUSTER_MAP_FILE_NAME)));
        if (!(Paths.get(trainResult.results.client.clusterMap).endsWith(CLUSTER_MAP_FILE_NAME))) {
            FLLogger.e(trainResult.results.client.clusterMap + " is invalid cluster mapping file name");
            return null;
        }
        if (!Files.exists(Paths.get(trainResult.results.client.clusterMap))) {
            FLLogger.e(trainResult.results.client.clusterMap + " is not found.");
            return null;
        }

        return trainResultBuilder.build();
    }

    private String parsePredictionResult(String predictionResultJson) {
        if (predictionResultJson == null) {
            FLLogger.e("predictionResultJson is null.");
            return null;
        }
        FLLogger.d("### predictionResultJson" + System.lineSeparator() + predictionResultJson);
        com.sony.fl.json.LinearFedHLCR.results.Prediction prediction = Json.deserialize(predictionResultJson, com.sony.fl.json.LinearFedHLCR.results.Prediction.class);
        if (prediction == null) {
            FLLogger.e("predictionResultJson cannot be JSON deserialized.");
            return null;
        }
        if (prediction.results.state == null) {
            FLLogger.e("Prediction.results.state is null.");
            return null;
        }
        if (prediction.results.state != 0) {
            FLLogger.e("Prediction failed with state " + prediction.results.state + ". (" + prediction.results.description + ")");
            return null;
        }
        if (prediction.results.application.predictionResult == null) {
            FLLogger.e("Prediction.results.application.predictionResult is null.");
            return null;
        }
        return prediction.results.application.predictionResult;
    }

    private TaskResult.PBEvaluationResult parseEvaluationResult(String evaluationResultJson, 
            Path outputPath) {
        // if (evaluationResultJson == null || evaluationResultJson.isEmpty()) {
        //     FLLogger.e("evaluationResultStr is null");
        //     return null;
        // }
        if (evaluationResultJson == null) {
            FLLogger.e("evaluationResultJson is null.");
            return null;
        }
        FLLogger.d("### evaluationResultJson" + System.lineSeparator() + evaluationResultJson);
        com.sony.fl.json.LinearFedHLCR.results.Evaluation evaluationResult = Json.deserialize(evaluationResultJson, com.sony.fl.json.LinearFedHLCR.results.Evaluation.class);
        if (evaluationResult == null) {
            FLLogger.e("predictionResultJson cannot be JSON deserialized.");
            return null;
        }
        if (evaluationResult.results.state == null) {
            FLLogger.e("Evaluatio.results.state is null.");
            return null;
        }
        if (evaluationResult.results.state != 0) {
            FLLogger.e("Evaluation failed with state " + evaluationResult.results.state + ". (" + evaluationResult.results.description + ")");
            return null;
        }

        if (evaluationResult.results.server.evaluationResult == null) {
            FLLogger.e("Evaluation.results.server.evaluationResult is null");
            return null;
        }

        DataMetadata metaData = DataMetadata.fromJsonString(evaluationResult.results.server.evaluationResult);
        String tensor_map_file = metaData.get("tensor_map_file");
        if (tensor_map_file == null) {
            FLLogger.e("'tensor_map_file' not found in DataMetadata. (" + evaluationResult.results.server.evaluationResult + ")");
            return null;
        }
        String save_result = metaData.get("save_result");
        if (save_result != null) {
            if (!(save_result.equals("success"))) {
                FLLogger.e("save result is " + save_result + " (" + evaluationResult.results.server.evaluationResult + ")");
                return null;
            }
            if (!Files.exists(Paths.get(tensor_map_file))) {
                FLLogger.e(tensor_map_file + " is not found. (" + evaluationResult.results.server.evaluationResult + ")");
                return null;
            }
        }

        TaskResult.PBEvaluationResult.Builder builder = TaskResult.PBEvaluationResult.newBuilder();
        builder.setEvaluationResultFileName(parseFileName(outputPath, tensor_map_file));
        return builder.build();
    }

    private int parseUpdateInfoResult(String updateInfoResultJson, Path backUpPath) {
        // if (updateInfoResultJson == null || updateInfoResultJson.isEmpty()) {
        //     FLLogger.e("updateInfoResultStr is null.");
        //     return 1;
        // }
        if (updateInfoResultJson == null) {
            FLLogger.e("updateInfoResultJson is null.");
            return 1;
        }
        FLLogger.d("### updateInfoResultJson" + System.lineSeparator() + updateInfoResultJson);
        com.sony.fl.json.LinearFedHLCR.results.UpdateInfo updateInfoResult = Json.deserialize(updateInfoResultJson, com.sony.fl.json.LinearFedHLCR.results.UpdateInfo.class);
        if (updateInfoResult == null) {
            FLLogger.e("updateInfoResultJson cannot be JSON deserialized.");
            return 1;
        }
        if (updateInfoResult.results.state == null) {
            FLLogger.e("UpdateInfo.results.state is null.");
            return 1;
        }
        if (updateInfoResult.results.state != 0) {
            FLLogger.e("UpdateInfo failed with state " + updateInfoResult.results.state + ". (" + updateInfoResult.results.description + ")");
            return 1;
        }
        if (updateInfoResult.results.client.clusterMap == null) {
            FLLogger.e("updateInfo.results.client.clusterMap is null.");
            return 1;
        }
        if (!(Paths.get(updateInfoResult.results.client.clusterMap).endsWith(CLUSTER_MAP_FILE_NAME))) {
            FLLogger.e(updateInfoResult.results.client.clusterMap + " is invalid cluster mapping file name");
            return 1;
        }
        if (!Files.exists(Paths.get(updateInfoResult.results.client.clusterMap))) {
            FLLogger.e(updateInfoResult.results.client.clusterMap + " is not found.");
            return 1;
        }
        return 0;
    }

    private String parseFileName(Path dirPath, String filePathStr) {
        Path absoluteDirPath = dirPath.toAbsolutePath();
        Path absoluteFilePath = Paths.get(filePathStr).toAbsolutePath();
        // FLLogger.d("#########     dirPath: " + absoluteDirPath.toString());
        // FLLogger.d("#########    filepath: " + absoluteFilePath.toString());
        // FLLogger.d("#########   dir namec: " + String.valueOf(absoluteDirPath.getNameCount()));
        // FLLogger.d("#########  file namec: " + String.valueOf(absoluteFilePath.getNameCount()));
        String fileNameStr = filePathStr;
        if (absoluteDirPath.getNameCount() < absoluteFilePath.getNameCount()) {
            fileNameStr = absoluteFilePath.subpath(absoluteDirPath.getNameCount(), absoluteFilePath.getNameCount()).toString();
        }
        if (fileNameStr.equals(filePathStr)) {
            FLLogger.w("Could not parse file name from \"" + filePathStr.toString() + "\".");
        }

        return fileNameStr;
    }

}
