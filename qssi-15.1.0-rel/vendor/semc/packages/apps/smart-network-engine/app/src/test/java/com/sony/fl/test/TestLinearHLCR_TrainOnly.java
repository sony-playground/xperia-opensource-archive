package com.sony.fl.test;

import static org.junit.Assert.assertEquals;

import java.io.IOException;
import java.nio.file.Files;
import static java.nio.file.StandardCopyOption.REPLACE_EXISTING;
import java.nio.file.Path;
import java.nio.file.Paths;

import java.lang.reflect.InvocationTargetException;

import com.sony.fl.TrainManager;

import com.sony.fl.TrainManager.TrainResult;
import com.sony.fl.exception.FLException;
import com.sony.fl.pb.TaskInfo;
import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.utils.Const;
import com.sony.fl.utils.CreatePBForTest;
import com.sony.fl.utils.DataMetadataUtil;
import com.sony.fl.utils.PBChecker;
import com.sony.fl.utils.PathChecker;

public class TestLinearHLCR_TrainOnly {

    public static void setupForTrain(Path inputPath, Path LinearHLCRSamplePath) throws IOException {
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearHLCRGlobalWeight.json"),      inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel0.json"), inputPath.resolve("LinearRegressionGlobalModel0.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel1.json"), inputPath.resolve("LinearRegressionGlobalModel1.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel2.json"), inputPath.resolve("LinearRegressionGlobalModel2.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel3.json"), inputPath.resolve("LinearRegressionGlobalModel3.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel4.json"), inputPath.resolve("LinearRegressionGlobalModel4.json"));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("LinearRegressionGlobalModel5.json"), inputPath.resolve("LinearRegressionGlobalModel5.json"));

        Files.copy(LinearHLCRSamplePath.resolve("back_up").resolve("LinearHLCRTrainHyperParams.json"), inputPath.resolve("LinearHLCRTrainHyperParams.json"));

        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("Data_64.jsonl"), inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.copy(LinearHLCRSamplePath.resolve("SNE").resolve("data_64.txt"), inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
    }

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

    public static void main(String[] args) throws FLException {
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
            setupForTrain(inputPath, LinearHLCRSamplePath);
        }
        catch (IOException ex) {
            ex.printStackTrace();
            return;
        }
        String[] FLIDs = new String[] { "FLa", "FLb", "FLc" };
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForLinearHLCRForSNE();
        for (int itr = 1; itr <= LOOP_COUNT; itr++) {
            String FLID = FLIDs[itr%3];
            System.out.println(String.format("[%05d] FLID[%s] ========================================", itr, FLID));
            String taskID = "FL_" + itr;
            TrainResult trainResult = trainManager.train(
                    FLID, taskID, metaData, trainInfo, inputPath, outputPath);
            assertEquals(0, trainResult.getStatus());
            assertEquals(0, PBChecker.checkPBTrainResult(trainResult.getTrainResult(), trainInfo));
            assertEquals(true, trainResult.getTrainResult().hasLinearHLCRLocalModel());
            Path backUpPath = root.resolve(FLID).resolve(taskID);
            assertEquals(true, PathChecker.checkFolderPath(backUpPath, true, true, true));
        }
    }
}

