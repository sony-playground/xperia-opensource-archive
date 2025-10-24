/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.util;

import androidx.annotation.NonNull;

public class Log {

    private static final String TAG = "SMARTNET";

    private static final int V = 0x0001;
    private static final int I = 0x0004;
    private static final int W = 0x0008;
    private static final int E = 0x0010;
    private static final int WTF = 0x0020;

    public enum Level {
        /** OFF log level constant that prints only errors */
        OFF(WTF | E),
        /** INFO log level constant */
        INFO(WTF | E | W | I),
        /** DEBUG log level constant that prints all logs */
        DEBUG(WTF | E | W | I | V);

        private final int mInternalLevel;

        Level(int internalLevel) {
            mInternalLevel = internalLevel;
        }

        int getInternalLevel() {
            return mInternalLevel;
        }
    }

    /** Keep track of current log level. Default is {@link Level#INFO}. */
    private static Level sLevel = Level.INFO;

    public static Level getLogLevel() {
        return sLevel;
    }

    public static void setLogLevel(@NonNull Level level) {
        sLevel = level;
    }

    public static void v(String tag, String msg) {
        if ((sLevel.getInternalLevel() & V) != 0) {
            android.util.Log.v(TAG, "[" + tag + "] " + msg);
        }
    }

    public static void i(String tag, String msg) {
        if ((sLevel.getInternalLevel() & I) != 0) {
            android.util.Log.i(TAG, "[" + tag + "] " + msg);
        }
    }

    public static void w(String tag, String msg) {
        if ((sLevel.getInternalLevel() & W) != 0) {
            android.util.Log.w(TAG, "[" + tag + "] " + msg);
        }
    }

    public static void e(String tag, String msg) {
        if ((sLevel.getInternalLevel() & E) != 0) {
            android.util.Log.e(TAG, "[" + tag + "] " + msg);
        }
    }

    public static void wtf(String tag, String msg) {
        if ((sLevel.getInternalLevel() & WTF) != 0) {
            android.util.Log.wtf(TAG, "[" + tag + "] " + msg);
        }
    }
}
