package com.sony.fl;

/**
 * @author Masanobu Jimbo
 */

import com.sony.fl.pb.*;

public class TaskManager {
    String register() { // TODO : define args
        return null;
    }

    TaskInfo.PBTaskInfo generateTrainTask(String FLID) {
        return null;
    }

    // TODO : enable to receive parameters for evaluation
    TaskInfo.PBTaskInfo generateEvaluationTask(String FLID) {
        return null;
    }

    TaskInfo.PBTaskInfo generateDeployTask(String FLID, String appID) {
        return null;
    }

    int aggregateTrainTask(TaskResult.PBTrainResult[] trainResults, String modelPath) {
        return 0;
    }

    EvaluationMetrix.PBEvaluationMetrix aggregateEvaluationTask(
            TaskResult.PBEvaluationResult[] evaluationResults) {
        return null;
    }

    String getFLStatus(String FLID) {
        return null;
    }

}