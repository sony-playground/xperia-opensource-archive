/*
 * Copyright 2020, 2022, 2023 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.api;

import static com.sonymobile.smartnetworkengine.api.SneLoggingEventCallback.STOP_REASON_NORMAL;
import static com.sonymobile.smartnetworkengine.api.SneLoggingEventCallback.STOP_REASON_SOFTAP_STARTED;
import static com.sonymobile.smartnetworkengine.api.SneLoggingEventCallback.STOP_REASON_UNKNOWN;

import android.os.Bundle;
import android.os.RemoteException;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

/**
 * The manager to provide the Smart Network Engine event API.
 *
 * Get an instance of this class by calling {@link SneApiClient#connect} with
 * {@link SneApiClient#SNE_EVENT_SERVICE}.
 *
 * @see SneApiClient
 */
public final class SneEventManager {

    /** Bundle key for "Wifi RSSI CAP Threshold". The value is an integer. */
    public static String CONFIG_KEY_RSSI_CAP_THRESHOLD = "rssi_cap_threshold";

    /** Bundle key for "Wifi Avoid flapping RSSI range". The value is an integer. */
    public static String CONFIG_KEY_AVOID_FLAPPING_RSSI_RANGE = "avoid_flapping_rssi_range";

    /** Bundle key for "Inference threshold for Primary NN". The value is a float. */
    public static String CONFIG_KEY_NN_PRIMARY_INFERENCE_THRESHOLD =
            "nn_primary_inference_threshold";

    /** Bundle key for "Inference threshold move ratio for Primary NN". The value is a float. */
    public static String CONFIG_KEY_NN_PRIMARY_INFERENCE_THRESHOLD_MOVE_RATIO =
            "nn_primary_inference_threshold_move_ratio";

    /** Bundle key for "Inference threshold for Secondary NN". The value is a float. */
    public static String CONFIG_KEY_NN_SECONDARY_INFERENCE_THRESHOLD =
            "nn_secondary_inference_threshold";

    /** Bundle key for "Inference threshold move ratio for Secondary NN". The value is a float. */
    public static String CONFIG_KEY_NN_SECONDARY_INFERENCE_THRESHOLD_MOVE_RATIO =
            "nn_secondary_inference_threshold_move_ratio";

    private ISneEventManager mService;

    SneEventManager(@NonNull ISneEventManager service) {
        mService = service;
    }

    void release() {
        mService = null;
    }

    /**
     * Gets the configurations in Smart Network Engine application which are useful for
     * handling various events from the event API.
     */
    @NonNull
    public Bundle getAppConfigurations() {
        try {
            validateConnection();
            return mService.getAppConfigurations();
        } catch (RemoteException | IllegalStateException e) {
            return new Bundle();
        }
    }

    /**
     * Sets a callback for receiving logging events from application. Caller can unset a
     * previously registered callback by calling this method with null argument.
     *
     * @see SneLoggingEventCallback
     */
    public void setLoggingEventCallback(@Nullable SneLoggingEventCallback callback) {
        try {
            validateConnection();
            mService.setLoggingEventCallback(
                    callback != null ? new SneLoggingEventCallbackProxy(callback) : null);
        } catch (RemoteException | IllegalStateException ignored) {
        }
    }

    /**
     * Sets a callback for receiving network decision events from application. Caller can unset a
     * previously registered callback by calling this method with null argument.
     *
     * @see SneNetworkDecisionEventCallback
     */
    public void setNetworkDecisionEventCallback(
            @Nullable SneNetworkDecisionEventCallback callback) {
        try {
            validateConnection();
            mService.setNetworkDecisionEventCallback(
                    callback != null ?
                            new SneNetworkDecisionEventCallbackProxy(callback) : null);
        } catch (RemoteException | IllegalStateException ignored) {
        }
    }

    /**
     * Gets detailed Wi-Fi statistics.
     * Before accessing to those statistics, refresh is also executed to get latest statistics.
     */
    @Nullable
    public WifiStats refreshAndGetWifiStats() {
        try {
            validateConnection();
            return mService.refreshAndGetWifiStats();
        } catch (RemoteException | IllegalStateException e) {
            return null;
        }
    }

    private void validateConnection() {
        if (mService == null) {
            throw new IllegalStateException("No service connection");
        }
    }

    /**
     * Callback proxy for {@link SneLoggingEventCallback} object.
     */
    private static class SneLoggingEventCallbackProxy extends ISneLoggingEventCallback.Stub {

        private final SneLoggingEventCallback mSneLoggingEventCallback;

        SneLoggingEventCallbackProxy(@NonNull SneLoggingEventCallback callback) {
            mSneLoggingEventCallback = callback;
        }

        @Override
        public void onStarted() {
            mSneLoggingEventCallback.onStarted();
        }

        @Override
        public void onStopped(int reason) {
            if (reason < STOP_REASON_NORMAL || STOP_REASON_SOFTAP_STARTED < reason) {
                reason = STOP_REASON_UNKNOWN;
            }
            mSneLoggingEventCallback.onStopped(reason);
        }

        @Override
        public void onStatsUpdated(LoggingStats stats) {
            mSneLoggingEventCallback.onStatsUpdated(stats);
        }
    }

    /**
     * Callback proxy for {@link SneNetworkDecisionEventCallback} object.
     */
    private static class SneNetworkDecisionEventCallbackProxy extends
            ISneNetworkDecisionEventCallback.Stub {

        private final SneNetworkDecisionEventCallback mSneNetworkDecisionEventCallback;

        SneNetworkDecisionEventCallbackProxy(@NonNull SneNetworkDecisionEventCallback callback) {
            mSneNetworkDecisionEventCallback = callback;
        }

        @Override
        public void onDecisionMade(boolean wifiUsable, LoggingStats sourceStats) {
            mSneNetworkDecisionEventCallback.onDecisionMade(wifiUsable, sourceStats);
        }
    }
}
