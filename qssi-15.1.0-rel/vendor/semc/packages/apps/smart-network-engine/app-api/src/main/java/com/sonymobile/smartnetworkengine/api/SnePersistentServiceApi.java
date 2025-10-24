/*
 * Copyright 2021 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.api;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;

public class SnePersistentServiceApi {
    public static final String ACTION_REVERSE_BIND =
            "com.sonymobile.smartnetworkengine.intent.action.REVERSE_BIND";
    public static final String ACTION_REVERSE_UNBIND =
            "com.sonymobile.smartnetworkengine.intent.action.REVERSE_UNBIND";
    private static final String ENABLER_PKG = "com.sonymobile.smartnetworkengine";
    private static final String ENABLER_SERVICE =
            "com.sonymobile.smartnetworkengine.SnePersistentService";
    public static final String EXTRA_ENABLER_PKG = "packageName";
    public static final String EXTRA_ENABLER_CLASS = "className";

    /**
     * Request SnePersistentService to bind to specified service.
     */
    public static ComponentName reverseBindService(Context context, String packageName,
            String serviceClass) {
        Intent intent = new Intent(ACTION_REVERSE_BIND);
        intent.setClassName(ENABLER_PKG, ENABLER_SERVICE);
        intent.putExtra(EXTRA_ENABLER_PKG, packageName);
        intent.putExtra(EXTRA_ENABLER_CLASS, serviceClass);
        intent.addFlags(Intent.FLAG_RECEIVER_FOREGROUND);
        return context.startService(intent);
    }
}
