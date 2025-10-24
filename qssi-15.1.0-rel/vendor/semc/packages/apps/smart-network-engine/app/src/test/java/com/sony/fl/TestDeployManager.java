package com.sony.fl;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.nio.file.NoSuchFileException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Iterator;

import com.sony.fl.PredictManager.PredictResult;
import com.sony.fl.algorithm.LinearFedHLCRClient;
import com.sony.fl.algorithm.NNFedHLCRClient;
import com.sony.fl.exception.FLException;
import com.sony.fl.pb.TaskInfo;
import com.sony.fl.utils.Const;
import com.sony.fl.utils.CreatePBForTest;
import com.sony.fl.utils.DataMetadataUtil;
import com.sony.fl.utils.PathChecker;
import com.sony.fl.logger.*;

import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.DataSerializer;
import com.sony.fl.tensor.Tensor;
import com.sony.fl.tensor.TensorMap;
import com.sony.fl.tensor.TensorShape;

import org.apache.commons.io.file.PathUtils;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import java.util.HashMap;
import java.util.Map;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;

/**
 * @author Masanobu Jimbo
 */

public class TestDeployManager {
    public DeployManager deployManager;
    public Path trainManagerRoot = Paths.get("src/test/resources/TrainManagerRoot");
    public Path predictManagerRoot = Paths.get("src/test/resources/PredictManagerRoot");
    public Path inputPath = Paths.get("src/test/resources/input");
    public Path outputPath = Paths.get("src/test/resources/output");
    public Path trainInputPath = Paths.get("src/test/resources/input_train");
    public Path LinearHLCRSamplePath = Paths.get("src/test/resources/LinearHLCR");
    public Path NNHLCRSamplePath = Paths.get("src/test/resources/NNHLCR");
    public Path badNNHLCRSamplePath = Paths.get("src/test/resources/NNHLCR/bad_files");
    public Path nnpSamplePath = Paths.get("src/test/resources/NNHLCR/nnp");
    float[][] sequenceData = {{0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f},
                              {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f},
                              {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f}};
    String groupLabel = "BSSID1";

    public DataMetadata data;
    public DataMetadata dataForLinearHLCR;

    @Before
    public void setUP() 
            throws IOException, FLException, InstantiationException, 
            IllegalAccessException, ClassNotFoundException {
        Files.createDirectories(trainManagerRoot);
        Files.createDirectories(predictManagerRoot);
        Files.createDirectories(inputPath);
        Files.createDirectories(outputPath);
        Files.createDirectories(trainInputPath);
        deployManager = new DeployManager(trainManagerRoot, predictManagerRoot);
    }

    public void setUpForDeploy() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        System.err.printf("ENTER TestDeployManager#setUpForDeploy(%s)%n", inputPath);
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), 
                inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("calibrate").resolve("lstm20.protobuf"), 
                inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("calibrate").resolve("lstm19.protobuf"), 
                inputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("calibrate").resolve("network.nntxt"), 
                inputPath.resolve("graph.nntxt"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), 
                inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("back_up").resolve(NNFedHLCRClient.UPDATE_PARAM_FILE_NAME), 
                inputPath.resolve(NNFedHLCRClient.UPDATE_PARAM_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.ALL_DATA_DAT_FILE_NAME),
                inputPath.resolve(Const.ALL_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.ALL_DATA_IDX_FILE_NAME),
                inputPath.resolve(Const.ALL_DATA_IDX_FILE_NAME));

        Path datFile = Paths.get(inputPath.toString(), Const.ALL_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.ALL_DATA_IDX_FILE_NAME);
        DataMetadata data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(data, "save_result", "success");
        this.data = data;
    }

    public void setUpForDeployForLinearHLCR() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        System.err.printf("ENTER TestDeployManager#setUpForDeploy(%s)%n", inputPath);
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("LinearHLCRGlobalWeight.json"),      inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("LinearRegressionGlobalModel.json"), inputPath.resolve("LinearRegressionGlobalModel.json"));

        Files.copy(LinearHLCRSamplePath.resolve("back_up").resolve(LinearFedHLCRClient.HYPER_PARAM_FILE_NAME), inputPath.resolve(LinearFedHLCRClient.HYPER_PARAM_FILE_NAME));

        Files.copy(LinearHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_DAT_FILE_NAME), inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.copy(LinearHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_IDX_FILE_NAME), inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));

        Path datFile = Paths.get(inputPath.toString(), Const.TEST_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TEST_DATA_IDX_FILE_NAME);
        DataMetadata metaData = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(metaData, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(metaData, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(metaData, "save_result", "success");
        this.dataForLinearHLCR = metaData;
    }

    public void setUpForTrain() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        System.err.printf("ENTER TestDeployManager#setUpForTrain(%s)%n", trainInputPath);
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), 
                trainInputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), 
                trainInputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), 
                trainInputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), 
                trainInputPath.resolve("graph.nntxt"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), 
                trainInputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("Hyper_Param.dat"), 
                trainInputPath.resolve("Hyper_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_DAT_FILE_NAME), 
                trainInputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_IDX_FILE_NAME), 
                trainInputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));

        Path datFile = Paths.get(trainInputPath.toString(), Const.TRAIN_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(trainInputPath.toString(), Const.TRAIN_DATA_IDX_FILE_NAME);
        DataMetadata data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(data, "save_result", "success");
        this.data = data;
    }

    @After
    public void cleaning() throws IOException {
        System.err.printf("ENTER TestDeployManager#cleaning(%s)%n", inputPath);
        PathUtils.deleteDirectory(trainManagerRoot);
        PathUtils.deleteDirectory(predictManagerRoot);
        PathUtils.deleteDirectory(inputPath);
        PathUtils.deleteDirectory(outputPath);
        PathUtils.deleteDirectory(trainInputPath);
    }

/*
 #####   ######  #####   #        ####    #   #
 #    #  #       #    #  #       #    #    # #
 #    #  #####   #    #  #       #    #     #
 #    #  #       #####   #       #    #     #
 #    #  #       #       #       #    #     #
 #####   ######  #       ######   ####      #
*/
    @Test
    public void testDeployOnlyForLinearHLCR() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        System.out.printf("##### testDeployOnlyForLinearHLCR%n");
        setUpForDeployForLinearHLCR();

        try {
            PathUtils.deleteFile(inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
            PathUtils.deleteFile(inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
        }
        catch (NoSuchFileException ex) {
            ex.printStackTrace();
            fail();
        }
        catch (IOException ex) {
            ex.printStackTrace();
            fail();
        }

        final String FLID = "fl-d";
        final String taskID = "task-d";

        final TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForLinearHLCR();

        final Path clusterMapFile = predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME);

        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearHLCRGlobalWeight.json")));
        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearHLCRUpdateHyperParams.json")));
        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearRegressionGlobalModel.json")));
        assertFalse(Files.exists(clusterMapFile));

        final int result = deployManager.deploy(FLID, taskID, deployInfo, inputPath);
        assertEquals(0, result);

        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearHLCRGlobalWeight.json")));
        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearHLCRUpdateHyperParams.json")));
        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearRegressionGlobalModel.json")));
        assertFalse(Files.exists(clusterMapFile));
    }

    @Test
    public void testDeployOnlyForNNHLCR() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        System.out.printf("##### testDeployOnlyForNNHLCR%n");
        setUpForDeploy();

        try {
            PathUtils.deleteFile(inputPath.resolve(Const.ALL_DATA_DAT_FILE_NAME));
            PathUtils.deleteFile(inputPath.resolve(Const.ALL_DATA_IDX_FILE_NAME));
        }
        catch (NoSuchFileException ex) {
            ex.printStackTrace();
            fail();
        }
        catch (IOException ex) {
            ex.printStackTrace();
            fail();
        }

        final String FLID = "fl-d";
        final String taskID = "task-d";

        final TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();

        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("cluster1.protobuf")));
        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("cluster2.protobuf")));
        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("graph.nntxt")));
        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("HLCR_Param.dat")));

        final int result = deployManager.deploy(FLID, taskID, deployInfo, inputPath);
        assertEquals(0, result);

        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("cluster1.protobuf")));
        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("cluster2.protobuf")));
        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("graph.nntxt")));
        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("HLCR_Param.dat")));

        Path clusterMapFile = predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve(NNFedHLCRClient.CLUSTER_MAP_FILE_NAME);
        assertFalse(Files.exists(clusterMapFile));
    }

    @Test
    public void testDeployNoDataForLinearHLCR() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        System.out.printf("##### testDeployNoDataForLinearHLCR%n");
        setUpForDeployForLinearHLCR();

        try {
            PathUtils.deleteFile(inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
            PathUtils.deleteFile(inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
        }
        catch (NoSuchFileException ex) {
            ex.printStackTrace();
            fail();
        }
        catch (IOException ex) {
            ex.printStackTrace();
            fail();
        }

        final Path datFile = Paths.get(inputPath.toString(), "phony");
        final Path idxFile = Paths.get(inputPath.toString(), "phony");
        final DataMetadata nodata = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(nodata, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(nodata, "tensor_map_index_file", idxFile.toString());

        final String FLID = "fl-d";
        final String taskID = "task-d";

        final TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForLinearHLCR();

        final Path clusterMapFile = predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME);

        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearHLCRGlobalWeight.json")));
        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearHLCRUpdateHyperParams.json")));
        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearRegressionGlobalModel.json")));
        assertFalse(Files.exists(clusterMapFile));

        final int result = deployManager.deploy(FLID, taskID, nodata, deployInfo, inputPath);
        assertEquals(0, result);

        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearHLCRGlobalWeight.json")));
        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearHLCRUpdateHyperParams.json")));
        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearRegressionGlobalModel.json")));
        assertFalse(Files.exists(clusterMapFile));
    }

    @Test
    public void testDeployNoDataForNNHLCR() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        System.out.printf("##### testDeployNoDataForNNHLCR%n");
        setUpForDeploy();

        try {
            PathUtils.deleteFile(inputPath.resolve(Const.ALL_DATA_DAT_FILE_NAME));
            PathUtils.deleteFile(inputPath.resolve(Const.ALL_DATA_IDX_FILE_NAME));
        }
        catch (NoSuchFileException ex) {
            ex.printStackTrace();
            fail();
        }
        catch (IOException ex) {
            ex.printStackTrace();
            fail();
        }

        final Path datFile = Paths.get(inputPath.toString(), "phony");
        final Path idxFile = Paths.get(inputPath.toString(), "phony");
        final DataMetadata nodata = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(nodata, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(nodata, "tensor_map_index_file", idxFile.toString());

        final String FLID = "fl-d";
        final String taskID = "task-d";

        final TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();

        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("cluster1.protobuf")));
        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("cluster2.protobuf")));
        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("graph.nntxt")));
        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("HLCR_Param.dat")));

        final int result = deployManager.deploy(FLID, taskID, nodata, deployInfo, inputPath);
        assertEquals(0, result);

        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("cluster1.protobuf")));
        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("cluster2.protobuf")));
        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("graph.nntxt")));
        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("HLCR_Param.dat")));

        Path clusterMapFile = predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve(NNFedHLCRClient.CLUSTER_MAP_FILE_NAME);
        assertFalse(Files.exists(clusterMapFile));
    }

    @Test
    public void testDeployForLinearHLCR() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        System.out.printf("##### testDeployForLinearHLCR%n");
        setUpForDeployForLinearHLCR();

        final String FLID = "fl-d";
        final String taskID = "task-d";

        final TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForLinearHLCR();

        final Path clusterMapFile = predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME);

        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearHLCRGlobalWeight.json")));
        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearHLCRUpdateHyperParams.json")));
        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearRegressionGlobalModel.json")));
        assertFalse(Files.exists(clusterMapFile));

        final int result = deployManager.deploy(FLID, taskID, this.dataForLinearHLCR, deployInfo, inputPath);
        assertEquals(0, result);

        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearHLCRGlobalWeight.json")));
        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearHLCRUpdateHyperParams.json")));
        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("LinearRegressionGlobalModel.json")));
        assertTrue(Files.exists(clusterMapFile));

        String clusterMap = readFile(clusterMapFile.toString());
        String ans = readFile("src/test/resources/LinearHLCR/calibrate/cluster_map.json");
        isSameClustermapJson(ans, clusterMap, 2, 2);
    }

    @Test
    public void testDeployForNNHLCR() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        System.out.printf("##### testDeployForNNHLCR%n");
        setUpForDeploy();

        final String FLID = "fl-d";
        final String taskID = "task-d";

        final TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();

        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("cluster1.protobuf")));
        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("cluster2.protobuf")));
        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("graph.nntxt")));
        assertFalse(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("HLCR_Param.dat")));

        final int result = deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath);
        assertEquals(0, result);

        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("cluster1.protobuf")));
        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("cluster2.protobuf")));
        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("graph.nntxt")));
        assertTrue(Files.exists(predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve("HLCR_Param.dat")));

        Path clusterMapFile = predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID).resolve(NNFedHLCRClient.CLUSTER_MAP_FILE_NAME);
        String clusterMap = readFile(clusterMapFile.toString());
        String ans = readFile("src/test/resources/NNHLCR/calibrate/ClusterMapAns.dat");
        isSameClustermap(ans, clusterMap);
    }

    private JsonNode parseClusterMap(String jsonString, int K, int C) throws JsonProcessingException {
        System.err.printf("##### parseClusterMap[%s]%n", jsonString);
        JsonNode jn_node = new ObjectMapper().readTree(jsonString);
        assertNotNull(jn_node);
        JsonNode jn_K = jn_node.get("K");
        assertNotNull(jn_K);
        assertEquals(K, jn_K.intValue());
        JsonNode jn_cluster_map = jn_node.get("cluster_map");
        assertNotNull(jn_cluster_map);
        assertEquals(C, jn_cluster_map.size());
        Iterator<String> fieldNames = jn_cluster_map.fieldNames();
        while (fieldNames.hasNext()) {
            String fieldName = fieldNames.next();
            JsonNode jn_group = jn_cluster_map.get(fieldName);
            int group = jn_group.intValue();
            assertTrue(0 <= group && group < K);
        }
        return jn_node;
    }
    private void isSameClustermapJson(String str_a, String str_b, int K, int C) {
        try {
            JsonNode map_a = this.parseClusterMap(str_a, K, C);
            JsonNode map_b = this.parseClusterMap(str_b, K, C);

            final int k_a = map_a.get("K").intValue();
            final int k_b = map_b.get("K").intValue();

            assertEquals(k_a, k_b);

            Iterator<String> fieldNames = map_a.get("cluster_map").fieldNames();
            while (fieldNames.hasNext()) {
                String fieldName = fieldNames.next();
                JsonNode jn_group_a = map_a.get("cluster_map").get(fieldName);
                assertNotNull(jn_group_a);
                JsonNode jn_group_b = map_b.get("cluster_map").get(fieldName);
                assertNotNull(jn_group_b);
                int group_a = jn_group_a.intValue();
                int group_b = jn_group_b.intValue();
                assertEquals(group_a, group_b);
            }
        }
        catch (JsonProcessingException ex) {
            ex.printStackTrace();
            fail();
        }
    }

    private void isSameClustermap(String str_a, String str_b) {
        String[] strs_a = str_a.split(System.getProperty("line.separator"));
        String[] strs_b = str_b.split(System.getProperty("line.separator"));
        assertEquals(strs_a.length, strs_b.length);
        int L = strs_a.length;
        Map<String, Integer> cluster_map = new HashMap<>();
        for (int i=1;i<L;i++) {
            String[] raw = strs_a[i].split(" ");
            cluster_map.put(raw[0], Integer.parseInt(raw[1]));
        }
        for (int i=1;i<L;i++) {
            String[] raw = strs_b[i].split(" ");
            assertEquals(Integer.parseInt(raw[1]), (int)cluster_map.get(raw[0]));
        }
    }

    
    //@Test
    public void testDeployWithValidInput() 
            throws FLException, IOException, InstantiationException, 
            IllegalAccessException, ClassNotFoundException, NoSuchMethodException, InvocationTargetException {
        setUpForDeployForLinearHLCR();
        String FLID = "fl-1";
        String taskID = "task-d";
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForLinearHLCR();
        assertEquals(0, deployManager.deploy(FLID, taskID, this.dataForLinearHLCR, deployInfo, inputPath));
        Path firstDeployPath = predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID);
        assertEquals(true, PathChecker.checkFolderPath(firstDeployPath, true, true, true));
        Path backUpPath = trainManagerRoot.resolve(FLID).resolve(taskID);
        assertEquals(false, PathChecker.checkFolderPath(backUpPath, false, false, false));
        
        // redeploy case
        setUpForTrain();
        FLID = "fl-2";
        taskID = "task-d2";
        TrainManager trainManager = new TrainManager(trainManagerRoot);
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();
        assertEquals(0,trainManager.train(FLID, "train1", this.data, trainInfo, trainInputPath, outputPath).getStatus());
        assertEquals(0, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
        Path secondDeployPath = predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID);
        assertEquals(true, PathChecker.checkFolderPath(firstDeployPath, true, true, true));
        assertEquals(true, PathChecker.checkFolderPath(secondDeployPath, true, true, true));
        backUpPath = trainManagerRoot.resolve(FLID).resolve(taskID);
        assertEquals(false, PathChecker.checkFolderPath(backUpPath, false, false, false));
        // duplication case
        assertEquals(1, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
        assertEquals(false, PathChecker.checkFolderPath(backUpPath, false, false, false));
        
        // redeploy case
        FLID = "fl-3";
        taskID = "task-d3";
        assertEquals(0,trainManager.train(FLID, "train2", this.data, trainInfo, trainInputPath, outputPath).getStatus());
        assertEquals(0, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
        Path thirdDeployPath = predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID);
        assertEquals(false, PathChecker.checkFolderPath(firstDeployPath, true, true, true));
        assertEquals(true, PathChecker.checkFolderPath(secondDeployPath, true, true, true));
        assertEquals(true, PathChecker.checkFolderPath(thirdDeployPath, true, true, true));
        backUpPath = trainManagerRoot.resolve(FLID).resolve(taskID);
        assertEquals(false, PathChecker.checkFolderPath(backUpPath, false, false, false));
}

    @Test
    public void testDeployWithInvalidInputPath() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpForDeploy();
        String FLID = "fl-1";
        String taskID = "task-bad";
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForLinearHLCR();
        Path invalidInputPath = Paths.get("bad_path");
        assertEquals(1, deployManager.deploy(FLID, taskID, this.data, deployInfo, invalidInputPath));
        Path path = predictManagerRoot.resolve(deployInfo.getAppID()).resolve(taskID);
        assertFalse(PathChecker.checkFolderPath(path, true, true, true));
    }


    @Test //0.15157336
    public void testDeployPredictWithValidData() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        Double[] flattenedSequenceData = Tensor.toDoubleArrayFrom(this.sequenceData);
        assertNotNull(flattenedSequenceData);
        int m = this.sequenceData.length;
        int n = this.sequenceData[0].length;
        TensorMap tensorMap = TensorMap.newInstance();
        tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(n));
        tensorMap.set(NNFedHLCRClient.TENSOR_SEQUENCE_DATA, Tensor.newTensor(TensorShape.createShape(m, n), flattenedSequenceData));
        tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));

        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        String FLID = "fl";
        setUpForDeploy();
        String taskID = "good_fl";
        assertEquals(0, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
        PredictManager pm = new PredictManager(predictManagerRoot, deployInfo.getAppID());
        PredictResult pr = pm.predict(tensorMap);
        assertEquals(0, pr.getStatus());
        TensorMap result = pr.getResult();
        Tensor resultLabel = result.get(NNFedHLCRClient.TENSOR_Y_PRED);
        assertNotNull(resultLabel);
        assertTrue(resultLabel.isScalar());
        Double predictLabel = (Double)resultLabel.getValue();
        FLLogger.i(String.valueOf(predictLabel));
    }

    @Test
    public void testDeployPredictWithNoDataForNNHLCR() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        Double[] flattenedSequenceData = Tensor.toDoubleArrayFrom(this.sequenceData);
        assertNotNull(flattenedSequenceData);
        int m = this.sequenceData.length;
        int n = this.sequenceData[0].length;
        TensorMap tensorMap = TensorMap.newInstance();
        tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(n));
        tensorMap.set(NNFedHLCRClient.TENSOR_SEQUENCE_DATA, Tensor.newTensor(TensorShape.createShape(m, n), flattenedSequenceData));
        tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));

        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        String FLID = "fl";
        setUpForDeploy();
        String taskID = "nodata_fl";
        assertEquals(0, deployManager.deploy(FLID, taskID, deployInfo, inputPath));
        PredictManager pm = new PredictManager(predictManagerRoot, deployInfo.getAppID());
        PredictResult pr = pm.predict(tensorMap);
        assertEquals(0, pr.getStatus());
        TensorMap result = pr.getResult();
        Tensor resultLabel = result.get(NNFedHLCRClient.TENSOR_Y_PRED);
        assertNotNull(resultLabel);
        assertTrue(resultLabel.isScalar());
        Double predictLabel = (Double)resultLabel.getValue();
        FLLogger.i(String.valueOf(predictLabel));
    }

    @Test
    public void testDeployPredictWithNoDataForLinearHLCR() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        TensorMap tensorMap = TensorMap.fromJsonString("{\"x\":{\"value\":[3.0,3.0],\"shape\":[2]},\"g\":{\"value\":[\"group0\"],\"shape\":[1]}}");

        setUpForDeployForLinearHLCR();
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForLinearHLCR();
        String FLID = "fl";
        setUpForDeploy();
        String taskID = "nodata_fl";
        assertEquals(0, deployManager.deploy(FLID, taskID, deployInfo, inputPath));
        PredictManager pm = new PredictManager(predictManagerRoot, deployInfo.getAppID());
        PredictResult pr = pm.predict(tensorMap);
        assertEquals(0, pr.getStatus());
        TensorMap result = pr.getResult();
        Tensor resultLabel = result.get(NNFedHLCRClient.TENSOR_Y_PRED);
        assertNotNull(resultLabel);
        assertTrue(resultLabel.isScalar());
        Double predictLabel = (Double)resultLabel.getValue();
        FLLogger.i(String.valueOf(predictLabel));
    }

    @Test
    public void testDeployPredictWithWrongNnpI5() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        String FLID = "bad_fl";
        setUpForDeploy();
        String taskID = "bad_nntxt1";
        Files.copy(nnpSamplePath.resolve("I5.nntxt"), 
                inputPath.resolve("graph.nntxt"), StandardCopyOption.REPLACE_EXISTING);
        Files.copy(nnpSamplePath.resolve("I5.protobuf"), 
                inputPath.resolve("cluster1.protobuf"), StandardCopyOption.REPLACE_EXISTING);
        Files.copy(nnpSamplePath.resolve("I5.protobuf"), 
                inputPath.resolve("cluster2.protobuf"), StandardCopyOption.REPLACE_EXISTING);
        assertEquals(1, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
        Path backUpPath = trainManagerRoot.resolve(FLID).resolve(taskID);
        assertEquals(false, PathChecker.checkFolderPath(backUpPath, false, false, false));
    }

    @Test
    public void testDeployPredictWithWrongNnpT10() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        String FLID = "bad_fl";
        setUpForDeploy();
        String taskID = "bad_nntxt1";
        Files.copy(nnpSamplePath.resolve("T10.nntxt"), 
                inputPath.resolve("graph.nntxt"), StandardCopyOption.REPLACE_EXISTING);
        Files.copy(nnpSamplePath.resolve("T10.protobuf"), 
                inputPath.resolve("cluster1.protobuf"), StandardCopyOption.REPLACE_EXISTING);
        Files.copy(nnpSamplePath.resolve("T10.protobuf"), 
                inputPath.resolve("cluster2.protobuf"), StandardCopyOption.REPLACE_EXISTING);
        assertEquals(1, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
        Path backUpPath = trainManagerRoot.resolve(FLID).resolve(taskID);
        assertEquals(false, PathChecker.checkFolderPath(backUpPath, false, false, false));
    }

    @Test
    public void testDeployPredictWithWrongNnpInfer() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        String FLID = "bad_fl";
        setUpForDeploy();
        String taskID = "bad_nntxt1";
        Files.copy(nnpSamplePath.resolve("infer.nntxt"), 
                inputPath.resolve("graph.nntxt"), StandardCopyOption.REPLACE_EXISTING);
        Files.copy(nnpSamplePath.resolve("infer.protobuf"), 
                inputPath.resolve("cluster1.protobuf"), StandardCopyOption.REPLACE_EXISTING);
        Files.copy(nnpSamplePath.resolve("infer.protobuf"), 
                inputPath.resolve("cluster2.protobuf"), StandardCopyOption.REPLACE_EXISTING);
        assertEquals(1, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
        Path backUpPath = trainManagerRoot.resolve(FLID).resolve(taskID);
        assertEquals(false, PathChecker.checkFolderPath(backUpPath, false, false, false));
    }

    //@Test
    public void testDeployPredictWithValidNnpB128() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        String FLID = "valid_fl";
        setUpForDeploy();
        String taskID = "valid_nntxt1";
        Files.copy(nnpSamplePath.resolve("B128.nntxt"), 
                inputPath.resolve("graph.nntxt"), StandardCopyOption.REPLACE_EXISTING);
        Files.copy(nnpSamplePath.resolve("B128.protobuf"), 
                inputPath.resolve("cluster1.protobuf"), StandardCopyOption.REPLACE_EXISTING);
        Files.copy(nnpSamplePath.resolve("B128.protobuf"), 
                inputPath.resolve("cluster2.protobuf"), StandardCopyOption.REPLACE_EXISTING);
        assertEquals(0, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
        Path backUpPath = trainManagerRoot.resolve(FLID).resolve(taskID);
        assertEquals(false, PathChecker.checkFolderPath(backUpPath, false, false, false));
    }

    @Test
    public void testDeployPredictWithBadTxtForHLCRParam() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        String FLID = "bad_fl";
        setUpForDeploy();
        String taskID = "bad_hlcr1";
        Files.copy(badNNHLCRSamplePath.resolve("bad_txt.txt"), 
                inputPath.resolve("HLCR_Param.dat"), StandardCopyOption.REPLACE_EXISTING);
        assertEquals(1, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
        Path backUpPath = trainManagerRoot.resolve(FLID).resolve(taskID);
        assertEquals(false, PathChecker.checkFolderPath(backUpPath, false, false, false));
    }

    @Test
    public void testDeployPredictWithBadHLCRParamWrongK() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        String FLID = "bad_fl";
        setUpForDeploy();
        String taskID = "bad_hlcr2";
        Files.copy(badNNHLCRSamplePath.resolve("wrong_K_HLCR_Param.dat"), 
                inputPath.resolve("HLCR_Param.dat"), StandardCopyOption.REPLACE_EXISTING);
        assertEquals(1, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
        Path backUpPath = trainManagerRoot.resolve(FLID).resolve(taskID);
        assertEquals(false, PathChecker.checkFolderPath(backUpPath, false, false, false));
    }

    @Test
    public void testDeployPredictWithBadHLCRParamWrongI() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        String FLID = "bad_fl";
        setUpForDeploy();
        String taskID = "bad_hlcr3";
        Files.copy(badNNHLCRSamplePath.resolve("wrong_I_HLCR_Param.dat"), 
                inputPath.resolve("HLCR_Param.dat"), StandardCopyOption.REPLACE_EXISTING);
        assertEquals(1, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
        Path backUpPath = trainManagerRoot.resolve(FLID).resolve(taskID);
        assertEquals(false, PathChecker.checkFolderPath(backUpPath, false, false, false));
    }

    @Test
    public void testDeployPredictWithBadTxtForUpdateParam() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        String FLID = "bad_fl";
        setUpForDeploy();
        String taskID = "bad_udpate_Param1";
        Files.copy(badNNHLCRSamplePath.resolve("bad_txt.txt"), 
                inputPath.resolve(NNFedHLCRClient.UPDATE_PARAM_FILE_NAME), StandardCopyOption.REPLACE_EXISTING);
        assertEquals(1, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
        Path backUpPath = trainManagerRoot.resolve(FLID).resolve(taskID);
        assertEquals(false, PathChecker.checkFolderPath(backUpPath, false, false, false));
    }

//  @Test
//  public void testDeployPredictWithBadTxtForAllData() throws IOException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
//      TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
//      String FLID = "bad_fl";
//      setUpForDeploy();
//      String taskID = "bad_hlcr2";
//      Files.copy(badNNHLCRSamplePath.resolve("bad_txt.txt"), 
//              inputPath.resolve(PredictManager.ALL_DATA_FILE_NAME), StandardCopyOption.REPLACE_EXISTING);
//      assertEquals(1, deployManager.deploy(FLID, taskID, deployInfo, inputPath));
//  }

    @Test
    public void testDeployWithFailedDataSerializerSave() 
            throws FLException, IOException, InstantiationException, 
            IllegalAccessException, ClassNotFoundException, NoSuchMethodException, InvocationTargetException {
        setUpForDeploy();
        DataMetadataUtil.set(this.data, "save_result", "failed");
        String FLID = "fl-1";
        String taskID = "task-save";
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForLinearHLCR();
        assertEquals(1, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
    }

    /*
  ####    #####   ####   #####
 #          #    #    #  #    #
  ####      #    #    #  #    #
      #     #    #    #  #####
 #    #     #    #    #  #
  ####      #     ####   #
*/

    @Test
    public void testStopWithValidInput() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpForDeploy();
        String FLID = "fl-1";
        String taskID = "task-d";
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        assertEquals(0, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
        Path deployPath = predictManagerRoot.resolve(deployInfo.getAppID());
        assertTrue(PathChecker.checkFolderPath(deployPath, true, true, true));
        TaskInfo.PBStopInfo stopInfo = CreatePBForTest.createValidStopInfo();
        assertEquals(0, deployManager.stop(stopInfo));
        Path stopPath = predictManagerRoot.resolve(stopInfo.getAppID());
        assertFalse(PathChecker.checkFolderPath(stopPath, false, false, false));
        assertEquals(deployPath, stopPath);
        // duplication stop
        assertEquals(0, deployManager.stop(stopInfo));
    }

    @Test
    public void testStopWithValidAppID() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpForDeploy();
        String FLID = "fl-1";
        String taskID = "task-d";
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        String appID = deployInfo.getAppID();
        assertEquals(0, deployManager.deploy(FLID, taskID, this.data, deployInfo, inputPath));
        Path deployPath = predictManagerRoot.resolve(appID);
        assertTrue(PathChecker.checkFolderPath(deployPath, true, true, true));
        assertEquals(0, deployManager.stop(appID));
        Path stopPath = predictManagerRoot.resolve(appID);
        assertFalse(PathChecker.checkFolderPath(stopPath, false, false, false));
        assertEquals(deployPath, stopPath);
        // duplication stop
        assertEquals(0, deployManager.stop(appID));
    }
    /*
 #####   #####      #    #    #    ##     #####  ######
 #    #  #    #     #    #    #   #  #      #    #
 #    #  #    #     #    #    #  #    #     #    #####
 #####   #####      #    #    #  ######     #    #
 #       #   #      #     #  #   #    #     #    #
 #       #    #     #      ##    #    #     #    ######
*/

    @Test
    public void testCopyModelFile() 
            throws NoSuchMethodException,
            SecurityException,
            IllegalAccessException,
            IllegalArgumentException, 
            InvocationTargetException, 
            IOException
    {
        Method method = DeployManager.class.getDeclaredMethod("copyModelFile", 
                Path.class, Path.class, String.class, TaskInfo.PBDeployInfo.class);
        method.setAccessible(true);
        String taskID = "taskD";
        // valid case
        Path path1 = inputPath.resolve("tmp1.nnp");
        Path path2 = inputPath.resolve("tmp2.nnp");
        File file1 = new File(path1.toString());
        File file2 = new File(path2.toString());
        assertTrue(file1.createNewFile());
        assertTrue(file2.createNewFile());
        assertEquals(0, (int)method.invoke(deployManager, inputPath, predictManagerRoot, 
                taskID, CreatePBForTest.createValidDeployInfoForNNHLCR()));
        Path newPath1 = predictManagerRoot.resolve("tmp1.nnp");
        Path newPath2 = predictManagerRoot.resolve("tmp2.nnp");
        Path newPath3 = predictManagerRoot.resolve("TrainData.dat");
        Path newPath4 = predictManagerRoot.resolve(taskID + ".protobuf");
        assertTrue(Files.exists(newPath1));
        assertTrue(Files.exists(newPath2));
        assertFalse(Files.exists(newPath3));
        assertTrue(Files.exists(newPath4));
        // duplication case
        assertEquals(0, (int)method.invoke(deployManager, inputPath, predictManagerRoot, 
                taskID, CreatePBForTest.createValidDeployInfoForNNHLCR()));
        // invalid case
        Path badPath = Paths.get("badpath");
        assertEquals(1, (int)method.invoke(deployManager, badPath, predictManagerRoot, 
                taskID, CreatePBForTest.createValidDeployInfoForNNHLCR()));
    }

    @Test
    public void testCopyClusterMappingFile() 
            throws NoSuchMethodException,
            SecurityException,
            IllegalAccessException,
            IllegalArgumentException, 
            InvocationTargetException, 
            IOException
    {
        Method method = DeployManager.class.getDeclaredMethod("copyBackUpFile", 
                Path.class, Path.class);
        method.setAccessible(true);
        Path path1 = inputPath.resolve("tmp1.dat");
        Path path2 = inputPath.resolve("tmp2.dat");
        File file1 = new File(path1.toString());
        File file2 = new File(path2.toString());
        assertTrue(file1.createNewFile());
        assertTrue(file2.createNewFile());
        assertEquals(0, (int)method.invoke(deployManager, inputPath, predictManagerRoot));
        Path newPath1 = predictManagerRoot.resolve("tmp1.dat");
        Path newPath2 = predictManagerRoot.resolve("tmp2.dat");
        assertTrue(Files.exists(newPath1));
        assertTrue(Files.exists(newPath2));
        // duplication case
        assertEquals(0, (int)method.invoke(deployManager, inputPath, predictManagerRoot));
        // invalid case
        Path badPath = Paths.get("badpath");
        assertEquals(1, (int)method.invoke(deployManager, badPath, predictManagerRoot));
    }

    @Test
    public void testDeleteDir() 
            throws NoSuchMethodException,
            SecurityException,
            IllegalAccessException,
            IllegalArgumentException, 
            InvocationTargetException, 
            IOException
    {
        Method method = DeployManager.class.getDeclaredMethod("deleteDir", Path.class);
        method.setAccessible(true);
        // valid case
        Path validPath = Paths.get("src/test/resources/tmp");
        Files.createDirectories(validPath);
        assertEquals(0, (int)method.invoke(deployManager, validPath));
        Path badPath = Paths.get("badpath");
        // invalid path case
        assertEquals(1, (int)method.invoke(deployManager, badPath));
    }

    @Test
    public void testGetNewBackUpFolder() 
            throws NoSuchMethodException,
            SecurityException,
            IllegalAccessException,
            IllegalArgumentException, 
            InvocationTargetException, 
            IOException
    {
        Method method = DeployManager.class.getDeclaredMethod("getNewBackUpFolder",
                String.class, String.class);
        method.setAccessible(true);
        // valid case
        Path path = (Path)method.invoke(deployManager, "test1", "test2");
        assertTrue(path.toString().equals("src/test/resources/TrainManagerRoot/test1/test2"));
        // duplication case
        path = (Path)method.invoke(deployManager, "test1", "test2");
        assertTrue(path.toString().equals("src/test/resources/TrainManagerRoot/test1/test2"));
        // invalid input
        path = (Path)method.invoke(deployManager, "/etc", "issue");
        assertNull(path);
    }

    @Test
    public void testCreateFolderForPrediction() 
            throws NoSuchMethodException,
            SecurityException,
            IllegalAccessException,
            IllegalArgumentException, 
            InvocationTargetException, 
            IOException
    {
        Method method = DeployManager.class.getDeclaredMethod("createFolderForPrediction",
                String.class, String.class);
        method.setAccessible(true);
        Path path = (Path)method.invoke(deployManager, "test1", "test2");
        assertTrue(path.toString().equals("src/test/resources/PredictManagerRoot/test1/test2"));
        assertTrue(Files.exists(path));
        // duplication case
        path = (Path)method.invoke(deployManager, "test1", "test2");
        assertTrue(path.toString().equals("src/test/resources/PredictManagerRoot/test1/test2"));
        // invalid case
        path = (Path)method.invoke(deployManager, "/etc", "passwd");
        assertNull(path);
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

    private DataMetadata generateOver10000TensorMaps() {
        Path datFile = Paths.get(this.inputPath.toString(), "TensorMaps10001.jsonl");
        Path idxFile = Paths.get(this.inputPath.toString(), "TensorMaps10001.index");
        DataSerializer serializer;
        try {
            serializer = DataSerializer.createFor(datFile, idxFile);
        }
        catch (FLException ex) {
            ex.printStackTrace();
            return null;
        }
        try {
            try (BufferedReader br = Files.newBufferedReader(this.inputPath.resolve(Const.ALL_DATA_DAT_FILE_NAME))) {
                TensorMap tensorMap = TensorMap.fromJsonString(br.readLine());
                for (int n = 0; n < 10001; n++) {
                    serializer.save(tensorMap);
                }
            }
        }
        catch (IOException ex) {
            ex.printStackTrace();
            return null;
        }
        return serializer.getMetadata();
    }

    @Test
    public void testDeploy_NNHLCR_Over10000TensorMaps() {
        try { setUpForDeploy(); } catch (Exception ex) { ex.printStackTrace(); fail(); }

        DataMetadata meta = this.generateOver10000TensorMaps();
        assertNotNull(meta);

        final String FLID = "fl-d";
        final String taskID = "task-d";

        final TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();

        final int result = deployManager.deploy(FLID, taskID, meta, deployInfo, this.inputPath);
        assertEquals(1, result);
    }

//    @Test
//    public void testDeploy_NNHLCR_NoReadPermitToCalibrateParamsFile() {
//        try { setUpForDeploy(); } catch (Exception ex) { ex.printStackTrace(); fail(); }
//
//        this.inputPath.resolve(NNFedHLCRClient.UPDATE_PARAM_FILE_NAME).toFile().setReadable(false);
//
//        final String FLID = "fl-2";
//        final String taskID = "task-2_1";
//
//        final TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
//
//        final int result = deployManager.deploy(FLID, taskID, this.data, deployInfo, this.inputPath);
//
//        assertEquals(1, result);
//    }

    @Test
    public void testDeploy_NNHLCR_InvalidNumOfFeatures() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("calibrate").resolve("lstm20.protobuf"), inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("calibrate").resolve("lstm19.protobuf"), inputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("calibrate").resolve("network.nntxt"), inputPath.resolve("graph.nntxt"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("back_up").resolve(NNFedHLCRClient.UPDATE_PARAM_FILE_NAME), inputPath.resolve(NNFedHLCRClient.UPDATE_PARAM_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("InvalidNumOfFeatures.jsonl"), inputPath.resolve(Const.ALL_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("TrainData.txt"), inputPath.resolve(Const.ALL_DATA_IDX_FILE_NAME));

        Path datFile = Paths.get(inputPath.toString(), Const.ALL_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.ALL_DATA_IDX_FILE_NAME);
        DataMetadata data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(data, "save_result", "success");
        assertNotNull(data);

        final String FLID = "fl-d";
        final String taskID = "task-d";

        final TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();

        final int result = deployManager.deploy(FLID, taskID, data, deployInfo, this.inputPath);
        assertEquals(1, result);

    }

    @Test
    public void testDeploy_NNHLCR_InvalidTensorMap3() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("calibrate").resolve("lstm20.protobuf"), inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("calibrate").resolve("lstm19.protobuf"), inputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("calibrate").resolve("network.nntxt"), inputPath.resolve("graph.nntxt"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("back_up").resolve(NNFedHLCRClient.UPDATE_PARAM_FILE_NAME), inputPath.resolve(NNFedHLCRClient.UPDATE_PARAM_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("InvalidTensorY.jsonl"), inputPath.resolve(Const.ALL_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("TrainData.txt"), inputPath.resolve(Const.ALL_DATA_IDX_FILE_NAME));

        Path datFile = Paths.get(inputPath.toString(), Const.ALL_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.ALL_DATA_IDX_FILE_NAME);
        DataMetadata data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(data, "save_result", "success");
        assertNotNull(data);

        final String FLID = "fl-d";
        final String taskID = "task-d";

        final TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();

        final int result = deployManager.deploy(FLID, taskID, data, deployInfo, this.inputPath);
        assertEquals(1, result);
    }

    @Test
    public void testDeploy_NNHLCR_InvalidTensorXLengthMax() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("calibrate").resolve("lstm20.protobuf"), inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("calibrate").resolve("lstm19.protobuf"), inputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("calibrate").resolve("network.nntxt"), inputPath.resolve("graph.nntxt"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("back_up").resolve(NNFedHLCRClient.UPDATE_PARAM_FILE_NAME), inputPath.resolve(NNFedHLCRClient.UPDATE_PARAM_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("InvalidTensorXLengthMax.jsonl"), inputPath.resolve(Const.ALL_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("TrainData.txt"), inputPath.resolve(Const.ALL_DATA_IDX_FILE_NAME));

        Path datFile = Paths.get(inputPath.toString(), Const.ALL_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.ALL_DATA_IDX_FILE_NAME);
        DataMetadata data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(data, "save_result", "success");
        assertNotNull(data);

        final String FLID = "fl-d";
        final String taskID = "task-d";

        final TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();

        final int result = deployManager.deploy(FLID, taskID, data, deployInfo, this.inputPath);
        assertEquals(1, result);
    }

    @Test
    public void testDeploy_NNHLCR_NoNumOfFeatures_1() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpForDeploy();

        Path datFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.jsonl");
        Path idxFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.index");

        // String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        String tensorMapString = "{\"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        TensorMap tensorMap = TensorMap.fromJsonString(tensorMapString);
        assertNotNull(tensorMap);

        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        serializer.save(tensorMap);
        DataMetadata metaData = serializer.getMetadata();

        final String FLID = "fl-d";
        final String taskID = "task-d";

        final TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();

        final int result = deployManager.deploy(FLID, taskID, metaData, deployInfo, this.inputPath);
        assertEquals(1, result);
    }

    @Test
    public void testDeploy_NNHLCR_NoNumOfFeatures_2() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpForDeploy();

        Path datFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.jsonl");
        Path idxFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.index");

        String tensorMapString_1 = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        String tensorMapString_2 = "{\"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        TensorMap tensorMap_1 = TensorMap.fromJsonString(tensorMapString_1);
        assertNotNull(tensorMap_1);
        TensorMap tensorMap_2 = TensorMap.fromJsonString(tensorMapString_2);
        assertNotNull(tensorMap_2);

        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        serializer.save(tensorMap_1);
        serializer.save(tensorMap_2);
        DataMetadata metaData = serializer.getMetadata();

        final String FLID = "fl-d";
        final String taskID = "task-d";

        final TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();

        final int result = deployManager.deploy(FLID, taskID, metaData, deployInfo, this.inputPath);
        assertEquals(1, result);
    }

    @Test
    public void testDeploy_NNHLCR_NoGroupLabel() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpForDeploy();

        Path datFile = Paths.get(inputPath.toString(), "NoGroupLabel.jsonl");
        Path idxFile = Paths.get(inputPath.toString(), "NoGroupLabel.index");

        // String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [2, 3], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        TensorMap tensorMap = TensorMap.fromJsonString(tensorMapString);
        assertNotNull(tensorMap);

        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        serializer.save(tensorMap);
        DataMetadata metaData = serializer.getMetadata();

        final String FLID = "fl-d";
        final String taskID = "task-d";

        final TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();

        final int result = deployManager.deploy(FLID, taskID, metaData, deployInfo, this.inputPath);
        assertEquals(1, result);
    }

    @Test
    public void testDeploy_NNHLCR_NoY() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpForDeploy();

        Path datFile = Paths.get(inputPath.toString(), "NoY.jsonl");
        Path idxFile = Paths.get(inputPath.toString(), "NoY.index");

        // String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [2, 3], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"x\": {\"shape\": [2, 3], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        TensorMap tensorMap = TensorMap.fromJsonString(tensorMapString);
        assertNotNull(tensorMap);

        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        serializer.save(tensorMap);
        DataMetadata metaData = serializer.getMetadata();

        final String FLID = "fl-d";
        final String taskID = "task-d";

        final TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();

        final int result = deployManager.deploy(FLID, taskID, metaData, deployInfo, this.inputPath);
        assertEquals(1, result);
    }

    @Test
    public void testDeploy_NNHLCR_NoX() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpForDeploy();

        Path datFile = Paths.get(inputPath.toString(), "NoX.jsonl");
        Path idxFile = Paths.get(inputPath.toString(), "NoX.index");

        // String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [2, 3], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}}";
        TensorMap tensorMap = TensorMap.fromJsonString(tensorMapString);
        assertNotNull(tensorMap);

        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        serializer.save(tensorMap);
        DataMetadata metaData = serializer.getMetadata();

        final String FLID = "fl-d";
        final String taskID = "task-d";

        final TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();

        final int result = deployManager.deploy(FLID, taskID, metaData, deployInfo, this.inputPath);
        assertEquals(1, result);
    }
}
