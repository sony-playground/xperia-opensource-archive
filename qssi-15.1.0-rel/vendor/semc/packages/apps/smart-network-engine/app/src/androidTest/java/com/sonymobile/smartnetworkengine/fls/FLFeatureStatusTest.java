/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls;

import static com.sonymobile.smartnetworkengine.fls.FLSystemManager.FEATURE_CONNECTED;
import static com.sonymobile.smartnetworkengine.fls.FLSystemManager.FEATURE_ENTRY;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotEquals;
import static org.junit.Assert.assertTrue;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sonymobile.smartnetworkengine.fls.FLSystemManager.FLFeatureStatus;

import org.junit.Test;
import org.junit.runner.RunWith;

@RunWith(AndroidJUnit4.class)
public class FLFeatureStatusTest {

    @Test
    public void testBasic() {
        // Action
        FLFeatureStatus featureStatus = FLFeatureStatus.builder()
                .feature(FEATURE_ENTRY)
                .build();

        // Check
        assertFalse(featureStatus.isPredictionEnabled());

        // Action
        featureStatus = FLFeatureStatus.builder()
                .feature(FEATURE_ENTRY)
                .predictionEnabled(true)
                .dataCollectionSession(true)
                .build();

        // Check
        assertTrue(featureStatus.isPredictionEnabled());
        assertTrue(featureStatus.isDataCollectionSession());
    }

    @Test
    public void testEquals() {
        // Prepare
        FLFeatureStatus featureStatus = FLFeatureStatus.builder()
                .feature(FEATURE_ENTRY)
                .build();
        FLFeatureStatus featureStatus2 = FLFeatureStatus.builder()
                .feature(FEATURE_ENTRY)
                .build();

        // Action and Check
        assertEquals(featureStatus, featureStatus);
        assertEquals(featureStatus, featureStatus2);

        // Prepare
        featureStatus2 = FLFeatureStatus.builder()
                .feature(FEATURE_ENTRY)
                .predictionEnabled(true)
                .build();

        // Action and Check
        assertNotEquals(featureStatus, featureStatus2);

        // Prepare
        featureStatus2 = FLFeatureStatus.builder()
                .feature(FEATURE_ENTRY)
                .dataCollectionSession(true)
                .build();

        // Action and Check
        assertNotEquals(featureStatus, featureStatus2);

        // Prepare
        featureStatus2 = FLFeatureStatus.builder()
                .feature(FEATURE_CONNECTED)
                .build();

        // Action and Check
        assertNotEquals(featureStatus, featureStatus2);
    }
}
