/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.data;

import static com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.FLTask;
import static com.sonymobile.smartnetworkengine.fls.data.FLTrainingDataAccessor.DataSet;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;

import android.content.Context;

import androidx.test.core.app.ApplicationProvider;
import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sony.fl.pb.TaskInfo.ModelType;
import com.sony.fl.pb.TaskInfo.TaskType;
import com.sony.fl.pb.TaskInfo.PBTaskInfo;
import com.sony.fl.pb.TaskInfo.PBDeployInfo;
import com.sony.fl.tensor.DataMetadata;

import org.apache.commons.io.file.PathUtils;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Stream;

/**
 * Verify {@link FLFileManager} implementation.
 */
@RunWith(AndroidJUnit4.class)
public class FLFileManagerTest {

    private Path mTaskDataTopDir;

    private Path mUploadDataTopDir;

    private Path mCalibrationTopDir;

    private FLFileManager mFLFileManager;

    @Before
    public void setUp() throws IOException {
        Context context = ApplicationProvider.getApplicationContext();
        mTaskDataTopDir = context.getFilesDir().toPath().resolve("testDir1");
        mUploadDataTopDir = context.getFilesDir().toPath().resolve("testDir2");
        mCalibrationTopDir = context.getFilesDir().toPath().resolve("testDir3");
        mFLFileManager = new FLFileManager(mTaskDataTopDir, mUploadDataTopDir, mCalibrationTopDir);
    }

    @After
    public void tearDown() throws IOException {
        if (Files.exists(mTaskDataTopDir)) {
            PathUtils.deleteDirectory(mTaskDataTopDir);
        }
        if (Files.exists(mUploadDataTopDir)) {
            PathUtils.deleteDirectory(mUploadDataTopDir);
        }
        if (Files.exists(mCalibrationTopDir)) {
            PathUtils.deleteDirectory(mCalibrationTopDir);
        }
    }

    @Test
    public void testWriteDataFileForNNHLCR() throws IOException {
        // Create Stream of DataSet
        List<DataSet> dataSetList = new ArrayList<>();
        for (int i = 0; i < 3; i++) {
            DataSet dataSet = DataSet.builder().groupLabel("BSSID" + (i + 1)).features(
                            new float[][]{{0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f,
                                    1.0f},
                                    {1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f}})
                    .label(1.0f)
                    .build();
            dataSetList.add(dataSet);
        }
        Stream<DataSet> dataSetStream = dataSetList.stream();

        // Create FLTask
        PBDeployInfo pbDeployInfo = PBDeployInfo.newBuilder().setModelType(
                ModelType.NNHLCR).build();
        PBTaskInfo pbTaskInfo = PBTaskInfo.newBuilder().setTaskType(TaskType.Deploy).setTaskID(
                "Test").setDeployInfo(pbDeployInfo).build();
        FLTask flTask = FLTask.newBuilder().setTaskDataFile("Test").setTaskInfo(pbTaskInfo).build();
        Files.createDirectories(mTaskDataTopDir.resolve(mFLFileManager.getTaskDataPath(flTask)));

        // Action
        DataMetadata dataMetadata = mFLFileManager.writeDataFile(flTask, dataSetStream);

        // Check
        Path taskDataDir = mFLFileManager.getTaskDataPath(flTask);
        assertNotNull(taskDataDir);
        Path dataFilePath = taskDataDir.resolve(FLFileManager.DATA_DAT_FILE_NAME);
        Path indexFilePath = taskDataDir.resolve(FLFileManager.DATA_IDX_FILE_NAME);
        assertNotNull(dataMetadata);
        assertTrue(Files.exists(dataFilePath));
        assertTrue(Files.exists(indexFilePath));
    }

    @Test
    public void testWriteDataFileForLinerHLCR() throws IOException {
        // Create Stream of DataSet
        List<DataSet> dataSetList = new ArrayList<>();
        for (int i = 0; i < 3; i++) {
            DataSet dataSet = DataSet.builder().groupLabel("BSSID" + (i + 1)).features(
                            new float[][]{{0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f,
                                    1.0f}})
                    .label(1.0f)
                    .build();
            dataSetList.add(dataSet);
        }
        Stream<DataSet> dataSetStream = dataSetList.stream();

        // Create FLTask
        PBDeployInfo pbDeployInfo = PBDeployInfo.newBuilder().setModelType(
                ModelType.LinerHLCR).build();
        PBTaskInfo pbTaskInfo = PBTaskInfo.newBuilder().setTaskType(TaskType.Deploy).setTaskID(
                "Test").setDeployInfo(pbDeployInfo).build();
        FLTask flTask = FLTask.newBuilder().setTaskDataFile("Test").setTaskInfo(pbTaskInfo).build();
        Files.createDirectories(mTaskDataTopDir.resolve(mFLFileManager.getTaskDataPath(flTask)));

        // Action
        DataMetadata dataMetadata = mFLFileManager.writeDataFile(flTask, dataSetStream);

        // Check
        Path taskDataDir = mFLFileManager.getTaskDataPath(flTask);
        assertNotNull(taskDataDir);
        Path dataFilePath = taskDataDir.resolve(FLFileManager.DATA_DAT_FILE_NAME);
        Path indexFilePath = taskDataDir.resolve(FLFileManager.DATA_IDX_FILE_NAME);
        assertNotNull(dataMetadata);
        assertTrue(Files.exists(dataFilePath));
        assertTrue(Files.exists(indexFilePath));
    }

    @Test
    public void testWriteDataFileForCalibration() {
        // Create Stream of DataSet
        List<DataSet> dataSetList = new ArrayList<>();
        for (int i = 0; i < 3; i++) {
            DataSet dataSet = DataSet.builder().groupLabel("BSSID" + (i + 1)).features(
                            new float[][]{{0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f,
                                    1.0f},
                                    {1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f}})
                    .label(1.0f)
                    .build();
            dataSetList.add(dataSet);
        }
        Stream<DataSet> dataSetStream = dataSetList.stream();

        // Prepare
        mFLFileManager.prepareCalibrationPath();

        // Action
        DataMetadata dataMetadata = mFLFileManager.writeDataFile(dataSetStream, ModelType.NNHLCR);

        // Check
        Path dataFilePath = mCalibrationTopDir.resolve(FLFileManager.DATA_DAT_FILE_NAME);
        Path indexFilePath = mCalibrationTopDir.resolve(FLFileManager.DATA_IDX_FILE_NAME);
        assertNotNull(dataMetadata);
        assertTrue(Files.exists(dataFilePath));
        assertTrue(Files.exists(indexFilePath));
    }

    @Test
    public void testToSpaceSeparatedString() {
        float[] feature = {0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f};

        // Action
        String result = mFLFileManager.toSpaceSeparatedString(feature);

        // Check
        String expected = "0.0 0.1 0.2 0.3 0.4 0.5";
        assertEquals(expected, result);
    }
}
