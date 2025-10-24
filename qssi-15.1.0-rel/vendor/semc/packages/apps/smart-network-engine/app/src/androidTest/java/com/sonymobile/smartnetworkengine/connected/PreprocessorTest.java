/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.connected;

import static com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData.SneInferenceResult;
import static com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData.SneRuntimeStats;
import static com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData.SneSensorData;
import static com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData.SneWifiInfo;
import static com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData.SneWifiTrafficStats;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData;
import com.sonymobile.smartnetworkengine.connected.logger.LoggerService;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@RunWith(AndroidJUnit4.class)
public class PreprocessorTest {
    private List<SneRuntimeStats> mRuntimeStatsList = new ArrayList<>();
    private LoggerService.SessionInfo mSessionInfo;

    private final static long TIME_24_H_BEFORE = System.currentTimeMillis() - 24 * 60 * 60 * 1000;
    private final static long TIME_12_H_BEFORE = System.currentTimeMillis() - 12 * 60 * 60 * 1000;

    @Before
    public void setup() {
        // Add default data set
        mRuntimeStatsList.add(
                createRuntimeStats(0.1f, 0.2f, -80, 100, 300, 150, 200, 300, 10, 20, 60, true, 10,
                        true));
        mRuntimeStatsList.add(
                createRuntimeStats(0.1f, 0.2f, -80, 100, 300, 150, 200, 300, 10, 20, 60, true, 10,
                        true));
        mRuntimeStatsList.add(
                createRuntimeStats(0.1f, 0.2f, -80, 100, 300, 150, 200, 300, 10, 20, 60, true, 10,
                        true));
        mSessionInfo = new LoggerService.SessionInfo.Builder()
                .currentBssid("test").wifiSecurityType(1).homeNetwork(false).userSelected(false)
                .build();
    }

    @Test
    public void testCheckConditionLoggedDuration() {
        // The last disconnection happens 24 hours before, prediction is void.
        assertFalse(Preprocessor.checkPredictionCondition(mRuntimeStatsList, mSessionInfo,
                TIME_24_H_BEFORE));
        // The last disconnection happens within 24 hours, prediction is valid
        assertTrue(Preprocessor.checkPredictionCondition(mRuntimeStatsList, mSessionInfo,
                TIME_12_H_BEFORE));
    }

    @Test
    public void testCheckConditionHomeNetwork() {
        // Check prediction is void if network is home network
        mSessionInfo = new LoggerService.SessionInfo.Builder()
                .currentBssid("test").wifiSecurityType(1).homeNetwork(true).userSelected(false)
                .build();
        assertFalse(Preprocessor.checkPredictionCondition(mRuntimeStatsList, mSessionInfo,
                TIME_12_H_BEFORE));

        // Check prediction is valid if network is NOT home network
        mSessionInfo = new LoggerService.SessionInfo.Builder()
                .currentBssid("test").wifiSecurityType(1).homeNetwork(false).userSelected(false)
                .build();
        assertTrue(Preprocessor.checkPredictionCondition(mRuntimeStatsList, mSessionInfo,
                TIME_12_H_BEFORE));
    }

    @Test
    public void testCheckConditionStatsSize() {
        // If there is no runtime stats, prediction is void.
        mRuntimeStatsList.clear();
        assertFalse(Preprocessor.checkPredictionCondition(mRuntimeStatsList, mSessionInfo,
                TIME_12_H_BEFORE));
    }

    @Test
    public void testCheckConditionScore() {
        SneRuntimeStats score49stats = createRuntimeStats(0.1f, 0.2f, -80, 100, 300, 150, 200, 300,
                10, 20, 49, true, 10, true);

        mRuntimeStatsList.add(2, score49stats);

        // Wherever runtimeScore including score 49 exists, preprocess is void.
        assertFalse(Preprocessor.checkPredictionCondition(mRuntimeStatsList, mSessionInfo,
                TIME_12_H_BEFORE));
    }

    @Test
    public void testCheckParametersInferenceResult() {
        // normal case
        assertTrue(Preprocessor.checkPredictionParameters(mRuntimeStatsList));

        // inference Result is over 1
        SneRuntimeStats inferenceResultOver1stats = createRuntimeStats(2.0f, 0.2f, -80, 100, 300,
                150, 200, 300, 10, 20, 49, true, 10, true);
        mRuntimeStatsList.add(inferenceResultOver1stats);
        assertFalse(Preprocessor.checkPredictionParameters(mRuntimeStatsList));

        mRuntimeStatsList.remove(mRuntimeStatsList.size() - 1); // remove the last one

        // inference result is less than zero
        SneRuntimeStats inferenceResultNegative = createRuntimeStats(-1.0f, 0.2f, -80, 100, 300,
                150, 200, 300, 10, 20, 49, true, 10, true);
        mRuntimeStatsList.add(inferenceResultNegative);
        assertFalse(Preprocessor.checkPredictionParameters(mRuntimeStatsList));
    }

    @Test
    public void testCheckParametersRssi() {
        // rssi is positive value
        SneRuntimeStats rssiPositive = createRuntimeStats(0.1f, 0.2f, 10, 100, 300, 150, 200, 300,
                10, 20, 49, true, 10, true);
        mRuntimeStatsList.add(rssiPositive);
        assertFalse(Preprocessor.checkPredictionParameters(mRuntimeStatsList));
    }

    @Test
    public void testCheckParameterIntegralUsedDesc() {
        // integral used desc is negative
        SneRuntimeStats integralUsedDescNegative = createRuntimeStats(0.1f, 0.2f, -80, -100, 300,
                150, 200, 300, 10, 20, 60, true, 10, true);
        mRuntimeStatsList.add(integralUsedDescNegative);
        assertFalse(Preprocessor.checkPredictionParameters(mRuntimeStatsList));
    }

    @Test
    public void testCheckParameterCcaBtAvg() {
        // onTime is negative
        SneRuntimeStats onTimeNegative = createRuntimeStats(0.1f, 0.2f, -80, 100, -150, 300, 200,
                300, 10, 20, 60, true, 10, true);
        mRuntimeStatsList.add(onTimeNegative);
        assertFalse(Preprocessor.checkPredictionParameters(mRuntimeStatsList));
        mRuntimeStatsList.remove(mRuntimeStatsList.size() - 1);

        // onTime is zero
        SneRuntimeStats onTimeZero = createRuntimeStats(0.1f, 0.2f, -80, 100, 0, 300, 200,
                300, 10, 20, 60, true, 10, true);
        mRuntimeStatsList.add(onTimeZero);
        assertFalse(Preprocessor.checkPredictionParameters(mRuntimeStatsList));
        mRuntimeStatsList.remove(mRuntimeStatsList.size() - 1);

        // ccaBt ratio is over 1
        SneRuntimeStats ccaBtOver = createRuntimeStats(0.1f, 0.2f, -80, 100, 300, 450, 200, 300, 10,
                20, 60, true, 10, true);
        mRuntimeStatsList.add(ccaBtOver);
        assertFalse(Preprocessor.checkPredictionParameters(mRuntimeStatsList));
    }

    @Test
    public void testCheckParameterLinkSpeed() {
        SneRuntimeStats linkSpeedNegative = createRuntimeStats(0.1f, 0.2f, -80, 100, 300, 150, -200,
                300, 10, 20, 60, true, 10, true);
        mRuntimeStatsList.add(linkSpeedNegative);
        // linkspeed is negative
        assertFalse(Preprocessor.checkPredictionParameters(mRuntimeStatsList));
    }

    @Test
    public void testExtractFeaturesByUsingTestData() {
        mRuntimeStatsList.clear(); // Clear default data

        // Add real data
        mRuntimeStatsList.add(
                createRuntimeStats(0.0557999983f, 9.99999975e-05f, -79, 440, 6970, 189, 26, 59, 0,
                        0, 60, false, 0, true));
        mRuntimeStatsList.add(
                createRuntimeStats(0.0174000002f, 0.00219999999f, -81, 472, 1112, 16, 26, 35, 2, 5,
                        60, false, 0, true));
        mRuntimeStatsList.add(
                createRuntimeStats(0.0278999992f, 0.101800002f, -81, 356, 1074, 34, 19, 652, 74, 85,
                        60, false, 0, true));
        mRuntimeStatsList.add(
                createRuntimeStats(0.195999995f, 0.186499998f, -82, 2644, 2233, 364, 19, 3376, 391,
                        374, 60, false, 0, true));
        mRuntimeStatsList.add(
                createRuntimeStats(0.243300006f, 0.3917f, -85, 3468, 2840, 580, 6, 392, 227, 199,
                        60, false, 0, true));
        mRuntimeStatsList.add(
                createRuntimeStats(0.102899998f, 0.67900002f, -81, 960, 2817, 548, 26, 566, 470,
                        268, 60, false, 0, true));
        mRuntimeStatsList.add(
                createRuntimeStats(0.0844999999f, 0.978799999f, -81, 1468, 2823, 723, 26, 1323, 672,
                        348, 60, false, 0, true));

        WifiPredictionData.SneWifiEvent wifiEvent = WifiPredictionData.SneWifiEvent.newBuilder()
                .setLoggedInfo(WifiPredictionData.SneLoggedInfo.newBuilder()
                        .setLoggedSettingDetail(0) // !wifiOn
                        .build())
                .build();
        List<List<Float>> features = Preprocessor.extractFeatures(mRuntimeStatsList, mSessionInfo,
                System.currentTimeMillis(), System.currentTimeMillis() - 10 * 1000, wifiEvent);

        List<List<Float>> expectedResults = Arrays.asList(
                Arrays.asList(0.0557999983f, 0.017400000f, 0.0278999991f, 0.1959999948f,
                        0.2433000057f, 0.1028999984f, 0.0844999998f),
                Arrays.asList(9.99999975e-05f, 0.0022f, 0.1018000022f, 0.1864999980f, 0.3916999996f,
                        0.6790000200f, 0.9787999987f),
                Arrays.asList(-79.0f, -81.0f, -81.0f, -82.0f, -85.0f, -81.0f, -81.0f),
                Arrays.asList(440.0f, 472.0f, 356.0f, 2644.0f, 3468.0f, 960.0f, 1468.0f),
                Arrays.asList(0.0271162123f, 0.0143884892f, 0.0316573556f, 0.1630094043f,
                        0.2042253521f, 0.1945331913f, 0.2561105207f),
                Arrays.asList(26.0f, 26.0f, 19.0f, 19.0f, 6.0f, 26.0f, 26.0f),
                Arrays.asList(59.0f, 35.0f, 652.0f, 3376.0f, 392.0f, 566.0f, 1323.0f),
                Arrays.asList(0.0f, 2.0f, 74.0f, 391.0f, 227.0f, 470.0f, 672.0f),
                Arrays.asList(0.0f, 5.0f, 85.0f, 374.0f, 199.0f, 268.0f, 348.0f),
                Arrays.asList(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
                Arrays.asList(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                Arrays.asList(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
                Arrays.asList(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f)
        );

        List<List<Float>> invertedResults = new ArrayList<>();
        // invert row and column
        for (int i = 0; i < expectedResults.get(0).size(); i++) {
            List<Float> oneLine = new ArrayList<>();
            for (int j = 0; j < expectedResults.get(i).size(); j++) {
                oneLine.add(expectedResults.get(j).get(i));
            }
            invertedResults.add(oneLine);
        }

        // Check values of features equal to expected results.
        for (int i = 0; i < invertedResults.size(); i++) {
            for (int j = 0; j < invertedResults.get(i).size(); j++) {
                assertEquals(invertedResults.get(i).get(j), features.get(i).get(j), 0.001);
            }
        }
    }

    private SneRuntimeStats createRuntimeStats(float primeInference,
            float secondaryInference, int rssi, int integralUsedDesc, int onTime, int ccaBusy,
            int linkspeed, int contentionTimeAvg, int rxPkt, int txPkt, int score, boolean isMoving,
            int stepCount, boolean band) {
        SneWifiInfo sneWifiInfo = SneWifiInfo.newBuilder()
                .setRssi(rssi)
                .setContentionAverageTime(contentionTimeAvg)
                .setLinkSpeed(linkspeed)
                .setCcaBusyTime(ccaBusy)
                .setOnTime(onTime)
                .setScore(score)
                .setFrequency(band ? 5180 : 2412)
                .build();

        SneInferenceResult inferenceResult = SneInferenceResult.newBuilder()
                .setPrimary(primeInference)
                .setSecondary(secondaryInference)
                .build();

        SneWifiTrafficStats trafficStats = SneWifiTrafficStats.newBuilder()
                .setIntegralUsedDescriptorInDriver(integralUsedDesc)
                .setRxPkt(rxPkt)
                .setTxPkt(txPkt).build();

        SneSensorData sensorData = SneSensorData.newBuilder()
                .setIsMoving(isMoving)
                .setSensorStepCount(stepCount).build();

        SneRuntimeStats runtimeStats = SneRuntimeStats
                .newBuilder()
                .setInferenceResult(inferenceResult)
                .setWifiInfo(sneWifiInfo)
                .setSensorData(sensorData)
                .setWifiTrafficStats(trafficStats)
                .build();
        return runtimeStats;
    }
}
