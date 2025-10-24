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

/**
 * Request continuous NUD (Neighbor Unreachability Detection) to framework when wifi is not
 * preferred as default network during "connected" period - i.e. after wifi being default network.
 * This class is for compatibility to keep similar behavior as Android R sony device.
 */
public class NudRequester {
    private static final String TAG = NudRequester.class.getSimpleName();

    private static final int REQUEST_INTERVAL_MS = 3000;

    private final Object mRequestNudToken = new Object();

    private final DefaultNetworkController mDefaultNetworkController;

    private final WifiExtController mWifiExtController;

    private final Handler mHandler;

    private final ConnectivityManager mConnectivityManager;

    private boolean mWifiOnceBecomeDefaultNetwork;

    private boolean mWifiConnected;

    private boolean mStarted;

    // This callback runs on NudRequester thread.
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
                    mHandler.post(NudRequester.this::resetState);
                }

                @Override
                public void onPreferenceChanged() {
                    mHandler.post(() -> {
                        if (!mDefaultNetworkController.isWifiNetworkPreferred()) {
                            // Just to make sure no active nud request exists to start new one.
                            mHandler.removeCallbacksAndMessages(mRequestNudToken);
                            requestNudContinuously();
                        } else {
                            mHandler.removeCallbacksAndMessages(mRequestNudToken);
                        }
                    });
                }
            };

    public NudRequester(Context context, DefaultNetworkController networkController) {
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

    private void requestNudContinuously() {
        if (mStarted && mWifiConnected && mWifiOnceBecomeDefaultNetwork) {
            Log.v(TAG, "call requestNudOperation()");
            mWifiExtController.requestNudOperation();
            mHandler.postDelayed(this::requestNudContinuously, mRequestNudToken,
                    REQUEST_INTERVAL_MS);
        }
    }

    private void resetState() {
        mWifiConnected = false;
        mWifiOnceBecomeDefaultNetwork = false;
        mHandler.removeCallbacksAndMessages(mRequestNudToken);
    }
}
