package com.sony.fl.test;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import com.sony.fl.algorithm.NNFedHLCRClient;
import com.sony.fl.PredictManager;
import com.sony.fl.DeployManager;

import com.sony.fl.exception.FLException;
import com.sony.fl.pb.TaskInfo;
import com.sony.fl.utils.CreatePBForTest;

public class TestMultiThread implements IExecutor {

    public static int count = 0;

    TestMultiThread(int num) {
        count = num;
    }

    public synchronized void notifyStop() {
        count--;
    }

    public static int getCount() {
        return count;
    }

    private static final int NUM_OF_THREADS;
    static {
        int num_of_threads = 3;
        String s = System.getenv("FL_NUM_OF_THREADS");
        try {
            if (s != null) {
                int v = Integer.parseInt(s);
                if (v > 1) num_of_threads = v;
            }
        }
        catch (NumberFormatException ex) {
            System.err.println(String.format("The num of threads uses 3 because FL_NUM_OF_THREADS[%s] is invalid", s));
        }
        NUM_OF_THREADS = num_of_threads;
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
    }

    public static void main(String[] args) {

        // deployManager
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

        // main
        IExecutor iexe = new TestMultiThread(NUM_OF_THREADS);

        TestRaceCondition r = TestRaceCondition.newInstance(iexe, deployManager);
        for (int i=0; i < NUM_OF_THREADS; i++) {
            Thread t = new Thread(r);
            t.start();
        }

        while (true) {
            try { Thread.sleep(100); } catch (Exception ex) {};
            if (getCount() <= 1) {
                System.exit(0);
            }
        }
    }
}
