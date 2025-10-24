/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.comm;

import androidx.annotation.NonNull;
import androidx.annotation.VisibleForTesting;

import com.sony.fl.pb.TaskInfo.TaskType;
import com.sony.fl.utils.PBChecker;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.AppidSpecificConfig;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.ClientConfig;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.ClientConfigRoot;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.FLTask;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.GeneralConfiguration;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.TargetDevice;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Objects;
import java.util.Set;
import java.util.regex.Pattern;

/**
 * The fields validator for {@link ClientConfig} object.
 */
public class FLClientConfigDataValidator {

    /** A regex pattern for file path string */
    private static final Pattern FILEPATH_PATTERN = Pattern.compile(
            "^[0-9a-zA-Z][0-9a-zA-Z/_-]*\\.[0-9a-zA-Z]+$");

    /** A regex pattern for UUID like string */
    private static final Pattern UUID_PATTERN = Pattern.compile(
            "^[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}$");

    /**
     * Validate {@link ClientConfigRoot} object.
     *
     * @param clientConfigRoot the object to be validated
     * @throws IllegalArgumentException if validation fails
     */
    public static void validateRoot(@NonNull ClientConfigRoot clientConfigRoot) {
        Objects.requireNonNull(clientConfigRoot, "Should never happens");

        String msg = "client_configs";
        checkNumberRange(clientConfigRoot.getClientConfigsCount(), 1, 32, msg);

        for (ClientConfig clientConfig : clientConfigRoot.getClientConfigsList()) {
            msg = "configuration_name";
            checkTrue(clientConfig.hasConfigurationName(), msg);
            checkNumberRange(clientConfig.getConfigurationName().length(), 1, 128, msg);

            /* <Target Device> */

            msg = "target_device";
            checkTrue(clientConfig.hasTargetDevice(), msg);
            TargetDevice targetDevice = clientConfig.getTargetDevice();

            msg = "sw_label_regex";
            checkTrue(targetDevice.hasSwLabelRegex(), msg);
            checkNumberRange(targetDevice.getSwLabelRegex().length(), 1, 128, msg);

            msg = "device_type";
            checkTrue(targetDevice.hasDeviceType(), msg);

            msg = "device_ids";
            checkNumberRange(targetDevice.getDeviceIdsCount(), 0, 32, msg);
            for (String deviceId : targetDevice.getDeviceIdsList()) {
                checkUuidFormat(deviceId, msg);
            }

            msg = "device_ratio";
            checkTrue(targetDevice.hasDeviceRatio(), msg);
            checkNumberRange(targetDevice.getDeviceRatio(), 1, 100, msg);
        }
    }

    /**
     * Validate {@link ClientConfig} object.
     *
     * @param clientConfig          the object to be validated
     * @param appIdList             the list of supported appId
     * @param unsupportedAppIdCheck the flag to show whether to validate unsupported appId or not
     * @throws IllegalArgumentException if validation fails
     */
    public static void validate(@NonNull ClientConfig clientConfig, List<String> appIdList,
            boolean unsupportedAppIdCheck) {
        /* <General Configuration> */

        String msg = "general_configuration";
        checkTrue(clientConfig.hasGeneralConfiguration(), msg);
        GeneralConfiguration generalConfiguration = clientConfig.getGeneralConfiguration();

        msg = "operation_mode";
        checkTrue(generalConfiguration.hasOperationMode(), msg);

        msg = "client_polling_frequency_hours";
        checkTrue(generalConfiguration.hasClientPollingFrequencyMins(), msg);
        checkNumberRange(generalConfiguration.getClientPollingFrequencyMins(), 1, Long.MAX_VALUE,
                msg);

        msg = "uploadable_period_hours";
        checkTrue(generalConfiguration.hasUploadablePeriodHours(), msg);
        checkNumberRange(generalConfiguration.getUploadablePeriodHours(), 1, 720, msg);

        /* <AppId Specific configs> */

        List<String> remainingAppIds = new ArrayList<>(appIdList);
        for (AppidSpecificConfig specificConfig : clientConfig.getAppidSpecificConfigsList()) {
            msg = "app_id";
            checkTrue(specificConfig.hasAppId(), msg);
            if (!PBChecker.isValidID(specificConfig.getAppId())) {
                throw new IllegalArgumentException("invalid app_id");
            }

            if (!remainingAppIds.remove(specificConfig.getAppId()) && unsupportedAppIdCheck) {
                throw new IllegalArgumentException("unknown app_id");
            }

            msg = "inference_threshold";
            checkTrue(specificConfig.hasInferenceThreshold(), msg);
            checkFloatNumberRange(specificConfig.getInferenceThreshold(), 0.0f, Float.MAX_VALUE,
                    msg);

            msg = "training_data_collection_ratio";
            checkTrue(specificConfig.hasTrainingDataCollectionRatio(), msg);
            checkNumberRange(specificConfig.getTrainingDataCollectionRatio(), 0, 100, msg);

            msg = "max_num_of_training_data";
            checkTrue(specificConfig.hasMaxNumOfTrainingSession(), msg);
            checkNumberRange(specificConfig.getMaxNumOfTrainingSession(), 1, 100000, msg);

            msg = "max_num_of_training_data_per_bssid";
            checkTrue(specificConfig.hasMaxNumOfTrainingSessionPerBssid(), msg);
            checkNumberRange(specificConfig.getMaxNumOfTrainingSessionPerBssid(), 1, 100000, msg);

            msg = "max_period_days_of_training_data";
            checkTrue(specificConfig.hasMaxPeriodDaysOfTrainingSession(), msg);
            checkNumberRange(specificConfig.getMaxPeriodDaysOfTrainingSession(), 1, 365, msg);

            msg = "data_count_threshold";
            checkTrue(specificConfig.hasDataCountThreshold(), msg);
            checkNumberRange(specificConfig.getDataCountThreshold(), 1, Integer.MAX_VALUE, msg);

            msg = "periodic_calibration_frequency_days";
            checkTrue(specificConfig.hasPeriodicCalibrationFrequencyDays(), msg);
            checkNumberRange(specificConfig.getPeriodicCalibrationFrequencyDays(), 0,
                    Integer.MAX_VALUE, msg);

            msg = "positive_label_threshold";
            checkTrue(specificConfig.hasPositiveLabelThreshold(), msg);
            checkFloatNumberRange(specificConfig.getPositiveLabelThreshold(), 0.0f, 1.0f, msg);

            msg = "positive_rate_threshold";
            checkTrue(specificConfig.hasPositiveRateThreshold(), msg);
            checkFloatNumberRange(specificConfig.getPositiveRateThreshold(), 0.0f, 1.0f, msg);

            msg = "inference_enabled";
            checkTrue(specificConfig.hasInferenceEnabled(), msg);
        }
        if (!remainingAppIds.isEmpty()) {
            throw new IllegalArgumentException("invalid appid_specific_configs");
        }

        /* <FL tasks> */

        msg = "fl_tasks";
        checkNumberRange(clientConfig.getFlTasksCount(), 0,
                5L * clientConfig.getAppidSpecificConfigsCount(), msg);

        Set<String> taskIds = new HashSet<>(clientConfig.getFlTasksCount());
        Set<String> deleteExistFlIds = new HashSet<>();
        for (FLTask flTask : clientConfig.getFlTasksList()) {
            msg = "task_info";
            checkTrue(flTask.hasTaskInfo(), msg);

            msg = "appID in task_info";
            checkTrue(flTask.getTaskInfo().hasAppID(), msg);

            // Skip validation of taskInfo if the given appId is unsupported
            if (appIdList.contains(flTask.getTaskInfo().getAppID())) {
                if (PBChecker.checkPBTaskInfo(flTask.getTaskInfo()) != 0) {
                    throw new IllegalArgumentException("invalid task_info");
                }

                msg = "taskId in task_info";
                checkTrue(flTask.getTaskInfo().hasTaskID(), msg);
                if (!taskIds.add(flTask.getTaskInfo().getTaskID())) {
                    throw new IllegalArgumentException("duplicate taskID found in task_info");
                }

                msg = "task_data_file";
                TaskType taskType = flTask.getTaskInfo().getTaskType();
                if (taskType == TaskType.Train || taskType == TaskType.Evaluation
                        || taskType == TaskType.Deploy) {
                    checkTrue(flTask.hasTaskDataFile(), msg);
                    checkNumberRange(flTask.getTaskDataFile().length(), 1, 128, msg);
                    checkFilepathFormat(flTask.getTaskDataFile(), msg);
                    // Any task should not be after delete task in the same FLID
                    msg = "taskType order";
                    checkFalse(deleteExistFlIds.contains(flTask.getTaskInfo().getFLID()), msg);
                } else if (taskType == TaskType.Delete) {
                    checkFalse(flTask.hasTaskDataFile(), msg);
                    deleteExistFlIds.add(flTask.getTaskInfo().getFLID());
                } else {
                    throw new IllegalArgumentException("unsupported task type");
                }
            } else if (unsupportedAppIdCheck) {
                throw new IllegalArgumentException("unknown appId found in task_info");
            }
        }
    }

    /**
     * Validate the task data pointed by {@link FLTask#getTaskDataFile()}.
     *
     * @param taskData the task data binary to be validated
     * @throws IllegalArgumentException if validation fails
     */
    public static void validateTaskData(@NonNull byte[] taskData) {
        Objects.requireNonNull(taskData, "Should never happens");
        // Verify the magic number of the file
        if (!(taskData.length > 2 && taskData[0] == 0x50 /* P */ && taskData[1] == 0x4B /* K */)) {
            throw new IllegalArgumentException("not zip format");
        }
    }

    private static void checkTrue(boolean value, String msg) {
        if (!value) {
            throw new IllegalArgumentException("not true (" + msg + ")");
        }
    }

    private static void checkFalse(boolean value, String msg) {
        if (value) {
            throw new IllegalArgumentException("not false (" + msg + ")");
        }
    }

    @VisibleForTesting
    static void checkNumberRange(long value, long startInclusive, long endInclusive, String msg) {
        if (!(startInclusive <= value && value <= endInclusive)) {
            throw new IllegalArgumentException(
                    String.format("not in range: %d <= [%d] <= %d (%s)", startInclusive, value,
                            endInclusive, msg));
        }
    }

    @VisibleForTesting
    static void checkFloatNumberRange(float value, float startInclusive, float endInclusive,
            String msg) {
        if (!(Float.compare(startInclusive, value) <= 0
                && Float.compare(value, endInclusive) <= 0)) {
            throw new IllegalArgumentException(
                    String.format("not in range: %f <= [%f] <= %f (%s)", startInclusive, value,
                            endInclusive, msg));
        }
    }

    @VisibleForTesting
    static void checkFilepathFormat(String value, String msg) {
        if (!FILEPATH_PATTERN.matcher(value).matches()) {
            throw new IllegalArgumentException("illegal string: " + value + " (" + msg + ")");
        }
    }

    @VisibleForTesting
    static void checkUuidFormat(String value, String msg) {
        if (!UUID_PATTERN.matcher(value).matches()) {
            throw new IllegalArgumentException("illegal string: " + value + " (" + msg + ")");
        }
    }
}
