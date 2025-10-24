/*
 * Copyright 2018, 2019, 2020, 2021, 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine;

import android.app.Application;
import android.content.Context;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.sonymobile.smartnetworkengine.event.EventForwarder;
import com.sonymobile.smartnetworkengine.fls.FLSystemManager;

public class SneApplication extends Application {

    private static SneApplication sInstance = null;

    private EventForwarder mEventForwarder = null;

    private volatile WifiExtController mWifiExtController = null;

    private volatile FLSystemManager mFLSystemManager = null;

    @Override
    public void onCreate() {
        super.onCreate();
        sInstance = this;
    }

    /**
     * A convenient method to retrieve application context.
     *
     * Note that this method is currently intended to be used from
     * static utility class. Hence do not use from other type of class.
     */
    @Nullable
    public static Context getContext() {
        if (sInstance == null) {
            // Application class may not be initialized yet. (cf. JIML-147480)
            return null;
        }
        return sInstance.getApplicationContext();
    }

    /**
     * Returns {@link EventForwarder} instance.
     */
    @NonNull
    public synchronized EventForwarder getEventForwarder() {
        if (mEventForwarder == null) {
            mEventForwarder = new EventForwarder();
        }
        return mEventForwarder;
    }

    /**
     * Returns {@link WifiExtController} instance.
     */
    @Nullable
    public WifiExtController getWifiExtController() {
        return mWifiExtController;
    }

    /**
     * Sets {@link WifiExtController} instance.
     */
    void setWifiExtController(@NonNull WifiExtController wifiExtController) {
        mWifiExtController = wifiExtController;
    }

    /**
     * Returns {@link FLSystemManager} instance, or null if FL system is disabled.
     */
    @Nullable
    public FLSystemManager getFLSystemManager() {
        return mFLSystemManager;
    }

    /**
     * Sets {@link FLSystemManager} instance.
     */
    void setFLSystemManager(@NonNull FLSystemManager flSystemManager) {
        mFLSystemManager = flSystemManager;
    }
}
