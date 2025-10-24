/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.connected.logger;

import static com.sonymobile.smartnetworkengine.Constants.IDD_DAILY_UPLOAD_LIMIT_SIZE;
import static com.sonymobile.smartnetworkengine.Constants.IDD_DAILY_UPLOAD_LIMIT_SIZE_FOR_DEBUG;
import static com.sonymobile.smartnetworkengine.Constants.IDD_UPLOAD_LIMIT_PERIOD_MSEC;
import static com.sonymobile.smartnetworkengine.SneUtils.isDebugBuild;

import com.sonymobile.smartnetworkengine.PreferenceAccessor;
import com.sonymobile.smartnetworkengine.util.Log;

public class LoggerUtils {

    private static final String TAG = LoggerUtils.class.getSimpleName();

    private static final int DAILY_LIMIT_SIZE_BYTE =
            isDebugBuild() ? IDD_DAILY_UPLOAD_LIMIT_SIZE_FOR_DEBUG : IDD_DAILY_UPLOAD_LIMIT_SIZE;

    public static boolean isLoggingAllowed() {
        return PreferenceAccessor.getDailyUpdateSize() < DAILY_LIMIT_SIZE_BYTE;
    }

    public static void resetDailySizeIfNeeded() {
        long startTime = PreferenceAccessor.getStartTime();
        long now = System.currentTimeMillis();
        if (startTime + IDD_UPLOAD_LIMIT_PERIOD_MSEC < now) {
            Log.v(TAG, "Reset total size which indicates number of data sent to IDD daemon.");
            PreferenceAccessor.setStartTime(now);
            PreferenceAccessor.setDailyUpdateSize(0);
        }
    }
}
