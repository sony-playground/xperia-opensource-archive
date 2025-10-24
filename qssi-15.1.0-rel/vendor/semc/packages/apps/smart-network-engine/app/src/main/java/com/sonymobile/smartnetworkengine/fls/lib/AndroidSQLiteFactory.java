/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.lib;

import androidx.annotation.Keep;

import com.sony.fl.db.DB;
import com.sony.fl.db.DBFactory;
import com.sony.fl.utils.PathChecker;
import com.sonymobile.smartnetworkengine.util.Log;

import java.io.File;
import java.nio.file.Path;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

@Keep
public class AndroidSQLiteFactory implements DBFactory {

    private static final String TAG = AndroidSQLiteFactory.class.getSimpleName();

    private static final String DB_FILENAME = "sqlite.db";

    private static final Map<File, DB> DB_INSTANCES = new ConcurrentHashMap<>();

    @Override
    public DB getDB(Path dirPath) {
        if (!PathChecker.checkFolderPath(dirPath, true, true, true)) {
            Log.w(TAG, "invalid path is specified: " + dirPath);
            return null;
        }
        // Database file existence check is needed at least for unit testing as the file is often
        // removed at the end of each test.
        return DB_INSTANCES.compute(getDatabaseFile(dirPath),
                (k, v) -> (v == null || !k.exists()) ? new AndroidSQLite(k) : v);
    }

    /**
     * Return a {@link File} instance pointing to a SQLite database file.
     */
    private File getDatabaseFile(Path dirPath) {
        return new File(dirPath.toFile(), DB_FILENAME);
    }
}
