/*
 * Copyright 2021 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.compatible;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.os.Handler;
import android.os.HandlerThread;

import androidx.annotation.NonNull;

import com.sonymobile.smartnetworkengine.DefaultNetworkController;
import com.sonymobile.smartnetworkengine.SneApplication;
import com.sonymobile.smartnetworkengine.WifiExtController;
import com.sonymobile.smartnetworkengine.util.Log;

import java.util.concurrent.TimeUnit;

/**
 * Adding wifi AP to blocklist, which disconnected after linger timer completion
 */
public class LingeredApBlocker {

    private static final String TAG = LingeredApBlocker.class.getSimpleName();

    // Make this threshold way before 30 sec to surely add blocklist before disconnection.
    private static final long MIN_TIME_TO_WAIT_BEFORE_BLOCKLIST_MILLIS =
            TimeUnit.SECONDS.toMillis(28);

    private final Object mRequestBlocklistToken = new Object();

    private final ConnectivityManager mConnectivityManager;

    private final DefaultNetworkController mDefaultNetworkController;

    private final WifiExtController mWifiExtController;

    private final Handler mHandler;

    private boolean mWifiConnected;

    private boolean mWifiOnceBecomeDefaultNetwork;

    private boolean mAlreadyBlocklisted;

    private boolean mStarted;

    // This callback runs on original thread.
    private final ConnectivityManager.NetworkCallback mDefaultNetworkCallback =
            new ConnectivityManager.NetworkCallback() {
                @Override
                public void onCapabilitiesChanged(@NonNull Network network,
                        @NonNull NetworkCapabilities nc) {
                    super.onCapabilitiesChanged(network, nc);
                    if (nc.hasTransport(NetworkCapabilities.TRANSPORT_WIFI)) {
                        mWifiOnceBecomeDefaultNetwork = true;
                    }
                }
            };

    private final DefaultNetworkController.StatusListener mStatusListener =
            new DefaultNetworkController.StatusListener() {
                @Override
                public void onStart() {
                    mHandler.post(() -> mWifiConnected = true);
                }

                @Override
                public void onStop() {
                    mHandler.post(LingeredApBlocker.this::resetState);
                }

                @Override
                public void onPreferenceChanged() {
                    mHandler.post(() -> {
                        if (!mDefaultNetworkController.isWifiNetworkPreferred()) {
                            if (isBlocklistingCondition()) {
                                mHandler.postDelayed(LingeredApBlocker.this::blocklistAp,
                                        mRequestBlocklistToken,
                                        MIN_TIME_TO_WAIT_BEFORE_BLOCKLIST_MILLIS);
                            }
                        } else {
                            mHandler.removeCallbacksAndMessages(mRequestBlocklistToken);
                        }
                    });
                }
            };

    public LingeredApBlocker(Context context, DefaultNetworkController networkController) {
        mConnectivityManager = (ConnectivityManager) context.getSystemService(
                Context.CONNECTIVITY_SERVICE);
        mDefaultNetworkController = networkController;
        mWifiExtController = ((SneApplication) context.getApplicationContext())
                .getWifiExtController();

        // Create original thread
        HandlerThread handlerThread = new HandlerThread(TAG);
        handlerThread.start();
        mHandler = new Handler(handlerThread.getLooper());
    }

    public void start() {
        mHandler.post(() -> {
            if (!mStarted) {
                resetState();
                mConnectivityManager.registerDefaultNetworkCallback(mDefaultNetworkCallback,
                        mHandler);
                mDefaultNetworkController.registerStatusListener(mStatusListener);
                mStarted = true;
            }
        });
    }

    public void stop() {
        mHandler.post(() -> {
            if (mStarted) {
                resetState();
                mConnectivityManager.unregisterNetworkCallback(mDefaultNetworkCallback);
                mDefaultNetworkController.unregisterStatusListener(mStatusListener);
                mStarted = false;
            }
        });
    }

    private void blocklistAp() {
        if (isBlocklistingCondition()) {
            Log.i(TAG, "call blocklistCurrentBssid()");
            mWifiExtController.blocklistCurrentBssid();
            mAlreadyBlocklisted = true;
        }
    }

    private void resetState() {
        mWifiConnected = false;
        mWifiOnceBecomeDefaultNetwork = false;
        mAlreadyBlocklisted = false;
        mHandler.removeCallbacksAndMessages(mRequestBlocklistToken);
    }

    private boolean isBlocklistingCondition() {
        return mStarted && mWifiConnected && mWifiOnceBecomeDefaultNetwork && !mAlreadyBlocklisted;
    }
}
