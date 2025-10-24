package com.sony.fl;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

import com.sony.fl.algorithm.NNFedHLCRClient;
import com.sony.fl.exception.FLException;
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

public class TestExclusiveControl {
    public Path trainManagerRoot = Paths.get("src/test/resources/TrainManagerRoot");
    public Path predictManagerRoot = Paths.get("src/test/resources/PredictManagerRoot");
    public Path inputPath = Paths.get("src/test/resources/input");
    public Path outputPath = Paths.get("src/test/resources/output");
    public Path NNHLCRSamplePath = Paths.get("src/test/resources/NNHLCR");
    public TrainManager trainManager;
    public DeployManager deployManager;
    public PredictManager predictManager;
    String key;
    
    public DataMetadata input;
    public DataMetadata trainData;

    @Before
    public void setup() throws IOException, FLException, 
            InstantiationException, IllegalAccessException, ClassNotFoundException, NoSuchMethodException, InvocationTargetException {
        Files.createDirectories(trainManagerRoot);
        Files.createDirectories(predictManagerRoot);
        Files.createDirectories(inputPath);
        Files.createDirectories(outputPath);

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
        Files.copy(NNHLCRSamplePath.resolve("train_and_eval").resolve(Const.TRAIN_DATA_DAT_FILE_NAME),
                inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("train_and_eval").resolve(Const.TRAIN_DATA_IDX_FILE_NAME),
                inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));

        Path datFile = Paths.get(inputPath.toString(), Const.ALL_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.ALL_DATA_IDX_FILE_NAME);
        DataMetadata input = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(input, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(input, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(input, "save_result", "success");
        this.input = input;

        DataMetadata trainData = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(trainData, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(trainData, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(trainData, "save_result", "success");
        this.trainData = trainData;

        String FLID = "fl0";
        String taskID = "task0";
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();

        trainManager = new TrainManager(trainManagerRoot);
        deployManager = new DeployManager(trainManagerRoot, predictManagerRoot);
        assertEquals(0, deployManager.deploy(FLID, taskID, this.input, deployInfo, inputPath));
        predictManager = new PredictManager(predictManagerRoot, deployInfo.getAppID());

        key = ClientTaskController.getTaskFlag();
        assertEquals(true, key.length() > 0);
        ClientTaskController.releaseTaskFlag("dummy_key");
    }

    @After
    public void clean() {
        ClientTaskController.releaseTaskFlag(key);
        try {
            PathUtils.deleteDirectory(trainManagerRoot);
            PathUtils.deleteDirectory(predictManagerRoot);
            PathUtils.deleteDirectory(inputPath);
            PathUtils.deleteDirectory(outputPath);
        } catch (IOException e) {
            assertEquals(0, 1);
        }
    }

    @Test
    public void testTrainWithoutKey() throws FLException {
        String FLID = "fl1";
        String taskID = "task1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForLinearHLCR(); 
        assertEquals(2, trainManager.train(FLID, taskID, this.trainData, trainInfo, inputPath, outputPath).getStatus());
    }

    @Test
    public void testEvaluationWithoutKey() {
        String FLID = "fl2";
        TaskInfo.PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForLinearHLCR();
        assertEquals(2, trainManager.evaluation(FLID, this.trainData, evaluationInfo, inputPath, outputPath).getStatus());
    }

    @Test 
    public void testDeleteWithoutKey() {
        String FLID = "fl3";
        TaskInfo.PBDeleteInfo deleteInfo = CreatePBForTest.createValidDeleteInfo();
        assertEquals(2, trainManager.delete(FLID, deleteInfo));
    }

    @Test
    public void testDeployWithoutKey() {
        String FLID = "fl4";
        String taskID = "task4";
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForLinearHLCR();
        assertEquals(2, deployManager.deploy(FLID, taskID, this.input, deployInfo, inputPath));
    }

    @Test
    public void testStopWithoutKey() {
        TaskInfo.PBStopInfo stopInfo = CreatePBForTest.createValidStopInfo();
        assertEquals(2, deployManager.stop(stopInfo));
    }

//  @Test
//  public void testPredictWithoutKey() throws NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
//      Constructor<DataMetadata> constructor = DataMetadata.class.getDeclaredConstructor();
//      constructor.setAccessible(true);
//      DataMetadata metaData = constructor.newInstance();
//      assertEquals(2, predictManager.predict(metaData).getStatus());
//  }

    @Test
    public void testPredictForSNEWithoutKey() {
        float[][] sequenceData = {{0.0f, 0.1f, 0.2f}, {1.0f, -1.1f, 2.5f}};
        String groupLabel = "g1";
        Double[] flattenedSequenceData = Tensor.toDoubleArrayFrom(sequenceData);
        assertNotEquals(null, flattenedSequenceData);
        int m = sequenceData.length;
        int n = sequenceData[0].length;
        TensorMap tensorMap = TensorMap.newInstance();
        tensorMap.set(NNFedHLCRClient.TENSOR_SEQUENCE_DATA, Tensor.newTensor(TensorShape.createShape(m, n), flattenedSequenceData));
        tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));
        assertEquals(2, predictManager.predict(tensorMap).getStatus());
    }

    @Test
    public void testCalibrateWithoutKey() {
        assertEquals(2, predictManager.calibrate(this.input));
    }

    @Test
    public void testReset() {
        assertEquals(2, predictManager.calibrate(this.input));
        ClientTaskController.reset();
        assertEquals(0, predictManager.calibrate(this.input));
    }
}
