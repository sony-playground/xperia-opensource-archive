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

import com.sony.fl.algorithm.NNFedHLCRClient;
import com.sony.fl.PredictManager;
import com.sony.fl.DeployManager;

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

public class TestNNHLCR_LoopPredictManager {

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

    public static float[] loadDataY(Path filePath) throws IOException {
        String ansStr = readFile(filePath.toString());
        String[] strs = ansStr.split(System.getProperty("line.separator"));
        float[] ret = new float[64];
        for (int i=0;i<64;i++) ret[i] = Float.valueOf(strs[i]);
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

        DeployManager deployManager;
        try {
            deployManager = new DeployManager(trainManagerRoot, predictManagerRoot);
        }
        catch (FLException ex) {
            ex.printStackTrace();
            return;
        }

        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        String appID = deployInfo.getAppID();

        String FLID = "fl-p";
        String taskID = "task-p";

        deployManager.deploy(FLID, taskID, data, deployInfo, inputPath);

        PredictManager predictManager;
        try {
            predictManager = new PredictManager(predictManagerRoot, appID);
        }
        catch (FLException ex) {
            ex.printStackTrace();
            return;
        }

        {
            String groupLabel = "BSSID1";

            float[] label;
            try {
                label = loadDataY(NNHLCRSamplePath.resolve("predict").resolve("y_pred.csv"));
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

            int count = 0;
            for (int l = 0;l < LOOP_COUNT;l++) {
                for (int i = 0;i < 64;i++) {
                    System.out.println(String.format("[%05d][%02d]==================================================", l+1, i+1));
                    count++;
                    // timestamp
                    timestamp = new Timestamp(System.currentTimeMillis());
                    sdf = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss.SSS");
                    ts = sdf.format(timestamp);

                    float[][] sequenceData;
                    try {
                        sequenceData = loadDataX(NNHLCRSamplePath.resolve("predict").resolve("x_"+ i +".csv"));
                    }
                    catch (IOException ex) {
                        ex.printStackTrace();
                        break;
                    }

                    Double[] flattenedSequenceData = Tensor.toDoubleArrayFrom(sequenceData);
                    assertNotEquals(null, flattenedSequenceData);
                    int m = sequenceData.length;
                    int n = sequenceData[0].length;

                    TensorMap tensorMap = TensorMap.newInstance();
                    tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(n));
                    tensorMap.set(NNFedHLCRClient.TENSOR_SEQUENCE_DATA, Tensor.newTensor(TensorShape.createShape(m, n), flattenedSequenceData));
                    tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));

                    PredictManager.PredictResult predictResult = predictManager.predict(tensorMap);
                    outputCsv(CSV_FILENAME, ts, count, i);
                    assertEquals(0, predictResult.getStatus());

                    System.out.println(String.format("[%02d] status: %d", i, predictResult.getStatus()));
                    TensorMap result = predictResult.getResult();
                    if (result != null) {
                        Tensor resultLabel = result.get(NNFedHLCRClient.TENSOR_Y_PRED);
                        assertNotNull(resultLabel);
                        assertTrue(resultLabel.isScalar());
                        Double predictLabel = (Double)resultLabel.getValue();
                        System.out.println(String.format("[%02d] predict label: %f", i, predictLabel));
                        System.out.println(String.format("[%02d] label = %f, predicted label = %f", i, label[i], predictLabel));
                        assertEquals(label[i], predictLabel, 1e-5);
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

