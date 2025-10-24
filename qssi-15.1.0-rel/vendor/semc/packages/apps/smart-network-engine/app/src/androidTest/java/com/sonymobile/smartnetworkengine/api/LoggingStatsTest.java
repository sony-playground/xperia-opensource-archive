/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.api;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.assertTrue;

import android.os.Parcel;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.MockitoAnnotations;

/**
 * Verify {@link LoggingStats} implementation.
 */
@RunWith(AndroidJUnit4.class)
public class LoggingStatsTest {

    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);
    }

    @Test
    public void testBuilders() {
        verifyLoggingStats(createLoggingStats());
    }

    /**
     * Verify parcel serialization/deserialization.
     */
    @Test
    public void testParcelWriteRead() {
        LoggingStats writeLoggingStats = createLoggingStats();

        // Action
        Parcel parcel = Parcel.obtain();
        writeLoggingStats.writeToParcel(parcel, 0);
        parcel.setDataPosition(0);
        LoggingStats readLoggingStats = LoggingStats.CREATOR.createFromParcel(parcel);

        // Check
        verifyLoggingStats(readLoggingStats);
    }

    private LoggingStats createLoggingStats() {
        // Wifi
        LoggingStats.Wifi wifi = LoggingStats.Wifi.builder()
                .linkSpeed(1)
                .frequency(2)
                .channelWidth("abc")
                .rssi(3)
                .score(4)
                .txBad(5)
                .txRetries(6)
                .txSuccess(7)
                .rxSuccess(8)
                .txTime(9)
                .rxTime(10)
                .onTime(11)
                .ccaBusyTime(12)
                .contentionAverageTime(13)
                .contentionNumOfSamples(14)
                .numOfTxTriesInDriver(15)
                .integralUsedDescriptorInDriver(16)
                .wifiGeneration(17)
                .ipLinkVerifierResult(18)
                .txPackets(19)
                .rxPackets(20)
                .build();

        // TcpProtocol
        LoggingStats.TcpProtocol tcpProtocol = LoggingStats.TcpProtocol.builder()
                .tcpLossUndo(1)
                .tcpLossFailures(2)
                .tcpLostRetransmit(3)
                .tcpRetransFail(4)
                .tcpTimeouts(5)
                .build();

        // Sensor
        LoggingStats.Sensor sensor = LoggingStats.Sensor.builder()
                .acceleration(1.1f)
                .stepCount(2)
                .build();

        // Activity
        LoggingStats.Activity activity = LoggingStats.Activity.builder()
                .type(1)
                .confidence(2)
                .isMoving(true)
                .build();

        // InferenceResult
        LoggingStats.InferenceResult inferenceResult = LoggingStats.InferenceResult.builder()
                .primary(1.1f)
                .secondary(2.2f)
                .build();

        return LoggingStats.builder()
                .wifi(wifi)
                .tcpProtocol(tcpProtocol)
                .sensor(sensor)
                .activity(activity)
                .inferenceResult(inferenceResult)
                .build();
    }

    private void verifyLoggingStats(LoggingStats loggingStats) {
        // Wifi
        LoggingStats.Wifi wifi = loggingStats.getWifi();
        assertEquals(1, wifi.getLinkSpeed());
        assertEquals(2, wifi.getFrequency());
        assertEquals("abc", wifi.getChannelWidth());
        assertEquals(3, wifi.getRssi());
        assertEquals(4, wifi.getScore());
        assertEquals(5, wifi.getTxBad());
        assertEquals(6, wifi.getTxRetries());
        assertEquals(7, wifi.getTxSuccess());
        assertEquals(8, wifi.getRxSuccess());
        assertEquals(9, wifi.getTxTime());
        assertEquals(10, wifi.getRxTime());
        assertEquals(11, wifi.getOnTime());
        assertEquals(12, wifi.getCcaBusyTime());
        assertEquals(13, wifi.getContentionAverageTime());
        assertEquals(14, wifi.getContentionNumOfSamples());
        assertEquals(15, wifi.getNumOfTxTriesInDriver());
        assertEquals(16, wifi.getIntegralUsedDescriptorInDriver());
        assertEquals(17, wifi.getWifiGeneration());
        assertEquals(18, wifi.getIpLinkVerifierResult());
        assertEquals(19, wifi.getTxPackets());
        assertEquals(20, wifi.getRxPackets());

        // TcpProtocol
        LoggingStats.TcpProtocol tcpProtocol = loggingStats.getTcpProtocol();
        assertEquals(1, tcpProtocol.getTcpLossUndo());
        assertEquals(2, tcpProtocol.getTcpLossFailures());
        assertEquals(3, tcpProtocol.getTcpLostRetransmit());
        assertEquals(4, tcpProtocol.getTcpRetransFail());
        assertEquals(5, tcpProtocol.getTcpTimeouts());

        // Sensor
        LoggingStats.Sensor sensor = loggingStats.getSensor();
        assertEquals(1.1f, sensor.getAcceleration());
        assertEquals(2, sensor.getStepCount());

        // Activity
        LoggingStats.Activity activity = loggingStats.getActivity();
        assertEquals(1, activity.getType());
        assertEquals(2, activity.getConfidence());
        assertTrue(activity.isMoving());

        // InferenceResult
        LoggingStats.InferenceResult inferenceResult = loggingStats.getInferenceResult();
        assertEquals(1.1f, inferenceResult.getPrimary());
        assertEquals(2.2f, inferenceResult.getSecondary());
    }
}
