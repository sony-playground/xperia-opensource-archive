/*
 * Copyright 2020, 2022, 2023 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.event;

import static android.content.pm.PackageManager.CERT_INPUT_SHA256;

import static com.sonymobile.smartnetworkengine.Constants.AVOID_FLAPPING_RSSI_RANGE;
import static com.sonymobile.smartnetworkengine.Constants.NN_PRIMARY;
import static com.sonymobile.smartnetworkengine.Constants.NN_SECONDARY;
import static com.sonymobile.smartnetworkengine.Constants.RSSI_CAP_THRESHOLD;
import static com.sonymobile.smartnetworkengine.api.SneEventManager.CONFIG_KEY_AVOID_FLAPPING_RSSI_RANGE;
import static com.sonymobile.smartnetworkengine.api.SneEventManager.CONFIG_KEY_NN_PRIMARY_INFERENCE_THRESHOLD;
import static com.sonymobile.smartnetworkengine.api.SneEventManager.CONFIG_KEY_NN_PRIMARY_INFERENCE_THRESHOLD_MOVE_RATIO;
import static com.sonymobile.smartnetworkengine.api.SneEventManager.CONFIG_KEY_NN_SECONDARY_INFERENCE_THRESHOLD;
import static com.sonymobile.smartnetworkengine.api.SneEventManager.CONFIG_KEY_NN_SECONDARY_INFERENCE_THRESHOLD_MOVE_RATIO;
import static com.sonymobile.smartnetworkengine.api.SneEventManager.CONFIG_KEY_RSSI_CAP_THRESHOLD;

import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.net.wifi.ScanResult;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.net.wifi.WifiUsabilityStatsEntry;
import android.os.Bundle;
import android.os.IBinder;
import android.os.Parcel;
import android.os.RemoteException;
import android.text.TextUtils;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.google.common.collect.ArrayListMultimap;
import com.google.common.collect.ListMultimap;
import com.sonymobile.smartnetworkengine.SneApplication;
import com.sonymobile.smartnetworkengine.WifiExtController;
import com.sonymobile.smartnetworkengine.api.ISneEventManager;
import com.sonymobile.smartnetworkengine.api.ISneLoggingEventCallback;
import com.sonymobile.smartnetworkengine.api.ISneNetworkDecisionEventCallback;
import com.sonymobile.smartnetworkengine.api.WifiStats;
import com.sonymobile.smartnetworkengine.connected.logger.collector.WifiLinkLayerStatsCollector;
import com.sonymobile.smartnetworkengine.util.Log;
import com.sonymobile.smartnetworkengine.util.NeuralNetworkConfiguration;

import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;


/**
 * A service to provide event APIs which are intended to be used from the Extension application.
 * This service is alive as long as the binding with the application exists.
 *
 * Note it might be reasonable to integrate this service into CoreService as only a few small
 * logic exist here. Let's consider once CoreService refactor is completed. Two things we need
 * to be considered are,
 * (1) When Smart Network Engine application dies and restarts, the binding to the Extension
 * application can automatically be recovered with |onServiceConnected| callback.
 * (2) When the Extension application dies, it can be detected as |onDestroy| is called.
 * At this point not 100% sure those behaviors can be realized with CoreService.
 */
public class EventApiService extends Service {

    private static final String TAG = EventApiService.class.getSimpleName();

    private static final String ACTION_EVENT_MANAGER =
            "com.sonymobile.smartnetworkengine.intent.action.ISneEventManager";

    private static final int USABILITY_STATS_TIMEOUT_MSEC = 300;
    private static final int MIN_API_ACCESS_INTERVAL_MSEC = 300;

    private EventForwarder mEventForwarder;
    private WifiManager mWifiManager;
    private WifiUsabilityStatsListener mWifiUsabilityStatsListener;
    private ExecutorService mExecutor;
    private WifiExtController mWifiExtController;
    private long mLastValidCallTimestamp = 0;
    private long mSeqNo = 0;
    private WifiStats mPrevWifiStats = null;

    private static final ListMultimap<String, String> GRANTED_APPS_LIST =
            ArrayListMultimap.create();
    static {
        // For PS now app's test version
        GRANTED_APPS_LIST.put("com.gaikai.client",
                "7ABE7576C613FF987ED3C2AF2A93E74BB36BD4D22626E4DD70C73870E76D5F57");
        // For PS now app's release version, with development signature
        GRANTED_APPS_LIST.put("com.scee.psxandroid",
                "5F7674BF19068F5734FD5EF6BD83BEDEE3DDD37623CC189F7C681A5B6BA6ABAB");
        // For PS now app's release version, with production signature
        GRANTED_APPS_LIST.put("com.scee.psxandroid",
                "DB4C389642CDDC762F6C72B867B8FCD939E5B5DAE4AC3763DBCDF62327D382F7");
    }

    /* Interface for application */
    private final ISneEventManager.Stub mServiceInterface = new ISneEventManager.Stub() {
        // Cached app configurations
        private Bundle mAppConfigs;

        @Override
        public boolean onTransact(int code, Parcel data, Parcel reply, int flags)
                throws RemoteException {
            String packageName = null;
            final String[] packages = getPackageManager().getPackagesForUid(getCallingUid());
            if (packages != null && packages.length > 0) {
                packageName = packages[0];
            }
            if (TextUtils.isEmpty(packageName) || !isGrantedApp(packageName)) {
                Log.i(TAG, packageName + " is NOT a Granted App");
                return false;
            }
            return super.onTransact(code, data, reply, flags);
        }

        @NonNull
        @Override
        public Bundle getAppConfigurations() {
            if (mAppConfigs == null) {
                mAppConfigs = retrieveAppConfigs();
            }
            return mAppConfigs;
        }

        @Override
        public void setLoggingEventCallback(@Nullable ISneLoggingEventCallback callback) {
            mEventForwarder.setLoggingEventCallback(callback);
        }

        @Override
        public void setNetworkDecisionEventCallback(
                @Nullable ISneNetworkDecisionEventCallback callback) {
            mEventForwarder.setNetworkDecisionEventCallback(callback);
        }

        @Nullable
        @Override
        public WifiStats refreshAndGetWifiStats() {
            mWifiExtController =
                    ((SneApplication) getApplicationContext()).getWifiExtController();
            if (mWifiExtController != null) {
                long currentTimestamp = System.currentTimeMillis();
                if (currentTimestamp - mLastValidCallTimestamp > MIN_API_ACCESS_INTERVAL_MSEC) {
                    mLastValidCallTimestamp = currentTimestamp;
                    refreshWifiUsabilityStats();
                    mPrevWifiStats = genWifiStats();
                    mSeqNo++;
                } else {
                    Log.i(TAG, "Too frequent access is detected (interval=" +
                            (currentTimestamp - mLastValidCallTimestamp) + "ms)."
                            + " Just return previous WifiStats");
                }
                return mPrevWifiStats;
            } else {
                Log.v(TAG, "mWifiExtController is null...");
                return null;
            }
        }
    };

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        Log.v(TAG, "onBind: " + intent);
        String action = intent.getAction();
        if (ACTION_EVENT_MANAGER.equals(action)) {
            return mServiceInterface;
        }
        return null;
    }

    @Override
    public void onCreate() {
        Log.i(TAG, "Service created");
        super.onCreate();
        mEventForwarder = ((SneApplication) getApplicationContext()).getEventForwarder();
        mWifiManager = (WifiManager) getSystemService(Context.WIFI_SERVICE);
        mWifiUsabilityStatsListener = new WifiUsabilityStatsListener();
        mExecutor = Executors.newSingleThreadExecutor();
        mWifiManager.addOnWifiUsabilityStatsListener(
                mExecutor, mWifiUsabilityStatsListener);
    }

    @Override
    public void onDestroy() {
        Log.i(TAG, "Service destroyed");
        super.onDestroy();
        // Clean up callbacks so that EventForwarder#noteFooBar methods will do nothing.
        mEventForwarder.setLoggingEventCallback(null);
        mEventForwarder.setNetworkDecisionEventCallback(null);
        mWifiManager.removeOnWifiUsabilityStatsListener(mWifiUsabilityStatsListener);
        mExecutor.shutdown();
    }

    private boolean isGrantedApp(String packageName) {
        List<String> correctHash = GRANTED_APPS_LIST.get(packageName);
        if (correctHash == null || correctHash.isEmpty()) {
            return false;
        }
        return correctHash.stream().anyMatch(
                hash -> getPackageManager().hasSigningCertificate(
                        packageName, hex2Bytes(hash), CERT_INPUT_SHA256));
    }

    private byte[] hex2Bytes(String s) {
        int len = s.length();
        byte[] data = new byte[len / 2];
        for (int i = 0; i < len; i += 2) {
            data[i / 2] = (byte) ((Character.digit(s.charAt(i), 16) << 4)
                    + Character.digit(s.charAt(i + 1), 16));
        }
        return data;
    }

    private Bundle retrieveAppConfigs() {
        Bundle configs = new Bundle();
        configs.putInt(CONFIG_KEY_RSSI_CAP_THRESHOLD, RSSI_CAP_THRESHOLD);
        configs.putInt(CONFIG_KEY_AVOID_FLAPPING_RSSI_RANGE, AVOID_FLAPPING_RSSI_RANGE);
        // TODO: Consider to avoid creating new instances here. It would be better to manage
        //  instances (for both primary and secondary) in e.g. SneApplication class globally.
        NeuralNetworkConfiguration primary = new NeuralNetworkConfiguration(this, NN_PRIMARY);
        NeuralNetworkConfiguration secondary = new NeuralNetworkConfiguration(this, NN_SECONDARY);
        configs.putFloat(CONFIG_KEY_NN_PRIMARY_INFERENCE_THRESHOLD, primary.getThreshold());
        configs.putFloat(CONFIG_KEY_NN_PRIMARY_INFERENCE_THRESHOLD_MOVE_RATIO,
                primary.getThresholdMoveRatio());
        configs.putFloat(CONFIG_KEY_NN_SECONDARY_INFERENCE_THRESHOLD, secondary.getThreshold());
        configs.putFloat(CONFIG_KEY_NN_SECONDARY_INFERENCE_THRESHOLD_MOVE_RATIO,
                secondary.getThresholdMoveRatio());
        return configs;
    }

    private void refreshWifiUsabilityStats() {
        mWifiUsabilityStatsListener.countDownLatch = new CountDownLatch(1);
        // Assuming that null check of mWifiExtController has been already done in upper function
        mWifiExtController.requestWifiStatsUpdate();
        try {
            mWifiUsabilityStatsListener.countDownLatch.await(
                    USABILITY_STATS_TIMEOUT_MSEC, TimeUnit.MILLISECONDS);
        } catch (Exception e) {
            Log.e(TAG, "failed to update WifiUsabilityStats: " + e);
        }
    }

    private int getChannelWidth(String bssid) {
        if (bssid != null) {
            List<ScanResult> scanResults = mWifiManager.getScanResults();
            for (ScanResult scanResult : scanResults) {
                if (bssid.equals(scanResult.BSSID)) {
                    return scanResult.channelWidth;
                }
            }
        }
        return -1;
    }

    private WifiStats genWifiStats() {
        int frequency = -1;
        int rssi = -127;
        int txLinkSpeed = -1;
        int rxLinkSpeed = -1;
        long rawTxSuccess = -1;
        long rawTxRetries = -1;
        long rawTxBad = -1;
        long rawRxSuccess = -1;
        WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo;
        WifiLinkLayerStatsCollector.ContentionInfo contentionInfo;
        int standard = -1;
        int channelWidth = -1;

        WifiInfo wifiInfo = mWifiManager.getConnectionInfo();
        if (wifiInfo != null) {
            frequency = wifiInfo.getFrequency();
            standard = wifiInfo.getWifiStandard();
            channelWidth = getChannelWidth(wifiInfo.getBSSID());
        }
        if (mWifiUsabilityStatsListener.wifiStatsEntry != null) {
            rssi = mWifiUsabilityStatsListener.wifiStatsEntry.getRssi();
            txLinkSpeed = mWifiUsabilityStatsListener.wifiStatsEntry.getLinkSpeedMbps();
            rxLinkSpeed = mWifiUsabilityStatsListener.wifiStatsEntry.getRxLinkSpeedMbps();
            rawTxSuccess = mWifiUsabilityStatsListener.wifiStatsEntry.getTotalTxSuccess();
            rawTxRetries = mWifiUsabilityStatsListener.wifiStatsEntry.getTotalTxRetries();
            rawTxBad = mWifiUsabilityStatsListener.wifiStatsEntry.getTotalTxBad();
            rawRxSuccess = mWifiUsabilityStatsListener.wifiStatsEntry.getTotalRxSuccess();
        }
        // Assuming that null check of mWifiExtController has been already done in upper function
        String wifiInterface = mWifiExtController.getPrimaryInterfaceName();
        WifiLinkLayerStatsCollector linkLayerStatsCollector =
                new WifiLinkLayerStatsCollector(this, wifiInterface);
        linkLayerStatsCollector.refresh();
        radioTimeInfo = linkLayerStatsCollector.getRadioTimeInfo();
        contentionInfo = linkLayerStatsCollector.getContentionInfo();

        return WifiStats.builder()
                .seqNo(mSeqNo)
                .frequency(frequency)
                .rssi(rssi)
                .txLinkSpeed(txLinkSpeed)
                .rxLinkSpeed(rxLinkSpeed)
                .txBad(rawTxBad)
                .txRetries(rawTxRetries)
                .txSuccess(rawTxSuccess)
                .rxSuccess(rawRxSuccess)
                .txTime(radioTimeInfo.getRawTxTime())
                .rxTime(radioTimeInfo.getRawRxTime())
                .onTime(radioTimeInfo.getRawOnTimeOnCurrentFreq())
                .ccaBusyTime(radioTimeInfo.getRawCcaBusyTimeOnCurrentFreq())
                .contentionAverageTime(contentionInfo.getAverageTime())
                .contentionNumOfSamples(contentionInfo.getRawNumOfSamples())
                .wifiGeneration(standard)
                .channelWidth(channelWidth)
                .build();
    }

    static class WifiUsabilityStatsListener implements WifiManager.OnWifiUsabilityStatsListener {
        volatile WifiUsabilityStatsEntry wifiStatsEntry;
        volatile CountDownLatch countDownLatch;

        @Override
        public void onWifiUsabilityStats(int seqNum, boolean isSameBssidAndFreq,
                WifiUsabilityStatsEntry statsEntry) {
            wifiStatsEntry = statsEntry;
            if (countDownLatch != null) {
                countDownLatch.countDown();
            }
        }
    }
}
