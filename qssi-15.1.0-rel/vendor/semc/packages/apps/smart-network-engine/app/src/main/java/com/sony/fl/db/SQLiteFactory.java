package com.sony.fl.db;

import java.nio.file.Path;
import java.util.HashMap;
import java.util.Map;

import com.sony.fl.logger.FLLogger;
import com.sony.fl.utils.PathChecker;

/**
 * @author Masanobu Jimbo
 */

public class SQLiteFactory implements DBFactory{
    private static Object lock = new Object();
    private static Map<Path, SQLite> sqliteMap = new HashMap<>();

    public DB getDB(Path dirPath) {
        SQLite sqlite = null;
        if (!PathChecker.checkFolderPath(dirPath, true, true, true)) {
            FLLogger.w(dirPath + " is an invalid path.");
            return null;
        }
        synchronized(lock) {
            if (sqliteMap.containsKey(dirPath)) {
                sqlite = sqliteMap.get(dirPath);
            } else {
                sqlite = new SQLite(dirPath);
                sqliteMap.put(dirPath, sqlite);
            }
        }
        return sqlite;
    }
}