/*
 * Copyright 2020, 2023 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.ext;

import static com.sonymobile.smartnetworkengine.ext.Constants.IDD_PROBE_NAME_CELLULAR;
import static com.sonymobile.smartnetworkengine.ext.Constants.IDD_PROBE_PKG_CELLULAR;
import static com.sonymobile.smartnetworkengine.ext.Constants.SETTINGS_VERBOSE_LOGGING_ENABLED;

import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.database.ContentObserver;
import android.net.Uri;
import android.os.Handler;
import android.os.IBinder;
import android.provider.Settings;

import com.sonyericsson.idd.api.Idd;
import com.sonymobile.smartnetworkengine.ext.cellular.CellularLogger;
import com.sonymobile.smartnetworkengine.ext.util.Log;
import com.sonymobile.smartnetworkengine.ext.util.Log.Level;

/**
 * Main service which always runs while device is on.
 */
public class ExtService extends Service {

    private static final String TAG = ExtService.class.getSimpleName();

    private static final String ACTION_IDD_CONFIG_UPDATED = "com.sonyericsson.idd.CONFIG_UPDATED";

    private CellularLogger mCellularLogger;

    /** A content observer to control log level upon verbose logging setting */
    private final ContentObserver mLogLevelObserver = new ContentObserver(new Handler()) {
        @Override
        public void onChange(boolean selfChange) {
            Log.setLogLevel(Settings.Global.getInt(getContentResolver(),
                    SETTINGS_VERBOSE_LOGGING_ENABLED, 0) == 1 ? Level.DEBUG : Level.INFO);
        }
    };

    /** A broadcast receiver to be notified of IDD config updated */
    private BroadcastReceiver mIddConfigUpdateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            Log.v(TAG, "IDD config update is received.");
            if (isIddProbeCellularActive()) {
                maybeStartCellularLogger();
            } else {
                maybeStopCellularLogger();
            }
        }
    };

    @Override
    public void onCreate() {
        super.onCreate();
        Log.i(TAG, "Service created");

        // Log level control through Settings provider
        final Uri logUri = Settings.Global.getUriFor(SETTINGS_VERBOSE_LOGGING_ENABLED);
        getContentResolver().registerContentObserver(logUri, false, mLogLevelObserver);
        Log.setLogLevel(Settings.Global.getInt(getContentResolver(),
                SETTINGS_VERBOSE_LOGGING_ENABLED, 0) == 1 ? Level.DEBUG : Level.INFO);

        registerReceiver(mIddConfigUpdateReceiver, new IntentFilter(ACTION_IDD_CONFIG_UPDATED),
                Context.RECEIVER_EXPORTED);
        if (isIddProbeCellularActive()) {
            maybeStartCellularLogger();
        }
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.i(TAG, "Service destroyed");
        getContentResolver().unregisterContentObserver(mLogLevelObserver);
        unregisterReceiver(mIddConfigUpdateReceiver);
        maybeStopCellularLogger();
    }

    private void maybeStartCellularLogger() {
        if (mCellularLogger == null) {
            Log.v(TAG, "Start CellularLogger");
            mCellularLogger = new CellularLogger(this);
            mCellularLogger.start();
        }
    }

    private void maybeStopCellularLogger() {
        if (mCellularLogger != null) {
            Log.v(TAG, "Stop CellularLogger");
            mCellularLogger.quitSync();
            mCellularLogger = null;
        }
    }

    private boolean isIddProbeCellularActive() {
        return Idd.isProbeActive(IDD_PROBE_PKG_CELLULAR, IDD_PROBE_NAME_CELLULAR);
    }
}
