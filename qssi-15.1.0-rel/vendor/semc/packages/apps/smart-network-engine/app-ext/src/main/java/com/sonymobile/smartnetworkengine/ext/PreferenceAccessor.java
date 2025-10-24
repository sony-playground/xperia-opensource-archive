/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.ext;

import android.content.SharedPreferences;

import androidx.preference.PreferenceManager;

/**
 * Accessor to shared preference.
 */
public class PreferenceAccessor {

    private static final String DAILY_UPDATE_SIZE = "DAILY_UPDATE_SIZE";

    private static final String START_TIME = "START_TIME";

    public static long getDailyUpdateSize() {
        return getSharedPreferences().getLong(DAILY_UPDATE_SIZE, 0);
    }

    public static void setDailyUpdateSize(long value) {
        getSharedPreferences().edit()
                .putLong(DAILY_UPDATE_SIZE, value)
                .apply();
    }

    public static long getStartTime() {
        return getSharedPreferences().getLong(START_TIME, 0);
    }

    public static void setStartTime(long value) {
        getSharedPreferences().edit()
                .putLong(START_TIME, value)
                .apply();
    }

    private static SharedPreferences getSharedPreferences() {
        return PreferenceManager.getDefaultSharedPreferences(SneeApplication.getContext());
    }
}
