/*
 * Copyright 2019, 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.connected.logger.collector;

import static androidx.test.platform.app.InstrumentationRegistry.getInstrumentation;

import static junit.framework.TestCase.assertEquals;

import static org.mockito.Mockito.doReturn;
import static org.mockito.Mockito.doThrow;
import static org.mockito.Mockito.spy;
import static org.mockito.Mockito.when;

import android.content.Context;
import android.content.res.AssetManager;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sonymobile.smartnetworkengine.connected.logger.collector.WifiLinkLayerStatsCollector.LinkLayerStatsParser;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
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
 * Verify {@link WifiLinkLayerStatsCollector} implementation.
 */
@RunWith(AndroidJUnit4.class)
public class WifiLinkLayerStatsCollectorTest {

    @Mock
    private Context mMockContext;

    @Mock
    private WifiManager mMockWifiManager;

    @Mock
    private WifiInfo mMockWifiInfo;

    private WifiLinkLayerStatsCollector mCollector;

    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);
        when(mMockContext.getSystemService(Context.WIFI_SERVICE)).thenReturn(mMockWifiManager);
        mCollector = spy(new WifiLinkLayerStatsCollector(mMockContext, "wlan0" /* anything ok */));
        mCollector.mSourceNodePath = Paths.get("dummy" /* anything ok */);
    }

    @Test
    public void testConstruct() {
        // Check
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaTxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaRxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaOnTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaCcaBusyTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawTxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawRxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawOnTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawCcaBusyTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getContentionInfo().getAverageTime());
        assertEquals(-1, mCollector.getContentionInfo().getDeltaNumOfSamples());
        assertEquals(-1, mCollector.getContentionInfo().getRawNumOfSamples());
    }

    @Test
    public void testFirstRefresh() throws IOException {
        when(mMockWifiInfo.getFrequency()).thenReturn(2457);
        when(mMockWifiManager.getConnectionInfo()).thenReturn(mMockWifiInfo);
        setStatsFromFile("ll_stats_0");

        // Action
        mCollector.refresh();

        // Check
        assertEquals(0, mCollector.getRadioTimeInfo().getDeltaTxTime());
        assertEquals(0, mCollector.getRadioTimeInfo().getDeltaRxTime());
        assertEquals(0, mCollector.getRadioTimeInfo().getDeltaOnTimeOnCurrentFreq());
        assertEquals(0, mCollector.getRadioTimeInfo().getDeltaCcaBusyTimeOnCurrentFreq());
        assertEquals(123 + 24, mCollector.getRadioTimeInfo().getRawTxTime());
        assertEquals(168 + 98, mCollector.getRadioTimeInfo().getRawRxTime());
        assertEquals(4107, mCollector.getRadioTimeInfo().getRawOnTimeOnCurrentFreq());
        assertEquals(1768, mCollector.getRadioTimeInfo().getRawCcaBusyTimeOnCurrentFreq());
        assertEquals(294, mCollector.getContentionInfo().getAverageTime());
        assertEquals(0, mCollector.getContentionInfo().getDeltaNumOfSamples());
        assertEquals(138, mCollector.getContentionInfo().getRawNumOfSamples());
    }

    @Test
    public void testMultipleRefresh() throws IOException {
        when(mMockWifiInfo.getFrequency()).thenReturn(2457);
        when(mMockWifiManager.getConnectionInfo()).thenReturn(mMockWifiInfo);
        setStatsFromFile("ll_stats_0");

        // Action
        mCollector.refresh();
        setStatsFromFile("ll_stats_1");
        mCollector.refresh();

        // Check
        assertEquals((272 + 24) - (123 + 24), mCollector.getRadioTimeInfo().getDeltaTxTime());
        assertEquals((322 + 101) - (168 + 98), mCollector.getRadioTimeInfo().getDeltaRxTime());
        assertEquals(8912 - 4107, mCollector.getRadioTimeInfo().getDeltaOnTimeOnCurrentFreq());
        assertEquals(3493 - 1768, mCollector.getRadioTimeInfo().getDeltaCcaBusyTimeOnCurrentFreq());
        assertEquals(272 + 24, mCollector.getRadioTimeInfo().getRawTxTime());
        assertEquals(322 + 101, mCollector.getRadioTimeInfo().getRawRxTime());
        assertEquals(8912, mCollector.getRadioTimeInfo().getRawOnTimeOnCurrentFreq());
        assertEquals(3493, mCollector.getRadioTimeInfo().getRawCcaBusyTimeOnCurrentFreq());
        assertEquals(176, mCollector.getContentionInfo().getAverageTime());
        assertEquals(469 - 138, mCollector.getContentionInfo().getDeltaNumOfSamples());
        assertEquals(469, mCollector.getContentionInfo().getRawNumOfSamples());
    }

    @Test
    public void testMultipleRefresh2() throws IOException {
        when(mMockWifiInfo.getFrequency()).thenReturn(2457);
        when(mMockWifiManager.getConnectionInfo()).thenReturn(mMockWifiInfo);
        setStatsFromFile("ll_stats_0");

        // Action
        mCollector.refresh();
        setStatsFromFile("ll_stats_1");
        mCollector.refresh();
        setStatsFromFile("ll_stats_2");
        mCollector.refresh();

        // Check
        assertEquals((641 + 92) - (272 + 24), mCollector.getRadioTimeInfo().getDeltaTxTime());
        assertEquals((999 + 221) - (322 + 101), mCollector.getRadioTimeInfo().getDeltaRxTime());
        assertEquals(21731 - 8912, mCollector.getRadioTimeInfo().getDeltaOnTimeOnCurrentFreq());
        assertEquals(8701 - 3493, mCollector.getRadioTimeInfo().getDeltaCcaBusyTimeOnCurrentFreq());
        assertEquals(641 + 92, mCollector.getRadioTimeInfo().getRawTxTime());
        assertEquals(999 + 221, mCollector.getRadioTimeInfo().getRawRxTime());
        assertEquals(21731, mCollector.getRadioTimeInfo().getRawOnTimeOnCurrentFreq());
        assertEquals(8701, mCollector.getRadioTimeInfo().getRawCcaBusyTimeOnCurrentFreq());
        assertEquals(333, mCollector.getContentionInfo().getAverageTime());
        assertEquals(1282 - 469, mCollector.getContentionInfo().getDeltaNumOfSamples());
        assertEquals(1282, mCollector.getContentionInfo().getRawNumOfSamples());
    }

    @Test
    public void testMultipleRefresh_frequencyChange() throws IOException {
        when(mMockWifiInfo.getFrequency()).thenReturn(2457);
        when(mMockWifiManager.getConnectionInfo()).thenReturn(mMockWifiInfo);
        setStatsFromFile("ll_stats_0");

        // Action
        mCollector.refresh();
        when(mMockWifiInfo.getFrequency()).thenReturn(5700);
        setStatsFromFile("ll_stats_1");
        mCollector.refresh();

        // Check
        assertEquals((272 + 24) - (123 + 24), mCollector.getRadioTimeInfo().getDeltaTxTime());
        assertEquals((322 + 101) - (168 + 98), mCollector.getRadioTimeInfo().getDeltaRxTime());
        assertEquals(0, mCollector.getRadioTimeInfo().getDeltaOnTimeOnCurrentFreq());
        assertEquals(0, mCollector.getRadioTimeInfo().getDeltaCcaBusyTimeOnCurrentFreq());
        assertEquals(272 + 24, mCollector.getRadioTimeInfo().getRawTxTime());
        assertEquals(322 + 101, mCollector.getRadioTimeInfo().getRawRxTime());
        assertEquals(110, mCollector.getRadioTimeInfo().getRawOnTimeOnCurrentFreq());
        assertEquals(0, mCollector.getRadioTimeInfo().getRawCcaBusyTimeOnCurrentFreq());
        assertEquals(176, mCollector.getContentionInfo().getAverageTime());
        assertEquals(469 - 138, mCollector.getContentionInfo().getDeltaNumOfSamples());
        assertEquals(469, mCollector.getContentionInfo().getRawNumOfSamples());
    }

    @Test
    public void testMultipleRefresh_wrapAround() throws IOException {
        when(mMockWifiInfo.getFrequency()).thenReturn(2457);
        when(mMockWifiManager.getConnectionInfo()).thenReturn(mMockWifiInfo);
        setStatsFromFile("ll_stats_0");

        // Action
        mCollector.refresh();
        setStatsFromFile("ll_stats_1");
        mCollector.refresh();
        setStatsFromFile("ll_stats_2b");
        mCollector.refresh();

        // Check
        assertEquals(0, mCollector.getRadioTimeInfo().getDeltaTxTime());
        assertEquals(0, mCollector.getRadioTimeInfo().getDeltaRxTime());
        assertEquals(0, mCollector.getRadioTimeInfo().getDeltaOnTimeOnCurrentFreq());
        assertEquals(0, mCollector.getRadioTimeInfo().getDeltaCcaBusyTimeOnCurrentFreq());
        assertEquals(41 + 92, mCollector.getRadioTimeInfo().getRawTxTime());
        assertEquals(99 + 221, mCollector.getRadioTimeInfo().getRawRxTime());
        assertEquals(1731, mCollector.getRadioTimeInfo().getRawOnTimeOnCurrentFreq());
        assertEquals(701, mCollector.getRadioTimeInfo().getRawCcaBusyTimeOnCurrentFreq());
        assertEquals(33, mCollector.getContentionInfo().getAverageTime());
        assertEquals(0, mCollector.getContentionInfo().getDeltaNumOfSamples());
        assertEquals(282, mCollector.getContentionInfo().getRawNumOfSamples());
    }

    @Test
    public void testMultipleRefresh_wrapAround2() throws IOException {
        when(mMockWifiInfo.getFrequency()).thenReturn(2457);
        when(mMockWifiManager.getConnectionInfo()).thenReturn(mMockWifiInfo);
        setStatsFromFile("ll_stats_0");

        // Action
        mCollector.refresh();
        setStatsFromFile("ll_stats_1");
        mCollector.refresh();
        setStatsFromFile("ll_stats_2b");
        mCollector.refresh();
        setStatsFromFile("ll_stats_2");
        mCollector.refresh();

        // Check
        assertEquals((641 + 92) - (41 + 92), mCollector.getRadioTimeInfo().getDeltaTxTime());
        assertEquals((999 + 221) - (99 + 221), mCollector.getRadioTimeInfo().getDeltaRxTime());
        assertEquals(21731 - 1731, mCollector.getRadioTimeInfo().getDeltaOnTimeOnCurrentFreq());
        assertEquals(8701 - 701, mCollector.getRadioTimeInfo().getDeltaCcaBusyTimeOnCurrentFreq());
        assertEquals(641 + 92, mCollector.getRadioTimeInfo().getRawTxTime());
        assertEquals(999 + 221, mCollector.getRadioTimeInfo().getRawRxTime());
        assertEquals(21731, mCollector.getRadioTimeInfo().getRawOnTimeOnCurrentFreq());
        assertEquals(8701, mCollector.getRadioTimeInfo().getRawCcaBusyTimeOnCurrentFreq());
        assertEquals(333, mCollector.getContentionInfo().getAverageTime());
        assertEquals(1282 - 282, mCollector.getContentionInfo().getDeltaNumOfSamples());
        assertEquals(1282, mCollector.getContentionInfo().getRawNumOfSamples());
    }

    @Test
    public void testRefreshError_invalidFrequency() throws IOException {
        when(mMockWifiInfo.getFrequency()).thenReturn(2457);
        when(mMockWifiManager.getConnectionInfo()).thenReturn(mMockWifiInfo);
        setStatsFromFile("ll_stats_0");

        // Action
        mCollector.refresh();
        when(mMockWifiInfo.getFrequency()).thenReturn(-1);
        setStatsFromFile("ll_stats_1");
        mCollector.refresh();

        // Check
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaTxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaRxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaOnTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaCcaBusyTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawTxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawRxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawOnTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawCcaBusyTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getContentionInfo().getAverageTime());
        assertEquals(-1, mCollector.getContentionInfo().getDeltaNumOfSamples());
        assertEquals(-1, mCollector.getContentionInfo().getRawNumOfSamples());
    }

    @Test
    public void testRefreshError_fetchFailure() throws IOException {
        when(mMockWifiInfo.getFrequency()).thenReturn(2457);
        when(mMockWifiManager.getConnectionInfo()).thenReturn(mMockWifiInfo);
        setStatsFromFile("ll_stats_0");

        // Action
        mCollector.refresh();
        doThrow(new IOException()).when(mCollector).readLinkLayerStatsFile();
        mCollector.refresh();

        // Check
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaTxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaRxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaOnTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaCcaBusyTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawTxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawRxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawOnTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawCcaBusyTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getContentionInfo().getAverageTime());
        assertEquals(-1, mCollector.getContentionInfo().getDeltaNumOfSamples());
        assertEquals(-1, mCollector.getContentionInfo().getRawNumOfSamples());
    }

    @Test
    public void testRefreshError_invalidFormat() throws IOException {
        when(mMockWifiInfo.getFrequency()).thenReturn(2457);
        when(mMockWifiManager.getConnectionInfo()).thenReturn(mMockWifiInfo);
        setStatsFromFile("ll_stats_0");

        // Action
        mCollector.refresh();
        setStatsFromFile("ll_stats_invalid");
        mCollector.refresh();

        // Check
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaTxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaRxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaOnTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaCcaBusyTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawTxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawRxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawOnTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawCcaBusyTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getContentionInfo().getAverageTime());
        assertEquals(-1, mCollector.getContentionInfo().getDeltaNumOfSamples());
        assertEquals(-1, mCollector.getContentionInfo().getRawNumOfSamples());
    }

    @Test
    public void testNotSupported() throws IOException {
        mCollector.mSourceNodePath = null;
        when(mMockWifiInfo.getFrequency()).thenReturn(2457);
        when(mMockWifiManager.getConnectionInfo()).thenReturn(mMockWifiInfo);
        setStatsFromFile("ll_stats_0");

        // Action
        mCollector.refresh();

        // Check
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaTxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaRxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaOnTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getRadioTimeInfo().getDeltaCcaBusyTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawTxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawRxTime());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawOnTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getRadioTimeInfo().getRawCcaBusyTimeOnCurrentFreq());
        assertEquals(-1, mCollector.getContentionInfo().getAverageTime());
        assertEquals(-1, mCollector.getContentionInfo().getDeltaNumOfSamples());
        assertEquals(-1, mCollector.getContentionInfo().getRawNumOfSamples());
    }

    @Test
    public void testLinkLayerStatsParser() throws IOException {
        List<String> llStats = readStatsFile("ll_stats_0");
        LinkLayerStatsParser linkLayerStats = new LinkLayerStatsParser(llStats, 2457);

        // Check
        assertEquals(294, linkLayerStats.getAcBeContentionAverageTime());
        assertEquals(138, linkLayerStats.getAcBeNumOfContentionSamples());
        assertEquals((123 + 24), linkLayerStats.getTxTime());
        assertEquals((168 + 98), linkLayerStats.getRxTime());
        assertEquals(4107, linkLayerStats.getOnTimeOnRadio0CurrentFreq());
        assertEquals(1768, linkLayerStats.getCcaBusyTimeOnRadio0CurrentFreq());
    }

    @Test
    public void testLinkLayerStatsParserForSingleRadioDevice() throws IOException {
        List<String> llStats = readStatsFile("ll_stats_single_radio");
        LinkLayerStatsParser linkLayerStats = new LinkLayerStatsParser(llStats, 2457);

        // Check
        assertEquals(48, linkLayerStats.getAcBeContentionAverageTime());
        assertEquals(529, linkLayerStats.getAcBeNumOfContentionSamples());
        assertEquals(222, linkLayerStats.getTxTime());
        assertEquals(567, linkLayerStats.getRxTime());
        assertEquals(16826, linkLayerStats.getOnTimeOnRadio0CurrentFreq());
        assertEquals(1539, linkLayerStats.getCcaBusyTimeOnRadio0CurrentFreq());
    }

    private void setStatsFromFile(String filePath) throws IOException {
        List<String> llStats = readStatsFile(filePath);
        doReturn(llStats).when(mCollector).readLinkLayerStatsFile();
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
