/*
 * Copyright (C) 2021 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.util;

import static junit.framework.TestCase.assertEquals;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import org.junit.Test;
import org.junit.runner.RunWith;

/**
 * Verify {@link ExponentialBackoff} implementation.
 */
@RunWith(AndroidJUnit4.class)
public class ExponentialBackoffTest {

    @Test
    public void testBackoff() {
        // Prepare (for FLS download case)
        ExponentialBackoff exponentialBackoff = new ExponentialBackoff(45, 10);

        // Action and Check
        //  0.75h/1.5h/3h/6h/12h/24h/2d/4d/8d/16d/1m/1m...
        assertEquals(45, exponentialBackoff.nextBackoff());
        assertEquals(90, exponentialBackoff.nextBackoff());    // 1
        assertEquals(180, exponentialBackoff.nextBackoff());   // 2
        assertEquals(360, exponentialBackoff.nextBackoff());   // 3
        assertEquals(720, exponentialBackoff.nextBackoff());   // 4
        assertEquals(1440, exponentialBackoff.nextBackoff());  // 5
        assertEquals(2880, exponentialBackoff.nextBackoff());  // 6
        assertEquals(5760, exponentialBackoff.nextBackoff());  // 7
        assertEquals(11520, exponentialBackoff.nextBackoff()); // 8
        assertEquals(23040, exponentialBackoff.nextBackoff()); // 9
        assertEquals(46080, exponentialBackoff.nextBackoff()); // 10
        assertEquals(46080, exponentialBackoff.nextBackoff()); // 10
        assertEquals(46080, exponentialBackoff.nextBackoff()); // 10

        // Prepare (for FLS upload case)
        exponentialBackoff = new ExponentialBackoff(45, 7);

        // Action and Check
        //  0.75h/1.5h/3h/6h/12h/24h/2d/4d/4d...
        assertEquals(45, exponentialBackoff.nextBackoff());
        assertEquals(90, exponentialBackoff.nextBackoff());   // 1
        assertEquals(180, exponentialBackoff.nextBackoff());  // 2
        assertEquals(360, exponentialBackoff.nextBackoff());  // 3
        assertEquals(720, exponentialBackoff.nextBackoff());  // 4
        assertEquals(1440, exponentialBackoff.nextBackoff()); // 5
        assertEquals(2880, exponentialBackoff.nextBackoff()); // 6
        assertEquals(5760, exponentialBackoff.nextBackoff()); // 7
        assertEquals(5760, exponentialBackoff.nextBackoff()); // 7
        assertEquals(5760, exponentialBackoff.nextBackoff()); // 7

    }

    @Test
    public void testGetBackoffCount() {
        ExponentialBackoff exponentialBackoff = new ExponentialBackoff(10, 3);

        // Action and Check
        assertEquals(0, exponentialBackoff.getBackoffCount());
        assertEquals(10, exponentialBackoff.nextBackoff());

        assertEquals(1, exponentialBackoff.getBackoffCount());
        assertEquals(20, exponentialBackoff.nextBackoff());

        assertEquals(2, exponentialBackoff.getBackoffCount());
        assertEquals(40, exponentialBackoff.nextBackoff());

        assertEquals(3, exponentialBackoff.getBackoffCount());
        assertEquals(80, exponentialBackoff.nextBackoff());

        assertEquals(3, exponentialBackoff.getBackoffCount());
        assertEquals(80, exponentialBackoff.nextBackoff());
    }

    @Test
    public void testSetBackoffCount() {
        ExponentialBackoff exponentialBackoff = new ExponentialBackoff(10, 3);

        // Action & Check
        exponentialBackoff.setBackoffCount(exponentialBackoff.getBackoffCount());
        assertEquals(10, exponentialBackoff.nextBackoff());

        exponentialBackoff.setBackoffCount(exponentialBackoff.getBackoffCount());
        assertEquals(20, exponentialBackoff.nextBackoff());

        exponentialBackoff.setBackoffCount(10);
        assertEquals(3, exponentialBackoff.getBackoffCount());
        assertEquals(80, exponentialBackoff.nextBackoff());
    }
}
