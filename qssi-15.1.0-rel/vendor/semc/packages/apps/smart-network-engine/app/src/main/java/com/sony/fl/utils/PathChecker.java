package com.sony.fl.utils;

/**
 * @author Masanobu Jimbo
 */

import java.nio.file.Path;

import com.sony.fl.logger.FLLogger;

import java.nio.file.Files;

public class PathChecker {
    private static boolean checkPath(Path path, boolean isDirectory, boolean isReadable,
            boolean isWritable, boolean isExcutable) {
        if (!Files.exists(path)) {
            FLLogger.i(path.toString() + " is not found.");
            return false;
        }
        if (isDirectory && !Files.isDirectory(path)) {
            FLLogger.i(path.toString() + " is not a directory.");
            return false;
        }
        if (isReadable && !Files.isReadable(path)) {
            FLLogger.i(path.toString() + " is not readable.");
            return false;
        }
        if (isWritable && !Files.isWritable(path)) {
            FLLogger.i(path.toString() + " is not writeble.");
            return false;
        }
        if (isExcutable && !Files.isExecutable(path)) {
            FLLogger.i(path.toString() + " is not executable.");
            return false;
        }
        return true;
    }

    public static boolean checkFolderPath(Path dirPath, boolean isReadable,
            boolean isWritable, boolean isExcutable) {
        return checkPath(dirPath, true, isReadable, isWritable, isExcutable);
    }

    public static boolean checkFilePath(Path filePath, boolean isReadable,
            boolean isWritable, boolean isExcutable) {
        return checkPath(filePath, false, isReadable, isWritable, isExcutable);
    }
}

