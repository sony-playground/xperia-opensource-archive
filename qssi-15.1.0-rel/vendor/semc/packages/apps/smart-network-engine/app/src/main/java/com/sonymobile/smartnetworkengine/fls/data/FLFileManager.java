/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.data;

import static com.sonymobile.smartnetworkengine.Constants.FLS_TASK_DATA_FILE_MAX_SIZE;

import android.text.TextUtils;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;

import com.sony.fl.algorithm.LinearFedHLCRClient;
import com.sony.fl.algorithm.NNFedHLCRClient;
import com.sony.fl.exception.FLException;
import com.sony.fl.pb.TaskInfo.ModelType;
import com.sony.fl.pb.TaskInfo.TaskType;
import com.sony.fl.pb.TaskResult.PBTaskResult;
import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.DataSerializer;
import com.sony.fl.tensor.Tensor;
import com.sony.fl.tensor.TensorMap;
import com.sony.fl.tensor.TensorShape;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.FLTask;
import com.sonymobile.smartnetworkengine.fls.data.FLTrainingDataAccessor.DataSet;
import com.sonymobile.smartnetworkengine.util.Log;

import org.apache.commons.io.file.PathUtils;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Map;
import java.util.stream.Stream;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

/**
 * This class provides the file load/store API for the interaction with FL library.
 */
public class FLFileManager {

    private static final String TAG = FLFileManager.class.getSimpleName();

    private static final String UPLOAD_DATA_OUTPUT_DIR = "output";

    private static final String UPLOAD_DATA_PB_TASK_RESULT_FILE = "pbTaskResult.dat";

    @VisibleForTesting
    static final String DATA_DAT_FILE_NAME = "Data.jsonl";

    @VisibleForTesting
    static final String DATA_IDX_FILE_NAME = "Data.txt";

    private final Path mTaskDataTopDir;

    private final Path mUploadDataTopDir;

    private final Path mCalibrationTopDir;

    public FLFileManager(@NonNull Path taskDataTopDir, @NonNull Path uploadDataTopDir,
            @NonNull Path calibrationTopDir) {
        mTaskDataTopDir = taskDataTopDir;
        mUploadDataTopDir = uploadDataTopDir;
        mCalibrationTopDir = calibrationTopDir;
    }

    // ---------- APIs for "Task Data"
    // <Directory structure>
    //  task_data/<task_id>/...     # files extracted from downloaded zip file

    //TODO: consider a/b folder switch should be implemented?
    public boolean saveTaskData(@NonNull Map<FLTask, byte[]> taskDataMap) {
        // Delete the existing files first
        try {
            PathUtils.deleteDirectory(mTaskDataTopDir);
        } catch (IOException e) {
            Log.w(TAG, "failed to delete the task data top directory: " + e);
        }

        // Store each task data
        int totalSize = 0;
        for (Map.Entry<FLTask, byte[]> taskData : taskDataMap.entrySet()) {
            // Create a task data directory
            Path taskDataDir = getTaskDataPath(taskData.getKey());
            if (taskDataDir == null) {
                Log.e(TAG, "the task data file name is empty");
                return false;
            }
            try {
                Files.createDirectories(taskDataDir);
            } catch (IOException e) {
                Log.e(TAG, "failed to create the task data directory: " + e);
                return false;
            }
            byte[] zipContent = taskData.getValue();
            try (ByteArrayInputStream bis = new ByteArrayInputStream(zipContent);
                 ZipInputStream zis = new ZipInputStream(bis)) {
                // Unzip the zipped task data and write it to the file(s)
                ZipEntry entry;
                while ((entry = zis.getNextEntry()) != null) {
                    if (!entry.isDirectory()) { // Flatten directory structure for simplicity
                        // Check if total size is less than the limit
                        totalSize += entry.getSize();
                        if (totalSize > (FLS_TASK_DATA_FILE_MAX_SIZE * 2/* unzipped size = x2 */)) {
                            Log.e(TAG, "total size of the task data is over limit: " + totalSize);
                            return false;
                        }
                        Path dest = taskDataDir.resolve(Paths.get(
                                entry.getName()).getFileName().toString());
                        Files.copy(zis, dest);
                    }
                }
            } catch (IOException e) {
                Log.e(TAG, "failed to unzip and write the task data: " + e);
                // Delete already extracted data
                try {
                    PathUtils.deleteDirectory(mTaskDataTopDir);
                } catch (IOException ignored) {
                }
                return false;
            }
        }
        return true;
    }

    public void deleteTaskData(@NonNull FLTask flTask) {
        Path taskDataDir = getTaskDataPath(flTask);
        if (taskDataDir != null && Files.exists(taskDataDir)) {
            try {
                PathUtils.deleteDirectory(taskDataDir);
            } catch (IOException e) {
                Log.e(TAG, "failed to delete the task data directory: " + e);
            }
        }
    }

    @Nullable
    public Path getTaskDataPath(FLTask flTask) {
        if (flTask == null || !flTask.hasTaskInfo() || TextUtils.isEmpty(
                flTask.getTaskInfo().getTaskID())) {
            return null;
        }
        return mTaskDataTopDir.resolve(flTask.getTaskInfo().getTaskID());
    }

    // ---------- APIs for "Upload Data"
    // <Directory structure>
    //  upload_data/<task_id>/output/...        # files written by FL library
    //                       /pbTaskResult.dat  # PBTaskResult with the result from FL library

    /**
     * Prepares the upload data directory for specified FL task. The directory can be used to store
     * the result from either training or evaluation.
     */
    public boolean prepareUploadDataPath(@NonNull FLTask flTask) {
        Path uploadDataDir = getUploadDataPath(flTask);
        Path uploadDataOutputDir = getUploadDataOutputPath(flTask);
        if (uploadDataDir != null && uploadDataOutputDir != null) {
            if (Files.exists(uploadDataDir)) {
                throw new IllegalStateException("directory already exists: " + uploadDataDir);
            }
            try {
                // Create |uploadDataOutputDir| as it's under |uploadDataDir| so all necessary
                // directories are created
                Files.createDirectories(uploadDataOutputDir);
                return true;
            } catch (IOException e) {
                Log.e(TAG, "failed to create the upload data directory: " + e);
            }
        }
        return false;
    }

    /**
     * Saves the PBTaskResult object with the result from training/evaluation API.
     */
    public boolean saveUploadPBTaskResultData(@NonNull FLTask flTask,
            @NonNull PBTaskResult pbTaskResult) {
        Path uploadDataDir = getUploadDataPath(flTask);
        if (uploadDataDir != null) {
            Path pbTaskResultFile = uploadDataDir.resolve(UPLOAD_DATA_PB_TASK_RESULT_FILE);
            if (Files.exists(pbTaskResultFile)) {
                throw new IllegalStateException("file already exists: " + pbTaskResultFile);
            }
            try {
                Files.write(pbTaskResultFile, pbTaskResult.toByteArray());
                return true;
            } catch (IOException e) {
                Log.e(TAG, "failed to write the pb task result data: " + e);
            }
        }
        return false;
    }

    /**
     * Delete the upload data associated with specified FL task.
     */
    public void deleteUploadData(@NonNull FLTask flTask) {
        Path uploadDataDir = getUploadDataPath(flTask);
        if (uploadDataDir != null && Files.exists(uploadDataDir)) {
            try {
                PathUtils.deleteDirectory(uploadDataDir);
            } catch (IOException e) {
                Log.e(TAG, "failed to delete the upload data directory: " + e);
            }
        }
    }

    /**
     * Deletes all upload data.
     */
    public void deleteAllUploadData() {
        if (Files.exists(mUploadDataTopDir)) {
            try {
                PathUtils.deleteDirectory(mUploadDataTopDir);
            } catch (IOException e) {
                Log.e(TAG, "failed to delete the upload data top directory: " + e);
            }
        }
    }

    /**
     * Returns 'output' directory path to be used by training/evaluation API.
     */
    @Nullable
    public Path getUploadDataOutputPath(FLTask flTask) {
        Path uploadDataDir = getUploadDataPath(flTask);
        if (uploadDataDir != null) {
            return uploadDataDir.resolve(UPLOAD_DATA_OUTPUT_DIR);
        }
        return null;
    }

    /**
     * Returns top directory path of the upload data associated with specified FL task.
     */
    @Nullable
    public Path getUploadDataPath(FLTask flTask) {
        if (flTask == null || !flTask.hasTaskInfo() || TextUtils.isEmpty(
                flTask.getTaskInfo().getTaskID())) {
            return null;
        }
        return mUploadDataTopDir.resolve(flTask.getTaskInfo().getTaskID());
    }

    // ---------- APIs for "Calibration"
    // <Directory structure>
    //  calibration/AllData.dat

    @Nullable
    public Path prepareCalibrationPath() {
        if (Files.exists(mCalibrationTopDir)) {
            throw new IllegalStateException("directory already exists: " + mCalibrationTopDir);
        }
        try {
            Files.createDirectories(mCalibrationTopDir);
            return mCalibrationTopDir;
        } catch (IOException e) {
            Log.e(TAG, "failed to create the calibration directory: " + e);
        }
        return null;
    }

    public void deleteCalibrationData() {
        if (Files.exists(mCalibrationTopDir)) {
            try {
                PathUtils.deleteDirectory(mCalibrationTopDir);
            } catch (IOException e) {
                Log.e(TAG, "failed to delete the calibration directory: " + e);
            }
        }
    }

    // ---------- APIs for data and index files (required for Training/Evaluation/Calibration
    // (incl. deploy))

    /**
     * Creates data and index files for calibration.
     */
    @Nullable
    public DataMetadata writeDataFile(@NonNull Stream<DataSet> dataSetStream,
            @NonNull ModelType modelType) {
        Path dataFilePath = mCalibrationTopDir.resolve(DATA_DAT_FILE_NAME);
        Path indexFilePath = mCalibrationTopDir.resolve(DATA_IDX_FILE_NAME);
        return writeDataFile(dataFilePath, indexFilePath, dataSetStream, modelType);
    }

    /**
     * Creates data and index files for deploy/training/evaluation.
     */
    @Nullable
    public DataMetadata writeDataFile(@NonNull FLTask flTask,
            @NonNull Stream<DataSet> dataSetStream) {
        TaskType taskType = flTask.getTaskInfo().getTaskType();
        ModelType modelType;
        if (taskType == TaskType.Deploy) {
            modelType = flTask.getTaskInfo().getDeployInfo().getModelType();
        } else if (taskType == TaskType.Train) {
            modelType = flTask.getTaskInfo().getTrainInfo().getModelType();
        } else if (taskType == TaskType.Evaluation) {
            modelType = flTask.getTaskInfo().getEvaluationInfo().getModelType();
        } else {
            throw new IllegalStateException("Unexpected value: " + taskType);
        }
        Path taskDataDir = getTaskDataPath(flTask);
        if (taskDataDir != null) {
            Path dataFilePath = taskDataDir.resolve(DATA_DAT_FILE_NAME);
            Path indexFilePath = taskDataDir.resolve(DATA_IDX_FILE_NAME);
            return writeDataFile(dataFilePath, indexFilePath, dataSetStream, modelType);
        }
        return null;
    }

    private DataMetadata writeDataFile(@NonNull Path dataFilePath, @NonNull Path indexFilePath,
            @NonNull Stream<DataSet> dataSetStream, @NonNull ModelType modelType) {
        if (Files.exists(dataFilePath)) {
            throw new IllegalStateException("File already exists: " + dataFilePath);
        } else if (Files.exists(indexFilePath)) {
            throw new IllegalStateException("File already exists: " + indexFilePath);
        }
        try {
            DataSerializer dataSerializer = DataSerializer.createFor(dataFilePath, indexFilePath);
            dataSetStream.forEach(dataSet -> {
                float[][] features = dataSet.getFeatures();
                int timeSeriesLength = features.length;
                int numOfFeatures = 0;
                if (timeSeriesLength != 0) {
                    numOfFeatures = features[0].length;
                }
                Double[] featuresArray = Tensor.toDoubleArrayFrom(features);
                TensorMap tensorMap = TensorMap.newInstance();
                // Generation of TensorMap depends on the model specification used in appId
                if (modelType == ModelType.LinerHLCR) {
                    TensorShape tensorShape = TensorShape.createShape(numOfFeatures);
                    if (tensorShape != null && featuresArray != null) {
                        tensorMap.set(LinearFedHLCRClient.TENSOR_GROUP_LABEL,
                                Tensor.newTensor(dataSet.getGroupLabel()));
                        tensorMap.set(LinearFedHLCRClient.TENSOR_Y,
                                Tensor.newTensor(dataSet.getLabel()));
                        tensorMap.set(LinearFedHLCRClient.TENSOR_X,
                                Tensor.newTensor(tensorShape, featuresArray));
                        dataSerializer.save(tensorMap);
                    } else {
                        throw new RuntimeException("Cannot set features to tensorMap");
                    }
                } else if (modelType == ModelType.NNHLCR) {
                    TensorShape tensorShape = TensorShape.createShape(timeSeriesLength,
                            numOfFeatures);
                    if (tensorShape != null && featuresArray != null) {
                        tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES,
                                Tensor.newTensor(numOfFeatures));
                        tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL,
                                Tensor.newTensor(dataSet.getGroupLabel()));
                        tensorMap.set(NNFedHLCRClient.TENSOR_Y,
                                Tensor.newTensor(dataSet.getLabel()));
                        tensorMap.set(NNFedHLCRClient.TENSOR_X,
                                Tensor.newTensor(tensorShape, featuresArray));
                        dataSerializer.save(tensorMap);
                    } else {
                        throw new RuntimeException("Cannot set features to tensorMap");
                    }
                } else {
                    throw new RuntimeException("Unsupported modelType");
                }
            });
            return dataSerializer.getMetadata();
        } catch (FLException e) {
            Log.e(TAG, "failed to create DataSerializer: " + e);
        } catch (RuntimeException e) {
            Log.e(TAG, "failed to save data in stream: " + e);
        }
        return null;
    }

    @VisibleForTesting
    String toSpaceSeparatedString(@NonNull float[] floats) {
        int iMax = floats.length - 1;
        if (iMax == -1) {
            return "";
        }

        StringBuilder b = new StringBuilder();
        for (int i = 0; ; i++) {
            b.append(floats[i]);
            if (i == iMax) {
                return b.toString();
            }
            b.append(" ");
        }
    }
}
