/*
 * Copyright 2020 Sony Corporation
 */

package com.sonymobile.smartnetworkengine;

import static androidx.test.platform.app.InstrumentationRegistry.getInstrumentation;

import static junit.framework.TestCase.assertFalse;
import static junit.framework.TestCase.assertTrue;

import static org.mockito.ArgumentMatchers.anyBoolean;
import static org.mockito.ArgumentMatchers.anyInt;
import static org.mockito.Mockito.never;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;

import android.net.wifi.WifiConnectedSessionInfo;
import android.net.wifi.WifiManager;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sonymobile.smartnetworkengine.CoreService.DefaultNetworkControllerImpl;
import com.sonymobile.smartnetworkengine.testutils.TestLooper;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

/**
 * Verify {@link DefaultNetworkControllerImpl} implementation.
 */
@RunWith(AndroidJUnit4.class)
public class DefaultNetworkControllerImplTest {

    private static final int SESSION_ID = 123456;

    private static final long DURATION_TIMER_MSEC = 9000;

    @Mock
    private WifiManager.ScoreUpdateObserver mScoreUpdateObserver;

    private TestLooper mLooper;

    private DefaultNetworkControllerImpl mDefaultNetworkController;

    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);
        mLooper = new TestLooper();
        mDefaultNetworkController = new DefaultNetworkControllerImpl(
                getInstrumentation().getTargetContext(), mLooper.getLooper());
        mDefaultNetworkController.onSetScoreUpdateObserver(mScoreUpdateObserver);
    }

    /**
     * Verify the behavior with typical use case.
     */
    @Test
    public void testBasicScenario() {
        // Action (wifi connection is established)
        mDefaultNetworkController.onStart(new WifiConnectedSessionInfo.Builder(SESSION_ID).build());

        // Check (wifi network is default)
        assertTrue(mDefaultNetworkController.isWifiNetworkPreferred());
        verify(mScoreUpdateObserver, never()).notifyStatusUpdate(anyInt(), anyBoolean());

        // Action (wifi quality degradation is predicted)
        mDefaultNetworkController.preferNonWifiNetwork(DURATION_TIMER_MSEC);

        // Check (mobile network is now default)
        assertFalse(mDefaultNetworkController.isWifiNetworkPreferred());
        verify(mScoreUpdateObserver, times(1)).notifyStatusUpdate(SESSION_ID, false);

        // Action (3 secs passes)
        mLooper.moveTimeForward(3000);
        mLooper.dispatchAll();

        // Check (nothing changes)
        assertFalse(mDefaultNetworkController.isWifiNetworkPreferred());
        verify(mScoreUpdateObserver, times(1)).notifyStatusUpdate(anyInt(), anyBoolean());

        // Action (wifi quality degradation is still predicted)
        mDefaultNetworkController.preferNonWifiNetwork(DURATION_TIMER_MSEC);

        // Check (nothing changes)
        assertFalse(mDefaultNetworkController.isWifiNetworkPreferred());
        verify(mScoreUpdateObserver, times(1)).notifyStatusUpdate(anyInt(), anyBoolean());

        // Action (the timer is expired without additional |preferNonWifiNetwork| call)
        mLooper.moveTimeForward(DURATION_TIMER_MSEC);
        mLooper.dispatchAll();

        // Check (wifi network is now default)
        assertTrue(mDefaultNetworkController.isWifiNetworkPreferred());
        verify(mScoreUpdateObserver, times(1)).notifyStatusUpdate(SESSION_ID, true);
        verify(mScoreUpdateObserver, times(2)).notifyStatusUpdate(anyInt(), anyBoolean());

        // Action (wifi disconnection happens)
        mDefaultNetworkController.onStop(SESSION_ID);

        // Check
        assertTrue(mDefaultNetworkController.isWifiNetworkPreferred());
        verify(mScoreUpdateObserver, times(2)).notifyStatusUpdate(anyInt(), anyBoolean());
    }

    /**
     * Verify the clean up behavior upon wifi disconnection.
     */
    @Test
    public void testCleanupOnDisconnection() {
        // Action
        mDefaultNetworkController.onStart(new WifiConnectedSessionInfo.Builder(SESSION_ID).build());
        mDefaultNetworkController.preferNonWifiNetwork(DURATION_TIMER_MSEC);

        // Check (mobile network is now default)
        assertFalse(mDefaultNetworkController.isWifiNetworkPreferred());
        verify(mScoreUpdateObserver, times(1)).notifyStatusUpdate(SESSION_ID, false);

        // Action
        mDefaultNetworkController.onStop(SESSION_ID);

        // Check (|DefaultNetworkController| is initialized)
        assertTrue(mDefaultNetworkController.isWifiNetworkPreferred());
        verify(mScoreUpdateObserver, times(1)).notifyStatusUpdate(anyInt(), anyBoolean());
    }

    /**
     * Verify that the interaction with wifi framework doesn't happen once |stop| is called.
     */
    @Test
    public void testDoesNothingAfterStop() {
        // Action (call the API just after initialization)
        mDefaultNetworkController.preferNonWifiNetwork(DURATION_TIMER_MSEC);

        // Check (does nothing to wifi framework)
        assertTrue(mDefaultNetworkController.isWifiNetworkPreferred());
        verify(mScoreUpdateObserver, never()).notifyStatusUpdate(anyInt(), anyBoolean());

        // Action (call the API after |stop|)
        mDefaultNetworkController.onStart(new WifiConnectedSessionInfo.Builder(SESSION_ID).build());
        mDefaultNetworkController.onStop(SESSION_ID);

        // Check (does nothing to wifi framework)
        assertTrue(mDefaultNetworkController.isWifiNetworkPreferred());
        verify(mScoreUpdateObserver, never()).notifyStatusUpdate(anyInt(), anyBoolean());
    }

// TODO: Recover this test scenario probably as ConnectedManager unit test.
//
//    /**
//     * Verify the interaction with wifi framework depending on 'Smart Connectivity' on/off.
//     */
//    @Test
//    public void testWifiNetworkScoreSupportOnOff() {
//        mDefaultNetworkController.setWifiNetworkScoreSupportEnabled(false);
//
//        // Action
//        mDefaultNetworkController.onStart(SESSION_ID);
//        mDefaultNetworkController.preferNonWifiNetwork(DURATION_TIMER_MSEC);
//
//        // Check (does nothing to wifi framework)
//        assertTrue(mDefaultNetworkController.isWifiNetworkPreferred());
//        verify(mScoreUpdateObserver, never()).notifyStatusUpdate(anyInt(), anyBoolean());
//
//        // Action (user enables 'Smart Connectivity')
//        mDefaultNetworkController.setWifiNetworkScoreSupportEnabled(true);
//
//        // Check (nothing changes and wifi network is default)
//        assertTrue(mDefaultNetworkController.isWifiNetworkPreferred());
//        verify(mScoreUpdateObserver, never()).notifyStatusUpdate(anyInt(), anyBoolean());
//
//        // Action (wifi quality degradation is predicted)
//        mDefaultNetworkController.preferNonWifiNetwork(DURATION_TIMER_MSEC);
//
//        // Check (mobile network is now default)
//        assertFalse(mDefaultNetworkController.isWifiNetworkPreferred());
//        verify(mScoreUpdateObserver, times(1)).notifyStatusUpdate(SESSION_ID, false);
//
//        // Action (user disables 'Smart Connectivity')
//        mDefaultNetworkController.setWifiNetworkScoreSupportEnabled(false);
//
//        // Check (wifi network is now default)
//        assertTrue(mDefaultNetworkController.isWifiNetworkPreferred());
//        verify(mScoreUpdateObserver, times(1)).notifyStatusUpdate(SESSION_ID, true);
//        verify(mScoreUpdateObserver, times(2)).notifyStatusUpdate(anyInt(), anyBoolean());
//
//        // Action (user enables 'Smart Connectivity')
//        mDefaultNetworkController.setWifiNetworkScoreSupportEnabled(true);
//
//        // Check (nothing changes)
//        assertTrue(mDefaultNetworkController.isWifiNetworkPreferred());
//        verify(mScoreUpdateObserver, times(2)).notifyStatusUpdate(anyInt(), anyBoolean());
//
//        // Action (user disables 'Smart Connectivity' while wifi network is default)
//        mDefaultNetworkController.setWifiNetworkScoreSupportEnabled(false);
//
//        // Check (nothing changes)
//        assertTrue(mDefaultNetworkController.isWifiNetworkPreferred());
//        verify(mScoreUpdateObserver, times(2)).notifyStatusUpdate(anyInt(), anyBoolean());
//
//        // Action (user enables 'Smart Connectivity' while wifi network is default)
//        mDefaultNetworkController.setWifiNetworkScoreSupportEnabled(true);
//
//        // Check (nothing changes)
//        assertTrue(mDefaultNetworkController.isWifiNetworkPreferred());
//        verify(mScoreUpdateObserver, times(2)).notifyStatusUpdate(anyInt(), anyBoolean());
//    }

    /**
     * Verify that the timer inside |PreferNonWifiNetwork| works as expected.
     */
    @Test
    public void testPreferNonWifiNetworkTimer() {
        // Action
        mDefaultNetworkController.onStart(new WifiConnectedSessionInfo.Builder(SESSION_ID).build());
        mDefaultNetworkController.preferNonWifiNetwork(3000);

        // Check (mobile network is now default)
        assertFalse(mDefaultNetworkController.isWifiNetworkPreferred());
        verify(mScoreUpdateObserver, times(1)).notifyStatusUpdate(SESSION_ID, false);

        // Action
        mLooper.moveTimeForward(1000);
        mLooper.dispatchAll();

        // Check (nothing changes)
        assertFalse(mDefaultNetworkController.isWifiNetworkPreferred());
        verify(mScoreUpdateObserver, times(1)).notifyStatusUpdate(anyInt(), anyBoolean());

        // Action
        mLooper.moveTimeForward(1000);
        mLooper.dispatchAll();

        // Check (nothing changes)
        assertFalse(mDefaultNetworkController.isWifiNetworkPreferred());
        verify(mScoreUpdateObserver, times(1)).notifyStatusUpdate(anyInt(), anyBoolean());

        // Action
        mLooper.moveTimeForward(1000);
        mLooper.dispatchAll();

        // Check (wifi network is now default)
        assertTrue(mDefaultNetworkController.isWifiNetworkPreferred());
        verify(mScoreUpdateObserver, times(1)).notifyStatusUpdate(SESSION_ID, true);
        verify(mScoreUpdateObserver, times(2)).notifyStatusUpdate(anyInt(), anyBoolean());
    }
}
