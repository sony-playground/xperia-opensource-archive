package com.sony.fl.test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;

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

import com.sony.fl.PredictManager;
import com.sony.fl.DeployManager;
import com.sony.fl.TrainManager;

import com.sony.fl.TrainManager.EvaluationResult;
import com.sony.fl.TrainManager.TrainResult;

import com.sony.fl.algorithm.NNFedHLCRClient;
import com.sony.fl.exception.FLException;
import com.sony.fl.pb.TaskInfo;
import com.sony.fl.pb.TaskInfo.PBEvaluationInfo;
import com.sony.fl.utils.Const;
import com.sony.fl.utils.CreatePBForTest;
import com.sony.fl.utils.PBChecker;
import com.sony.fl.utils.PathChecker;

import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.DataSerializer;
import com.sony.fl.tensor.Tensor;
import com.sony.fl.tensor.TensorMap;
import com.sony.fl.tensor.TensorShape;

import org.apache.commons.io.file.PathUtils;

public class TestMixManager {

    private static final int DEPLOY_LOOP_COUNT = 3;
    private static final int TRAIN_LOOP_COUNT = 500;

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
    }

    public static void setupForTrain(Path inputPath, Path NNHLCRSamplePath) throws IOException {
//        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), 
//                inputPath.resolve("HLCR_Param.dat"));
//        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), 
//                    inputPath.resolve("cluster1.protobuf"));
//        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), 
//                inputPath.resolve("cluster2.protobuf"));
//        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), 
//                inputPath.resolve("graph.nntxt"));
//        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), 
//                inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("Hyper_Param.dat"), 
                inputPath.resolve("Hyper_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_DAT_FILE_NAME), 
                inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_IDX_FILE_NAME), 
                inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
    }

    public static void setUpForEvaluation(Path inputPath, Path NNHLCRSamplePath) throws IOException {
//      Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), 
//              inputPath.resolve("HLCR_Param.dat"));
//      Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), 
//              inputPath.resolve("cluster1.protobuf"));
//      Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), 
//              inputPath.resolve("cluster2.protobuf"));
//      Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), 
//              inputPath.resolve("graph.nntxt"));
//      Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), 
//              inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_DAT_FILE_NAME), 
                inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_IDX_FILE_NAME), 
                inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
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

    public static void main(String[] args) throws FLException {
        Path trainManagerRoot = Paths.get("src/test/resources/TrainManagerRoot");
        Path predictManagerRoot = Paths.get("src/test/resources/PredictManagerRoot");
        Path inputPath = Paths.get("src/test/resources/input");
        Path outputPath = Paths.get("src/test/resources/output");
        Path NNHLCRSamplePath = Paths.get("src/test/resources/NNHLCR");

        try {
            Files.createDirectories(trainManagerRoot);
            Files.createDirectories(predictManagerRoot);
            Files.createDirectories(inputPath);
            Files.createDirectories(outputPath);

            createFilesForDeploy(inputPath, NNHLCRSamplePath);
            setupForTrain(inputPath, NNHLCRSamplePath);
            setUpForEvaluation(inputPath, NNHLCRSamplePath);
        }
        catch (IOException ex) {
            ex.printStackTrace();
            return;
        }

        DataMetadata data;
        try {
            Path datFile = Paths.get(inputPath.toString(), Const.ALL_DATA_DAT_FILE_NAME);
            Path idxFile = Paths.get(inputPath.toString(), Const.ALL_DATA_IDX_FILE_NAME);
            DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
            try (BufferedReader br = Files.newBufferedReader(datFile)) {
                TensorMap tensorMap = TensorMap.fromJsonString(br.readLine());    // 1-line JSON object
                serializer.save(tensorMap);
            }
            data = serializer.getMetadata();
        }
        catch (IOException|FLException ex) {
            ex.printStackTrace();
            return;
        }

        DataMetadata trainData;
        try {
            Path datFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_DAT_FILE_NAME);
            Path idxFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_IDX_FILE_NAME);
            DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
            trainData= serializer.getMetadata();
        }
        catch (FLException ex) {
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
        // Deploy
        TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();

        String FLID = "fl-p";
        String taskID = "task-p";

        deployManager.deploy(FLID, taskID, data, deployInfo, inputPath);

        String appID = deployInfo.getAppID();
        PredictManager predictManager;
        try {
            predictManager = new PredictManager(predictManagerRoot, appID);
        }
        catch (FLException ex) {
            ex.printStackTrace();
            return;
        }

        TrainManager trainManager;
        try {
            trainManager = new TrainManager(trainManagerRoot);
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
            String CSV_FILENAME = "/var/fl/test_loop_predict_" + ts + ".csv";
            outputCsv(CSV_FILENAME, "timestamp", "loopCount", "fileCount");

            int count = 0;
            for (int l = 0;l < DEPLOY_LOOP_COUNT;l++) {
                count++;
                // timestamp
                timestamp = new Timestamp(System.currentTimeMillis());
                sdf = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss.SSS");
                ts = sdf.format(timestamp);

                for (int k = 0;k < TRAIN_LOOP_COUNT;k++) {
                    { // Predict
                        float[][] sequenceData;
                        int i = k % 10;
                        System.out.println("============[i:"+i+"]============");
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

                        PredictManager.PredictResult predictResult = 
                                predictManager.predict(tensorMap);
                        assertEquals(0, predictResult.getStatus());

                        System.out.println(String.format("[%02d] status: %d", i, predictResult.getStatus()));
                        TensorMap result = predictResult.getResult();
                        if (result != null) {
                            Double tensorLabel = (Double)result.get("label").getValue();
                            String tensorResult = (String)result.get("result").getValue();
                            System.out.println(String.format("[%02d] predict label: %f", i, tensorLabel));
                            System.out.println(String.format("[%02d] predict result: %s", i, tensorResult));
                            System.out.println(String.format("[%02d] label = %f, predicted label = %f", i, label[i], tensorLabel));
                            assertEquals(label[i], tensorLabel, 1e-5);
                        }
                    }

                    for (int m = 0;m < 2;m++) {
                        { // Train Evaluation
                            FLID = "fl-" + (m%2==0?"A":"B") + "-" + l;
                            taskID = "task-" + k;
                            { // Train
                                TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();        
                                TrainResult trainResult = trainManager.train(
                                        FLID, taskID, trainData, trainInfo, inputPath, outputPath);

                                assertEquals(0, trainResult.getStatus());
                                assertEquals(0, PBChecker.checkPBTrainResult(trainResult.getTrainResult(), trainInfo));
                                assertEquals(true, trainResult.getTrainResult().hasNNHLCRModel());

                                //System.out.println(String.format("status: %d", trainResult.getStatus()));
                                //System.out.println(String.format("check train result:%d", PBChecker.checkPBTrainResult(trainResult.getTrainResult(), trainInfo)));
                                //System.out.println(String.format("has NNHLCRModel:%s", (trainResult.getTrainResult().hasNNHLCRModel() ? "True" : "False")));
                                Path backUpPath = trainManagerRoot.resolve(FLID).resolve(taskID);
                                assertEquals(true, PathChecker.checkFolderPath(backUpPath, true, true, true));
                                //System.out.println(String.format("check folder path:%s", (PathChecker.checkFolderPath(backUpPath, true, true, true) ? "True" : "False")));
                            }

                            { // Evaluation
                                PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();        
                                EvaluationResult evaluationResult = trainManager.evaluation(
                                        FLID, trainData, evaluationInfo, inputPath, outputPath);
                                System.out.println(String.format("status: %d", evaluationResult.getStatus()));
                                System.out.println(String.format("check evaluation result:%d", PBChecker.checkPBEvaluationResult(evaluationResult.getEvaluationResult(), evaluationInfo)));
                            }

                            // OUTPUT
                            //outputCsv(CSV_FILENAME, ts, count, i);
                        }
                    }
                }

                deployManager.deploy(FLID, taskID, data, deployInfo, inputPath);
            }
        }

        try {
            PathUtils.deleteDirectory(predictManagerRoot);
            PathUtils.deleteDirectory(trainManagerRoot);
            PathUtils.deleteDirectory(inputPath);
            PathUtils.deleteDirectory(outputPath);
        }
        catch (IOException ex) {
            ex.printStackTrace();
            return;
        }
    }
}
