package com.sony.fl.logger;
/**
 * @author Masanobu Jimbo
 */


public class DummyLogger implements LoggerInterface {
    public void e(String tag, String msg) {}
    public void w(String tag, String msg) {}
    public void i(String tag, String msg) {}
    public void d(String tag, String msg) {}
}