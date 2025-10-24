/*
 * Copyright 2018, 2019, 2020, 2021, 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.connected;

import static com.sonymobile.smartnetworkengine.Constants.AVOID_FLAPPING_RSSI_RANGE;
import static com.sonymobile.smartnetworkengine.Constants.CELL_NETWORK_TYPE_LTE;
import static com.sonymobile.smartnetworkengine.Constants.CELL_NETWORK_TYPE_LTE_NR_CONNECTED;
import static com.sonymobile.smartnetworkengine.Constants.CELL_NETWORK_TYPE_LTE_NR_NOT_RESTRICTED;
import static com.sonymobile.smartnetworkengine.Constants.CELL_NETWORK_TYPE_NR;
import static com.sonymobile.smartnetworkengine.Constants.NN_LTE;
import static com.sonymobile.smartnetworkengine.Constants.NN_LTE_NR_CONNECTED;
import static com.sonymobile.smartnetworkengine.Constants.NN_LTE_NR_NOT_RESTRICTED;
import static com.sonymobile.smartnetworkengine.Constants.NN_NR;
import static com.sonymobile.smartnetworkengine.Constants.NN_PRIMARY;
import static com.sonymobile.smartnetworkengine.Constants.NN_SECONDARY;
import static com.sonymobile.smartnetworkengine.Constants.PROP_ALWAYS_PREFER_NON_WIFI;
import static com.sonymobile.smartnetworkengine.Constants.PROP_NN_CELL_INFERENCE_RESULT_OVERRIDE;
import static com.sonymobile.smartnetworkengine.Constants.RSSI_CAP_THRESHOLD;
import static com.sonymobile.smartnetworkengine.Constants.WIFI_TRANSITION_SCORE;
import static com.sonymobile.smartnetworkengine.SneUtils.isDebugBuild;

import android.annotation.SuppressLint;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.os.SystemProperties;
import android.telephony.TelephonyManager;

import androidx.annotation.MainThread;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;

import com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData.SneRuntimeStats;
import com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData.SneWifiEvent;
import com.sonymobile.smartnetworkengine.DefaultNetworkController;
import com.sonymobile.smartnetworkengine.SneApplication;
import com.sonymobile.smartnetworkengine.connected.logger.LoggerService;
import com.sonymobile.smartnetworkengine.event.EventForwarder;
import com.sonymobile.smartnetworkengine.fls.FLSystemManager;
import com.sonymobile.smartnetworkengine.fls.Predictor;
import com.sonymobile.smartnetworkengine.util.Log;
import com.sonymobile.smartnetworkengine.util.NeuralNetworkConfiguration;

import java.util.ArrayList;
import java.util.List;

/**
 * This class controls default network only after Wi-Fi initially becoming default (and validated).
 */
public class SneConnectedScore {

    private static final String TAG = SneConnectedScore.class.getSimpleName();

    private static final long DURATION_TIMER_MSEC = 9000;

    private final Context mContext;

    // NOTE: DefaultNetworkController is allowed to be used only between start() and stop(),
    // since it does not support multi-client.
    private final DefaultNetworkController mDefaultNetworkController;

    @Nullable
    private final Predictor mPredictor;

    private final EventForwarder mEventForwarder;

    private final TelephonyManager mTelephonyManager;

    private final InferenceThreshold mInferenceThreshold;

    private boolean mStarted;

    @Nullable
    private LoggerService mLoggerService;

    @Nullable
    private LoggerService.SessionInfo mSessionInfo;

    private final List<SneRuntimeStats> mRuntimeStatsList = new ArrayList<>(
            Preprocessor.MAX_NUM_OF_STATS_SAMPLES);

    private long mConnectedTime;

    private long mPreviousDisconnectedTime;

    @Nullable
    private SneWifiEvent mPreviousWifiEvent;

    @VisibleForTesting
    final InferenceResultInjectorImpl mInjector = new InferenceResultInjectorImpl();

    private final ServiceConnection mConnectionToLogger = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder service) {
            mLoggerService = ((LoggerService.LocalBinder) service).getService();
            mLoggerService.setInferenceResultInjector(mInjector);
            mLoggerService.registerStatsUpdateListener(mInjector);
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            mLoggerService = null;
        }
    };

    SneConnectedScore(@NonNull Context context, @NonNull DefaultNetworkController controller) {
        mContext = context;
        mDefaultNetworkController = controller;
        FLSystemManager flSystemManager = ((SneApplication) context.getApplicationContext())
                .getFLSystemManager();
        mPredictor = flSystemManager != null ? flSystemManager.getPredictor(
                FLSystemManager.FEATURE_CONNECTED) : null;
        mEventForwarder = ((SneApplication) context.getApplicationContext()).getEventForwarder();
        mTelephonyManager = (TelephonyManager) context.getSystemService(Context.TELEPHONY_SERVICE);
        mInferenceThreshold = new InferenceThreshold(context);
    }

    @SuppressLint("MissingPermission")
    @MainThread
    public void start() {
        if (!mStarted) {
            Log.v(TAG, "started");
            mConnectedTime = System.currentTimeMillis();
            mContext.bindService(new Intent(mContext, LoggerService.class), mConnectionToLogger, 0);
            mStarted = true;
        }
    }

    @MainThread
    public void stop() {
        if (mStarted) {
            Log.v(TAG, "stopped");
            if (mLoggerService != null) {
                // No need to call |unregisterStatsUpdateListener| as callback is still needed
                mLoggerService.setInferenceResultInjector(null);
                mLoggerService = null;
            }
            mContext.unbindService(mConnectionToLogger);
            mDefaultNetworkController.preferWifiNetwork();
            mInjector.mWifiPreferred = true; // Reset default network preference
            mSessionInfo = null;
            mRuntimeStatsList.clear();
            if (mPredictor != null) {
                mPredictor.reset();
            }
            mStarted = false;
        }
    }

    private boolean isInferenceResultOverThreshold(SneRuntimeStats stats) {
        float primaryResult = stats.getInferenceResult().getPrimary();
        float secondaryResult = stats.getInferenceResult().getSecondary();
        float primaryThreshold = mInferenceThreshold.primary;
        float secondaryThreshold = mInferenceThreshold.secondary;
        int velocityBasedScore = stats.getInferenceResult().getVelocityBasedScore();

        // Multiply move ratio by threshold when moving.
        if (stats.getSensorData().getIsMoving()) {
            primaryThreshold *= mInferenceThreshold.primaryMoveRatio;
            secondaryThreshold *= mInferenceThreshold.secondaryMoveRatio;
        }
        Log.v(TAG, "active inference thresholds: " + primaryThreshold + ", " + secondaryThreshold);

        return (primaryResult > primaryThreshold) || (secondaryResult > secondaryThreshold) ||
                (velocityBasedScore < WIFI_TRANSITION_SCORE);
    }

    /**
     * Check cellular inference result for cellular quality
     *
     * @param stats SneRuntimeStats passed by LoggerService
     * @return true: cellular quality is bad, false: others
     */
    private boolean isCellularNetworkBad(SneRuntimeStats stats) {
        int networkType = stats.getCellularInfo().getNetworkType();
        float inferenceResult = stats.getInferenceResult().getCellular();
        float threshold;
        switch (networkType) {
            case CELL_NETWORK_TYPE_LTE:
                threshold = mInferenceThreshold.lte;
                break;
            case CELL_NETWORK_TYPE_NR:
                threshold = mInferenceThreshold.nr;
                break;
            case CELL_NETWORK_TYPE_LTE_NR_CONNECTED:
                threshold = mInferenceThreshold.lteNrConnected;
                break;
            case CELL_NETWORK_TYPE_LTE_NR_NOT_RESTRICTED:
                threshold = mInferenceThreshold.lteNrNotRestricted;
                break;
            default:
                threshold = 0.9f;
                break;
        }

        if (isDebugBuild()) {
            int inferenceResultOverride = SystemProperties.getInt(
                    PROP_NN_CELL_INFERENCE_RESULT_OVERRIDE, 0);
            if (inferenceResultOverride < 100 && inferenceResultOverride > 0) {
                Log.v(TAG, "override cellular inference result, before = " + inferenceResult);
                inferenceResult = inferenceResultOverride / 100f;
            }
        }
        Log.v(TAG, "cellular network type = " + networkType + " inference result = "
                + inferenceResult + " inference threshold = " + threshold);

        return (inferenceResult > threshold);
    }

    static class InferenceThreshold {
        public float primary;
        public float primaryMoveRatio;
        public float secondary;
        public float secondaryMoveRatio;
        public float lte;
        public float nr;
        public float lteNrConnected;
        public float lteNrNotRestricted;

        public InferenceThreshold(@NonNull Context context) {
            // Load Wifi neural network thresholds
            NeuralNetworkConfiguration primaryConfig = new NeuralNetworkConfiguration(context,
                    NN_PRIMARY);
            primary = primaryConfig.getThreshold();
            primaryMoveRatio = primaryConfig.getThresholdMoveRatio();
            NeuralNetworkConfiguration secondaryConfig = new NeuralNetworkConfiguration(context,
                    NN_SECONDARY);
            secondary = secondaryConfig.getThreshold();
            secondaryMoveRatio = secondaryConfig.getThresholdMoveRatio();

            //Load cellular neural network thresholds
            lte = (new NeuralNetworkConfiguration(context, NN_LTE)).getThreshold();
            nr = (new NeuralNetworkConfiguration(context, NN_NR)).getThreshold();
            lteNrConnected = (new NeuralNetworkConfiguration(context,
                    NN_LTE_NR_CONNECTED)).getThreshold();
            lteNrNotRestricted = (new NeuralNetworkConfiguration(context,
                    NN_LTE_NR_NOT_RESTRICTED)).getThreshold();
        }
    }

    @VisibleForTesting
    @MainThread
    class InferenceResultInjectorImpl implements LoggerService.InferenceResultInjector,
            LoggerService.StatsUpdateListener {
        private boolean mWifiPreferred = true;
        private int mRssiCapThresholdToWifi;

        @Override
        public void onSessionInfoUpdate(@NonNull LoggerService.SessionInfo sessionInfo) {
            Log.v(TAG, "onSessionInfoUpdate: " + sessionInfo);
            if (mSessionInfo != null && !sessionInfo.getCurrentBssid().equals(
                    mSessionInfo.getCurrentBssid())) {
                // Wifi roaming happens so the data for the intention feature needs to be cleared
                mRuntimeStatsList.clear();
            }
            mSessionInfo = sessionInfo;
        }

        /**
         * This callback method does the followings:
         * 1. Determine which network should be a default from the stats and inference results
         * 2. Perform FL prediction if necessary and pass its result to the logger
         */
        @Override
        public LoggerService.InferenceResultInfo onInferenceResultRequested(
                @NonNull SneRuntimeStats runtimeStats) {
            LoggerService.InferenceResultInfo.Builder builder = null;
            // If debug property is enabled, force to call sendPrediction().
            if (isDebugBuild() && SystemProperties.getBoolean(PROP_ALWAYS_PREFER_NON_WIFI, false)) {
                mDefaultNetworkController.preferNonWifiNetwork(DURATION_TIMER_MSEC);
            } else {
                int rssi = runtimeStats.getWifiInfo().getRssi();
                if (mWifiPreferred) { // Default network is probably Wifi
                    if (mRuntimeStatsList.size() >= Preprocessor.MAX_NUM_OF_STATS_SAMPLES) {
                        mRuntimeStatsList.remove(0); // remove the first sample
                    }
                    mRuntimeStatsList.add(runtimeStats);
                    if (isInferenceResultOverThreshold(runtimeStats)
                            && !isCellularNetworkBad(runtimeStats)
                            && rssi <= RSSI_CAP_THRESHOLD
                            && !mTelephonyManager.isNetworkRoaming()
                            && (mSessionInfo != null && !mSessionInfo.isHomeNetwork()
                            && !mSessionInfo.isUserSelected())) {
                        boolean toNonWifiNetwork = true;
                        if (mPredictor != null) {
                            List<List<Float>> features = Preprocessor.extractFeatures(
                                    mRuntimeStatsList, mSessionInfo, mConnectedTime,
                                    mPreviousDisconnectedTime, mPreviousWifiEvent);
                            if (features != null) {
                                // Run inference for the intention feature
                                Predictor.PredictionResult result = mPredictor.predict2d(features,
                                        mSessionInfo.getCurrentBssid());
                                Log.v(TAG, "Predictor#predict result: " + result);
                                // Fill in the inference result info to be returned to the logger
                                builder = LoggerService.InferenceResultInfo.builder()
                                        .userWifiPreferenceInferenceData(result)
                                        .userWifiPreferenceScoreUsable(result.isScoreUsable());
                                if (result.isScored()) {
                                    builder.userWifiPreferenceScore(result.getScore());
                                }
                                // Check the inference result
                                if (result.isScoreUsable() && result.aboveScoreThreshold()) {
                                    // User does not want to switch
                                    toNonWifiNetwork = false;
                                }
                            }
                        }
                        if (toNonWifiNetwork) {
                            // To non-Wifi network
                            mDefaultNetworkController.preferNonWifiNetwork(DURATION_TIMER_MSEC);
                            mRssiCapThresholdToWifi = rssi + AVOID_FLAPPING_RSSI_RANGE;
                            mWifiPreferred = false;
                        }
                    }
                } else { // Default network is probably non-Wifi (Mobile)
                    if (!isInferenceResultOverThreshold(runtimeStats)
                            && rssi >= mRssiCapThresholdToWifi) {
                        // To Wifi network
                        mRuntimeStatsList.clear();
                        mWifiPreferred = true;
                    } else {
                        // Keep non-Wifi network
                        mDefaultNetworkController.preferNonWifiNetwork(DURATION_TIMER_MSEC);
                    }
                }
                mEventForwarder.noteNetworkDecisionMade(mWifiPreferred, runtimeStats);
            }
            return builder != null ? builder.build() : null;
        }

        @Override
        public void onAllStatsCollected(@NonNull SneWifiEvent wifiEvent, long connectedTimeMs,
                long disconnectedTimeMs, @Nullable Object inferenceData) {
            mPreviousWifiEvent = wifiEvent;
            mPreviousDisconnectedTime = disconnectedTimeMs;
        }
    }
}
