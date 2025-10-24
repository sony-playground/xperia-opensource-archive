/*
 * Copyright 2021 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.ui;

import static android.app.PendingIntent.FLAG_CANCEL_CURRENT;
import static android.app.PendingIntent.FLAG_IMMUTABLE;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiInfo;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.app.NotificationCompat;
import androidx.core.app.NotificationManagerCompat;

import com.sonymobile.smartnetworkengine.R;
import com.sonymobile.smartnetworkengine.util.Log;

public class NotificationUtil {

    private static final String TAG = NotificationUtil.class.getSimpleName();

    private static final String SMART_NET_ENTRY_NOTIFICATION = "SmartNetEntryNotification";

    private static final int SMART_NET_ENTRY_NOTIFICATION_ID = 1;

    private final Context mContext;

    private final NotificationManager mNotificationManager;

    @Nullable
    private Notification mEntryNotification;

    public NotificationUtil(@NonNull Context context) {
        mContext = context;
        mNotificationManager = (NotificationManager) context.getSystemService(
                Context.NOTIFICATION_SERVICE);
    }

    /**
     * Creates notification for entry.
     */
    public void createEntryNotification(@NonNull WifiConfiguration wifiConfig) {
        if (mEntryNotification != null) {
            return;
        }

        // Create notification channel
        NotificationChannel channel = new NotificationChannel(SMART_NET_ENTRY_NOTIFICATION,
                mContext.getString(R.string.smart_network_notification_channel_entry_title),
                NotificationManager.IMPORTANCE_MIN);
        mNotificationManager.createNotificationChannel(channel);

        // Create an action to open settings for entry notification.
        Intent openSettingIntent = new Intent(mContext, SettingsActivity.class);
        openSettingIntent.setFlags(Intent.FLAG_ACTIVITY_SINGLE_TOP);
        PendingIntent openSettingPendingIntent = PendingIntent.getActivity(mContext, 0,
                openSettingIntent, FLAG_CANCEL_CURRENT | FLAG_IMMUTABLE);
        NotificationCompat.Action openSettingAction = new NotificationCompat.Action.Builder(0,
                mContext.getString(R.string.smart_network_notification_entry_button),
                openSettingPendingIntent).build();

        // Create an action to change default NW to Wi-Fi forcibly
        Intent connectAnywayIntent = new Intent(mContext, NotificationEventReceiver.class);
        connectAnywayIntent.putExtra("wifi_config", wifiConfig);
        PendingIntent connectAnywayPendingIntent = PendingIntent.getBroadcast(mContext, 0,
                connectAnywayIntent, FLAG_CANCEL_CURRENT | FLAG_IMMUTABLE);
        NotificationCompat.Action connectAnywayAction = new NotificationCompat.Action.Builder(0,
                mContext.getString(R.string.smart_network_notification_entry_button_connect_anyway),
                connectAnywayPendingIntent).build();

        // Create notification
        String ssid = WifiInfo.sanitizeSsid(wifiConfig.SSID);
        mEntryNotification = new NotificationCompat.Builder(mContext,
                SMART_NET_ENTRY_NOTIFICATION)
                .setSmallIcon(R.drawable.ic_info)
                .setContentTitle(
                        mContext.getString(R.string.smart_network_notification_entry_title))
                .setContentText(
                        mContext.getString(R.string.smart_network_notification_entry_text, ssid))
                .setStyle(new NotificationCompat.BigTextStyle().bigText(
                        mContext.getString(R.string.smart_network_notification_entry_text, ssid)))
                .setAutoCancel(false)
                .addAction(openSettingAction)
                .addAction(connectAnywayAction)
                .build();

        Log.v(TAG, "Notify entry notification");
        NotificationManagerCompat notificationManagerCompat = NotificationManagerCompat.from(
                mContext);
        notificationManagerCompat.notify(SMART_NET_ENTRY_NOTIFICATION_ID, mEntryNotification);
    }

    public void cancelEntryNotification() {
        if (mEntryNotification != null) {
            Log.v(TAG, "Cancel entry notification");
            mNotificationManager.cancel(SMART_NET_ENTRY_NOTIFICATION_ID);
            mEntryNotification = null;
        }
    }
}
