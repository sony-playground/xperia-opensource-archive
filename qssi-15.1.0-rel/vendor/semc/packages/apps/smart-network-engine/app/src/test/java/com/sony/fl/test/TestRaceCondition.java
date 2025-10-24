package com.sony.fl.test;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import com.sony.fl.DeployManager;
import com.sony.fl.PredictManager;

import com.sony.fl.algorithm.NNFedHLCRClient;
import com.sony.fl.exception.FLException;
import com.sony.fl.pb.TaskInfo;

import com.sony.fl.utils.Const;
import com.sony.fl.utils.CreatePBForTest;

import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.DataSerializer;
import com.sony.fl.tensor.Tensor;
import com.sony.fl.tensor.TensorMap;
import com.sony.fl.tensor.TensorShape;

class TestRaceCondition implements Runnable
{
    private static final String RED = "[31m";
    private static final String GREEN = "[32m";
    private static final String ORANGE = "[33m";
    private static final String WHITE = "[37m";

    private static void println_RED(String s) {//{{{
        System.out.print(RED);
        System.out.println(s);
        System.out.print(WHITE);
    }//}}}
    private static void println_GREEN(String s) {//{{{
        System.out.print(GREEN);
        System.out.println(s);
        System.out.print(WHITE);
    }//}}}
    private static void println_ORANGE(String s) {//{{{
        System.out.print(ORANGE);
        System.out.println(s);
        System.out.print(WHITE);
    }//}}}

    public static final Path trainManagerRoot;
    public static final Path predictManagerRoot;
    public static final Path inputPath;
    public static final Path NNHLCRSamplePath;

    static//{{{
    {
        trainManagerRoot   = Paths.get("src/test/resources/TrainManagerRoot");
        predictManagerRoot = Paths.get("src/test/resources/PredictManagerRoot");
        inputPath          = Paths.get("src/test/resources/input");
        NNHLCRSamplePath   = Paths.get("src/test/resources/NNHLCR");
    }//}}}

    public static TestRaceCondition newInstance(IExecutor executor, DeployManager deployManager)//{{{
    {
        if (executor == null) return null;
        if (deployManager == null) return null;
        return new TestRaceCondition(executor, deployManager);
    }//}}}

    private final IExecutor executor;
    private final DeployManager deployManager;

    private TestRaceCondition(IExecutor executor, DeployManager deployManager)//{{{
    {
        this.executor = executor;
        this.deployManager = deployManager;
    }//}}}

    private TestRaceCondition()//{{{
    {
        this.executor = null;
        this.deployManager = null;
    }//}}}

    private String readFile(String path) throws IOException {//{{{
        StringBuilder builder = new StringBuilder();
        try (BufferedReader reader = new BufferedReader(new FileReader(path))) {
            String string = reader.readLine();
            builder.append(string);
            while ((string = reader.readLine()) != null){
                builder.append(System.getProperty("line.separator") + string);
            }
        }
        return builder.toString();
    }//}}}

    private float[] loadDataY(Path filePath) throws IOException {//{{{
        String ansStr = this.readFile(filePath.toString());
        String[] strs = ansStr.split(System.getProperty("line.separator"));
        float[] ret = new float[64];
        for (int i=0;i<64;i++) ret[i] = Float.valueOf(strs[i]);
        return ret;
    }//}}}

    private float[][] loadDataX(Path filePath) throws IOException {//{{{
        String ansStr = this.readFile(filePath.toString());
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
    }//}}}

    private void main()
    {
        final String name = Thread.currentThread().getName();

        final TestRaceCondition me = new TestRaceCondition();

        final TaskInfo.PBDeployInfo deployInfo = CreatePBForTest.createValidDeployInfoForNNHLCR();
        final String appID = deployInfo.getAppID();

        final String FLID = String.format("fl-m-%s", name);
        final String groupLabel = "BSSID1";

        float[] label;
        try {
            label = me.loadDataY(NNHLCRSamplePath.resolve("predict").resolve("y_pred.csv"));
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

        boolean deploy_retry = false;
        boolean predict_retry = false;

        int rcd;
        for (int n = 1;; n++)
        {
            final String taskID = String.format("task-m-%s-%05d", name, n);
            rcd = this.deployManager.deploy(FLID, taskID, data, deployInfo, inputPath);
            if (rcd == 2)
            {
                println_ORANGE(String.format("[%s][%05d] deploy wait status: %d", taskID, n, rcd));
                deploy_retry = true;
                try { Thread.sleep(10); } catch (Exception ex) {};
                continue;
            }
            else
            if (rcd != 0)
            {
                println_RED(String.format("[%s][%05d] deploy failed status: %d", taskID, n, rcd));
                return;
            }

            println_GREEN(String.format("[%s][%05d] deploy status: %d", taskID, n, rcd));

            if (deploy_retry && predict_retry)
            {
                println_GREEN(String.format("[%s] complete", name));
                return;
            }

            PredictManager predictManager;
            try {
                predictManager = new PredictManager(predictManagerRoot, appID);
            }
            catch (FLException ex) {
                ex.printStackTrace();
                return;
            }

            for (int i = 0; i < 64;) {
                println_GREEN(String.format("[%s][%05d][%02d]==================================================", taskID, n, i));
                final float[][] sequenceData;
                try {
                    sequenceData = me.loadDataX(NNHLCRSamplePath.resolve("predict").resolve("x_"+ i +".csv"));
                }
                catch (IOException ex) {
                    ex.printStackTrace();
                    break;
                }

                Double[] flattenedSequenceData = Tensor.toDoubleArrayFrom(sequenceData);
                if (flattenedSequenceData == null) {
                    println_RED(String.format("[%s][%05d] illegal sequenceData", taskID, n));
                    break;
                }

                int shape_m = sequenceData.length;
                int shape_n = sequenceData[0].length;

                TensorMap tensorMap = TensorMap.newInstance();
                tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES, Tensor.newTensor(n));
                tensorMap.set(NNFedHLCRClient.TENSOR_SEQUENCE_DATA, Tensor.newTensor(TensorShape.createShape(shape_m, shape_n), flattenedSequenceData));
                tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));

                PredictManager.PredictResult predictResult = predictManager.predict(tensorMap);
                rcd = predictResult.getStatus();
                if (rcd == 2)
                {
                    println_ORANGE(String.format("[%s][%05d] predict wait status: %d", taskID, n, rcd));
                    predict_retry = true;
                    try { Thread.sleep(10); } catch (Exception ex) {};
                    continue;
                }
                else
                if (rcd != 0)
                {
                    println_RED(String.format("[%s][%05d] deploy failed status: %d", taskID, n, rcd));
                    return;
                }
                println_GREEN(String.format("[%s][%05d][%02d] predict status: %d", taskID, n, i, rcd));

                if (deploy_retry && predict_retry)
                {
                    println_GREEN(String.format("[%s] complete", name));
                    return;
                }

                i++;
            }
        }
    }

    public void run()
    {
        try
        {
            this.main();
        }
        catch (Exception ex)
        {
            ex.printStackTrace();
        }
        finally
        {
            this.executor.notifyStop();
        }
    }
}

