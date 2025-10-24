/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.ui;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.net.wifi.WifiConfiguration;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

/**
 * This class provide to receive event when user taps "CONNECT ANYWAY" on a notification.
 */
public class NotificationEventReceiver extends BroadcastReceiver {

    @Nullable
    private static NotificationEventListener sNotificationEventListener = null;

    @Override
    public void onReceive(Context context, Intent intent) {
        WifiConfiguration wifiConfig = intent.getParcelableExtra("wifi_config");
        NotificationEventListener notificationEventListener = sNotificationEventListener;
        if (notificationEventListener != null) {
            notificationEventListener.onConnectAnywayTapped(wifiConfig);
        }
    }

    /**
     * Interface for receiving "CONNECT ANYWAY" event.
     */
    public interface NotificationEventListener {
        /**
         * Called when user taps "CONNECT ANYWAY" on a notification.
         *
         * @param wifiConfig the configuration of Wi-Fi network to be connected.
         */
        void onConnectAnywayTapped(@NonNull WifiConfiguration wifiConfig);
    }

    /**
     * Set listener for receiving "CONNECT ANYWAY" event.
     *
     * @param listener to listen "CONNECT ANYWAY" event. Set null to clear listener.
     */
    public static void setNotificationEventListener(
            @Nullable NotificationEventListener listener) {
        sNotificationEventListener = listener;
    }
}