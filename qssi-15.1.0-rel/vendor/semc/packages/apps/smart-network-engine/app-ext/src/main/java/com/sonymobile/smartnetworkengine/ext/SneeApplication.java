/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.ext;

import android.app.Application;
import android.content.Context;

import androidx.annotation.Nullable;

public class SneeApplication extends Application {

    private static SneeApplication sInstance = null;

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
}
