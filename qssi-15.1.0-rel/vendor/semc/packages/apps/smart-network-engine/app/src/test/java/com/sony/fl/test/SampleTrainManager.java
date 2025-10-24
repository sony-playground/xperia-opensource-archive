package com.sony.fl.test;

//import static org.junit.Assert.assertEquals;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import com.sony.fl.TrainManager;

import com.sony.fl.TrainManager.EvaluationResult;
//import com.sony.fl.TrainManager.TrainResult;
import com.sony.fl.exception.FLException;
import com.sony.fl.pb.TaskInfo;
import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.DataSerializer;
import com.sony.fl.utils.Const;
import com.sony.fl.utils.CreatePBForTest;
import com.sony.fl.utils.PBChecker;
//import com.sony.fl.utils.PathChecker;

public class SampleTrainManager {

//  public static void setupForTrain(Path inputPath, Path NNHLCRSamplePath) throws IOException {
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
//      Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("Hyper_Param.dat"), 
//              inputPath.resolve("Hyper_Param.dat"));
//      Files.copy(NNHLCRSamplePath.resolve("data").resolve(TrainManager.TRAIN_DATA_FILE_NAME), 
//              inputPath.resolve(TrainManager.TRAIN_DATA_FILE_NAME));
//  }

    public static void setUpForEvaluation(Path inputPath, Path NNHLCRSamplePath) throws IOException {
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

    public static int[] loadDataY(Path filePath) throws IOException {
        String ansStr = readFile(filePath.toString());
        String[] strs = ansStr.split(System.getProperty("line.separator"));
        int[] ret = new int[64];
        for (int i=0;i<64;i++) ret[i] = Integer.valueOf(strs[i]);
        return ret;
    }

    public static float[] loadDataYPred(Path filePath) throws IOException {
        String ansStr = readFile(filePath.toString());
        String[] strs = ansStr.split(System.getProperty("line.separator"));
        float[] ret = new float[64];
        for (int i=0;i<64;i++) ret[i] = Float.valueOf(strs[i]);
        return ret;
    }

    public static void main(String[] args) {
        try {
            sample(args);
        }
        catch (IOException ex) {
            ex.printStackTrace();
            return;
        }
    }

    public static void sample(String[] args) throws IOException {
        Path root = Paths.get("src/test/resources/TrainManagerRoot");
        Path inputPath = Paths.get("src/test/resources/input");
        Path outputPath = Paths.get("src/test/resources/output");
        Path NNHLCRSamplePath = Paths.get("src/test/resources/NNHLCR");

        DataMetadata metaData;
        try {
            Path datFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_DAT_FILE_NAME);
            Path idxFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_IDX_FILE_NAME);
            DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
            metaData = serializer.getMetadata();
        }
        catch (FLException ex) {
            ex.printStackTrace();
            return;
        }

        try {
            Files.createDirectories(root);
            Files.createDirectories(inputPath);
            Files.createDirectories(outputPath);
        }
        catch (IOException ex) {
            ex.printStackTrace();
            return;
        }

        TrainManager trainManager;
        try {
            trainManager = new TrainManager(root);
        }
        catch (FLException ex) {
            ex.printStackTrace();
            return;
        }

        try {
//          setupForTrain(inputPath, NNHLCRSamplePath);
            setUpForEvaluation(inputPath, NNHLCRSamplePath);
        }
        catch (IOException ex) {
            ex.printStackTrace();
            return;
        }

        String FLID = "fl-SNE";
//      TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();
        TaskInfo.PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();

//      final int n_max = 50000;
        final int n_max = 2;
        for (int n = 0; n < n_max; n++) {
            System.out.println(String.format("[%03d]==================================================", n+1));

//          // train
//          String taskID = String.format("task-2_%d", n+1);
//          TrainResult trainResult = trainManager.train(
//                  FLID, taskID, trainInfo, inputPath, outputPath);
//
//          System.out.println(String.format("status: %d", trainResult.getStatus()));
//          System.out.println(String.format("check train result:%d", PBChecker.checkPBTrainResult(trainResult.getTrainResult(), trainInfo)));
//          System.out.println(String.format("has NNHLCRModel:%s", (trainResult.getTrainResult().hasNNHLCRModel() ? "True" : "False")));
//
//          Path backUpPath = root.resolve(FLID).resolve(taskID);
//          System.out.println(String.format("check folder path:%s", (PathChecker.checkFolderPath(backUpPath, true, true, true) ? "True" : "False")));

            // evaluation
            EvaluationResult evaluationResult = trainManager.evaluation(
                    FLID, metaData, evaluationInfo, inputPath, outputPath);

//          assertEquals(0, evaluationResult.getStatus());
//          assertEquals(0, PBChecker.checkPBEvaluationResult(evaluationResult.getEvaluationResult(), 
//                  evaluationInfo));
            System.out.println(String.format("status: %d", evaluationResult.getStatus()));
            System.out.println(String.format("check evaluation result:%d", PBChecker.checkPBEvaluationResult(evaluationResult.getEvaluationResult(), evaluationInfo)));

            String jni_output = readFile(outputPath.toString() + "/" + evaluationResult.getEvaluationResult().getEvaluationResultFileName());
            String[] rows = jni_output.split(System.getProperty("line.separator"));
            int N = Integer.valueOf(rows[0]);
            float[] predicted_label = loadDataYPred(NNHLCRSamplePath.resolve("predict").resolve("y_pred.csv"));
            int[] label = loadDataY(NNHLCRSamplePath.resolve("predict").resolve("y.csv"));
//          assertEquals(predicted_label.length, N);
            System.out.println(String.format("predicted_label.length: %d == %d", predicted_label.length, N));
            for (int i = 0; i < N; i++) {
                    String[] values = rows[i+1].split(" ");
                    int l = Integer.valueOf(values[0]);
                    float pl = Float.valueOf(values[1]);
//                  assertEquals(label[i], l);
                    System.out.println(String.format("label[%d]: %d == %d", i, label[i], l));
//                  assertEquals(predicted_label[i], pl, 1e-5);
                    System.out.println(String.format("predicted_label[%d]: %f == %f == %f", i, predicted_label[i], pl, 1e-5));
            }
        }
    }
}

