/*
 * Copyright 2019 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.connected;

import static androidx.test.platform.app.InstrumentationRegistry.getInstrumentation;

import static com.sonymobile.smartnetworkengine.Constants.AVOID_FLAPPING_RSSI_RANGE;
import static com.sonymobile.smartnetworkengine.Constants.RSSI_CAP_THRESHOLD;

import static org.mockito.ArgumentMatchers.anyLong;
import static org.mockito.Mockito.doReturn;
import static org.mockito.Mockito.never;
import static org.mockito.Mockito.spy;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import android.content.Context;
import android.content.ContextWrapper;
import android.telephony.TelephonyManager;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData;
import com.sonymobile.smartnetworkengine.DefaultNetworkController;
import com.sonymobile.smartnetworkengine.SneApplication;
import com.sonymobile.smartnetworkengine.connected.logger.LoggerService.SessionInfo;
import com.sonymobile.smartnetworkengine.event.EventForwarder;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

/**
 * Verify {@link SneConnectedScore} implementation.
 */
@RunWith(AndroidJUnit4.class)
public class SneConnectedScoreTest {

    @Mock
    private TelephonyManager mTelephonyManager;

    @Mock
    private SneApplication mSneApplication;

    @Mock
    private EventForwarder mEventForwarder;

    @Mock
    private DefaultNetworkController mDefaultNetworkController;

    private SneConnectedScore mSneConnectedScore;

    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);
        // Setup for target Context
        Context targetContext = spy(new ContextWrapper(getInstrumentation().getTargetContext()));
        doReturn(mTelephonyManager).when(targetContext).getSystemService(Context.TELEPHONY_SERVICE);
        when(mSneApplication.getEventForwarder()).thenReturn(mEventForwarder);
        doReturn(mSneApplication).when(targetContext).getApplicationContext();
        // Setup for SneConnectedScore under test
        mSneConnectedScore = new SneConnectedScore(targetContext, mDefaultNetworkController);
        mSneConnectedScore.start();
    }

    @Test
    public void testInferenceUnderThreshold() {
        SessionInfo sessionInfo = SessionInfo.builder()
                .currentBssid("aa:bb:cc:dd:ee:ff")
                .homeNetwork(false)
                .userSelected(false)
                .build();
        WifiPredictionData.SneRuntimeStats runtimeStats = newTestRuntimeStats(0.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD, false, 60);

        // Action
        mSneConnectedScore.mInjector.onSessionInfoUpdate(sessionInfo);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check
        verify(mDefaultNetworkController, never()).preferNonWifiNetwork(anyLong());
    }

    @Test
    public void testInferenceUnderThreshold_moving() {
        SessionInfo sessionInfo = SessionInfo.builder()
                .currentBssid("aa:bb:cc:dd:ee:ff")
                .homeNetwork(false)
                .userSelected(false)
                .build();
        WifiPredictionData.SneRuntimeStats runtimeStats = newTestRuntimeStats(0.0f, 0.7f, 0.0f,
                RSSI_CAP_THRESHOLD, true, 60);

        // Action
        mSneConnectedScore.mInjector.onSessionInfoUpdate(sessionInfo);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check
        verify(mDefaultNetworkController).preferNonWifiNetwork(anyLong());
    }

    @Test
    public void testInferenceOverThreshold() {
        SessionInfo sessionInfo = SessionInfo.builder()
                .currentBssid("aa:bb:cc:dd:ee:ff")
                .homeNetwork(false)
                .userSelected(false)
                .build();
        WifiPredictionData.SneRuntimeStats runtimeStats = newTestRuntimeStats(1.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD, false, 60);

        // Action
        mSneConnectedScore.mInjector.onSessionInfoUpdate(sessionInfo);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check
        verify(mDefaultNetworkController).preferNonWifiNetwork(anyLong());
    }

    @Test
    public void testInferenceOverThreshold_badCellularQuality() {
        SessionInfo sessionInfo = SessionInfo.builder()
                .currentBssid("aa:bb:cc:dd:ee:ff")
                .homeNetwork(false)
                .userSelected(false)
                .build();
        WifiPredictionData.SneRuntimeStats runtimeStats = newTestRuntimeStats(1.0f, 0.0f, 1.0f,
                RSSI_CAP_THRESHOLD, false, 60);

        // Action
        mSneConnectedScore.mInjector.onSessionInfoUpdate(sessionInfo);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check
        verify(mDefaultNetworkController, never()).preferNonWifiNetwork(anyLong());
    }

    @Test
    public void testInferenceOverThreshold_goodRssi() {
        SessionInfo sessionInfo = SessionInfo.builder()
                .currentBssid("aa:bb:cc:dd:ee:ff")
                .homeNetwork(false)
                .userSelected(false)
                .build();
        WifiPredictionData.SneRuntimeStats runtimeStats = newTestRuntimeStats(1.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD + 1, false, 60);

        // Action
        mSneConnectedScore.mInjector.onSessionInfoUpdate(sessionInfo);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check
        verify(mDefaultNetworkController, never()).preferNonWifiNetwork(anyLong());
    }

    @Test
    public void testInferenceOverThreshold_homeNetwork() {
        SessionInfo sessionInfo = SessionInfo.builder()
                .currentBssid("aa:bb:cc:dd:ee:ff")
                .homeNetwork(true)
                .userSelected(false)
                .build();
        WifiPredictionData.SneRuntimeStats runtimeStats = newTestRuntimeStats(1.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD, false, 60);

        // Action
        mSneConnectedScore.mInjector.onSessionInfoUpdate(sessionInfo);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check
        verify(mDefaultNetworkController, never()).preferNonWifiNetwork(anyLong());
    }

    @Test
    public void testInferenceOverThreshold_userSelected() {
        SessionInfo sessionInfo = SessionInfo.builder()
                .currentBssid("aa:bb:cc:dd:ee:ff")
                .homeNetwork(false)
                .userSelected(true)
                .build();
        WifiPredictionData.SneRuntimeStats runtimeStats = newTestRuntimeStats(1.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD, false, 60);

        // Action
        mSneConnectedScore.mInjector.onSessionInfoUpdate(sessionInfo);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check
        verify(mDefaultNetworkController, never()).preferNonWifiNetwork(anyLong());
    }

    @Test
    public void testInferenceOverThreshold_roaming() {
        doReturn(true).when(mTelephonyManager).isNetworkRoaming();
        SessionInfo sessionInfo = SessionInfo.builder()
                .currentBssid("aa:bb:cc:dd:ee:ff")
                .homeNetwork(false)
                .userSelected(false)
                .build();
        WifiPredictionData.SneRuntimeStats runtimeStats = newTestRuntimeStats(1.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD, false, 60);

        // Action
        mSneConnectedScore.mInjector.onSessionInfoUpdate(sessionInfo);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check
        verify(mDefaultNetworkController, never()).preferNonWifiNetwork(anyLong());
    }

    @Test
    public void testInferenceFlapping() {
        SessionInfo sessionInfo = SessionInfo.builder()
                .currentBssid("aa:bb:cc:dd:ee:ff")
                .homeNetwork(false)
                .userSelected(false)
                .build();
        WifiPredictionData.SneRuntimeStats runtimeStats = newTestRuntimeStats(1.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD, false, 60);

        // Action-1
        mSneConnectedScore.mInjector.onSessionInfoUpdate(sessionInfo);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check (mobile network is now default)
        verify(mDefaultNetworkController, times(1)).preferNonWifiNetwork(anyLong());

        // Action-2: RSSI: OK, Inference: NG
        runtimeStats = newTestRuntimeStats(1.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD + AVOID_FLAPPING_RSSI_RANGE, false, 60);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check (mobile network is still default)
        verify(mDefaultNetworkController, times(2)).preferNonWifiNetwork(anyLong());

        // Action-3: RSSI: NG, Infer: OK
        runtimeStats = newTestRuntimeStats(0.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD + AVOID_FLAPPING_RSSI_RANGE - 1, false, 60);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check (mobile network is still default)
        verify(mDefaultNetworkController, times(3)).preferNonWifiNetwork(anyLong());

        // Action-4: RSSI: OK, Inference: OK
        runtimeStats = newTestRuntimeStats(0.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD + AVOID_FLAPPING_RSSI_RANGE, false, 60);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check (wifi network is now default)
        verify(mDefaultNetworkController, times(3)).preferNonWifiNetwork(anyLong());
    }

    @Test
    public void testInferenceFlapping_noCriteriaOnWifiInvolved() {
        SessionInfo sessionInfo = SessionInfo.builder()
                .currentBssid("aa:bb:cc:dd:ee:ff")
                .homeNetwork(false)
                .userSelected(false)
                .build();
        WifiPredictionData.SneRuntimeStats runtimeStats = newTestRuntimeStats(1.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD, false, 60);

        // Action-1
        mSneConnectedScore.mInjector.onSessionInfoUpdate(sessionInfo);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check (mobile network is now default)
        verify(mDefaultNetworkController, times(1)).preferNonWifiNetwork(anyLong());

        // Action-2: RSSI: NG, Inference: NG
        runtimeStats = newTestRuntimeStats(1.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD + 1, false, 60);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check (mobile network is still default)
        verify(mDefaultNetworkController, times(2)).preferNonWifiNetwork(anyLong());

        // Action-3: RSSI: NG, Inference: NG
        doReturn(true).when(mTelephonyManager).isNetworkRoaming(); // Enter roaming state
        runtimeStats = newTestRuntimeStats(1.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD, false, 60);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check (mobile network is still default)
        verify(mDefaultNetworkController, times(3)).preferNonWifiNetwork(anyLong());

        // Action-4: RSSI: OK, Inference: OK
        runtimeStats = newTestRuntimeStats(0.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD + AVOID_FLAPPING_RSSI_RANGE, false, 60);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check (wifi network is now default)
        verify(mDefaultNetworkController, times(3)).preferNonWifiNetwork(anyLong());
    }

    @Test
    public void testInferenceFlapping_noCriteriaOnNonWifiInvolved() {
        SessionInfo sessionInfo = SessionInfo.builder()
                .currentBssid("aa:bb:cc:dd:ee:ff")
                .homeNetwork(false)
                .userSelected(false)
                .build();
        WifiPredictionData.SneRuntimeStats runtimeStats = newTestRuntimeStats(1.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD, false, 60);

        // Action-1
        mSneConnectedScore.mInjector.onSessionInfoUpdate(sessionInfo);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check (mobile network is now default)
        verify(mDefaultNetworkController, times(1)).preferNonWifiNetwork(anyLong());

        // Action-2
        runtimeStats = newTestRuntimeStats(0.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD + AVOID_FLAPPING_RSSI_RANGE, false, 60);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check (wifi network is now default)
        verify(mDefaultNetworkController, times(1)).preferNonWifiNetwork(anyLong());

        // Action-3
        // Confirm RSSI cap to wifi does NOT work.
        runtimeStats = newTestRuntimeStats(0.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD + AVOID_FLAPPING_RSSI_RANGE - 1, false, 60);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check (wifi network is still default)
        verify(mDefaultNetworkController, times(1)).preferNonWifiNetwork(anyLong());
    }

    @Test
    public void testVelocityBasedScore_underThreshold() {
        SessionInfo sessionInfo = SessionInfo.builder()
                .currentBssid("aa:bb:cc:dd:ee:ff")
                .homeNetwork(false)
                .userSelected(false)
                .build();
        WifiPredictionData.SneRuntimeStats runtimeStats = newTestRuntimeStats(0.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD, false, 49);

        // Action
        mSneConnectedScore.mInjector.onSessionInfoUpdate(sessionInfo);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check
        verify(mDefaultNetworkController, times(1)).preferNonWifiNetwork(anyLong());
    }

    @Test
    public void testStopResetDefaultNetworkToWifi() {
        SessionInfo sessionInfo = SessionInfo.builder()
                .currentBssid("aa:bb:cc:dd:ee:ff")
                .homeNetwork(false)
                .userSelected(false)
                .build();
        // Switch default network to non-WiFi
        WifiPredictionData.SneRuntimeStats runtimeStats = newTestRuntimeStats(1.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD, false, 60);

        mSneConnectedScore.mInjector.onSessionInfoUpdate(sessionInfo);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Action
        mSneConnectedScore.stop();

        // Check
        verify(mDefaultNetworkController, times(1)).preferWifiNetwork();
    }

    @Test
    public void testEventForwarder() {
        SessionInfo sessionInfo = SessionInfo.builder()
                .currentBssid("aa:bb:cc:dd:ee:ff")
                .homeNetwork(false)
                .userSelected(false)
                .build();
        WifiPredictionData.SneRuntimeStats runtimeStats = newTestRuntimeStats(0.0f, 0.0f, 0.0f,
                RSSI_CAP_THRESHOLD, false, 60);

        // Action
        mSneConnectedScore.mInjector.onSessionInfoUpdate(sessionInfo);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check
        verify(mEventForwarder, times(1)).noteNetworkDecisionMade(true, runtimeStats);

        // Action
        runtimeStats = newTestRuntimeStats(1.0f, 0.0f, 0.0f, RSSI_CAP_THRESHOLD, false, 60);
        mSneConnectedScore.mInjector.onInferenceResultRequested(runtimeStats);

        // Check
        verify(mEventForwarder, times(1)).noteNetworkDecisionMade(false, runtimeStats);
    }

    private WifiPredictionData.SneRuntimeStats newTestRuntimeStats(float primaryInferenceResult,
            float secondaryInferenceResult, float cellInferenceResult, int rssi, boolean isMoving,
            int score) {
        WifiPredictionData.SneInferenceResult sneInferenceResult =
                WifiPredictionData.SneInferenceResult.newBuilder()
                        .setPrimary(primaryInferenceResult)
                        .setSecondary(secondaryInferenceResult)
                        .setVelocityBasedScore(score)
                        .setCellular(cellInferenceResult)
                        .build();
        WifiPredictionData.SneSensorData sneSensorData =
                WifiPredictionData.SneSensorData.newBuilder()
                        .setIsMoving(isMoving)
                        .build();
        WifiPredictionData.SneWifiInfo sneWifiInfo =
                WifiPredictionData.SneWifiInfo.newBuilder()
                        .setRssi(rssi)
                        .build();
        return WifiPredictionData.SneRuntimeStats.newBuilder()
                .setWifiInfo(sneWifiInfo)
                .setInferenceResult(sneInferenceResult)
                .setSensorData(sneSensorData)
                .build();
    }
}
