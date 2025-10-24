package com.sony.fl.utils;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import com.sony.fl.PredictManager;
import com.sony.fl.TrainManager;
import com.sony.fl.pb.TaskResult;
import com.sony.fl.tensor.TensorMap;

public class ResultUtil {
    public static TrainManager.TrainResult newTrainResult(int status, TaskResult.PBTrainResult trainResult) throws NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        Constructor<?> constructor = TrainManager.TrainResult.class.getDeclaredConstructor(int.class, TaskResult.PBTrainResult.class);
        constructor.setAccessible(true);
        return (TrainManager.TrainResult)constructor.newInstance(status, trainResult);
    }

    public static TrainManager.EvaluationResult newEvaluationResult(int status, TaskResult.PBEvaluationResult evaluationResult) throws NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        Constructor<?> constructor = TrainManager.EvaluationResult.class.getDeclaredConstructor(int.class, TaskResult.PBEvaluationResult.class);
        constructor.setAccessible(true);
        return (TrainManager.EvaluationResult)constructor.newInstance(status, evaluationResult);
    }

    public static PredictManager.PredictResult newPredictResult(int status) throws NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        Constructor<?> constructor = PredictManager.PredictResult.class.getDeclaredConstructor(int.class);
        constructor.setAccessible(true);
        return (PredictManager.PredictResult)constructor.newInstance(status);
    }

    public static PredictManager.PredictResult newPredictResult(int status, TensorMap tensorMap) throws NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {
        Constructor<?> constructor = PredictManager.PredictResult.class.getDeclaredConstructor(int.class, TensorMap.class);
        constructor.setAccessible(true);
        return (PredictManager.PredictResult)constructor.newInstance(status, tensorMap);
    }
}
