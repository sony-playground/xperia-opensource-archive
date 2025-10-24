package com.sony.fl.algorithm;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Collections;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.sony.fl.TrainManager.EvaluationResult;
import com.sony.fl.exception.FLException;
import com.sony.fl.json.Json;
import com.sony.fl.logger.FLLogger;
import com.sony.fl.pb.LinearHLCR;
import com.sony.fl.pb.TaskInfo;
import com.sony.fl.pb.TaskResult;
import com.sony.fl.pb.TaskResult.PBEvaluationResult;
import com.sony.fl.utils.Const;
import com.sony.fl.utils.CreatePBForTest;
import com.sony.fl.utils.DataMetadataUtil;
import com.sony.fl.utils.PBChecker;
import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.DataSerializer;
import com.sony.fl.tensor.Tensor;
import com.sony.fl.tensor.TensorMap;
import com.sony.fl.tensor.TensorShape;

import org.apache.commons.io.file.PathUtils;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class TestLinearFedHLCRClient {
    public Path inputPath = Paths.get("src/test/resources/input");
    public Path outputPath = Paths.get("src/test/resources/output");
    public Path oldBackUpPath = Paths.get("src/test/resources/old");
    public Path newBackUpPath = Paths.get("src/test/resources/new");
    public Path LinearHLCRSamplePath = Paths.get("src/test/resources/LinearHLCR");
    LinearFedHLCRClient client;

    public DataMetadata data;

    @Before
    public void setUp() throws IOException {
        Files.createDirectories(inputPath);
        Files.createDirectories(outputPath);
        Files.createDirectories(oldBackUpPath);
        Files.createDirectories(newBackUpPath);
    }

    @After
    public void clean() throws IOException {
        PathUtils.deleteDirectory(inputPath);
        PathUtils.deleteDirectory(outputPath);
        PathUtils.deleteDirectory(oldBackUpPath);
        PathUtils.deleteDirectory(newBackUpPath);
    }

    public void setUpClient() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        LinearHLCR.PBLinearHLCRGlobalModel modelInfo = CreatePBForTest.createValidLinearHLCRGlobalModel();
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("LinearHLCRGlobalWeight.json"),      inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("LinearRegressionGlobalModel.json"), inputPath.resolve("LinearRegressionGlobalModel.json"));
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("LinearHLCRTrainHyperParams.json"),  inputPath.resolve("LinearHLCRTrainHyperParams.json"));
        Files.copy(LinearHLCRSamplePath.resolve("back_up").resolve(LinearFedHLCRClient.HYPER_PARAM_FILE_NAME), oldBackUpPath.resolve(LinearFedHLCRClient.HYPER_PARAM_FILE_NAME));
        Files.copy(LinearHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_DAT_FILE_NAME), inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.copy(LinearHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_IDX_FILE_NAME), inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));

        client = new LinearFedHLCRClient(modelInfo, oldBackUpPath, inputPath);
        PathUtils.delete(inputPath.resolve("LinearHLCRGlobalWeight.json"));
        PathUtils.delete(inputPath.resolve("LinearRegressionGlobalModel.json"));
        PathUtils.delete(inputPath.resolve("LinearHLCRTrainHyperParams.json"));
        PathUtils.delete(oldBackUpPath.resolve(LinearFedHLCRClient.HYPER_PARAM_FILE_NAME));

        Path datFile = Paths.get(inputPath.toString(), Const.TEST_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TEST_DATA_IDX_FILE_NAME);
        DataMetadata data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(data, "tensor_map_file", datFile.toAbsolutePath().toString());
        DataMetadataUtil.set(data, "tensor_map_index_file", idxFile.toAbsolutePath().toString());
        DataMetadataUtil.set(data, "save_result", "success");
        this.data = data;
    }

    // // TODO: delete?
    // private com.sony.fl.json.LinearFedHLCR.parameters.Training trainParametersJson() {
    //     String json =
    //         "{"
    //             + "\"method\":\"Training\","
    //             + "\"parameters\":{"
    //                 + "\"server\":{"
    //                     + "\"hyperParams\":\"" + outputPath.resolve("LinearHLCRGlobalWeight.json").toString() + "\"," // TODO: stub file name
    //                     + "\"output\":\"" + outputPath.toString() + "\""
    //                 + "},"
    //                 + "\"client\":{"
    //                     + "\"dataSet\":\"" + this.data.toJsonString() + "\"" // TODO: stub file name
    //                     + "\"output\":\"" + newBackUpPath.toString() + "\"" // TODO: stub file name
    //                 + "}"
    //             + "}"
    //         + "}";
    //         return Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.results.Training.class);
    // }

    // private com.sony.fl.json.LinearFedHLCR.parameters.Evaluation evaluationParametersJson() {
    //     String json =
    //         "{"
    //             + "\"method\":\"Training\","
    //             + "\"results\":{"
    //                 + "\"state\":0,"
    //                 + "\"server\":{"
    //                     + "\"linearModels\":["
    //                         + "\"" + outputPath.resolve("LinearRegressionGlobalModel1.json").toString() + "\","
    //                         + "\"" + outputPath.resolve("LinearRegressionGlobalModel2.json").toString() + "\""
    //                     + "],"
    //                     + "\"localCount\":\"" + outputPath.resolve("LinearHLCRGlobalWeight.json").toString() + "\","
    //                     + "\"validationMetrix\":\"" + outputPath.resolve("validation_metrix.dat").toString() + "\""
    //                 + "},"
    //                 + "\"client\":{"
    //                     + "\"clusterMap\":\"" + newBackUpPath.resolve("cluster_map.json").toString() + "\""
    //                 + "}"
    //             + "}"
    //         + "}";
    //         return Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.results.Training.class);
    // }

    private com.sony.fl.json.LinearFedHLCR.results.Training trainResultJson() {
        String json =
            "{"
                + "\"method\":\"Training\","
                + "\"results\":{"
                    + "\"state\":0,"
                    + "\"server\":{"
                        + "\"linearModels\":["
                            + "\"" + outputPath.resolve("LinearRegressionGlobalModel1.json").toString() + "\","
                            + "\"" + outputPath.resolve("LinearRegressionGlobalModel2.json").toString() + "\""
                        + "],"
                        + "\"localCount\":\"" + outputPath.resolve("LinearHLCRGlobalWeight.json").toString() + "\","
                        + "\"validationMetrix\":\"" + outputPath.resolve("validation_metrix.dat").toString() + "\""
                    + "},"
                    + "\"client\":{"
                        + "\"clusterMap\":\"" + newBackUpPath.resolve("cluster_map.json").toString() + "\""
                    + "}"
                + "}"
            + "}";
            return Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.results.Training.class);
    }

    private com.sony.fl.json.LinearFedHLCR.results.Evaluation evaluationResultJson() {
        String json =
            "{"
                + "\"method\":\"Evaluation\","
                + "\"results\":{"
                    + "\"state\":0,"
                    + "\"server\":{"
                        + "\"evaluationResult\": \"{\\\"save_result\\\":\\\"success\\\",\\\"tensor_map_file\\\":\\\"" + outputPath.resolve("Evaluation_Result.jsonl").toString() + "\\\",\\\"tensor_map_index_file\\\":\\\"" + outputPath.resolve("Evaluation_Result.txt").toString() + "\\\"}\"" // stub file name
                    + "}"
                + "}"
            + "}";
            return Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.results.Evaluation.class);
    }

    private com.sony.fl.json.LinearFedHLCR.results.Prediction predictionResultJson() {
        String json =
            "{"
                + "\"method\":\"Prediction\","
                + "\"results\":{"
                    + "\"state\":0,"
                    + "\"application\":{"
                        + "\"predictionResult\": \"{\\\"y_pred\\\":{\\\"shape\\\":[1],\\\"value\\\":[0.1798144280910492]}}" + "\""
                    + "}"
                + "}"
            + "}";
            return Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.results.Prediction.class);
    }


    private com.sony.fl.json.LinearFedHLCR.results.UpdateInfo updateInfoResultJson() {
        String json =
            "{"
                + "\"method\":\"UpdateInfo\","
                + "\"results\":{"
                    + "\"state\":0,"
                    + "\"client\":{"
                        + "\"clusterMap\":\"" + newBackUpPath.resolve("cluster_map.json").toString() + "\""
                    + "}"
                + "}"
            + "}";
            return Json.deserialize(json, com.sony.fl.json.LinearFedHLCR.results.UpdateInfo.class);
    }

/*
 #####
#     #   ####   #    #   ####    #####  #####   #    #   ####    #####   ####
#        #    #  ##   #  #          #    #    #  #    #  #    #     #    #    #
#        #    #  # #  #   ####      #    #    #  #    #  #          #    #    #
#        #    #  #  # #       #     #    #####   #    #  #          #    #    #
#     #  #    #  #   ##  #    #     #    #   #   #    #  #    #     #    #    #
 #####    ####   #    #   ####      #    #    #   ####    ####      #     ####
*/

    @Test
    public void testConstructorWithValidInput() throws IOException, FLException {
        LinearHLCR.PBLinearHLCRGlobalModel modelInfo = CreatePBForTest.createValidLinearHLCRGlobalModel();
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("LinearHLCRGlobalWeight.json"),      inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("LinearRegressionGlobalModel.json"), inputPath.resolve("LinearRegressionGlobalModel.json"));
        client = new LinearFedHLCRClient(modelInfo, oldBackUpPath, inputPath);
        // Files.copy(LinearHLCRSamplePath.resolve("back_up").resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME), inputPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        Files.copy(LinearHLCRSamplePath.resolve("back_up").resolve(LinearFedHLCRClient.HYPER_PARAM_FILE_NAME), inputPath.resolve(LinearFedHLCRClient.HYPER_PARAM_FILE_NAME));
        boolean flag = false;
        try {
            client = new LinearFedHLCRClient(modelInfo, oldBackUpPath, inputPath);
        } catch (FLException e) {
            flag = true;
        }
        assertFalse(flag);
    }

    @Test
    public void testConstructorWithInvalidInput2() throws IOException, FLException {
        LinearHLCR.PBLinearHLCRGlobalModel modelInfo = CreatePBForTest.createValidLinearHLCRGlobalModel();
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("Invalid_LinearHLCRGlobalWeight.json"), inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("LinearRegressionGlobalModel.json"), inputPath.resolve("LinearRegressionGlobalModel.json"));
        boolean flag = false;
        try {
            client = new LinearFedHLCRClient(modelInfo, oldBackUpPath, inputPath);
        } catch (FLException e) {
            flag = true;
        }
        assertTrue(flag);
    }

    @Test
    public void testConstructorWithInvalidInput() throws IOException {
        LinearHLCR.PBLinearHLCRGlobalModel modelInfo = CreatePBForTest.createValidLinearHLCRGlobalModel();
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("LinearRegressionGlobalModel.json"), inputPath.resolve("LinearRegressionGlobalModel.json"));
        Files.createFile(inputPath.resolve("XXXLinearHLCRGlobalWeight.json"));
        boolean flag = false;
        try {
            client = new LinearFedHLCRClient(modelInfo, inputPath, oldBackUpPath);
        } catch (FLException e) {
            flag = true;
        }
        assertTrue(flag);
    }

/*
#######
   #     #####     ##       #    #    #
   #     #    #   #  #      #    ##   #
   #     #    #  #    #     #    # #  #
   #     #####   ######     #    #  # #
   #     #   #   #    #     #    #   ##
   #     #    #  #    #     #    #    #
*/
    @Test
    public void testTrainWithValidInput() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpClient();
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForLinearHLCR();
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("LinearHLCRGlobalWeight.json"),      inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("LinearRegressionGlobalModel.json"), inputPath.resolve("LinearRegressionGlobalModel.json"));
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("LinearHLCRTrainHyperParams.json"),  inputPath.resolve("LinearHLCRTrainHyperParams.json"));
        // Files.copy(LinearHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_DAT_FILE_NAME),
        //         inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        // Files.copy(LinearHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_IDX_FILE_NAME),
        //         inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));

        DataMetadata dataMetadata = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(dataMetadata, "tensor_map_file", inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME).toAbsolutePath().toString());
        DataMetadataUtil.set(dataMetadata, "tensor_map_index_file", inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME).toAbsolutePath().toString());
        DataMetadataUtil.set(dataMetadata, "save_result", "success");
        TaskResult.PBTrainResult trainResult = client.train(dataMetadata, trainInfo, inputPath, inputPath, newBackUpPath, outputPath);
        assertNotNull(trainResult);
        assertEquals(0, PBChecker.checkPBTrainResult(trainResult, trainInfo));
        assertTrue(trainResult.hasLinearHLCRLocalModel());
    }

    @Test
    public void testTrainWithInvalidInput() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpClient();
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForLinearHLCR();
        // Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("Hyper_Param.dat"), 
        //         inputPath.resolve("Hyper_Param.dat"));
        Files.copy(LinearHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_DAT_FILE_NAME), 
                inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.copy(LinearHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_IDX_FILE_NAME), 
                inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
        DataMetadata dataMetadata = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(dataMetadata, "tensor_map_file", inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME).toString());
        DataMetadataUtil.set(dataMetadata, "tensor_map_index_file", inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME).toString());
        DataMetadataUtil.set(dataMetadata, "save_result", "success");
        assertNull(client.train(dataMetadata, trainInfo, inputPath, inputPath, newBackUpPath, outputPath));
    }

    @Test
    public void testTrainWithInvalidInputLinearHLCRGlobalWeight() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpClient();
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForLinearHLCR();
        Files.copy(LinearHLCRSamplePath.resolve("back_up").resolve("Invalid_LinearHLCRTrainHyperParams.json"), inputPath.resolve("LinearHLCRTrainHyperParams.json"));

        DataMetadata dataMetadata = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(dataMetadata, "tensor_map_file", LinearHLCRSamplePath.resolve("SNE").resolve("Data.jsonl").toAbsolutePath().toString());
        DataMetadataUtil.set(dataMetadata, "tensor_map_index_file", LinearHLCRSamplePath.resolve("SNE").resolve("Data.txt").toAbsolutePath().toString());
        DataMetadataUtil.set(dataMetadata, "save_result", "success");
        TaskResult.PBTrainResult trainResult = client.train(dataMetadata, trainInfo, inputPath, inputPath, newBackUpPath, outputPath);
        assertNull(trainResult);
        assertEquals(1, PBChecker.checkPBTrainResult(trainResult, trainInfo));
    }

    @Test
    public void testTrainWithInvalidTensorMapFile() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpClient();
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForLinearHLCR();
        Files.copy(LinearHLCRSamplePath.resolve("back_up").resolve("LinearHLCRTrainHyperParams.json"), inputPath.resolve("LinearHLCRTrainHyperParams.json"));
        Files.copy(LinearHLCRSamplePath.resolve("data").resolve("Invalid_TestData.jsonl"), inputPath.resolve("Invalid_TestData.jsonl"));

        DataMetadata dataMetadata = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(dataMetadata, "tensor_map_file", inputPath.resolve("Invalid_TestData.jsonl").toAbsolutePath().toString());
        DataMetadataUtil.set(dataMetadata, "tensor_map_index_file", inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME).toAbsolutePath().toString());
        DataMetadataUtil.set(dataMetadata, "save_result", "success");
        TaskResult.PBTrainResult trainResult = client.train(dataMetadata, trainInfo, inputPath, inputPath, newBackUpPath, outputPath);
        assertNull(trainResult);
        assertEquals(1, PBChecker.checkPBTrainResult(trainResult, trainInfo));
    }

/*
 ######  #    #    ##    #       #    #    ##     #####  ######
 #       #    #   #  #   #       #    #   #  #      #    #
 #####   #    #  #    #  #       #    #  #    #     #    #####
 #       #    #  ######  #       #    #  ######     #    #
 #        #  #   #    #  #       #    #  #    #     #    #
 ######    ##    #    #  ######   ####   #    #     #    ######
*/

    @Test
    public void testEvaluateWithValidInput()
            throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException,
            InvocationTargetException {
        setUpClient();
        TaskInfo.PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForLinearHLCR();
        TaskResult.PBEvaluationResult evaluationResult = client.evaluate(this.data, evaluationInfo, inputPath, inputPath, outputPath);
        assertNotNull(evaluationResult);
        assertEquals(0, PBChecker.checkPBEvaluationResult(evaluationResult, evaluationInfo));
    }

    // TODO: no case. because not used preprocess params.
    // @Test
    // public void testEvaluateWithInvalidInput()
    //         throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException,
    //         InvocationTargetException {
    //     setUpClient();
    //     TaskInfo.PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForLinearHLCR();
    //     Files.copy(LinearHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_DAT_FILE_NAME),
    //             inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
    //     Files.copy(LinearHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_IDX_FILE_NAME),
    //             inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
    //     assertNull(client.evaluate(this.data, evaluationInfo, inputPath, inputPath, outputPath));
    // }

/*
 #####   #####   ######  #####      #     ####    #####
 #    #  #    #  #       #    #     #    #    #     #
 #    #  #    #  #####   #    #     #    #          #
 #####   #####   #       #    #     #    #          #
 #       #   #   #       #    #     #    #    #     #
 #       #    #  ######  #####      #     ####      #
*/
    @Test
    public void testPredictForSNEWithValidInput() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpClient();
        String groupLabel = "group0";
        Double[] flattenedSequenceData = new Double[] { 3.0, 3.0 };
        assertNotEquals(null, flattenedSequenceData);
        TensorMap tensorMap = TensorMap.newInstance();
        tensorMap.set(LinearFedHLCRClient.TENSOR_X, Tensor.newTensor(TensorShape.createShape(2), flattenedSequenceData));
        tensorMap.set(LinearFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));
        TensorMap result = client.predict(tensorMap);
        assertNotNull(result);
        Tensor<Double> resultLabel = result.get(LinearFedHLCRClient.TENSOR_Y_PRED);
        assertNotNull(resultLabel);
        assertTrue(resultLabel.isScalar());
        Double predictLabel = resultLabel.getValue();
        assertEquals(3.5, predictLabel, 1e-5);
    }

/*
 #    #  #####   #####     ##     #####  ###### ##   ##    ##    #####
 #    #  #    #  #    #   #  #      #    #      # # # #   #  #   #    #
 #    #  #    #  #    #  #    #     #    #####  #  #  #  #    #  #    #
 #    #  #####   #    #  ######     #    #      #     #  ######  #####
 #    #  #       #    #  #    #     #    #      #     #  #    #  #
  ####   #       #####   #    #     #    ###### #     #  #    #  #
*/

    // TODO:
    @Test
    public void testUpdateClusterMapWithValidInput() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpClient();
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForLinearHLCR();
        Files.copy(LinearHLCRSamplePath.resolve("back_up").resolve(LinearFedHLCRClient.HYPER_PARAM_FILE_NAME),
                inputPath.resolve(LinearFedHLCRClient.HYPER_PARAM_FILE_NAME));
        assertEquals(0, client.updateClusterMapping(deployInfo, this.data, inputPath, inputPath, newBackUpPath));
    }

    @Test
    public void testUpdateClusterMapWithInvalidInput() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpClient();
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForLinearHLCR();
        assertEquals(1, client.updateClusterMapping(deployInfo, this.data, inputPath, inputPath, newBackUpPath));
    }

/*
#     #                                   ###
##   ##   ####   #####   ######  #         #     #    #  ######   ####
# # # #  #    #  #    #  #       #         #     ##   #  #       #    #
#  #  #  #    #  #    #  #####   #         #     # #  #  #####   #    #
#     #  #    #  #    #  #       #         #     #  # #  #       #    #
#     #  #    #  #    #  #       #         #     #   ##  #       #    #
#     #   ####   #####   ######  ######   ###    #    #  #        ####
*/

    @Test
    public void testCreateModelInfoStrWithValidInput() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("createModelInfoStr", 
                LinearHLCR.PBLinearHLCRGlobalModel.class, Path.class, Path.class);
        method.setAccessible(true);
        LinearHLCR.PBLinearHLCRGlobalModel modelInfo = CreatePBForTest.createValidLinearHLCRGlobalModel();
        Files.createFile(this.inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(this.inputPath.resolve("LinearRegressionGlobalModel.json"));
        Files.createFile(this.oldBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        String modelInfoStr = (String)method.invoke(client, modelInfo, oldBackUpPath, inputPath);

        com.sony.fl.json.LinearFedHLCR.parameters.Initialize modelInfoStrs = Json.deserialize(modelInfoStr, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);
        assertEquals(this.inputPath.resolve("LinearHLCRGlobalWeight.json").toAbsolutePath(), Paths.get(modelInfoStrs.parameters.server.globalWeight));
        assertEquals(this.oldBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME).toAbsolutePath(), Paths.get(modelInfoStrs.parameters.internal.clusterMap));
        for(int i=0;i<modelInfoStrs.parameters.server.linearModels.size();i++) {
            assertEquals(this.inputPath.resolve("LinearRegressionGlobalModel.json").toAbsolutePath(), Paths.get(modelInfoStrs.parameters.server.linearModels.get(i)));
        }
    }

    @Test
    public void testCreateModelInfoStrWithLinearLegressionFileZero() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("createModelInfoStr", 
                LinearHLCR.PBLinearHLCRGlobalModel.class, Path.class, Path.class);
        method.setAccessible(true);

        LinearHLCR.PBLinearHLCRGlobalModel.Builder builder = LinearHLCR.PBLinearHLCRGlobalModel.newBuilder();
        builder.setHLCRParamsFileName("LinearHLCRGlobalWeight.json");
        // builder.addLinearRegressionFileNames("LinearRegressionGlobalModel.json");
        // builder.addLinearRegressionFileNames("LinearRegressionGlobalModel.json");
        LinearHLCR.PBLinearHLCRGlobalModel modelInfo = builder.build();

        Files.createFile(this.inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(this.inputPath.resolve("LinearRegressionGlobalModel.json"));
        Files.createFile(this.oldBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        String modelInfoStr = (String)method.invoke(client, modelInfo, oldBackUpPath, inputPath);
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize modelInfoStrs = Json.deserialize(modelInfoStr, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);
        assertEquals(this.inputPath.resolve("LinearHLCRGlobalWeight.json").toAbsolutePath(), Paths.get(modelInfoStrs.parameters.server.globalWeight));
        assertEquals(this.oldBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME).toAbsolutePath(), Paths.get(modelInfoStrs.parameters.internal.clusterMap));
        for(int i=0;i<modelInfoStrs.parameters.server.linearModels.size();i++) {
            assertEquals(this.inputPath.resolve("LinearRegressionGlobalModel.json").toAbsolutePath(), Paths.get(modelInfoStrs.parameters.server.linearModels.get(i)));
        }
    }

    @Test
    public void testCreateModelInfoStrWithLinearLegressionFileOne() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("createModelInfoStr", 
                LinearHLCR.PBLinearHLCRGlobalModel.class, Path.class, Path.class);
        method.setAccessible(true);

        LinearHLCR.PBLinearHLCRGlobalModel.Builder builder = LinearHLCR.PBLinearHLCRGlobalModel.newBuilder();
        builder.setHLCRParamsFileName("LinearHLCRGlobalWeight.json");
        builder.addLinearRegressionFileNames("LinearRegressionGlobalModel.json");
        // builder.addLinearRegressionFileNames("LinearRegressionGlobalModel.json");
        LinearHLCR.PBLinearHLCRGlobalModel modelInfo = builder.build();

        Files.createFile(this.inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(this.inputPath.resolve("LinearRegressionGlobalModel.json"));
        Files.createFile(this.oldBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        String modelInfoStr = (String)method.invoke(client, modelInfo, this.oldBackUpPath, this.inputPath);
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize modelInfoStrs = Json.deserialize(modelInfoStr, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);
        assertEquals(this.inputPath.resolve("LinearHLCRGlobalWeight.json").toAbsolutePath(), Paths.get(modelInfoStrs.parameters.server.globalWeight));
        assertEquals(this.oldBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME).toAbsolutePath(), Paths.get(modelInfoStrs.parameters.internal.clusterMap));
        for(int i=0;i<modelInfoStrs.parameters.server.linearModels.size();i++) {
            assertEquals(this.inputPath.resolve("LinearRegressionGlobalModel.json").toAbsolutePath(), Paths.get(modelInfoStrs.parameters.server.linearModels.get(i)));
        }
    }


    @Test
    public void testCreateModelInfoStrWithoutClusterFile() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("createModelInfoStr", 
                LinearHLCR.PBLinearHLCRGlobalModel.class, Path.class, Path.class);
        method.setAccessible(true);
        LinearHLCR.PBLinearHLCRGlobalModel modelInfo = CreatePBForTest.createValidLinearHLCRGlobalModel();
        Files.createFile(inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(oldBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        String modelInfoStr = (String)method.invoke(client, modelInfo, oldBackUpPath, inputPath);
        assertNull(modelInfoStr);
    }

    @Test
    public void testCreateModelInfoStrWithoutHLCRParamFile() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("createModelInfoStr", 
                LinearHLCR.PBLinearHLCRGlobalModel.class, Path.class, Path.class);
        method.setAccessible(true);
        LinearHLCR.PBLinearHLCRGlobalModel modelInfo = CreatePBForTest.createValidLinearHLCRGlobalModel();
        Files.createFile(inputPath.resolve("LinearRegressionGlobalModel.json"));
        Files.createFile(oldBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        String modelInfoStr = (String)method.invoke(client, modelInfo, oldBackUpPath, inputPath);
        assertNull(modelInfoStr);
    }

    @Test
    public void testCreateModelInfoStrWithoutClusterMapFile() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("createModelInfoStr", 
                LinearHLCR.PBLinearHLCRGlobalModel.class, Path.class, Path.class);
        method.setAccessible(true);
        LinearHLCR.PBLinearHLCRGlobalModel modelInfo = CreatePBForTest.createValidLinearHLCRGlobalModel();
        Files.createFile(this.inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(this.inputPath.resolve("LinearRegressionGlobalModel.json"));
        String modelInfoStr = (String)method.invoke(client, modelInfo, oldBackUpPath, inputPath);
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize modelInfoStrs = Json.deserialize(modelInfoStr, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);
        assertEquals(this.inputPath.resolve("LinearHLCRGlobalWeight.json").toAbsolutePath(), Paths.get(modelInfoStrs.parameters.server.globalWeight));
        assertNull(modelInfoStrs.parameters.internal.clusterMap);
        for(int i=0;i<modelInfoStrs.parameters.server.linearModels.size();i++) {
            assertEquals(this.inputPath.resolve("LinearRegressionGlobalModel.json").toAbsolutePath(), Paths.get(modelInfoStrs.parameters.server.linearModels.get(i)));
        }
    }

    @Test
    public void testCreateModelInfoStrWithoutBackUpPath() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("createModelInfoStr", 
                LinearHLCR.PBLinearHLCRGlobalModel.class, Path.class, Path.class);
        method.setAccessible(true);
        LinearHLCR.PBLinearHLCRGlobalModel modelInfo = CreatePBForTest.createValidLinearHLCRGlobalModel();
        Files.createFile(this.inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(this.inputPath.resolve("LinearRegressionGlobalModel.json"));
        Files.createFile(this.oldBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        String modelInfoStr = (String)method.invoke(client, modelInfo, null, inputPath);
        com.sony.fl.json.LinearFedHLCR.parameters.Initialize modelInfoStrs = Json.deserialize(modelInfoStr, com.sony.fl.json.LinearFedHLCR.parameters.Initialize.class);
        assertEquals(this.inputPath.resolve("LinearHLCRGlobalWeight.json").toAbsolutePath(), Paths.get(modelInfoStrs.parameters.server.globalWeight));
        assertNull(modelInfoStrs.parameters.internal.clusterMap);
        for(int i=0;i<modelInfoStrs.parameters.server.linearModels.size();i++) {
            assertEquals(this.inputPath.resolve("LinearRegressionGlobalModel.json").toAbsolutePath(), Paths.get(modelInfoStrs.parameters.server.linearModels.get(i)));
        }
    }

/*
#######                                   ###
   #     #####     ##       #    #    #    #     #    #  ######   ####
   #     #    #   #  #      #    ##   #    #     ##   #  #       #    #
   #     #    #  #    #     #    # #  #    #     # #  #  #####   #    #
   #     #####   ######     #    #  # #    #     #  # #  #       #    #
   #     #   #   #    #     #    #   ##    #     #   ##  #       #    #
   #     #    #  #    #     #    #    #   ###    #    #  #        ####
*/


    @Test
    public void testCreateTrainInfoStrWithValidInput()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("createTrainInfoStr",
                DataMetadata.class, TaskInfo.PBTrainInfo.class , Path.class, Path.class, Path.class);
        method.setAccessible(true);
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForLinearHLCR();
        Files.createFile(inputPath.resolve("LinearHLCRTrainHyperParams.json"));
        String trainInfoStr = (String)method.invoke(
                client, this.data, trainInfo, inputPath, newBackUpPath, outputPath);
        com.sony.fl.json.LinearFedHLCR.parameters.Training createdJson = Json.deserialize(trainInfoStr, com.sony.fl.json.LinearFedHLCR.parameters.Training.class);
        assertNotNull(createdJson.parameters.server.hyperParams);
        assertNotNull(createdJson.parameters.server.output);
        assertNotNull(createdJson.parameters.client.dataSet);
        assertNotNull(createdJson.parameters.client.output);

        // TODO:
        assertEquals(inputPath.resolve("LinearHLCRTrainHyperParams.json").toAbsolutePath().toString(), createdJson.parameters.server.hyperParams);
        assertEquals(outputPath.toAbsolutePath().toString(), createdJson.parameters.server.output);
        assertEquals(this.data.toJsonString(), createdJson.parameters.client.dataSet);
        assertEquals(newBackUpPath.toAbsolutePath().toString(), createdJson.parameters.client.output);
    }

    @Test
    public void testCreateTrainInfoStrWithoutHyperParamFile()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("createTrainInfoStr",
                DataMetadata.class, TaskInfo.PBTrainInfo.class , Path.class, Path.class, Path.class);
        method.setAccessible(true);
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForLinearHLCR();
        Files.createFile(inputPath.resolve("preprocess_params.dat"));
        Files.createFile(inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.createFile(inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
        String trainInfoStr = (String)method.invoke(
                client, this.data, trainInfo, inputPath, newBackUpPath, outputPath);
        assertNull(trainInfoStr);
    }

/*
#######                           ###
#        #    #    ##    #         #     #    #  ######   ####
#        #    #   #  #   #         #     ##   #  #       #    #
#####    #    #  #    #  #         #     # #  #  #####   #    #
#        #    #  ######  #         #     #  # #  #       #    #
#         #  #   #    #  #         #     #   ##  #       #    #
#######    ##    #    #  ######   ###    #    #  #        ####
*/
    @Test
    public void testCreateEvaluationInfoStrWithValidInput()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("createEvaluationInfoStr",
                DataMetadata.class, TaskInfo.PBEvaluationInfo.class , Path.class);
        method.setAccessible(true);
        TaskInfo.PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForLinearHLCR();
        String evaluationInfoStr = (String)method.invoke(client, this.data, evaluationInfo, outputPath);
        com.sony.fl.json.LinearFedHLCR.parameters.Evaluation createdJson = Json.deserialize(evaluationInfoStr, com.sony.fl.json.LinearFedHLCR.parameters.Evaluation.class);
        assertNotNull(createdJson.parameters.server.output);
        assertNotNull(createdJson.parameters.client.dataSet);

        assertEquals(outputPath.toAbsolutePath().toString(), createdJson.parameters.server.output);
        assertEquals(this.data.toJsonString(), createdJson.parameters.client.dataSet);
    }

/*
 #    #  #####   #####     ##     #####  ######    #     #    #  ######   ####
 #    #  #    #  #    #   #  #      #    #         #     ##   #  #       #    #
 #    #  #    #  #    #  #    #     #    #####     #     # #  #  #####   #    #
 #    #  #####   #    #  ######     #    #         #     #  # #  #       #    #
 #    #  #       #    #  #    #     #    #         #     #   ##  #       #    #
  ####   #       #####   #    #     #    ######   ###    #    #  #        ####
*/

    @Test
    public void testCreateUpdateInfoStrWithValidInput() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("createUpdateInfoStr", 
                TaskInfo.PBDeployInfo.class, DataMetadata.class, Path.class, Path.class, Path.class);
        method.setAccessible(true);

        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForLinearHLCR();

        Files.createFile(inputPath.resolve(LinearFedHLCRClient.HYPER_PARAM_FILE_NAME));

        String updateInfoStr = (String)method.invoke(
                client, deployInfo, this.data, inputPath, inputPath, outputPath);

        com.sony.fl.json.LinearFedHLCR.parameters.UpdateInfo updateInfoStrs = Json.deserialize(updateInfoStr, com.sony.fl.json.LinearFedHLCR.parameters.UpdateInfo.class);

        assertEquals(inputPath.resolve("LinearHLCRUpdateHyperParams.json").toAbsolutePath().toString(), Paths.get(updateInfoStrs.parameters.server.hyperParams).toString());
        assertEquals(outputPath.toAbsolutePath().toString(), Paths.get(updateInfoStrs.parameters.client.output).toString());

        JsonNode updateInfoDataSet = new ObjectMapper().readTree(updateInfoStrs.parameters.client.dataSet);
        // System.out.println(updateInfoDataSet.get("save_result").asText());
        // System.out.println(updateInfoDataSet.get("tensor_map_file").asText());

        assertEquals("success", updateInfoDataSet.get("save_result").asText());
        assertEquals(inputPath.resolve("TestData.jsonl").toAbsolutePath().toString(), updateInfoDataSet.get("tensor_map_file").asText());
        assertEquals(inputPath.resolve("TestData.txt").toAbsolutePath().toString(), updateInfoDataSet.get("tensor_map_index_file").asText());

        Path ansPath = Paths.get("src/test/resources/jni_json/updateInfoStr.txt");
    }

    @Test
    public void testCreateUpdateInfoStrWithoutData() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("createUpdateInfoStr", 
                TaskInfo.PBDeployInfo.class, DataMetadata.class, Path.class, Path.class, Path.class);
        method.setAccessible(true);
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForLinearHLCR();
        String updateInfoStr = (String)method.invoke(
                client, deployInfo, this.data, inputPath, inputPath, outputPath);
        assertNull(updateInfoStr);
    }

/*
 #####   #####   ######  #####      #     ####    #####    #     #    #  ######
 #    #  #    #  #       #    #     #    #    #     #      #     ##   #  #
 #    #  #    #  #####   #    #     #    #          #      #     # #  #  #####
 #####   #####   #       #    #     #    #          #      #     #  # #  #
 #       #   #   #       #    #     #    #    #     #      #     #   ##  #
 #       #    #  ######  #####      #     ####      #     ###    #    #  #
*/

    @Test
    public void testCreatePredictInfoStrWithValidInput()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("createPredictInfoStr", TensorMap.class);
        method.setAccessible(true);

        Files.createFile(inputPath.resolve(LinearFedHLCRClient.HYPER_PARAM_FILE_NAME));

        String groupLabel = "group0";
        Double[] flattenedSequenceData = new Double[] { 3.0, 3.0 };
        assertNotEquals(null, flattenedSequenceData);
        TensorMap tensorMap = TensorMap.newInstance();
        tensorMap.set(LinearFedHLCRClient.TENSOR_X, Tensor.newTensor(TensorShape.createShape(2), flattenedSequenceData));
        tensorMap.set(LinearFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));

        String predictInfoStr = (String)method.invoke(client, tensorMap);
        assertNotNull(predictInfoStr);

        com.sony.fl.json.LinearFedHLCR.parameters.Prediction predictInfoStrs = Json.deserialize(predictInfoStr, com.sony.fl.json.LinearFedHLCR.parameters.Prediction.class);
        assertNotNull(predictInfoStrs);
        assertEquals(tensorMap.toJsonString(), predictInfoStrs.parameters.application.data);
    }

    // TODO:
    @Test
    public void testCreatePredictInfoStrWithInvalidInput()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("createPredictInfoStr", TensorMap.class);
        method.setAccessible(true);
        TensorMap tensorMap = TensorMap.newInstance();
        String predictInfoStr = (String)method.invoke(client, tensorMap);
        com.sony.fl.json.LinearFedHLCR.parameters.Prediction predictInfoStrs = Json.deserialize(predictInfoStr, com.sony.fl.json.LinearFedHLCR.parameters.Prediction.class);
        assertEquals("{}", predictInfoStrs.parameters.application.data);
    }

/*
#######                                 ######
   #     #####     ##       #    #    # #     #  ######   ####   #    #  #
   #     #    #   #  #      #    ##   # #     #  #       #       #    #  #
   #     #    #  #    #     #    # #  # ######   #####    ####   #    #  #
   #     #####   ######     #    #  # # #   #    #            #  #    #  #
   #     #   #   #    #     #    #   ## #    #   #       #    #  #    #  #
   #     #    #  #    #     #    #    # #     #  ######   ####    ####   ######
*/

    //TODO:
    @Test
    public void testParseTrainResultWithValidInput()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseTrainResult", String.class , Path.class, Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Training trainResultJson = trainResultJson();
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.createFile(outputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(newBackUpPath.resolve("cluster_map.json"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, Json.serialize(trainResultJson), newBackUpPath, outputPath);
        assertNotNull(trainResult);
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForLinearHLCR();
        assertEquals(0, PBChecker.checkPBTrainResult(trainResult, trainInfo));
        assertTrue(trainResult.hasLinearHLCRLocalModel());
    }

    @Test
    public void testParseTrainResultWithoutValidationMetrixFile()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseTrainResult", 
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Training trainResultJson = trainResultJson();
        // Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.createFile(outputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(newBackUpPath.resolve("cluster_map.json"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, Json.serialize(trainResultJson), newBackUpPath, outputPath);
        assertNull(trainResult);
    }

    @Test
    public void testParseTrainResultWithoutClusterFile()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseTrainResult",
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Training trainResultJson = trainResultJson();
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel1.json"));
        // Files.createFile(outputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.createFile(outputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(newBackUpPath.resolve("cluster_map.json"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, Json.serialize(trainResultJson), newBackUpPath, outputPath);
        assertNull(trainResult);
    }

    @Test
    public void testParseTrainResultWithoutHLCRParamFile()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseTrainResult",
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Training trainResultJson = trainResultJson();
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel2.json"));
        // Files.createFile(outputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(newBackUpPath.resolve("cluster_map.json"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, Json.serialize(trainResultJson), newBackUpPath, outputPath);
        assertNull(trainResult);
    }

    @Test
    public void testParseTrainResultWithoutClusterMapFile()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseTrainResult",
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Training trainResultJson = trainResultJson();
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.createFile(outputPath.resolve("LinearHLCRGlobalWeight.json"));
        // Files.createFile(newBackUpPath.resolve("cluster_map.json"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, Json.serialize(trainResultJson), newBackUpPath, outputPath);
        assertNull(trainResult);
    }

    @Test
    public void testParseTrainResultWithInvalidClusterMapFile()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseTrainResult",
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Training trainResultJson = trainResultJson();
        trainResultJson.results.client.clusterMap = newBackUpPath.resolve("invalid_cluster_map.json").toString();
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.createFile(outputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(newBackUpPath.resolve("invalid_cluster_map.json"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, Json.serialize(trainResultJson), newBackUpPath, outputPath);
        assertNull(trainResult);
    }

    @Test
    public void testParseTrainResultWithNullOutput()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseTrainResult",
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.createFile(outputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(newBackUpPath.resolve("cluster_map.json"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, null, newBackUpPath, outputPath);
        assertNull(trainResult);
    }

    @Test
    public void testParseTrainResultWithEmptyOutput()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseTrainResult",
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.createFile(outputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(newBackUpPath.resolve("cluster_map.json"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, "", newBackUpPath, outputPath);
        assertNull(trainResult);
    }

    @Test
    public void testParseTrainResultWithFailedState()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseTrainResult",
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Training trainResultJson = trainResultJson();
        trainResultJson.results.state = 1;
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.createFile(outputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(newBackUpPath.resolve("cluster_map.json"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, Json.serialize(trainResultJson), newBackUpPath, outputPath);
        assertNull(trainResult);
    }

    @Test
    public void testParseTrainResultWithNullState()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseTrainResult",
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Training trainResultJson = trainResultJson();
        trainResultJson.results.state = null;
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.createFile(outputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(newBackUpPath.resolve("cluster_map.json"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, Json.serialize(trainResultJson), newBackUpPath, outputPath);
        assertNull(trainResult);
    }

    @Test
    public void testParseTrainResultWithNullLinearModels()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseTrainResult",
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Training trainResultJson = trainResultJson();
        trainResultJson.results.server.linearModels = null;
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.createFile(outputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(newBackUpPath.resolve("cluster_map.json"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, Json.serialize(trainResultJson), newBackUpPath, outputPath);
        assertNull(trainResult);
    }

    @Test
    public void testParseTrainResultWithNullLocalCount()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseTrainResult",
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Training trainResultJson = trainResultJson();
        trainResultJson.results.server.localCount = null;
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.createFile(outputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(newBackUpPath.resolve("cluster_map.json"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, Json.serialize(trainResultJson), newBackUpPath, outputPath);
        assertNull(trainResult);
    }

    @Test
    public void testParseTrainResultWithNullValidationMetrix()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseTrainResult",
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Training trainResultJson = trainResultJson();
        trainResultJson.results.server.validationMetrix = null;
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.createFile(outputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(newBackUpPath.resolve("cluster_map.json"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, Json.serialize(trainResultJson), newBackUpPath, outputPath);
        assertNull(trainResult);
    }

    @Test
    public void testParseTrainResultWithNullClusterMap()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseTrainResult",
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Training trainResultJson = trainResultJson();
        trainResultJson.results.client.clusterMap = null;
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.createFile(outputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(newBackUpPath.resolve("cluster_map.json"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, Json.serialize(trainResultJson), newBackUpPath, outputPath);
        assertNull(trainResult);
    }

    @Test
    public void testParseTrainResultWithEmptyLinearModels()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseTrainResult",
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Training trainResultJson = trainResultJson();
        trainResultJson.results.server.linearModels = Collections.emptyList();
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.createFile(outputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.createFile(outputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.createFile(newBackUpPath.resolve("cluster_map.json"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, Json.serialize(trainResultJson), newBackUpPath, outputPath);
        assertNull(trainResult);
    }

/*
#######                         ######
#        #    #    ##    #      #     #  ######   ####   #    #  #        #####
#        #    #   #  #   #      #     #  #       #       #    #  #          #
#####    #    #  #    #  #      ######   #####    ####   #    #  #          #
#        #    #  ######  #      #   #    #            #  #    #  #          #
#         #  #   #    #  #      #    #   #       #    #  #    #  #          #
#######    ##    #    #  ###### #     #  ######   ####    ####   ######     #
*/

    @Test
    public void testParseEvaluationResultWithValidInput()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseEvaluationResult",
                String.class , Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Evaluation evaluationResultJson = evaluationResultJson();
        FLLogger.d("##########" + Json.serialize(evaluationResultJson));
        Files.createFile(outputPath.resolve("Evaluation_Result.jsonl"));
        PBEvaluationResult evaluationResult = (TaskResult.PBEvaluationResult)method.invoke(
                client, Json.serialize(evaluationResultJson), outputPath);
        assertNotNull(evaluationResult); // TODO : we need to check more.
    }

    @Test
    public void testParseEvaluationResultWithoutEvaluationResult()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseEvaluationResult",
                String.class , Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Evaluation evaluationResultJson = evaluationResultJson();
        PBEvaluationResult evaluationResult = (TaskResult.PBEvaluationResult)method.invoke(
                client, Json.serialize(evaluationResultJson), outputPath);
        assertNull(evaluationResult);
    }

    @Test
    public void testParseEvaluationResultWithNullResult()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseEvaluationResult",
                String.class , Path.class);
        method.setAccessible(true);
        Files.createFile(outputPath.resolve("Evaluation_Result.jsonl"));
        PBEvaluationResult evaluationResult = (TaskResult.PBEvaluationResult)method.invoke(
                client, null, outputPath);
        assertNull(evaluationResult);
    }

    @Test
    public void testParseEvaluationResultWithEmptyResult()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseEvaluationResult",
                String.class , Path.class);
        method.setAccessible(true);
        Files.createFile(outputPath.resolve("Evaluation_Result.jsonl"));
        PBEvaluationResult evaluationResult = (TaskResult.PBEvaluationResult)method.invoke(
                client, "", outputPath);
        assertNull(evaluationResult);
    }

    @Test
    public void testParseEvaluationResultWithFailedState()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseEvaluationResult",
                String.class , Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Evaluation evaluationResultJson = evaluationResultJson();
        evaluationResultJson.results.state = 1;
        Files.createFile(outputPath.resolve("Evaluation_Result.jsonl"));
        PBEvaluationResult evaluationResult = (TaskResult.PBEvaluationResult)method.invoke(
                client, Json.serialize(evaluationResultJson), outputPath);
        assertNull(evaluationResult);
    }

    @Test
    public void testParseEvaluationResultWithNullState()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseEvaluationResult",
                String.class , Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Evaluation evaluationResultJson = evaluationResultJson();
        evaluationResultJson.results.state = null;
        Files.createFile(outputPath.resolve("Evaluation_Result.jsonl"));
        PBEvaluationResult evaluationResult = (TaskResult.PBEvaluationResult)method.invoke(
                client, Json.serialize(evaluationResultJson), outputPath);
        assertNull(evaluationResult);
    }

    @Test
    public void testParseEvaluationResultWithNullEvaluationResult()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseEvaluationResult",
                String.class , Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.Evaluation evaluationResultJson = evaluationResultJson();
        evaluationResultJson.results.server.evaluationResult = null;
        Files.createFile(outputPath.resolve("Evaluation_Result.jsonl"));
        PBEvaluationResult evaluationResult = (TaskResult.PBEvaluationResult)method.invoke(
                client, Json.serialize(evaluationResultJson), outputPath);
        assertNull(evaluationResult);
    }

/*
                                                ######
 #    #  #####   #####     ##     #####  ###### #     #  ######   ####   #    #
 #    #  #    #  #    #   #  #      #    #      #     #  #       #       #    #
 #    #  #    #  #    #  #    #     #    #####  ######   #####    ####   #    #
 #    #  #####   #    #  ######     #    #      #   #    #            #  #    #
 #    #  #       #    #  #    #     #    #      #    #   #       #    #  #    #
  ####   #       #####   #    #     #    ###### #     #  ######   ####    ####
*/

    @Test
    public void testParseUpdateInfoResultWithValidInput() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult", String.class , Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.UpdateInfo updateInfoResultJson = updateInfoResultJson();
        Files.createFile(newBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        int evaluationResult = (int)method.invoke(client, Json.serialize(updateInfoResultJson), newBackUpPath);
        assertEquals(0, evaluationResult);
    }

    @Test
    public void testParseUpdateInfoResultWithFailedState() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult", String.class , Path.class);
        method.setAccessible(true);
        com.sony.fl.json.LinearFedHLCR.results.UpdateInfo updateInfoResultJson = updateInfoResultJson();
        updateInfoResultJson.results.state = 1;
        Files.createFile(newBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        int evaluationResult = (int)method.invoke(client, Json.serialize(updateInfoResultJson), newBackUpPath);
        assertEquals(1, evaluationResult);
    }

    @Test
    public void testParseUpdateInfoResultWithoutClusterMap() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult", String.class , Path.class);
        method.setAccessible(true);

        com.sony.fl.json.LinearFedHLCR.results.UpdateInfo updateInfoResultJson = updateInfoResultJson();

        int evaluationResult = (int)method.invoke(client, Json.serialize(updateInfoResultJson), newBackUpPath);
        assertEquals(1, evaluationResult);
    }

    @Test
    public void testParseUpdateInfoResultWithNullResult() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult", 
                String.class , Path.class);
        method.setAccessible(true);
        Files.createFile(newBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        int evaluationResult = (int)method.invoke(
                client, null, newBackUpPath);
        assertEquals(1, evaluationResult);
    }

    @Test
    public void testParseUpdateInfoResultWithEmptyResult() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult", 
                String.class , Path.class);
        method.setAccessible(true);
        Files.createFile(newBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        int evaluationResult = (int)method.invoke(
                client, "", newBackUpPath);
        assertEquals(1, evaluationResult);
    }

    public String readFile(String path) throws IOException {
        StringBuilder builder = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new FileReader(path))) {
            String string = reader.readLine();
            builder.append(string);
            while ((string = reader.readLine()) != null){
                builder.append(System.getProperty("line.separator") + string);
            }
        }
        return builder.toString();
    }

    @Test
    public void testParseUpdateInfoResultWithNoResults()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "{\"method\":\"UpdateInfo\"}";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult",
                String.class , Path.class);
        method.setAccessible(true);
        Files.createFile(newBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        int evaluationResult = (int)method.invoke(client, resultStr, newBackUpPath);
        assertEquals(1, evaluationResult);
    }

    @Test
    public void testParseUpdateInfoResultWithEmptyJson()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "{}";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult",
                String.class , Path.class);
        method.setAccessible(true);
        Files.createFile(newBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        int evaluationResult = (int)method.invoke(client, resultStr, newBackUpPath);
        assertEquals(1, evaluationResult);
    }

    @Test
    public void testParseUpdateInfoResultWithEmptyResults()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "{\"method\":\"UpdateInfo\",\"results\":{}}";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult",
                String.class , Path.class);
        method.setAccessible(true);
        Files.createFile(newBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        int evaluationResult = (int)method.invoke(client, resultStr, newBackUpPath);
        assertEquals(1, evaluationResult);
    }

    @Test
    public void testParseUpdateInfoResultWithNoState()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "{\"method\":\"UpdateInfo\",\"results\":{\"client\":{\"clusterMap\":\"ClusterMap.dat\"}}}";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult",
                String.class , Path.class);
        method.setAccessible(true);
        Files.createFile(newBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        int evaluationResult = (int)method.invoke(client, resultStr, newBackUpPath);
        assertEquals(1, evaluationResult);
    }

    @Test
    public void testParseUpdateInfoResultWithNoClient()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "{\"method\":\"UpdateInfo\",\"results\":{\"state\":0\"}}";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult",
                String.class , Path.class);
        method.setAccessible(true);
        Files.createFile(newBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        int evaluationResult = (int)method.invoke(client, resultStr, newBackUpPath);
        assertEquals(1, evaluationResult);
    }

    @Test
    public void testParseUpdateInfoResultWithEmptyClient()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "{\"method\":\"UpdateInfo\",\"results\":{\"state\":0,\"client\":{}}}";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult",
                String.class , Path.class);
        method.setAccessible(true);
        Files.createFile(newBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        int evaluationResult = (int)method.invoke(client, resultStr, newBackUpPath);
        assertEquals(1, evaluationResult);
    }

    @Test
    public void testParseUpdateInfoResultWithEmptyClusterMapFileName()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "{\"method\":\"UpdateInfo\",\"results\":{\"state\":0,\"client\":{\"clusterMap\":\"\"}}}";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult",
                String.class , Path.class);
        method.setAccessible(true);
        Files.createFile(newBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        int evaluationResult = (int)method.invoke(client, resultStr, newBackUpPath);
        assertEquals(1, evaluationResult);
    }

    @Test
    public void testParseUpdateInfoResultWithInvalidClusterMapFileName()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "{\"method\":\"UpdateInfo\",\"results\":{\"state\":0,\"client\":{\"clusterMap\":\"InvalidClusterMap\"}}}";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult",
                String.class , Path.class);
        method.setAccessible(true);
        Files.createFile(newBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        int evaluationResult = (int)method.invoke(client, resultStr, newBackUpPath);
        assertEquals(1, evaluationResult);
    }

    @Test
    public void testParseUpdateInfoResultWithInvalidResultJson()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "InvalidJson";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult",
                String.class , Path.class);
        method.setAccessible(true);
        Files.createFile(newBackUpPath.resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        int evaluationResult = (int)method.invoke(client, resultStr, newBackUpPath);
        assertEquals(1, evaluationResult);
    }

/*
                                                        ######
 #####   #####   ######  #####      #     ####    ##### #     #  ######   ####
 #    #  #    #  #       #    #     #    #    #     #   #     #  #       #
 #    #  #    #  #####   #    #     #    #          #   ######   #####    ####
 #####   #####   #       #    #     #    #          #   #   #    #            #
 #       #   #   #       #    #     #    #    #     #   #    #   #       #    #
 #       #    #  ######  #####      #     ####      #   #     #  ######   ####
*/

    @Test
    public void testParsePredictResultWithValidInput() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parsePredictionResult", String.class);
        method.setAccessible(true);

        com.sony.fl.json.LinearFedHLCR.results.Prediction predictionResultJson = predictionResultJson();
        String predictionResultStr = (String)method.invoke(client, Json.serialize(predictionResultJson));

        assertNotNull(predictionResultStr);
        TensorMap predictionResultTensorMap = TensorMap.fromJsonString(predictionResultStr);
        Double actualYPred = (Double)predictionResultTensorMap.get("y_pred").getValue();
        assertEquals(0.1798144280910492, actualYPred.doubleValue(), 0.0);
    }

    @Test
    public void testParsePredictResultWithNullInput() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parsePredictionResult", String.class);
        method.setAccessible(true);

        String predictionResultJson = null;
        String predictionResultStr = (String)method.invoke(client, predictionResultJson);

        assertNull(predictionResultStr);
    }

    @Test
    public void testParsePredictResultWithFailedState()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parsePredictionResult", String.class);
        method.setAccessible(true);

        com.sony.fl.json.LinearFedHLCR.results.Prediction predictionResultJson = predictionResultJson();
        predictionResultJson.results.state = 1;
        String predictionResultStr = (String)method.invoke(client, Json.serialize(predictionResultJson));

        assertNull(predictionResultStr);
    }

    @Test
    public void testParsePredictResultWithNoResults()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "{\"method\":\"Prediction\"}";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parsePredictionResult", String.class);
        method.setAccessible(true);

        String predictionResultStr = (String)method.invoke(client, resultStr);
        assertNull(predictionResultStr);
    }

    @Test
    public void testParsePredictResultWithEmptyJson()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "{}";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parsePredictionResult", String.class);
        method.setAccessible(true);

        String predictionResultStr = (String)method.invoke(client, resultStr);
        assertNull(predictionResultStr);
    }

    @Test
    public void testParsePredictResultWithEmptyResults()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "{\"method\":\"Prediction\",\"results\":{}}";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parsePredictionResult", String.class);
        method.setAccessible(true);

        String predictionResultStr = (String)method.invoke(client, resultStr);
        assertNull(predictionResultStr);
    }

    @Test
    public void testParsePredictResultWithNoState()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "{\"method\":\"Prediction\",\"results\":{\"application\":{\"predictionResult\":\"{\\\"y_pred\\\":{\\\"shape\\\":[1],\\\"value\\\":[0.1798144280910492]}}\"}}}";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parsePredictionResult", String.class);
        method.setAccessible(true);

        String predictionResultStr = (String)method.invoke(client, resultStr);
        assertNull(predictionResultStr);
    }

    @Test
    public void testParsePredictResultWithNoApplication()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "{\"method\":\"Prediction\",\"results\":{\"state\":0}}";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parsePredictionResult", String.class);
        method.setAccessible(true);

        String predictionResultStr = (String)method.invoke(client, resultStr);
        assertNull(predictionResultStr);
    }

    @Test
    public void testParsePredictResultWithEmptyApplication()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "{\"method\":\"Prediction\",\"results\":{\"state\":0,\"application\":{}}}";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parsePredictionResult", String.class);
        method.setAccessible(true);

        String predictionResultStr = (String)method.invoke(client, resultStr);
        assertNull(predictionResultStr);
    }

    @Test
    public void testParsePredictResultWithEmptyPredictionResult()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "{\"method\":\"Prediction\",\"results\":{\"state\":0,\"application\":{\"predictionResult\":\"{}\"}}}";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parsePredictionResult", String.class);
        method.setAccessible(true);

        String predictionResultStr = (String)method.invoke(client, resultStr);
        assertEquals("{}", predictionResultStr);
    }

    @Test
    public void testParsePredictResultWithInvalidResultJson()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "InvalidJson";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parsePredictionResult", String.class);
        method.setAccessible(true);

        String predictionResultStr = (String)method.invoke(client, resultStr);
        assertNull(predictionResultStr);
    }

    @Test
    public void testParsePredictResultWithInvalidPredictionResultJson()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        String resultStr = "{\"method\":\"Prediction\",\"results\":{\"state\":0,\"application\":{\"predictionResult\":\"InvalidJson\"}}}";

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parsePredictionResult", String.class);
        method.setAccessible(true);

        String predictionResultStr = (String)method.invoke(client, resultStr);
        assertEquals("InvalidJson", predictionResultStr);
    }

    @Test
    public void testFinalize()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        client.finalize();
    }

    @Test
    public void testFinalizeWithAlreadyFinalized()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        client.finalize();
        client.finalize();
    }

    @Test
    public void testTrainWithAlreadyFinalized() throws IOException, FLException, NoSuchMethodException,
            InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpClient();
        client.finalize();
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForLinearHLCR();

        DataMetadata dataMetadata = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(dataMetadata, "tensor_map_file", inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME).toString());
        DataMetadataUtil.set(dataMetadata, "tensor_map_index_file", inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME).toString());
        DataMetadataUtil.set(dataMetadata, "save_result", "success");
        TaskResult.PBTrainResult trainResult = client.train(dataMetadata, trainInfo, inputPath, inputPath, newBackUpPath, outputPath);
        assertNull(trainResult);
    }

    @Test
    public void testEvaluateWithAlreadyFinalized() throws IOException, FLException, NoSuchMethodException,
            InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpClient();
        client.finalize();
        TaskInfo.PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForLinearHLCR();
        assertNull(client.evaluate(this.data, evaluationInfo, inputPath, inputPath, outputPath));
    }

    @Test
    public void testPredictWithAlreadyFinalized() throws IOException, FLException, NoSuchMethodException,
            InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpClient();
        client.finalize();
        String groupLabel = "group0";
        Double[] flattenedSequenceData = new Double[] { 3.0, 3.0 };
        assertNotEquals(null, flattenedSequenceData);
        TensorMap tensorMap = TensorMap.newInstance();
        tensorMap.set(LinearFedHLCRClient.TENSOR_X, Tensor.newTensor(TensorShape.createShape(2), flattenedSequenceData));
        tensorMap.set(LinearFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));
        TensorMap result = client.predict(tensorMap);
        assertNull(result);
    }

    @Test
    public void testUpdateInfoWithAlreadyFinalized() throws IOException, FLException, NoSuchMethodException,
            InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpClient();
        client.finalize();
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForLinearHLCR();
        Files.copy(LinearHLCRSamplePath.resolve("back_up").resolve(LinearFedHLCRClient.HYPER_PARAM_FILE_NAME),
                inputPath.resolve(LinearFedHLCRClient.HYPER_PARAM_FILE_NAME));
        assertEquals(1, client.updateClusterMapping(deployInfo, this.data, inputPath, inputPath, newBackUpPath));
    }

    @Test
    public void testParseFileName() throws NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException, IOException, FLException {
        setUpClient();
        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseFileName", Path.class, String.class);
        method.setAccessible(true);

        Path filepath = null;
        String res = null;
        filepath = outputPath.resolve("LinearRegressionGlobalModel.json").toAbsolutePath();
        res = (String)method.invoke(client, outputPath, filepath.toString());
        assertEquals("LinearRegressionGlobalModel.json", res);

        filepath = Paths.get("src/test/resources/output/LinearRegressionGlobalModel.json");
        res = (String)method.invoke(client, outputPath, filepath.toString());
        assertEquals("LinearRegressionGlobalModel.json", res);

        filepath = outputPath.resolve("subdir1/subdir2/LinearRegressionGlobalModel.json").toAbsolutePath();
        res = (String)method.invoke(client, outputPath, filepath.toString());
        assertEquals("subdir1/subdir2/LinearRegressionGlobalModel.json", res);

        filepath = Paths.get("output/LinearRegressionGlobalModel.json");
        res = (String)method.invoke(client, outputPath, filepath.toString());
        assertEquals("output/LinearRegressionGlobalModel.json", res);

        filepath = Paths.get(".");
        res = (String)method.invoke(client, outputPath, filepath.toString());
        assertEquals(".", res);

        filepath = Paths.get("");
        res = (String)method.invoke(client, outputPath, filepath.toString());
        assertEquals("", res);

        filepath = Paths.get(" ");
        res = (String)method.invoke(client, outputPath, filepath.toString());
        assertEquals(" ", res);

    }

    @Test
    public void testEvaluate_DataZero() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpClient();
        TaskInfo.PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForLinearHLCR();

        Path datFile = Paths.get(outputPath.toString(), "testEvaluate_DataZero.dat");
        Path idxFile = Paths.get(outputPath.toString(), "testEvaluate_DataZero.idx");
        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        // Do not save.
        DataMetadata zero = serializer.getMetadata();

        TaskResult.PBEvaluationResult result = client.evaluate(zero, evaluationInfo, this.inputPath, this.inputPath, this.outputPath);

        assertNotNull(result);
        assertEquals(0, PBChecker.checkPBEvaluationResult(result, evaluationInfo));
    }

    @Test
    public void testParseEvaluationResultWithNoData()
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException,
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();

        Method method = LinearFedHLCRClient.class.getDeclaredMethod("parseEvaluationResult", String.class , Path.class);
        method.setAccessible(true);

        String resultStr = "{\"method\": \"Evaluation\",\"results\": {\"server\": {\"evaluationResult\": \"{\\\"tensor_map_file\\\":\\\"" + outputPath.resolve("Evaluation_Result.jsonl").toString() + "\\\",\\\"tensor_map_index_file\\\":\\\"" + outputPath.resolve("Evaluation_Result.txt").toString() + "\\\"}\"},\"state\": 0}}";

        TaskInfo.PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForLinearHLCR();

        Files.createFile(outputPath.resolve("Evaluation_Result.jsonl"));

        TaskResult.PBEvaluationResult evaluationResult = (TaskResult.PBEvaluationResult)method.invoke(this.client, resultStr, this.outputPath);

        assertNotNull(evaluationResult);
        assertEquals(0, PBChecker.checkPBEvaluationResult(evaluationResult, evaluationInfo));
    }
}
