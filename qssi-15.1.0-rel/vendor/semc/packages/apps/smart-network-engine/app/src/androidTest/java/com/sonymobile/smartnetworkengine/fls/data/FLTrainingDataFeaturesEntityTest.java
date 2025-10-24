/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.data;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import org.junit.Test;
import org.junit.runner.RunWith;

/**
 * Verify {@link FLTrainingDataFeaturesEntity} implementation.
 */
@RunWith(AndroidJUnit4.class)
public class FLTrainingDataFeaturesEntityTest {

    @Test
    public void testGetAvailableFeatures() {
        FLTrainingDataFeaturesEntity entity = new FLTrainingDataFeaturesEntity();
        entity.feature1 = 0.1f;
        entity.feature2 = 0.2f;
        entity.feature3 = 0.3f;

        // Action
        float[] features = entity.getAvailableFeatures();

        // Check
        assertEquals(entity.feature1, features[0], 0);
        assertEquals(entity.feature2, features[1], 0);
        assertEquals(entity.feature3, features[2], 0);
        assertNull(entity.feature4);
        assertNull(entity.feature5);
        assertNull(entity.feature6);
        assertNull(entity.feature7);
        assertNull(entity.feature8);
        assertNull(entity.feature9);
        assertNull(entity.feature10);
        assertNull(entity.feature11);
        assertNull(entity.feature12);
        assertNull(entity.feature13);
        assertNull(entity.feature14);
        assertNull(entity.feature15);
    }

    @Test
    public void testSetAvailableFeatures() {
        float[] features = new float[]{0.1f, 0.2f, 0.3f};

        // Action
        FLTrainingDataFeaturesEntity entity = new FLTrainingDataFeaturesEntity(features);

        // Check
        assertArrayEquals(features, entity.getAvailableFeatures(), 0);
        assertEquals(features[0], entity.feature1, 0);
        assertEquals(features[1], entity.feature2, 0);
        assertEquals(features[2], entity.feature3, 0);
        assertNull(entity.feature4);
        assertNull(entity.feature5);
        assertNull(entity.feature6);
        assertNull(entity.feature7);
        assertNull(entity.feature8);
        assertNull(entity.feature9);
        assertNull(entity.feature10);
        assertNull(entity.feature11);
        assertNull(entity.feature12);
        assertNull(entity.feature13);
        assertNull(entity.feature14);
        assertNull(entity.feature15);
    }
}
