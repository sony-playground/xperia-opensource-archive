package com.sony.fl.test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.apache.commons.io.FileUtils;

import java.lang.reflect.InvocationTargetException;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.sony.fl.TrainManager;

import com.sony.fl.TrainManager.EvaluationResult;
import com.sony.fl.algorithm.LinearFedHLCRClient;
//import com.sony.fl.TrainManager.TrainResult;
import com.sony.fl.exception.FLException;
import com.sony.fl.pb.TaskInfo;
import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.Tensor;
import com.sony.fl.tensor.TensorMap;
import com.sony.fl.utils.Const;
import com.sony.fl.utils.CreatePBForTest;
import com.sony.fl.utils.DataMetadataUtil;
import com.sony.fl.utils.PBChecker;
//import com.sony.fl.utils.PathChecker;

public class TestLinearHLCR_EvaluationOnly {

    private static final int LOOP_COUNT;
    private static TensorMap result;
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

    public static void setUpForEvaluation(Path inputPath, Path LinearHLCRSamplePath) throws IOException {
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearHLCRGlobalWeight.json"),      inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel0.json"), inputPath.resolve("LinearRegressionGlobalModel0.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel1.json"), inputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel2.json"), inputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel3.json"), inputPath.resolve("LinearRegressionGlobalModel3.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel4.json"), inputPath.resolve("LinearRegressionGlobalModel4.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel5.json"), inputPath.resolve("LinearRegressionGlobalModel5.json"));

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

    public static double[] loadDataY(Path filePath) throws IOException {
        String ansStr = readFile(filePath.toString());
        JsonNode jsonNode = new ObjectMapper().readTree(ansStr);
        int size = jsonNode.get("y").size();
        double[] ret = new double[size];
        for (int i=0;i<size;i++) {
            ret[i] = jsonNode.get("y").get(i).doubleValue();
        }
        return ret;
    }

    public static double[] loadDataYPred(Path filePath) throws IOException {
        String ansStr = readFile(filePath.toString());
        JsonNode jsonNode = new ObjectMapper().readTree(ansStr);
        int size = jsonNode.get("y_pred").size();
        double[] ret = new double[size];
        for (int i=0;i<size;i++) {
            ret[i] = jsonNode.get("y_pred").get(i).doubleValue();
        }
        return ret;
    }

    public static void main(String[] args) {
        Path root = Paths.get("src/test/resources/TrainManagerRoot");
        Path inputPath = Paths.get("src/test/resources/input");
        Path outputPath = Paths.get("src/test/resources/output");
        Path LinearHLCRSamplePath = Paths.get("src/test/resources/LinearHLCR");

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
            setUpForEvaluation(inputPath, LinearHLCRSamplePath);
        }
        catch (IOException ex) {
            ex.printStackTrace();
            return;
        }

        String FLID = "fl-SNE";
        TaskInfo.PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForLinearHLCRForSNE();

        for (int i = 1; i <= LOOP_COUNT; i++) {
            System.out.println(String.format("[%05d]==================================================", i));

            // evaluation
            EvaluationResult evaluationResult = trainManager.evaluation(
                    FLID, metaData, evaluationInfo, inputPath, outputPath);

            System.out.println(String.format("status: %d", evaluationResult.getStatus()));
            System.out.println(String.format("check evaluation result:%d", PBChecker.checkPBEvaluationResult(evaluationResult.getEvaluationResult(), evaluationInfo)));
            assertEquals(0, evaluationResult.getStatus());
            assertEquals(0, PBChecker.checkPBEvaluationResult(evaluationResult.getEvaluationResult(), evaluationInfo));

            String[] rows;
            int N;
            double[] predicted_label;
            double[] label;
            try {
                String jni_output = readFile(outputPath.toString() + "/" + evaluationResult.getEvaluationResult().getEvaluationResultFileName());
                rows = jni_output.split(System.getProperty("line.separator"));
                N = Integer.valueOf(rows.length);
                predicted_label = loadDataYPred(LinearHLCRSamplePath.resolve("SNE").resolve("predict_result_64.json"));
                label = loadDataY(LinearHLCRSamplePath.resolve("SNE").resolve("label_result_64.json"));
            }
            catch (IOException ex) {
                ex.printStackTrace();
                return;
            }
            System.out.println(String.format("predicted_label.length: %d == %d", predicted_label.length, N));
            assertEquals(predicted_label.length, N);

            for (int j = 0; j < N; j++) {
                result = TensorMap.fromJsonString(rows[j]);
                Tensor<Double> resultPredictedLabel = result.get(LinearFedHLCRClient.TENSOR_Y_PRED);
                Tensor<Double> resultLabel = result.get(LinearFedHLCRClient.TENSOR_Y);

                assertNotNull(resultPredictedLabel);
                assertNotNull(resultLabel);
                assertTrue(resultPredictedLabel.isScalar());
                assertTrue(resultLabel.isScalar());

                Double l = resultLabel.getValue();
                Double pl = resultPredictedLabel.getValue();
                System.out.println(String.format("label[%d]: %f == %f", j, label[j], l));
                assertEquals(label[j], l.doubleValue(), 0.0);
                System.out.println(String.format("predicted_label[%d]: %f == %f == %f", j, predicted_label[j], pl, 1e-5));
                assertEquals(predicted_label[j], pl, 1e-5);
            }

            try {
                FileUtils.cleanDirectory(outputPath.toFile());
            }
            catch (IOException ex) {
                ex.printStackTrace();
                return;
            }
        }
    }
}

