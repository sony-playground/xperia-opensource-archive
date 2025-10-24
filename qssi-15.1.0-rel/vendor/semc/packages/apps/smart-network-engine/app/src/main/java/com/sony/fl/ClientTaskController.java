package com.sony.fl;

import java.util.UUID;
import com.sony.fl.logger.FLLogger;

/**
 * @author Masanobu Jimbo
 */

public class ClientTaskController {
    private static final Object lock = new Object();
    private static volatile String key = "";

    public static String getTaskFlag() {
        String ret = "";
        synchronized(lock) {
            if (key.length() == 0) {
                key = UUID.randomUUID().toString();
                ret = key;
                FLLogger.d("Key = " + key);
            }
        }
        return ret;
    }

    public static void releaseTaskFlag(String argKey) {
        synchronized(lock) {
            if (key.equals(argKey)) {
                key = "";
                FLLogger.d("The key was released.");
            } else {
                FLLogger.i("The Key was wrong.");
            }
        }
    }

    public static void reset() {
        synchronized(lock) {
            key = "";
        }
        FLLogger.w("The key was released forcefully.");
    }
}