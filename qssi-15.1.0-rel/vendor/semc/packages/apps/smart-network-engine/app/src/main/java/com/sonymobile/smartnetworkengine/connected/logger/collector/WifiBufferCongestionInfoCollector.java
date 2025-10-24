/*
 * Copyright 2019 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.connected.logger.collector;

import static java.lang.Math.max;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;

import com.sonymobile.smartnetworkengine.util.Log;
import com.sonymobile.smartnetworkengine.util.WifiStatsNodeFinder;
import com.sonymobile.smartnetworkengine.util.WifiStatsNodeFinder.StatsType;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Optional;

/**
 * Wi-Fi buffer congestion info collector
 * (NumOfTxTries, NumOfTxNoAck, NumOfUsedDescriptors, IntegralUsedDescriptor)
 */
public class WifiBufferCongestionInfoCollector {

    private static final String TAG = WifiBufferCongestionInfoCollector.class.getSimpleName();

    /** A path to the sysfs node created by Qualcomm WLAN driver */
    @VisibleForTesting
    @Nullable
    /* private final */ Path mSourceNodePath;

    /** Wi-Fi buffer congestion info */
    private final BufferCongestionInfo mBufferCongestionInfo = new BufferCongestionInfo();

    public WifiBufferCongestionInfoCollector(@NonNull String interfaceName) {
        // Search "buf_info" node on sysfs
        mSourceNodePath = WifiStatsNodeFinder.findSourceNodePath(StatsType.BUF_INFO, interfaceName);
        if (mSourceNodePath == null) {
            Log.w(TAG, "Wi-Fi congestion collection is not supported on this platform");
        }
    }

    /**
     * Return Wi-Fi buffer congestion info.
     */
    @NonNull
    public BufferCongestionInfo getBufferCongestionInfo() {
        return new BufferCongestionInfo(mBufferCongestionInfo);
    }

    /**
     * Fetch latest stats to update congestion information.
     */
    public void refresh() {
        if (mSourceNodePath == null) {
            return; // Do nothing since not supported
        }

        // Fetch congestion info through sysfs.
        BufferCongestionInfoParser stats;
        try {
            stats = new BufferCongestionInfoParser(readCongestionInfoFile());
        } catch (IOException | IllegalArgumentException e) {
            Log.w(TAG, "Unable to fetch Wi-Fi congestion. Refresh is aborted: " + e.getMessage());
            resetStatistics();
            return;
        }

        mBufferCongestionInfo.update(stats);

        // For debugging
        Log.v(TAG, mBufferCongestionInfo.toString());
    }

    private void resetStatistics() {
        mBufferCongestionInfo.reset();
    }

    @VisibleForTesting
    List<String> readCongestionInfoFile() throws IOException {
        return Files.readAllLines(mSourceNodePath, StandardCharsets.UTF_8);
    }

    /**
     * A class to hold Wi-Fi buffer congestion information
     */
    public static class BufferCongestionInfo {

        private long mDeltaTxTries = -1;

        private BufferCongestionInfoParser mPrevStats;

        BufferCongestionInfo() {
        }

        // Copy constructor
        BufferCongestionInfo(BufferCongestionInfo source) {
            mDeltaTxTries = source.mDeltaTxTries;
            mPrevStats = source.mPrevStats;
        }

        public long getDeltaTxTries() {
            return mDeltaTxTries;
        }

        public int getIntegralUsedDescriptor() {
            if (mPrevStats != null) {
                return mPrevStats.getIntegralUsedDescriptor();
            }
            return -1;
        }

        void reset() {
            mDeltaTxTries = -1;
            mPrevStats = null;
        }

        void update(@NonNull BufferCongestionInfoParser stats) {
            if (mPrevStats == null) {
                mDeltaTxTries = 0;
            } else {
                mDeltaTxTries = max(stats.getNumOfTxTries() - mPrevStats.getNumOfTxTries(), 0);
            }
            mPrevStats = stats;
        }

        @Override
        public String toString() {
            return "BufferCongestionInfo(DeltaTxTries=" + getDeltaTxTries()
                    + ", IntegralUsedDescriptor=" + getIntegralUsedDescriptor() + ")";

        }
    }

    /**
     * A sysfs (somc_ebc_info) parser
     */
    @VisibleForTesting
    /* private */ static class BufferCongestionInfoParser {

        /** Total number of TX tries to WLAN chip (cumulative value). */
        private long mNumOfTxTries;

        /** Number of in-use descriptors for sending to WLAN chip (time-integral value). */
        private int mIntegralUsedDescriptor;

        BufferCongestionInfoParser(@NonNull List<String> congestion) {
            if (!parse(congestion)) {
                throw new IllegalArgumentException("parse failure");
            }
        }

        long getNumOfTxTries() {
            return mNumOfTxTries;
        }

        int getIntegralUsedDescriptor() {
            return mIntegralUsedDescriptor;
        }

        @SuppressWarnings("OptionalGetWithoutIsPresent")
        private boolean parse(List<String> congestion) {
            try {
                if (congestion.isEmpty()) {
                    Log.w(TAG, "Failed to parse buffer congestion info due to empty input");
                    return false;
                }

                String line = congestion.get(0);
                Log.v(TAG, "Parsing Buffer Congestion info from [" + line + "]");

                mNumOfTxTries = parseElementAsLong(line, "num_tx_tries").get();
                mIntegralUsedDescriptor = parseElementAsInt(line, "integral_used_desc").get();
            } catch (NoSuchElementException e) {
                Log.w(TAG, "Failed to parse buffer congestion info : " + e.getMessage());
                return false;
            }
            return true;
        }

        private Optional<String> parseElementAsString(String line, String key) {
            String keyPrefix = key + " = ";
            Optional<String> elementOpt = Arrays.stream(line.split(","))
                    .map(String::trim)
                    .filter(e -> e.startsWith(keyPrefix))
                    .findFirst();
            return elementOpt.map(e -> e.substring(keyPrefix.length()).trim());
        }

        private Optional<Integer> parseElementAsInt(String line, String key) {
            try {
                return parseElementAsString(line, key).map(Integer::parseInt);
            } catch (NumberFormatException e) {
                return Optional.empty();
            }
        }

        private Optional<Long> parseElementAsLong(String line, String key) {
            try {
                return parseElementAsString(line, key).map(Long::parseLong);
            } catch (NumberFormatException e) {
                return Optional.empty();
            }
        }
    }

}
