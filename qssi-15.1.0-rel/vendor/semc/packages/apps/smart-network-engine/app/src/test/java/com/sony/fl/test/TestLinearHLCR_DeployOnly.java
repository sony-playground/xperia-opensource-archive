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

import com.sony.fl.algorithm.LinearFedHLCRClient;
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

public class TestLinearHLCR_DeployOnly {

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

    public static void createFilesForDeploy(Path inputPath, Path LinearHLCRSamplePath) throws IOException {
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearHLCRGlobalWeight.json"),      inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel0.json"), inputPath.resolve("LinearRegressionGlobalModel0.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel1.json"), inputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel2.json"), inputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel3.json"), inputPath.resolve("LinearRegressionGlobalModel3.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel4.json"), inputPath.resolve("LinearRegressionGlobalModel4.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel5.json"), inputPath.resolve("LinearRegressionGlobalModel5.json"));

        Files.copy(LinearHLCRSamplePath.resolve("back_up").resolve("LinearHLCRUpdateHyperParams.json"), inputPath.resolve("LinearHLCRUpdateHyperParams.json"));

        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("Data_64.jsonl"), inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("data_64.txt"), inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
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
        Path predictManagerRoot = Paths.get("src/test/resources/PredictManagerRoot");
        Path inputPath = Paths.get("src/test/resources/input");
        Path LinearHLCRSamplePath = Paths.get("src/test/resources/LinearHLCR");

        try {
            Files.createDirectories(trainManagerRoot);
            Files.createDirectories(predictManagerRoot);
            Files.createDirectories(inputPath);

            createFilesForDeploy(inputPath, LinearHLCRSamplePath);
        }
        catch (IOException ex) {
            ex.printStackTrace();
            return;
        }

        DataMetadata data;
        try {
            Path datFile = Paths.get(inputPath.toString(), Const.TEST_DATA_DAT_FILE_NAME);
            Path idxFile = Paths.get(inputPath.toString(), Const.TEST_DATA_IDX_FILE_NAME);
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

        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForLinearHLCRForSNE();
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
//                createFilesForDeploy(inputPath, LinearHLCRSamplePath);
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

            Path clusterMapFile = predictManagerRoot.resolve(appID).resolve(taskID).resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME);
//          String old_cm;
//          String ans;
//          try {
//              old_cm = readFile(clusterMapFile.toString());
//              ans = readFile("src/test/resources/LinearHLCR/calibrate/ClusterMapAns.dat");
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

