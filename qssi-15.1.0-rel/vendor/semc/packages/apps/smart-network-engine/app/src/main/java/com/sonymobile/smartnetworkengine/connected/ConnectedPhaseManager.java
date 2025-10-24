/*
 * Copyright 2020, 2021, 2022, 2023 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.connected;

import static com.sonymobile.smartnetworkengine.Constants.SETTINGS_SMARTNET_CONNECTED_ENABLED;
import static com.sonymobile.smartnetworkengine.SneUtils.isDebugBuild;
import static com.sonymobile.smartnetworkengine.fls.FLSystemManager.FEATURE_CONNECTED;

import android.annotation.SuppressLint;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.database.ContentObserver;
import android.net.ConnectivityManager;
import android.net.ConnectivityManager.NetworkCallback;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkInfo;
import android.net.TransportInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.provider.Settings;

import androidx.annotation.MainThread;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;

import com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData.SneWifiEvent;
import com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData.UserWifiPreferenceInfo;
import com.sonymobile.smartnetworkengine.DefaultNetworkController;
import com.sonymobile.smartnetworkengine.PreferenceAccessor;
import com.sonymobile.smartnetworkengine.SneApplication;
import com.sonymobile.smartnetworkengine.SneUtils;
import com.sonymobile.smartnetworkengine.connected.logger.LoggerService;
import com.sonymobile.smartnetworkengine.connected.logger.LoggerService.StatsUpdateListener;
import com.sonymobile.smartnetworkengine.connected.logger.LoggerUtils;
import com.sonymobile.smartnetworkengine.debug.DebugViewService;
import com.sonymobile.smartnetworkengine.fls.FLSystemManager;
import com.sonymobile.smartnetworkengine.fls.Predictor;
import com.sonymobile.smartnetworkengine.fls.Predictor.PredictionResult;
import com.sonymobile.smartnetworkengine.util.IddWrapper;
import com.sonymobile.smartnetworkengine.util.Log;

/**
 * This class controls logger, predictor etc for connected wifi quality.
 */
public class ConnectedPhaseManager {

    private static final String TAG = ConnectedPhaseManager.class.getSimpleName();

    private static final int SERVICE_STOP_DELAY_MILLS = 3000;

    private final Context mContext;

    @Nullable
    private final FLSystemManager mFLSystemManager;

    private final SneConnectedScore mSneConnectedScore;

    private final CollectedDataHandler mCollectedDataHandler;

    private final Handler mHandler = new Handler(Looper.getMainLooper());

    private final ConnectivityManager mConnectivityManager;

    private boolean mStarted;

    private boolean mServicesStarted;

    private boolean mServicesStopping;

    /** A content observer to monitor Smart Connectivity on/off setting change */
    private final ContentObserver mSneSettingsObserver = new ContentObserver(new Handler()) {
        @Override
        public void onChange(boolean selfChange) {
            if (mServicesStarted) {
                if (SneUtils.isSmartNetworkConnectedSettingsEnabled()) {
                    Log.v(TAG, "Connected Settings is enabled, start SneConnectedScore");
                    mSneConnectedScore.start();
                } else {
                    Log.v(TAG, "Connected Settings is disabled, stop SneConnectedScore");
                    mSneConnectedScore.stop();
                }
            }
            updateFLSystemConnectedFeatureStatus();
        }
    };

    /** This callback is to start services when default network changes to wifi */
    private final NetworkCallback mDefaultNetworkCallback = new NetworkCallback() {
        @Override
        public void onCapabilitiesChanged(@NonNull Network network,
                @NonNull NetworkCapabilities nc) {
            super.onCapabilitiesChanged(network, nc);
            if (nc.hasTransport(NetworkCapabilities.TRANSPORT_WIFI)
                    && nc.hasCapability(NetworkCapabilities.NET_CAPABILITY_VALIDATED)) {
                TransportInfo transportInfo = nc.getTransportInfo();
                if (transportInfo instanceof WifiInfo) {
                    startServices();
                }
            }
        }
    };

    /** This callback is to stop services when Wi-Fi is disconnected */
    private final BroadcastReceiver mWifiConnectionReceiver = new BroadcastReceiver() {
        private boolean mWifiConnected;

        @Override
        public void onReceive(Context context, Intent intent) {
            if (WifiManager.NETWORK_STATE_CHANGED_ACTION.equals(intent.getAction())) {
                NetworkInfo networkInfo = (NetworkInfo) intent.getParcelableExtra(
                        WifiManager.EXTRA_NETWORK_INFO);
                if (networkInfo != null) {
                    if (networkInfo.isConnected() && !mWifiConnected) {
                        mWifiConnected = true;
                    } else if (!networkInfo.isConnected() && mWifiConnected) {
                        mWifiConnected = false;
                        postStopServices();
                    }
                }
            }
        }
    };

    private final ServiceConnection mConnectionToLogger = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder service) {
            LoggerService loggerService = ((LoggerService.LocalBinder) service).getService();
            loggerService.registerStatsUpdateListener(mCollectedDataHandler);
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
        }
    };

    public ConnectedPhaseManager(@NonNull Context context,
            @NonNull DefaultNetworkController defaultNetworkController) {
        mContext = context;
        mFLSystemManager = ((SneApplication) context.getApplicationContext()).getFLSystemManager();
        mSneConnectedScore = new SneConnectedScore(mContext, defaultNetworkController);
        mCollectedDataHandler = new CollectedDataHandler(mContext);
        mConnectivityManager = mContext.getSystemService(ConnectivityManager.class);
    }

    @MainThread
    public void start() {
        if (!mStarted) {
            // Monitor Smart Connectivity on/off setting change
            mContext.getContentResolver().registerContentObserver(
                    Settings.Global.getUriFor(SETTINGS_SMARTNET_CONNECTED_ENABLED), false,
                    mSneSettingsObserver);
            mConnectivityManager.registerDefaultNetworkCallback(mDefaultNetworkCallback, mHandler);
            IntentFilter intentFilter = new IntentFilter(WifiManager.NETWORK_STATE_CHANGED_ACTION);
            mContext.registerReceiver(mWifiConnectionReceiver, intentFilter);
            updateFLSystemConnectedFeatureStatus();
            mStarted = true;
        }
    }

    @MainThread
    public void stop() {
        if (mStarted) {
            mContext.getContentResolver().unregisterContentObserver(mSneSettingsObserver);
            mConnectivityManager.unregisterNetworkCallback(mDefaultNetworkCallback);
            mContext.unregisterReceiver(mWifiConnectionReceiver);
            mStarted = false;
        }
    }

    @SuppressLint("MissingPermission")
    private void startServices() {
        if (!mServicesStarted) {
            LoggerUtils.resetDailySizeIfNeeded();
            mContext.startService(new Intent(mContext, LoggerService.class));
            // TODO: |startService| above and |bindService| here can probably be merged to one call
            mContext.bindService(new Intent(mContext, LoggerService.class), mConnectionToLogger, 0);
            if (isDebugBuild() && PreferenceAccessor.getDebugViewType()
                    != DebugViewService.DEBUG_VIEW_TYPE_DISABLE && Settings.canDrawOverlays(
                    mContext)) {
                mContext.startService(new Intent(mContext, DebugViewService.class));
            }
            if (SneUtils.isSmartNetworkConnectedSettingsEnabled()) {
                mSneConnectedScore.start();
            }
            mServicesStarted = true;
        }
    }

    private void postStopServices() {
        if (mServicesStarted && !mServicesStopping) {
            // Must stop SneConnectedScore here - not in stopServices(), otherwise stop could occur
            // just after next wifi connection, making SneEntryScore scenario not work properly.
            mSneConnectedScore.stop();
            mHandler.postDelayed(this::stopServices, SERVICE_STOP_DELAY_MILLS);
            mServicesStopping = true;
        }
    }

    @SuppressLint("MissingPermission")
    private void stopServices() {
        mContext.unbindService(mConnectionToLogger);
        mContext.stopService(new Intent(mContext, DebugViewService.class));
        mContext.stopService(new Intent(mContext, LoggerService.class));
        mServicesStopping = false;
        mServicesStarted = false;
        // When a disconnection occurs, LoggerService stops after SERVICE_STOP_DELAY_MILLS
        // is elapsed. If next connection occurs immediately, the callback for starting
        // LoggerService/SneConnectedScore can be missed.
        // So re-registration is needed to ensure get the callback in such a case.
        if (mStarted) {
            mConnectivityManager.unregisterNetworkCallback(mDefaultNetworkCallback);
            mConnectivityManager.registerDefaultNetworkCallback(mDefaultNetworkCallback, mHandler);
        }
    }

    private void updateFLSystemConnectedFeatureStatus() {
        if (mFLSystemManager != null) {
            mFLSystemManager.setFeatureEnabled(FEATURE_CONNECTED,
                    SneUtils.isSmartNetworkConnectedSettingsEnabled());
        }
    }

    /**
     * This class is responsible for:
     * 1. Sending the collected data to IDD daemon
     * 2. Storing the collected data as training data
     */
    @VisibleForTesting
    static class CollectedDataHandler implements StatsUpdateListener {

        private static final String TAG = CollectedDataHandler.class.getSimpleName();

        private static final long CONNECTION_DURATION_THRESHOLD_MSEC = 90 * 1000; // 90 secs
        private static final long RECONNECTION_PERIOD_THRESHOLD_MSEC = 90 * 1000; // 90 secs

        private final Context mContext;
        private final Predictor mPredictor;

        @Nullable
        private SneWifiEvent mPreviousWifiData;
        private long mPreviousDisconnectedTimeMs;
        @Nullable
        private PredictionResult mPreviousPredictionResult;

        public CollectedDataHandler(@NonNull Context context) {
            mContext = context;
            FLSystemManager flSystemManager =
                    ((SneApplication) mContext.getApplicationContext()).getFLSystemManager();
            mPredictor = flSystemManager != null ? flSystemManager.getPredictor(
                    flSystemManager.FEATURE_CONNECTED) : null;
        }

        @Override
        public void onAllStatsCollected(@NonNull SneWifiEvent wifiData, long connectedTimeMs,
                long disconnectedTimeMs, @Nullable Object inferenceData) {
            if (mPreviousWifiData != null && mPreviousPredictionResult != null
                    && mPreviousPredictionResult.isScored()) {
                boolean wantToKeep = doesUserWantToKeepWifi(wifiData, connectedTimeMs,
                        mPreviousDisconnectedTimeMs);
                Log.v(TAG, "doesUserWantToKeepWifi: " + wantToKeep);
                // Add info of user intention inference session and label
                UserWifiPreferenceInfo userWifiPreferenceInfo =
                        UserWifiPreferenceInfo.newBuilder()
                                .setDataStoreSession(!mPreviousPredictionResult.isScoreUsable())
                                .setModelId(mPreviousPredictionResult.getModelVersion())
                                .setReconnection(wantToKeep)
                                .build();
                mPreviousWifiData = mPreviousWifiData.toBuilder()
                        .setLoggedInfo(mPreviousWifiData.getLoggedInfo().toBuilder()
                                .setUserWifiPreferenceInfo(userWifiPreferenceInfo))
                        .build();
                // Store the collected data as training data
                if (mPredictor != null) {
                    mPredictor.addTrainingData(mPreviousPredictionResult, wantToKeep ? 1 : 0);
                }
            } else {
                Log.v(TAG,
                        "No add training data: previous wifiData or predictionResult is missing");
            }

            // Send the collected data to IDD daemon
            if (LoggerUtils.isLoggingAllowed() && mPreviousWifiData != null) {
                IddWrapper.addEvent(mContext, mPreviousWifiData);

                // Update daily logged size
                int size = mPreviousWifiData.getSerializedSize();
                long total = PreferenceAccessor.getDailyUpdateSize() + size;
                PreferenceAccessor.setDailyUpdateSize(total);
                Log.v(TAG, "Logged data has been sent to IDD (size: " + size + ", daily total: "
                        + total + ")");
            }

            // Keep for next session
            mPreviousWifiData = wifiData;
            mPreviousDisconnectedTimeMs = disconnectedTimeMs;
            mPreviousPredictionResult = (PredictionResult) inferenceData;
        }

        /**
         * Calculates the label for the user intention model.
         */
        @VisibleForTesting
        boolean doesUserWantToKeepWifi(SneWifiEvent wifiData, long connectedTimeMs,
                long previousDisconnectedTimeMs) {
            long connectionDuration = wifiData.getLoggedInfo().getLoggedDuration();
            long reconnectionPeriod = connectedTimeMs - previousDisconnectedTimeMs;
            return (connectionDuration > CONNECTION_DURATION_THRESHOLD_MSEC)
                    && (reconnectionPeriod < RECONNECTION_PERIOD_THRESHOLD_MSEC);
        }
    }
}
