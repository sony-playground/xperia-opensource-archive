/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.comm;

import android.os.Build;

import com.sonymobile.smartnetworkengine.util.Log;

import okhttp3.OkHttpClient;
import okhttp3.logging.HttpLoggingInterceptor;
import okhttp3.logging.HttpLoggingInterceptor.Level;

class OkHttpClientFactory {

    // OkHttpClients should be shared
    private static final OkHttpClient CLIENT = new OkHttpClient();

    private static final boolean DEBUG_BUILD = Build.TYPE.equals("userdebug");

    static OkHttpClient getOkHttpClient() {
        // Add Logging Interceptor for debugging HTTP request and response data
        if (DEBUG_BUILD && Log.getLogLevel() == Log.Level.DEBUG) {
            HttpLoggingInterceptor logging = new HttpLoggingInterceptor(
                    message -> Log.v("OkHttp", message));
            logging.setLevel(Level.BODY);
            return CLIENT.newBuilder()
                    .addInterceptor(logging)
                    .build();
        }
        return CLIENT;
    }
    // TODO: okhttp's default User-Agent string should be changed?
}
