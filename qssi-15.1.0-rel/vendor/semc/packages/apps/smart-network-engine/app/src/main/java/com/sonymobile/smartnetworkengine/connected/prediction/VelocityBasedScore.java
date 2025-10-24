/*
 * Copyright 2017 The Android Open Source Project
 * Copyright 2020, 2022 Sony Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * NOTE: This file has been modified by Sony Corporation
 * Modifications are licensed under the License.
 */

package com.sonymobile.smartnetworkengine.connected.prediction;

import static com.sonymobile.smartnetworkengine.Constants.WIFI_TRANSITION_SCORE;

import android.net.wifi.WifiInfo;

import com.sonymobile.smartnetworkengine.util.KalmanFilter;
import com.sonymobile.smartnetworkengine.util.Matrix;

/**
 * Class used to calculate scores for connected wifi networks and report it to the associated
 * network agent. This class is implemented with reference to com.android.server.wifi
 * .VelocityBasedConnectedScore
 */
public class VelocityBasedScore {

    // RSSI Threshold for exit wifi connection
    private static final int EXIT_RSSI_24GHZ_BAND = -83;
    private static final int EXIT_RSSI_5GHZ_BAND = -81;
    private static final int EXIT_RSSI_6GHZ_BAND = -80;

    // Band range
    private static final int BAND_24_GHZ_START_FREQ_MHZ = 2412;
    private static final int BAND_24_GHZ_END_FREQ_MHZ = 2484;
    private static final int BAND_5_GHZ_START_FREQ_MHZ = 5160;
    private static final int BAND_5_GHZ_END_FREQ_MHZ = 5865;
    private static final int BAND_6_GHZ_START_FREQ_MHZ = 5945;
    private static final int BAND_6_GHZ_END_FREQ_MHZ = 7105;

    private static final double DEFUALT_HORIZON = 15;
    private static final double DEFUALT_RSSI_STD_DEVIATION = 2.0;
    private static final double MIN_PPS_FOR_MESURE_SUCCESS = 2.0;

    private int mFrequency = BAND_5_GHZ_START_FREQ_MHZ;
    private double mThresholdAdjustment;
    private final KalmanFilter mFilter;
    private long mLastMillis;

    public VelocityBasedScore() {
        mFilter = new KalmanFilter();
        mFilter.mH = new Matrix(2, new double[]{1.0, 0.0});
        mFilter.mR = new Matrix(1, new double[]{1.0});
    }

    /**
     * Set the Kalman filter's state transition matrix F and process noise covariance Q given a time
     * step.
     *
     * @param dt delta time, in seconds
     */
    private void setDeltaTimeSeconds(double dt) {
        mFilter.mF = new Matrix(2, new double[]{1.0, dt, 0.0, 1.0});
        Matrix tG = new Matrix(1, new double[]{0.5 * dt * dt, dt});
        double stda = 0.02; // standard deviation of modelled acceleration
        mFilter.mQ = tG.dotTranspose(tG).dot(new Matrix(2, new double[]{
                stda * stda, 0.0,
                0.0, stda * stda}));
    }

    /**
     * Reset the filter state.
     */
    public void reset() {
        mLastMillis = 0;
        mThresholdAdjustment = 0;
        mFilter.mx = null;
    }

    /**
     * Updates scoring state using RSSI and measurement noise estimate
     * <p>
     * This is useful if an RSSI comes from another source (e.g. scan results) and the expected
     * noise varies by source.
     *
     * @param rssi              signal strength (dB).
     * @param millis            millisecond-resolution time.
     * @param standardDeviation of the RSSI.
     */
    public void updateUsingRssi(int rssi, long millis, double standardDeviation) {
        if (millis <= 0) return;
        if (mLastMillis <= 0 || millis < mLastMillis || mFilter.mx == null) {
            double initialVariance = 9.0 * standardDeviation * standardDeviation;
            mFilter.mx = new Matrix(1, new double[]{rssi, 0.0});
            mFilter.mP = new Matrix(2, new double[]{initialVariance, 0.0, 0.0, 0.0});
        } else {
            double dt = (millis - mLastMillis) * 0.001;
            mFilter.mR.put(0, 0, standardDeviation * standardDeviation);
            setDeltaTimeSeconds(dt);
            mFilter.predict();
            mFilter.update(new Matrix(1, new double[]{rssi}));
        }
        mLastMillis = millis;
        mFilteredRssi = mFilter.mx.get(0, 0);
        mEstimatedRateOfRssiChange = mFilter.mx.get(1, 0);
    }

    /**
     * Updates the state.
     */
    public void updateUsingWifiInfo(WifiInfo wifiInfo, long millis) {
        int frequency = wifiInfo.getFrequency();
        if (frequency != mFrequency) {
            mLastMillis = 0; // Probably roamed; reset filter but retain threshold adjustment
            // Consider resetting or partially resetting threshold adjustment
            // Consider checking bssid
            mFrequency = frequency;
        }
        updateUsingRssi(wifiInfo.getRssi(), millis, DEFUALT_RSSI_STD_DEVIATION);
        adjustThreshold(wifiInfo);
    }

    private double mFilteredRssi;
    private double mEstimatedRateOfRssiChange;

    private int getExitRssi(int frequency) {
        if (frequency >= BAND_24_GHZ_START_FREQ_MHZ && frequency <= BAND_24_GHZ_END_FREQ_MHZ) {
            return EXIT_RSSI_24GHZ_BAND;
        } else if (frequency >= BAND_5_GHZ_START_FREQ_MHZ && frequency <= BAND_5_GHZ_END_FREQ_MHZ) {
            return EXIT_RSSI_5GHZ_BAND;
        } else if (frequency >= BAND_6_GHZ_START_FREQ_MHZ && frequency <= BAND_6_GHZ_END_FREQ_MHZ) {
            return EXIT_RSSI_6GHZ_BAND;
        } else {
            return EXIT_RSSI_5GHZ_BAND;
        }
    }

    /**
     * Returns the most recently computed extimate of the RSSI.
     */
    public double getFilteredRssi() {
        return mFilteredRssi;
    }

    /**
     * Returns the estimated rate of change of RSSI, in dB/second
     */
    public double getEstimatedRateOfRssiChange() {
        return mEstimatedRateOfRssiChange;
    }

    /**
     * Returns the adjusted RSSI threshold
     */
    public double getAdjustedRssiThreshold() {
        return getExitRssi(mFrequency) + mThresholdAdjustment;
    }

    /**
     * Adjusts the threshold if appropriate
     * <p>
     * If the (filtered) rssi is near or below the current effective threshold, and the rate of rssi
     * change is small, and there is traffic, and the error rate is looking reasonable, then
     * decrease the effective threshold to keep from dropping a perfectly good connection.
     */
    private void adjustThreshold(WifiInfo wifiInfo) {
        if (mThresholdAdjustment < -7) return;
        if (mFilteredRssi >= getAdjustedRssiThreshold() + 2.0) return;
        if (Math.abs(mEstimatedRateOfRssiChange) >= 0.2) return;
        double txSuccessPps = wifiInfo.getSuccessfulTxPacketsPerSecond();
        double rxSuccessPps = wifiInfo.getSuccessfulRxPacketsPerSecond();
        if (txSuccessPps < MIN_PPS_FOR_MESURE_SUCCESS) return;
        if (rxSuccessPps < MIN_PPS_FOR_MESURE_SUCCESS) return;
        double txBadPps = wifiInfo.getLostTxPacketsPerSecond();
        double txRetriesPps = wifiInfo.getRetriedTxPacketsPerSecond();
        double probabilityOfSuccessfulTx = txSuccessPps / (txSuccessPps + txBadPps + txRetriesPps);
        if (probabilityOfSuccessfulTx > 0.2) {
            // May want this amount to vary with how close to threshold we are
            mThresholdAdjustment -= 0.5;
        }
    }

    /**
     * Velocity scorer - predict the rssi a few seconds from now
     */
    public int generateScore() {
        if (mFilter.mx == null) return WIFI_TRANSITION_SCORE + 1;
        double badRssi = getAdjustedRssiThreshold();
        Matrix x = new Matrix(mFilter.mx);
        double filteredRssi = x.get(0, 0);
        setDeltaTimeSeconds(DEFUALT_HORIZON);
        x = mFilter.mF.dot(x);
        double forecastRssi = x.get(0, 0);
        if (forecastRssi > filteredRssi) {
            forecastRssi = filteredRssi; // Be pessimistic about predicting an actual increase
        }
        return (int) (Math.round(forecastRssi) - badRssi) + WIFI_TRANSITION_SCORE;
    }
}
