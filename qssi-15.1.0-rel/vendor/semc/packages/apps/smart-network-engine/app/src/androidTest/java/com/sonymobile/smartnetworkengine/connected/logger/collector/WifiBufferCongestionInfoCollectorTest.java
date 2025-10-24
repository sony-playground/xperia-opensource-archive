/*
 * Copyright 2019 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.connected.logger.collector;

import static androidx.test.platform.app.InstrumentationRegistry.getInstrumentation;

import static junit.framework.TestCase.assertEquals;

import static org.mockito.Mockito.doReturn;
import static org.mockito.Mockito.doThrow;
import static org.mockito.Mockito.spy;

import android.content.res.AssetManager;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sonymobile.smartnetworkengine.connected.logger.collector.WifiBufferCongestionInfoCollector.BufferCongestionInfoParser;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.MockitoAnnotations;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.nio.file.Paths;
import java.util.List;
import java.util.stream.Collectors;

/**
 * Verify {@link WifiBufferCongestionInfoCollector} implementation.
 */
@RunWith(AndroidJUnit4.class)
public class WifiBufferCongestionInfoCollectorTest {

    private WifiBufferCongestionInfoCollector mCollector;

    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);
        mCollector = spy(new WifiBufferCongestionInfoCollector("wlan0" /* anything ok */));
        mCollector.mSourceNodePath = Paths.get("dummy" /* anything ok */);
    }

    @Test
    public void testConstruct() {
        // Check
        assertEquals(-1, mCollector.getBufferCongestionInfo().getDeltaTxTries());
        assertEquals(-1, mCollector.getBufferCongestionInfo().getIntegralUsedDescriptor());
    }

    @Test
    public void testFirstRefresh() throws IOException {
        setStatsFromFile("somc_ebc_info_0");

        // Action
        mCollector.refresh();

        // Check
        assertEquals(0, mCollector.getBufferCongestionInfo().getDeltaTxTries());
        assertEquals(30, mCollector.getBufferCongestionInfo().getIntegralUsedDescriptor());
    }

    @Test
    public void testMultipleRefresh() throws IOException {
        setStatsFromFile("somc_ebc_info_0");

        // Action
        mCollector.refresh();
        setStatsFromFile("somc_ebc_info_1");
        mCollector.refresh();

        // Check
        assertEquals(223 - 123, mCollector.getBufferCongestionInfo().getDeltaTxTries());
        assertEquals(60, mCollector.getBufferCongestionInfo().getIntegralUsedDescriptor());
    }

    @Test
    public void testRefreshError_fetchFailure() throws IOException {
        setStatsFromFile("somc_ebc_info_0");

        // Action
        mCollector.refresh();
        doThrow(new IOException()).when(mCollector).readCongestionInfoFile();
        mCollector.refresh();

        // Check
        assertEquals(-1, mCollector.getBufferCongestionInfo().getDeltaTxTries());
        assertEquals(-1, mCollector.getBufferCongestionInfo().getIntegralUsedDescriptor());
    }

    @Test
    public void testRefreshError_invalidFormat() throws IOException {
        setStatsFromFile("somc_ebc_info_0");

        // Action
        mCollector.refresh();
        setStatsFromFile("somc_ebc_info_invalid");
        mCollector.refresh();

        // Check
        assertEquals(-1, mCollector.getBufferCongestionInfo().getDeltaTxTries());
        assertEquals(-1, mCollector.getBufferCongestionInfo().getIntegralUsedDescriptor());
    }

    @Test
    public void testNotSupported() throws IOException {
        mCollector.mSourceNodePath = null;
        setStatsFromFile("somc_ebc_info_0");

        // Action
        mCollector.refresh();

        // Check
        assertEquals(-1, mCollector.getBufferCongestionInfo().getDeltaTxTries());
        assertEquals(-1, mCollector.getBufferCongestionInfo().getIntegralUsedDescriptor());
    }

    @Test
    public void testBufferCongestionInfoParser() throws IOException {
        List<String> stats = readStatsFile("somc_ebc_info_1");
        BufferCongestionInfoParser congestionStats = new BufferCongestionInfoParser(stats);

        // Check
        assertEquals(223, congestionStats.getNumOfTxTries());
        assertEquals(60, congestionStats.getIntegralUsedDescriptor());
    }

    private void setStatsFromFile(String filePath) throws IOException {
        List<String> stats = readStatsFile(filePath);
        doReturn(stats).when(mCollector).readCongestionInfoFile();
    }

    private List<String> readStatsFile(String filePath) throws IOException {
        AssetManager assetManager = getInstrumentation().getContext().getAssets();
        try (InputStream in = assetManager.open(filePath);
             InputStreamReader reader = new InputStreamReader(in, StandardCharsets.UTF_8);
             BufferedReader bufferedReader = new BufferedReader(reader)) {
            return bufferedReader.lines().collect(Collectors.toList());
        }
    }
}
