package com.sony.fl.logger;
/**
 * @author Masanobu Jimbo
 */

public interface LoggerInterface {
    abstract public void e(String tag, String msg);
    abstract public void w(String tag, String msg);
    abstract public void i(String tag, String msg);
    abstract public void d(String tag, String msg);
}