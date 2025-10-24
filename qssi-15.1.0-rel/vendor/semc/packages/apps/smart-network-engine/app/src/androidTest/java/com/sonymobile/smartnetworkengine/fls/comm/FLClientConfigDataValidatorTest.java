/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.comm;

import static com.sonymobile.smartnetworkengine.Constants.FLS_APP_ID_CONNECTED;
import static com.sonymobile.smartnetworkengine.Constants.FLS_APP_ID_ENTRY;
import static com.sonymobile.smartnetworkengine.Constants.FLS_APP_ID_LIST;

import static org.junit.Assert.fail;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sony.fl.pb.LinearHLCR;
import com.sony.fl.pb.NNHLCR;
import com.sony.fl.pb.TaskInfo;
import com.sony.fl.pb.TaskInfo.PBTaskInfo;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.AppidSpecificConfig;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.ClientConfig;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.ClientConfigRoot;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.FLTask;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.GeneralConfiguration;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.GeneralConfiguration.OperationMode;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.TargetDevice;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.TargetDevice.DeviceType;

import org.junit.Test;
import org.junit.runner.RunWith;

/**
 * Verify {@link FLClientConfigDataValidator} implementation.
 */
@RunWith(AndroidJUnit4.class)
public class FLClientConfigDataValidatorTest {

    @Test
    public void testValidate() {
        // Prepare
        TargetDevice targetDevice = TargetDevice.newBuilder()
                .setSwLabelRegex(".*")
                .setDeviceType(DeviceType.LIVE_AND_TEST)
                .setDeviceRatio(100)
                .build();
        GeneralConfiguration generalConfiguration = GeneralConfiguration.newBuilder()
                .setOperationMode(OperationMode.NORMAL)
                .setClientPollingFrequencyMins(Long.MAX_VALUE)
                .setUploadablePeriodHours(720)
                .build();
        AppidSpecificConfig appidSpecificConfigForConnected = AppidSpecificConfig.newBuilder()
                .setAppId(FLS_APP_ID_CONNECTED)
                .setInferenceThreshold(1.0f)
                .setTrainingDataCollectionRatio(0)
                .setMaxNumOfTrainingSession(100000)
                .setMaxNumOfTrainingSessionPerBssid(100000)
                .setMaxPeriodDaysOfTrainingSession(365)
                .setDataCountThreshold(Integer.MAX_VALUE)
                .setPeriodicCalibrationFrequencyDays(Integer.MAX_VALUE)
                .setPositiveLabelThreshold(1.0f)
                .setPositiveRateThreshold(1.0f)
                .setInferenceEnabled(true)
                .build();
        AppidSpecificConfig appidSpecificConfigForEntry = AppidSpecificConfig.newBuilder()
                .setAppId(FLS_APP_ID_ENTRY)
                .setInferenceThreshold(0.0f)
                .setTrainingDataCollectionRatio(100)
                .setMaxNumOfTrainingSession(1)
                .setMaxNumOfTrainingSessionPerBssid(1)
                .setMaxPeriodDaysOfTrainingSession(1)
                .setDataCountThreshold(1)
                .setPeriodicCalibrationFrequencyDays(0)
                .setPositiveLabelThreshold(0.0f)
                .setPositiveRateThreshold(0.0f)
                .setInferenceEnabled(false)
                .build();
        PBTaskInfo pbTaskInfoForConnected = PBTaskInfo.newBuilder()
                .setFLLibVersion("")
                .setTaskID("FL_test_connected-1")
                .setFLID("FL_test_connected")
                .setTaskType(TaskInfo.TaskType.Deploy)
                .setDeployInfo(TaskInfo.PBDeployInfo.newBuilder()
                        .setModelType(TaskInfo.ModelType.NNHLCR)
                        .setNNHLCRModel(NNHLCR.PBNNHLCRModel.newBuilder()
                                .setHLCRParamsFileName("test.dat")
                                .addNNGraphFileNames("test.nntxt")
                                .addNNWeightsFileNames("test.protobuf")
                                .build())
                        .setAppID(FLS_APP_ID_CONNECTED)
                        .setDataInfo(TaskInfo.PBDataInfo.newBuilder()
                                .setPreprocessParamsFileName("test2.dat")
                                .build())
                        .build())
                .setAppID(FLS_APP_ID_CONNECTED)
                .build();
        PBTaskInfo pbTaskInfoForEntry = PBTaskInfo.newBuilder()
                .setFLLibVersion("")
                .setTaskID("FL_test_entry-1")
                .setFLID("FL_test_entry")
                .setTaskType(TaskInfo.TaskType.Deploy)
                .setDeployInfo(TaskInfo.PBDeployInfo.newBuilder()
                        .setModelType(TaskInfo.ModelType.LinerHLCR)
                        .setLinearHLCRGlobalModel(LinearHLCR.PBLinearHLCRGlobalModel.newBuilder()
                                .setHLCRParamsFileName("test.json")
                                .addLinearRegressionFileNames("test.json")
                                .build())
                        .setAppID(FLS_APP_ID_ENTRY)
                        .setDataInfo(TaskInfo.PBDataInfo.newBuilder()
                                .setPreprocessParamsFileName("")
                                .build())
                        .build())
                .setAppID(FLS_APP_ID_ENTRY)
                .build();
        FLTask flDeployTaskForConnected = FLTask.newBuilder()
                .setTaskInfo(pbTaskInfoForConnected)
                .setTaskDataFile("task_data/test_connected.zip")
                .build();
        FLTask flDeployTaskForEntry = FLTask.newBuilder()
                .setTaskInfo(pbTaskInfoForEntry)
                .setTaskDataFile("task_data/test_entry.zip")
                .build();
        ClientConfig clientConfig = ClientConfig.newBuilder()
                .setConfigurationName("test")
                .setTargetDevice(targetDevice)
                .setGeneralConfiguration(generalConfiguration)
                .addAppidSpecificConfigs(appidSpecificConfigForConnected)
                .addAppidSpecificConfigs(appidSpecificConfigForEntry)
                .addFlTasks(flDeployTaskForConnected)
                .addFlTasks(flDeployTaskForEntry)
                .build();

        // Action and Check (for ClientConfigRoot)
        FLClientConfigDataValidator.validateRoot(
                ClientConfigRoot.newBuilder().addClientConfigs(clientConfig).build());

        // Action and Check (for ClientConfig)
        FLClientConfigDataValidator.validate(clientConfig, FLS_APP_ID_LIST, false);

        // Prepare (no AppId Specific config)
        ClientConfig modifiedClientConfig = clientConfig.toBuilder()
                .clearAppidSpecificConfigs()
                .build();

        // Action and Check
        try {
            FLClientConfigDataValidator.validate(modifiedClientConfig, FLS_APP_ID_LIST, false);
            fail();
        } catch (RuntimeException ignored) {
        }

        // Prepare (missing part of AppId in AppId Specific config)
        modifiedClientConfig = clientConfig.toBuilder()
                .clearAppidSpecificConfigs()
                .addAppidSpecificConfigs(appidSpecificConfigForConnected)
                .build();

        // Action and Check
        try {
            FLClientConfigDataValidator.validate(modifiedClientConfig, FLS_APP_ID_LIST, false);
            fail();
        } catch (RuntimeException ignored) {
        }

        // Prepare (invalid AppId in AppId Specific config) with lack of supported appId
        AppidSpecificConfig modifiedAppidSpecificConfig =
                appidSpecificConfigForConnected.toBuilder()
                        .setAppId("not_used_appid")
                        .build();
        modifiedClientConfig = clientConfig.toBuilder()
                .clearAppidSpecificConfigs()
                .addAppidSpecificConfigs(modifiedAppidSpecificConfig)
                .addAppidSpecificConfigs(appidSpecificConfigForEntry)
                .build();

        // Action and Check
        try {
            FLClientConfigDataValidator.validate(modifiedClientConfig, FLS_APP_ID_LIST, false);
            fail();
        } catch (RuntimeException ignored) {
        }

        // Prepare (invalid AppId in AppId Specific config)
        modifiedClientConfig = clientConfig.toBuilder()
                .addAppidSpecificConfigs(modifiedAppidSpecificConfig)
                .build();

        // Action and Check w/o unsupportedAppIdCheck
        FLClientConfigDataValidator.validate(modifiedClientConfig, FLS_APP_ID_LIST, false);

        // Action and Check with unsupportedAppIdCheck
        try {
            FLClientConfigDataValidator.validate(modifiedClientConfig, FLS_APP_ID_LIST, true);
            fail();
        } catch (RuntimeException ignored) {
        }

        // Prepare (invalid AppId in FL tasks)
        FLTask modifiedFlTask = flDeployTaskForConnected.toBuilder()
                .setTaskInfo(pbTaskInfoForConnected.toBuilder()
                        .setAppID("not_used_appid")
                        .build())
                .build();
        modifiedClientConfig = clientConfig.toBuilder()
                .clearFlTasks()
                .addFlTasks(modifiedFlTask)
                .addFlTasks(flDeployTaskForEntry)
                .build();

        // Action and Check w/o unsupportedAppIdCheck
        FLClientConfigDataValidator.validate(modifiedClientConfig, FLS_APP_ID_LIST, false);

        // Action and Check with unsupportedAppIdCheck
        try {
            FLClientConfigDataValidator.validate(modifiedClientConfig, FLS_APP_ID_LIST, true);
            fail();
        } catch (RuntimeException ignored) {
        }

        // Prepare (duplicate TaskId in FL tasks)
        modifiedClientConfig = clientConfig.toBuilder()
                .addFlTasks(flDeployTaskForConnected)
                .build();

        // Action and Check
        try {
            FLClientConfigDataValidator.validate(modifiedClientConfig, FLS_APP_ID_LIST, false);
            fail();
        } catch (RuntimeException ignored) {
        }

        // Action and Check (no config)
        try {
            FLClientConfigDataValidator.validateRoot(ClientConfigRoot.newBuilder().build());
            fail();
        } catch (RuntimeException ignored) {
        }
    }

    @Test
    public void testValidateTaskData() {
        // Action and Check
        FLClientConfigDataValidator.validateTaskData(new byte[]{0x50, 0x4B, 0x00});

        // Action and Check
        try {
            FLClientConfigDataValidator.validateTaskData(new byte[]{0x00, 0x00, 0x00});
            fail();
        } catch (RuntimeException ignored) {
        }

        // Action and Check
        try {
            FLClientConfigDataValidator.validateTaskData(new byte[]{0x50, 0x4B});
            fail();
        } catch (RuntimeException ignored) {
        }

        // Action and Check
        try {
            FLClientConfigDataValidator.validateTaskData(new byte[]{});
            fail();
        } catch (RuntimeException ignored) {
        }
    }

    @Test
    public void testCheckNumberRange() {
        // Action and Check
        FLClientConfigDataValidator.checkNumberRange(5, 0, Long.MAX_VALUE, "0 <= 5 <= max");

        // Action and Check
        FLClientConfigDataValidator.checkNumberRange(0, 0, Long.MAX_VALUE, "0 <= 0 <= max");

        // Action and Check
        FLClientConfigDataValidator.checkNumberRange(Long.MAX_VALUE, 0, Long.MAX_VALUE,
                "0 <= max <= max");

        // Action and Check
        FLClientConfigDataValidator.checkNumberRange(1, 1, 1, "1 <= 1 <= 1");

        // Action and Check
        try {
            FLClientConfigDataValidator.checkNumberRange(-1, 0, Long.MAX_VALUE, "0 <= -1 <= max");
            fail();
        } catch (RuntimeException ignored) {
        }

        // Action and Check
        try {
            FLClientConfigDataValidator.checkNumberRange(Long.MAX_VALUE, 0, Long.MAX_VALUE - 1,
                    "0 <= max <= max-1");
            fail();
        } catch (RuntimeException ignored) {
        }

        // Action and Check
        try {
            FLClientConfigDataValidator.checkNumberRange(0, 1, 1, "1 <= 0 <= 1");
            fail();
        } catch (RuntimeException ignored) {
        }
    }

    @Test
    public void testCheckFloatNumberRange() {
        // Action and Check
        FLClientConfigDataValidator.checkFloatNumberRange(0.5f, 0.0f, 1.0f, "0.0 <= 0.5 <= 1.0");

        // Action and Check
        FLClientConfigDataValidator.checkFloatNumberRange(0.0f, 0.0f, 1.0f, "0.0 <= 0.0 <= 1.0");

        // Action and Check
        FLClientConfigDataValidator.checkFloatNumberRange(1.0f, 0.0f, 1.0f, "0.0 <= 1.0 <= 1.0");

        // Action and Check
        FLClientConfigDataValidator.checkFloatNumberRange(1.0f, 0.0f, Float.MAX_VALUE,
                "0.0 <= 1.0 <= max");

        // Action and Check
        try {
            FLClientConfigDataValidator.checkFloatNumberRange(-1.0f, 0.0f, 1.0f,
                    "0.0 <= -1.0 <= 1.0");
            fail();
        } catch (RuntimeException ignored) {
        }

        // Action and Check
        try {
            FLClientConfigDataValidator.checkFloatNumberRange(1.1f, 0.0f, 1.0f,
                    "0.0 <= 1.1 <= 1.0");
            fail();
        } catch (RuntimeException ignored) {
        }

        // Action and Check
        try {
            FLClientConfigDataValidator.checkFloatNumberRange(-1.0f, 0.0f, Float.MAX_VALUE,
                    "0 <= -1.0 <= max");
            fail();
        } catch (RuntimeException ignored) {
        }

        // Action and Check
        try {
            FLClientConfigDataValidator.checkFloatNumberRange(Float.MAX_VALUE, 0.0f,
                    10000000 /* MAX_VALUE doesn't work */, "0.0 <= max <= 10000000");
            fail();
        } catch (RuntimeException ignored) {
        }
    }

    @Test
    public void testCheckFilepathFormat() {
        // Action and Check
        FLClientConfigDataValidator.checkFilepathFormat("test.dat", "");

        // Action and Check
        FLClientConfigDataValidator.checkFilepathFormat("test/test.dat", "");

        // Action and Check
        try {
            FLClientConfigDataValidator.checkFilepathFormat("test", "");
            fail();
        } catch (RuntimeException ignored) {
        }

        // Action and Check
        try {
            FLClientConfigDataValidator.checkFilepathFormat("test.dat ", "");
            fail();
        } catch (RuntimeException ignored) {
        }

        // Action and Check
        try {
            FLClientConfigDataValidator.checkFilepathFormat("/usr/test.dat", "");
            fail();
        } catch (RuntimeException ignored) {
        }

        // Action and Check
        try {
            FLClientConfigDataValidator.checkFilepathFormat("../usr/test.dat", "");
            fail();
        } catch (RuntimeException ignored) {
        }
    }

    @Test
    public void testCheckUuidFormat() {
        // Action and Check
        FLClientConfigDataValidator.checkUuidFormat("025fb490-7e73-4ed6-ab73-613eaf2c86cf", "");

        // Action and Check
        try {
            FLClientConfigDataValidator.checkUuidFormat("abc", "");
            fail();
        } catch (RuntimeException ignored) {
        }
    }
}
