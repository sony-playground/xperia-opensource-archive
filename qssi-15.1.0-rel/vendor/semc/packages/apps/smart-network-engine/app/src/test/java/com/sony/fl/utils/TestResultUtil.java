package com.sony.fl.utils;

import java.lang.reflect.InvocationTargetException;

import org.junit.Test;
import static org.junit.Assert.assertEquals;

import com.sony.fl.PredictManager;
import com.sony.fl.TrainManager;
import com.sony.fl.pb.TaskResult;
import com.sony.fl.tensor.Tensor;
import com.sony.fl.tensor.TensorMap;
import com.sony.fl.tensor.TensorShape;
import com.sony.fl.utils.CreatePBForTest;
import com.sony.fl.utils.ResultUtil;

public class TestResultUtil {
    @Test
    public void createTrainResult() throws NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        TaskResult.PBTrainResult pbTrainResult = CreatePBForTest.createValidTrainTaskResultForNNHLCR();
        TrainManager.TrainResult trainResult = ResultUtil.newTrainResult(1, pbTrainResult);

        assertEquals(1, trainResult.getStatus());

        TaskResult.PBTrainResult resultTrainResult = trainResult.getTrainResult();
        assertEquals("validatation_metirix.dat", resultTrainResult.getValidationMetrixFileName());
    }

    @Test
    public void createEvaluationResult() throws NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        TaskResult.PBEvaluationResult pbEvaluationResult = CreatePBForTest.createValidEvaluationTaskResultWithValidEvaluationTask();
        TrainManager.EvaluationResult evaluationResult = ResultUtil.newEvaluationResult(2, pbEvaluationResult);

        assertEquals(2, evaluationResult.getStatus());

        TaskResult.PBEvaluationResult resultEvaluationResult = evaluationResult.getEvaluationResult();
        assertEquals("Evaluation_Result.dat", resultEvaluationResult.getEvaluationResultFileName());
    }

    @Test
    public void createPredictResult1() throws NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        PredictManager.PredictResult predictResult = ResultUtil.newPredictResult(3);

        assertEquals(3, predictResult.getStatus());
    }

    @Test
    public void createPredictResult2() throws NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        TensorMap tensorMap = TensorMap.newInstance();
        Tensor tensor = Tensor.newTensor(TensorShape.createShape(2, 3), new Double[] { 1.01, 1.02, 1.03, 2.01, 2.02, 2.03 });
        tensorMap.set("tensor", tensor);

        PredictManager.PredictResult predictResult = ResultUtil.newPredictResult(4, tensorMap);

        assertEquals(4, predictResult.getStatus());
        TensorMap resultTensorMap = predictResult.getResult();
        Tensor resultTensor = resultTensorMap.get("tensor");
        Double[] vector = (Double[])resultTensor.getValue();
        assertEquals(1.01d, vector[0].doubleValue(), 0.0);
        assertEquals(1.02d, vector[1].doubleValue(), 0.0);
        assertEquals(1.03d, vector[2].doubleValue(), 0.0);
        assertEquals(2.01d, vector[3].doubleValue(), 0.0);
        assertEquals(2.02d, vector[4].doubleValue(), 0.0);
        assertEquals(2.03d, vector[5].doubleValue(), 0.0);
    }
}
