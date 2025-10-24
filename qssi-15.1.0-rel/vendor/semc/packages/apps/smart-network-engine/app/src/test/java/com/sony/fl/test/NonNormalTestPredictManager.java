package com.sony.fl.test;

//import org.apache.commons.codec.binary.Hex;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

//import java.sql.Connection;
//import java.sql.DriverManager;
//import java.sql.SQLException;
//import java.sql.ResultSet;
//import java.sql.Statement;
import java.sql.Timestamp;
import java.text.SimpleDateFormat;

import com.sony.fl.PredictManager;
import com.sony.fl.DeployManager;

import com.sony.fl.algorithm.NNFedHLCRClient;
import com.sony.fl.exception.FLException;
import com.sony.fl.pb.TaskInfo;
//import com.sony.fl.utils.Base64Wrapper;
import com.sony.fl.utils.Const;
import com.sony.fl.utils.CreatePBForTest;

import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.DataSerializer;
import com.sony.fl.tensor.Tensor;
import com.sony.fl.tensor.TensorMap;
import com.sony.fl.tensor.TensorShape;

import org.apache.commons.io.file.PathUtils;
//import org.junit.After;
//import org.junit.Before;
//import org.junit.Test;


public class NonNormalTestPredictManager {

    private static final String RED = "[31m";
    private static final String GREEN = "[32m";
    private static final String ORANGE = "[33m";
    private static final String WHITE = "[37m";

    private static void println_RED(String s) {//{{{
        System.out.print(RED);
        System.out.println(s);
        System.out.print(WHITE);
    }//}}}
    private static void println_GREEN(String s) {//{{{
        System.out.print(GREEN);
        System.out.println(s);
        System.out.print(WHITE);
    }//}}}
    private static void println_ORANGE(String s) {//{{{
        System.out.print(ORANGE);
        System.out.println(s);
        System.out.print(WHITE);
    }//}}}

    private static final int LOOP_COUNT;
    static {
        int loop_count = 1;
        String s = System.getenv("FL_LOOP_COUNT");
        try {
            if (s != null) {
                int v = Integer.parseInt(s);
                if (v > 0) loop_count = v;
            }
        }
        catch (NumberFormatException ex) {
            System.err.println(String.format("The loop counter uses 1 because FL_LOOP_COUNT[%s] is invalid", s));
        }
        LOOP_COUNT = loop_count;
    }

    public static void createFilesForDeploy(Path inputPath, Path NNHLCRSamplePath) throws IOException {//{{{
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
    }//}}}

    private static final Path trainManagerRoot;
    private static final Path predictManagerRoot;
    private static final Path inputPath;
    private static final Path NNHLCRSamplePath;

    static {//{{{
        trainManagerRoot   = Paths.get("src/test/resources/TrainManagerRoot");
        predictManagerRoot = Paths.get("src/test/resources/PredictManagerRoot");
        inputPath          = Paths.get("src/test/resources/input");
        NNHLCRSamplePath   = Paths.get("src/test/resources/NNHLCR");
    }//}}}

    public static void clean() {//{{{
        try { PathUtils.deleteDirectory(predictManagerRoot); }
        catch (IOException ex) { return; }
        try { PathUtils.deleteDirectory(trainManagerRoot); }
        catch (IOException ex) { return; }
        try { PathUtils.deleteDirectory(inputPath); }
        catch (IOException ex) { return; }
    }//}}}

    public static boolean case1_1() {//{{{
        clean();
        PredictManager predictManager = null;
        try {
            //
            Files.createDirectories(trainManagerRoot);
            Files.createDirectories(predictManagerRoot);

            DeployManager deployManager = new DeployManager(trainManagerRoot, predictManagerRoot);

            String FLID = "fl-p";
            String taskID = "task-p";
            TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
            Files.createDirectories(inputPath);
            createFilesForDeploy(inputPath, NNHLCRSamplePath);

            Path datFile = Paths.get(inputPath.toString(), Const.ALL_DATA_DAT_FILE_NAME);
            Path idxFile = Paths.get(inputPath.toString(), Const.ALL_DATA_IDX_FILE_NAME);
            DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
            try (BufferedReader br = Files.newBufferedReader(datFile)) {
                TensorMap tensorMap = TensorMap.fromJsonString(br.readLine());    // 1-line JSON object
                serializer.save(tensorMap);
            }
            DataMetadata data = serializer.getMetadata();

            deployManager.deploy(FLID, taskID, data, deployInfo, inputPath);

            //
/**/        Path invalidRoot = Paths.get("src/test/resources/InvalidRoot");
            String appID = deployInfo.getAppID();

            println_GREEN(String.format("[%s] Start", new Object(){}.getClass().getEnclosingMethod().getName()));
            predictManager = new PredictManager(invalidRoot, appID);
        }
        catch (FLException | IOException ex) {
            println_GREEN(String.format("[%s] The result was as expected.", new Object(){}.getClass().getEnclosingMethod().getName()));
            System.out.print("[33m");
            ex.printStackTrace();
            System.out.print("[37m");
            return true;
        }
        finally {
            if (predictManager != null) {
                println_GREEN(String.format("[%s] finalize", new Object(){}.getClass().getEnclosingMethod().getName()));
                predictManager.finalize();
            }
        }
        println_RED(String.format("[%s] The result was not as expected.", new Object(){}.getClass().getEnclosingMethod().getName()));
        return false;
    }//}}}

    public static boolean case1_2() {//{{{
        clean();
        PredictManager predictManager = null;
        try {
            //
            Files.createDirectories(trainManagerRoot);
            Files.createDirectories(predictManagerRoot);

            DeployManager deployManager = new DeployManager(trainManagerRoot, predictManagerRoot);

            String FLID = "fl-p";
            String taskID = "task-p";
            TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
            Files.createDirectories(inputPath);
            createFilesForDeploy(inputPath, NNHLCRSamplePath);

            Path datFile = Paths.get(inputPath.toString(), Const.ALL_DATA_DAT_FILE_NAME);
            Path idxFile = Paths.get(inputPath.toString(), Const.ALL_DATA_IDX_FILE_NAME);
            DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
            try (BufferedReader br = Files.newBufferedReader(datFile)) {
                TensorMap tensorMap = TensorMap.fromJsonString(br.readLine());    // 1-line JSON object
                serializer.save(tensorMap);
            }
            DataMetadata data = serializer.getMetadata();

            deployManager.deploy(FLID, taskID, data, deployInfo, inputPath);

            //
/**/        Path sqliteDB = Paths.get(predictManagerRoot.toString(), "sqlight.db");
/**/        try (BufferedWriter bw = Files.newBufferedWriter(sqliteDB, StandardCharsets.UTF_8)) {
/**/            bw.write("Test");
/**/            bw.newLine();
/**/        }

            //
            String appID = deployInfo.getAppID();

            println_GREEN(String.format("[%s] Start", new Object(){}.getClass().getEnclosingMethod().getName()));
            predictManager = new PredictManager(predictManagerRoot, appID);
        }
        catch (FLException | IOException ex) {
            println_GREEN(String.format("[%s] The result was as expected.", new Object(){}.getClass().getEnclosingMethod().getName()));
            System.out.print(ORANGE);
            ex.printStackTrace();
            System.out.print(WHITE);
            return true;
        }
        finally {
            if (predictManager != null) {
                println_GREEN(String.format("[%s] finalize", new Object(){}.getClass().getEnclosingMethod().getName()));
                predictManager.finalize();
            }
        }
        println_RED(String.format("[%s] The result was not as expected.", new Object(){}.getClass().getEnclosingMethod().getName()));
        return false;
    }//}}}

//    public static boolean update(String appID) {
//        //String query = "UPDATE hoge SET hoge = hoge WHERE hoge = hoge";
//        String query = String.format("SELECT * FROM PredictManager WHERE AppID = '%s'", appID);
//
//        Connection conn = null;
//        Statement stmt = null;
//        ResultSet rs = null;
//        try {
//            String uri = String.format("jdbc:sqlite:%s/sqlight.db", predictManagerRoot.toString());
//            conn = DriverManager.getConnection(uri);
//            stmt = conn.createStatement();
//            //stmt.executeUpdate(query);
//            rs = stmt.executeQuery(query);
//            //stmt.executeUpdate(query);
//            byte[] modelInfo = Base64Wrapper.decode(rs.getString("modelInfo"));
//            println_RED(new String(Hex.encodeHex(modelInfo)));
//        } catch (SQLException ex) {
//            return false;
//        } finally {
//            if (rs != null) try { rs.close(); } catch (SQLException ex) {}
//            if (stmt != null) try { stmt.close(); } catch (SQLException ex) {}
//            if (conn != null) try { conn.close(); } catch (SQLException ex) {}
//        }
//
//        return true;
//    }

    public static boolean case2_1() {//{{{
        clean();
        PredictManager predictManager = null;
        try {
            //
            Files.createDirectories(predictManagerRoot);
            TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
            String appID = deployInfo.getAppID();

            predictManager = new PredictManager(predictManagerRoot, appID);

            //
            float[][] sequenceData = {{0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f,
                0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f},
                {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f,
                0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f}};
            String groupLabel = "BSSID1";

            Double[] flattenedSequenceData = Tensor.toDoubleArrayFrom(sequenceData);
            assertNotEquals(null, flattenedSequenceData);
            int m = sequenceData.length;
            int n = sequenceData[0].length;

            TensorMap tensorMap = TensorMap.newInstance();
            tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(n));
            tensorMap.set(NNFedHLCRClient.TENSOR_SEQUENCE_DATA, Tensor.newTensor(TensorShape.createShape(m, n), flattenedSequenceData));
            tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));

            println_GREEN(String.format("[%s] Start", new Object(){}.getClass().getEnclosingMethod().getName()));
            PredictManager.PredictResult predictResult = predictManager.predict(tensorMap);

            if (predictResult.getStatus() == 3) {
                println_GREEN(String.format("[%s] The result was as expected.", new Object(){}.getClass().getEnclosingMethod().getName()));
                return true;
            }
        }
        catch (FLException | IOException ex) {
            println_RED(String.format("[%s] The result was not as expected.", new Object(){}.getClass().getEnclosingMethod().getName()));
            System.out.print(ORANGE);
            ex.printStackTrace();
            System.out.print(WHITE);
            return false;
        }
        finally {
            if (predictManager != null) {
                println_GREEN(String.format("[%s] finalize", new Object(){}.getClass().getEnclosingMethod().getName()));
                predictManager.finalize();
            }
        }
        println_RED(String.format("[%s] The result was not as expected.", new Object(){}.getClass().getEnclosingMethod().getName()));
        return false;
    }//}}}

    public static boolean case2_2() {//{{{
        clean();
        PredictManager predictManager = null;
        try {
            //
            Files.createDirectories(trainManagerRoot);
            Files.createDirectories(predictManagerRoot);

            DeployManager deployManager = new DeployManager(trainManagerRoot, predictManagerRoot);

            String FLID = "fl-p";
            String taskID = "task-p";
            TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
            Files.createDirectories(inputPath);
            createFilesForDeploy(inputPath, NNHLCRSamplePath);

            Path datFile = Paths.get(inputPath.toString(), Const.ALL_DATA_DAT_FILE_NAME);
            Path idxFile = Paths.get(inputPath.toString(), Const.ALL_DATA_IDX_FILE_NAME);
            DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
            try (BufferedReader br = Files.newBufferedReader(datFile)) {
                TensorMap tensorMap;
                tensorMap = TensorMap.fromJsonString(br.readLine());    // 1-line JSON object
                serializer.save(tensorMap);
            }
            DataMetadata data = serializer.getMetadata();

            deployManager.deploy(FLID, taskID, data, deployInfo, inputPath);

            //
            String appID = deployInfo.getAppID();

            predictManager = new PredictManager(predictManagerRoot, appID);

            //
/**/        float[][] sequenceData = null;
            String groupLabel = "BSSID1";

            TensorMap tensorMap = TensorMap.newInstance();
            tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));

            println_GREEN(String.format("[%s] Start", new Object(){}.getClass().getEnclosingMethod().getName()));
            PredictManager.PredictResult predictResult = predictManager.predict(tensorMap);

            if (predictResult.getStatus() == 1) {
                println_GREEN(String.format("[%s] The result was as expected.", new Object(){}.getClass().getEnclosingMethod().getName()));
                return true;
            }
        }
        catch (FLException | IOException ex) {
            println_GREEN(String.format("[%s] The result was as expected.", new Object(){}.getClass().getEnclosingMethod().getName()));
            System.out.print("[33m");
            ex.printStackTrace();
            System.out.print("[37m");
            return true;
        }
        finally {
            if (predictManager != null) {
                println_GREEN(String.format("[%s] finalize", new Object(){}.getClass().getEnclosingMethod().getName()));
                predictManager.finalize();
            }
        }
        println_RED(String.format("[%s] The result was not as expected.", new Object(){}.getClass().getEnclosingMethod().getName()));
        return false;
    }//}}}

    public static boolean case2_4() {//{{{
        clean();
        PredictManager predictManager = null;
        try {
            //
            Files.createDirectories(trainManagerRoot);
            Files.createDirectories(predictManagerRoot);

            DeployManager deployManager = new DeployManager(trainManagerRoot, predictManagerRoot);

            String FLID = "fl-p";
            String taskID = "task-p";
            TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
            Files.createDirectories(inputPath);
            createFilesForDeploy(inputPath, NNHLCRSamplePath);

            Path datFile = Paths.get(inputPath.toString(), Const.ALL_DATA_DAT_FILE_NAME);
            Path idxFile = Paths.get(inputPath.toString(), Const.ALL_DATA_IDX_FILE_NAME);
            DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
            try (BufferedReader br = Files.newBufferedReader(datFile)) {
                TensorMap tensorMap;
                tensorMap = TensorMap.fromJsonString(br.readLine());    // 1-line JSON object
                serializer.save(tensorMap);
            }
            DataMetadata data = serializer.getMetadata();

            deployManager.deploy(FLID, taskID, data, deployInfo, inputPath);

            //
            String appID = deployInfo.getAppID();

            predictManager = new PredictManager(predictManagerRoot, appID);
/**/        predictManager.finalize();

            //
            float[][] sequenceData = {{0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f,
                0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f},
                {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f,
                0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f}};
            String groupLabel = "BSSID1";

            Double[] flattenedSequenceData = Tensor.toDoubleArrayFrom(sequenceData);
            assertNotEquals(null, flattenedSequenceData);
            int m = sequenceData.length;
            int n = sequenceData[0].length;

            TensorMap tensorMap = TensorMap.newInstance();
            tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(n));
            tensorMap.set(NNFedHLCRClient.TENSOR_SEQUENCE_DATA, Tensor.newTensor(TensorShape.createShape(m, n), flattenedSequenceData));
            tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));

            println_GREEN(String.format("[%s] Start", new Object(){}.getClass().getEnclosingMethod().getName()));
            PredictManager.PredictResult predictResult = predictManager.predict(tensorMap);

            if (predictResult.getStatus() == 1) {
                println_GREEN(String.format("[%s] The result was as expected.", new Object(){}.getClass().getEnclosingMethod().getName()));
                return true;
            }
        }
        catch (FLException | IOException ex) {
            println_GREEN(String.format("[%s] The result was as expected.", new Object(){}.getClass().getEnclosingMethod().getName()));
            System.out.print("[33m");
            ex.printStackTrace();
            System.out.print("[37m");
            return true;
        }
        finally {
            if (predictManager != null) {
                println_GREEN(String.format("[%s] finalize", new Object(){}.getClass().getEnclosingMethod().getName()));
                predictManager.finalize();
            }
        }
        println_RED(String.format("[%s] The result was not as expected.", new Object(){}.getClass().getEnclosingMethod().getName()));
        return false;
    }//}}}

    public static void main(String[] args) {
        boolean success;
        for (int i = 0; i < LOOP_COUNT; i++) {
            // case1: public PredictManager(Path dirPath, String appID) throws FLException
    
            // case1-1: dirPath に存在しないパスを指定する
            success = case1_1();
            if (!success) break;
            // case1-2: {root}/sqlight.db を作成してから new する
            success = case1_2();
            if (!success) break;
            // case1-3: TaskInfo.PBDeployInfo の modeltype に 'foo' をセットして deploy してから PredictManager を new する
            // protobuf をいじるのは難しいので対象外
    
            // case2: public PredictResult predict(float[][] dataSequence, String groupLabel)
            // case2-1: deploy せずに predict する               return new PredictResult(3, Float.NaN);
            success = case2_1();
            if (!success) break;
            // case2-2: dataSequence を null にして predict する return new PredictResult(1, Float.NaN);
            success = case2_2();
            if (!success) break;
            // case2-3: 他のタスクが実行中、case2-2 と結果が同じになるのでテスト対象外
            // case2-4: finalize してから predict する           return new PredictResult(1, ret);
            success = case2_4();
            if (!success) break;
        }
    }
}

