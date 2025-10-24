package com.sony.fl.test;

import static org.junit.Assert.assertEquals;

import java.io.BufferedReader;
//import java.io.BufferedWriter;
import java.io.FileReader;
//import java.io.FileWriter;
//import java.io.PrintWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;

import java.lang.reflect.InvocationTargetException;

//import java.sql.Timestamp;
//import java.text.SimpleDateFormat;

import com.sony.fl.algorithm.NNFedHLCRClient;
import com.sony.fl.PredictManager;
import com.sony.fl.DeployManager;

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

//import org.apache.commons.io.file.PathUtils;

public class TestNNHLCR_DeployOnly {

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

    public static void createFilesForDeploy(Path inputPath, Path NNHLCRSamplePath) throws IOException {
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
    }

    public static String readFile(String path) throws IOException {
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

//    private static void outputCsv(String outputFile, String timeStamp, String... args) {
//        FileWriter fw = null;
//        PrintWriter pw = null;
//        try {
//            fw = new FileWriter(outputFile, true);
//            pw = new PrintWriter(new BufferedWriter(fw));
//            pw.println(timeStamp + "," + String.join(",", args));
//        }
//        catch (IOException ex) {
//            ex.printStackTrace();
//        }
//        finally {
//            if ( pw != null) {
//                pw.close();
//            }
//        }
//    }

//    private static void outputCsv(String outputFile, String timeStamp, int loopCount, int fileCount) {
//        outputCsv(outputFile, timeStamp, String.valueOf(loopCount), String.valueOf(fileCount));
//    }


    public static void main(String[] args) {
        Path trainManagerRoot = Paths.get("src/test/resources/TrainManagerRoot");
        Path predictManagerRoot = Paths.get("src/test/resources2/PredictManagerRoot");
        Path inputPath = Paths.get("src/test/resources/input");
        Path NNHLCRSamplePath = Paths.get("src/test/resources/NNHLCR");

        try {
            Files.createDirectories(trainManagerRoot);
            Files.createDirectories(predictManagerRoot);
            Files.createDirectories(inputPath);

            createFilesForDeploy(inputPath, NNHLCRSamplePath);
        }
        catch (IOException ex) {
            ex.printStackTrace();
            return;
        }

        DataMetadata data;
        try {
            Path datFile = Paths.get(inputPath.toString(), Const.ALL_DATA_DAT_FILE_NAME);
            Path idxFile = Paths.get(inputPath.toString(), Const.ALL_DATA_IDX_FILE_NAME);
            data = DataMetadataUtil.newInstance();
            DataMetadataUtil.set(data, "tensor_map_file", datFile.toString());
            DataMetadataUtil.set(data, "tensor_map_index_file", idxFile.toString());
            DataMetadataUtil.set(data, "save_result", "success");
        }
        catch (NoSuchMethodException|InstantiationException|IllegalAccessException|InvocationTargetException ex) {
            ex.printStackTrace();
            return;
        }

        final String FLID = "fl-c";

        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        final String appID = deployInfo.getAppID();

        DeployManager deployManager;
        try {
            deployManager = new DeployManager(trainManagerRoot, predictManagerRoot);
        }
        catch (FLException ex) {
            ex.printStackTrace();
            return;
        }

        int rcd;
        for (int i = 1; i <= LOOP_COUNT; i++) {
            System.out.println(String.format("[%05d]==================================================", i));
//            try {
//                createFilesForDeploy(inputPath, NNHLCRSamplePath);
//            }
//            catch (IOException ex) {
//                ex.printStackTrace();
//                return;
//            }
            // ######
            // #     #  ######  #####   #        ####    #   #
            // #     #  #       #    #  #       #    #    # #
            // #     #  #####   #    #  #       #    #     #
            // #     #  #       #####   #       #    #     #
            // #     #  #       #       #       #    #     #
            // ######   ######  #       ######   ####      #
            String taskID = String.format("task-c-%05d", i);
            rcd = deployManager.deploy(FLID, taskID, data, deployInfo, inputPath);
            assertEquals(0, rcd);

            Path clusterMapFile = predictManagerRoot.resolve(appID).resolve(taskID).resolve(NNFedHLCRClient.CLUSTER_MAP_FILE_NAME);
//          String old_cm;
//          String ans;
//          try {
//              old_cm = readFile(clusterMapFile.toString());
//              ans = readFile("src/test/resources/NNHLCR/calibrate/ClusterMapAns.dat");
//          }
//          catch (IOException ex) {
//              ex.printStackTrace();
//              return;
//          }
//          assertEquals(old_cm, ans);
            assertEquals(true, Files.exists(clusterMapFile));
        }
    }
}

