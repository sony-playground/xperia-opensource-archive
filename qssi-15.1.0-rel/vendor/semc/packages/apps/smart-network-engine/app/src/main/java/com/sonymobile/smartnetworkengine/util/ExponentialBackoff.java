/*
 * Copyright (C) 2021 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.util;

/**
 * A simple implementation of exponential backoff.
 */
public class ExponentialBackoff {

    private static final int MULTIPLIER = 2;

    private final long mInitialInterval;

    private final int mMaximumBackoffs;

    private int mBackoffCount = 0;

    public ExponentialBackoff(long initialInterval, int maximumBackoffs) {
        mInitialInterval = initialInterval;
        mMaximumBackoffs = maximumBackoffs;
    }

    public long nextBackoff() {
        long backoff = mInitialInterval * (long) Math.pow(MULTIPLIER, mBackoffCount);
        if (mBackoffCount < mMaximumBackoffs) mBackoffCount++;
        return backoff;
    }

    public int getBackoffCount() {
        return mBackoffCount;
    }

    public void setBackoffCount(int backoffCount) {
        if (backoffCount > mMaximumBackoffs) backoffCount = mMaximumBackoffs;
        mBackoffCount = backoffCount;
    }
}
