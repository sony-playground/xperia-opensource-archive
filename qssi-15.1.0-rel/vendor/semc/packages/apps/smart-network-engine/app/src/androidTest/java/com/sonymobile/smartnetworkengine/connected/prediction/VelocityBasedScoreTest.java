/*
 * Copyright 2020 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.connected.prediction;

import static androidx.test.core.app.ApplicationProvider.getApplicationContext;

import static junit.framework.TestCase.assertEquals;

import android.content.res.Resources;

import androidx.annotation.NonNull;
import androidx.test.ext.junit.runners.AndroidJUnit4;

import org.junit.Ignore;
import org.junit.Test;
import org.junit.runner.RunWith;

@Ignore("TODO: needs system uid to get it working properly")
@RunWith(AndroidJUnit4.class)
public class VelocityBasedScoreTest {

    // FYI: Here is the comment from WLAN framework team about the entry/bad RSSI values.
    //  The default values of entry RSSI have been changed from AOSP to meet requirement
    //  from Docomo and applied to all variants.
    //  Set entry RSSI(for both 2.4GHz and 5GHz bands) values to -78dBm. Meanwhile,
    //  adjust bad RSSI(5GHz band) value to take advantage of 3dBm hysteresis which is
    //  recommended by Google.

    /**
     * Verify 'config_wifi_framework_wifi_score_entry_rssi_threshold_24GHz' config value.
     */
    @Test
    public void testConfigWifiFrameworkWifiScoreEntryRssiThreshold24Ghz() {
        assertEquals(-78, getWifiIntegerResource(
                "config_wifi_framework_wifi_score_entry_rssi_threshold_24GHz"));
    }

    /**
     * Verify 'config_wifi_framework_wifi_score_bad_rssi_threshold_24GHz' config value.
     * Note that this value is hard-coded in VelocityBasedScore.
     */
    @Test
    public void testConfigWifiFrameworkWifiScoreBadRssiThreshold24Ghz() {
        assertEquals(-83, getWifiIntegerResource(
                "config_wifi_framework_wifi_score_bad_rssi_threshold_24GHz"));
    }

    /**
     * Verify 'config_wifi_framework_wifi_score_entry_rssi_threshold_5GHz' config value
     */
    @Test
    public void testConfigWifiFrameworkWifiScoreEntryRssiThreshold5Ghz() {
        assertEquals(-78, getWifiIntegerResource(
                "config_wifi_framework_wifi_score_entry_rssi_threshold_5GHz"));
    }

    /**
     * Verify 'config_wifi_framework_wifi_score_bad_rssi_threshold_5GHz' config value.
     * Note that this value is hard-coded in VelocityBasedScore.
     */
    @Test
    public void testConfigWifiFrameworkWifiScoreBadRssiThreshold5Ghz() {
        assertEquals(-81, getWifiIntegerResource(
                "config_wifi_framework_wifi_score_bad_rssi_threshold_5GHz"));
    }

    /**
     * Retrieve an integer resource in wifi framework dynamically.
     */
    private int getWifiIntegerResource(@NonNull String name) {
        final String packageName = "com.google.android.wifi.resources";
        try {
            Resources res = getApplicationContext()
                    .getPackageManager().getResourcesForApplication(packageName);
            return res.getInteger(res.getIdentifier(name, "integer", packageName));
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
