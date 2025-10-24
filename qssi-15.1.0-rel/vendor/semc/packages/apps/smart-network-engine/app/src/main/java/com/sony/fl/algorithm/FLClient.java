package com.sony.fl.algorithm;

import java.nio.file.Path;

/**
 * @author Masanobu Jimbo
 */

import com.sony.fl.pb.*;
import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.TensorMap;

abstract public class FLClient {

    abstract public TaskResult.PBTrainResult train(
            DataMetadata metaData,
            TaskInfo.PBTrainInfo trainInfo,
            Path dataPath,
            Path trainParamPath,
            Path newBackUpPath,
            Path outputPath
    );

    abstract public TaskResult.PBEvaluationResult evaluate(
            DataMetadata metaData,
            TaskInfo.PBEvaluationInfo evaluationInfo,
            Path dataPath,
            Path evaluationParamPath,
            Path outputPath
    );

    abstract public TensorMap predict(TensorMap input);

    abstract public void finalize();
}
