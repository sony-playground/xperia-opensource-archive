/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.connected;

import static androidx.test.platform.app.InstrumentationRegistry.getInstrumentation;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.ArgumentMatchers.anyFloat;
import static org.mockito.ArgumentMatchers.eq;
import static org.mockito.Mockito.doReturn;
import static org.mockito.Mockito.never;
import static org.mockito.Mockito.spy;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import android.content.Context;
import android.content.ContextWrapper;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData;
import com.sonymobile.smartnetworkengine.SneApplication;
import com.sonymobile.smartnetworkengine.connected.ConnectedPhaseManager.CollectedDataHandler;
import com.sonymobile.smartnetworkengine.fls.FLSystemManager;
import com.sonymobile.smartnetworkengine.fls.Predictor;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

/**
 * Verify {@link CollectedDataHandler} implementation.
 */
@RunWith(AndroidJUnit4.class)
public class CollectedDataHandlerTest {

    @Mock
    private SneApplication mSneApplication;

    @Mock
    private FLSystemManager mFLSystemManager;

    @Mock
    private Predictor mPredictor;

    private CollectedDataHandler mCollectedDataHandler;

    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);
        // Setup for target Context
        Context targetContext = spy(new ContextWrapper(getInstrumentation().getTargetContext()));
        doReturn(mSneApplication).when(targetContext).getApplicationContext();
        when(mSneApplication.getFLSystemManager()).thenReturn(mFLSystemManager);
        doReturn(mPredictor).when(mFLSystemManager).getPredictor(
                mFLSystemManager.FEATURE_CONNECTED);
        mCollectedDataHandler = new CollectedDataHandler(targetContext);
    }

    @Test
    public void testOnAllStatsCollected() {
        // Prepare
        WifiPredictionData.SneWifiEvent wifiEvent = WifiPredictionData.SneWifiEvent.newBuilder()
                .setLoggedInfo(WifiPredictionData.SneLoggedInfo.newBuilder()
                        .setLoggedDuration(100000) // 100s
                        .build())
                .build();
        Predictor.PredictionResult predictionResult = Predictor.PredictionResult.builder()
                .scoreUsable(false)
                .modelVersion("test")
                .score(1f, 0.5f)
                .build();
        Predictor.PredictionResult predictionResult2 = Predictor.PredictionResult.builder()
                .scoreUsable(false)
                .modelVersion("test")
                .score(0f, 0.5f)
                .build();
        Predictor.PredictionResult predictionResult3 = Predictor.PredictionResult.builder()
                .scoreUsable(false)
                .modelVersion("test")
                .build();

        // Action
        mCollectedDataHandler.onAllStatsCollected(wifiEvent, 0, 100000, null);

        // Check (no previous wifiData)
        verify(mPredictor, never()).addTrainingData(any(), anyFloat());

        // Action
        mCollectedDataHandler.onAllStatsCollected(wifiEvent, 100000, 200000, predictionResult);

        // Check (no previous predictionResult)
        verify(mPredictor, never()).addTrainingData(any(), anyFloat());

        // Action
        mCollectedDataHandler.onAllStatsCollected(wifiEvent, 300000, 400000, predictionResult2);

        // Check (adding training data with false label)
        verify(mPredictor, times(1)).addTrainingData(eq(predictionResult), eq(0f));

        // Action
        mCollectedDataHandler.onAllStatsCollected(wifiEvent, 450000, 550000, predictionResult3);

        // Check (adding training data with true label)
        verify(mPredictor, times(1)).addTrainingData(eq(predictionResult2), eq(1f));

        // Action
        mCollectedDataHandler.onAllStatsCollected(wifiEvent, 550000, 650000, null);

        // Check (isScored is false)
        verify(mPredictor, times(2)).addTrainingData(any(), anyFloat());
    }

    @Test
    public void testDoesUserWantToKeepWifi() {
        // Prepare
        long connectedTimeMs = 100000;
        WifiPredictionData.SneWifiEvent wifiEvent = WifiPredictionData.SneWifiEvent.newBuilder()
                .setLoggedInfo(WifiPredictionData.SneLoggedInfo.newBuilder()
                        .setLoggedDuration(90001)
                        .build())
                .build();
        WifiPredictionData.SneWifiEvent wifiEvent2 = WifiPredictionData.SneWifiEvent.newBuilder()
                .setLoggedInfo(WifiPredictionData.SneLoggedInfo.newBuilder()
                        .setLoggedDuration(90000)
                        .build())
                .build();

        // Action & Check (connectionDuration > 90s && reconnectionPeriod < 90s)
        assertTrue(mCollectedDataHandler.doesUserWantToKeepWifi(wifiEvent, connectedTimeMs,
                connectedTimeMs - 89999));

        // Action & Check (connectionDuration <= 90s && reconnectionPeriod < 90s)
        assertFalse(mCollectedDataHandler.doesUserWantToKeepWifi(wifiEvent2, connectedTimeMs,
                connectedTimeMs - 89999));

        // Action & Check (connectionDuration > 90s && reconnectionPeriod >= 90s)
        assertFalse(mCollectedDataHandler.doesUserWantToKeepWifi(wifiEvent, connectedTimeMs,
                connectedTimeMs - 90000));

        // Action & Check (connectionDuration <= 90s && reconnectionPeriod >= 90s)
        assertFalse(mCollectedDataHandler.doesUserWantToKeepWifi(wifiEvent2, connectedTimeMs,
                connectedTimeMs - 90000));
    }
}
