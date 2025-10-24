/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine;

import android.content.Context;
import android.content.SharedPreferences;

import com.sonymobile.smartnetworkengine.debug.DebugViewService;

import java.util.Objects;

public class PreferenceAccessor {

    private static final String SHARED_PREFS_FILENAME = "SmartNetworkEngineSharedPrefs";

    private static final String KEY_DEBUG_VIEW_TYPE = "DEBUG_VIEW_TYPE";

    private static final String KEY_DAILY_UPDATE_SIZE = "DAILY_UPDATE_SIZE";

    private static final String KEY_START_TIME = "START_TIME";

    public static long getDailyUpdateSize() {
        return getSharedPreferences().getLong(KEY_DAILY_UPDATE_SIZE, 0);
    }

    public static void setDailyUpdateSize(long value) {
        getSharedPreferences().edit()
                .putLong(KEY_DAILY_UPDATE_SIZE, value)
                .apply();
    }

    public static long getStartTime() {
        return getSharedPreferences().getLong(KEY_START_TIME, 0);
    }

    public static void setStartTime(long value) {
        getSharedPreferences().edit()
                .putLong(KEY_START_TIME, value)
                .apply();
    }

    public static int getDebugViewType() {
        return getSharedPreferences().getInt(KEY_DEBUG_VIEW_TYPE,
                DebugViewService.DEBUG_VIEW_TYPE_DISABLE); //TODO: unnecessary dependency
    }

    public static void setDebugViewType(int value) {
        getSharedPreferences().edit()
                .putInt(KEY_DEBUG_VIEW_TYPE, value)
                .apply();
    }

    private static SharedPreferences getSharedPreferences() {
        return Objects.requireNonNull(SneApplication.getContext(), "Should never happen")
                .getSharedPreferences(SHARED_PREFS_FILENAME, Context.MODE_PRIVATE);
    }
}
