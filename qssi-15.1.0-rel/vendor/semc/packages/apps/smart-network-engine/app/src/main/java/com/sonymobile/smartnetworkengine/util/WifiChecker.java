/*
 * Copyright 2022, 2024 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.util;

import android.net.wifi.WifiInfo;

public class WifiChecker {
    /**
     * Min bound on the 6.0 GHz (802.11ax) WLAN channels.
     */
    public static final int BAND_6_GHZ_MIN_FREQ_MHZ = 5925;

    /**
     * Max bound on the 6.0 GHz (802.11ax) WLAN channels.
     */
    public static final int BAND_6_GHZ_MAX_FREQ_MHZ = 7125;

    /**
     * Utility function to check if a frequency within 6 GHz band
     *
     * @param freqMhz
     * @return true if within 6GHz, false otherwise
     */
    public static boolean is6GHz(int freqMhz) {
        return (freqMhz >= BAND_6_GHZ_MIN_FREQ_MHZ && freqMhz < BAND_6_GHZ_MAX_FREQ_MHZ);
    }

     /**
     * Utility function to check if the connected WiFi is MLO connection
     *
     * @param wifiInfo
     * @return true if it is MLO connection, false otherwise
     */
    public static boolean isMloConnection(WifiInfo wifiInfo) {
        return wifiInfo != null && wifiInfo.getAssociatedMloLinks().size() > 1;
    }
}
