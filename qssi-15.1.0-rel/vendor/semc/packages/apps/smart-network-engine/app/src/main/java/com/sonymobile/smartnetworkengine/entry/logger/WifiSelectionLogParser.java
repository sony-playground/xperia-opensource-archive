/*
 * Copyright 2020, 2021, 2022, 2023 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.entry.logger;

import static com.sonymobile.smartnetworkengine.Constants.ENTRY_ASSET_DIR;
import static com.sonymobile.smartnetworkengine.Constants.ENTRY_MEAN_FILENAME;
import static com.sonymobile.smartnetworkengine.Constants.ENTRY_VAR_FILENAME;

import android.content.Context;
import android.content.res.AssetManager;
import android.net.wifi.ScanResult;
import android.os.Build;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;

import com.sonymobile.smartnetworkengine.api.LoggingStats;
import com.sonymobile.smartnetworkengine.entry.logger.WifiSelectionLogger.ConnectStatsInfo;
import com.sonymobile.smartnetworkengine.entry.logger.WifiSelectionLogger.LoggingStatsInfo;
import com.sonymobile.smartnetworkengine.entry.logger.WifiSelectionLogger.ScanResultInfo;
import com.sonymobile.smartnetworkengine.entry.logger.WifiSelectionLogger.ValidationCompleteStatsInfo;
import com.sonymobile.smartnetworkengine.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.file.Paths;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.TimeZone;

public class WifiSelectionLogParser {

    private static final String TAG = WifiSelectionLogParser.class.getSimpleName();

    private static final boolean DEBUG_BUILD = Build.TYPE.equals("userdebug");

    private static final int MAX_QUEUE_LENGTH = 20;

    private static final int SIZE_OF_LABEL_SAMPLES = 10;

    private final ArrayDeque<ScanResultInfo> mScanResultsInfoBeforeValidationQueue
            = new ArrayDeque<>();

    private final ArrayList<LoggingStatsInfo> mLoggingStatsInfoList = new ArrayList<>();

    private ConnectStatsInfo mConnectStatsInfo;

    private ValidationCompleteStatsInfo mValidationCompleteStatsInfo;

    private String mConnectedBSSID;

    @VisibleForTesting // This can be avoided once |parseFeatures| UT is ready
    @Nullable
    List<Float> mFeatures;

    private float mLabelAverage;

    @VisibleForTesting
    @Nullable
    final Map<String, Float> mVarMap;

    @VisibleForTesting
    @Nullable
    final Map<String, Float> mMeanMap;

    @NonNull
    private final AssetManager mAssetManager;

    public WifiSelectionLogParser(Context context) {
        mAssetManager = context.getAssets();
        mVarMap = loadMapForNormalization(
                Paths.get(ENTRY_ASSET_DIR, ENTRY_VAR_FILENAME).toString());
        mMeanMap = loadMapForNormalization(
                Paths.get(ENTRY_ASSET_DIR, ENTRY_MEAN_FILENAME).toString());
        mLabelAverage = 0;
    }

    public void putLabelAverage(float labelAverage) {
        mLabelAverage = labelAverage;
    }

    public void putScanResultInfoBeforeValidation(ScanResultInfo scanResultInfo) {
        if (mScanResultsInfoBeforeValidationQueue.size() > MAX_QUEUE_LENGTH) {
            mScanResultsInfoBeforeValidationQueue.poll();
        }
        mScanResultsInfoBeforeValidationQueue.add(scanResultInfo);
    }

    public void putConnectStatsInfo(ConnectStatsInfo connectStatsInfo) {
        mConnectStatsInfo = connectStatsInfo;
    }

    public void putValidationCompleteStatsInfo(
            ValidationCompleteStatsInfo validationCompleteStatsInfo) {
        mValidationCompleteStatsInfo = validationCompleteStatsInfo;
    }

    public void putConnectedBssid(String bssid) {
        mConnectedBSSID = bssid;
    }

    public void putLoggingStatsInfo(LoggingStatsInfo loggingStatsInfo) {
        if (mLoggingStatsInfoList.size() < SIZE_OF_LABEL_SAMPLES) {
            mLoggingStatsInfoList.add(loggingStatsInfo);
        }
    }

    @Nullable
    public List<Float> parseFeatures() {
        if (!isDataAvailable()) {
            return null;
        }
        int frequency = mValidationCompleteStatsInfo.getFrequency();
        List<Float> features = new ArrayList<>();
        features.add(parseCcabt(frequency));
        features.add(mLabelAverage);
        features.add(parseNumOfAllCoChannels(frequency));
        features.add(parseMetricsInfo());
        features.add(parseDate());
        if (!features.contains(Float.NaN)) {
            mFeatures = features;
        } else {
            mFeatures = null;
        }
        if (DEBUG_BUILD) {
            Log.v(TAG, "parseFeatures " + mFeatures);
        }
        return mFeatures;
    }

    @Nullable
    public Float parseLabel() {
        Float label = null;
        if (mFeatures != null) {
            float result = getLabel();
            if (!Float.isNaN(result)) {
                label = result;
            }
        }
        return label;
    }

    private float parseCcabt(int frequency) {

        long[] ccabtsScan = getBeforeValidationCcaBusyTimes(frequency);
        Long ccabt = mConnectStatsInfo.getRadioTimeInfo().getCcaBusyTimes().get(frequency);
        long ccabtConnected = 0;
        if (ccabt != null) {
            ccabtConnected = ccabt;
        } else {
            Log.e(TAG, "Unexpected: could not get cca busy time for scan");
        }

        long ccabtValidated = 0;
        ccabt = mValidationCompleteStatsInfo.getRadioTimeInfo().getCcaBusyTimes().get(frequency);
        if (ccabt != null) {
            ccabtValidated = ccabt;
        } else {
            Log.e(TAG, "Unexpected: could not get cca busy time for validation complete");
        }

        long[] ontimesScan = getBeforeValidationOnTimes(frequency);
        long ontimeConnected = 0;
        ccabt = mConnectStatsInfo.getRadioTimeInfo().getOnTimes().get(frequency);
        if (ccabt != null) {
            ontimeConnected = ccabt;
        } else {
            Log.e(TAG, "Unexpected: could not get cca busy time for connected");
        }

        long ontimeValidated = 0;
        Long ontime = mValidationCompleteStatsInfo.getRadioTimeInfo().getOnTimes().get(frequency);
        if (ontime != null) {
            ontimeValidated = ontime;
        } else {
            Log.e(TAG, "Unexpected: could not get ontime for validation complete");
        }

        long[] timesScan = getBeforeValidationTimes();
        long timeConnected = mConnectStatsInfo.getTimeStamp();
        long timeValidated = mValidationCompleteStatsInfo.getTimeStamp();

        // Calculate ccabt connected-scan ratio
        float ccabtCsRatio = -1;
        long ccabtScan = 0;
        long ontimeScan = 0;
        long timeScan = 0;
        float ontimeCsDiff;
        // If ccabt_cs_ratio is greater than 1,
        // calculate again in the next scan record cca busy time.
        for (int i = 0; i < ccabtsScan.length; i++) {
            ccabtScan = ccabtsScan[i];
            ontimeScan = ontimesScan[i];
            timeScan = timesScan[i];
            ontimeCsDiff = ontimeConnected - ontimeScan;
            if (ontimeCsDiff > 0 && timeScan < timeConnected && ccabtScan != -1
                    && ontimeScan != -1) {
                ccabtCsRatio = (ccabtConnected - ccabtScan) / ontimeCsDiff;
            }
            if (ccabtCsRatio <= 1 && ccabtCsRatio >= 0) {
                break;
            }
        }

        // Calcurlate ccabt varidated-connected ratio
        float ccabtVcRatio = -1;
        long ontimeVcDiff = ontimeValidated - ontimeConnected;
        // check outliers
        if (ontimeVcDiff > 0 && timeConnected < timeValidated) {
            ccabtVcRatio = (float) (ccabtValidated - ccabtConnected) / ontimeVcDiff;
        }

        // Calculate ccabt varidated-scan ratio
        float ccabtVsRatio = -1;
        long ontimeVsDiff = ontimeValidated - ontimeScan;
        // check outliers
        if (ontimeVsDiff > 0) {
            ccabtVsRatio = (float) (ccabtValidated - ccabtScan) / ontimeVsDiff;
        }

        float ccabtFeature = -1;
        if (ccabtCsRatio > 1) {
            if (ccabtVcRatio >= 0 && ccabtVcRatio <= 1) {
                ccabtFeature = ccabtVcRatio;
            }
        } else if (ccabtVcRatio > 1) {
            if (ccabtCsRatio >= 0 && ccabtCsRatio <= 1) {
                ccabtFeature = ccabtCsRatio;
            }
        } else {
            if (ccabtVsRatio >= 0 && ccabtVsRatio <= 1) {
                ccabtFeature = ccabtVsRatio;
            }
        }

        // check outliers
        float result = Float.NaN;
        if (ccabtFeature >= 0 && ccabtFeature <= 1) {
            ccabtFeature = normalization("ccabt_ontime_weighted_average", ccabtFeature);
            result = ccabtFeature;
        }
        return result;
    }

    private float parseMetricsInfo() {
        float result = Float.NaN;
        long txSuccessV = mValidationCompleteStatsInfo.getRawTxSuccess();
        long txSuccessC = mConnectStatsInfo.getRawTxSuccess();
        long txSuccess = txSuccessV - txSuccessC;
        if (txSuccessV >= 0 && txSuccessC >= 0 && txSuccess >= 0 && txSuccess <= 100000) {
            result = normalization("txSuccess", txSuccess);
        }
        return result;
    }

    private float parseDate() {
        Date date = new Date(mValidationCompleteStatsInfo.getTimeStamp());
        Calendar calendar = Calendar.getInstance();
        calendar.setTimeZone(TimeZone.getTimeZone("GMT"));
        calendar.setTime(date);
        int time = calendar.get(Calendar.HOUR_OF_DAY);
        if (time < 5) {
            time += 24;
        }
        return normalization("corrected_hour", time);
    }

    private float parseNumOfAllCoChannels(int frequency) {
        if (mScanResultsInfoBeforeValidationQueue.isEmpty()) {
            return Float.NaN;
        }
        List<String> coChannelBSSIDs = new ArrayList<>();
        for (ScanResultInfo scanResultInfo : mScanResultsInfoBeforeValidationQueue) {
            List<ScanResult> scanResults = scanResultInfo.getScanResults();
            for (ScanResult scanResult : scanResults) {
                if (frequency == scanResult.frequency & !scanResult.BSSID.equals(mConnectedBSSID)) {
                    coChannelBSSIDs.add(scanResult.BSSID);
                }
            }
        }
        int numOfCoChannels = coChannelBSSIDs.size();
        float avgNumOfCoChannels =
                (float) numOfCoChannels / mScanResultsInfoBeforeValidationQueue.size();
        return normalization("num_of_coChannels", avgNumOfCoChannels);
    }

    private float getLabel() {
        if (mLoggingStatsInfoList.size() < SIZE_OF_LABEL_SAMPLES) {
            // If an evaluation period is shorter than 30 sec., it is aborted.
            return Float.NaN;
        }

        long totalCcaBusyTime = 0;
        long totalOnTime = 0;

        for (LoggingStatsInfo loggingStatsInfo : mLoggingStatsInfoList) {
            LoggingStats.Wifi wifi = loggingStatsInfo.getWifi();
            long ccaBusyTimeDiff = wifi.getCcaBusyTime();
            long onTimeDiff = wifi.getOnTime();
            if (onTimeDiff > 0 && ccaBusyTimeDiff / onTimeDiff <= 1) {
                totalCcaBusyTime += ccaBusyTimeDiff;
                totalOnTime += onTimeDiff;
            }
        }

        float result = Float.NaN;
        if (totalOnTime > 0) {
            result = (float) totalCcaBusyTime / totalOnTime;
        }
        return result;
    }

    private long[] getBeforeValidationCcaBusyTimes(int frequency) {
        long[] ccaBusyTimes = new long[mScanResultsInfoBeforeValidationQueue.size()];
        int i = 0;
        for (ScanResultInfo scanResultInfo : mScanResultsInfoBeforeValidationQueue) {
            Long ccaBusyTime = scanResultInfo.getRadioTimeInfo().getCcaBusyTimes().get(frequency);
            if (ccaBusyTime != null) {
                ccaBusyTimes[i++] = ccaBusyTime;
            } else {
                ccaBusyTimes[i++] = -1;
            }
        }
        return ccaBusyTimes;
    }

    private long[] getBeforeValidationOnTimes(int frequency) {
        long[] onTimes = new long[mScanResultsInfoBeforeValidationQueue.size()];
        int i = 0;
        for (ScanResultInfo scanResultInfo : mScanResultsInfoBeforeValidationQueue) {
            Long onTime = scanResultInfo.getRadioTimeInfo().getOnTimes().get(frequency);
            if (onTime != null) {
                onTimes[i++] = onTime;
            } else {
                onTimes[i++] = -1;
            }
        }
        return onTimes;
    }

    private long[] getBeforeValidationTimes() {
        long[] times = new long[mScanResultsInfoBeforeValidationQueue.size()];
        int i = 0;
        for (ScanResultInfo scanResultInfo : mScanResultsInfoBeforeValidationQueue) {
            times[i++] = scanResultInfo.getTimeStamp();
        }
        return times;
    }

    @VisibleForTesting
    /* package */ float normalization(String item, float value) {
        float result = 0;
        if (mMeanMap != null && mVarMap != null) {
            final float mean = mMeanMap.get(item);
            final float var = mVarMap.get(item);
            final float sd = (float) Math.sqrt(var);
            if (sd != 0) {
                result = (value - mean) / sd;
            }
        }
        return result;
    }

    private boolean isDataAvailable() {
        return (!mScanResultsInfoBeforeValidationQueue.isEmpty() && mConnectStatsInfo != null
                && mValidationCompleteStatsInfo != null && !mConnectedBSSID.isEmpty());
    }

    public void clearData() {
        mScanResultsInfoBeforeValidationQueue.clear();
        mLoggingStatsInfoList.clear();
        mConnectStatsInfo = null;
        mValidationCompleteStatsInfo = null;
    }

    private Map<String, Float> loadMapForNormalization(String filename) {
        Map<String, Float> map = new HashMap<>();
        try (InputStream inputStream = mAssetManager.open(filename);
             InputStreamReader reader = new InputStreamReader(inputStream);
             BufferedReader bufferedReader = new BufferedReader(reader)) {

            String headers = bufferedReader.readLine();
            String values = bufferedReader.readLine();
            if (headers != null && values != null) {
                String[] header = headers.split(",");
                String[] value = values.split(",");
                for (int i = 0; i < header.length; i++) {
                    map.put(header[i], Float.parseFloat(value[i]));
                }
            }
        } catch (IOException e) {
            Log.e(TAG, "parser cannot read csv data for normalization");
        }
        return map;
    }
}
