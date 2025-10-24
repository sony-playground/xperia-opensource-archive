/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls;

import static org.junit.Assert.assertEquals;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import org.junit.Test;
import org.junit.runner.RunWith;

import java.util.Arrays;
import java.util.Collections;

@RunWith(AndroidJUnit4.class)
public class FLPreferenceAccessorTest {

    @Test
    public void testCreatePendingFLTaskIndexListString() {
        // Action
        String str = FLPreferenceAccessor.toCommaSeparatedString(Arrays.asList(0, 1, 2));

        // Check
        assertEquals("0,1,2", str);

        // Action
        str = FLPreferenceAccessor.toCommaSeparatedString(Collections.singletonList(2));

        // Check
        assertEquals("2", str);

        // Action
        str = FLPreferenceAccessor.toCommaSeparatedString(Collections.emptyList());

        // Check
        assertEquals("", str);
    }
}
