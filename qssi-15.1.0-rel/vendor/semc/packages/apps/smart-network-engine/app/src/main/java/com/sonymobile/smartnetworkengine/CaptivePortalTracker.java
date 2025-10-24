/*
 * Copyright 2020 Sony Corporation
 */

package com.sonymobile.smartnetworkengine;

import android.content.Context;
import android.content.SharedPreferences;
import android.net.ConnectivityManager;
import android.net.ConnectivityManager.NetworkCallback;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkRequest;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiConfiguration.KeyMgmt;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;
import androidx.annotation.WorkerThread;

import java.time.Instant;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.stream.Collectors;

/**
 * This class manages the list of Wifi networks which are/were behind captive portal.
 * <p>
 * Note that only wifi networks with captive portal "and WPA2/3-Personal security" are tracked.
 */
public class CaptivePortalTracker {

    private static final String TAG = CaptivePortalTracker.class.getSimpleName();

    @VisibleForTesting
    static final String SHARED_PREFS_FILENAME = "CaptivePortalNetworkSharedPrefs";

    @VisibleForTesting
    static final int MAX_NUM_OF_TRACKED_NETWORKS = 50;

    private static CaptivePortalTracker sInstance;

    private final ConnectivityManager mConnectivityManager;

    private final WifiManager mWifiManager;

    private final Handler mHandler;

    private final SharedPreferences mSharedPreferences;

    private boolean mStarted;

    /** A shared preference key that indicates the most recent captive portal wifi network */
    @NonNull
    private String mLastDetectedKey = "";

    @VisibleForTesting
    final NetworkCallback mWifiNetworkCallback = new NetworkCallback() {
        private boolean mCaptivePortalDetected;
        private boolean mValidationDetected;
        private boolean mShouldRecord;
        @Nullable
        private WifiConfiguration mCurrentWifiConfig;
        @Nullable
        private Network mNetwork;

        @WorkerThread
        @Override
        public void onCapabilitiesChanged(Network network,
                NetworkCapabilities networkCapabilities) {
            super.onCapabilitiesChanged(network, networkCapabilities);
            if (mCurrentWifiConfig == null) {
                // Obtain current wifi network configuration
                WifiInfo wifiInfo = mWifiManager.getConnectionInfo();
                if (wifiInfo != null) {
                    Optional<WifiConfiguration> configOpt =
                            // WARNING: the passwords in plaintext are returned.
                            mWifiManager.getPrivilegedConfiguredNetworks().stream()
                                    .filter(e -> e.networkId == wifiInfo.getNetworkId())
                                    .findFirst();
                    mCurrentWifiConfig = configOpt.orElse(null);
                }
                if (mCurrentWifiConfig == null) {
                    // Never happen?
                    return;
                }
                mNetwork = network;
            }

            // To prevent false detection of captive portal after MBB occurs, if received network
            // object does not match mNetwork, no further processing is performed.
            if (!network.equals(mNetwork)) {
                return;
            }

            if (networkCapabilities.hasCapability(
                    NetworkCapabilities.NET_CAPABILITY_CAPTIVE_PORTAL)) {
                if (mCaptivePortalDetected) {
                    // Already processed
                    return;
                }

                // Interested in WPA-PSK/SAE security only
                if (mCurrentWifiConfig.allowedKeyManagement.get(KeyMgmt.WPA_PSK)
                        || mCurrentWifiConfig.allowedKeyManagement.get(KeyMgmt.SAE)) {
                    mShouldRecord = true;
                    // To avoid possible lock wait at caller of |isEverCaptivePortalDetected| method
                    // because both persisting to and reading from the shared preference may happen
                    // concurrently(reader needs to wait for persist completion).
                    // Note: might be better to move this logic to validated state since the list of
                    // wifi networks are updated upon validated event, but this is earlier than it.
                    mLastDetectedKey = mCurrentWifiConfig.getKey();
                }
                mCaptivePortalDetected = true;
            } else if (networkCapabilities.hasCapability(
                    NetworkCapabilities.NET_CAPABILITY_VALIDATED)) {
                if (mValidationDetected) {
                    // Already processed
                    return;
                }

                String key = mCurrentWifiConfig.getKey();
                if (mShouldRecord || mSharedPreferences.contains(key)) {
                    // Persist with current timestamp
                    mSharedPreferences.edit()
                            .putLong(key, Instant.now().getEpochSecond())
                            .apply();
                }
                mValidationDetected = true;
            }
        }

        @WorkerThread
        @Override
        public void onLost(Network network) {
            super.onLost(network);
            if (network.equals(mNetwork)) {
                mCaptivePortalDetected = false;
                mValidationDetected = false;
                mShouldRecord = false;
                mCurrentWifiConfig = null;
                mNetwork = null;
            }
        }
    };

    @VisibleForTesting
    CaptivePortalTracker(Context context, Looper looper) {
        mConnectivityManager = (ConnectivityManager) context.getSystemService(
                Context.CONNECTIVITY_SERVICE);
        mWifiManager = (WifiManager) context.getSystemService(Context.WIFI_SERVICE);
        if (looper == null) {
            HandlerThread handlerThread = new HandlerThread(TAG);
            handlerThread.start();
            looper = handlerThread.getLooper();
        }
        mHandler = new Handler(looper);
        mSharedPreferences = context.getSharedPreferences(SHARED_PREFS_FILENAME,
                Context.MODE_PRIVATE);
    }

    void start() {
        mHandler.post(() -> {
            if (!mStarted) {
                // Clean up overflow entries in persisted data
                @SuppressWarnings("unchecked")
                Map<String, Long> trackedNetworks = (Map<String, Long>) mSharedPreferences.getAll();
                List<String> overflowKeys = trackedNetworks.entrySet().stream()
                        .sorted(Map.Entry.<String, Long>comparingByValue().reversed())
                        .skip(MAX_NUM_OF_TRACKED_NETWORKS)
                        .map(Map.Entry::getKey)
                        .collect(Collectors.toList());
                if (!overflowKeys.isEmpty()) {
                    SharedPreferences.Editor editor = mSharedPreferences.edit();
                    overflowKeys.forEach(editor::remove);
                    editor.apply();
                }

                // Monitor Wifi network events
                NetworkRequest networkRequest = new NetworkRequest.Builder()
                        .addTransportType(NetworkCapabilities.TRANSPORT_WIFI)
                        .build();
                mConnectivityManager.registerNetworkCallback(networkRequest,
                        mWifiNetworkCallback, mHandler);
                mStarted = true;
            }
        });
    }

    void stop() {
        mHandler.post(() -> {
            if (mStarted) {
                mConnectivityManager.unregisterNetworkCallback(mWifiNetworkCallback);
                mStarted = false;
            }
        });
    }

    public boolean isEverCaptivePortalDetected(@NonNull WifiConfiguration wifiConfiguration) {
        String key = wifiConfiguration.getKey();
        return key.equals(mLastDetectedKey) || mSharedPreferences.contains(key);
    }

    public static synchronized CaptivePortalTracker getInstance(Context context) {
        if (sInstance == null) {
            sInstance = new CaptivePortalTracker(context, null);
        }
        return sInstance;
    }
}
