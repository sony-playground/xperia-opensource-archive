/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.lib;

import androidx.annotation.Keep;

import com.sony.fl.logger.LoggerInterface;
import com.sonymobile.smartnetworkengine.util.Log;

@Keep
public class Logger implements LoggerInterface {
    @Override
    public void e(String tag, String msg) {
        Log.e(tag, msg);
    }

    @Override
    public void w(String tag, String msg) {
        Log.w(tag, msg);
    }

    @Override
    public void i(String tag, String msg) {
        Log.i(tag, msg);
    }

    @Override
    public void d(String tag, String msg) {
        Log.v(tag, msg);
    }
}
