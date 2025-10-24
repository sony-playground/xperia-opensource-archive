/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.connected;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;

import com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData;
import com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData.SneRuntimeStats;
import com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData.SneWifiEvent;
import com.sonymobile.smartnetworkengine.connected.logger.LoggerService.SessionInfo;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

/**
 * This class checks parameters and creates the features for the user intention prediction.
 */
public class Preprocessor {

    public static final int MAX_NUM_OF_STATS_SAMPLES = 30;

    private static final List<Integer> mKnownFrequencyList = Collections.unmodifiableList(
            Arrays.asList(2412, 2417, 2422, 2427, 2432, 2437, 2442, 2447, 2452, 2457, 2462,
                    2467, 2472, 5180, 5200, 5220, 5240, 5260, 5280, 5300, 5320, 5500, 5520,
                    5540, 5560, 5580, 5600, 5620, 5640, 5660, 5680, 5700, 5720, 5745, 5765,
                    5785, 5805, 5825));

    /**
     * Create parameters to predict user intention.
     *
     * @return parameters to predict user intention. Return {@code null} if contains not valid
     * parameters for predict.
     */
    @Nullable
    public static List<List<Float>> extractFeatures(@NonNull List<SneRuntimeStats> statsList,
            @NonNull SessionInfo sessionInfo, long connectedTimeMs, long previousDisconnectedTimeMs,
            @Nullable SneWifiEvent wifiEvent) {
        if (!checkPredictionCondition(statsList, sessionInfo, connectedTimeMs) ||
                !checkPredictionParameters(statsList)) {
            return null;
        }

        List<List<Float>> parameters = new ArrayList<>(statsList.size());
        for (SneRuntimeStats stats : statsList) {
            WifiPredictionData.SneInferenceResult inferenceResults = stats.getInferenceResult();
            WifiPredictionData.SneWifiInfo wifiInfo = stats.getWifiInfo();
            WifiPredictionData.SneWifiTrafficStats trafficStats = stats.getWifiTrafficStats();
            WifiPredictionData.SneSensorData sensorData = stats.getSensorData();

            List<Float> features = new ArrayList<>();
            features.add(inferenceResults.getPrimary());
            features.add(inferenceResults.getSecondary());
            features.add((float) wifiInfo.getRssi());
            features.add((float) trafficStats.getIntegralUsedDescriptorInDriver());
            features.add((float) wifiInfo.getCcaBusyTime() / wifiInfo.getOnTime());
            features.add((float) wifiInfo.getLinkSpeed());
            features.add((float) wifiInfo.getContentionAverageTime());
            features.add((float) trafficStats.getRxPkt());
            features.add((float) trafficStats.getTxPkt());
            features.add(sensorData.getIsMoving() ? 1.0f : 0.0f);
            features.add(wifiInfo.getFrequency() > 4000 ? 1.0f : 0.0f); // 2.4GHz or 5GHz
            features.add((float) sessionInfo.getWifiSecurityType());
            features.add(turnWifiOffBefore(
                    connectedTimeMs, previousDisconnectedTimeMs, wifiEvent) ? 1.0f : 0.0f);
            parameters.add(features);
        }
        return parameters;
    }

    // "the last session, user turn off WiFi and the last session's end time is within 90 sec"
    private static boolean turnWifiOffBefore(long connectedTimeMs, long previousDisconnectedTimeMs,
            @Nullable SneWifiEvent wifiEvent) {
        if (wifiEvent != null) {
            // Bitset: IS_HOME|SCREEN_OFF|SNE_ON|ULTRA_STAMINA_ON|AIRPLANE_ON|TETHER_ON|WIFI_ON
            boolean wifiOn = (wifiEvent.getLoggedInfo().getLoggedSettingDetail() & 0x01) == 1;
            return !wifiOn && (connectedTimeMs - previousDisconnectedTimeMs) < 90 * 1000;
        }
        return false;
    }

    /**
     * Check whether it meets a scope of prediction
     *
     * @return {@code true} if meets conditions. Otherwise return {@code false}.
     */
    @VisibleForTesting
    static boolean checkPredictionCondition(List<SneRuntimeStats> statsList,
            SessionInfo sessionInfo, long connectedTimeMs) {
        long currentTimeMs = System.currentTimeMillis();
        return // Check wifi connection duration is less than 24h
                currentTimeMs - connectedTimeMs < 24 * 60 * 60 * 1000
                        // Check not home wifi
                        && !sessionInfo.isHomeNetwork()
                        // Check num of the samples is more than 1 (at least 3 sec)
                        && !statsList.isEmpty()
                        // Check default network is not already cellular (should never happen)
                        && statsList.stream().allMatch(e -> e.getWifiInfo().getScore() >= 50);
    }

    /**
     * Check there is no outlier in parameters
     *
     * @return {@code true} there are no outlier parameters. Otherwise return {@code false}.
     */
    @VisibleForTesting
    static boolean checkPredictionParameters(List<SneRuntimeStats> statsList) {
        for (SneRuntimeStats stats : statsList) {
            WifiPredictionData.SneInferenceResult inferenceResult = stats.getInferenceResult();
            WifiPredictionData.SneWifiInfo wifiInfo = stats.getWifiInfo();
            WifiPredictionData.SneWifiTrafficStats trafficStats = stats.getWifiTrafficStats();

            // for inference result primary
            if (inferenceResult.getPrimary() < 0 || 1 < inferenceResult.getPrimary()) {
                return false;
            }

            // for inference result secondary
            if (inferenceResult.getSecondary() < 0 || 1 < inferenceResult.getSecondary()) {
                return false;
            }

            // for rssi
            if (wifiInfo.getRssi() < -100 || 0 < wifiInfo.getRssi()) {
                return false;
            }

            // for integral used descriptor in driver
            if (trafficStats.getIntegralUsedDescriptorInDriver() < 0) {
                return false;
            }

            // for ccabt average
            if (wifiInfo.getOnTime() <= 0 || wifiInfo.getCcaBusyTime() < 0
                    || ((float) wifiInfo.getCcaBusyTime() / wifiInfo.getOnTime()) > 1) {
                return false;
            }

            // for link speed
            if (wifiInfo.getLinkSpeed() < 0) {
                return false;
            }

            // for band
            if (!mKnownFrequencyList.contains(wifiInfo.getFrequency())) {
                return false;
            }
        }
        return true;
    }
}
