package com.sony.fl.algorithm;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import com.sony.fl.PredictManager;
import com.sony.fl.TrainManager;
import com.sony.fl.exception.FLException;
import com.sony.fl.pb.NNHLCR;
import com.sony.fl.pb.TaskInfo;
import com.sony.fl.pb.TaskResult;
import com.sony.fl.pb.TaskResult.PBEvaluationResult;
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

public class TestNNFedHLCRClient {
    public Path inputPath = Paths.get("src/test/resources/input");
    public Path outputPath = Paths.get("src/test/resources/output");
    public Path oldBackUpPath = Paths.get("src/test/resources/old");
    public Path newBackUpPath = Paths.get("src/test/resources/new");
    public Path NNHLCRSamplePath = Paths.get("src/test/resources/NNHLCR");
    NNFedHLCRClient client;

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
        NNHLCR.PBNNHLCRModel modelInfo = CreatePBForTest.createValidNNHLCRModel();
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), 
                inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), 
                inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), 
                inputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), 
                inputPath.resolve("graph.nntxt"));
        Files.copy(NNHLCRSamplePath.resolve("back_up").resolve(NNFedHLCRClient.CLUSTER_MAP_FILE_NAME), 
                oldBackUpPath.resolve(NNFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.ALL_DATA_DAT_FILE_NAME), 
                inputPath.resolve(Const.ALL_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.ALL_DATA_IDX_FILE_NAME), 
                inputPath.resolve(Const.ALL_DATA_IDX_FILE_NAME));

        client = new NNFedHLCRClient(modelInfo, oldBackUpPath, inputPath);
        PathUtils.delete(inputPath.resolve("HLCR_Param.dat"));
        PathUtils.delete(inputPath.resolve("cluster1.protobuf"));
        PathUtils.delete(inputPath.resolve("cluster2.protobuf"));
        PathUtils.delete(inputPath.resolve("graph.nntxt"));
        PathUtils.delete(oldBackUpPath.resolve(NNFedHLCRClient.CLUSTER_MAP_FILE_NAME));

        Path datFile = Paths.get(inputPath.toString(), Const.ALL_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.ALL_DATA_IDX_FILE_NAME);
        DataMetadata data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(data, "save_result", "success");
        this.data = data;
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
        NNHLCR.PBNNHLCRModel modelInfo = CreatePBForTest.createValidNNHLCRModel();
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), 
                inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), 
                inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), 
                inputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), 
                inputPath.resolve("graph.nntxt"));
        client = new NNFedHLCRClient(modelInfo, oldBackUpPath, inputPath);
        Files.copy(NNHLCRSamplePath.resolve("back_up").resolve(NNFedHLCRClient.CLUSTER_MAP_FILE_NAME), 
                inputPath.resolve(NNFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        client = new NNFedHLCRClient(modelInfo, oldBackUpPath, inputPath);
    }

    @Test
    public void testConstructorWithInvalidInput() throws IOException {
        NNHLCR.PBNNHLCRModel modelInfo = CreatePBForTest.createValidNNHLCRModel();
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), 
                inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), 
                inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), 
                inputPath.resolve("graph.nntxt"));
        Files.createFile(inputPath.resolve("clusterX.protobuf"));
        boolean flag = false;
        try {
            client = new NNFedHLCRClient(modelInfo, inputPath, oldBackUpPath);
        } catch (FLException e) {
            flag = true;
        }
        assertEquals(true, flag);
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
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), 
                inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("Hyper_Param.dat"), 
                inputPath.resolve("Hyper_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_DAT_FILE_NAME), 
                inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_IDX_FILE_NAME), 
                inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
        DataMetadata dataMetadata = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(dataMetadata, "tensor_map_file", inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME).toString());
        DataMetadataUtil.set(dataMetadata, "tensor_map_index_file", inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME).toString());
        DataMetadataUtil.set(dataMetadata, "save_result", "success");
        assertEquals(false, 
                client.train(dataMetadata, trainInfo, inputPath, inputPath, newBackUpPath, outputPath) == null);
    }

    @Test
    public void testTrainWithInvalidInput() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpClient();
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("Hyper_Param.dat"), 
                inputPath.resolve("Hyper_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_DAT_FILE_NAME), 
                inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_IDX_FILE_NAME), 
                inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
        DataMetadata dataMetadata = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(dataMetadata, "tensor_map_file", inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME).toString());
        DataMetadataUtil.set(dataMetadata, "tensor_map_index_file", inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME).toString());
        DataMetadataUtil.set(dataMetadata, "save_result", "success");
        assertEquals(true, 
                client.train(dataMetadata, trainInfo, inputPath, inputPath, newBackUpPath, outputPath) == null);
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
    public void testEvaluateWithValidInput() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpClient();
        TaskInfo.PBEvaluationInfo evaluationInfo = 
                CreatePBForTest.createValidEvaluationInfoForNNHLCR();
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), 
                inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_DAT_FILE_NAME), 
                inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_IDX_FILE_NAME), 
                inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
        assertEquals(false, 
                client.evaluate(this.data, evaluationInfo, inputPath, inputPath, outputPath) == null);
    }

    @Test
    public void testEvaluateWithInvalidInput() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpClient();
        TaskInfo.PBEvaluationInfo evaluationInfo = 
                CreatePBForTest.createValidEvaluationInfoForNNHLCR();
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_DAT_FILE_NAME), 
                inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_IDX_FILE_NAME), 
                inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
        assertEquals(true, 
                client.evaluate(this.data, evaluationInfo, inputPath, inputPath, outputPath) == null);
    }

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
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), 
                newBackUpPath.resolve("preprocess_params.dat"));
        float[][] dataSequence = {{0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 
                0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f},
                {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 
                0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f}};
        String groupLabel = "BSSID1";
        Double[] flattenedSequenceData = Tensor.toDoubleArrayFrom(dataSequence);
        assertNotEquals(null, flattenedSequenceData);
        int m = dataSequence.length;
        int n = dataSequence[0].length;
        TensorMap tensorMap = TensorMap.newInstance();
        tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(TensorShape.createShape(1), new Integer[] {n}));
        tensorMap.set(NNFedHLCRClient.TENSOR_SEQUENCE_DATA, Tensor.newTensor(TensorShape.createShape(m, n), flattenedSequenceData));
        tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));
        assertEquals(false, client.predict(tensorMap) == null);
    }

/*
 #    #  #####   #####     ##     #####  ###### ##   ##    ##    #####
 #    #  #    #  #    #   #  #      #    #      # # # #   #  #   #    #
 #    #  #    #  #    #  #    #     #    #####  #  #  #  #    #  #    #
 #    #  #####   #    #  ######     #    #      #     #  ######  #####
 #    #  #       #    #  #    #     #    #      #     #  #    #  #
  ####   #       #####   #    #     #    ###### #     #  #    #  #
*/

    @Test
    public void testUpdateClusterMapWithValidInput() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpClient();
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), 
                inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("back_up").resolve(NNFedHLCRClient.UPDATE_PARAM_FILE_NAME), 
                inputPath.resolve(NNFedHLCRClient.UPDATE_PARAM_FILE_NAME));
        assertEquals(0, client.updateClusterMapping(deployInfo, this.data, 
                inputPath, inputPath, newBackUpPath));
    }

    @Test
    public void testUpdateClusterMapWithInvalidInput() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpClient();
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("createModelInfoStr", 
                NNHLCR.PBNNHLCRModel.class, Path.class, Path.class);
        method.setAccessible(true);
        NNHLCR.PBNNHLCRModel modelInfo = CreatePBForTest.createValidNNHLCRModel();
        Files.createFile(inputPath.resolve("HLCR_Param.dat"));
        Files.createFile(inputPath.resolve("cluster1.protobuf"));
        Files.createFile(inputPath.resolve("cluster2.protobuf"));
        Files.createFile(inputPath.resolve("graph.nntxt"));
        Files.createFile(oldBackUpPath.resolve(NNFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        String modelInfoStr = (String)method.invoke(client, modelInfo, oldBackUpPath, inputPath);
        Path ansPath = Paths.get("src/test/resources/jni/modelInfoStr.txt");
        String ansStr = readFile(ansPath.toString());
        String[] modelInfoStrs = modelInfoStr.split(System.getProperty("line.separator"));
        String[] ansStrs = ansStr.split(System.getProperty("line.separator"));
        assertEquals(true, modelInfoStrs[0].equals(ansStrs[0]));
        for(int i=1;i<=4;i++) {
            assertEquals(Paths.get(modelInfoStrs[i]), Paths.get(ansStrs[i]).toAbsolutePath()); 
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("createModelInfoStr", 
                NNHLCR.PBNNHLCRModel.class, Path.class, Path.class);
        method.setAccessible(true);
        NNHLCR.PBNNHLCRModel modelInfo = CreatePBForTest.createValidNNHLCRModel();
        Files.createFile(inputPath.resolve("HLCR_Param.dat"));
        Files.createFile(inputPath.resolve("cluster1.protobuf"));
        Files.createFile(inputPath.resolve("graph.nntxt"));
        String modelInfoStr = (String)method.invoke(client, modelInfo, oldBackUpPath, inputPath);
        assertEquals(true, modelInfoStr == null);
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("createModelInfoStr", 
                NNHLCR.PBNNHLCRModel.class, Path.class, Path.class);
        method.setAccessible(true);
        NNHLCR.PBNNHLCRModel modelInfo = CreatePBForTest.createValidNNHLCRModel();
        Files.createFile(inputPath.resolve("cluster1.protobuf"));
        Files.createFile(inputPath.resolve("cluster2.protobuf"));
        Files.createFile(inputPath.resolve("graph.nntxt"));
        Files.createFile(oldBackUpPath.resolve(NNFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        String modelInfoStr = (String)method.invoke(client, modelInfo, oldBackUpPath, inputPath);
        assertEquals(true, modelInfoStr == null);
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("createTrainInfoStr", 
                TaskInfo.PBTrainInfo.class , Path.class, Path.class, Path.class);
        method.setAccessible(true);
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();
        Files.createFile(inputPath.resolve("Hyper_Param.dat"));
        Files.createFile(inputPath.resolve("preprocess_params.dat"));
        Files.createFile(inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.createFile(inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
        String trainInfoStr = (String)method.invoke(
                client, trainInfo, inputPath, newBackUpPath, outputPath);
        Path ansPath = Paths.get("src/test/resources/jni/trainInfoStr.txt");
        String ansStr = readFile(ansPath.toString());
        String[] trainInfoStrs = trainInfoStr.split(System.getProperty("line.separator"));
        String[] ansStrs = ansStr.split(System.getProperty("line.separator"));
        assertEquals(4, ansStrs.length);
        assertEquals(trainInfoStrs.length, ansStrs.length);
        for(int i=0;i<4;i++) {
            assertEquals(Paths.get(trainInfoStrs[i]), Paths.get(ansStrs[i]).toAbsolutePath()); 
        }
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("createTrainInfoStr", 
                TaskInfo.PBTrainInfo.class , Path.class, Path.class, Path.class);
        method.setAccessible(true);
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();
        Files.createFile(inputPath.resolve("preprocess_params.dat"));
        Files.createFile(inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.createFile(inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
        String trainInfoStr = (String)method.invoke(
                client, trainInfo, inputPath, newBackUpPath, outputPath);
        assertEquals(true, trainInfoStr == null);
    }

    @Test
    public void testCreateTrainInfoStrWithoutPreprocessingFile() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = NNFedHLCRClient.class.getDeclaredMethod("createTrainInfoStr", 
                TaskInfo.PBTrainInfo.class , Path.class, Path.class, Path.class);
        method.setAccessible(true);
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();
        Files.createFile(inputPath.resolve("Hyper_Param.dat"));
        Files.createFile(inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.createFile(inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
        String trainInfoStr = (String)method.invoke(
                client, trainInfo, inputPath, newBackUpPath, outputPath);
        assertEquals(true, trainInfoStr == null);
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("createEvaluationInfoStr", 
                TaskInfo.PBEvaluationInfo.class , Path.class, Path.class);
        method.setAccessible(true);
        TaskInfo.PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();
        Files.createFile(inputPath.resolve("preprocess_params.dat"));
        Files.createFile(inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.createFile(inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
        String evaluationInfoStr = (String)method.invoke(
                client, evaluationInfo, inputPath, outputPath);
        Path ansPath = Paths.get("src/test/resources/jni/evaluationInfoStr.txt");
        String ansStr = readFile(ansPath.toString());
        String[] evaluationInfoStrs = evaluationInfoStr.split(System.getProperty("line.separator"));
        String[] ansStrs = ansStr.split(System.getProperty("line.separator"));
        assertEquals(2, ansStrs.length);
        assertEquals(evaluationInfoStrs.length, ansStrs.length);
        for(int i=0;i<2;i++) {
            assertEquals(Paths.get(evaluationInfoStrs[i]), Paths.get(ansStrs[i]).toAbsolutePath()); 
        }
    }

    @Test
    public void testCreateEvaluationInfoStrWithoutPreprocessingParam() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = NNFedHLCRClient.class.getDeclaredMethod("createEvaluationInfoStr", 
                TaskInfo.PBEvaluationInfo.class , Path.class, Path.class);
        method.setAccessible(true);
        TaskInfo.PBEvaluationInfo trainInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();
        Files.createFile(inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.createFile(inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
        String trainInfoStr = (String)method.invoke(
                client, trainInfo, inputPath, outputPath);
        assertEquals(true, trainInfoStr == null);
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("createUpdateInfoStr", 
                TaskInfo.PBDeployInfo.class, DataMetadata.class, Path.class, Path.class, Path.class);
        method.setAccessible(true);
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        Files.createFile(inputPath.resolve("preprocess_params.dat"));
        Files.createFile(inputPath.resolve(NNFedHLCRClient.UPDATE_PARAM_FILE_NAME));
        Path datFile = Paths.get(inputPath.toString(), Const.ALL_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.ALL_DATA_IDX_FILE_NAME);
        DataMetadata metaData = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(metaData, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(metaData, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(metaData, "save_result", "success");
        String updateInfoStr = (String)method.invoke(
                client, deployInfo, metaData, inputPath, inputPath, outputPath);
        Path ansPath = Paths.get("src/test/resources/jni/updateInfoStr.txt");
        String ansStr = readFile(ansPath.toString());
        String[] updateInfoStrs = updateInfoStr.split(System.getProperty("line.separator"));
        String[] ansStrs = ansStr.split(System.getProperty("line.separator"));
        assertEquals(3, ansStrs.length);
        assertEquals(updateInfoStrs.length, ansStrs.length);
        for(int i=0;i<3;i++) {
            assertEquals(Paths.get(updateInfoStrs[i]), Paths.get(ansStrs[i]).toAbsolutePath()); 
        }
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("createUpdateInfoStr", 
                TaskInfo.PBDeployInfo.class, DataMetadata.class, Path.class, Path.class, Path.class);
        method.setAccessible(true);
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        Path datFile = Paths.get(inputPath.toString(), Const.ALL_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.ALL_DATA_IDX_FILE_NAME);
        DataMetadata metaData = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(metaData, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(metaData, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(metaData, "save_result", "success");
        String updateInfoStr = (String)method.invoke(
                client, deployInfo, metaData, inputPath, inputPath, outputPath);
        assertEquals(true, updateInfoStr == null);
    }

    @Test
    public void testCreateUpdateInfoStrWithoutPreprocessParam() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = NNFedHLCRClient.class.getDeclaredMethod("createUpdateInfoStr", 
                TaskInfo.PBDeployInfo.class, DataMetadata.class, Path.class, Path.class, Path.class);
        method.setAccessible(true);
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        Files.createFile(inputPath.resolve("preprocess_params.dat"));
        String updateInfoStr = (String)method.invoke(
                client, deployInfo, this.data, inputPath, inputPath, outputPath);
        assertEquals(true, updateInfoStr == null);
    }

/*
 #####   #####   ######  #####      #     ####    #####    #     #    #  ######
 #    #  #    #  #       #    #     #    #    #     #      #     ##   #  #
 #    #  #    #  #####   #    #     #    #          #      #     # #  #  #####
 #####   #####   #       #    #     #    #          #      #     #  # #  #
 #       #   #   #       #    #     #    #    #     #      #     #   ##  #
 #       #    #  ######  #####      #     ####      #     ###    #    #  #
*/

/*
#######                                 ######
   #     #####     ##       #    #    # #     #  ######   ####   #    #  #
   #     #    #   #  #      #    ##   # #     #  #       #       #    #  #
   #     #    #  #    #     #    # #  # ######   #####    ####   #    #  #
   #     #####   ######     #    #  # # #   #    #            #  #    #  #
   #     #   #   #    #     #    #   ## #    #   #       #    #  #    #  #
   #     #    #  #    #     #    #    # #     #  ######   ####    ####   ######
*/

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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("parseTrainResult", 
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        Path resultPath = Paths.get("src/test/resources/jni/trainResultStr.txt");
        String resultStr = readFile(resultPath.toString());
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("cluster1.protobuf"));
        Files.createFile(outputPath.resolve("cluster2.protobuf"));
        Files.createFile(outputPath.resolve("HLCR_Param.dat"));
        Files.createFile(newBackUpPath.resolve("ClusterMap.dat"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, resultStr, newBackUpPath, outputPath);
        assertEquals(true, trainResult != null); // TODO : we need to check more.
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("parseTrainResult", 
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        Path resultPath = Paths.get("src/test/resources/jni/trainResultStr.txt");
        String resultStr = readFile(resultPath.toString());
        Files.createFile(outputPath.resolve("cluster1.protobuf"));
        Files.createFile(outputPath.resolve("cluster2.protobuf"));
        Files.createFile(outputPath.resolve("HLCR_Param.dat"));
        Files.createFile(newBackUpPath.resolve("ClusterMap.dat"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, resultStr, newBackUpPath, outputPath);
        assertEquals(true, trainResult == null); 
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("parseTrainResult", 
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        Path resultPath = Paths.get("src/test/resources/jni/trainResultStr.txt");
        String resultStr = readFile(resultPath.toString());
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("cluster1.protobuf"));
        Files.createFile(outputPath.resolve("HLCR_Param.dat"));
        Files.createFile(newBackUpPath.resolve("ClusterMap.dat"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, resultStr, newBackUpPath, outputPath);
        assertEquals(true, trainResult == null); 
    }

    @Test
    public void testParseTrainResultWithoutHLCRParam() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = NNFedHLCRClient.class.getDeclaredMethod("parseTrainResult", 
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        Path resultPath = Paths.get("src/test/resources/jni/trainResultStr.txt");
        String resultStr = readFile(resultPath.toString());
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("cluster1.protobuf"));
        Files.createFile(outputPath.resolve("cluster2.protobuf"));
        Files.createFile(newBackUpPath.resolve("ClusterMap.dat"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, resultStr, newBackUpPath, outputPath);
        assertEquals(true, trainResult == null);
    }

    @Test
    public void testParseTrainResultWithoutClusterMap() 
        throws NoSuchMethodException,
        SecurityException,
        IllegalAccessException,
        IllegalArgumentException, 
        InvocationTargetException, IOException, FLException,
        InstantiationException
    {
        setUpClient();
        Method method = NNFedHLCRClient.class.getDeclaredMethod("parseTrainResult", 
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        Path resultPath = Paths.get("src/test/resources/jni/trainResultStr.txt");
        String resultStr = readFile(resultPath.toString());
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("cluster1.protobuf"));
        Files.createFile(outputPath.resolve("cluster2.protobuf"));
        Files.createFile(outputPath.resolve("HLCR_Param.dat"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, resultStr, newBackUpPath, outputPath);
        assertEquals(true, trainResult == null);
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("parseTrainResult", 
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("cluster1.protobuf"));
        Files.createFile(outputPath.resolve("cluster2.protobuf"));
        Files.createFile(outputPath.resolve("HLCR_Param.dat"));
        Files.createFile(newBackUpPath.resolve("ClusterMap.dat"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, null, newBackUpPath, outputPath);
        assertEquals(true, trainResult == null); 
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("parseTrainResult", 
                String.class , Path.class, Path.class);
        method.setAccessible(true);
        Files.createFile(outputPath.resolve("validation_metrix.dat"));
        Files.createFile(outputPath.resolve("cluster1.protobuf"));
        Files.createFile(outputPath.resolve("cluster2.protobuf"));
        Files.createFile(outputPath.resolve("HLCR_Param.dat"));
        Files.createFile(newBackUpPath.resolve("ClusterMap.dat"));
        TaskResult.PBTrainResult trainResult = (TaskResult.PBTrainResult)method.invoke(
                client, "", newBackUpPath, outputPath);
        assertEquals(true, trainResult == null); 
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("parseEvaluationResult", 
                String.class , Path.class);
        method.setAccessible(true);
        Path resultPath = Paths.get("src/test/resources/jni/evaluationResultStr.txt");
        String resultStr = readFile(resultPath.toString());
        Files.createFile(outputPath.resolve("Evaluation_Result.dat"));
        PBEvaluationResult evaluationResult = (TaskResult.PBEvaluationResult)method.invoke(
                client, resultStr, outputPath);
        assertEquals(true, evaluationResult != null); // TODO : we need to check more.
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("parseEvaluationResult", 
                String.class , Path.class);
        method.setAccessible(true);
        Path resultPath = Paths.get("src/test/resources/jni/evaluationResultStr.txt");
        String resultStr = readFile(resultPath.toString());
        PBEvaluationResult evaluationResult = (TaskResult.PBEvaluationResult)method.invoke(
                client, resultStr, outputPath);
        assertEquals(true, evaluationResult == null);
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("parseEvaluationResult", 
                String.class , Path.class);
        method.setAccessible(true);
        Files.createFile(outputPath.resolve("Evaluation_Result.dat"));
        PBEvaluationResult evaluationResult = (TaskResult.PBEvaluationResult)method.invoke(
                client, null, outputPath);
        assertEquals(true, evaluationResult == null);
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("parseEvaluationResult", 
                String.class , Path.class);
        method.setAccessible(true);
        Files.createFile(outputPath.resolve("Evaluation_Result.dat"));
        PBEvaluationResult evaluationResult = (TaskResult.PBEvaluationResult)method.invoke(
                client, "", outputPath);
        assertEquals(true, evaluationResult == null);
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult", 
                String.class , Path.class);
        method.setAccessible(true);
        Path resultPath = Paths.get("src/test/resources/jni/updateInfoResultStr.txt");
        String resultStr = readFile(resultPath.toString());
        Files.createFile(newBackUpPath.resolve(NNFedHLCRClient.CLUSTER_MAP_FILE_NAME));
        int evaluationResult = (int)method.invoke(
                client, resultStr, newBackUpPath);
        assertEquals(0, evaluationResult);
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult", 
                String.class , Path.class);
        method.setAccessible(true);
        Path resultPath = Paths.get("src/test/resources/jni/updateInfoResultStr.txt");
        String resultStr = readFile(resultPath.toString());
        int evaluationResult = (int)method.invoke(
                client, resultStr, newBackUpPath);
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult", 
                String.class , Path.class);
        method.setAccessible(true);
        Files.createFile(newBackUpPath.resolve(NNFedHLCRClient.CLUSTER_MAP_FILE_NAME));
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
        Method method = NNFedHLCRClient.class.getDeclaredMethod("parseUpdateInfoResult", 
                String.class , Path.class);
        method.setAccessible(true);
        Files.createFile(newBackUpPath.resolve(NNFedHLCRClient.CLUSTER_MAP_FILE_NAME));
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
}
