/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.util;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;

import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.Optional;

/**
 * A utility class to find wifi statistics file path.
 */
public class WifiStatsNodeFinder {

    public enum StatsType {
        LL_STATS,
        BUF_INFO
    }

    /**
     * The path formats for wifi statistics files. Search is performed in the declared order.
     *
     * NOTE: This list may need to be updated every time when new platform is introduced as the path
     * may be changed.
     */
    private static final List<String> PATH_FORMATS = List.of(
            // Nagara
            "/sys/devices/platform/soc/1c00000.qcom,pcie/pci0000:00/0000:00:00.0/0000:01:00"
                    + ".0/net/%2$s/somcsne_%1$s",
            //Columbia
            "/sys/kernel/adrastea/somc_sne/%1$s",
            // Others
            "/sys/kernel/wifi/somc_sne/%1$s");

    /**
     * The found path format for this platform. This is needed to avoid unnecessary file access to
     * the {@link #PATH_FORMATS} occurred every time when {@link #findSourceNodePath(StatsType,
     * String)} is called.
     */
    @VisibleForTesting
    @Nullable
    /* private */ static String sFoundPathFormat;

    /**
     * Finds a proper full path pointing to wifi statistics file.
     */
    @Nullable
    public static Path findSourceNodePath(@NonNull StatsType type, @NonNull String interfaceName) {
        // No synchronization for |sFoundPathFormat| as not so important
        if (sFoundPathFormat == null) {
            Optional<String> pathFormatOpt = PATH_FORMATS.stream()
                    .filter(f -> {
                        // Construct a path to the node
                        Path nodePath = constructNodePath(f, type, interfaceName);
                        // Check if the node is accessible
                        try (InputStream notUsed = Files.newInputStream(nodePath)) {
                            return true;
                        } catch (IOException e) {
                            return false;
                        }
                    })
                    .findFirst();
            pathFormatOpt.ifPresent(f -> sFoundPathFormat = f);
            if (sFoundPathFormat == null) {
                return null;
            }
        }
        return constructNodePath(sFoundPathFormat, type, interfaceName);
    }

    private static Path constructNodePath(String pathFormat, StatsType type, String interfaceName) {
        return Paths.get(String.format(pathFormat, type.name().toLowerCase(), interfaceName));
    }
}
