/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls;

import android.content.Context;
import android.content.SharedPreferences;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.sonymobile.smartnetworkengine.SneApplication;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.function.UnaryOperator;
import java.util.stream.Collectors;

public class FLPreferenceAccessor {

    private static final String SHARED_PREFS_FILENAME = "SmartNetworkEngineFLSystemSharedPrefs";

    /** Indicates current version number of {@link #SHARED_PREFS_FILENAME} file format */
    public static final int CURRENT_VERSION = 3;

    public static final String KEY_PREFS_VERSION = "PREFS_VERSION";

    public static final String KEY_DOWNLOAD_START_TIME = "DOWNLOAD_START_TIME";

    public static final String KEY_DOWNLOAD_RETRY_BACKOFF_COUNT = "DOWNLOAD_RETRY_BACKOFF_COUNT";

    public static final String KEY_UPLOAD_PERIOD_START_TIME = "UPLOAD_PERIOD_START_TIME";

    public static final String KEY_UPLOAD_PERIOD_END_TIME = "UPLOAD_PERIOD_END_TIME";

    public static final String KEY_UPLOAD_RETRY_BACKOFF_COUNT = "UPLOAD_RETRY_BACKOFF_COUNT";

    public static final String KEY_CLIENT_CONFIG_AS_STRING = "CLIENT_CONFIG_AS_STRING";

    public static final String KEY_SKIPPED_CLIENT_CONFIG_AS_HASH = "SKIPPED_CLIENT_CONFIG_AS_HASH";

    public static final String KEY_PENDING_FL_TASK_INDEX_LIST = "PENDING_FL_TASK_INDEX_LIST";

    public static final String KEY_COMPLETED_FL_TASK_ID_LIST = "COMPLETED_FL_TASK_ID_LIST";

    public static final String KEY_PENDING_PRIORITY_FL_TASK_INDEX_LIST =
            "PENDING_PRIORITY_FL_TASK_INDEX_LIST";

    public static final String KEY_PENDING_UPLOAD_FL_TASK_INDEX_LIST =
            "PENDING_UPLOAD_FL_TASK_INDEX_LIST";

    public static final UnaryOperator<String> MODEL_TYPE_KEY_GENERATOR =
            s -> String.format("MODEL_TYPE@%s", s);

    public static final UnaryOperator<String> MODEL_VERSION_KEY_GENERATOR =
            s -> String.format("MODEL_VERSION@%s", s);

    public static final UnaryOperator<String> LAST_CALIBRATION_TIME_KEY_GENERATOR =
            s -> String.format("LAST_CALIBRATION_TIME@%s", s);

    public static int getPrefsVersion() {
        return getSharedPreferences().getInt(KEY_PREFS_VERSION, 1);
    }

    public static long getDownloadStartTime() {
        return getSharedPreferences().getLong(KEY_DOWNLOAD_START_TIME, 0);
    }

    public static int getDownloadRetryBackoffCount() {
        return getSharedPreferences().getInt(KEY_DOWNLOAD_RETRY_BACKOFF_COUNT, 0);
    }

    public static long getUploadPeriodStartTime() {
        return getSharedPreferences().getLong(KEY_UPLOAD_PERIOD_START_TIME, 0);
    }

    public static long getUploadPeriodEndTime() {
        return getSharedPreferences().getLong(KEY_UPLOAD_PERIOD_END_TIME, 0);
    }

    public static int getUploadRetryBackoffCount() {
        return getSharedPreferences().getInt(KEY_UPLOAD_RETRY_BACKOFF_COUNT, 0);
    }

    @Nullable
    public static String getSkippedClientConfigAsHash() {
        return getSharedPreferences().getString(KEY_SKIPPED_CLIENT_CONFIG_AS_HASH, null);
    }

    public static List<Integer> getPendingFLTaskIndexList() {
        return fromCommaSeparatedIntegers(KEY_PENDING_FL_TASK_INDEX_LIST);
    }

    public static List<Integer> getPendingPriorityFLTaskIndexList() {
        return fromCommaSeparatedIntegers(KEY_PENDING_PRIORITY_FL_TASK_INDEX_LIST);
    }

    public static List<Integer> getPendingUploadFLTaskIndexList() {
        return fromCommaSeparatedIntegers(KEY_PENDING_UPLOAD_FL_TASK_INDEX_LIST);
    }

    public static List<String> getCompletedFLTaskIdList() {
        return fromCommaSeparatedStrings(KEY_COMPLETED_FL_TASK_ID_LIST);
    }

    public static int getModelType(@NonNull String appId) {
        return getSharedPreferences().getInt(MODEL_TYPE_KEY_GENERATOR.apply(appId), 0);
    }

    @Nullable
    public static String getModelVersion(@NonNull String appId) {
        return getSharedPreferences().getString(MODEL_VERSION_KEY_GENERATOR.apply(appId), null);
    }

    public static long getLastCalibrationTime(@NonNull String appId) {
        return getSharedPreferences().getLong(LAST_CALIBRATION_TIME_KEY_GENERATOR.apply(appId), 0);
    }

    /**
     * Get the shared preferences instance for edit operation.
     */
    public static SharedPreferences getSharedPreferences() {
        return Objects.requireNonNull(SneApplication.getContext(), "Should never happen")
                .getSharedPreferences(SHARED_PREFS_FILENAME, Context.MODE_PRIVATE);
    }

    public static String toCommaSeparatedString(@NonNull List<Integer> indexList) {
        return indexList.stream()
                .map(String::valueOf)
                .collect(Collectors.joining(","));
    }

    private static List<Integer> fromCommaSeparatedIntegers(String key) {
        return Arrays.stream(
                        getSharedPreferences().getString(key, "").split(","))
                .filter(e -> !e.isEmpty())
                .map(Integer::valueOf)
                .collect(Collectors.toCollection(ArrayList::new));
    }

    private static List<String> fromCommaSeparatedStrings(String key) {
        return Arrays.stream(
                        getSharedPreferences().getString(key, "").split(","))
                .filter(e -> !e.isEmpty()).collect(Collectors.toCollection(ArrayList::new));
    }
}
