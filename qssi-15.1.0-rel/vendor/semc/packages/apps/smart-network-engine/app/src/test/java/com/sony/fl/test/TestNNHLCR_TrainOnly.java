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

public class TestNNHLCR_TrainOnly {

    public static void setupForTrain(Path inputPath, Path NNHLCRSamplePath) throws IOException {
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
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("Hyper_Param.dat"), 
                inputPath.resolve("Hyper_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_DAT_FILE_NAME), 
                inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_IDX_FILE_NAME), 
                inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
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
            Path datFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_DAT_FILE_NAME);
            Path idxFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_IDX_FILE_NAME);
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
            setupForTrain(inputPath, NNHLCRSamplePath);
        }
        catch (IOException ex) {
            ex.printStackTrace();
            return;
        }
        String[] FLIDs = new String[] { "FLa", "FLb", "FLc" };
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();
        for (int itr = 1; itr <= LOOP_COUNT; itr++) {
            String FLID = FLIDs[itr%3];
            System.out.println(String.format("[%05d] FLID[%s] ========================================", itr, FLID));
            String taskID = "FL_" + itr;
            TrainResult trainResult = trainManager.train(
                    FLID, taskID, metaData, trainInfo, inputPath, outputPath);
            assertEquals(0, trainResult.getStatus());
            assertEquals(0, PBChecker.checkPBTrainResult(trainResult.getTrainResult(), trainInfo));
            assertEquals(true, trainResult.getTrainResult().hasNNHLCRModel());
            Path backUpPath = root.resolve(FLID).resolve(taskID);
            assertEquals(true, PathChecker.checkFolderPath(backUpPath, true, true, true));
            try {
                Files.copy(outputPath.resolve("cluster1.protobuf"), 
                        inputPath.resolve("cluster1.protobuf"), REPLACE_EXISTING);
                Files.copy(outputPath.resolve("cluster2.protobuf"), 
                        inputPath.resolve("cluster2.protobuf"), REPLACE_EXISTING);
                //Files.copy(outputPath.resolve("HLCR_Param.dat"), 
                        //inputPath.resolve("HLCR_Param.dat"), REPLACE_EXISTING);
            }
            catch (IOException ex) {
                ex.printStackTrace();
                return;
            }
        }
    }
}

