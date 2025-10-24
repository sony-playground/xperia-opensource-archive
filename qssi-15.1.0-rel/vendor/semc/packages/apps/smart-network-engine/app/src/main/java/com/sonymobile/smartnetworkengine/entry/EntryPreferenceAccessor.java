/*
 * Copyright 2021 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.entry;

import android.content.Context;
import android.content.SharedPreferences;

import com.sonymobile.smartnetworkengine.SneApplication;

import java.util.Objects;

public class EntryPreferenceAccessor {

    private static final String SHARED_PREFS_FILENAME = "SmartNetworkEngineEntrySharedPrefs";

    public static final String KEY_LOGGER_DAILY_UPDATE_SIZE = "LOGGER_DAILY_UPDATE_SIZE";

    public static final String KEY_LOGGER_START_TIME = "LOGGER_START_TIME";

    public static long getLoggerDailyUpdateSize() {
        return getSharedPreferences().getLong(KEY_LOGGER_DAILY_UPDATE_SIZE, 0);
    }

    public static long getLoggerStartTime() {
        return getSharedPreferences().getLong(KEY_LOGGER_START_TIME, 0);
    }

    /**
     * Get the shared preferences instance for edit operation.
     */
    public static SharedPreferences getSharedPreferences() {
        return Objects.requireNonNull(SneApplication.getContext(), "Should never happen")
                .getSharedPreferences(SHARED_PREFS_FILENAME, Context.MODE_PRIVATE);
    }
}
