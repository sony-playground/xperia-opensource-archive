/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.util;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sonymobile.smartnetworkengine.util.WifiStatsNodeFinder.StatsType;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import java.nio.file.Path;
import java.nio.file.Paths;

@RunWith(AndroidJUnit4.class)
public class WifiStatsNodeFinderTest {

    // TODO: this hardcode will be removed with upcoming change
    private static final String IF_NAME = "wlan0";

    @Before
    public void setUp() {
        // Reset internal state
        WifiStatsNodeFinder.sFoundPathFormat = null;
    }

    @Test
    public void testBasicScenario() {
        // Action
        Path p1 = WifiStatsNodeFinder.findSourceNodePath(StatsType.BUF_INFO, IF_NAME);
        Path p2 = WifiStatsNodeFinder.findSourceNodePath(StatsType.LL_STATS, IF_NAME);

        // Check
        assertNotNull(p1);
        assertNotNull(p2);
    }

    @Test
    public void testFoundPathFormat() {
        // Action
        WifiStatsNodeFinder.findSourceNodePath(StatsType.LL_STATS, IF_NAME);

        // Check (|sFoundPathFormat| is set by 1st call)
        assertNotNull(WifiStatsNodeFinder.sFoundPathFormat);

        // Action
        WifiStatsNodeFinder.sFoundPathFormat = "/foobar";
        Path p1 = WifiStatsNodeFinder.findSourceNodePath(StatsType.LL_STATS, IF_NAME);
        Path p2 = WifiStatsNodeFinder.findSourceNodePath(StatsType.BUF_INFO, IF_NAME);

        // Check (|sFoundPathFormat| is used from 2nd call onwards)
        assertEquals(Paths.get("/foobar"), p1);
        assertEquals(Paths.get("/foobar"), p2);
    }
}
