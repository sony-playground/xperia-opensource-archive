/*
 * Copyright (C) 2019 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.debug;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

import androidx.annotation.Nullable;

import com.sonymobile.smartnetworkengine.PreferenceAccessor;
import com.sonymobile.smartnetworkengine.SneUtils;
import com.sonymobile.smartnetworkengine.api.debug.ISneDebugManager;
import com.sonymobile.smartnetworkengine.util.Log;

/**
 * A service to provide debug APIs which are intended to be used from sne-fts-tester application.
 * This service is alive as long as the binding with the application exists.
 */
public class DebugApiService extends Service {

    private static final String TAG = DebugApiService.class.getSimpleName();

    private static final String ACTION_DEBUG_MANAGER =
            "com.sonymobile.smartnetworkengine.intent.action.ISneDebugManager";

    /* Interface for application */
    private final ISneDebugManager.Stub mServiceInterface = new ISneDebugManager.Stub() {
        @Override
        public void setForcibleReleaseBuild(boolean enable) {
            SneUtils.setForcibleReleaseBuild(enable);
        }

        @Override
        public void setIddUploadedSize(long size) {
            PreferenceAccessor.setDailyUpdateSize(size);
        }
    };

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        Log.v(TAG, "onBind: " + intent);
        String action = intent.getAction();
        if (ACTION_DEBUG_MANAGER.equals(action)) {
            return mServiceInterface;
        }
        return null;
    }
}
