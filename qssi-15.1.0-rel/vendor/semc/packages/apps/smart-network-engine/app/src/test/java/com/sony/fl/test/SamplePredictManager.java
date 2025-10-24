package com.sony.fl.test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotEquals;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import com.sony.fl.PredictManager;
import com.sony.fl.DeployManager;

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

import org.apache.commons.io.file.PathUtils;

public class SamplePredictManager {
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

//        {
//            float[][] sequenceData = {{0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f,
//                0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f},
//                {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f,
//                0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f}};
//            String groupLabel = "BSSID1";
//
//            PredictManager.PredictResult predictResult =
//                    predictManager.predict(sequenceData, groupLabel);
//
//            assertEquals(0, predictResult.getStatus());
//
//            System.out.println(String.format("status: %d", predictResult.getStatus()));
//            System.out.println(String.format("predict label: %f", predictResult.getPredictLabel()));
//            System.out.println(String.format("predict result: %s", predictResult.getPredictResult()));
//        }

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
//          for (int x = 0; x < 10000; x++) {
                for (int i = 0;i < 64;i++) {
//              for (int i = 0;i < 1;i++) {
                    System.out.println(String.format("[%02d]==================================================", i+1));
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
//          }
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

