package com.sony.fl;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import com.sony.fl.TrainManager.EvaluationResult;
import com.sony.fl.TrainManager.TrainResult;
import com.sony.fl.algorithm.LinearFedHLCRClient;
import com.sony.fl.exception.FLException;
import com.sony.fl.logger.FLLogger;
import com.sony.fl.pb.TaskInfo;
import com.sony.fl.pb.TaskInfo.PBDeleteInfo;
import com.sony.fl.pb.TaskInfo.PBEvaluationInfo;
import com.sony.fl.pb.TaskResult;
import com.sony.fl.pb.LinearHLCR;
import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.DataSerializer;
import com.sony.fl.tensor.TensorMap;
import com.sony.fl.utils.Const;
import com.sony.fl.utils.CreatePBForTest;
import com.sony.fl.utils.DataMetadataUtil;
import com.sony.fl.utils.PBChecker;
import com.sony.fl.utils.PathChecker;

import org.apache.commons.io.file.PathUtils;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import static java.nio.file.StandardCopyOption.REPLACE_EXISTING;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;

/**
 * @author Masanobu Jimbo
 */

public class TestTrainManager {
    public TrainManager trainManager;
    public Path root = Paths.get("src/test/resources/TrainManagerRoot");
    public Path inputPath = Paths.get("src/test/resources/input");
    public Path outputPath = Paths.get("src/test/resources/output");
    public Path LinearHLCRSamplePath = Paths.get("src/test/resources/LinearHLCR");
    public Path NNHLCRSamplePath = Paths.get("src/test/resources/NNHLCR");

    public DataMetadata train_meta;
    public DataMetadata eval_meta;

    @Before
    public void setUp() 
            throws IOException, FLException, 
            InstantiationException, IllegalAccessException, ClassNotFoundException{
        Files.createDirectories(root);
        Files.createDirectories(inputPath);
        Files.createDirectories(outputPath);
        trainManager = new TrainManager(root);
    }

    public void setupForTrain() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
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

        Path datFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_IDX_FILE_NAME);
        DataMetadata train_data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(train_data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(train_data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(train_data, "save_result", "success");
        this.train_meta = train_data;
    }

    public void setupForTrainForLinearHLCR() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("LinearHLCRGlobalWeight.json"),      inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("LinearRegressionGlobalModel.json"), inputPath.resolve("LinearRegressionGlobalModel.json"));
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("LinearHLCRTrainHyperParams.json"),  inputPath.resolve("LinearHLCRTrainHyperParams.json"));

        Files.copy(LinearHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_DAT_FILE_NAME), inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.copy(LinearHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_IDX_FILE_NAME), inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));

        Path datFile = Paths.get(inputPath.toString(), Const.TEST_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TEST_DATA_IDX_FILE_NAME);
        DataMetadata metaData = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(metaData, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(metaData, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(metaData, "save_result", "success");
        this.train_meta = metaData;
    }

    public void setUpForEvaluation() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
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

        Path datFile = Paths.get(inputPath.toString(), Const.TEST_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TEST_DATA_IDX_FILE_NAME);
        DataMetadata eval_data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(eval_data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(eval_data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(eval_data, "save_result", "success");
        this.eval_meta = eval_data;
    }

    public void setUpForEvaluationForLinearHLCR() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("LinearHLCRGlobalWeight.json"),      inputPath.resolve("LinearHLCRGlobalWeight.json"));
        Files.copy(LinearHLCRSamplePath.resolve("task_info").resolve("LinearRegressionGlobalModel.json"), inputPath.resolve("LinearRegressionGlobalModel.json"));

        Files.copy(LinearHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_DAT_FILE_NAME), inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.copy(LinearHLCRSamplePath.resolve("data").resolve(Const.TEST_DATA_IDX_FILE_NAME), inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));

        Path datFile = Paths.get(inputPath.toString(), Const.TEST_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TEST_DATA_IDX_FILE_NAME);
        DataMetadata metaData = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(metaData, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(metaData, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(metaData, "save_result", "success");
        this.eval_meta = metaData;
    }

	public void setUpForTrainAndEvaluation() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
		Path dataPath = Paths.get("src/test/resources/NNHLCR/train_and_eval");
		Files.copy(dataPath.resolve("HLCR_Param.dat"), 
				inputPath.resolve("HLCR_Param.dat"));
		Files.copy(dataPath.resolve("init_param.protobuf"), 
				inputPath.resolve("cluster1.protobuf"));
		Files.copy(dataPath.resolve("init_param.protobuf"), 
				inputPath.resolve("cluster2.protobuf"));
		Files.copy(dataPath.resolve("network.nntxt"), 
				inputPath.resolve("graph.nntxt"));
		Files.copy(dataPath.resolve("preprocess_params.dat"), 
				inputPath.resolve("preprocess_params.dat"));
		Files.copy(dataPath.resolve("Hyper_Param.dat"), 
                inputPath.resolve("Hyper_Param.dat"));
		Files.copy(dataPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME), 
				inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
		Files.copy(dataPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME), 
				inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
		Files.copy(dataPath.resolve(Const.TEST_DATA_DAT_FILE_NAME), 
				inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
		Files.copy(dataPath.resolve(Const.TEST_DATA_IDX_FILE_NAME), 
				inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));

        Path datFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_IDX_FILE_NAME);
        DataMetadata train_data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(train_data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(train_data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(train_data, "save_result", "success");
        this.train_meta = train_data;

        datFile = Paths.get(inputPath.toString(), Const.TEST_DATA_DAT_FILE_NAME);
        idxFile = Paths.get(inputPath.toString(), Const.TEST_DATA_IDX_FILE_NAME);
        DataMetadata eval_data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(eval_data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(eval_data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(eval_data, "save_result", "success");
        this.eval_meta = eval_data;
	}

    @After
    public void cleaning() throws IOException {
        PathUtils.deleteDirectory(root);
        PathUtils.deleteDirectory(inputPath);
        PathUtils.deleteDirectory(outputPath);
    }

    @Test
    public void createInstanceWithInvalidPath() 
            throws InstantiationException, IllegalAccessException, ClassNotFoundException {
        boolean flag = true;
        Path badPath = Paths.get("badpath");
        try {
            trainManager = new TrainManager(badPath);
        } catch (FLException e) {
            flag = false;
        }
        if (flag) assertEquals(0, 1);
    }

/*
  #####  #####     ##       #    #    #
    #    #    #   #  #      #    ##   #
    #    #    #  #    #     #    # #  #
    #    #####   ######     #    #  # #
    #    #   #   #    #     #    #   ##
    #    #    #  #    #     #    #    #
*/
    @Test
    public void testTrainWithValidLinearHLCRInput() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setupForTrainForLinearHLCR();
        String FLID = "fl-1";
        String taskID = "task-1_1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForLinearHLCR();        

        TrainResult trainResult = trainManager.train(
                FLID, taskID, this.train_meta, trainInfo, inputPath, outputPath);
        assertEquals(0, trainResult.getStatus());
        assertEquals(0, PBChecker.checkPBTrainResult(trainResult.getTrainResult(), trainInfo));
        assertEquals(true, trainResult.getTrainResult().hasLinearHLCRLocalModel());
        Path backUpPath = root.resolve(FLID).resolve(taskID);
        assertEquals(true, PathChecker.checkFolderPath(backUpPath, true, true, true));
    }

    @Test
    public void testTrainWithValidNNHLCRInput() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setupForTrain();
        String FLID = "fl-2";
        String taskID = "task-2_1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();        
        TrainResult trainResult = trainManager.train(
                FLID, taskID, this.train_meta, trainInfo, inputPath, outputPath);
        assertEquals(0, trainResult.getStatus());
        assertEquals(0, PBChecker.checkPBTrainResult(trainResult.getTrainResult(), trainInfo));
        assertEquals(true, trainResult.getTrainResult().hasNNHLCRModel());
        Path backUpPath = root.resolve(FLID).resolve(taskID);
        assertEquals(true, PathChecker.checkFolderPath(backUpPath, true, true, true));
        // duplication case
        trainResult = trainManager.train(
                FLID, taskID, this.train_meta, trainInfo, inputPath, outputPath);
        assertEquals(1, trainResult.getStatus());
        // next train task
        String taskID_next = "task-2_1-2";
        trainResult = trainManager.train(
                FLID, taskID_next, this.train_meta, trainInfo, inputPath, outputPath);
        assertEquals(0, trainResult.getStatus());
        assertEquals(false, PathChecker.checkFolderPath(backUpPath, true, true, true));
        Path newBackUpPath = root.resolve(FLID).resolve(taskID_next);
        assertEquals(true, PathChecker.checkFolderPath(newBackUpPath, true, true, true));
    }

	@Test
	public void testTrainAPIForSNE() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
		setUpForTrainAndEvaluation();
        String FLID = "fl-SNE";
        String taskID = "task-1";
		// run train
		TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();        
        TrainResult trainResult = trainManager.train(
                FLID, taskID, this.train_meta, trainInfo, inputPath, outputPath);
        assertEquals(0, trainResult.getStatus());
        assertEquals(0, PBChecker.checkPBTrainResult(trainResult.getTrainResult(), trainInfo));
        assertEquals(true, trainResult.getTrainResult().hasNNHLCRModel());
        Path backUpPath = root.resolve(FLID).resolve(taskID);
        assertEquals(true, PathChecker.checkFolderPath(backUpPath, true, true, true));
		Files.copy(outputPath.resolve("cluster1.protobuf"), 
				inputPath.resolve("cluster1.protobuf"), REPLACE_EXISTING);
		Files.copy(outputPath.resolve("cluster2.protobuf"), 
				inputPath.resolve("cluster2.protobuf"), REPLACE_EXISTING);
        // check HLCRParam and validation_metrix files
        Path hlcrParamFilePath = outputPath.resolve("HLCR_Param.dat");
        int numOfCluster = getKFromHLCRParam(hlcrParamFilePath);
        assertEquals(2, numOfCluster);
        int[] localNK = getLocalNKFromHLCRParam(hlcrParamFilePath);
        assertEquals(numOfCluster, localNK.length);
        Path trainValidationFilePath = outputPath.resolve("validation_metrix.dat");
        int numOfData = getNFromValidationResult(trainValidationFilePath);
        float trainLoss = getLossFromValidationResult(trainValidationFilePath);
        assertEquals(64, numOfData);
        if (localNK[0] * localNK[1] == 0) {
            assertEquals(0.6920, trainLoss, 1e-2);
        } else {
            assertEquals(0.6917, trainLoss, 1e-2);
        }
		// evaluate trained model
		PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();        
        EvaluationResult evaluationResult = trainManager.evaluation(
                FLID, this.eval_meta, evaluationInfo, inputPath, outputPath);
        assertEquals(0, evaluationResult.getStatus());
        assertEquals(0, PBChecker.checkPBEvaluationResult(evaluationResult.getEvaluationResult(), 
                evaluationInfo));
		Path resultPath = Paths.get("src/test/resources/NNHLCR/train_and_eval");
        String jni_output = readFile(outputPath.toString() + "/" + evaluationResult.getEvaluationResult().getEvaluationResultFileName());
        String[] rows = jni_output.split(System.getProperty("line.separator"));
        int N = Integer.valueOf(rows[0]);
        float[][] predicted_label = loadDataYPreds(resultPath.resolve("y_pred.csv"));
        int[] label = loadDataY(resultPath.resolve("y.csv"));
        assertEquals(predicted_label.length, N);
        for (int i = 0; i < N; i++) {
                String[] values = rows[i+1].split(" ");
                int y = Integer.valueOf(values[0]);
                float y_pred = Float.valueOf(values[1]);
                assertEquals(label[i], y);
                assertEquals(true, isMatch(y_pred, predicted_label[i]));
				FLLogger.i(i + " : " + y_pred + " : " 
						+ predicted_label[i][0] + " " + predicted_label[i][1] 
						+ " " + predicted_label[i][2] + " " + predicted_label[i][3] + " ");
        }
	}

	boolean isMatch(float value, float[] list) {
		for (int i=0;i<4;i++) {
			if (Math.abs(value - list[i]) < 1e4) {
				return true;
			}
		}
		return false;
	}

    public int getKFromHLCRParam(Path filePath) throws IOException {
        String hlcrParamStr = readFile(filePath.toString());
        String[] rows = hlcrParamStr.split(System.getProperty("line.separator"));
        return Integer.valueOf(rows[0]);
    }

    public int[] getLocalNKFromHLCRParam(Path filePath) throws IOException {
        String hlcrParamStr = readFile(filePath.toString());
        String[] rows = hlcrParamStr.split(System.getProperty("line.separator"));
        int[] ans = new int[rows.length-1];
        for (int i=0; i<rows.length-1;i++) {
            ans[i] = Integer.valueOf(rows[i+1]);
        }
        return ans;
    }

    public int getNFromValidationResult(Path filePath) throws IOException {
        String validationStr = readFile(filePath.toString());
        String[] columns = validationStr.split(" ");
        return Integer.valueOf(columns[0]);
    }

    public float getLossFromValidationResult(Path filePath) throws IOException {
        String validationStr = readFile(filePath.toString());
        String[] columns = validationStr.split(" ");
        return Float.valueOf(columns[1]);
    }

	public float[][] loadDataYPreds(Path filePath) throws IOException {
        String ansStr = readFile(filePath.toString());
        String[] strs = ansStr.split(System.getProperty("line.separator"));
        float[][] ret = new float[64][];
        for (int i=0;i<64;i++) {
			ret[i] = new float[4];
			String[] row = strs[i].split(" ");
			for (int j=0;j<4;j++) {
				ret[i][j] = Float.valueOf(row[j]);
			}
		}
        return ret;
    }

    @Test
    public void testTrainWithValidNNHLCRInputMultipleTimes() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setupForTrain();
        String FLID = "FL";
        int MAX_ITR = 10;
		TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();
        for (int itr = 0; itr < MAX_ITR; itr++) {
            String taskID = "FL_" + itr;
			TrainResult trainResult = trainManager.train(
                    FLID, taskID, this.train_meta, trainInfo, inputPath, outputPath);
			assertEquals(0, trainResult.getStatus());
			assertEquals(0, PBChecker.checkPBTrainResult(trainResult.getTrainResult(), trainInfo));
			assertEquals(true, trainResult.getTrainResult().hasNNHLCRModel());
			Path backUpPath = root.resolve(FLID).resolve(taskID);
			assertEquals(true, PathChecker.checkFolderPath(backUpPath, true, true, true));
			Files.copy(outputPath.resolve("cluster1.protobuf"), 
					inputPath.resolve("cluster1.protobuf"), REPLACE_EXISTING);
			Files.copy(outputPath.resolve("cluster2.protobuf"), 
					inputPath.resolve("cluster2.protobuf"), REPLACE_EXISTING);
			//Files.copy(outputPath.resolve("HLCR_Param.dat"), 
					//inputPath.resolve("HLCR_Param.dat"), REPLACE_EXISTING);
        }  
    }


    @Test
    public void testTrainWithInvalidInputPath() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setupForTrainForLinearHLCR();
        String FLID = "fl-1";
        String taskID = "task-bad1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForLinearHLCR();    
        Path invalidInputPath = Paths.get("bad_path");    
        TrainResult trainResult = trainManager.train(
                FLID, taskID, this.train_meta, trainInfo, invalidInputPath, outputPath);
        assertEquals(1, trainResult.getStatus());
        Path backUpPath = root.resolve(FLID).resolve(taskID);
        assertEquals(false, PathChecker.checkFolderPath(backUpPath, true, true, true));
    }

    @Test
    public void testTrainWithInvalidOutputPath() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setupForTrainForLinearHLCR();
        String FLID = "fl-1";
        String taskID = "task-bad2";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForLinearHLCR();    
        Path invalidOutputPath = Paths.get("bad_path");    
        TrainResult trainResult = trainManager.train(
                FLID, taskID, this.train_meta, trainInfo, inputPath, invalidOutputPath);
        assertEquals(1, trainResult.getStatus());
        Path backUpPath = root.resolve(FLID).resolve(taskID);
        assertEquals(false, PathChecker.checkFolderPath(backUpPath, true, true, true));
    }

    @Test
    public void testTrainWithFailedDataSerializerSave() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setupForTrain();
        DataMetadataUtil.set(this.train_meta, "save_result", "failed");
        String FLID = "fl-1";
        String taskID = "task-save";
		TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();
        TrainResult trainResult = trainManager.train(
                FLID, taskID, this.train_meta, trainInfo, inputPath, outputPath);
        assertEquals(1, trainResult.getStatus());
    }

/*
######  #    #    ##    #       #    #    ##     #####     #     ####   #    #
 #       #    #   #  #   #       #    #   #  #      #       #    #    #  ##   #
 #####   #    #  #    #  #       #    #  #    #     #       #    #    #  # #  #
 #       #    #  ######  #       #    #  ######     #       #    #    #  #  # #
 #        #  #   #    #  #       #    #  #    #     #       #    #    #  #   ##
 ######    ##    #    #  ######   ####   #    #     #       #     ####   #    #
*/

    @Test
    public void testEvaluationWithValidLinearHLCRInput() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpForEvaluationForLinearHLCR();
        String FLID = "fl-1";
        PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForLinearHLCR();        
        EvaluationResult evaluationResult = trainManager.evaluation(
                FLID, this.eval_meta, evaluationInfo, inputPath, outputPath);
        assertEquals(0, evaluationResult.getStatus());
        assertEquals(0, PBChecker.checkPBEvaluationResult(evaluationResult.getEvaluationResult(), 
                evaluationInfo));
    }

    @Test
    public void testEvaluationWithValidNNHLCRInput() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpForEvaluation();
        String FLID = "fl-2";
        PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();        
        EvaluationResult evaluationResult = trainManager.evaluation(
                FLID, this.eval_meta, evaluationInfo, inputPath, outputPath);
        assertEquals(0, evaluationResult.getStatus());
        assertEquals(0, PBChecker.checkPBEvaluationResult(evaluationResult.getEvaluationResult(), 
                evaluationInfo));
    }

    @Test
    public void testEvaluationWithInValidInputPath() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpForEvaluationForLinearHLCR();
        String FLID = "fl-1";
        PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForLinearHLCR(); 
        Path invalidInputPath = Paths.get("bad_path");        
        EvaluationResult evaluationResult = trainManager.evaluation(
                FLID, this.eval_meta, evaluationInfo, invalidInputPath, outputPath);
        assertEquals(1, evaluationResult.getStatus());
    }

    @Test
    public void testEvaluationWithInValidOutputPath() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpForEvaluationForLinearHLCR();
        String FLID = "fl-1";
        PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForLinearHLCR(); 
        Path invalidOutputPath = Paths.get("bad_path");        
        EvaluationResult evaluationResult = trainManager.evaluation(
                FLID, this.eval_meta, evaluationInfo, inputPath, invalidOutputPath);
        assertEquals(1, evaluationResult.getStatus());
    }

    @Test
    public void testEvaluationAPIForSNE() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpForEvaluation();
        String FLID = "fl-SNE";
        PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();        
        EvaluationResult evaluationResult = trainManager.evaluation(
                FLID, this.eval_meta, evaluationInfo, inputPath, outputPath);
        assertEquals(0, evaluationResult.getStatus());
        assertEquals(0, PBChecker.checkPBEvaluationResult(evaluationResult.getEvaluationResult(), 
                evaluationInfo));
        //FLLogger.i(readFile(outputPath.toString() + "/" + evaluationResult.getEvaluationResult().getEvaluationResultFileName()));
        String jni_output = readFile(outputPath.toString() + "/" + evaluationResult.getEvaluationResult().getEvaluationResultFileName());
        String[] rows = jni_output.split(System.getProperty("line.separator"));
        int N = Integer.valueOf(rows[0]);
        float[] predicted_label = loadDataYPred(NNHLCRSamplePath.resolve("predict").resolve("y_pred.csv"));
        int[] label = loadDataY(NNHLCRSamplePath.resolve("predict").resolve("y.csv"));
        assertEquals(predicted_label.length, N);
        for (int i = 0; i < N; i++) {
                String[] values = rows[i+1].split(" ");
                int l = Integer.valueOf(values[0]);
                float pl = Float.valueOf(values[1]);
                assertEquals(label[i], l);
                assertEquals(predicted_label[i], pl, 1e-5);
        }
    }

    public int[] loadDataY(Path filePath) throws IOException {
        String ansStr = readFile(filePath.toString());
        String[] strs = ansStr.split(System.getProperty("line.separator"));
        int[] ret = new int[64];
        for (int i=0;i<64;i++) ret[i] = Integer.valueOf(strs[i]);
        return ret;
    }

    public float[] loadDataYPred(Path filePath) throws IOException {
        String ansStr = readFile(filePath.toString());
        String[] strs = ansStr.split(System.getProperty("line.separator"));
        float[] ret = new float[64];
        for (int i=0;i<64;i++) ret[i] = Float.valueOf(strs[i]);
        return ret;
    }

    @Test
    public void testEvaluationWithFailedDataSerializerSave() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        setUpForEvaluationForLinearHLCR();
        DataMetadataUtil.set(this.eval_meta, "save_result", "failed");
        String FLID = "fl-1";
        PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForLinearHLCR();
        EvaluationResult evaluationResult = trainManager.evaluation(
                FLID, this.eval_meta, evaluationInfo, inputPath, outputPath);
        assertEquals(1, evaluationResult.getStatus());
    }

/*
#####   ######  #       ######   #####  ######
 #    #  #       #       #          #    #
 #    #  #####   #       #####      #    #####
 #    #  #       #       #          #    #
 #    #  #       #       #          #    #
 #####   ######  ######  ######     #    ######
*/

    @Test
    public void testDeleteWithValidInput() {
        String FLID = "fl-d";
        Path dirPath = root.resolve(FLID);
        try {
            Files.createDirectories(dirPath);
        } catch (IOException e) {
            assertEquals(0, 1);
        }
        assertEquals(true, Files.exists(dirPath));
        PBDeleteInfo deleteInfo = CreatePBForTest.createValidDeleteInfo();        
        int deleteResult = trainManager.delete(FLID, deleteInfo);
        assertEquals(0, deleteResult);
        assertEquals(false, Files.exists(dirPath));
    }

/*
#####   #####      #    #    #    ##     #####  ######
 #    #  #    #     #    #    #   #  #      #    #
 #    #  #    #     #    #    #  #    #     #    #####
 #####   #####      #    #    #  ######     #    #
 #       #   #      #     #  #   #    #     #    #
 #       #    #     #      ##    #    #     #    ######
*/
    @Test
    public void testGetNewBackUpFolder() 
            throws NoSuchMethodException,
            SecurityException,
            IllegalAccessException,
            IllegalArgumentException, 
            InvocationTargetException
    {
        Method method = TrainManager.class.getDeclaredMethod("getNewBackUpFolder", 
                String.class, String.class);
        method.setAccessible(true);
        Path path = (Path)method.invoke(trainManager, "test1", "test2");
        assertEquals(true, path.toString().equals("src/test/resources/TrainManagerRoot/test1/test2"));
        // duplication case
        path = (Path)method.invoke(trainManager, "test1", "test2");
        assertEquals(true, path.toString().equals("src/test/resources/TrainManagerRoot/test1/test2"));
        // invalid input
        path = (Path)method.invoke(trainManager, "/etc", "issue");
        assertEquals(true, path == null);
    }
      
    
    @Test
    public void testDeleteDir() 
            throws NoSuchMethodException,
            SecurityException,
            IllegalAccessException,
            IllegalArgumentException, 
            InvocationTargetException
    {
        Method method = TrainManager.class.getDeclaredMethod("deleteDir", Path.class);
        method.setAccessible(true);
        Path badPath = Paths.get("badpath");
        // invalid path case
        assertEquals(1, (int)method.invoke(trainManager, badPath));
    }

    public String readFile(String path) throws IOException {
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

	@Test
	public void testTrainingAPI_NoDataForLinearHLCR() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException
    {
        setupForTrainForLinearHLCR();

        String FLID = "fl-1";
        String taskID = "task-1_1";

        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForLinearHLCR();

        Path datFile = Paths.get(outputPath.toString(), "testTrainingAPI_NoData.dat");
        Path idxFile = Paths.get(outputPath.toString(), "testTrainingAPI_NoData.idx");
        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        // Do not save.
        DataMetadata zero = serializer.getMetadata();

        TrainResult trainResult = trainManager.train(FLID, taskID, zero, trainInfo, this.inputPath, this.outputPath);

        assertEquals(0, trainResult.getStatus());
        assertEquals(0, PBChecker.checkPBTrainResult(trainResult.getTrainResult(), trainInfo));

        final TaskResult.PBTrainResult pbTrainResult = trainResult.getTrainResult();
        assertTrue(Files.exists(this.outputPath.resolve(pbTrainResult.getValidationMetrixFileName())));

        final LinearHLCR.PBLinearHLCRLocalModel pbLinearHLCRLocalModel = pbTrainResult.getLinearHLCRLocalModel();
        assertTrue(Files.exists(this.outputPath.resolve(pbLinearHLCRLocalModel.getHLCRParamsFileName())));
        final int count = pbLinearHLCRLocalModel.getLinearRegressionFileNamesCount();
        for (int ii = 0; ii < count; ii++) { assertTrue(Files.exists(this.outputPath.resolve(pbLinearHLCRLocalModel.getLinearRegressionFileNames(ii)))); }
        assertTrue(Files.exists(this.outputPath.resolve(pbTrainResult.getValidationMetrixFileName())));

        Path clusterMapFile = this.root.resolve(FLID).resolve(taskID).resolve(LinearFedHLCRClient.CLUSTER_MAP_FILE_NAME);
        assertTrue(Files.exists(clusterMapFile));

        JsonNode jn_node = new ObjectMapper().readTree(readFile(clusterMapFile.toString()));
        JsonNode jn_K = jn_node.get("K");
        assertNotNull(jn_K);
        assertEquals(2, jn_K.intValue());
        JsonNode jn_cluster_map = jn_node.get("cluster_map");
        assertNotNull(jn_cluster_map);
        assertEquals(0, jn_cluster_map.size());
    }

	@Test
	public void testTrainingAPI_NoDataForNNHLCR() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException
    {
        setupForTrain();

        String FLID = "fl-1";
        String taskID = "task-1_1";

        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();

        Path datFile = Paths.get(outputPath.toString(), "testTrainingAPI_NoData.dat");
        Path idxFile = Paths.get(outputPath.toString(), "testTrainingAPI_NoData.idx");
        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        // Do not save.
        DataMetadata zero = serializer.getMetadata();

        TrainResult trainResult = trainManager.train(FLID, taskID, zero, trainInfo, this.inputPath, this.outputPath);

        assertEquals(0, trainResult.getStatus());
    }

	@Test
	public void testEvaluationAPI_NoDataForLinearHLCR() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException
    {
        setUpForEvaluationForLinearHLCR();

        String FLID = "fl-1";

        PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForLinearHLCR();

        Path datFile = Paths.get(outputPath.toString(), "testEvaluationAPI_NoData.dat");
        Path idxFile = Paths.get(outputPath.toString(), "testEvaluationAPI_NoData.idx");
        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        // Do not save.
        DataMetadata zero = serializer.getMetadata();

        EvaluationResult evaluationResult = trainManager.evaluation(FLID, zero, evaluationInfo, this.inputPath, this.outputPath);

        assertEquals(0, evaluationResult.getStatus());
        assertEquals(0, PBChecker.checkPBEvaluationResult(evaluationResult.getEvaluationResult(), evaluationInfo));

        TaskResult.PBEvaluationResult pbEvaluationResult = evaluationResult.getEvaluationResult();
        assertTrue(Files.exists(this.outputPath.resolve(pbEvaluationResult.getEvaluationResultFileName())));
    }

	@Test
	public void testEvaluationAPI_NoDataForNNHLCR() throws IOException, FLException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException
    {
        setUpForEvaluation();

        String FLID = "fl-1";

        PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();

        Path datFile = Paths.get(outputPath.toString(), "testEvaluationAPI_NoData.dat");
        Path idxFile = Paths.get(outputPath.toString(), "testEvaluationAPI_NoData.idx");
        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        // Do not save.
        DataMetadata zero = serializer.getMetadata();

        EvaluationResult evaluationResult = trainManager.evaluation(FLID, zero, evaluationInfo, this.inputPath, this.outputPath);

        assertEquals(0, evaluationResult.getStatus());
    }

    private DataMetadata generateOver10000TensorMaps() {
        Path datFile = Paths.get(this.inputPath.toString(), "TensorMaps10001.jsonl");
        Path idxFile = Paths.get(this.inputPath.toString(), "TensorMaps10001.index");
        DataSerializer serializer;
        try {
            serializer = DataSerializer.createFor(datFile, idxFile);
        }
        catch (FLException ex) {
            ex.printStackTrace();
            return null;
        }
        try {
            try (BufferedReader br = Files.newBufferedReader(this.inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME))) {
                TensorMap tensorMap = TensorMap.fromJsonString(br.readLine());
                for (int n = 0; n < 10001; n++) {
                    serializer.save(tensorMap);
                }
            }
        }
        catch (IOException ex) {
            ex.printStackTrace();
            return null;
        }
        return serializer.getMetadata();
    }

    @Test
    public void testTraining_NNHLCR_Over10000TensorMaps() {
        try { setupForTrain(); } catch (Exception ex) { ex.printStackTrace(); fail(); }

        DataMetadata meta = this.generateOver10000TensorMaps();
        assertNotNull(meta);

        String FLID = "fl-2";
        String taskID = "task-2_1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();        

        TrainResult trainResult = trainManager.train(FLID, taskID, meta, trainInfo, this.inputPath, this.outputPath);

        assertEquals(1, trainResult.getStatus());
    }

    @Test
    public void testEvaluation_NNHLCR_Over10000TensorMaps() {
        try { setupForTrain(); /* setUpForEvaluation(); */ } catch (Exception ex) { ex.printStackTrace(); fail(); }

        DataMetadata meta = this.generateOver10000TensorMaps();
        assertNotNull(meta);

        String FLID = "fl-2";
        PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();        

        EvaluationResult evaluationResult = trainManager.evaluation(FLID, meta, evaluationInfo, this.inputPath, this.outputPath);

        assertEquals(1, evaluationResult.getStatus());
    }

    @Test
    public void testTraining_NNHLCR_NoReadPermitToHyperParamFile() {
        try { setupForTrain(); } catch (Exception ex) { ex.printStackTrace(); fail(); }

        this.inputPath.resolve("Hyper_Param.dat").toFile().setReadable(false);

        String FLID = "fl-2";
        String taskID = "task-2_1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();        

        TrainResult trainResult = trainManager.train( FLID, taskID, this.train_meta, trainInfo, inputPath, outputPath);

        assertEquals(1, trainResult.getStatus());
    }

    @Test
    public void testTrain_NNHLCR_InvalidNumOfFeatures() throws NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException, IOException {
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), inputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), inputPath.resolve("graph.nntxt"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("Hyper_Param.dat"), inputPath.resolve("Hyper_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("InvalidNumOfFeatures.jsonl"), inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve(Const.TRAIN_DATA_IDX_FILE_NAME), inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
        Path datFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_IDX_FILE_NAME);
        DataMetadata train_data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(train_data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(train_data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(train_data, "save_result", "success");

        String FLID = "fl-i";
        String taskID = "task-i_1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();

        TrainResult trainResult = trainManager.train(FLID, taskID, train_data, trainInfo, inputPath, outputPath);
        assertEquals(1, trainResult.getStatus());
    }

    @Test
    public void testTrain_NNHLCR_InvalidTensorY() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), inputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), inputPath.resolve("graph.nntxt"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("Hyper_Param.dat"), inputPath.resolve("Hyper_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("InvalidTensorY.jsonl"), inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve(Const.TRAIN_DATA_IDX_FILE_NAME), inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
        Path datFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_IDX_FILE_NAME);
        DataMetadata train_data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(train_data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(train_data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(train_data, "save_result", "success");

        String FLID = "fl-i";
        String taskID = "task-i_1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();

        TrainResult trainResult = trainManager.train(FLID, taskID, train_data, trainInfo, inputPath, outputPath);
        assertEquals(1, trainResult.getStatus());
    }

    // @Test
    // public void testTrainWithInvalidTensorXLengthMin() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
    //     Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), inputPath.resolve("HLCR_Param.dat"));
    //     Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), inputPath.resolve("cluster1.protobuf"));
    //     Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), inputPath.resolve("cluster2.protobuf"));
    //     Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), inputPath.resolve("graph.nntxt"));
    //     Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), inputPath.resolve("preprocess_params.dat"));
    //     Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("Hyper_Param.dat"), inputPath.resolve("Hyper_Param.dat"));
    //     Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("InvalidTensorXLengthMin.jsonl"), inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
    //     Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve(Const.TRAIN_DATA_IDX_FILE_NAME), inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
    //     Path datFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_DAT_FILE_NAME);
    //     Path idxFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_IDX_FILE_NAME);
    //     DataMetadata train_data = DataMetadataUtil.newInstance();
    //     DataMetadataUtil.set(train_data, "tensor_map_file", datFile.toString());
    //     DataMetadataUtil.set(train_data, "tensor_map_index_file", idxFile.toString());
    //     DataMetadataUtil.set(train_data, "save_result", "success");

    //     String FLID = "fl-i";
    //     String taskID = "task-i_1";
    //     TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();

    //     TrainResult trainResult = trainManager.train(FLID, taskID, train_data, trainInfo, inputPath, outputPath);
    //     assertEquals(1, trainResult.getStatus());
    // }

    @Test
    public void testTrain_NNHLCR_InvalidTensorXLengthMax() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), inputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), inputPath.resolve("graph.nntxt"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("Hyper_Param.dat"), inputPath.resolve("Hyper_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("InvalidTensorXLengthMax.jsonl"), inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve(Const.TRAIN_DATA_IDX_FILE_NAME), inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
        Path datFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_IDX_FILE_NAME);
        DataMetadata train_data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(train_data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(train_data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(train_data, "save_result", "success");

        String FLID = "fl-i";
        String taskID = "task-i_1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();

        TrainResult trainResult = trainManager.train(FLID, taskID, train_data, trainInfo, inputPath, outputPath);
        assertEquals(1, trainResult.getStatus());
    }

    @Test
    public void testTrain_NNHLCR_InvalidFormatTrainParamFile() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), inputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), inputPath.resolve("graph.nntxt"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("Invalid_Format_Hyper_Param.dat"), inputPath.resolve("Hyper_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_DAT_FILE_NAME), inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_IDX_FILE_NAME), inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
        Path datFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_IDX_FILE_NAME);
        DataMetadata train_data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(train_data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(train_data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(train_data, "save_result", "success");

        String FLID = "fl-i";
        String taskID = "task-i_1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();

        TrainResult trainResult = trainManager.train(FLID, taskID, train_data, trainInfo, inputPath, outputPath);
        assertEquals(1, trainResult.getStatus());
    }

    @Test
    public void testTrain_NNHLCR_InvalidLearningRate() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), inputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), inputPath.resolve("graph.nntxt"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("Invalid_LearningRate_Hyper_Param.dat"), inputPath.resolve("Hyper_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_DAT_FILE_NAME), inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_IDX_FILE_NAME), inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
        Path datFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_IDX_FILE_NAME);
        DataMetadata train_data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(train_data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(train_data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(train_data, "save_result", "success");

        String FLID = "fl-i";
        String taskID = "task-i_1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();

        TrainResult trainResult = trainManager.train(FLID, taskID, train_data, trainInfo, inputPath, outputPath);
        assertEquals(1, trainResult.getStatus());
    }

    @Test
    public void testTrain_NNHLCR_InvalidBatchSize() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), inputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), inputPath.resolve("graph.nntxt"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("Invalid_BatchSize_Hyper_Param.dat"), inputPath.resolve("Hyper_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_DAT_FILE_NAME), inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_IDX_FILE_NAME), inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
        Path datFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_IDX_FILE_NAME);
        DataMetadata train_data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(train_data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(train_data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(train_data, "save_result", "success");

        String FLID = "fl-i";
        String taskID = "task-i_1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();

        TrainResult trainResult = trainManager.train(FLID, taskID, train_data, trainInfo, inputPath, outputPath);
        assertEquals(1, trainResult.getStatus());
    }

    @Test
    public void testTrain_NNHLCR_InvalidNumOfEpoch() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), inputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), inputPath.resolve("graph.nntxt"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("Invalid_NumOfEpoch_Hyper_Param.dat"), inputPath.resolve("Hyper_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_DAT_FILE_NAME), inputPath.resolve(Const.TRAIN_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data").resolve(Const.TRAIN_DATA_IDX_FILE_NAME), inputPath.resolve(Const.TRAIN_DATA_IDX_FILE_NAME));
        Path datFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TRAIN_DATA_IDX_FILE_NAME);
        DataMetadata train_data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(train_data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(train_data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(train_data, "save_result", "success");

        String FLID = "fl-i";
        String taskID = "task-i_1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();

        TrainResult trainResult = trainManager.train(FLID, taskID, train_data, trainInfo, inputPath, outputPath);
        assertEquals(1, trainResult.getStatus());
    }

    // @Test
    // public void testEvaluationWithInvalidFormatEvaluationInfo() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        // Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), inputPath.resolve("HLCR_Param.dat"));
        // Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), inputPath.resolve("cluster1.protobuf"));
        // Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), inputPath.resolve("cluster2.protobuf"));
        // Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), inputPath.resolve("graph.nntxt"));
        // Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), inputPath.resolve("preprocess_params.dat"));
        // Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve(Const.TEST_DATA_DAT_FILE_NAME), inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        // Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("TrainData.txt"), inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
        // Path datFile = Paths.get(inputPath.toString(), Const.TEST_DATA_DAT_FILE_NAME);
        // Path idxFile = Paths.get(inputPath.toString(), Const.TEST_DATA_IDX_FILE_NAME);
        // DataMetadata eval_data = DataMetadataUtil.newInstance();
        // DataMetadataUtil.set(eval_data, "tensor_map_file", datFile.toString());
        // DataMetadataUtil.set(eval_data, "tensor_map_index_file", idxFile.toString());
        // DataMetadataUtil.set(eval_data, "save_result", "success");

        // String FLID = "fl-i";
        // PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();
        // EvaluationResult evaluationResult = trainManager.evaluation(FLID, eval_data, evaluationInfo, inputPath, outputPath);
        // assertEquals(1, evaluationResult.getStatus());
    // }

    @Test
    public void testEvaluation_NNHLCR_WithInvalidNumOfFeatures() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), inputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), inputPath.resolve("graph.nntxt"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("InvalidNumOfFeatures.jsonl"), inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("TrainData.txt"), inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
        Path datFile = Paths.get(inputPath.toString(), Const.TEST_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TEST_DATA_IDX_FILE_NAME);
        DataMetadata eval_data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(eval_data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(eval_data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(eval_data, "save_result", "success");

        String FLID = "fl-i";
        PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();
        EvaluationResult evaluationResult = trainManager.evaluation(FLID, eval_data, evaluationInfo, inputPath, outputPath);
        assertEquals(1, evaluationResult.getStatus());
    }

    @Test
    public void testEvaluation_NNHLCR_InvalidTensorY() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), inputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), inputPath.resolve("graph.nntxt"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("InvalidTensorY.jsonl"), inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("TrainData.txt"), inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
        Path datFile = Paths.get(inputPath.toString(), Const.TEST_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TEST_DATA_IDX_FILE_NAME);
        DataMetadata eval_data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(eval_data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(eval_data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(eval_data, "save_result", "success");

        String FLID = "fl-i";
        PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();
        EvaluationResult evaluationResult = trainManager.evaluation(FLID, eval_data, evaluationInfo, inputPath, outputPath);
        assertEquals(1, evaluationResult.getStatus());
    }

    // @Test
    // public void testEvaluationWithInvalidTensorXLengthMin() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
    //     Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), inputPath.resolve("HLCR_Param.dat"));
    //     Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), inputPath.resolve("cluster1.protobuf"));
    //     Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), inputPath.resolve("cluster2.protobuf"));
    //     Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), inputPath.resolve("graph.nntxt"));
    //     Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), inputPath.resolve("preprocess_params.dat"));
    //     Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("InvalidTensorXMin.jsonl"), inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        // Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("TrainData.txt"), inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
    //     Path datFile = Paths.get(inputPath.toString(), Const.TEST_DATA_DAT_FILE_NAME);
    //     Path idxFile = Paths.get(inputPath.toString(), Const.TEST_DATA_IDX_FILE_NAME);
    //     DataMetadata eval_data = DataMetadataUtil.newInstance();
    //     DataMetadataUtil.set(eval_data, "tensor_map_file", datFile.toString());
    //     DataMetadataUtil.set(eval_data, "tensor_map_index_file", idxFile.toString());
    //     DataMetadataUtil.set(eval_data, "save_result", "success");

    //     String FLID = "fl-i";
    //     PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();
    //     EvaluationResult evaluationResult = trainManager.evaluation(FLID, eval_data, evaluationInfo, inputPath, outputPath);
    //     assertEquals(1, evaluationResult.getStatus());
    // }

    @Test
    public void testEvaluation_NNHLCR_InvalidTensorXLengthMax() throws NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("HLCR_Param.dat"), inputPath.resolve("HLCR_Param.dat"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster1.protobuf"), inputPath.resolve("cluster1.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("cluster2.protobuf"), inputPath.resolve("cluster2.protobuf"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("graph.nntxt"), inputPath.resolve("graph.nntxt"));
        Files.copy(NNHLCRSamplePath.resolve("task_info").resolve("preprocess_params.dat"), inputPath.resolve("preprocess_params.dat"));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("InvalidTensorXLengthMax.jsonl"), inputPath.resolve(Const.TEST_DATA_DAT_FILE_NAME));
        Files.copy(NNHLCRSamplePath.resolve("data_invalid").resolve("TrainData.txt"), inputPath.resolve(Const.TEST_DATA_IDX_FILE_NAME));
        Path datFile = Paths.get(inputPath.toString(), Const.TEST_DATA_DAT_FILE_NAME);
        Path idxFile = Paths.get(inputPath.toString(), Const.TEST_DATA_IDX_FILE_NAME);
        DataMetadata eval_data = DataMetadataUtil.newInstance();
        DataMetadataUtil.set(eval_data, "tensor_map_file", datFile.toString());
        DataMetadataUtil.set(eval_data, "tensor_map_index_file", idxFile.toString());
        DataMetadataUtil.set(eval_data, "save_result", "success");

        String FLID = "fl-i";
        PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();
        EvaluationResult evaluationResult = trainManager.evaluation(FLID, eval_data, evaluationInfo, inputPath, outputPath);
        assertEquals(1, evaluationResult.getStatus());
    }

    @Test
    public void testTrain_NNHLCR_NoNumOfFeatures_1() throws FLException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        setupForTrain();

        Path datFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.jsonl");
        Path idxFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.index");

        // String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        String tensorMapString = "{\"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        TensorMap tensorMap = TensorMap.fromJsonString(tensorMapString);
        assertNotNull(tensorMap);

        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        serializer.save(tensorMap);
        DataMetadata metaData = serializer.getMetadata();

        String FLID = "fl-i";
        String taskID = "task-i_1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();

        TrainResult trainResult = trainManager.train(FLID, taskID, metaData, trainInfo, this.inputPath, this.outputPath);
        assertEquals(1, trainResult.getStatus());
    }

    @Test
    public void testTrain_NNHLCR_NoNumOfFeatures_2() throws FLException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        setupForTrain();

        Path datFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.jsonl");
        Path idxFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.index");

        String tensorMapString_1 = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        String tensorMapString_2 = "{\"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        TensorMap tensorMap_1 = TensorMap.fromJsonString(tensorMapString_1);
        assertNotNull(tensorMap_1);
        TensorMap tensorMap_2 = TensorMap.fromJsonString(tensorMapString_2);
        assertNotNull(tensorMap_2);

        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        serializer.save(tensorMap_1);
        serializer.save(tensorMap_2);
        DataMetadata metaData = serializer.getMetadata();

        String FLID = "fl-i";
        String taskID = "task-i_1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();

        TrainResult trainResult = trainManager.train(FLID, taskID, metaData, trainInfo, this.inputPath, this.outputPath);
        assertEquals(1, trainResult.getStatus());
    }

    @Test
    public void testTrain_NNHLCR_NoGroupLabel() throws FLException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        setupForTrain();

        Path datFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.jsonl");
        Path idxFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.index");

        // String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        TensorMap tensorMap = TensorMap.fromJsonString(tensorMapString);
        assertNotNull(tensorMap);

        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        serializer.save(tensorMap);
        DataMetadata metaData = serializer.getMetadata();

        String FLID = "fl-i";
        String taskID = "task-i_1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();

        TrainResult trainResult = trainManager.train(FLID, taskID, metaData, trainInfo, this.inputPath, this.outputPath);
        assertEquals(1, trainResult.getStatus());
    }

    @Test
    public void testTrain_NNHLCR_NoY() throws FLException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        setupForTrain();

        Path datFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.jsonl");
        Path idxFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.index");

        // String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"x\": {\"shape\": [2, 3], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        TensorMap tensorMap = TensorMap.fromJsonString(tensorMapString);
        assertNotNull(tensorMap);

        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        serializer.save(tensorMap);
        DataMetadata metaData = serializer.getMetadata();

        String FLID = "fl-i";
        String taskID = "task-i_1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();

        TrainResult trainResult = trainManager.train(FLID, taskID, metaData, trainInfo, this.inputPath, this.outputPath);
        assertEquals(1, trainResult.getStatus());
    }

    @Test
    public void testTrain_NNHLCR_NoX() throws FLException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        setupForTrain();

        Path datFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.jsonl");
        Path idxFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.index");

        // String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}}";
        TensorMap tensorMap = TensorMap.fromJsonString(tensorMapString);
        assertNotNull(tensorMap);

        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        serializer.save(tensorMap);
        DataMetadata metaData = serializer.getMetadata();

        String FLID = "fl-i";
        String taskID = "task-i_1";
        TaskInfo.PBTrainInfo trainInfo = CreatePBForTest.createValidTrainInfoForNNHLCR();

        TrainResult trainResult = trainManager.train(FLID, taskID, metaData, trainInfo, this.inputPath, this.outputPath);
        assertEquals(1, trainResult.getStatus());
    }

    @Test
    public void testEvaluation_NNHLCR_NoNumOfFeatures_1() throws FLException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        setUpForEvaluation();

        Path datFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.jsonl");
        Path idxFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.index");

        // String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        String tensorMapString = "{\"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        TensorMap tensorMap = TensorMap.fromJsonString(tensorMapString);
        assertNotNull(tensorMap);

        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        serializer.save(tensorMap);
        DataMetadata metaData = serializer.getMetadata();

        String FLID = "fl-i";
        PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();
        EvaluationResult evaluationResult = trainManager.evaluation(FLID, metaData, evaluationInfo, this.inputPath, this.outputPath);
        assertEquals(1, evaluationResult.getStatus());
    }

    @Test
    public void testEvaluation_NNHLCR_NoNumOfFeatures_2() throws FLException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        setUpForEvaluation();

        Path datFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.jsonl");
        Path idxFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.index");

        String tensorMapString_1 = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        String tensorMapString_2 = "{\"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        TensorMap tensorMap_1 = TensorMap.fromJsonString(tensorMapString_1);
        assertNotNull(tensorMap_1);
        TensorMap tensorMap_2 = TensorMap.fromJsonString(tensorMapString_2);
        assertNotNull(tensorMap_2);

        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        serializer.save(tensorMap_1);
        serializer.save(tensorMap_2);
        DataMetadata metaData = serializer.getMetadata();

        String FLID = "fl-i";
        PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();
        EvaluationResult evaluationResult = trainManager.evaluation(FLID, metaData, evaluationInfo, this.inputPath, this.outputPath);
        assertEquals(1, evaluationResult.getStatus());
    }

    @Test
    public void testEvaluation_NNHLCR_NoGroupLabel() throws FLException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        setUpForEvaluation();

        Path datFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.jsonl");
        Path idxFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.index");

        // String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        TensorMap tensorMap = TensorMap.fromJsonString(tensorMapString);
        assertNotNull(tensorMap);

        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        serializer.save(tensorMap);
        DataMetadata metaData = serializer.getMetadata();

        String FLID = "fl-i";
        PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();
        EvaluationResult evaluationResult = trainManager.evaluation(FLID, metaData, evaluationInfo, this.inputPath, this.outputPath);
        assertEquals(1, evaluationResult.getStatus());
    }

    @Test
    public void testEvaluation_NNHLCR_NoY() throws FLException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        setUpForEvaluation();

        Path datFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.jsonl");
        Path idxFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.index");

        // String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"x\": {\"shape\": [2, 3], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        TensorMap tensorMap = TensorMap.fromJsonString(tensorMapString);
        assertNotNull(tensorMap);

        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        serializer.save(tensorMap);
        DataMetadata metaData = serializer.getMetadata();

        String FLID = "fl-i";
        PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();
        EvaluationResult evaluationResult = trainManager.evaluation(FLID, metaData, evaluationInfo, this.inputPath, this.outputPath);
        assertEquals(1, evaluationResult.getStatus());
    }

    @Test
    public void testEvaluation_NNHLCR_NoX() throws FLException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException, IOException {
        setUpForEvaluation();

        Path datFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.jsonl");
        Path idxFile = Paths.get(inputPath.toString(), "NoNumOfFeatures.index");

        // String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}, \"x\": {\"shape\": [1, 13], \"value\": [1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,12.0,13.0]}}";
        String tensorMapString = "{\"num_of_features\": {\"shape\": [1], \"value\": [13]}, \"group_label\": {\"shape\": [1], \"value\": [\"1\"]}, \"y\": {\"shape\": [1], \"value\": [0]}}";
        TensorMap tensorMap = TensorMap.fromJsonString(tensorMapString);
        assertNotNull(tensorMap);

        DataSerializer serializer = DataSerializer.createFor(datFile, idxFile);
        serializer.save(tensorMap);
        DataMetadata metaData = serializer.getMetadata();

        String FLID = "fl-i";
        PBEvaluationInfo evaluationInfo = CreatePBForTest.createValidEvaluationInfoForNNHLCR();
        EvaluationResult evaluationResult = trainManager.evaluation(FLID, metaData, evaluationInfo, this.inputPath, this.outputPath);
        assertEquals(1, evaluationResult.getStatus());
    }
}
