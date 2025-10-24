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
import java.nio.file.StandardCopyOption;

import java.lang.reflect.InvocationTargetException;

import com.sony.fl.algorithm.NNFedHLCRClient;
import com.sony.fl.exception.FLException;
import com.sony.fl.logger.FLLogger;
import com.sony.fl.pb.TaskInfo;
import com.sony.fl.utils.Const;
import com.sony.fl.utils.CreatePBForTest;
import com.sony.fl.utils.DataMetadataUtil;

import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.DataSerializer;
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

public class TestPredictManager {
    public DeployManager deployManager;
    public PredictManager predictManager;
    public String appID;
    public String taskID;
    public Path predictManagerRoot = Paths.get("src/test/resources/PredictManagerRoot");
    public Path trainManagerRoot = Paths.get("src/test/resources/TrainManagerRoot");
    public Path inputPath = Paths.get("src/test/resources/input");
    public Path NNHLCRSamplePath = Paths.get("src/test/resources/NNHLCR");

    public DataMetadata data;

    @Before
    public void setUP() 
            throws IOException, FLException, InstantiationException, 
            IllegalAccessException, ClassNotFoundException,
            NoSuchMethodException, InvocationTargetException {
        String FLID = "fl-p";
        taskID = "task-p";
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        appID = deployInfo.getAppID();
        Files.createDirectories(trainManagerRoot);
        Files.createDirectories(predictManagerRoot);
        Files.createDirectories(inputPath);
        createFilesForDeploy();

        Path datFile = Paths.get(inputPath.toString(), Const.ALL_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.ALL_DATA_IDX_FILE_NAME);
        DataMetadata metaData = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(metaData, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(metaData, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(metaData, "save_result", "success");

        this.data = metaData;

        System.out.printf("### %s%n", this.data.toJsonString());

        deployManager = new DeployManager(trainManagerRoot, predictManagerRoot);
        assertEquals(0, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
        predictManager = new PredictManager(predictManagerRoot, appID);
    }

    public void createFilesForDeploy() throws IOException {
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), 
                inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), 
                inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), 
                inputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), 
                inputPath.resolve("graph.nntxt"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), 
                inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("back_up").resolve(NNFedHLCRClient.UPDATE_PARAM_FILE_NAME), 
                inputPath.resolve(NNFedHLCRClient.UPDATE_PARAM_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.ALL_DATA_DAT_FILE_NAME), 
                inputPath.resolve(Const.ALL_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.ALL_DATA_IDX_FILE_NAME), 
                inputPath.resolve(Const.ALL_DATA_IDX_FILE_NAME));
    }

    @After
    public void cleaning() throws IOException {
        PathUtils.deleteDirectory(predictManagerRoot);
        PathUtils.deleteDirectory(trainManagerRoot);
        PathUtils.deleteDirectory(inputPath);
    }

    @Test
    public void crateInstanceWithInvalidPath() 
            throws InstantiationException, IllegalAccessException, ClassNotFoundException {
        boolean flag = true;
        Path badPath = Paths.get("badpath");
        try {
            predictManager = new PredictManager(badPath, appID);
        } catch (FLException e) {
            flag = false;
        }
        if (flag) assertEquals(0, 1);
    }

/*
 #####   #####   ######  #####      #     ####    #####
 #    #  #    #  #       #    #     #    #    #     #
 #    #  #    #  #####   #    #     #    #          #
 #####   #####   #       #    #     #    #          #
 #       #   #   #       #    #     #    #    #     #
 #       #    #  ######  #####      #     ####      #
*/
//  @Test
//  public void testPredictWithValidInput() {
//      PredictManager.PredictResult predictResult = predictManager.predict(this.data);
//      assertEquals(0, predictResult.getStatus());
//  }

//  @Test
//  public void testPredictWithInvalidInputPath() {
//      Path badPath = Paths.get("bad path");
//      PredictManager.PredictResult predictResult = predictManager.predict(badPath);
//      assertEquals(1, predictResult.getStatus());
//  }

//  @Test
//  public void testPredictWithEmptyModel() 
//          throws FLException, InstantiationException, IllegalAccessException, ClassNotFoundException {
//      PredictManager emptyPredictManager = null;
//      String emptyAppID = "undeployed-app";
//      emptyPredictManager = new PredictManager(predictManagerRoot, emptyAppID);
//      PredictManager.PredictResult predictResult = emptyPredictManager.predict(this.data);
//      assertEquals(3, predictResult.getStatus());
//  }

    @Test
    public void testPredictForSNEWithValidInput() {
        float[][] sequenceData = {{0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 
            0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f},
            {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 
            0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f}};
        String groupLabel = "BSSID1";
        Double[] flattenedSequenceData = Tensor.toDoubleArrayFrom(sequenceData);
        assertNotNull(flattenedSequenceData);
        int m = sequenceData.length;
        int n = sequenceData[0].length;
        TensorMap tensorMap = TensorMap.newInstance();
        tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(n));
        tensorMap.set(NNFedHLCRClient.TENSOR_SEQUENCE_DATA, Tensor.newTensor(TensorShape.createShape(m, n), flattenedSequenceData));
        tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));
        PredictManager.PredictResult predictResult = 
                predictManager.predict(tensorMap);
        assertEquals(0, predictResult.getStatus());
    }

    @Test
    public void testPredictAPIForSNE() throws IOException {
        String groupLabel = "BSSID1";
        float[] label = loadDataY(NNHLCRSamplePath.resolve("predict").resolve("y_pred.csv"));
        for (int i = 0;i < 64;i++) {
            float[][] sequenceData = loadDataX(NNHLCRSamplePath.resolve("predict").resolve("x_"+ i +".csv"));
            Double[] flattenedSequenceData = Tensor.toDoubleArrayFrom(sequenceData);
            assertNotNull(flattenedSequenceData);
            int m = sequenceData.length;
            int n = sequenceData[0].length;
            TensorMap tensorMap = TensorMap.newInstance();
            tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(n));
            tensorMap.set(NNFedHLCRClient.TENSOR_SEQUENCE_DATA, Tensor.newTensor(TensorShape.createShape(m, n), flattenedSequenceData));
            tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));
            PredictManager.PredictResult predictResult = 
                    predictManager.predict(tensorMap);
            assertEquals(0, predictResult.getStatus());
            TensorMap result = predictResult.getResult();
            Tensor resultLabel = result.get(NNFedHLCRClient.TENSOR_Y_PRED);
            assertNotNull(resultLabel);
            assertTrue(resultLabel.isScalar());
            Double predictLabel = (Double)resultLabel.getValue();
            assertEquals(label[i], predictLabel, 1e-5);
            FLLogger.d("label = " + label[i] + " , predicted label = " + predictResult.getResult().get(NNFedHLCRClient.TENSOR_Y_PRED).getValue());
        }
    }

    public float[][] loadDataX(Path filePath) throws IOException {
        String ansStr = readFile(filePath.toString());
        String[] lines = ansStr.split(System.getProperty("line.separator"));
        int L = lines.length;
        float[][] ret = new float[L][];
        for (int i=0;i<L;i++) {
            String[] elements = lines[i].split(",");
            int D = elements.length;
            ret[i] = new float[D];
            for (int j=0;j<D;j++) {
                ret[i][j] = Float.valueOf(elements[j]);
            }
        }
        return ret;
    }

    public float[] loadDataY(Path filePath) throws IOException {
        String ansStr = readFile(filePath.toString());
        String[] strs = ansStr.split(System.getProperty("line.separator"));
        float[] ret = new float[64];
        for (int i=0;i<64;i++) ret[i] = Float.valueOf(strs[i]);
        return ret;
    }

    @Test
    public void testPredictForSNEWithEmptyModel() 
            throws FLException, InstantiationException, IllegalAccessException, ClassNotFoundException {
        String emptyAppID = "undeployed-app";
        PredictManager emptyPredictManager = new PredictManager(predictManagerRoot, emptyAppID);
        float[][] sequenceData = {{0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 
                0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f},
                {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 
                0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f}};
        String groupLabel = "BSSID1";
        Double[] flattenedSequenceData = Tensor.toDoubleArrayFrom(sequenceData);
        assertNotNull(flattenedSequenceData);
        int m = sequenceData.length;
        int n = sequenceData[0].length;
        TensorMap tensorMap = TensorMap.newInstance();
        tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(n));
        tensorMap.set(NNFedHLCRClient.TENSOR_SEQUENCE_DATA, Tensor.newTensor(TensorShape.createShape(m, n), flattenedSequenceData));
        tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));
        PredictManager.PredictResult predictResult = 
                emptyPredictManager.predict(tensorMap);
        assertEquals(3, predictResult.getStatus());
    }

    @Test
    public void testPredictForSNEWithoutData() {
        float[][] sequenceData = null;
        String groupLabel = "g1";
        TensorMap tensorMap = TensorMap.newInstance();
        tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));
        PredictManager.PredictResult predictResult = 
                predictManager.predict(tensorMap);
        assertEquals(1, predictResult.getStatus());
    }

    @Test
    public void testPredictForSNEWithoutNumOfFeatures() {
        float[][] sequenceData = {{0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f,
            0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f},
            {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f,
            0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f}};
        String groupLabel = "BSSID1";
        Double[] flattenedSequenceData = Tensor.toDoubleArrayFrom(sequenceData);
        assertNotNull(flattenedSequenceData);
        int m = sequenceData.length;
        int n = sequenceData[0].length;
        TensorMap tensorMap = TensorMap.newInstance();
        // tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(n));
        tensorMap.set(NNFedHLCRClient.TENSOR_SEQUENCE_DATA, Tensor.newTensor(TensorShape.createShape(m, n), flattenedSequenceData));
        tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));
        PredictManager.PredictResult predictResult =
                predictManager.predict(tensorMap);
        assertEquals(1, predictResult.getStatus());
    }

    @Test
    public void testPredictForSNEWithoutSequenceData() {
        float[][] sequenceData = {{0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f,
            0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f},
            {20.0f, 10.1f, 30.2f, 40.3f, 10.4f, 20.5f, 30.6f,
            30.0f, 60.1f, 70.2f, 20.3f, 10.4f, 40.5f, 10.6f}};
        String groupLabel = "BSSID1";
        // Double[] flattenedSequenceData = Tensor.toDoubleArrayFrom(sequenceData);
        // assertNotNull(flattenedSequenceData);
        // int m = sequenceData.length;
        int n = sequenceData[0].length;
        TensorMap tensorMap = TensorMap.newInstance();
        tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(n));
        // tensorMap.set(NNFedHLCRClient.TENSOR_SEQUENCE_DATA, Tensor.newTensor(TensorShape.createShape(m, n), flattenedSequenceData));
        tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));
        PredictManager.PredictResult predictResult = predictManager.predict(tensorMap);
        assertEquals(1, predictResult.getStatus());
    }

    @Test
    public void testPredictForSNEWithoutGroupLabel() {
        float[][] sequenceData = {{0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 
            0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f},
            {20.0f, 10.1f, 30.2f, 40.3f, 10.4f, 20.5f, 30.6f, 
            30.0f, 60.1f, 70.2f, 20.3f, 10.4f, 40.5f, 10.6f}};
        // String groupLabel = "BSSID1";
        Double[] flattenedSequenceData = Tensor.toDoubleArrayFrom(sequenceData);
        assertNotNull(flattenedSequenceData);
        int m = sequenceData.length;
        int n = sequenceData[0].length;
        TensorMap tensorMap = TensorMap.newInstance();
        tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(n));
        tensorMap.set(NNFedHLCRClient.TENSOR_SEQUENCE_DATA, Tensor.newTensor(TensorShape.createShape(m, n), flattenedSequenceData));
        // tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));
        PredictManager.PredictResult predictResult = 
                predictManager.predict(tensorMap);
        assertEquals(0, predictResult.getStatus());
    }

    @Test
    public void testPredictForSNEWithInvalidDimensionData() {
        float[][] sequenceData = {{0.0f, 0.1f, 0.2f},
            {0.0f, 0.1f, 0.2f}};
        String groupLabel = "BSSID1";
        Double[] flattenedSequenceData = Tensor.toDoubleArrayFrom(sequenceData);
        assertNotNull(flattenedSequenceData);
        int m = sequenceData.length;
        int n = sequenceData[0].length;
        TensorMap tensorMap = TensorMap.newInstance();
        tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(n));
        tensorMap.set(NNFedHLCRClient.TENSOR_SEQUENCE_DATA, Tensor.newTensor(TensorShape.createShape(m, n), flattenedSequenceData));
        tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));
        PredictManager.PredictResult predictResult = 
                predictManager.predict(tensorMap);
        assertEquals(0, predictResult.getStatus());
        TensorMap result = predictResult.getResult();
        Tensor resultLabel = result.get(NNFedHLCRClient.TENSOR_Y_PRED);
        assertNotNull(resultLabel);
        assertTrue(resultLabel.isScalar());
        Double predictLabel = (Double)resultLabel.getValue();
        assertEquals(-Float.MAX_VALUE, predictLabel, 0.0);
        FLLogger.d("label = " + -Float.MAX_VALUE + " , predicted label = " + predictResult.getResult().get(NNFedHLCRClient.TENSOR_Y_PRED).getValue());
    }

    @Test
    public void testPredictForSNEemptyTensorMap() {
        TensorMap empty = TensorMap.newInstance();
        PredictManager.PredictResult predictResult = predictManager.predict(empty);
        assertEquals(1, predictResult.getStatus());
    }


/*
  ####     ##    #          #    #####   #####     ##     #####  ######
 #    #   #  #   #          #    #    #  #    #   #  #      #    #
 #       #    #  #          #    #####   #    #  #    #     #    #####
 #       ######  #          #    #    #  #####   ######     #    #
 #    #  #    #  #          #    #    #  #   #   #    #     #    #
  ####   #    #  ######     #    #####   #    #  #    #     #    ######
*/
    @Test
    public void testCalibrateForSNE() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        Path clusterMapFile = predictManagerRoot.resolve(appID).resolve(taskID).resolve(NNFedHLCRClient.CLUSTER_MAP_FILE_NAME);
        String old_cm = readFile(clusterMapFile.toString());
        Path dummyFile = NNHLCRSamplePath.resolve("calibrate").resolve("dummy_data.jsonl");
        Path datFile = Paths.get(inputPath.toString(), Const.ALL_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.ALL_DATA_IDX_FILE_NAME);
        DataMetadata metaData = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(metaData, "tensor_map_file", dummyFile.toString());
        DataMetadataUtil.set(metaData, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(metaData, "save_result", "success");
        assertEquals(0, predictManager.calibrate(metaData));
        String new_cm = readFile(clusterMapFile.toString());
        assertFalse(old_cm.equals(new_cm));
    }

    @Test
    public void testCalibrateForSNENoData() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        Path clusterMapFile = predictManagerRoot.resolve(appID).resolve(taskID).resolve(NNFedHLCRClient.CLUSTER_MAP_FILE_NAME);
        String old_cm = readFile(clusterMapFile.toString());
        Path dummyFile = NNHLCRSamplePath.resolve("calibrate").resolve("dummy_data.jsonl");
        Path datFile = Paths.get(inputPath.toString(), Const.ALL_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.ALL_DATA_IDX_FILE_NAME);
        DataMetadata metaData = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(metaData, "tensor_map_file", dummyFile.toString());
        DataMetadataUtil.set(metaData, "tensor_map_index_file", idxFile.toString());
        assertEquals(0, predictManager.calibrate(metaData));
        String new_cm = readFile(clusterMapFile.toString());
        assertTrue(old_cm.equals(new_cm));
    }

    @Test
    public void testCalibrateWithValidInput() {
        assertEquals(0, predictManager.calibrate(this.data));
    }

//  @Test
//  public void testCalibrateWithInvalidInput() {
//      Path invalidInputPath = Paths.get("bad_path");
//      assertEquals(1, predictManager.calibrate(invalidInputPath));
//  }

    @Test
    public void testCalibrateWithFailedDataSerializerSave() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException {
        DataMetadataUtil.set(this.data, "save_result", "failed");
        assertEquals(1, predictManager.calibrate(this.data));
    }

    @Test
    public void testCalibrateWithEmptyModel() 
            throws FLException, InstantiationException, IllegalAccessException, ClassNotFoundException {
        PredictManager emptyPredictManager = null;
        String emptyAppID = "undeployed-app";
        emptyPredictManager = new PredictManager(predictManagerRoot, emptyAppID);
        assertEquals(3, emptyPredictManager.calibrate(this.data));
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
}
