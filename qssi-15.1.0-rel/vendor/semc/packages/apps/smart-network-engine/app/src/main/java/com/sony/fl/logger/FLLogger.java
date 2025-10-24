package com.sony.fl.logger;

import com.sony.fl.Configuration;

/**
 * @author Masanobu Jimbo
 */


public class FLLogger {
    private static final LoggerInterface logger = setLogger();
    private static final int indexDiff = setIndexDiff();

    // ERROR
    public static void e(String msg) {
        logger.e(getClassName() + " " + getMethodName(), msg);
    }

    // WARN
    public static void w(String msg) {
        logger.w(getClassName() + " " + getMethodName(), msg);
    }

    // INFO
    public static void i(String msg) {
        logger.i(getClassName() + " " + getMethodName(), msg);
    }

    // DEBUG
    public static void d(String msg) {
        logger.d(getClassName() + " " + getMethodName(), msg);
    }

    private static String getClassName() {
        return Thread.currentThread().getStackTrace()[3 + indexDiff].getClassName();
    }

    private static String getMethodName() {
        return Thread.currentThread().getStackTrace()[3 + indexDiff].getMethodName();
    }

    private static LoggerInterface setLogger() {
        LoggerInterface lif;
        try {
            lif = (LoggerInterface)Class.forName(
                    Configuration.LOGGER_FQCN).newInstance();
        } catch (InstantiationException | IllegalAccessException | ClassNotFoundException e) {
            lif = new DummyLogger();
        }
        return lif;
    }

    private static int setIndexDiff() {
        StackTraceElement[] elements = Thread.currentThread().getStackTrace();
        int n = 0; 
        for (int i=0;i<elements.length;i++) {
            if (elements[i].getClassName().equals("java.lang.Thread")) {
                n = i;
                break;
            }
        }
        return n;
    }
}