/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.util;

import static com.sonymobile.smartnetworkengine.Constants.SETTINGS_HOME_NETWORK_DETECTION_ENABLED;

import android.content.Context;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.provider.Settings;

import com.sonymobile.smartnetworkengine.CaptivePortalTracker;

import java.util.Optional;

public class HomeNetworkDetector {

    /**
     * Decides whether the current network is a "home" network.
     * <p>
     * Home network definition:
     * - Using WPA2/3-Personal or WEP security and,
     * - Not behind Captive portal
     */
    public static boolean isHomeNetwork(Context context) {
        WifiManager wifiManager = (WifiManager) context.getSystemService(Context.WIFI_SERVICE);
        WifiInfo wifiInfo = wifiManager.getConnectionInfo();
        if (wifiInfo != null) {
            Optional<WifiConfiguration> configOpt =
                    // WARNING: the passwords in plaintext are returned.
                    wifiManager.getPrivilegedConfiguredNetworks().stream()
                            .filter(e -> e.networkId == wifiInfo.getNetworkId())
                            .findFirst();
            if (configOpt.isPresent()) {
                return isHomeNetwork(context, configOpt.get());
            }
        }
        return false;
    }

    /**
     * Decides whether the current network is a "home" network.
     * <p>
     * Home network definition:
     * - Using WPA2/3-Personal or WEP security and,
     * - Not behind Captive portal
     */
    public static boolean isHomeNetwork(Context context, WifiConfiguration config) {
        return (config.allowedKeyManagement.get(WifiConfiguration.KeyMgmt.WPA_PSK)
                || config.allowedKeyManagement.get(WifiConfiguration.KeyMgmt.SAE)
                || wepKeyExist(config))
                && !CaptivePortalTracker.getInstance(context).isEverCaptivePortalDetected(config)
                && (Settings.Global.getInt(context.getContentResolver(),
                SETTINGS_HOME_NETWORK_DETECTION_ENABLED, 1) == 1);
    }

    private static boolean wepKeyExist(WifiConfiguration config) {
        return config.wepKeys != null && config.wepKeys.length > 0 && config.wepKeys[0] != null;
    }
}
