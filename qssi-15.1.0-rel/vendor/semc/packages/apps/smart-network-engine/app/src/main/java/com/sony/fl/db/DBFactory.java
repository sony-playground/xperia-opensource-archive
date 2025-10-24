package com.sony.fl.db;

import java.nio.file.Path;

/**
 * @author Masanobu Jimbo
 */

public interface DBFactory {
    abstract public DB getDB(Path dirPath);
}