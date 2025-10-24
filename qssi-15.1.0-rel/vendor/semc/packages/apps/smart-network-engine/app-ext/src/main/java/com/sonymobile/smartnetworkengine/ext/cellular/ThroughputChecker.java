/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.ext.cellular;

import com.sonymobile.smartnetworkengine.ext.util.Log;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;

/**
 * Calculate throughput and judge the timing to upload data to IDD.
 */
public class ThroughputChecker {

    private static final String TAG = ThroughputChecker.class.getSimpleName();

    /** A queue to hold all samples whose length is limited to specified period */
    private final Queue<Long> mSamples = new LinkedList<>();
    /** A queue to hold samples which are over threshold */
    private final List<Long> mThreshOverSamples = new ArrayList<>();

    private final int mCheckPeriodNum;
    private final int mThreshOverNum;
    private final int mThresholdBytes;

    public ThroughputChecker(int checkPeriodNum, int threshOverNum, int thresholdBytes) {
        mCheckPeriodNum = checkPeriodNum;
        mThreshOverNum = threshOverNum;
        mThresholdBytes = thresholdBytes;
    }

    /** Reset internal data */
    public void reset() {
        mSamples.clear();
        mThreshOverSamples.clear();
    }

    /**
     * Add a sample data and return if internal data fulfills criteria.
     */
    public boolean addSample(long trafficBytes) {
        // When queue reaches to max length, remove oldest data.
        if (mSamples.size() == mCheckPeriodNum) {
            Long sample = mSamples.poll();
            mThreshOverSamples.remove(sample);
        }

        mSamples.add(trafficBytes);
        if (trafficBytes >= mThresholdBytes) {
            mThreshOverSamples.add(trafficBytes);
        }

        Log.v(TAG, "ThreshOverSamples=" + mThreshOverSamples.size());
        return (mSamples.size() == mCheckPeriodNum && mThreshOverSamples.size() >= mThreshOverNum);
    }
}
