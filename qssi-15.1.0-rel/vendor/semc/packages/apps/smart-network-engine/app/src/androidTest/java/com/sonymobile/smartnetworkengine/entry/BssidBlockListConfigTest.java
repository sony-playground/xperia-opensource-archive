/*
 * Copyright 2021 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.entry;

import static androidx.test.core.app.ApplicationProvider.getApplicationContext;

import static junit.framework.TestCase.assertEquals;

import android.content.res.Resources;

import androidx.annotation.NonNull;
import androidx.test.ext.junit.runners.AndroidJUnit4;

import org.junit.Ignore;
import org.junit.Test;
import org.junit.runner.RunWith;

/**
 * Verify the configs for the BSSID blocklist (related to wifi connection/disconnection flip flop)
 */
@Ignore("TODO: needs system uid to get it working properly")
@RunWith(AndroidJUnit4.class)
public class BssidBlockListConfigTest {

    /**
     * Verify 'config_wifiBssidBlocklistMonitorConnectedScoreBaseBlockDurationMs' config value.
     */
    @Test
    public void testConfigWifiBssidBlocklistMonitorConnectedScoreBaseBlockDurationMs() {
        assertEquals(30000, getWifiIntegerResource(
                "config_wifiBssidBlocklistMonitorConnectedScoreBaseBlockDurationMs"));
    }

    /**
     * Verify 'config_wifiBssidBlocklistMonitorFailureStreakCap' config value.
     */
    @Test
    public void testConfigWifiBssidBlocklistMonitorFailureStreakCap() {
        assertEquals(7, getWifiIntegerResource(
                "config_wifiBssidBlocklistMonitorFailureStreakCap"));
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
