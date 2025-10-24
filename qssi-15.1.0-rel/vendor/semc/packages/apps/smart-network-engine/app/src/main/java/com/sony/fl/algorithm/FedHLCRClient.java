package com.sony.fl.algorithm;

import java.nio.file.Path;

import com.sony.fl.pb.TaskInfo;
import com.sony.fl.tensor.DataMetadata;

/**
 * @author Masanobu Jimbo
 */

abstract public class FedHLCRClient extends FLClient {
    // for batch
    abstract public int updateClusterMapping(TaskInfo.PBDeployInfo deployInfo, 
        DataMetadata metaData, Path preprocessParamPath, Path calibrateInfoDirPath, Path newBackUpPath);

    protected boolean isFailedOrNot(long initializedPointer) {
        return initializedPointer == 0;
    }
}
