/*
 * Copyright 2021, 2022, 2023 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.entry.logger;

import static androidx.test.platform.app.InstrumentationRegistry.getInstrumentation;

import static org.hamcrest.CoreMatchers.is;
import static org.hamcrest.CoreMatchers.notNullValue;
import static org.hamcrest.CoreMatchers.nullValue;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertThat;

import android.content.res.AssetManager;
import android.net.wifi.ScanResult;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sonymobile.smartnetworkengine.api.LoggingStats;
import com.sonymobile.smartnetworkengine.entry.logger.collector.WifiLinkLayerStatsCollector;
import com.sonymobile.smartnetworkengine.util.Log;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.MockitoAnnotations;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Verify {@link WifiSelectionLogParser} implementation.
 */
@RunWith(AndroidJUnit4.class)
public class WifiSelectionLogParserTest {

    private WifiSelectionLogParser mLogParser;

    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);
        mLogParser = new WifiSelectionLogParser(getInstrumentation().getTargetContext());
    }

    @Test
    public void testMapInitialization() {
        // <Mean>
        //  ccabt_ontime_weighted_average,num_of_coChannels,txSuccess,corrected_hour
        //  0.36848477,5.07064411,46.16047136,15.88658627
        final Map<String, Float> mMeanExpected = new HashMap<String, Float>() {
            {
                put("ccabt_ontime_weighted_average", 0.36848477f);
                put("num_of_coChannels", 5.07064411f);
                put("txSuccess", 46.16047136f);
                put("corrected_hour", 15.88658627f);
            }
        };

        // Check
        assertThat(mLogParser.mMeanMap, is(mMeanExpected));

        // <Var>
        //  ccabt_ontime_weighted_average,num_of_coChannels,txSuccess,corrected_hour
        //  2.92639569e-02,5.86466974,7.33790372e+03,6.67706238e+01
        final Map<String, Float> mVarExpected = new HashMap<String, Float>() {
            {
                put("ccabt_ontime_weighted_average", 2.92639569e-02f);
                put("num_of_coChannels", 5.86466974f);
                put("txSuccess", 7.33790372e+03f);
                put("corrected_hour", 6.67706238e+01f);
            }
        };

        // Check
        assertThat(mLogParser.mVarMap, is(mVarExpected));
    }

    @Test
    public void testParseLabel() {
        mLogParser.mFeatures = new ArrayList<>();

        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(0).onTime(0).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1560).onTime(2947).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1951).onTime(2963).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1710).onTime(2959).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1585).onTime(2960).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(2284).onTime(2952).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1954).onTime(2961).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(2094).onTime(2955).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1948).onTime(2482).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1704).onTime(2169).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(2353).onTime(2964).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1997).onTime(2966).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1755).onTime(2961).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1991).onTime(2967).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1751).onTime(2968).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1575).onTime(2959).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1883).onTime(2967).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1722).onTime(2964).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1098).onTime(2336).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1572).onTime(2960).build(), null));

        // Action
        Float label = mLogParser.parseLabel();

        // Check
        assertThat(label, is(notNullValue()));
        assertEquals(label, 0.6623796749250433, 1e-6);
    }

    @Test
    public void testParseLabel_checkNumOfSamples() {
        mLogParser.mFeatures = new ArrayList<>();

        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(0).onTime(0).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1560).onTime(2947).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1951).onTime(2963).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1710).onTime(2959).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1585).onTime(2960).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(2284).onTime(2952).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1954).onTime(2961).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(2094).onTime(2955).build(), null));
        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1948).onTime(2482).build(), null));

        // Action (with 9 samples)
        Float label = mLogParser.parseLabel();

        // Check
        assertThat(label, is(nullValue()));

        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(1704).onTime(2169).build(), null));

        // Action (with 10 samples)
        label = mLogParser.parseLabel();

        // Check
        assertThat(label, is(notNullValue()));

        mLogParser.putLoggingStatsInfo(new WifiSelectionLogger.LoggingStatsInfo(
                LoggingStats.Wifi.builder().ccaBusyTime(2353).onTime(2964).build(), null));

        // Action (with 11 samples)
        Float label2 = mLogParser.parseLabel();

        // Check (over 10 samples are not used so result should be same as before)
        assertThat(label2, is(label));
    }

    @Test
    public void testParseDataForPrediction() {
        // NOTE: Values used in this test case is recorded in logid 65.
        mLogParser.putConnectedBssid("dc:fb:02:14:d3:b5");

        ScanResult scanResult1 = new ScanResult();
        scanResult1.BSSID = "dc:fb:02:14:d3:b5";
        scanResult1.frequency = 5640;
        HashMap<Integer, Long> onTimes1 = new HashMap<>();
        HashMap<Integer, Long> ccaBusyTimes1 = new HashMap<>();
        ccaBusyTimes1.put(5640, 17009L);
        onTimes1.put(5640, 1456675L);
        WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo1 =
                WifiLinkLayerStatsCollector.RadioTimeInfo.builder().onTimes(onTimes1).ccaBusyTimes(
                        ccaBusyTimes1).build();
        mLogParser.putScanResultInfoBeforeValidation(
                WifiSelectionLogger.ScanResultInfo.builder().timeStamp(1626677517228L)
                        .scanResults(new ArrayList<>(List.of(scanResult1)))
                        .radioTimeInfo(radioTimeInfo1)
                        .build());

        ScanResult scanResult2 = new ScanResult();
        scanResult2.frequency = 5640;
        scanResult2.BSSID = "dc:fb:02:14:d3:b5";
        HashMap<Integer, Long> ccaBusyTimes2 = new HashMap<>();
        HashMap<Integer, Long> onTimes2 = new HashMap<>();
        ccaBusyTimes2.put(5640, 17161L);
        onTimes2.put(5640, 1476218L);
        WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo2 =
                WifiLinkLayerStatsCollector.RadioTimeInfo.builder().onTimes(onTimes2).ccaBusyTimes(
                        ccaBusyTimes2).build();
        mLogParser.putScanResultInfoBeforeValidation(
                WifiSelectionLogger.ScanResultInfo.builder().timeStamp(1626677624424L)
                        .scanResults(new ArrayList<>(List.of(scanResult2)))
                        .radioTimeInfo(radioTimeInfo2)
                        .build());

        ScanResult scanResult3 = new ScanResult();
        scanResult3.frequency = 5640;
        scanResult3.BSSID = "dc:fb:02:14:d3:b5";
        HashMap<Integer, Long> ccaBusyTimes3 = new HashMap<>();
        HashMap<Integer, Long> onTimes3 = new HashMap<>();
        ccaBusyTimes3.put(5640, 17215L);
        onTimes3.put(5640, 1485045L);
        WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo3 =
                WifiLinkLayerStatsCollector.RadioTimeInfo.builder().onTimes(onTimes3).ccaBusyTimes(
                        ccaBusyTimes3).build();
        mLogParser.putScanResultInfoBeforeValidation(
                WifiSelectionLogger.ScanResultInfo.builder().timeStamp(1626677658845L)
                        .scanResults(new ArrayList<>(List.of(scanResult3)))
                        .radioTimeInfo(radioTimeInfo3)
                        .build());

        ScanResult scanResult4 = new ScanResult();
        scanResult4.frequency = 5640;
        scanResult4.BSSID = "dc:fb:02:14:d3:b5";
        HashMap<Integer, Long> ccaBusyTimes4 = new HashMap<>();
        HashMap<Integer, Long> onTimes4 = new HashMap<>();
        ccaBusyTimes4.put(5640, 17405L);
        onTimes4.put(5640, 1516610L);
        WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo4 =
                WifiLinkLayerStatsCollector.RadioTimeInfo.builder().onTimes(onTimes4).ccaBusyTimes(
                        ccaBusyTimes4).build();
        mLogParser.putScanResultInfoBeforeValidation(
                WifiSelectionLogger.ScanResultInfo.builder().timeStamp(1626677837528L)
                        .scanResults(new ArrayList<>(List.of(scanResult4)))
                        .radioTimeInfo(radioTimeInfo4)
                        .build());

        HashMap<Integer, Long> ccaBusyTimesConnect = new HashMap<>();
        HashMap<Integer, Long> onTimesConnect = new HashMap<>();
        ccaBusyTimesConnect.put(5640, 17037L);
        onTimesConnect.put(5640, 1458930L);
        WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfoConnect =
                WifiLinkLayerStatsCollector.RadioTimeInfo.builder().onTimes(
                        onTimesConnect).ccaBusyTimes(ccaBusyTimesConnect).build();
        WifiSelectionLogger.ConnectStatsInfo connectStatsInfo =
                WifiSelectionLogger.ConnectStatsInfo.builder().timestamp(1626677517516L).frequency(
                        5640).rawTxSuccess(2).radioTimeInfo(radioTimeInfoConnect).build();
        mLogParser.putConnectStatsInfo(connectStatsInfo);

        HashMap<Integer, Long> ccaBusyTimesValidated = new HashMap<>();
        HashMap<Integer, Long> onTimesValidated = new HashMap<>();
        ccaBusyTimesValidated.put(5640, 17037L);
        onTimesValidated.put(5640, 1458946L);
        WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfoValidated =
                WifiLinkLayerStatsCollector.RadioTimeInfo.builder().onTimes(
                        onTimesValidated).ccaBusyTimes(ccaBusyTimesValidated).build();
        WifiSelectionLogger.ValidationCompleteStatsInfo validationCompleteStatsInfo =
                WifiSelectionLogger.ValidationCompleteStatsInfo.builder().timestamp(
                        1626677520529L).frequency(5640).rawTxSuccess(65).radioTimeInfo(
                        radioTimeInfoValidated).build();
        mLogParser.putValidationCompleteStatsInfo(validationCompleteStatsInfo);
        mLogParser.putLabelAverage(0.37f);
        List<Float> feature = mLogParser.parseFeatures();

        Float ccabtExpected = -2.081963f;
        Float numOfCoChannelExpected = -2.0938294f;
        Float txSuccessExpected = 0.19658205f;
        Float correctedHoursExpected = -1.2099116f;
        Float labelAverageExpected = 0.37f;
        assertEquals(Arrays.asList(ccabtExpected, labelAverageExpected, numOfCoChannelExpected,
                txSuccessExpected, correctedHoursExpected), feature);
    }

    @Test
    public void testParseForPredictionCsv() throws IOException, JSONException {
        AssetManager assetManager = getInstrumentation().getContext().getAssets();
        InputStream inputStreamRawData = assetManager.open("raw_data.csv");
        InputStream inputStreamParsedData = assetManager.open("parsed_data.csv");

        InputStreamReader inputStreamReader = new InputStreamReader(inputStreamRawData);
        InputStreamReader inputStreamParsedDataReader = new InputStreamReader(
                inputStreamParsedData);

        // Read csv file including JSON
        List<String[]> rawData = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(inputStreamReader)) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] values = line.split(",(?=(?:[^\"]*\"[^\"]*\")*[^\"]*$)", -1);
                rawData.add(values);
            }
        }

        // Read csv file including expected results
        List<String[]> parsedData = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(inputStreamParsedDataReader)) {
            String line;
            while ((line = br.readLine()) != null) {
                String[] values = line.split(",");
                parsedData.add(values);
            }
        }

        for (int i = 1; i < rawData.size(); i++) { // pass header
            mLogParser.clearData();
            String[] line = rawData.get(i);
            // Extract JSON object and removing escape chars
            String jsonString = line[3];
            jsonString = jsonString.replace("\"\"", "\"");
            jsonString = jsonString.replace("\"{", "{");
            jsonString = jsonString.replace("}\"", "}");
            JSONObject parentJsonObject = null;

            // Create JsonObject
            try {
                parentJsonObject = new JSONObject(jsonString);
            } catch (JSONException e) {
                Log.e(this.getClass().getSimpleName(), "cannot parse: " + jsonString);
            }
            if (parentJsonObject != null) {
                // Parse JSON Object
                // ScanInfo
                JSONArray scanInfoJsonArrays = parentJsonObject.getJSONArray("scan_info");
                for (int j = 0; j < scanInfoJsonArrays.length(); j++) {
                    JSONArray scanInfoJsonArray = scanInfoJsonArrays.getJSONArray(j);
                    if (scanInfoJsonArray.length() == 0) {
                        // sometimes there is no component case.
                    } else {
                        JSONArray scanInfo = scanInfoJsonArray.getJSONArray(0);
                        ScanResult scanResult = new ScanResult();
                        long timeStamp = scanInfo.getLong(0);
                        scanResult.BSSID = scanInfo.getString(3);
                        int freq = scanInfo.getInt(5);
                        scanResult.frequency = freq;
                        long ccabt = scanInfo.getLong(11);
                        long onTime = scanInfo.getLong(12);
                        HashMap<Integer, Long> onTimes = new HashMap<>();
                        HashMap<Integer, Long> ccaBusyTimes = new HashMap<>();
                        ccaBusyTimes.put(freq, ccabt);
                        onTimes.put(freq, onTime);
                        WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo =
                                WifiLinkLayerStatsCollector.RadioTimeInfo.builder()
                                        .onTimes(onTimes).ccaBusyTimes(ccaBusyTimes).build();
                        mLogParser.putScanResultInfoBeforeValidation(
                                WifiSelectionLogger.ScanResultInfo.builder().timeStamp(timeStamp)
                                        .scanResults(new ArrayList<>(List.of(scanResult)))
                                        .radioTimeInfo(radioTimeInfo)
                                        .build());
                    }
                }

                // connectInfo
                JSONArray connectedInfoArray = parentJsonObject.getJSONArray(
                        "connected_info").getJSONArray(0);
                long timestampConnected = connectedInfoArray.getLong(0);
                String bssid = connectedInfoArray.getString(2);
                int freqConnected = connectedInfoArray.getInt(4);
                int txSuccessConnected = connectedInfoArray.getInt(7);
                long ccabtC = connectedInfoArray.getLong(11);
                long onTimeC = connectedInfoArray.getLong(12);
                HashMap<Integer, Long> ccaBusyTimesConnect = new HashMap<>();
                HashMap<Integer, Long> onTimesConnect = new HashMap<>();
                ccaBusyTimesConnect.put(freqConnected, ccabtC);
                onTimesConnect.put(freqConnected, onTimeC);
                WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfoConnect =
                        WifiLinkLayerStatsCollector.RadioTimeInfo.builder()
                                .onTimes(onTimesConnect)
                                .ccaBusyTimes(ccaBusyTimesConnect).build();
                WifiSelectionLogger.ConnectStatsInfo connectStatsInfo =
                        WifiSelectionLogger.ConnectStatsInfo.builder()
                                .timestamp(timestampConnected)
                                .frequency(freqConnected)
                                .rawTxSuccess(txSuccessConnected)
                                .radioTimeInfo(radioTimeInfoConnect)
                                .build();
                mLogParser.putConnectedBssid(bssid);
                mLogParser.putConnectStatsInfo(connectStatsInfo);

                // validatedInfo
                JSONArray validationCompleteInfoArray = parentJsonObject.getJSONArray(
                        "validation_complete_info").getJSONArray(0);
                long timestampValidationComplete = validationCompleteInfoArray.getLong(0);
                int freqValidationComplete = validationCompleteInfoArray.getInt(4);
                int txSuccessValidationComplete = validationCompleteInfoArray.getInt(7);
                long ccabtV = validationCompleteInfoArray.getLong(11);
                long onTimeV = validationCompleteInfoArray.getLong(12);
                HashMap<Integer, Long> ccaBusyTimesValidationComplete = new HashMap<>();
                HashMap<Integer, Long> onTimesValidationComplete = new HashMap<>();
                ccaBusyTimesValidationComplete.put(freqValidationComplete, ccabtV);
                onTimesValidationComplete.put(freqValidationComplete, onTimeV);
                WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfoValidationComplete =
                        WifiLinkLayerStatsCollector.RadioTimeInfo.builder()
                                .onTimes(onTimesValidationComplete)
                                .ccaBusyTimes(ccaBusyTimesValidationComplete).build();
                WifiSelectionLogger.ValidationCompleteStatsInfo validationCompleteStatsInfo =
                        WifiSelectionLogger.ValidationCompleteStatsInfo.builder()
                                .timestamp(timestampValidationComplete)
                                .frequency(freqValidationComplete)
                                .rawTxSuccess(txSuccessValidationComplete)
                                .radioTimeInfo(radioTimeInfoValidationComplete).build();
                mLogParser.putValidationCompleteStatsInfo(validationCompleteStatsInfo);
                mLogParser.putLabelAverage(0.37f);
                List<Float> feature =  mLogParser.parseFeatures();
                if (feature == null) continue;

                Float ccabt = feature.get(0);
                Float txSuccess = feature.get(3);
                Float correctedHour = feature.get(4);

                // search parsed_data for matched line
                for (int j = 1; j < parsedData.size(); j++) {
                    String[] parsedDataLine = parsedData.get(j);
                    int logId = Integer.parseInt(parsedDataLine[1]);
                    if (logId == i - 1) {
                        Float ccaBtOnTimeExpected = mLogParser.normalization(
                                "ccabt_ontime_weighted_average",
                                Float.parseFloat(parsedDataLine[2]));
                        Float txSuccessExpected = mLogParser.normalization("txSuccess",
                                Float.parseFloat(parsedDataLine[4]));
                        Float correctedHourExpected = mLogParser.normalization("corrected_hour",
                                Float.parseFloat(parsedDataLine[5]));
                        assertEquals("logId: " + logId + ": ccaBt", ccaBtOnTimeExpected, ccabt, 0);
                        assertEquals("logId: " + logId + ": txSuccess", txSuccessExpected,
                                txSuccess,
                                0.01);
                        assertEquals("logId: " + logId + ": correctedHour", correctedHourExpected,
                                correctedHour, 0.01);
                    }
                }
            }
        }
    }
}
