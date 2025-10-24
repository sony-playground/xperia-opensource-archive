package com.sony.fl.test;

import static org.junit.Assert.assertEquals;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import java.lang.reflect.InvocationTargetException;

import com.sony.fl.TrainManager;

import com.sony.fl.TrainManager.EvaluationResult;
//import com.sony.fl.TrainManager.TrainResult;
import com.sony.fl.exception.FLException;
import com.sony.fl.pb.TaskInfo;
import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.utils.Const;
import com.sony.fl.utils.CreatePBForTest;
import com.sony.fl.utils.DataMetadataUtil;
import com.sony.fl.utils.PBChecker;
//import com.sony.fl.utils.PathChecker;

public class TestNNHLCR_EvaluationOnly {

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
        Path root = Paths.get("src/test/resources/TrainManagerRoot");
        Path inputPath = Paths.get("src/test/resources/input");
        Path outputPath = Paths.get("src/test/resources/output");
        Path NNHLCRSamplePath = Paths.get("src/test/resources/NNHLCR");

        try {
            Files.createDirectories(root);
            Files.createDirectories(inputPath);
            Files.createDirectories(outputPath);
        }
        catch (IOException ex) {
            ex.printStackTrace();
            return;
        }

        DataMetadata metaData;
        try {
            Path datFile = Paths.get(inputPath.toString(), Const.TEST_DATA_DAT_FILE_NAME);
            Path idxFile = Paths.get(inputPath.toString(), Const.TEST_DATA_IDX_FILE_NAME);
            metaData = DataMetadataUtil.newInstance();
            DataMetadataUtil.set(metaData, "tensor_map_file", datFile.toString());
            DataMetadataUtil.set(metaData, "tensor_map_index_file", idxFile.toString());
            DataMetadataUtil.set(metaData, "save_result", "success");
        }
        catch (NoSuchMethodException|InstantiationException|IllegalAccessException|InvocationTargetException ex) {
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

        for (int i = 1; i <= LOOP_COUNT; i++) {
            System.out.println(String.format("[%05d]==================================================", i));

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

            System.out.println(String.format("status: %d", evaluationResult.getStatus()));
            System.out.println(String.format("check evaluation result:%d", PBChecker.checkPBEvaluationResult(evaluationResult.getEvaluationResult(), evaluationInfo)));
            assertEquals(0, evaluationResult.getStatus());
            assertEquals(0, PBChecker.checkPBEvaluationResult(evaluationResult.getEvaluationResult(), evaluationInfo));

            String[] rows;
            int N;
            float[] predicted_label;
            int[] label;
            try {
                String jni_output = readFile(outputPath.toString() + "/" + evaluationResult.getEvaluationResult().getEvaluationResultFileName());
                rows = jni_output.split(System.getProperty("line.separator"));
                N = Integer.valueOf(rows[0]);
                predicted_label = loadDataYPred(NNHLCRSamplePath.resolve("predict").resolve("y_pred.csv"));
                label = loadDataY(NNHLCRSamplePath.resolve("predict").resolve("y.csv"));
            }
            catch (IOException ex) {
                ex.printStackTrace();
                return;
            }
            System.out.println(String.format("predicted_label.length: %d == %d", predicted_label.length, N));
            assertEquals(predicted_label.length, N);

            for (int j = 0; j < N; j++) {
                    String[] values = rows[j+1].split(" ");
                    int l = Integer.valueOf(values[0]);
                    float pl = Float.valueOf(values[1]);
                    System.out.println(String.format("label[%d]: %d == %d", j, label[j], l));
                    assertEquals(label[j], l);
                    System.out.println(String.format("predicted_label[%d]: %f == %f == %f", j, predicted_label[j], pl, 1e-5));
                    assertEquals(predicted_label[j], pl, 1e-5);
            }
        }
    }
}

