/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.ext.cellular.collector;

import android.net.TrafficStats;

/**
 * Collect TrafficStats data (MobileRxBytesDiff, MobileTxBytesDiff)
 */
public class TrafficStatsCollector {
    private long mMobileRxBytesDiff;
    private long mMobileTxBytesDiff;
    private long mLastMobileTxBytes;
    private long mLastMobileRxBytes;

    public TrafficStatsCollector() {
        reset();
    }

    /**
     * Reset internal state.
     */
    public void reset() {
        mMobileRxBytesDiff = 0;
        mMobileTxBytesDiff = 0;
        mLastMobileRxBytes = -1;
        mLastMobileTxBytes = -1;
    }

    /**
     * Calculate diff values from previous call internally.
     * Call just before calling getters.
     */
    public void update() {
        // when called first time
        if (mLastMobileRxBytes == -1) {
            mLastMobileRxBytes = TrafficStats.getMobileRxBytes();
            mLastMobileTxBytes = TrafficStats.getMobileTxBytes();
        } else { // when called more than once after reset
            long currentMobileRxBytes = TrafficStats.getMobileRxBytes();
            long currentMobileTxBytes = TrafficStats.getMobileTxBytes();
            mMobileRxBytesDiff = currentMobileRxBytes - mLastMobileRxBytes;
            mMobileTxBytesDiff = currentMobileTxBytes - mLastMobileTxBytes;
            mLastMobileRxBytes = currentMobileRxBytes;
            mLastMobileTxBytes = currentMobileTxBytes;
        }
    }

    public long getMobileRxBytesDiff() {
        return mMobileRxBytesDiff;
    }

    public long getMobileTxBytesDiff() {
        return mMobileTxBytesDiff;
    }
}