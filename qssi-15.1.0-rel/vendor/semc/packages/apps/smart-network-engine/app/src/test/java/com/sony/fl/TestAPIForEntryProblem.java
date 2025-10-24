package com.sony.fl;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import java.lang.reflect.InvocationTargetException;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;

import com.sony.fl.algorithm.LinearFedHLCRClient;
import com.sony.fl.exception.FLException;
import com.sony.fl.logger.FLLogger;
import com.sony.fl.pb.TaskInfo;
import com.sony.fl.utils.Const;
import com.sony.fl.utils.CreatePBForTest;
import com.sony.fl.utils.DataMetadataUtil;

import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.Tensor;
import com.sony.fl.tensor.TensorMap;
import com.sony.fl.tensor.TensorShape;

import org.apache.commons.io.file.PathUtils;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

/**
 * @author Masanobu Jimbo
 */

public class TestAPIForEntryProblem {
    public TrainManager trainManager;
    public DeployManager deployManager;
    public PredictManager predictManager;

    public Path predictManagerRoot = Paths.get("src/test/resources/PredictManagerRoot");
    public Path trainManagerRoot = Paths.get("src/test/resources/TrainManagerRoot");
    public Path inputPath = Paths.get("src/test/resources/input");
    public Path outputPath = Paths.get("src/test/resources/output");
    public Path LinearHLCRSamplePath = Paths.get("src/test/resources/LinearHLCR");

    public DataMetadata data;

    @Before
    public void setUP() 
            throws IOException, FLException, InstantiationException, 
            IllegalAccessException, ClassNotFoundException,
            NoSuchMethodException, InvocationTargetException {

        Files.createDirectories(trainManagerRoot);
        Files.createDirectories(predictManagerRoot);
        Files.createDirectories(inputPath);
        Files.createDirectories(outputPath);
    }

    public void setUpData () throws NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        Path datFile = Paths.get(inputPath.toString(), Const.TEST_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TEST_DATA_IDX_FILE_NAME);
        DataMetadata metaData = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(metaData, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(metaData, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(metaData, "save_result", "success");

        this.data = metaData;

        System.out.printf("### %s%n", this.data.toJsonString());
    }


    public void createFilesForTrain() throws IOException {
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearHLCRGlobalWeight.json"),      inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel0.json"), inputPath.resolve("LinearRegressionGlobalModel0.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel1.json"), inputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel2.json"), inputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel3.json"), inputPath.resolve("LinearRegressionGlobalModel3.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel4.json"), inputPath.resolve("LinearRegressionGlobalModel4.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel5.json"), inputPath.resolve("LinearRegressionGlobalModel5.json"));

        Files.copy(LinearHLCRSamplePath.resolve("back_up").resolve("LinearHLCRTrainHyperParams.json"), inputPath.resolve("LinearHLCRTrainHyperParams.json"));

        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("Data.jsonl"), inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("data.txt"), inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
    }


    public void createFilesForEvaluation() throws IOException {
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearHLCRGlobalWeight.json"),      inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel0.json"), inputPath.resolve("LinearRegressionGlobalModel0.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel1.json"), inputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel2.json"), inputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel3.json"), inputPath.resolve("LinearRegressionGlobalModel3.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel4.json"), inputPath.resolve("LinearRegressionGlobalModel4.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel5.json"), inputPath.resolve("LinearRegressionGlobalModel5.json"));

        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("Data.jsonl"), inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("data.txt"), inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
    }

    public void createFilesForDeploy() throws IOException {
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearHLCRGlobalWeight.json"),      inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel0.json"), inputPath.resolve("LinearRegressionGlobalModel0.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel1.json"), inputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel2.json"), inputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel3.json"), inputPath.resolve("LinearRegressionGlobalModel3.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel4.json"), inputPath.resolve("LinearRegressionGlobalModel4.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel5.json"), inputPath.resolve("LinearRegressionGlobalModel5.json"));

        Files.copy(LinearHLCRSamplePath.resolve("back_up").resolve("LinearHLCRUpdateHyperParams.json"), inputPath.resolve("LinearHLCRUpdateHyperParams.json"));

        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("Data.jsonl"), inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("data.txt"), inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
    }

    public void createFilesForDeploy_python_test_case() throws IOException {
        Files.copy(LinearHLCRSamplePath.resolve("python_test_case").resolve("global_weight.json"), inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.copy(LinearHLCRSamplePath.resolve("python_test_case").resolve("model_S_0.json"),     inputPath.resolve("LinearRegressionGlobalModel0.json"));
        Files.copy(LinearHLCRSamplePath.resolve("python_test_case").resolve("model_S_1.json"),     inputPath.resolve("LinearRegressionGlobalModel1.json"));

        Files.copy(LinearHLCRSamplePath.resolve("back_up").resolve("LinearHLCRUpdateHyperParams.json"), inputPath.resolve("LinearHLCRUpdateHyperParams.json"));
    }

    @After
    public void cleaning() throws IOException {
        PathUtils.deleteDirectory(predictManagerRoot);
        PathUtils.deleteDirectory(trainManagerRoot);
        PathUtils.deleteDirectory(inputPath);
        PathUtils.deleteDirectory(outputPath);
    }

    @Test
    public void testTrainAPIForSNE () throws FLException, IOException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        String FLID = "fl";
        String taskID = "task-train";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForLinearHLCRForSNE();

        createFilesForTrain();
        setUpData();

        trainManager = new TrainManager(trainManagerRoot);
        assertEquals(0, trainManager.train(FLID, taskID, this.data, trainInfo, inputPath, outputPath).getStatus());
    }

    @Test
    public void testEvaluationAPIForSNE () throws FLException, IOException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        String FLID = "fl";
        String taskID = "task-evaluation";
        TaskInfo.PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForLinearHLCRForSNE();

        createFilesForEvaluation();
        setUpData();

        trainManager = new TrainManager(trainManagerRoot);
        assertEquals(0, trainManager.evaluation(FLID, this.data, evaluationInfo, inputPath, outputPath).getStatus());
    }


    @Test
    public void testDeployAndPredictAPIForSNE() throws IOException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, FLException {
        String FLID = "fl";
        String taskID = "task-deploy";
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForLinearHLCRForSNE();
        String appID = deployInfo.getAppID();

        createFilesForDeploy();

        setUpData();

        deployManager = new DeployManager(trainManagerRoot, predictManagerRoot);
        assertEquals(0, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
        predictManager = new PredictManager(predictManagerRoot, appID);


        TensorMap tensorMap = TensorMap.fromJsonString("{\"x\":{\"value\":[3,3,3,3,3],\"shape\":[5]},\"g\":{\"value\":[\"group0\"],\"shape\":[1]}}");
        PredictManager.PredictResult predictResult = predictManager.predict(tensorMap);
        assertEquals(0, predictResult.getStatus());
        TensorMap result = predictResult.getResult();
        Tensor<Double> resultLabel = result.get(LinearFedHLCRClient.TENSOR_Y_PRED);
        assertNotNull(resultLabel);
        assertTrue(resultLabel.isScalar());
        Double predictLabel = resultLabel.getValue();
        assertEquals(0.0334, predictLabel, 1e-2);
        FLLogger.d("predicted label = " + predictLabel);
    }

    private TensorMap generateTensorMaps() {
        try {
            try (BufferedReader br = Files.newBufferedReader(this.LinearHLCRSamplePath.resolve("python_test_case/data_S.jsonl"))) {
                TensorMap tensorMap = TensorMap.fromJsonString(br.readLine());
                return tensorMap;
            }
        }
        catch (IOException ex) {
            ex.printStackTrace();
            return null;
        }
    }

    private double get_y_pred() throws IOException, JsonProcessingException {
        try (BufferedReader br = Files.newBufferedReader(this.LinearHLCRSamplePath.resolve("python_test_case/predict_result.json"))) {
            String json = br.readLine();
            JsonNode jsonNode = new ObjectMapper().readTree(json);
            return jsonNode.get("y_pred").get(0).doubleValue();
        }
    }

    @Test
    public void testDeployAndPredictAPIForSNE_python_test_case() throws IOException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, FLException {
        String FLID = "fl";
        String taskID = "task-deploy";
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForLinearHLCRForSNE_python_test_case();
        String appID = deployInfo.getAppID();

        createFilesForDeploy_python_test_case();

        setUpData();

        deployManager = new DeployManager(trainManagerRoot, predictManagerRoot);
        assertEquals(0, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
        predictManager = new PredictManager(predictManagerRoot, appID);

        TensorMap tensorMap =  this.generateTensorMaps();

        PredictManager.PredictResult predictResult = predictManager.predict(tensorMap);

        assertEquals(0, predictResult.getStatus());
        TensorMap result = predictResult.getResult();
        Tensor<Double> resultLabel = result.get(LinearFedHLCRClient.TENSOR_Y_PRED);
        assertNotNull(resultLabel);
        assertTrue(resultLabel.isScalar());
        Double predictLabel = resultLabel.getValue();
        assertEquals(this.get_y_pred(), predictLabel, 0.0);
        FLLogger.d("predicted label = " + predictLabel);
    }
}
