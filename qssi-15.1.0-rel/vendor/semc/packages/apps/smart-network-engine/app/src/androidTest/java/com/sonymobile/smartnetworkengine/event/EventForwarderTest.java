/*
 * Copyright 2020 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.event;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData;
import com.sonymobile.smartnetworkengine.api.ISneLoggingEventCallback;
import com.sonymobile.smartnetworkengine.api.ISneNetworkDecisionEventCallback;
import com.sonymobile.smartnetworkengine.api.LoggingStats;
import com.sonymobile.smartnetworkengine.connected.logger.LoggerService;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.MockitoAnnotations;

import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

/**
 * Verify {@link EventForwarder} implementation.
 */
@RunWith(AndroidJUnit4.class)
public class EventForwarderTest {

    private final EventForwarder mEventForwarder = new EventForwarder();

    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);
    }

    @Test
    public void testNoteLoggingStart() throws Exception {
        SneLoggingEventCallbackImpl callback = new SneLoggingEventCallbackImpl();

        // Action
        mEventForwarder.setLoggingEventCallback(callback);
        mEventForwarder.noteLoggingStart();

        // Check
        assertTrue(callback.mStarted.await(1, TimeUnit.SECONDS));
    }

    @Test
    public void testNoteLoggingStop() throws Exception {
        SneLoggingEventCallbackImpl callback = new SneLoggingEventCallbackImpl();

        // Action
        mEventForwarder.setLoggingEventCallback(callback);
        mEventForwarder.noteLoggingStop(LoggerService.StopReason.NORMAL);

        // Check
        assertTrue(callback.mStopped.await(1, TimeUnit.SECONDS));
    }

    @Test
    public void testNoteLoggingStatsUpdate() throws Exception {
        SneLoggingEventCallbackImpl callback = new SneLoggingEventCallbackImpl();

        // Action
        mEventForwarder.setLoggingEventCallback(callback);
        mEventForwarder.noteLoggingStatsUpdate(
                WifiPredictionData.SneRuntimeStats.newBuilder().build());

        // Check
        assertTrue(callback.mUpdated.await(1, TimeUnit.SECONDS));
    }

    @Test
    public void testNoteNetworkDecisionMade() throws Exception {
        SneNetworkDecisionEventCallbackImpl callback = new SneNetworkDecisionEventCallbackImpl();

        // Action
        mEventForwarder.setNetworkDecisionEventCallback(callback);
        mEventForwarder.noteNetworkDecisionMade(true,
                WifiPredictionData.SneRuntimeStats.newBuilder().build());

        // Check
        assertTrue(callback.mMade.await(1, TimeUnit.SECONDS));
    }

    @Test
    public void testToLoggingStats() {
        WifiPredictionData.SneRuntimeStats sneRuntimeStats = newTestRuntimeStats();

        // Sne sub messages
        WifiPredictionData.SneWifiInfo sneWifiInfo = sneRuntimeStats.getWifiInfo();
        WifiPredictionData.SneWifiTrafficStats sneWifiTrafficStats =
                sneRuntimeStats.getWifiTrafficStats();
        WifiPredictionData.SneTcpStats sneTcpStats = sneRuntimeStats.getTcpStats();
        WifiPredictionData.SneSensorData sneSensorData = sneRuntimeStats.getSensorData();
        WifiPredictionData.SneInferenceResult sneInferenceResult =
                sneRuntimeStats.getInferenceResult();
        // Action
        LoggingStats loggingStats = mEventForwarder.toLoggingStats(sneRuntimeStats);

        // Check
        // (Wifi)
        LoggingStats.Wifi wifi = loggingStats.getWifi();
        assertEquals(sneWifiInfo.getLinkSpeed(), wifi.getLinkSpeed());
        assertEquals(sneWifiInfo.getFrequency(), wifi.getFrequency());
        assertEquals(
                mEventForwarder.toChannelWidthString(sneWifiInfo.getChannelWidth()),
                wifi.getChannelWidth());
        assertEquals(sneWifiInfo.getRssi(), wifi.getRssi());
        assertEquals(sneWifiInfo.getScore(), wifi.getScore());
        assertEquals(sneWifiTrafficStats.getTxBad(), wifi.getTxBad());
        assertEquals(sneWifiTrafficStats.getTxRetries(), wifi.getTxRetries());
        assertEquals(sneWifiTrafficStats.getTxSuccess(), wifi.getTxSuccess());
        assertEquals(sneWifiTrafficStats.getRxSuccess(), wifi.getRxSuccess());
        assertEquals(sneWifiInfo.getTxTime(), wifi.getTxTime());
        assertEquals(sneWifiInfo.getRxTime(), wifi.getRxTime());
        assertEquals(sneWifiInfo.getOnTime(), wifi.getOnTime());
        assertEquals(sneWifiInfo.getCcaBusyTime(), wifi.getCcaBusyTime());
        assertEquals(sneWifiInfo.getContentionAverageTime(),
                wifi.getContentionAverageTime());
        assertEquals(sneWifiInfo.getContentionNumOfSamples(),
                wifi.getContentionNumOfSamples());
        assertEquals(sneWifiTrafficStats.getNumOfTxTriesInDriver(),
                wifi.getNumOfTxTriesInDriver());
        assertEquals(sneWifiTrafficStats.getIntegralUsedDescriptorInDriver(),
                wifi.getIntegralUsedDescriptorInDriver());
        assertEquals(sneWifiInfo.getWifiGeneration(), wifi.getWifiGeneration());
        assertEquals(sneWifiTrafficStats.getTxPkt(), wifi.getTxPackets());
        assertEquals(sneWifiTrafficStats.getRxPkt(), wifi.getRxPackets());

        // (TcpProtocol)
        LoggingStats.TcpProtocol tcpProtocol = loggingStats.getTcpProtocol();
        assertEquals(sneTcpStats.getTcpLossUndo(), tcpProtocol.getTcpLossUndo());
        assertEquals(sneTcpStats.getTcpLossFailures(),
                tcpProtocol.getTcpLossFailures());
        assertEquals(sneTcpStats.getTcpLostRetransmit(),
                tcpProtocol.getTcpLostRetransmit());
        assertEquals(sneTcpStats.getTcpRetransFail(),
                tcpProtocol.getTcpRetransFail());
        assertEquals(sneTcpStats.getTcpTimeouts(), tcpProtocol.getTcpTimeouts());

        // (Sensor)
        LoggingStats.Sensor sensor = loggingStats.getSensor();
        assertEquals(sneSensorData.getSensorAcceleration(), sensor.getAcceleration(), 0.0);
        assertEquals(0, sensor.getStepCount()); // No forward

        // (Activity)
        LoggingStats.Activity activity = loggingStats.getActivity();
        assertEquals(LoggingStats.Activity.TYPE_NO_RESULT, activity.getType()); // No forward
        assertEquals(0, activity.getConfidence()); // No forward
        assertEquals(sneSensorData.getIsMoving(), activity.isMoving());

        // (InferenceResult)
        LoggingStats.InferenceResult inferenceResult = loggingStats.getInferenceResult();
        assertEquals(sneInferenceResult.getPrimary(), inferenceResult.getPrimary(), 0.0);
        assertEquals(sneInferenceResult.getSecondary(), inferenceResult.getSecondary(), 0.0);
    }

    private WifiPredictionData.SneRuntimeStats newTestRuntimeStats() {
        WifiPredictionData.SneWifiInfo wifiInfo =
                WifiPredictionData.SneWifiInfo.newBuilder()
                        .setLinkSpeed(1)
                        .setFrequency(2)
                        .setChannelWidth(3) // 3:ScanResult.CHANNEL_WIDTH_80MHZ
                        .setRssi(4)
                        .setScore(5)
                        .setContentionAverageTime(6)
                        .setContentionNumOfSamples(7)
                        .setTxTime(8)
                        .setRxTime(9)
                        .setOnTime(10)
                        .setCcaBusyTime(11)
                        .setWifiGeneration(12)
                        .build();
        WifiPredictionData.SneWifiTrafficStats wifiTrafficStats =
                WifiPredictionData.SneWifiTrafficStats.newBuilder()
                        .setTxPkt(1)
                        .setRxPkt(2)
                        .setTxBad(3)
                        .setTxRetries(4)
                        .setTxSuccess(5)
                        .setRxSuccess(6)
                        .setNumOfTxTriesInDriver(7)
                        .setIntegralUsedDescriptorInDriver(8)
                        .build();
        WifiPredictionData.SneTcpStats tcpStats =
                WifiPredictionData.SneTcpStats.newBuilder()
                        .setTcpLossUndo(1)
                        .setTcpLossFailures(2)
                        .setTcpLostRetransmit(3)
                        .setTcpRetransFail(4)
                        .setTcpTimeouts(5)
                        .build();
        WifiPredictionData.SneSensorData sensorData =
                WifiPredictionData.SneSensorData.newBuilder()
                        .setSensorAcceleration(1.1f)
                        .setSensorStepCount(2)
                        .setSensorActivityType(3) // 3:STILL
                        .setSensorActivityConfidence(4)
                        .setIsMoving(true)
                        .build();
        WifiPredictionData.SneInferenceResult inferenceResult =
                WifiPredictionData.SneInferenceResult.newBuilder()
                        .setPrimary(1.1f)
                        .setSecondary(2.2f)
                        .build();

        return WifiPredictionData.SneRuntimeStats.newBuilder()
                .setWifiInfo(wifiInfo)
                .setWifiTrafficStats(wifiTrafficStats)
                .setTcpStats(tcpStats)
                .setSensorData(sensorData)
                .setInferenceResult(inferenceResult)
                .build();
    }

    static class SneLoggingEventCallbackImpl extends ISneLoggingEventCallback.Stub {
        final CountDownLatch mStarted = new CountDownLatch(1);
        final CountDownLatch mStopped = new CountDownLatch(1);
        final CountDownLatch mUpdated = new CountDownLatch(1);

        @Override
        public void onStarted() {
            mStarted.countDown();
        }

        @Override
        public void onStopped(int reason) {
            mStopped.countDown();
        }

        @Override
        public void onStatsUpdated(LoggingStats stats) {
            mUpdated.countDown();
        }
    }

    static class SneNetworkDecisionEventCallbackImpl extends ISneNetworkDecisionEventCallback.Stub {
        final CountDownLatch mMade = new CountDownLatch(1);

        @Override
        public void onDecisionMade(boolean wifiUsable, LoggingStats sourceStats) {
            mMade.countDown();
        }
    }
}
