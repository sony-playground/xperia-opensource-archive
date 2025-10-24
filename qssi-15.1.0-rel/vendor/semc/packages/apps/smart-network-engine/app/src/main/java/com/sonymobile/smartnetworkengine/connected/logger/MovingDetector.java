/*
 * Copyright (C) 2019 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.connected.logger;

import androidx.annotation.VisibleForTesting;

/**
 * This class detects if device is moving or not using sensor acceleration data.
 * - If acceleration keeps over threshold for {@link #REQUIRED_PERIOD}, moving is detected.
 * - If acceleration keeps under threshold over {@link #EXTENSION_PERIOD}, detection is canceled.
 */
public class MovingDetector {
    @VisibleForTesting
    static final float MOVE_ACCELERATION_THRESHOLD = 1.0f;
    @VisibleForTesting
    static final int REQUIRED_PERIOD = 3;
    @VisibleForTesting
    static final int EXTENSION_PERIOD = 2;

    private int mConsecutiveThreshOver;
    private int mRemainedExtension;

    public void reset() {
        mConsecutiveThreshOver = 0;
        mRemainedExtension = 0;
    }

    /** Update internal state with acceleration and return if device is moving or not */
    public boolean update(float acceleration) {
        // update internal state
        if (acceleration >= MOVE_ACCELERATION_THRESHOLD) {
            mConsecutiveThreshOver++;
            // Reset extension either in following conditions.
            // (1) acceleration keeps over threshold for required period - i.e. moving criteria.
            // (2) an acceleration is over threshold during extension - rule to prolong extension.
            if (mConsecutiveThreshOver >= REQUIRED_PERIOD || mRemainedExtension > 0) {
                // Plus one is correct - if extension is say 2, 2 low accels after moving detection
                // is permitted and next 1 high accel will recover extension.
                mRemainedExtension = EXTENSION_PERIOD + 1;
            }
        } else {
            mConsecutiveThreshOver = 0;
            if (mRemainedExtension > 0) {
                mRemainedExtension--;
            }
        }

        return (mConsecutiveThreshOver >= REQUIRED_PERIOD || mRemainedExtension > 0);
    }
}
