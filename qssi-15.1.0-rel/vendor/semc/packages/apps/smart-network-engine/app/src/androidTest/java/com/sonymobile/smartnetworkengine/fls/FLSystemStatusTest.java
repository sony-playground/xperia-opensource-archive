/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls;

import static com.sonymobile.smartnetworkengine.Constants.FLS_APP_ID_LIST;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotEquals;
import static org.junit.Assert.assertTrue;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sonymobile.smartnetworkengine.fls.FLSystemManager.FLFeatureStatus;
import com.sonymobile.smartnetworkengine.fls.FLSystemManager.FLSystemStatus;

import org.junit.Test;
import org.junit.runner.RunWith;

import java.util.Map;
import java.util.stream.Collectors;

@RunWith(AndroidJUnit4.class)
public class FLSystemStatusTest {

    @Test
    public void testBasic() {
        // Action
        FLSystemStatus systemStatus = FLSystemStatus.builder().build();

        // Check
        assertFalse(systemStatus.isSystemEnabled());
        FLS_APP_ID_LIST.forEach(
                appId -> assertFalse(systemStatus.getFeatureStatus(appId).isPredictionEnabled()));

        // Action
        Map<String, FLFeatureStatus> featureStatusMap = FLS_APP_ID_LIST.stream()
                .collect(Collectors.toMap(e -> e,
                        e -> FLFeatureStatus.builder()
                                .feature(e)
                                .predictionEnabled(true)
                                .build()));
        FLSystemStatus systemStatus2 = FLSystemStatus.builder()
                .systemEnabled(true)
                .featureStatusMap(featureStatusMap)
                .build();

        // Check
        assertTrue(systemStatus2.isSystemEnabled());
        FLS_APP_ID_LIST.forEach(
                appId -> assertTrue(systemStatus2.getFeatureStatus(appId).isPredictionEnabled()));
    }

    @Test
    public void testEquals() {
        // Prepare
        FLSystemStatus systemStatus = FLSystemStatus.builder().build();
        FLSystemStatus systemStatus2 = FLSystemStatus.builder().build();

        // Action and Check
        assertEquals(systemStatus, systemStatus);
        assertEquals(systemStatus, systemStatus2);

        // Prepare
        systemStatus2 = FLSystemStatus.builder()
                .systemEnabled(true)
                .build();

        // Action and Check
        assertNotEquals(systemStatus, systemStatus2);

        // Prepare
        Map<String, FLFeatureStatus> featureStatusMap = FLS_APP_ID_LIST.stream()
                .collect(Collectors.toMap(e -> e,
                        e -> FLFeatureStatus.builder()
                                .feature(e)
                                .predictionEnabled(true)
                                .build()));
        systemStatus2 = FLSystemStatus.builder()
                .featureStatusMap(featureStatusMap)
                .build();

        // Action and Check
        assertNotEquals(systemStatus, systemStatus2);

        // Prepare
        systemStatus = FLSystemStatus.builder()
                .featureStatusMap(featureStatusMap)
                .build();
        systemStatus2 = FLSystemStatus.builder()
                .featureStatusMap(featureStatusMap)
                .build();

        // Action and Check
        assertEquals(systemStatus, systemStatus2);
    }

    @Test
    public void testToBuilder() {
        // Prepare
        FLSystemStatus systemStatus = FLSystemStatus.builder().systemEnabled(true).build();
        FLSystemStatus systemStatus2 = systemStatus.toBuilder().build();

        // Action and Check
        assertEquals(systemStatus, systemStatus2);

        // Prepare
        systemStatus2 = systemStatus.toBuilder().systemEnabled(false).build();

        // Action and Check
        assertNotEquals(systemStatus, systemStatus2);

        // Prepare
        Map<String, FLFeatureStatus> featureStatusMap = FLS_APP_ID_LIST.stream()
                .collect(Collectors.toMap(e -> e,
                        e -> FLFeatureStatus.builder()
                                .feature(e)
                                .predictionEnabled(true)
                                .build()));
        systemStatus2 = systemStatus.toBuilder().featureStatusMap(featureStatusMap).build();

        // Action and Check
        assertNotEquals(systemStatus, systemStatus2);
    }
}
