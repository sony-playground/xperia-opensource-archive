/*
 * Copyright 2017, 2022, 2023 Sony Corporation
 */

package com.sonymobile.smartnetworkengine;

import static com.sonymobile.smartnetworkengine.Constants.SETTINGS_VERBOSE_LOGGING_ENABLED;

import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.database.ContentObserver;
import android.net.ConnectivityManager;
import android.net.ConnectivityManager.NetworkCallback;
import android.net.LinkProperties;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkRequest;
import android.net.wifi.WifiConnectedSessionInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.provider.Settings;

import androidx.annotation.MainThread;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.sonymobile.smartnetworkengine.api.SnePersistentServiceApi;
import com.sonymobile.smartnetworkengine.compatible.LingeredApBlocker;
import com.sonymobile.smartnetworkengine.compatible.NudRequester;
import com.sonymobile.smartnetworkengine.connected.ConnectedPhaseManager;
import com.sonymobile.smartnetworkengine.entry.EntryPhaseManager;
import com.sonymobile.smartnetworkengine.fls.FLSystemService;
import com.sonymobile.smartnetworkengine.util.Log;
import com.sonymobile.smartnetworkengine.util.Log.Level;

import java.io.FileDescriptor;
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.Set;

public class CoreService extends Service {

    private static final String TAG = CoreService.class.getSimpleName();

    private static final boolean DEBUG_BUILD = Build.TYPE.equals("userdebug");

    private static final String ACTION_LOGGING_STARTED =
            "com.sonymobile.logalong.action.LOGGING_STARTED";
    private static final String ACTION_LOGGING_STOPPED =
            "com.sonymobile.logalong.action.LOGGING_STOPPED";

    private static final String SNE_EXT_PKG_NAME = "com.sonymobile.smartnetworkengine.ext";
    private static final String SNE_EXT_SERVICE_NAME =
            "com.sonymobile.smartnetworkengine.ext.ExtService";

    private WifiManager mWifiManager;

    private CaptivePortalTracker mCaptivePortalTracker;

    private NudRequester mNudRequester;

    private LingeredApBlocker mLingeredApBlocker;

    @Nullable
    private FLSystemService mFLSystemService;

    @Nullable
    private EntryPhaseManager mEntryPhaseManager;

    private ConnectedPhaseManager mConnectedPhaseManager;

    /**
     * A content observer to control log level upon verbose logging setting
     */
    private final ContentObserver mLogLevelObserver = new ContentObserver(new Handler()) {
        @Override
        public void onChange(boolean selfChange) {
            Log.setLogLevel(Settings.Global.getInt(getContentResolver(),
                    SETTINGS_VERBOSE_LOGGING_ENABLED, 0) == 1 ? Level.DEBUG : Level.INFO);
        }
    };

    /**
     * A broadcast receiver to control log level upon starting/existing Logalong
     */
    private final BroadcastReceiver mLogalongReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (ACTION_LOGGING_STARTED.equals(action)) {
                Log.setLogLevel(Level.DEBUG);
            } else if (ACTION_LOGGING_STOPPED.equals(action)) {
                Log.setLogLevel(Settings.Global.getInt(getContentResolver(),
                        SETTINGS_VERBOSE_LOGGING_ENABLED, 0) == 1 ? Level.DEBUG : Level.INFO);
            }
        }
    };

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        Log.i(TAG, "Service created");

        // Log level control through Settings provider
        getContentResolver().registerContentObserver(
                Settings.Global.getUriFor(SETTINGS_VERBOSE_LOGGING_ENABLED), false,
                mLogLevelObserver);
        Log.setLogLevel(Settings.Global.getInt(getContentResolver(),
                SETTINGS_VERBOSE_LOGGING_ENABLED, 0) == 1 ? Level.DEBUG : Level.INFO);

        // Log level control through Logalong application
        IntentFilter filter = new IntentFilter();
        filter.addAction(ACTION_LOGGING_STARTED);
        filter.addAction(ACTION_LOGGING_STOPPED);
        registerReceiver(mLogalongReceiver, filter, Context.RECEIVER_EXPORTED);

        mCaptivePortalTracker = CaptivePortalTracker.getInstance(this);
        mCaptivePortalTracker.start();

        DefaultNetworkControllerImpl defaultNetworkController = new DefaultNetworkControllerImpl(
                this, Looper.myLooper());
        ((SneApplication) getApplicationContext()).setWifiExtController(defaultNetworkController);

        mNudRequester = new NudRequester(this, defaultNetworkController);
        mNudRequester.start();
        mLingeredApBlocker = new LingeredApBlocker(this, defaultNetworkController);
        mLingeredApBlocker.start();

        // Bind ExtService on SmartNetworkEngineExt
        SnePersistentServiceApi.reverseBindService(this, SNE_EXT_PKG_NAME, SNE_EXT_SERVICE_NAME);

        if (getResources().getBoolean(R.bool.config_fl_system_enabled)) {
            // Initialize FL system
            mFLSystemService = new FLSystemService(this);
            mFLSystemService.start();
            ((SneApplication) getApplicationContext()).setFLSystemManager(mFLSystemService);

            // Initialize the entry feature
            mEntryPhaseManager = new EntryPhaseManager(this, defaultNetworkController);
            mEntryPhaseManager.start();
        }
        // Initialize the connected feature
        mConnectedPhaseManager = new ConnectedPhaseManager(this, defaultNetworkController);
        mConnectedPhaseManager.start();

        mWifiManager = (WifiManager) getSystemService(Context.WIFI_SERVICE);
        mWifiManager.setWifiConnectedNetworkScorer(getMainExecutor(), defaultNetworkController);
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        Log.i(TAG, "Service destroyed");

        mWifiManager.clearWifiConnectedNetworkScorer();
        mConnectedPhaseManager.stop();
        if (mEntryPhaseManager != null) {
            mEntryPhaseManager.quit();
        }
        if (mFLSystemService != null) {
            mFLSystemService.quit();
        }
        mLingeredApBlocker.stop();
        mNudRequester.stop();
        mCaptivePortalTracker.stop();
        unregisterReceiver(mLogalongReceiver);
        getContentResolver().unregisterContentObserver(mLogLevelObserver);
    }

    @Override
    protected void dump(FileDescriptor fd, PrintWriter writer, String[] args) {
        if (DEBUG_BUILD) {
            if (mEntryPhaseManager != null) {
                mEntryPhaseManager.dump(fd, writer, args);
            }
            if (mFLSystemService != null) {
                mFLSystemService.dump(fd, writer, args);
            }
        }
    }

    static class DefaultNetworkControllerImpl implements DefaultNetworkController,
            WifiExtController, WifiManager.WifiConnectedNetworkScorer {

        private static final String TAG = DefaultNetworkControllerImpl.class.getSimpleName();

        private static final String DEFAULT_PRIMARY_INTERFACE_NAME = "wlan0";

        /**
         * A token for {@link Handler#postDelayed(Runnable, Object, long)}
         */
        private static final Object PREFER_WIFI_TOKEN = new Object();

        /**
         * A lock object for updating network preference
         */
        private final Object mNetworkPrefLock = new Object();

        private final Handler mHandler;

        private final ConnectivityManager mConnectivityManager;

        @Nullable
        private WifiManager.ScoreUpdateObserver mScoreUpdateObserver;

        @Nullable
        private WifiConnectedSessionInfo mSessionInfo;

        private volatile boolean mWifiConnected;

        private boolean mWifiNetworkPreferred = true;

        private final Set<StatusListener> mStatusListeners = new HashSet<>();

        private final Set<StaStaConcurrencyListener> mStaStaConcurrencyListeners = new HashSet<>();

        private volatile boolean mStaStaConcurrent;

        /** Wifi network callback for detecting STA+STA Concurrency status */
        private final NetworkCallback mWifiNetworkCallback = new NetworkCallback() {
            private final Set<Network> mWifiNetworks = new HashSet<>();

            @Override
            public void onCapabilitiesChanged(@NonNull Network network,
                    @NonNull NetworkCapabilities networkCapabilities) {
                super.onCapabilitiesChanged(network, networkCapabilities);
                mWifiNetworks.add(network);
                if (mWifiNetworks.size() >= 2 && !mStaStaConcurrent) {
                    Log.v(TAG, "STA+STA concurrent: started");
                    mStaStaConcurrent = true;
                    notifyStaStaConcurrencyStatusChanged();
                }
            }

            @Override
            public void onLost(@NonNull Network network) {
                super.onLost(network);
                mWifiNetworks.remove(network);
                if (mWifiNetworks.size() < 2 && mStaStaConcurrent) {
                    Log.v(TAG, "STA+STA concurrent: ended");
                    mStaStaConcurrent = false;
                    notifyStaStaConcurrencyStatusChanged();
                }
            }

            private void notifyStaStaConcurrencyStatusChanged() {
                synchronized (mStaStaConcurrencyListeners) {
                    mStaStaConcurrencyListeners.forEach(l -> l.onStatusChanged(mStaStaConcurrent));
                }
            }
        };

        @NonNull
        private volatile String mPrimaryInterfaceName = DEFAULT_PRIMARY_INTERFACE_NAME;

        /** Default network callback for detecting wifi primary interface */
        private final NetworkCallback mDefaultNetworkCallback = new NetworkCallback() {
            @Nullable
            private Network mWifiDefaultNetwork;

            @Override
            public void onCapabilitiesChanged(@NonNull Network network,
                    @NonNull NetworkCapabilities networkCapabilities) {
                super.onCapabilitiesChanged(network, networkCapabilities);
                if (networkCapabilities.hasTransport(NetworkCapabilities.TRANSPORT_WIFI)) {
                    if (!network.equals(mWifiDefaultNetwork)
                            && networkCapabilities.getTransportInfo() instanceof WifiInfo) {
                        mWifiDefaultNetwork = network;
                        LinkProperties linkProperties = mConnectivityManager.getLinkProperties(
                                network);
                        if (linkProperties != null) {
                            mPrimaryInterfaceName = linkProperties.getInterfaceName();
                        } else { // Should never happen
                            Log.w(TAG, "failed to obtain link properties");
                        }
                        Log.v(TAG, "Primary interface: " + mPrimaryInterfaceName);
                    }
                } else {
                    maybeHandleWifiDefaultNetworkLost();
                }
            }

            @Override
            public void onLost(@NonNull Network network) {
                super.onLost(network);
                maybeHandleWifiDefaultNetworkLost();
            }

            private void maybeHandleWifiDefaultNetworkLost() {
                if (mWifiDefaultNetwork != null) {
                    mWifiDefaultNetwork = null;
                }
            }
        };

        DefaultNetworkControllerImpl(@NonNull Context context, @NonNull Looper looper) {
            mHandler = new Handler(looper);
            // Register network callbacks for STA+STA concurrency information APIs
            mConnectivityManager = context.getSystemService(ConnectivityManager.class);
            mConnectivityManager.registerNetworkCallback(
                    new NetworkRequest.Builder()
                            .addTransportType(NetworkCapabilities.TRANSPORT_WIFI)
                            .build(),
                    mWifiNetworkCallback);
            mConnectivityManager.registerDefaultNetworkCallback(mDefaultNetworkCallback);
        }

        // DefaultNetworkController implementations

        @Override
        public void registerStatusListener(@NonNull StatusListener statusListener) {
            synchronized (mStatusListeners) {
                mStatusListeners.add(statusListener);
            }
        }

        @Override
        public void unregisterStatusListener(@NonNull StatusListener statusListener) {
            synchronized (mStatusListeners) {
                mStatusListeners.remove(statusListener);
            }
        }

        @Override
        public boolean preferWifiNetwork() {
            synchronized (mNetworkPrefLock) {
                if (!mWifiConnected) {
                    Log.v(TAG, "Wifi is not connected. preferWifiNetwork does nothing");
                    return false;
                }
                // Update preference to Wifi preferred.
                if (!mWifiNetworkPreferred) {
                    mWifiNetworkPreferred = true;
                    handlePreferenceChange();
                    mHandler.removeCallbacksAndMessages(PREFER_WIFI_TOKEN);
                }
                Log.i(TAG, "Wifi is preferred as default network");
                return true;
            }
        }

        @Override
        public boolean preferNonWifiNetwork() {
            return preferNonWifiNetwork(0);
        }

        @Override
        public boolean preferNonWifiNetwork(long durationMs) {
            synchronized (mNetworkPrefLock) {
                if (!mWifiConnected) {
                    Log.v(TAG, "Wifi is not connected. preferNonWifiNetwork does nothing");
                    return false;
                }
                // Update preference to non-Wifi preferred.
                if (mWifiNetworkPreferred) {
                    mWifiNetworkPreferred = false;
                    handlePreferenceChange();
                }
                mHandler.removeCallbacksAndMessages(PREFER_WIFI_TOKEN);
                if (durationMs > 0) {
                    mHandler.postDelayed(this::preferWifiNetwork, PREFER_WIFI_TOKEN, durationMs);
                }
                Log.i(TAG, "Wifi is NOT preferred as default network" + (durationMs > 0 ?
                        " (duration: " + durationMs + " ms)" : ""));
                return true;
            }
        }

        @Override
        public boolean isWifiNetworkPreferred() {
            synchronized (mNetworkPrefLock) {
                return mWifiNetworkPreferred;
            }
        }

        // WifiExtController implementation

        @Override
        public void requestWifiStatsUpdate() {
            if (mScoreUpdateObserver != null && mWifiConnected) {
                mScoreUpdateObserver.triggerUpdateOfWifiUsabilityStats(getSessionId());
            }
        }

        @Override
        public void blocklistCurrentBssid() {
            if (mScoreUpdateObserver != null && mWifiConnected) {
                mScoreUpdateObserver.blocklistCurrentBssid(getSessionId());
            }
        }

        @Override
        public void requestNudOperation() {
            if (mScoreUpdateObserver != null && mWifiConnected) {
                mScoreUpdateObserver.requestNudOperation(getSessionId());
            }
        }

        @Override
        public boolean isUserSelected() {
            if (mSessionInfo != null && mWifiConnected) {
                return mSessionInfo.isUserSelected();
            }
            return false;
        }

        @Override
        public void registerStaStaConcurrencyListener(@NonNull StaStaConcurrencyListener listener) {
            synchronized (mStaStaConcurrencyListeners) {
                mStaStaConcurrencyListeners.add(listener);
            }
        }

        @Override
        public void unregisterStaStaConcurrencyListener(
                @NonNull StaStaConcurrencyListener listener) {
            synchronized (mStaStaConcurrencyListeners) {
                mStaStaConcurrencyListeners.remove(listener);
            }
        }

        @Override
        public boolean isStaStaConcurrent() {
            return mStaStaConcurrent;
        }

        // This method may return wrong information if clients call the method as soon as default
        // network is changed. This is because primary interface is updated when default network
        // is changed.
        // If you need to call this method at such time, you may need to obtain information from
        // network instance passed through default network callback.
        @NonNull
        @Override
        public String getPrimaryInterfaceName() {
            return mPrimaryInterfaceName;
        }

        @Override
        public boolean isWifiPreferred() {
            synchronized (mNetworkPrefLock) {
                return mWifiNetworkPreferred;
            }
        }

        // WifiConnectedNetworkScorer implementations

        @MainThread
        @Override
        public void onStart(@NonNull WifiConnectedSessionInfo sessionInfo) {
            Log.v(TAG, "Wifi connected: onStart() - sessionId=" + sessionInfo.getSessionId()
                    + ", userSelected=" + sessionInfo.isUserSelected());
            mSessionInfo = sessionInfo;
            mWifiConnected = true;
            synchronized (mStatusListeners) {
                mStatusListeners.forEach(StatusListener::onStart);
            }
        }

        @MainThread
        @Override
        public void onStop(int sessionId) {
            Log.v(TAG, "Wifi disconnected: onStop() - sessionId=" + sessionId);
            mWifiConnected = false;
            resetPreference();
            synchronized (mStatusListeners) {
                mStatusListeners.forEach(StatusListener::onStop);
            }
        }

        @MainThread
        @Override
        public void onSetScoreUpdateObserver(WifiManager.ScoreUpdateObserver observerImpl) {
            mScoreUpdateObserver = observerImpl;
        }

        // Private methods

        /**
         * Reset default network preference.
         */
        private void resetPreference() {
            synchronized (mNetworkPrefLock) {
                mHandler.removeCallbacksAndMessages(PREFER_WIFI_TOKEN);
                if (!mWifiNetworkPreferred) {
                    mWifiNetworkPreferred = true;
                    handlePreferenceChange();
                }
            }
        }

        /**
         * Propagate preference change to wifi framework.
         */
        private void handlePreferenceChange() {
            if (mScoreUpdateObserver != null && mWifiConnected) {
                mScoreUpdateObserver.notifyStatusUpdate(getSessionId(), mWifiNetworkPreferred);
                synchronized (mStatusListeners) {
                    mStatusListeners.forEach(StatusListener::onPreferenceChanged);
                }
            }
        }

        private int getSessionId() {
            return mSessionInfo != null ? mSessionInfo.getSessionId() : -1;
        }
    }
}
