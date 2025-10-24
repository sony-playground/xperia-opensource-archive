/*
 * Copyright 2017, 2018, 2019, 2020, 2021, 2022, 2023, 2024 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.connected.logger;

import static com.sonymobile.smartnetworkengine.Constants.CELL_NETWORK_TYPE_LTE;
import static com.sonymobile.smartnetworkengine.Constants.CELL_NETWORK_TYPE_LTE_NR_CONNECTED;
import static com.sonymobile.smartnetworkengine.Constants.CELL_NETWORK_TYPE_LTE_NR_NOT_RESTRICTED;
import static com.sonymobile.smartnetworkengine.Constants.CELL_NETWORK_TYPE_NR;
import static com.sonymobile.smartnetworkengine.Constants.SETTINGS_SMARTNET_CONNECTED_ENABLED;
import static com.sonymobile.smartnetworkengine.Constants.WIFI_PPS_THRESHOLD;
import static com.sonymobile.smartnetworkengine.Constants.WIFI_RSSI_THRESHOLD;
import static com.sonymobile.smartnetworkengine.Constants.WIFI_RSSI_THRESHOLD_6GHZ_AOSP;
import static com.sonymobile.smartnetworkengine.Constants.WIFI_TRANSITION_SCORE;
import static com.sonymobile.smartnetworkengine.SneUtils.isDebugBuild;
import static com.sonymobile.smartnetworkengine.connected.logger.collector.WifiBufferCongestionInfoCollector.BufferCongestionInfo;
import static com.sonymobile.smartnetworkengine.connected.logger.collector.WifiLinkLayerStatsCollector.ContentionInfo;
import static com.sonymobile.smartnetworkengine.connected.logger.collector.WifiLinkLayerStatsCollector.RadioTimeInfo;

import android.annotation.SuppressLint;
import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.database.ContentObserver;
import android.net.TrafficStats;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiEnterpriseConfig;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.net.wifi.WifiUsabilityStatsEntry;
import android.os.Binder;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.os.PowerManager;
import android.os.ServiceManager;
import android.provider.Settings;
import android.telephony.CellSignalStrengthLte;
import android.telephony.CellSignalStrengthNr;
import android.telephony.PhysicalChannelConfig;
import android.telephony.TelephonyManager;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData;
import com.sonymobile.smartnetworkengine.SneApplication;
import com.sonymobile.smartnetworkengine.SneUtils;
import com.sonymobile.smartnetworkengine.WifiExtController;
import com.sonymobile.smartnetworkengine.connected.logger.collector.SensorCollector;
import com.sonymobile.smartnetworkengine.connected.logger.collector.SupplicantStaIfaceHal;
import com.sonymobile.smartnetworkengine.connected.logger.collector.SupplicantStaIfaceHalAidlImpl;
import com.sonymobile.smartnetworkengine.connected.logger.collector.SupplicantStaIfaceHalHidlImpl;
import com.sonymobile.smartnetworkengine.connected.logger.collector.WifiBufferCongestionInfoCollector;
import com.sonymobile.smartnetworkengine.connected.logger.collector.WifiLinkLayerStatsCollector;
import com.sonymobile.smartnetworkengine.connected.prediction.PredictionManager;
import com.sonymobile.smartnetworkengine.connected.prediction.VelocityBasedScore;
import com.sonymobile.smartnetworkengine.event.EventForwarder;
import com.sonymobile.smartnetworkengine.util.HomeNetworkDetector;
import com.sonymobile.smartnetworkengine.util.Log;
import com.sonymobile.smartnetworkengine.util.WifiChecker;

import java.util.Arrays;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Set;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class LoggerService extends Service {

    private static final String TAG = LoggerService.class.getSimpleName();

    private static final String IDD_PROBE_VERSION = "2.2.1";

    private final IBinder mBinder = new LocalBinder();

    public class LocalBinder extends Binder {
        public LoggerService getService() {
            return LoggerService.this;
        }
    }

    @Nullable
    private EventForwarder mEventForwarder;
    private PredictionManager mSNPManager;
    private VelocityBasedScore mVelocityBasedScore;
    private final Handler mLoggingHandler = new Handler();
    private final Runnable mLoggingRunnable = new LoggingRunnable();
    private SensorCollector mSensorCollector;
    private WifiLinkLayerStatsCollector mWifiLinkLayerStatsCollector;
    private WifiBufferCongestionInfoCollector mWifiBufferCongestionInfoCollector;
    private MovingDetector mMovingDetector;
    private CellInfoMonitor mCellInfoMonitor;

    private final Set<StatsUpdateListener> mStatsUpdateListeners = new HashSet<>();
    @Nullable
    private InferenceResultInjector mInferenceResultInjector;

    private static SupplicantStaIfaceHal sSupplicantStaIfaceHal = null;

    private final SupplicantStaIfaceHal.SupplicantListener mSupplicantListener =
            new SupplicantStaIfaceHal.SupplicantListener() {
        @Override
        public void onDisconnected(boolean locallyGenerated, int reasonCode, String ifaceName) {
            if (mWifiInterface != null && mWifiInterface.equals(ifaceName)) {
                Log.v(TAG, "SupplicantListener onDisconnected");
                mSupplicantLocallyGenerated = locallyGenerated;
                mSupplicantReasonCode = reasonCode;
            }
        }
    };

    private WifiExtController mWifiExtController;
    private WifiManager mWiFiManager;
    private WifiInfo mWifiInfo;
    private WifiInfo mPrevWifiInfo;
    private WifiUsabilityStatsListener mWifiUsabilityStatsListener;
    private ExecutorService mWifiUsabilityStatsListenerExecutor;
    private TelephonyManager mTelephonyManager;
    private String mWifiInterface;

    private static final int MAX_LOGGING_SEC = isDebugBuild() ? 1800 : 120;
    private static final int LOGGING_INTERVAL_SEC = 3;
    private static final int WIFIINFO_LOGGING_INTERVAL_MS = (LOGGING_INTERVAL_SEC * 1000);
    private static final float INFERENCE_RESULT_INVALID = -1f;
    private static final float INFERENCE_RESULT_INVALID_ROAM = -2f;
    private static final float INFERENCE_RESULT_INVALID_INPUT = -3f;
    private static final int KEEPING_INFERENCE_RESULT_DIGIT = 4;
    private static final int KEEPING_SENSOR_ACCEL_DECIMAL_DIGIT = 1;
    private static final int OUTLIER_THRESHOLD_COUNTER = 100000;
    private static final int CELLULAR_RSRP_CAP = -120;
    private static final int MIN_24GHz_FREQ = 2410;
    private static final int MAX_24GHz_FREQ = 2495;
    private static final int BASE_24GHz_FREQ = 2407;
    private static final int MIN_5GHz_FREQ = 5180;
    private static final int MAX_5GHz_FREQ = 5875;
    private static final int BASE_5GHz_FREQ = 5000;

    private boolean mScreenOff;
    private boolean mIsSoftApStarted;

    private long mTmpTxPkts;
    private long mTmpRxPkts;
    private long mDeltaTxPkts;
    private long mDeltaRxPkts;
    private long mTmpTxBad;
    private long mTmpTxRetries;
    private long mTmpTxSuccess;
    private long mTmpRxSuccess;
    private boolean mSupplicantLocallyGenerated;
    private int mSupplicantReasonCode;
    private int mWifiEapMethod = WifiEnterpriseConfig.Eap.NONE;
    private int mWifiSecurityType = -1;
    private int mWifiUsabilityStatsSeqNumBeforeScreenOff = -1;
    private int mSneAospScore;
    private boolean mIsHomeNetwork = false;
    private boolean mIsUserSelected = false;
    private String mSsid = "";
    private String mStartBssid = "";
    private String mEndBssid = "";

    private long mLogStartTime;
    private long mLogEndTime;

    private Object mUserWifiPreferenceInferenceData;

    private Queue<WifiPredictionData.SneRuntimeStats> mRuntimeStatsQueue = new LinkedList<>();

    private static final String STAMINA_MODE_STATUS = "somc.ultrastamina_mode";

    public enum StopReason {
        // NOTE: SNE API side needs to be updated as well when adding/removing this enum constant.
        NORMAL,
        SCREENOFF,
        SHUTDOWN,
        SCOREOFF,
        VOICECALL, // This value is no longer used, but it is reserved for preventing conflict.
        SOFTAP_STARTED,
        STASTA_CONCURRENCY,
        MLO_CONNECTION
    }

    enum LoggingTiming {
        DISCONNECT(0),
        IP_LINK_VERIFY_TIMEOUT(1); // This value is no longer used.

        private int value;

        LoggingTiming(int value) {
            this.value = value;
        }

        private int getValue() {
            return this.value;
        }
    }

    private boolean mIsSettingsEnabled = false;
    private boolean mIsShutdownProceeding = false;
    private boolean mIsAlreadyLogging = false;
    private boolean mIsInitialLogging = true;
    private boolean mIsInitialLoggingAfterWifiConnection = true;
    private boolean mHasDetectedInvalidPredictionInput = false;
    private boolean mHasDetectedMloConnection = false;

    private ContentObserver mObserver = new ContentObserver(new Handler()) {
        @Override
        public void onChange(boolean selfChange) {
            super.onChange(selfChange);
            mIsSettingsEnabled = SneUtils.isSmartNetworkConnectedSettingsEnabled();
            if (mIsSettingsEnabled) {
                if (mIsAlreadyLogging) {
                    // When settings value of SNE is enabled after logger is started, it should
                    // reset.
                    // TODO: This condition is too complicated, so it should consider refactoring.
                    try {
                        mSNPManager.initializeNeuralNetworks();
                    } catch (RuntimeException e) {
                        Log.e(TAG, "Failed to initialize NeuralNetworks: " + e);
                        return;
                    }
                }
                startLoggingIfNeeded();
            } else if (!LoggerUtils.isLoggingAllowed()) {
                stopLogging(StopReason.SCOREOFF);
            }
        }
    };

    class LoggingRunnable implements Runnable {
        @Override
        public void run() {
            if (shouldDoLoggingProcess()) {
                loggingRuntimeData();
                mLoggingHandler.postDelayed(this, WIFIINFO_LOGGING_INTERVAL_MS);
            }
        }
    }

    @Override
    public IBinder onBind(Intent intent) {
        return mBinder;
    }

    @Override
    public boolean onUnbind(Intent intent) {
        return super.onUnbind(intent);
    }

    @Override
    public void onCreate() {
        Log.v(TAG, "LoggerService is started.");
        SneApplication sneApplication = (SneApplication) getApplicationContext();
        mEventForwarder = sneApplication.getEventForwarder();
        mWifiExtController = sneApplication.getWifiExtController();
        mIsUserSelected = mWifiExtController.isUserSelected();
        mWifiInterface = mWifiExtController.getPrimaryInterfaceName();

        PowerManager pm = (PowerManager) getSystemService(POWER_SERVICE);
        getContentResolver().registerContentObserver(
                Settings.Global.getUriFor(SETTINGS_SMARTNET_CONNECTED_ENABLED), false, mObserver);
        mIsSettingsEnabled = SneUtils.isSmartNetworkConnectedSettingsEnabled();
        mSNPManager = new PredictionManager(getApplicationContext());
        mVelocityBasedScore = new VelocityBasedScore();
        mLogStartTime = System.currentTimeMillis();
        mWiFiManager = (WifiManager) getSystemService(WIFI_SERVICE);
        mWifiUsabilityStatsListener = new WifiUsabilityStatsListener();
        mWifiUsabilityStatsListenerExecutor = Executors.newSingleThreadExecutor();
        mWiFiManager.addOnWifiUsabilityStatsListener(
                mWifiUsabilityStatsListenerExecutor, mWifiUsabilityStatsListener);

        mTelephonyManager = (TelephonyManager) getSystemService(TELEPHONY_SERVICE);

        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(Intent.ACTION_SCREEN_ON);
        intentFilter.addAction(Intent.ACTION_SCREEN_OFF);
        intentFilter.addAction(Intent.ACTION_SHUTDOWN);
        registerReceiver(mSettingsReceiver, intentFilter);
        registerReceiver(mWifiSoftApReceiver,
                new IntentFilter(WifiManager.WIFI_AP_STATE_CHANGED_ACTION));
        mIsSoftApStarted = mWiFiManager.isWifiApEnabled();
        mScreenOff = !pm.isInteractive();

        if (sSupplicantStaIfaceHal == null) {
            if (isAidlSupport()) {
                sSupplicantStaIfaceHal = new SupplicantStaIfaceHalAidlImpl();
            } else {
                sSupplicantStaIfaceHal = new SupplicantStaIfaceHalHidlImpl();
            }
            sSupplicantStaIfaceHal.initialize();
        }
        sSupplicantStaIfaceHal.setListener(mSupplicantListener);
        mSensorCollector = new SensorCollector(this);
        mWifiLinkLayerStatsCollector = new WifiLinkLayerStatsCollector(this, mWifiInterface);
        mWifiBufferCongestionInfoCollector = new WifiBufferCongestionInfoCollector(mWifiInterface);
        mMovingDetector = new MovingDetector();
        mCellInfoMonitor = new CellInfoMonitor(this);
        mWifiInfo = mWiFiManager.getConnectionInfo();
        if (mWifiInfo != null && mWifiInfo.getBSSID() != null) {
            mSsid = WifiInfo.sanitizeSsid(mWifiInfo.getSSID());
            mStartBssid = mEndBssid = mWifiInfo.getBSSID();
        }
        startLoggingIfNeeded();
        super.onCreate();
    }

    @Override
    public int onStartCommand(Intent intent, int i, int i1) {
        // If this service's process is killed while it is started, don't recreate until a future
        // explicit call to startService. This is required to avoid unexpected behavior which may
        // happen if this service is started prior to CoreService.
        return START_NOT_STICKY;
    }

    @Override
    public void onDestroy() {
        if (!mScreenOff && !mIsSoftApStarted) {
            StopReason reason = StopReason.SHUTDOWN;
            if (mWifiExtController.isStaStaConcurrent()) {
                reason = StopReason.STASTA_CONCURRENCY;
            } else if (mHasDetectedMloConnection) {
                reason = StopReason.MLO_CONNECTION;
            } else if (!mIsShutdownProceeding) {
                reason = StopReason.NORMAL;
                if (mIsAlreadyLogging) {
                    notifyAllStatsCollected(LoggingTiming.DISCONNECT);
                }
            }
            stopLogging(reason);
        }
        sSupplicantStaIfaceHal.setListener(null);
        getContentResolver().unregisterContentObserver(mObserver);
        unregisterReceiver(mSettingsReceiver);
        unregisterReceiver(mWifiSoftApReceiver);
        mWiFiManager.removeOnWifiUsabilityStatsListener(mWifiUsabilityStatsListener);
        mWifiUsabilityStatsListenerExecutor.shutdown();
        mWifiUsabilityStatsListenerExecutor = null;
        super.onDestroy();
    }

    public void registerStatsUpdateListener(@NonNull StatsUpdateListener listener) {
        mLoggingHandler.post(() -> mStatsUpdateListeners.add(listener));
    }

    public void unregisterStatsUpdateListener(@NonNull StatsUpdateListener listener) {
        mLoggingHandler.post(() -> mStatsUpdateListeners.remove(listener));
    }

    public void setInferenceResultInjector(@Nullable InferenceResultInjector injector) {
        mLoggingHandler.post(() -> {
            mInferenceResultInjector = injector;
            if (injector != null) {
                // Notify upon registration as caller could register late
                notifySessionInfoUpdate();
            }
        });
    }

    private void notifySessionInfoUpdate() {
        if (mInferenceResultInjector != null) {
            mInferenceResultInjector.onSessionInfoUpdate(
                    SessionInfo.builder()
                            .currentBssid(mEndBssid)
                            .wifiSecurityType(mWifiSecurityType)
                            .homeNetwork(mIsHomeNetwork)
                            .userSelected(mIsUserSelected)
                            .build());
        }
    }

    private boolean shouldDoLoggingProcess() {
        mPrevWifiInfo = mWifiInfo;
        mWifiInfo = mWiFiManager.getConnectionInfo();
        return mWifiInfo != null && mWifiInfo.getIpAddress() != 0 && mWifiInfo.getBSSID() != null
                && !mScreenOff && !mIsSoftApStarted
                && (LoggerUtils.isLoggingAllowed() || mIsSettingsEnabled);
    }

    /**
     * This checks whether prediction input such as frequency etc, includes invalid value or not.
     * If it is once invalid, this keeps returning false(invalid) until next WiFi connection.
     * As an exception, if initial input after Wi-Fi connection is invalid, checks second one.
     */
    private boolean detectInvalidPredictionInput() {
        boolean isInvalid = false;
        if (!mHasDetectedMloConnection && WifiChecker.isMloConnection(mWifiInfo)) {
            mHasDetectedMloConnection = true;
        }
        if (!mHasDetectedInvalidPredictionInput) {
            ContentionInfo contention = mWifiLinkLayerStatsCollector.getContentionInfo();
            RadioTimeInfo radioTime = mWifiLinkLayerStatsCollector.getRadioTimeInfo();
            if (mWifiInfo.getFrequency() <= 0 || mWifiInfo.getLinkSpeed() <= 0
                    || mWifiInfo.getRssi() >= 0 || mWifiInfo.getRssi() == WifiInfo.INVALID_RSSI
                    || radioTime.getDeltaTxTime() == RadioTimeInfo.INVALID_VALUE
                    || radioTime.getDeltaRxTime() == RadioTimeInfo.INVALID_VALUE
                    || radioTime.getDeltaOnTimeOnCurrentFreq() == RadioTimeInfo.INVALID_VALUE
                    || radioTime.getDeltaCcaBusyTimeOnCurrentFreq() == RadioTimeInfo.INVALID_VALUE
                    || contention.getAverageTime() == ContentionInfo.INVALID_VALUE
                    || contention.getDeltaNumOfSamples() == ContentionInfo.INVALID_VALUE
                    || WifiChecker.is6GHz(mWifiInfo.getFrequency())
                    || mHasDetectedMloConnection) {
                isInvalid = true;

                if (!mIsInitialLoggingAfterWifiConnection) {
                    mHasDetectedInvalidPredictionInput = true;
                }
            }
        }
        return (isInvalid || mHasDetectedInvalidPredictionInput);
    }

    private void startLoggingIfNeeded() {
        Log.v(TAG, "startLoggingIfNeeded()");
        if (!shouldDoLoggingProcess()) {
            Log.v(TAG, "Cannot start logging. isLoggingAllowed:" + LoggerUtils.isLoggingAllowed()
                    + ", mIsSettingsEnabled:" + mIsSettingsEnabled);
            return;
        }

        if (!mIsAlreadyLogging) {
            try {
                mSNPManager.initializeNeuralNetworks();
            } catch (RuntimeException e) {
                Log.e(TAG, "Failed to initialize NeuralNetworks: " + e);
                return;
            }
            mSensorCollector.start();
            mCellInfoMonitor.start();
            mTmpTxPkts = TrafficStats.getTxPackets(mWifiInterface);
            mTmpRxPkts = TrafficStats.getRxPackets(mWifiInterface);
            mTmpTxBad = mWifiUsabilityStatsListener.txBad;
            mTmpTxRetries = mWifiUsabilityStatsListener.txRetries;
            mTmpTxSuccess = mWifiUsabilityStatsListener.txSuccess;
            mTmpRxSuccess = mWifiUsabilityStatsListener.rxSuccess;
            loggingWifiConfiguration();
            mLoggingHandler.post(mLoggingRunnable);
            mIsInitialLogging = true;
            mIsAlreadyLogging = true;
            mSneAospScore = 60;

            notifySessionInfoUpdate();
            mEventForwarder.noteLoggingStart();
        }
    }

    private void stopLogging(@NonNull StopReason reason) {
        if (!mIsAlreadyLogging) {
            Log.v(TAG, "logging has already stopped");
            return;
        }
        Log.v(TAG, "stopLogging() - Reason: " + reason);
        mRuntimeStatsQueue.clear();
        mSensorCollector.stop();
        mCellInfoMonitor.stop();
        mMovingDetector.reset();
        mLoggingHandler.removeCallbacksAndMessages(null);
        mIsAlreadyLogging = false;
        mVelocityBasedScore.reset();

        mEventForwarder.noteLoggingStop(reason);
    }

    @SuppressLint("MissingPermission")
    private void loggingRuntimeData() {
        // Traffic Stats
        long baseTxPkts = mTmpTxPkts;
        long baseRxPkts = mTmpRxPkts;

        mTmpTxPkts = TrafficStats.getTxPackets(mWifiInterface);
        mTmpRxPkts = TrafficStats.getRxPackets(mWifiInterface);
        mDeltaTxPkts = mTmpTxPkts - baseTxPkts;
        mDeltaRxPkts = mTmpRxPkts - baseRxPkts;

        // WifiInfo
        int rssi = mWifiInfo.getRssi();
        long baseTxBad = mTmpTxBad;
        long baseTxRetries = mTmpTxRetries;
        long baseTxSuccess = mTmpTxSuccess;
        long baseRxSuccess = mTmpRxSuccess;
        mTmpTxBad = mWifiUsabilityStatsListener.txBad;
        mTmpTxRetries = mWifiUsabilityStatsListener.txRetries;
        mTmpTxSuccess = mWifiUsabilityStatsListener.txSuccess;
        mTmpRxSuccess = mWifiUsabilityStatsListener.rxSuccess;
        long deltaTxBad = getDifferentialValue(mTmpTxBad, baseTxBad);
        long deltaTxRetries = getDifferentialValue(mTmpTxRetries, baseTxRetries);
        long deltaTxSuccess = getDifferentialValue(mTmpTxSuccess, baseTxSuccess);
        long deltaRxSuccess = getDifferentialValue(mTmpRxSuccess, baseRxSuccess);
        boolean is6GHz = WifiChecker.is6GHz(mWifiInfo.getFrequency());

        mWifiLinkLayerStatsCollector.refresh();
        ContentionInfo contentionInfo = mWifiLinkLayerStatsCollector.getContentionInfo();
        RadioTimeInfo radioTimeInfo = mWifiLinkLayerStatsCollector.getRadioTimeInfo();

        mWifiBufferCongestionInfoCollector.refresh();
        BufferCongestionInfo bufferCongestionInfo =
                mWifiBufferCongestionInfoCollector.getBufferCongestionInfo();

        // Sensor Acceleration
        float acceleration = removeDecimalPlaces(mSensorCollector.getAcceleration(),
                KEEPING_SENSOR_ACCEL_DECIMAL_DIGIT);
        // Sensor - moving detection
        boolean moving = mMovingDetector.update(acceleration);
        Log.v(TAG, "moving detection:" + moving + ", acceleration:" + acceleration);

        // Reset NN when Wi-Fi roaming is detected.
        final String preBssid = (mPrevWifiInfo != null) ? mPrevWifiInfo.getBSSID() : "";
        final String curBssid = mWifiInfo.getBSSID();
        // update bssid
        mEndBssid = curBssid;
        final boolean isRoaming = !preBssid.equals(curBssid);
        if (isRoaming) {
            Log.v(TAG, "Wi-Fi roaming occurs - bssid(pre=" + preBssid + " cur=" + curBssid + ")");
            mSNPManager.resetRecurrentInputs();
            notifySessionInfoUpdate();
        }

        float[] inferenceResult;
        boolean isInvalidInput = detectInvalidPredictionInput();
        if (mIsSettingsEnabled && !isRoaming && !isInvalidInput) {
            List wifiStatsInputForNnCongestion = Arrays.asList(mWifiInfo.getLinkSpeed(),
                    convertFrequencyToChannel(mWifiInfo.getFrequency()), rssi, deltaTxBad,
                    deltaTxRetries, deltaTxSuccess, deltaRxSuccess, radioTimeInfo.getDeltaTxTime(),
                    radioTimeInfo.getDeltaOnTimeOnCurrentFreq(),
                    radioTimeInfo.getDeltaCcaBusyTimeOnCurrentFreq(),
                    contentionInfo.getAverageTime());

            List wifiStatsInputForNnDisconnection = Arrays.asList(mWifiInfo.getLinkSpeed(),
                    convertFrequencyToChannel(mWifiInfo.getFrequency()), rssi, deltaTxBad,
                    deltaTxRetries, deltaTxSuccess, deltaRxSuccess, radioTimeInfo.getDeltaTxTime(),
                    radioTimeInfo.getDeltaOnTimeOnCurrentFreq(),
                    radioTimeInfo.getDeltaCcaBusyTimeOnCurrentFreq());

            List trafficStatsForNn = Arrays.asList(mDeltaTxPkts, mDeltaRxPkts);

            // Run inference (TODO: Inference should be performed at SneConnectedScore)
            float[] result = mSNPManager.doInference(wifiStatsInputForNnCongestion,
                    wifiStatsInputForNnDisconnection, trafficStatsForNn);
            inferenceResult = new float[]{
                    removeDecimalPlaces(result[0], KEEPING_INFERENCE_RESULT_DIGIT),
                    removeDecimalPlaces(result[1], KEEPING_INFERENCE_RESULT_DIGIT)};
            Log.v(TAG, "score = " + mWifiInfo.getScore());
            Log.v(TAG, "inference results = " + Arrays.toString(inferenceResult));
        } else {
            float invalidResult = INFERENCE_RESULT_INVALID;
            if (mIsSettingsEnabled && isRoaming) {
                // At roaming, skip an inference and set reason to inference result, since Wi-Fi
                // framework could report pre-roaming frequency just after roaming.
                invalidResult = INFERENCE_RESULT_INVALID_ROAM;
            } else if (isInvalidInput) {
                // At detection of invalid input, stop inference and set reason to inference
                // result.
                invalidResult = INFERENCE_RESULT_INVALID_INPUT;
            }
            inferenceResult = new float[]{invalidResult, invalidResult};
        }

        // Update Wifi score
        mVelocityBasedScore.updateUsingWifiInfo(mWifiInfo, System.currentTimeMillis());
        int velocityBasedScore = mVelocityBasedScore.generateScore();
        Log.v(TAG, "velocityBasedScore = " + velocityBasedScore);
        if (mSneAospScore > WIFI_TRANSITION_SCORE
                && velocityBasedScore <= WIFI_TRANSITION_SCORE
                && mWifiInfo.getSuccessfulTxPacketsPerSecond() >= WIFI_PPS_THRESHOLD
                && mWifiInfo.getSuccessfulRxPacketsPerSecond() >= WIFI_PPS_THRESHOLD
        ) {
            velocityBasedScore = WIFI_TRANSITION_SCORE + 1;
        }
        if (mSneAospScore > WIFI_TRANSITION_SCORE && velocityBasedScore <= WIFI_TRANSITION_SCORE) {
            int wifiRssiThreshold = is6GHz ? WIFI_RSSI_THRESHOLD_6GHZ_AOSP : WIFI_RSSI_THRESHOLD;
            // We don't want to trigger a downward breach unless the rssi is
            // below the entry threshold.  There is noise in the measured rssi, and
            // the kalman-filtered rssi is affected by the trend, so check them both.
            if (mVelocityBasedScore.getFilteredRssi() >= wifiRssiThreshold
                    || mWifiInfo.getRssi() >= wifiRssiThreshold) {
                // Stay a notch above the transition score to reduce ambiguity.
                velocityBasedScore = WIFI_TRANSITION_SCORE + 1;
            }
        }
        Log.v(TAG, "velocityBasedScore = " + velocityBasedScore);
        mSneAospScore = velocityBasedScore;

        // Cellular Quality prediction
        int cellNetworkType = mCellInfoMonitor.getNetworkType();
        Log.v(TAG, "sne internal cellular network type = " + cellNetworkType);
        float inferenceResultCell = INFERENCE_RESULT_INVALID;
        List cellInfoForNn = null;
        CellSignalStrengthLte cssLte = mCellInfoMonitor.getCellSignalStrengthLte();
        switch (cellNetworkType) {
            case CELL_NETWORK_TYPE_LTE:
            case CELL_NETWORK_TYPE_LTE_NR_NOT_RESTRICTED:
                // Both LTE and LTE_NR_NOT_RESTRICTED use LTE predictor
                int cellBandwidth = mCellInfoMonitor.getLteCellBandwidthDownlinkKhz();
                if (cssLte != null && cellBandwidth != PhysicalChannelConfig.CELL_BANDWIDTH_UNKNOWN
                        && cssLte.getRsrp() < CELLULAR_RSRP_CAP) {
                    cellInfoForNn = Arrays.asList(cssLte.getRsrp(), cssLte.getRsrq(),
                            cssLte.getRssi(), cssLte.getRssnr(), cellBandwidth);
                }
                break;
            case CELL_NETWORK_TYPE_LTE_NR_CONNECTED:
                CellSignalStrengthNr cssNr = mCellInfoMonitor.getCellSignalStrengthNr();
                if (cssLte != null && cssNr != null && cssNr.getSsRsrp() < CELLULAR_RSRP_CAP) {
                    cellInfoForNn = Arrays.asList(cssLte.getLevel(), cssLte.getRsrp(),
                            cssLte.getRsrq(), cssLte.getRssi(), cssLte.getRssnr(), cssNr.getLevel(),
                            cssNr.getSsRsrp(), cssNr.getSsRsrq(), cssNr.getSsSinr());
                }
                break;
            case CELL_NETWORK_TYPE_NR:
                Log.v(TAG, "TODO: update input data for NR SA NN.");
                break;
            default:
                break;
        }

        float result = mSNPManager.doInferenceCell(cellNetworkType, cellInfoForNn);
        inferenceResultCell = removeDecimalPlaces(result, KEEPING_INFERENCE_RESULT_DIGIT);

        Log.v(TAG, "cellular inference result = " + inferenceResultCell);

        // Check mRuntimeStatsQueue size, remove head when queue is full.
        if (mRuntimeStatsQueue.size() == MAX_LOGGING_SEC / LOGGING_INTERVAL_SEC) {
            mRuntimeStatsQueue.poll();
        }

        // Build New SneRuntimeStats
        WifiPredictionData.SneRuntimeStats runtimeStats = buildSneRuntimeStats(
                mWifiInfo.getLinkSpeed(), mWifiInfo.getFrequency(),
                getChannelWidth(mWifiInfo.getBSSID()), rssi, mWifiInfo.getScore(),
                contentionInfo.getAverageTime(), contentionInfo.getDeltaNumOfSamples(),
                radioTimeInfo.getDeltaTxTime(), radioTimeInfo.getDeltaRxTime(),
                radioTimeInfo.getDeltaOnTimeOnCurrentFreq(),
                radioTimeInfo.getDeltaCcaBusyTimeOnCurrentFreq(), mWifiInfo.getWifiStandard(),
                mWifiInfo.getRxLinkSpeedMbps(), mDeltaTxPkts, mDeltaRxPkts,
                deltaTxBad, deltaTxRetries, deltaTxSuccess, deltaRxSuccess,
                bufferCongestionInfo.getDeltaTxTries(),
                bufferCongestionInfo.getIntegralUsedDescriptor(),
                acceleration, moving, inferenceResult[0], inferenceResult[1], mSneAospScore,
                inferenceResultCell, cellNetworkType);
        if (mInferenceResultInjector != null) {
            InferenceResultInfo resultInfo = mInferenceResultInjector.onInferenceResultRequested(
                    runtimeStats);
            // Update SneRuntimeStats if inference result is available
            if (resultInfo != null) {
                if (resultInfo.getUserWifiPreferenceScore() != null) {
                    runtimeStats = runtimeStats.toBuilder()
                            .setInferenceResult(runtimeStats.getInferenceResult().toBuilder()
                                    .setUserWifiPreference(resultInfo.getUserWifiPreferenceScore()))
                            .build();
                }
                mUserWifiPreferenceInferenceData = resultInfo.getUserWifiPreferenceInferenceData();
            }
        }

        if (mInferenceResultInjector != null || !mIsSettingsEnabled || mIsInitialLogging) {
            // Update default network information to SneRuntimeStats
            runtimeStats = runtimeStats.toBuilder()
                    .setInferenceResult(runtimeStats.getInferenceResult().toBuilder()
                            .setWifiPreferred(mWifiExtController.isWifiPreferred())).build();
        } else {
            Log.v(TAG, "Not set wifi_preferred as current WiFi session is disconnected");
        }

        // To use for lambda expression, variable must be effectively final.
        WifiPredictionData.SneRuntimeStats finalRuntimeStats = runtimeStats;

        // Add New SneRuntimeStats to Queue
        mRuntimeStatsQueue.offer(finalRuntimeStats);

        // Notify Logging data
        mStatsUpdateListeners.forEach(l -> l.onRuntimeStatsUpdated(finalRuntimeStats));
        mEventForwarder.noteLoggingStatsUpdate(finalRuntimeStats);

        mIsInitialLogging = false;
        mIsInitialLoggingAfterWifiConnection = false;
    }

    private WifiPredictionData.SneRuntimeStats buildSneRuntimeStats(
            int linkSpeed, int frequency, int channelWidth, int rssi,
            int score, long contentionAverageTime, long contentionNumOfSamples,
            long txTime, long rxTime, long onTime, long ccaBusyTime,
            int wifiGeneration, int rxLinkSpeed, long txPkt, long rxPkt,
            long txBad, long txRetries, long txSuccess, long rxSuccess,
            long numOfTxTriesInDriver, int integralUsedDescriptorInDriver,
            float sensorAcceleration, boolean isMoving, float inferenceResult1,
            float inferenceResult2, int velocityBasedScore, float inferenceResultCell,
            int networkType) {
        WifiPredictionData.SneWifiInfo wifiInfo =
                WifiPredictionData.SneWifiInfo.newBuilder()
                        .setLinkSpeed(linkSpeed)
                        .setFrequency(frequency)
                        .setChannelWidth(channelWidth)
                        .setRssi(rssi)
                        .setScore(score)
                        .setContentionAverageTime(contentionAverageTime)
                        .setContentionNumOfSamples(contentionNumOfSamples)
                        .setTxTime(txTime)
                        .setRxTime(rxTime)
                        .setOnTime(onTime)
                        .setCcaBusyTime(ccaBusyTime)
                        .setWifiGeneration(wifiGeneration)
                        .setRxLinkSpeed(rxLinkSpeed)
                        .build();
        WifiPredictionData.SneWifiTrafficStats wifiTrafficStats =
                WifiPredictionData.SneWifiTrafficStats.newBuilder()
                        .setTxPkt(txPkt)
                        .setRxPkt(rxPkt)
                        .setTxBad(txBad)
                        .setTxRetries(txRetries)
                        .setTxSuccess(txSuccess)
                        .setRxSuccess(rxSuccess)
                        .setNumOfTxTriesInDriver(numOfTxTriesInDriver)
                        .setIntegralUsedDescriptorInDriver(integralUsedDescriptorInDriver)
                        .build();
        WifiPredictionData.SneSensorData sensorData =
                WifiPredictionData.SneSensorData.newBuilder()
                        .setSensorAcceleration(sensorAcceleration)
                        .setIsMoving(isMoving)
                        .build();
        WifiPredictionData.SneInferenceResult inferenceResult =
                WifiPredictionData.SneInferenceResult.newBuilder()
                        .setPrimary(inferenceResult1)
                        .setSecondary(inferenceResult2)
                        .setVelocityBasedScore(velocityBasedScore)
                        .setCellular(inferenceResultCell)
                        .build();
        WifiPredictionData.SneCellularInfo cellularInfo =
                WifiPredictionData.SneCellularInfo.newBuilder()
                        .setNetworkType(networkType)
                        .build();
        return WifiPredictionData.SneRuntimeStats.newBuilder()
                .setWifiInfo(wifiInfo)
                .setWifiTrafficStats(wifiTrafficStats)
                .setSensorData(sensorData)
                .setInferenceResult(inferenceResult)
                .setCellularInfo(cellularInfo)
                .build();
    }

    private float removeDecimalPlaces(float value, int digit) {
        double coefficient = Math.pow((double) 10, (double) digit);
        return (float) (Math.floor(value * coefficient) / coefficient);
    }

    private long getDifferentialValue(long latestValue, long previousValue) {
        // if OnWifiUsabilityStats report delays after screen on, set the delta to 0
        if (mWifiUsabilityStatsListener.seqNumb - mWifiUsabilityStatsSeqNumBeforeScreenOff <= 1
                || mIsInitialLogging) {
            return 0;
        } else {
            long diffValue = latestValue - previousValue;
            return (diffValue > OUTLIER_THRESHOLD_COUNTER || diffValue < 0) ? 0 : diffValue;
        }
    }

    private int convertFrequencyToChannel(int freq) {
        int frequencyChannel;
        if (MIN_24GHz_FREQ <= freq && freq < MAX_24GHz_FREQ) {
            frequencyChannel = (freq - BASE_24GHz_FREQ) / 5;
        } else if (MIN_5GHz_FREQ <= freq && freq < MAX_5GHz_FREQ) {
            frequencyChannel = (freq - BASE_5GHz_FREQ) / 5;
        } else {
            frequencyChannel = 0;
        }
        return frequencyChannel;
    }

    private void notifyAllStatsCollected(LoggingTiming timing) {
        mLogEndTime = System.currentTimeMillis();

        // Build SneWifiEvent
        WifiPredictionData.SneWifiEvent wifiEvent = WifiPredictionData.SneWifiEvent.newBuilder()
                .setLoggerVersion(IDD_PROBE_VERSION)
                .addAllRuntimeStats(mRuntimeStatsQueue)
                .setLoggedInfo(loggingOnetimeData(timing))
                .build();

        // Notify Logging data
        mStatsUpdateListeners.forEach(
                l -> l.onAllStatsCollected(wifiEvent, mLogStartTime, mLogEndTime,
                        mUserWifiPreferenceInferenceData));
    }

    /**
     * Gets WiFi AP Channel bandwidth; returns one of CHANNEL_WIDTH_20MHZ, CHANNEL_WIDTH_40MHZ,
     * CHANNEL_WIDTH_80MHZ, CHANNEL_WIDTH_160MHZ, CHANNEL_WIDTH_80MHZ_PLUS_MHZ, or UNSPECIFIED.
     */
    private int getChannelWidth(String bssid) {
        if (bssid != null) {
            try {
                List<ScanResult> scanResults = mWiFiManager.getScanResults();
                for (ScanResult scanResult : scanResults) {
                    if (bssid.equals(scanResult.BSSID)) {
                        return scanResult.channelWidth;
                    }
                }
            } catch (RuntimeException e) {
                Log.e(TAG, "Failed to get scan results: " + e);
            }
        }
        return -1;
    }

    /**
     * When Wifi is connected, check Wifi EAP Method, Security type and Home network status.
     */
    private void loggingWifiConfiguration() {
        // WARNING: the passwords in plaintext are returned.
        final List<WifiConfiguration> configurations =
                mWiFiManager.getPrivilegedConfiguredNetworks();
        if (mWifiInfo != null && !configurations.isEmpty()) {
            for (WifiConfiguration config : configurations) {
                if (mWifiInfo.getNetworkId() == config.networkId) {
                    if (config.allowedKeyManagement.get(WifiConfiguration.KeyMgmt.NONE)) {
                        mWifiSecurityType = (config.wepKeys[0] != null) ?
                                WifiConfiguration.SECURITY_TYPE_WEP :
                                WifiConfiguration.SECURITY_TYPE_OPEN;
                    } else if (config.allowedKeyManagement.get(WifiConfiguration.KeyMgmt.WPA_PSK)) {
                        mWifiSecurityType = WifiConfiguration.SECURITY_TYPE_PSK;
                    } else if (config.allowedKeyManagement.get(
                            WifiConfiguration.KeyMgmt.IEEE8021X)) {
                        mWifiSecurityType = WifiConfiguration.SECURITY_TYPE_EAP;
                    } else if (config.allowedKeyManagement.get(WifiConfiguration.KeyMgmt.SAE)) {
                        mWifiSecurityType = WifiConfiguration.SECURITY_TYPE_SAE;
                    } else if (config.allowedKeyManagement.get(
                            WifiConfiguration.KeyMgmt.SUITE_B_192)) {
                        mWifiSecurityType = WifiConfiguration.SECURITY_TYPE_EAP_SUITE_B;
                    } else if (config.allowedKeyManagement.get(WifiConfiguration.KeyMgmt.OWE)) {
                        mWifiSecurityType = WifiConfiguration.SECURITY_TYPE_OWE;
                    }

                    if ((mWifiSecurityType == WifiConfiguration.SECURITY_TYPE_EAP
                            || mWifiSecurityType == WifiConfiguration.SECURITY_TYPE_EAP_SUITE_B)
                            && config.enterpriseConfig != null) {
                        mWifiEapMethod = config.enterpriseConfig.getEapMethod();
                    }

                    mIsHomeNetwork = HomeNetworkDetector.isHomeNetwork(this, config);
                    Log.v(TAG, "home network detection: " + (mIsHomeNetwork ? "Home" : "Non-home"));
                    break;
                }
            }
        }
    }

    @SuppressLint("MissingPermission")
    private WifiPredictionData.SneLoggedInfo loggingOnetimeData(LoggingTiming timing) {
        int wifiOn = mWiFiManager.isWifiEnabled() ? 1 : 0;
        int tetherOn =
                mWiFiManager.getWifiApState() == (WifiManager.WIFI_AP_STATE_ENABLING
                        | WifiManager.WIFI_AP_STATE_ENABLED) ? 1 : 0;
        int airplaneOn =
                Settings.Global.getString(getContentResolver(),
                        Settings.Global.AIRPLANE_MODE_ON).equals("1") ? 1 : 0;
        int ultraStaminaOn =
                Settings.Secure.getInt(getContentResolver(), STAMINA_MODE_STATUS, 0) != 0 ? 1 : 0;
        int sneOn = SneUtils.isSmartNetworkConnectedSettingsEnabled() ? 1 : 0;
        int screenOff = mScreenOff ? 1 : 0;
        int isHomeNetwork = mIsHomeNetwork ? 1 : 0;
        int isUserSelected = mIsUserSelected ? 1 : 0;
        // Bitset: IS_HOME|SCREEN_OFF|SNE_ON|ULTRA_STAMINA_ON|AIRPLANE_ON|TETHER_ON|WIFI_ON
        int detail = (wifiOn) | (tetherOn << 1) | (airplaneOn << 2) | (ultraStaminaOn << 3) |
                (sneOn << 4) | (screenOff << 5) | (isHomeNetwork << 6) | (isUserSelected << 7);

        WifiPredictionData.SneLoggedInfo.Builder loggedInfoBuilder =
                WifiPredictionData.SneLoggedInfo.newBuilder();
        loggedInfoBuilder.setLoggedReason(timing.getValue());
        loggedInfoBuilder.setLoggedDuration(mLogEndTime - mLogStartTime);
        loggedInfoBuilder.setLoggedSettingDetail(detail);
        loggedInfoBuilder.setWifiEapMethod(mWifiEapMethod);
        loggedInfoBuilder.setWifiSecurityType(mWifiSecurityType);
        if (timing == LoggingTiming.DISCONNECT) {
            loggedInfoBuilder.setSupplicantDisconLocally(mSupplicantLocallyGenerated);
            loggedInfoBuilder.setSupplicantDisconReason(mSupplicantReasonCode);
        }
        loggedInfoBuilder.setCellNetworkType(mTelephonyManager.getDataNetworkType());
        loggedInfoBuilder.setSsid(mSsid);
        loggedInfoBuilder.setStartBssid(mStartBssid);
        loggedInfoBuilder.setEndBssid(mEndBssid);

        return loggedInfoBuilder.build();
    }

    private final BroadcastReceiver mSettingsReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            switch (intent.getAction()) {
                case Intent.ACTION_SCREEN_ON:
                    mScreenOff = false;
                    startLoggingIfNeeded();
                    break;
                case Intent.ACTION_SCREEN_OFF:
                    mScreenOff = true;
                    mWifiUsabilityStatsSeqNumBeforeScreenOff = mWifiUsabilityStatsListener.seqNumb;
                    stopLogging(StopReason.SCREENOFF);
                    break;
                case Intent.ACTION_SHUTDOWN:
                    mIsShutdownProceeding = true;
                    break;
                default:
                    break;
            }
        }
    };

    private final BroadcastReceiver mWifiSoftApReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            int state = intent.getIntExtra(WifiManager.EXTRA_WIFI_AP_STATE,
                    WifiManager.WIFI_AP_STATE_DISABLED);
            switch (state) {
                case WifiManager.WIFI_AP_STATE_ENABLED:
                    mIsSoftApStarted = true;
                    stopLogging(StopReason.SOFTAP_STARTED);
                    break;
                case WifiManager.WIFI_AP_STATE_DISABLED:
                    mIsSoftApStarted = false;
                    startLoggingIfNeeded();
                    break;
                default:
                    break;
            }
        }
    };

    /**
     * Checks whether the current product supports AIDL interface or not.
     *
     * @return If {@code true} means that the current product supports AIDL.
     * {@code false} means that the current product doesn't support AIDL.
     */
    private boolean isAidlSupport() {
        try {
            return ServiceManager
                    .isDeclared("android.hardware.wifi.supplicant.ISupplicant/default");
        } catch (Exception e) {
            Log.e(TAG, "AIDL is not supported with exception: " + e);
        }
        return false;
    }

    static class WifiUsabilityStatsListener implements WifiManager.OnWifiUsabilityStatsListener {
        public long txBad = 0;
        public long txRetries = 0;
        public long txSuccess = 0;
        public long rxSuccess = 0;
        public int seqNumb = 0;

        @Override
        public void onWifiUsabilityStats(int seqNum, boolean isSameBssidAndFreq,
                WifiUsabilityStatsEntry statsEntry) {
            txBad = statsEntry.getTotalTxBad();
            txRetries = statsEntry.getTotalTxRetries();
            txSuccess = statsEntry.getTotalTxSuccess();
            rxSuccess = statsEntry.getTotalRxSuccess();
            seqNumb = seqNum;
        }
    }

    /**
     * This class contains information about current wifi connection.
     */
    public static class SessionInfo {

        private final String mCurrentBssid;

        private final int mWifiSecurityType;

        private final boolean mHomeNetwork;

        private final boolean mUserSelected;

        private SessionInfo(String currentBssid, int wifiSecurityType, boolean homeNetwork,
                boolean userSelected) {
            mCurrentBssid = currentBssid;
            mWifiSecurityType = wifiSecurityType;
            mHomeNetwork = homeNetwork;
            mUserSelected = userSelected;
        }

        public String getCurrentBssid() {
            return mCurrentBssid;
        }

        public int getWifiSecurityType() {
            return mWifiSecurityType;
        }

        public boolean isHomeNetwork() {
            return mHomeNetwork;
        }

        public boolean isUserSelected() {
            return mUserSelected;
        }

        @NonNull
        @Override
        public String toString() {
            return "SessionInfo(mCurrentBssid=" + mCurrentBssid + ", mWifiSecurityType="
                    + mWifiSecurityType + ", mHomeNetwork=" + mHomeNetwork + ", mUserSelected="
                    + mUserSelected + ")";
        }

        /**
         * Return a builder instance.
         */
        public static Builder builder() {
            return new Builder();
        }

        /**
         * A builder class to construct {@link SessionInfo} instance.
         */
        public static class Builder {

            private String mCurrentBssid;

            private int mWifiSecurityType;

            private boolean mHomeNetwork;

            private boolean mUserSelected;

            public Builder currentBssid(@NonNull String currentBssid) {
                mCurrentBssid = currentBssid;
                return this;
            }

            public Builder wifiSecurityType(int wifiSecurityType) {
                mWifiSecurityType = wifiSecurityType;
                return this;
            }

            public Builder homeNetwork(boolean homeNetwork) {
                mHomeNetwork = homeNetwork;
                return this;
            }

            public Builder userSelected(boolean userSelected) {
                mUserSelected = userSelected;
                return this;
            }

            public SessionInfo build() {
                return new SessionInfo(mCurrentBssid, mWifiSecurityType, mHomeNetwork,
                        mUserSelected);
            }
        }
    }

    /**
     * This class contains information about the inference result provided by client.
     */
    public static class InferenceResultInfo {

        @Nullable
        private final Float mUserWifiPreferenceScore;

        private final boolean mUserWifiPreferenceScoreUsable;

        @Nullable
        private final Object mUserWifiPreferenceInferenceData;

        private InferenceResultInfo(@Nullable Float userWifiPreferenceScore,
                boolean userWifiPreferenceScoreUsable,
                @Nullable Object userWifiPreferenceInferenceData) {
            mUserWifiPreferenceScore = userWifiPreferenceScore;
            mUserWifiPreferenceScoreUsable = userWifiPreferenceScoreUsable;
            mUserWifiPreferenceInferenceData = userWifiPreferenceInferenceData;
        }

        @Nullable
        public Float getUserWifiPreferenceScore() {
            return mUserWifiPreferenceScore;
        }

        public boolean isUserWifiPreferenceScoreUsable() {
            return mUserWifiPreferenceScoreUsable;
        }

        @Nullable
        public Object getUserWifiPreferenceInferenceData() {
            return mUserWifiPreferenceInferenceData;
        }

        @NonNull
        @Override
        public String toString() {
            return "InferenceResultInfo(" + "mUserWifiPreferenceScore=" + mUserWifiPreferenceScore
                    + ", mUserWifiPreferenceScoreUsable=" + mUserWifiPreferenceScoreUsable + ')';
        }

        /**
         * Return a builder instance.
         */
        public static Builder builder() {
            return new Builder();
        }

        /**
         * A builder class to construct {@link InferenceResultInfo} instance.
         */
        public static class Builder {

            private Float mUserWifiPreferenceScore = null;

            private boolean mUserWifiPreferenceScoreUsable;

            private Object mUserWifiPreferenceInferenceData;

            public Builder userWifiPreferenceScore(float userWifiPreferenceScore) {
                mUserWifiPreferenceScore = userWifiPreferenceScore;
                return this;
            }

            public Builder userWifiPreferenceScoreUsable(boolean userWifiPreferenceScoreUsable) {
                mUserWifiPreferenceScoreUsable = userWifiPreferenceScoreUsable;
                return this;
            }

            public Builder userWifiPreferenceInferenceData(Object userWifiPreferenceInferenceData) {
                mUserWifiPreferenceInferenceData = userWifiPreferenceInferenceData;
                return this;
            }

            public InferenceResultInfo build() {
                return new InferenceResultInfo(mUserWifiPreferenceScore,
                        mUserWifiPreferenceScoreUsable, mUserWifiPreferenceInferenceData);
            }
        }
    }

    /**
     * Interface to provide the stats collected by this logger.
     */
    public interface StatsUpdateListener {

        /**
         * Invoked when the runtime stats is collected/updated (almost every 3 secs).
         */
        default void onRuntimeStatsUpdated(
                @NonNull WifiPredictionData.SneRuntimeStats runtimeStats) {
        }

        /**
         * Invoked when all necessary stats on current wifi session are collected.
         */
        default void onAllStatsCollected(@NonNull WifiPredictionData.SneWifiEvent wifiEvent,
                long connectedTimeMs, long disconnectedTimeMs, @Nullable Object inferenceData) {
        }
    }

    /**
     * Interface to obtain the inference result from prediction component (for logging).
     */
    public interface InferenceResultInjector {

        /**
         * Invoked when current wifi session info is updated. Typically called when logging is
         * started or when wifi roaming happens.
         */
        void onSessionInfoUpdate(@NonNull SessionInfo sessionInfo);

        /**
         * Invoked when the runtime stats is updated (almost every 3 secs). A client should
         * perform inference from the passed {@link WifiPredictionData.SneRuntimeStats} instance
         * and return its result. If the client is not able to do inference at that time, null
         * can be returned.
         */
        @Nullable
        InferenceResultInfo onInferenceResultRequested(
                @NonNull WifiPredictionData.SneRuntimeStats runtimeStats);
    }
}
