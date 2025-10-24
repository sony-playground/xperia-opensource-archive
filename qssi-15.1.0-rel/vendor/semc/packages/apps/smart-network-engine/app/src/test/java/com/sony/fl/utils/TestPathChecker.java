package com.sony.fl.utils;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.apache.commons.io.file.PathUtils;
import org.junit.After;
import org.junit.Before;
import org.junit.experimental.theories.DataPoints;
import org.junit.experimental.theories.Theories;
import org.junit.experimental.theories.Theory;
import org.junit.runner.RunWith;

@RunWith(Theories.class)
public class TestPathChecker {
    public static final Path INPUT_PATH = Paths.get("src/test/resources/input");

    @Before
    public void setUp() throws IOException {
        Files.createDirectories(INPUT_PATH);
        setAllAccess(INPUT_PATH);
    }

    @After
    public void tearDown() throws IOException {
        setAllAccess(INPUT_PATH);
        PathUtils.deleteDirectory(INPUT_PATH);
    }

    @DataPoints
    public static boolean[][] PARAMS = {
            { true, true, true },
            { true, true, true },
            { true, true, false },
            { true, false, true },
            { true, false, false },
            { false, true, true },
            { false, true, false },
            { false, false, true },
            { false, false, false },
    };

    private static void setAllAccess(Path path) {
        path.toFile().setReadable(true);
        path.toFile().setWritable(true);
        path.toFile().setExecutable(true);
    }

    // checkFolderPath
    @Theory
    public void testCheckFolderPathWithNotExists(boolean[] params) {
        Path notExistsFolderPath = Paths.get("src/test/resources/not_exists");
        boolean isReadable = params[0];
        boolean isWritable = params[1];
        boolean isExcutable = params[2];
        boolean result = PathChecker.checkFolderPath(notExistsFolderPath, isReadable, isWritable, isExcutable);
        assertFalse(result);
    }

    @Theory
    public void testCheckFolderPathWithNotFolder(boolean[] params) throws IOException {
        Path notFolerPath = Paths.get(this.INPUT_PATH.toString(), "is_file");
        notFolerPath.toFile().createNewFile();
        boolean isReadable = params[0];
        boolean isWritable = params[1];
        boolean isExcutable = params[2];
        boolean result = PathChecker.checkFolderPath(notFolerPath, isReadable, isWritable, isExcutable);
        assertFalse(result);
    }

    @Theory
    public void testCheckFolderPathWithNotReadable(boolean[] params) {
        INPUT_PATH.toFile().setReadable(false);
        boolean checkReadable = params[0];
        boolean checkWritable = params[1];
        boolean checkExcutable = params[2];
        boolean result = PathChecker.checkFolderPath(this.INPUT_PATH, checkReadable, checkWritable, checkExcutable);
        if (checkReadable) {
            assertFalse(result);
        } else {
            assertTrue(result);
        }
    }

    @Theory
    public void testCheckFolderPathWithNotWritable(boolean[] params) {
        INPUT_PATH.toFile().setWritable(false);
        boolean checkReadable = params[0];
        boolean checkWritable = params[1];
        boolean checkExcutable = params[2];
        boolean result = PathChecker.checkFolderPath(this.INPUT_PATH, checkReadable, checkWritable, checkExcutable);
        if (checkWritable) {
            assertFalse(result);
        } else {
            assertTrue(result);
        }
    }

    @Theory
    public void testCheckFolderPathWithNotExecutable(boolean[] params) {
        INPUT_PATH.toFile().setExecutable(false);
        boolean checkReadable = params[0];
        boolean checkWritable = params[1];
        boolean checkExcutable = params[2];
        boolean result = PathChecker.checkFolderPath(this.INPUT_PATH, checkReadable, checkWritable, checkExcutable);
        if (checkExcutable) {
            assertFalse(result);
        } else {
            assertTrue(result);
        }
    }

    // CheckFilePath
    @Theory
    public void testCheckFilePathWithNotExists(boolean[] params) {
        Path notExistsFilePath = Paths.get("src/test/resources/not_exists");
        boolean checkReadable = params[0];
        boolean checkWritable = params[1];
        boolean checkExcutable = params[2];
        boolean result = PathChecker.checkFilePath(notExistsFilePath, checkReadable, checkWritable, checkExcutable);
        assertFalse(result);
    }

    @Theory
    public void testCheckFilePathWithNotReadable(boolean[] params) {
        INPUT_PATH.toFile().setReadable(false);
        boolean checkReadable = params[0];
        boolean checkWritable = params[1];
        boolean checkExcutable = params[2];
        boolean result = PathChecker.checkFilePath(this.INPUT_PATH, checkReadable, checkWritable, checkExcutable);
        if (checkReadable) {
            assertFalse(result);
        } else {
            assertTrue(result);
        }
    }

    @Theory
    public void testCheckFilePathWithNotWritable(boolean[] params) {
        INPUT_PATH.toFile().setWritable(false);
        boolean checkReadable = params[0];
        boolean checkWritable = params[1];
        boolean checkExcutable = params[2];
        boolean result = PathChecker.checkFilePath(this.INPUT_PATH, checkReadable, checkWritable, checkExcutable);
        if (checkWritable) {
            assertFalse(result);
        } else {
            assertTrue(result);
        }
    }

    @Theory
    public void testCheckFilePathWithNotExecutable(boolean[] params) {
        INPUT_PATH.toFile().setExecutable(false);
        boolean checkReadable = params[0];
        boolean checkWritable = params[1];
        boolean checkExcutable = params[2];
        boolean result = PathChecker.checkFilePath(this.INPUT_PATH, checkReadable, checkWritable, checkExcutable);
        if (checkExcutable) {
            assertFalse(result);
        } else {
            assertTrue(result);
        }
    }
}

