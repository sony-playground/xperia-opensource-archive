/*
 * Copyright 2020 Sony Corporation
 */

package com.sonymobile.smartnetworkengine;

import static androidx.test.platform.app.InstrumentationRegistry.getInstrumentation;

import static com.sonymobile.smartnetworkengine.CaptivePortalTracker.MAX_NUM_OF_TRACKED_NETWORKS;

import static junit.framework.TestCase.assertEquals;
import static junit.framework.TestCase.assertFalse;
import static junit.framework.TestCase.assertTrue;

import static org.mockito.Mockito.clearInvocations;
import static org.mockito.Mockito.doReturn;
import static org.mockito.Mockito.spy;
import static org.mockito.Mockito.times;
import static org.mockito.Mockito.verify;

import android.content.Context;
import android.content.ContextWrapper;
import android.content.SharedPreferences;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiConfiguration.KeyMgmt;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sonymobile.smartnetworkengine.testutils.TestLooper;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Function;
import java.util.stream.IntStream;

/**
 * Verify {@link CaptivePortalTracker} implementation.
 */
@RunWith(AndroidJUnit4.class)
public class CaptivePortalTrackerTest {

    private static final Function<Integer, String> KEY_GENERATOR = i -> String.format("k%d", i);

    private final NetworkCapabilities NC_CAPTIVE_PORTAL_DETECTED;

    private final NetworkCapabilities NC_VALIDATION_COMPLETED;

    @Mock
    private WifiManager mWifiManager;

    private Context mTargetContext;

    private TestLooper mTestLooper;

    private CaptivePortalTracker mTracker;

    private WifiConfiguration mWifiConfiguration;

    @Mock
    private Network mNetwork;

    public CaptivePortalTrackerTest() {
        NC_CAPTIVE_PORTAL_DETECTED = new NetworkCapabilities();
        addCapability(NC_CAPTIVE_PORTAL_DETECTED,
                NetworkCapabilities.NET_CAPABILITY_CAPTIVE_PORTAL);
        NC_VALIDATION_COMPLETED = new NetworkCapabilities();
        addCapability(NC_VALIDATION_COMPLETED, NetworkCapabilities.NET_CAPABILITY_VALIDATED);
    }

    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);
        // Setup for target Context
        mTargetContext = spy(new MockContext(getInstrumentation().getTargetContext()));
        doReturn(mWifiManager).when(mTargetContext).getSystemService(Context.WIFI_SERVICE);
        // Setup for CaptivePortalTracker under test
        mTestLooper = new TestLooper();
        mTracker = new CaptivePortalTracker(mTargetContext, mTestLooper.getLooper());
        // Clear preferences
        fillPreferenceWithDummyInfo(0);
    }

    @After
    public void tearDown() {
        mTracker.stop();
        mTestLooper.dispatchAll();
    }

    @Test
    public void testConnectedToCaptivePortal_wpaPsk() {
        setupWifiConnectionInfo(KeyMgmt.WPA_PSK);
        testConnectedToCaptivePortal(true /* expect detection */);
    }

    @Test
    public void testConnectedToCaptivePortal_sae() {
        setupWifiConnectionInfo(KeyMgmt.SAE);
        testConnectedToCaptivePortal(true /* expect detection */);
    }

    @Test
    public void testConnectedToCaptivePortal_wpaEap() {
        setupWifiConnectionInfo(KeyMgmt.WPA_EAP);
        testConnectedToCaptivePortal(false /* expect detection */);
    }

    @Test
    public void testConnectedToNonCaptivePortal_wpaPsk() {
        setupWifiConnectionInfo(KeyMgmt.WPA_PSK);
        testConnectedToNonCaptivePortal(false /* ever detected */);
    }

    @Test
    public void testConnectedToNonCaptivePortal_sae() {
        setupWifiConnectionInfo(KeyMgmt.SAE);
        testConnectedToNonCaptivePortal(false /* ever detected */);
    }

    @Test
    public void testConnectedToNonCaptivePortal_wpaEap() {
        setupWifiConnectionInfo(KeyMgmt.WPA_EAP);
        testConnectedToNonCaptivePortal(false /* ever detected */);
    }

    @Test
    public void testConnectedToNonCaptivePortal_everDetected() {
        setupWifiConnectionInfo(KeyMgmt.WPA_PSK);

        // Actions
        testConnectedToCaptivePortal(true /* expect detection */);

        // Check (to make sure one entry exists in shared preferences)
        SharedPreferences sharedPrefs = getTargetSharedPreferences();
        String key = sharedPrefs.getAll().keySet().stream().findFirst().orElse("");
        assertFalse(key.isEmpty());

        sharedPrefs.edit().putLong(key, 1).commit();
        clearInvocations(mWifiManager);

        // Actions
        testConnectedToNonCaptivePortal(true /* ever detected */);

        // Check (to make sure the entry has been updated by 2nd connection)
        assertTrue(sharedPrefs.getLong(key, 1) != 1);
    }

    @Test
    public void testCleanupOverflowEntries() {
        fillPreferenceWithDummyInfo(MAX_NUM_OF_TRACKED_NETWORKS + 2);

        // Action
        mTracker.start();
        mTestLooper.dispatchAll();

        // Check
        SharedPreferences sharedPrefs = getTargetSharedPreferences();
        assertEquals(MAX_NUM_OF_TRACKED_NETWORKS, sharedPrefs.getAll().size());
        assertFalse(sharedPrefs.contains(KEY_GENERATOR.apply(1)));
        assertFalse(sharedPrefs.contains(KEY_GENERATOR.apply(2)));
        assertTrue(sharedPrefs.contains(KEY_GENERATOR.apply(MAX_NUM_OF_TRACKED_NETWORKS + 1)));
        assertTrue(sharedPrefs.contains(KEY_GENERATOR.apply(MAX_NUM_OF_TRACKED_NETWORKS + 2)));
    }

    @Test
    public void testCleanupOverflowEntries_noOverflow() {
        fillPreferenceWithDummyInfo(MAX_NUM_OF_TRACKED_NETWORKS - 2);

        // Action
        mTracker.start();
        mTestLooper.dispatchAll();

        // Check
        SharedPreferences sharedPrefs = getTargetSharedPreferences();
        assertEquals(MAX_NUM_OF_TRACKED_NETWORKS - 2, sharedPrefs.getAll().size());
        assertTrue(sharedPrefs.contains(KEY_GENERATOR.apply(1)));
        assertTrue(sharedPrefs.contains(KEY_GENERATOR.apply(2)));
        assertFalse(sharedPrefs.contains(KEY_GENERATOR.apply(MAX_NUM_OF_TRACKED_NETWORKS)));
        assertFalse(sharedPrefs.contains(KEY_GENERATOR.apply(MAX_NUM_OF_TRACKED_NETWORKS - 1)));
    }

    @Test
    public void testCleanupOverflowEntries_noOverflow_max() {
        fillPreferenceWithDummyInfo(MAX_NUM_OF_TRACKED_NETWORKS);

        // Action
        mTracker.start();
        mTestLooper.dispatchAll();

        // Check
        SharedPreferences sharedPrefs = getTargetSharedPreferences();
        assertEquals(MAX_NUM_OF_TRACKED_NETWORKS, sharedPrefs.getAll().size());
        assertTrue(sharedPrefs.contains(KEY_GENERATOR.apply(1)));
        assertTrue(sharedPrefs.contains(KEY_GENERATOR.apply(MAX_NUM_OF_TRACKED_NETWORKS)));
    }

    @Test
    public void testCleanupOverflowEntries_noOverflow_zero() {
        fillPreferenceWithDummyInfo(0);

        // Action
        mTracker.start();
        mTestLooper.dispatchAll();

        // Check
        SharedPreferences sharedPrefs = getTargetSharedPreferences();
        assertEquals(0, sharedPrefs.getAll().size());
    }

    private void testConnectedToCaptivePortal(boolean expectDetection) {
        SharedPreferences sharedPrefs = getTargetSharedPreferences();
        int currentNumOfEntries = sharedPrefs.getAll().size();
        int expectNumOfEntries = expectDetection ? currentNumOfEntries + 1 : currentNumOfEntries;

        // Action-1
        mTracker.start();
        mTestLooper.dispatchAll();

        // Check
        assertFalse(mTracker.isEverCaptivePortalDetected(mWifiConfiguration));

        // Action-2 (Connected to Wifi network which is behind captive portal)
        mTracker.mWifiNetworkCallback.onCapabilitiesChanged(mNetwork, NC_CAPTIVE_PORTAL_DETECTED);

        // Check
        assertEquals(currentNumOfEntries, sharedPrefs.getAll().size());
        assertEquals(expectDetection, mTracker.isEverCaptivePortalDetected(mWifiConfiguration));
        verify(mWifiManager, times(1)).getConnectionInfo();

        // Action-3 (Still behind captive portal)
        mTracker.mWifiNetworkCallback.onCapabilitiesChanged(mNetwork, NC_CAPTIVE_PORTAL_DETECTED);

        // Check
        assertEquals(currentNumOfEntries, sharedPrefs.getAll().size());
        assertEquals(expectDetection, mTracker.isEverCaptivePortalDetected(mWifiConfiguration));
        verify(mWifiManager, times(1)).getConnectionInfo();

        // Action-4 (Captive portal passed)
        mTracker.mWifiNetworkCallback.onCapabilitiesChanged(mNetwork, NC_VALIDATION_COMPLETED);

        // Check
        assertEquals(expectNumOfEntries, sharedPrefs.getAll().size());
        assertEquals(expectDetection, mTracker.isEverCaptivePortalDetected(mWifiConfiguration));
        verify(mWifiManager, times(1)).getConnectionInfo();

        // Action-5 (Disconnected)
        mTracker.mWifiNetworkCallback.onLost(mNetwork);

        // Check
        assertEquals(expectNumOfEntries, sharedPrefs.getAll().size());
        assertEquals(expectDetection, mTracker.isEverCaptivePortalDetected(mWifiConfiguration));
    }

    private void testConnectedToNonCaptivePortal(boolean everDetected) {
        SharedPreferences sharedPrefs = getTargetSharedPreferences();
        int currentNumOfEntries = sharedPrefs.getAll().size();

        // Action-1
        mTracker.start();
        mTestLooper.dispatchAll();

        // Check
        assertEquals(everDetected, mTracker.isEverCaptivePortalDetected(mWifiConfiguration));

        // Action-2 (Connected to Wifi network which is NOT behind captive portal)
        mTracker.mWifiNetworkCallback.onCapabilitiesChanged(mNetwork, new NetworkCapabilities());

        // Check
        assertEquals(currentNumOfEntries, sharedPrefs.getAll().size());
        assertEquals(everDetected, mTracker.isEverCaptivePortalDetected(mWifiConfiguration));
        verify(mWifiManager, times(1)).getConnectionInfo();

        // Action-3 (Validated)
        mTracker.mWifiNetworkCallback.onCapabilitiesChanged(mNetwork, NC_VALIDATION_COMPLETED);

        // Check
        assertEquals(currentNumOfEntries, sharedPrefs.getAll().size());
        assertEquals(everDetected, mTracker.isEverCaptivePortalDetected(mWifiConfiguration));
        verify(mWifiManager, times(1)).getConnectionInfo();

        // Action-4 (Disconnected)
        mTracker.mWifiNetworkCallback.onLost(mNetwork);

        // Check
        assertEquals(currentNumOfEntries, sharedPrefs.getAll().size());
        assertEquals(everDetected, mTracker.isEverCaptivePortalDetected(mWifiConfiguration));
    }

    private void setupWifiConnectionInfo(int keyMgmt) {
        // for getConnectionInfo
        WifiInfo wifiInfo = new WifiInfo.Builder()
                .setNetworkId(1)
                .build();
        doReturn(wifiInfo).when(mWifiManager).getConnectionInfo();
        // for getPrivilegedConfiguredNetworks
        mWifiConfiguration = new WifiConfiguration();
        mWifiConfiguration.networkId = wifiInfo.getNetworkId();
        mWifiConfiguration.SSID = "\"TEST_AP\"";
        mWifiConfiguration.allowedKeyManagement.set(keyMgmt);
        List<WifiConfiguration> configs = new ArrayList<>();
        configs.add(mWifiConfiguration);
        doReturn(configs).when(mWifiManager).getPrivilegedConfiguredNetworks();
    }

    private void fillPreferenceWithDummyInfo(int num) {
        SharedPreferences.Editor editor = getTargetSharedPreferences().edit();
        IntStream.rangeClosed(1, num).forEach(i -> editor.putLong(KEY_GENERATOR.apply(i), i));
        editor.clear().commit();
    }

    private SharedPreferences getTargetSharedPreferences() {
        return mTargetContext.getSharedPreferences(
                CaptivePortalTracker.SHARED_PREFS_FILENAME, Context.MODE_PRIVATE);
    }

    private void addCapability(NetworkCapabilities nc, int capability) {
        try {
            //noinspection JavaReflectionMemberAccess
            NetworkCapabilities.class.getDeclaredMethod("addCapability", int.class)
                    .invoke(nc, capability);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    private static class MockContext extends ContextWrapper {

        MockContext(Context base) {
            super(base);
        }

        @Override
        public SharedPreferences getSharedPreferences(String name, int mode) {
            return super.getSharedPreferences(name + ".test", mode);
        }
    }
}
