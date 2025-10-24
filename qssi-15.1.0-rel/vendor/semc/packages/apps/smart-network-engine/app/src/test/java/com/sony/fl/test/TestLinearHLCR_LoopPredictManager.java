package com.sony.fl.test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import java.sql.Timestamp;
import java.text.SimpleDateFormat;

import java.lang.reflect.InvocationTargetException;

import com.sony.fl.algorithm.LinearFedHLCRClient;
import com.sony.fl.PredictManager;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.sony.fl.DeployManager;

import com.sony.fl.exception.FLException;
import com.sony.fl.pb.TaskInfo;
import com.sony.fl.utils.Const;
import com.sony.fl.utils.CreatePBForTest;
import com.sony.fl.utils.DataMetadataUtil;

import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.Tensor;
import com.sony.fl.tensor.TensorMap;

import org.apache.commons.io.file.PathUtils;

public class TestLinearHLCR_LoopPredictManager {

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
        Files.copy(LinearHLCRSamplePath.resolve("python_test_case").resolve("global_weight.json"), inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.copy(LinearHLCRSamplePath.resolve("python_test_case").resolve("model_S_0.json"),     inputPath.resolve("LinearRegressionGlobalModel0.json"));
        Files.copy(LinearHLCRSamplePath.resolve("python_test_case").resolve("model_S_1.json"),     inputPath.resolve("LinearRegressionGlobalModel1.json"));

        Files.copy(LinearHLCRSamplePath.resolve("back_up").resolve("LinearHLCRUpdateHyperParams.json"), inputPath.resolve("LinearHLCRUpdateHyperParams.json"));

        Files.copy(LinearHLCRSamplePath.resolve("python_test_case").resolve("data_S.jsonl"), inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.copy(LinearHLCRSamplePath.resolve("python_test_case").resolve("data_S.txt"), inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
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

    public static float[][] loadDataX(Path filePath) throws IOException {
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

    public static double[] loadDataY(Path filePath) throws IOException {
        String ansStr = readFile(filePath.toString());
        JsonNode jsonNode = new ObjectMapper().readTree(ansStr);
        int size = jsonNode.get("y_pred").size();
        double[] ret = new double[size];
        for (int i=0;i<size;i++) {
            ret[i] = jsonNode.get("y_pred").get(i).doubleValue();
        }
        return ret;
    }

    private static void outputCsv(String outputFile, String timeStamp, String... args) {
        FileWriter fw = null;
        PrintWriter pw = null;
        try {
            fw = new FileWriter(outputFile, true);
            pw = new PrintWriter(new BufferedWriter(fw));
            pw.println(timeStamp + "," + String.join(",", args));
        }
        catch (IOException ex) {
            ex.printStackTrace();
        }
        finally {
            if ( pw != null) {
                pw.close();
            }
        }
    }

    private static void outputCsv(String outputFile, String timeStamp, int loopCount, int fileCount) {
        outputCsv(outputFile, timeStamp, String.valueOf(loopCount), String.valueOf(fileCount));
    }

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

        DeployManager deployManager;
        try {
            deployManager = new DeployManager(trainManagerRoot, predictManagerRoot);
        }
        catch (FLException ex) {
            ex.printStackTrace();
            return;
        }

        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForLinearHLCRForSNE_python_test_case();
        String appID = deployInfo.getAppID();

        String FLID = "fl-p";
        String taskID = "task-p";

        deployManager.deploy(FLID, taskID, data, deployInfo, inputPath);

        PredictManager predictManager;
        try {
            predictManager = new PredictManager(predictManagerRoot, appID);
            int calibrate_result = predictManager.calibrate(data);
            assertEquals(0, calibrate_result);
        }
        catch (FLException ex) {
            ex.printStackTrace();
            return;
        }

        {
            double[] label;
            try {
                label = loadDataY(LinearHLCRSamplePath.resolve("python_test_case").resolve("predict_result.json"));
            }
            catch (IOException ex) {
                ex.printStackTrace();
                return;
            }

            Timestamp timestamp = new Timestamp(System.currentTimeMillis());
            SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddHHmmssSSS");
            String ts = sdf.format(timestamp);
            String CSV_FILENAME = "src/test/logs/test_loop_predict_" + ts + ".csv";
            outputCsv(CSV_FILENAME, "timestamp", "loopCount", "fileCount");

            int INNER_LOOP = 64;
            int DATA_USE_MAX = 8;
            int count = 0;
            for (int l = 0;l < LOOP_COUNT;l++) {
                TensorMap tensorMap;
                for (int k=0;k<INNER_LOOP/DATA_USE_MAX;k++) {
                    try (BufferedReader br = Files.newBufferedReader(LinearHLCRSamplePath.resolve("python_test_case/data_S.jsonl"))) {
                        for (int i=0;i<DATA_USE_MAX;i++) {
                            System.out.println(String.format("[%05d][%02d]==================================================", l+1, (k*8)+(i+1)));
                            count++;
                            // timestamp
                            timestamp = new Timestamp(System.currentTimeMillis());
                            sdf = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss.SSS");
                            ts = sdf.format(timestamp);

                            tensorMap = TensorMap.fromJsonString(br.readLine());

                            PredictManager.PredictResult predictResult = predictManager.predict(tensorMap);
                            outputCsv(CSV_FILENAME, ts, count, i);
                            assertEquals(0, predictResult.getStatus());

                            System.out.println(String.format("[%02d] status: %d", i, predictResult.getStatus()));
                            TensorMap result = predictResult.getResult();
                            if (result != null) {
                                Tensor<Double> resultLabel = result.get(LinearFedHLCRClient.TENSOR_Y_PRED);
                                assertNotNull(resultLabel);
                                assertTrue(resultLabel.isScalar());
                                Double predictLabel = resultLabel.getValue();
                                System.out.println(String.format("[%02d] predict label: %f", i, predictLabel));
                                System.out.println(String.format("[%02d] label = %f, predicted label = %f", i, label[i], predictLabel));
                                // assertEquals(label[i], predictLabel, 0.0);
                                assertEquals(label[i], predictLabel, 1e-5);
                            }
                        }
                        int calibrate_result = predictManager.calibrate(data);
                        assertEquals(0, calibrate_result);
                    }
                    catch (IOException ex) {
                        ex.printStackTrace();
                        break;
                    }
                }
            }
        }

        try {
            PathUtils.deleteDirectory(predictManagerRoot);
            PathUtils.deleteDirectory(trainManagerRoot);
            PathUtils.deleteDirectory(inputPath);
        }
        catch (IOException ex) {
            ex.printStackTrace();
            return;
        }
    }
}

