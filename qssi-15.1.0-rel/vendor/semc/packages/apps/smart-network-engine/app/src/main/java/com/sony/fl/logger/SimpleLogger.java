package com.sony.fl.logger;
/**
 * @author Masanobu Jimbo
 */


public class SimpleLogger implements LoggerInterface {
    public void e(String tag, String msg) {
        System.out.println("e : [" + tag + "] " + msg);
    }

    public void w(String tag, String msg) {
        System.out.println("w : [" + tag + "] " + msg);
    }

    public void i(String tag, String msg) {
        System.out.println("i : [" + tag + "] " + msg);
    }

    public void d(String tag, String msg) {
        System.out.println("d : [" + tag + "] " + msg);
    }

}