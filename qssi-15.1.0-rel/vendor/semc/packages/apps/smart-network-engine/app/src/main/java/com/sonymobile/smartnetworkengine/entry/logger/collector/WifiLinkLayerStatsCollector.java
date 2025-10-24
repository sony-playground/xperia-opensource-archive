/*
 * Copyright 2020, 2023 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.entry.logger.collector;

import static com.sonymobile.smartnetworkengine.connected.logger.collector.WifiLinkLayerStatsCollector.LOCK_READ_LINK_LAYER_STATS;

import androidx.annotation.NonNull;
import androidx.annotation.VisibleForTesting;

import com.sonymobile.smartnetworkengine.util.Log;
import com.sonymobile.smartnetworkengine.util.WifiStatsNodeFinder;
import com.sonymobile.smartnetworkengine.util.WifiStatsNodeFinder.StatsType;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.NoSuchElementException;
import java.util.Optional;

/**
 * Wifi LinkLayerStats collector (CCA busy per frequency)
 */
public class WifiLinkLayerStatsCollector {

    private static final String TAG = WifiLinkLayerStatsCollector.class.getSimpleName();

    // TODO: Get rid of this table to not hard-code supported frequencies.
    @VisibleForTesting
    /* private */ static final List<Integer> FREQUENCIES = Arrays.asList(
            2412, 2417, 2422, 2427, 2432, 2437, 2442, 2447, 2452, 2457, 2462, 2467, 2472, 2484,
            5180, 5200, 5220, 5240, 5260, 5280, 5300, 5320,
            5500, 5520, 5540, 5560, 5580, 5600, 5620, 5640, 5660, 5680, 5700, 5720, 5745, 5765,
            5785, 5805, 5825, 5845, 5865
    );

    /** Radio time (Radio On/CCA Busy/Transmitting/Receiving) information */
    private final RadioTimeInfo mRadioTimeInfo = new RadioTimeInfo();

    /**
     * Return radio time information.
     */
    @NonNull
    public RadioTimeInfo getRadioTimeInfo() {
        return new RadioTimeInfo(mRadioTimeInfo);
    }

    /**
     * Fetch latest stats to update radio time and contention related information.
     */
    public void refresh(@NonNull String interfaceName) {
        // Search "ll_stats" node on sysfs
        Path sourceNodePath = WifiStatsNodeFinder.findSourceNodePath(StatsType.LL_STATS,
                interfaceName);
        if (sourceNodePath == null) {
            Log.w(TAG, "LinkLayerStats collection is not supported on this platform");
            return; // Do nothing since not supported
        }

        // Fetch link layer stats through sysfs
        LinkLayerStatsParser stats;
        try {
            stats = new LinkLayerStatsParser(readLinkLayerStatsFile(sourceNodePath));
        } catch (IOException | IllegalArgumentException e) {
            Log.w(TAG, "Unable to fetch link layer stats. Refresh is aborted: " + e.getMessage());
            resetStatistics();
            return;
        }

        mRadioTimeInfo.update(stats);

        // For debugging
        Log.v(TAG, mRadioTimeInfo.toString());
    }

    private void resetStatistics() {
        mRadioTimeInfo.reset();
    }

    @VisibleForTesting
    List<String> readLinkLayerStatsFile(Path sourceNodePath) throws IOException {
        synchronized (LOCK_READ_LINK_LAYER_STATS) {
            return Files.readAllLines(sourceNodePath, StandardCharsets.UTF_8);
        }
    }

    /**
     * A class to hold radio time information
     */
    public static class RadioTimeInfo {

        @NonNull
        private Map<Integer, Long> mOnTimes = Collections.emptyMap();

        @NonNull
        private Map<Integer, Long> mCcaBusyTimes = Collections.emptyMap();

        RadioTimeInfo() {
        }

        // Copy constructor
        RadioTimeInfo(RadioTimeInfo source) {
            mOnTimes = source.mOnTimes;
            mCcaBusyTimes = source.mCcaBusyTimes;
        }

        RadioTimeInfo(Map<Integer, Long> onTimes, Map<Integer, Long> ccaBusyTimes) {
            mOnTimes = onTimes;
            mCcaBusyTimes = ccaBusyTimes;
        }

        public Map<Integer, Long> getOnTimes() {
            return Collections.unmodifiableMap(mOnTimes);
        }

        public Map<Integer, Long> getCcaBusyTimes() {
            return Collections.unmodifiableMap(mCcaBusyTimes);
        }

        void reset() {
            mOnTimes = Collections.emptyMap();
            mCcaBusyTimes = Collections.emptyMap();
        }

        void update(@NonNull LinkLayerStatsParser stats) {
            mCcaBusyTimes = stats.getCcaBusyTimePerFreq();
            mOnTimes = stats.getOnTimePerFreq();
        }

        @Override
        public String toString() {
            return "RadioTimeInfo(OnTimes=" + mOnTimes + ", CcaBusyTimes=" + mCcaBusyTimes + ")";
        }

        public static Builder builder() {
            return new Builder();
        }

        public static class Builder {
            @NonNull
            private Map<Integer, Long> mOnTimes = Collections.emptyMap();

            @NonNull
            private Map<Integer, Long> mCcaBusyTimes = Collections.emptyMap();

            public Builder onTimes(HashMap<Integer, Long> onTimes) {
                mOnTimes = onTimes;
                return this;
            }

            public Builder ccaBusyTimes(HashMap<Integer, Long> ccaBusyTimes) {
                mCcaBusyTimes = ccaBusyTimes;
                return this;
            }

            public RadioTimeInfo build() {
                return new RadioTimeInfo(mOnTimes, mCcaBusyTimes);
            }
        }
    }

    /**
     * A sysfs (ll_stats) parser
     */
    private static class LinkLayerStatsParser {

        private final Map<Integer, Long> mOnTimePerFreq = new HashMap<>();

        private final Map<Integer, Long> mCcaBusyTimePerFreq = new HashMap<>();

        LinkLayerStatsParser(@NonNull List<String> llStats) {
            if (!parse(llStats)) {
                throw new IllegalArgumentException("parse failure");
            }
        }

        @NonNull
        Map<Integer, Long> getOnTimePerFreq() {
            return mOnTimePerFreq;
        }

        @NonNull
        Map<Integer, Long> getCcaBusyTimePerFreq() {
            return mCcaBusyTimePerFreq;
        }

        @SuppressWarnings("OptionalGetWithoutIsPresent")
        private boolean parse(List<String> llStats) {
            try {
                // Parse CCA information in "LL_STATS_RADIO" section
                //  (ex. "Chan width: 0, center_freq: 2437, ... , on_time: 42933,
                //        cca_busy_time: 9460")
                for (Integer frequency : FREQUENCIES) { // TODO: Reduce lots of string searches
                    String freqFilterStr = String.format(Locale.US, "freq: %d,", frequency);
                    Optional<String> ccaStrOpt = llStats.stream()
                            .filter(l -> l.startsWith("freq:"))
                            .filter(l -> l.contains(freqFilterStr))
                            .findFirst(); // Read first line to match with the frequency.
                    if (ccaStrOpt.isPresent()) {
                        String line = ccaStrOpt.get();
                        mOnTimePerFreq.put(frequency, parseElementAsLong(line, "on").get());
                        mCcaBusyTimePerFreq.put(frequency,
                                parseElementAsLong(line, "ccabusy").get());
                    } else {
                        mOnTimePerFreq.put(frequency, 0L);
                        mCcaBusyTimePerFreq.put(frequency, 0L);
                    }
                }
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
