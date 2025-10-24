/*
 * Copyright (C) 2019 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.connected.logger;

import static com.sonymobile.smartnetworkengine.connected.logger.MovingDetector.EXTENSION_PERIOD;
import static com.sonymobile.smartnetworkengine.connected.logger.MovingDetector.MOVE_ACCELERATION_THRESHOLD;
import static com.sonymobile.smartnetworkengine.connected.logger.MovingDetector.REQUIRED_PERIOD;

import static junit.framework.TestCase.assertFalse;
import static junit.framework.TestCase.assertTrue;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

@RunWith(AndroidJUnit4.class)
public class MovingDetectorTest {

    private static final float LOW_ACCEL = MOVE_ACCELERATION_THRESHOLD - 0.1f;
    private static final float HIGH_ACCEL = MOVE_ACCELERATION_THRESHOLD;

    private MovingDetector mDetector;

    @Before
    public void setUp() {
        mDetector = new MovingDetector();
    }

    @Test
    public void testMoving_consecutiveHighAcceleration() {
        // Action and Check
        for (int i = 0; i < REQUIRED_PERIOD - 1; i++) {
            assertFalse(mDetector.update(HIGH_ACCEL));
        }
        assertTrue(mDetector.update(HIGH_ACCEL));
    }

    @Test
    public void testNotMoving_nonConsecutiveHighAcceleration() {
        // Action and Check
        for (int i = 0; i < REQUIRED_PERIOD - 1; i++) {
            assertFalse(mDetector.update(HIGH_ACCEL));
        }
        assertFalse(mDetector.update(LOW_ACCEL));
    }

    @Test
    public void testNotMoving_fluctuatingAccelerationAroundThreshold() {
        // Action and Check
        int someLoop = 3;
        for (int i = 0; i < REQUIRED_PERIOD * someLoop; i++) {
            float accel = (i % 2 == 0) ? HIGH_ACCEL : LOW_ACCEL;
            assertFalse(mDetector.update(accel));
        }
    }

    @Test
    public void testExtension_validAndExpired() {
        // Change to moving state.
        for (int i = 0; i < REQUIRED_PERIOD; i++) {
            mDetector.update(HIGH_ACCEL);
        }

        // Action and Check
        for (int i = 0; i < EXTENSION_PERIOD; i++) {
            assertTrue(mDetector.update(LOW_ACCEL));
        }
        assertFalse(mDetector.update(LOW_ACCEL));
    }

    @Test
    public void testExtension_resumedWithHighAcceleration() {
        // Change to moving state.
        for (int i = 0; i < REQUIRED_PERIOD; i++) {
            mDetector.update(HIGH_ACCEL);
        }
        // Use up extension.
        for (int i = 0; i < EXTENSION_PERIOD; i++) {
            mDetector.update(LOW_ACCEL);
        }

        // Action and Check
        assertTrue(mDetector.update(HIGH_ACCEL));
        for (int i = 0; i < EXTENSION_PERIOD; i++) {
            assertTrue(mDetector.update(LOW_ACCEL));
        }
        assertFalse(mDetector.update(LOW_ACCEL));
    }

    @Test
    public void testExtension_extendedWithFluctuatingAccelerationAroundThreshold() {
        // Change to moving state.
        for (int i = 0; i < REQUIRED_PERIOD; i++) {
            mDetector.update(HIGH_ACCEL);
        }

        // Action and Check
        int someLoop = 3;
        for (int i = 0; i < EXTENSION_PERIOD * someLoop; i++) {
            float accel = (i % 2 == 0) ? HIGH_ACCEL : LOW_ACCEL;
            assertTrue(mDetector.update(accel));
        }
    }

    @Test
    public void testReset_valid() {
        // Change to moving state.
        for (int i = 0; i < REQUIRED_PERIOD; i++) {
            mDetector.update(HIGH_ACCEL);
        }

        // Action
        mDetector.reset();

        // Check
        assertFalse(mDetector.update(HIGH_ACCEL));
    }
}
