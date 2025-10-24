/*
 * Copyright (C) 2019 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.util;

import static com.sonymobile.smartnetworkengine.Constants.PROP_IDD_DEBUG_MODE_ENABLED;

import android.content.Context;
import android.os.Build;
import android.os.SystemProperties;
import android.system.ErrnoException;
import android.system.Os;

import androidx.annotation.NonNull;

import com.google.protobuf.GeneratedMessageLite;
import com.sonyericsson.idd.api.Idd;

import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.function.UnaryOperator;

/**
 * This class provides IDD wrapper APIs which are required for debugging/testing purpose.
 */
public class IddWrapper {

    private static final boolean DEBUG_BUILD = Build.TYPE.equals("userdebug");

    /** IDD debug filename generator */
    private static final UnaryOperator<String> DEBUG_FILENAME_GENERATOR =
            s -> String.format("idd_%s.dat", s);

    /** Symbolic link filename which is linked to latest IDD debug file */
    private static final String LINK_NAME_TO_LATEST_DEBUG_FILE = "idd_latest.dat";

    /**
     * A wrapper method of {@link Idd#addEvent(Object)}.
     *
     * For debugging purpose, this method writes the data, which is sent to IDD daemon, into
     * a file if corresponding debug mode is enabled.
     */
    public static void addEvent(@NonNull Context context, @NonNull GeneratedMessageLite msg) {
        Idd.addEvent(msg);
        if (DEBUG_BUILD
                /* Intentionally use DEBUG_BUILD instead of isDebugBuild method in order to
                 * write idd debug file even if ForcibleReleaseBuild is enabled. */
                && SystemProperties.getBoolean(PROP_IDD_DEBUG_MODE_ENABLED, false)) {
            String fileName = getDebugFileName();
            // Write the data into a file
            createDebugFile(context, fileName, msg.toByteArray());
            // Update a symbolic link to the file above
            updateSymlinkToDebugFile(context, fileName);
        }
    }

    private static String getDebugFileName() {
        String timestamp = new SimpleDateFormat("yyMMdd_HHmm_ss", Locale.US).format(new Date());
        return DEBUG_FILENAME_GENERATOR.apply(timestamp);
    }

    private static void createDebugFile(Context context, String fileName, byte[] data) {
        Path path = Paths.get(context.getFilesDir().getPath(), fileName);
        try (final OutputStream os = Files.newOutputStream(path);
             final BufferedOutputStream bos = new BufferedOutputStream(os)) {
            bos.write(data);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void updateSymlinkToDebugFile(Context context, String fileName) {
        Path linkPath = Paths.get(context.getFilesDir().getPath(), LINK_NAME_TO_LATEST_DEBUG_FILE);
        try {
            Files.deleteIfExists(linkPath);
            Os.symlink(fileName, linkPath.toString());
        } catch (IOException | ErrnoException e) {
            e.printStackTrace();
        }
    }
}
