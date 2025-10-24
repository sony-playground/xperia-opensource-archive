/*
 * Copyright 2019, 2020, 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.connected.logger.collector;

import static java.lang.Math.max;

import android.content.Context;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;

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
import java.util.Locale;
import java.util.NoSuchElementException;
import java.util.Optional;

/**
 * Wifi LinkLayerStats collector (CCA busy and contention time)
 */
public class WifiLinkLayerStatsCollector {

    private static final String TAG = WifiLinkLayerStatsCollector.class.getSimpleName();

    /**
     * A static object for exclusive control to read LinkLayerStats file. This is also referenced in
     * collector of the entry feature.
     */
    public static final Object LOCK_READ_LINK_LAYER_STATS = new Object();

    private final WifiManager mWifiManager;

    /** A path to the sysfs node created by Qualcomm WLAN driver */
    @VisibleForTesting
    @Nullable
    /* private final */ Path mSourceNodePath;

    /** Radio time (Radio On/CCA Busy/Transmitting/Receiving) information */
    private final RadioTimeInfo mRadioTimeInfo = new RadioTimeInfo();

    /** Contention related information */
    private final ContentionInfo mContentionInfo = new ContentionInfo();

    public WifiLinkLayerStatsCollector(@NonNull Context context, @NonNull String interfaceName) {
        mWifiManager = (WifiManager) context.getSystemService(Context.WIFI_SERVICE);
        // Search "ll_stats" node on sysfs
        mSourceNodePath = WifiStatsNodeFinder.findSourceNodePath(StatsType.LL_STATS, interfaceName);
        if (mSourceNodePath == null) {
            Log.w(TAG, "LinkLayerStats collection is not supported on this platform");
        }
    }

    /**
     * Return radio time information.
     */
    @NonNull
    public RadioTimeInfo getRadioTimeInfo() {
        return new RadioTimeInfo(mRadioTimeInfo);
    }

    /**
     * Return contention related information.
     */
    @NonNull
    public ContentionInfo getContentionInfo() {
        return new ContentionInfo(mContentionInfo);
    }

    /**
     * Fetch latest stats to update radio time and contention related information.
     */
    public void refresh() {
        if (mSourceNodePath == null) {
            return; // Do nothing since not supported
        }

        // Obtain current frequency
        WifiInfo wifiInfo = mWifiManager.getConnectionInfo();
        if (wifiInfo == null || wifiInfo.getFrequency() == -1) { // Almost never happen
            Log.w(TAG, "Unable to obtain frequency. Refresh is aborted.");
            resetStatistics();
            return;
        }

        // Fetch link layer stats through sysfs
        LinkLayerStatsParser stats;
        try {
            stats = new LinkLayerStatsParser(readLinkLayerStatsFile(), wifiInfo.getFrequency());
        } catch (IOException | IllegalArgumentException e) {
            Log.w(TAG, "Unable to fetch link layer stats. Refresh is aborted: " + e.getMessage());
            resetStatistics();
            return;
        }

        mRadioTimeInfo.update(stats);
        mContentionInfo.update(stats);

        // For debugging
        Log.v(TAG, mRadioTimeInfo.toString());
        Log.v(TAG, mContentionInfo.toString());
    }

    private void resetStatistics() {
        mRadioTimeInfo.reset();
        mContentionInfo.reset();
    }

    @VisibleForTesting
    List<String> readLinkLayerStatsFile() throws IOException {
        synchronized (LOCK_READ_LINK_LAYER_STATS) {
            return Files.readAllLines(mSourceNodePath, StandardCharsets.UTF_8);
        }
    }

    /**
     * A class to hold radio time information
     */
    public static class RadioTimeInfo {

        public static final int INVALID_VALUE = -1;

        /** cf. {@link LinkLayerStatsParser#getTxTime()} */
        private long mDeltaTxTime = INVALID_VALUE;

        /** cf. {@link LinkLayerStatsParser#getRxTime()} */
        private long mDeltaRxTime = INVALID_VALUE;

        /** cf. {@link LinkLayerStatsParser#getOnTimeOnRadio0CurrentFreq()} */
        private long mDeltaOnTimeOnCurrentFreq = INVALID_VALUE;

        /** cf. {@link LinkLayerStatsParser#getCcaBusyTimeOnRadio0CurrentFreq()} */
        private long mDeltaCcaBusyTimeOnCurrentFreq = INVALID_VALUE;

        /** cf. {@link LinkLayerStatsParser#getTxTime()} */
        private long mRawTxTime = INVALID_VALUE;

        /** cf. {@link LinkLayerStatsParser#getRxTime()} */
        private long mRawRxTime = INVALID_VALUE;

        /** cf. {@link LinkLayerStatsParser#getOnTimeOnRadio0CurrentFreq()} */
        private long mRawOnTimeOnCurrentFreq = INVALID_VALUE;

        /** cf. {@link LinkLayerStatsParser#getCcaBusyTimeOnRadio0CurrentFreq()} */
        private long mRawCcaBusyTimeOnCurrentFreq = INVALID_VALUE;

        private LinkLayerStatsParser mPrevStats;

        RadioTimeInfo() {
        }

        // Copy constructor
        RadioTimeInfo(RadioTimeInfo source) {
            mDeltaTxTime = source.mDeltaTxTime;
            mDeltaRxTime = source.mDeltaRxTime;
            mDeltaOnTimeOnCurrentFreq = source.mDeltaOnTimeOnCurrentFreq;
            mDeltaCcaBusyTimeOnCurrentFreq = source.mDeltaCcaBusyTimeOnCurrentFreq;
            mRawTxTime = source.mRawTxTime;
            mRawRxTime = source.mRawRxTime;
            mRawOnTimeOnCurrentFreq = source.mRawOnTimeOnCurrentFreq;
            mRawCcaBusyTimeOnCurrentFreq = source.mRawCcaBusyTimeOnCurrentFreq;
            mPrevStats = source.mPrevStats;
        }

        public long getDeltaTxTime() {
            return mDeltaTxTime;
        }

        public long getDeltaRxTime() {
            return mDeltaRxTime;
        }

        public long getDeltaOnTimeOnCurrentFreq() {
            return mDeltaOnTimeOnCurrentFreq;
        }

        public long getDeltaCcaBusyTimeOnCurrentFreq() {
            return mDeltaCcaBusyTimeOnCurrentFreq;
        }

        public long getRawTxTime() {
            return mRawTxTime;
        }

        public long getRawRxTime() {
            return mRawRxTime;
        }

        public long getRawOnTimeOnCurrentFreq() {
            return mRawOnTimeOnCurrentFreq;
        }

        public long getRawCcaBusyTimeOnCurrentFreq() {
            return mRawCcaBusyTimeOnCurrentFreq;
        }

        void reset() {
            mDeltaTxTime = INVALID_VALUE;
            mDeltaRxTime = INVALID_VALUE;
            mDeltaOnTimeOnCurrentFreq = INVALID_VALUE;
            mDeltaCcaBusyTimeOnCurrentFreq = INVALID_VALUE;
            mRawTxTime = INVALID_VALUE;
            mRawRxTime = INVALID_VALUE;
            mRawOnTimeOnCurrentFreq = INVALID_VALUE;
            mRawCcaBusyTimeOnCurrentFreq = INVALID_VALUE;
            mPrevStats = null;
        }

        void update(@NonNull LinkLayerStatsParser stats) {
            if (mPrevStats == null) {
                mDeltaTxTime = 0;
                mDeltaRxTime = 0;
                mDeltaOnTimeOnCurrentFreq = 0;
                mDeltaCcaBusyTimeOnCurrentFreq = 0;
            } else {
                mDeltaTxTime = max(stats.getTxTime() - mPrevStats.getTxTime(), 0);
                mDeltaRxTime = max(stats.getRxTime() - mPrevStats.getRxTime(), 0);
                if (mPrevStats.getFrequency() != stats.getFrequency()) {
                    mDeltaOnTimeOnCurrentFreq = 0;
                    mDeltaCcaBusyTimeOnCurrentFreq = 0;
                } else {
                    mDeltaOnTimeOnCurrentFreq = max(stats.getOnTimeOnRadio0CurrentFreq()
                            - mPrevStats.getOnTimeOnRadio0CurrentFreq(), 0);
                    mDeltaCcaBusyTimeOnCurrentFreq = max(stats.getCcaBusyTimeOnRadio0CurrentFreq()
                            - mPrevStats.getCcaBusyTimeOnRadio0CurrentFreq(), 0);
                }
            }
            mRawTxTime = stats.getTxTime();
            mRawRxTime = stats.getRxTime();
            mRawOnTimeOnCurrentFreq = stats.getOnTimeOnRadio0CurrentFreq();
            mRawCcaBusyTimeOnCurrentFreq = stats.getCcaBusyTimeOnRadio0CurrentFreq();
            mPrevStats = stats;
        }

        @Override
        public String toString() {
            return "RadioTimeInfo(DeltaTxTime=" + getDeltaTxTime() + ", DeltaRxTime="
                    + getDeltaRxTime() + ", DeltaOnTimeOnCurrentFreq="
                    + getDeltaOnTimeOnCurrentFreq() + ", DeltaCcaBusyTimeOnCurrentFreq="
                    + getDeltaCcaBusyTimeOnCurrentFreq() + ", RawTxTime="
                    + getRawTxTime() + ", RawRxTime=" + getRawRxTime() + ", RawOnTimeOnCurrentFreq="
                    + getRawOnTimeOnCurrentFreq() + ", RawCcaBusyTimeOnCurrentFreq="
                    + getRawCcaBusyTimeOnCurrentFreq() + ", CurrentFreq=" + (mPrevStats != null
                    ? mPrevStats.getFrequency() : "n/a") + ")";
        }
    }

    /**
     * A class to hold contention related time information
     */
    public static class ContentionInfo {

        public static final int INVALID_VALUE = -1;

        /** cf. {@link LinkLayerStatsParser#getAcBeNumOfContentionSamples()} */
        private long mDeltaNumOfSamples = INVALID_VALUE;

        /** cf. {@link LinkLayerStatsParser#getAcBeNumOfContentionSamples()} */
        private long mRawNumOfSamples = INVALID_VALUE;

        private LinkLayerStatsParser mPrevStats;

        ContentionInfo() {
        }

        // Copy constructor
        ContentionInfo(ContentionInfo source) {
            mDeltaNumOfSamples = source.mDeltaNumOfSamples;
            mRawNumOfSamples = source.mRawNumOfSamples;
            mPrevStats = source.mPrevStats;
        }

        public long getAverageTime() {
            if (mPrevStats != null) {
                return mPrevStats.getAcBeContentionAverageTime();
            }
            return INVALID_VALUE;
        }

        public long getDeltaNumOfSamples() {
            return mDeltaNumOfSamples;
        }

        public long getRawNumOfSamples() {
            return mRawNumOfSamples;
        }

        void reset() {
            mDeltaNumOfSamples = INVALID_VALUE;
            mRawNumOfSamples = INVALID_VALUE;
            mPrevStats = null;
        }

        void update(@NonNull LinkLayerStatsParser stats) {
            if (mPrevStats == null) {
                mDeltaNumOfSamples = 0;
            } else {
                mDeltaNumOfSamples = max(stats.getAcBeNumOfContentionSamples()
                        - mPrevStats.getAcBeNumOfContentionSamples(), 0);
            }
            mRawNumOfSamples = stats.getAcBeNumOfContentionSamples();
            mPrevStats = stats;
        }

        @Override
        public String toString() {
            return "ContentionInfo(AverageTime=" + getAverageTime() + ", DeltaNumOfSamples="
                    + getDeltaNumOfSamples() + ", mRawNumOfSamples=" + mRawNumOfSamples + ")";
        }
    }

    /**
     * A sysfs (ll_stats) parser
     */
    @VisibleForTesting
    /* private */ static class LinkLayerStatsParser {

        /** AC_BE: Contention time (average) */
        private long mAcBeContentionAverageTime;

        /** AC_BE: Total number of the samples */
        private long mAcBeNumOfContentionSamples;

        /** Radio0: Tx time (cumulative) */
        private long mTxTimeOnRadio0;

        /** Radio0: Rx time (cumulative) */
        private long mRxTimeOnRadio0;

        /** Radio1: Tx time (cumulative) */
        private long mTxTimeOnRadio1;

        /** Radio1: Rx time (cumulative) */
        private long mRxTimeOnRadio1;

        /** Radio0: On time on current frequency (cumulative) */
        private long mOnTimeOnRadio0CurrentFreq;

        /** Radio0: CCA busy time on current frequency (cumulative) */
        private long mCcaBusyTimeOnRadio0CurrentFreq;

        /** Current frequency */
        private int mFrequency;

        LinkLayerStatsParser(@NonNull List<String> llStats, int frequency) {
            if (!parse(llStats, frequency)) {
                throw new IllegalArgumentException("parse failure");
            }
            mFrequency = frequency;
        }

        long getAcBeContentionAverageTime() {
            return mAcBeContentionAverageTime;
        }

        long getAcBeNumOfContentionSamples() {
            return mAcBeNumOfContentionSamples;
        }

        long getTxTime() {
            return mTxTimeOnRadio0 + mTxTimeOnRadio1;
        }

        long getRxTime() {
            return mRxTimeOnRadio0 + mRxTimeOnRadio1;
        }

        long getOnTimeOnRadio0CurrentFreq() {
            return mOnTimeOnRadio0CurrentFreq;
        }

        long getCcaBusyTimeOnRadio0CurrentFreq() {
            return mCcaBusyTimeOnRadio0CurrentFreq;
        }

        int getFrequency() {
            return mFrequency;
        }

        @SuppressWarnings("OptionalGetWithoutIsPresent")
        private boolean parse(List<String> llStats, int frequency) {
            try {
                // Parse contention information in "LL_STATS_IFACE" section
                //  (ex. "ac_type: 2, ... , contention_time: min-16 max-18597 avg-734,
                //        contention num samples: 1471, ...")
                Optional<String> contentionStrOpt = llStats.stream()
                        .filter(l -> l.startsWith("ac_type: 2")) // AC_BE only
                        .findFirst();
                String line = contentionStrOpt.get();
                Log.v(TAG, "Parsing contention info from [" + line + "]");

                // (contention_time)
                String strValue = parseElementAsString(line, "contention_time").get();
                int index = strValue.indexOf("avg-");
                if (index == -1) {
                    Log.w(TAG, "Failed to parse link layer stats(contention_time)");
                    return false;
                }
                mAcBeContentionAverageTime = Long.parseLong(strValue.substring(index + 4));

                // (contention num samples)
                mAcBeNumOfContentionSamples = parseElementAsLong(line,
                        "contention num samples").get();

                // Parse CCA information in "LL_STATS_RADIO" section
                //  (ex. "Radio: 0 on_time: 73160, tx_time: 1355, rx_time: 2521, ...")
                //  (ex. "Chan width: 0, center_freq: 2437, ... , on_time: 42933,
                //        cca_busy_time: 9460")
                Optional<String> radioStrOpt = llStats.stream()
                        .filter(l -> l.startsWith("Radio: 0")) // Radio-0 only
                        .findFirst();
                line = radioStrOpt.get();
                Log.v(TAG, "Parsing CCA info(1/3) from [" + line + "]");

                // (tx_time)
                mTxTimeOnRadio0 = parseElementAsLong(line, "tx").get();

                // (rx_time)
                mRxTimeOnRadio0 = parseElementAsLong(line, "rx").get();

                // If platform supports also Radio:1, sum TxTime/RxTime for Radio:1.
                // This process is required for absorb platform dependency.
                llStats.stream()
                        .filter(l -> l.startsWith("Radio: 1")) // Radio-1 only
                        .findFirst()
                        .ifPresent(l -> {
                            Log.v(TAG, "Parsing CCA info(2/3) from [" + l + "]");
                            mTxTimeOnRadio1 = parseElementAsLong(l, "tx").get();
                            mRxTimeOnRadio1 = parseElementAsLong(l, "rx").get();
                        });

                // If there're multiple output for same freq, the first is correct.
                String freqFilterStr = String.format(Locale.US, "freq: %d,", frequency);
                Optional<String> ccaStrOpt = llStats.stream()
                        .filter(l -> l.startsWith("freq:"))
                        .filter(l -> l.contains(freqFilterStr))
                        .findFirst();
                line = ccaStrOpt.get();
                Log.v(TAG, "Parsing CCA info(3/3) from [" + line + "]");

                // (on_time)
                mOnTimeOnRadio0CurrentFreq = parseElementAsLong(line, "on").get();

                // (cca_busy_time)
                mCcaBusyTimeOnRadio0CurrentFreq = parseElementAsLong(line, "ccabusy").get();
            } catch (NoSuchElementException | NumberFormatException e) {
                Log.w(TAG, "Failed to parse link layer stats: " + e.getMessage());
                return false;
            }
            return true;
        }

        private Optional<String> parseElementAsString(String line, String key) {
            String keyPrefix = key + ":";
            Optional<String> elementOpt = Arrays.stream(line.split(","))
                    .map(String::trim)
                    .filter(e -> e.startsWith(keyPrefix))
                    .findFirst();
            return elementOpt.map(e -> e.substring(keyPrefix.length()).trim());
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
