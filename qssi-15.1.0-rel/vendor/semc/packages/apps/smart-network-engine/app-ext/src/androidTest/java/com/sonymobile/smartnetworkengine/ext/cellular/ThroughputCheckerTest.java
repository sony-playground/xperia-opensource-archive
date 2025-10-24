/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.ext.cellular;

import static com.sonymobile.smartnetworkengine.ext.Constants.THROUGHPUT_CHECK_OVER_THRESHOLD;
import static com.sonymobile.smartnetworkengine.ext.Constants.THROUGHPUT_CHECK_PERIOD;
import static com.sonymobile.smartnetworkengine.ext.Constants.THROUGHPUT_THRESHOLD;

import static junit.framework.TestCase.assertFalse;
import static junit.framework.TestCase.assertTrue;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

@RunWith(AndroidJUnit4.class)
public class ThroughputCheckerTest {

    private static final int HIGH = THROUGHPUT_THRESHOLD;
    private static final int LOW = THROUGHPUT_THRESHOLD - 1;

    private ThroughputChecker mChecker;

    @Before
    public void setUp() {
        mChecker = new ThroughputChecker(THROUGHPUT_CHECK_PERIOD,
                THROUGHPUT_CHECK_OVER_THRESHOLD, THROUGHPUT_THRESHOLD);
    }

    @Test
    public void testAddSample_sampleNumNotEnough() {
        // Action & Check
        for (int i = 0; i < THROUGHPUT_CHECK_PERIOD - 1; i++) {
            assertFalse(mChecker.addSample(HIGH));
        }
    }

    @Test
    public void testAddSample_validSampleNotEnough() {
        // Action & Check
        for (int i = 0; i < THROUGHPUT_CHECK_PERIOD; i++) {
            long value = (i < THROUGHPUT_CHECK_OVER_THRESHOLD - 1) ? HIGH : LOW;
            assertFalse(mChecker.addSample(value));
        }
    }

    @Test
    public void testAddSample() {
        // Prepare buffer with threshold-minus-one valid samples.
        for (int i = 0; i < THROUGHPUT_CHECK_PERIOD - 1; i++) {
            long value = (i < THROUGHPUT_CHECK_OVER_THRESHOLD - 1) ? HIGH : LOW;
            mChecker.addSample(value);
        }
        // Action & Check
        assertTrue(mChecker.addSample(HIGH));
    }

    @Test
    public void testAddSample_overPeriod() {
        // Fill throughput buffer with under-threshold values.
        for (int i = 0; i < THROUGHPUT_CHECK_PERIOD; i++) {
            mChecker.addSample(LOW);
        }
        // Action & Check
        for (int i = 0; i < THROUGHPUT_CHECK_OVER_THRESHOLD; i++) {
            if (i < THROUGHPUT_CHECK_OVER_THRESHOLD - 1) {
                assertFalse(mChecker.addSample(HIGH));
            } else {
                assertTrue(mChecker.addSample(HIGH));
            }
        }
    }

    @Test
    public void testAddSample_fluctuatingThroughput() {
        // Fill throughput buffer.
        for (int i = 0; i < THROUGHPUT_CHECK_PERIOD; i++) {
            mChecker.addSample(LOW);
        }
        // Add fluctuating samples whose valid samples are threshold minus one.
        for (int i = 0; i < (THROUGHPUT_CHECK_OVER_THRESHOLD - 1) * 2; i++) {
            long value = (i % 2 == 0) ? HIGH : LOW;
            mChecker.addSample(value);
        }
        // Action & Check
        assertTrue(mChecker.addSample(HIGH));
        assertTrue(mChecker.addSample(LOW));
    }

    @Test
    public void testReset() {
        // Fill throughput buffer.
        for (int i = 0; i < THROUGHPUT_CHECK_PERIOD; ++i) {
            mChecker.addSample(HIGH);
        }
        // Action
        mChecker.reset();
        // Check
        assertFalse(mChecker.addSample(HIGH));
    }
}