/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.data;

import static com.sonymobile.smartnetworkengine.Constants.FLS_APP_ID_CONNECTED;
import static com.sonymobile.smartnetworkengine.Constants.FLS_APP_ID_INT_NUM_MAP;
import static com.sonymobile.smartnetworkengine.fls.data.FLTrainingDataAccessor.DataSet;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;

import android.content.Context;

import androidx.room.Room;
import androidx.test.core.app.ApplicationProvider;
import androidx.test.ext.junit.runners.AndroidJUnit4;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.MockitoAnnotations;

import java.util.List;
import java.util.Objects;
import java.util.concurrent.TimeUnit;
import java.util.stream.Stream;

/**
 * Verify {@link FLTrainingDataAccessor} implementation.
 */
@RunWith(AndroidJUnit4.class)
public class FLTrainingDataAccessorTest {

    private FLTrainingDataAccessor mAccessor;

    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);
        Context context = ApplicationProvider.getApplicationContext();
        FLTrainingDatabase trainingDatabase = Room.inMemoryDatabaseBuilder(context,
                FLTrainingDatabase.class).build();
        FLTrainingDataDao trainingDataDao = trainingDatabase.trainingDataDao();
        mAccessor = new FLTrainingDataAccessor(trainingDatabase, trainingDataDao);
    }

    @Test
    public void testToDataSet() {
        // Build a session entity
        FLTrainingDataSessionEntity sessionEntity = new FLTrainingDataSessionEntity();
        sessionEntity.appIdNum = 1;
        sessionEntity.groupLabel = "label";
        sessionEntity.timestamp = 12345;
        sessionEntity.label = 0.1f;
        sessionEntity.test = true;
        // Build features entities
        FLTrainingDataFeaturesEntity featuresEntity1 = new FLTrainingDataFeaturesEntity(
                new float[]{0.1f, 0.2f, 0.3f});
        FLTrainingDataFeaturesEntity featuresEntity2 = new FLTrainingDataFeaturesEntity(
                new float[]{1.1f, 1.2f, 1.3f});
        // Build a training data from the entities above
        FLTrainingData trainingData = new FLTrainingData();
        trainingData.sessionEntity = sessionEntity;
        trainingData.featuresEntities = List.of(featuresEntity1, featuresEntity2);

        // Action
        DataSet dataSet = mAccessor.toDataSet(trainingData);

        // Check
        assertEquals(sessionEntity.groupLabel, dataSet.getGroupLabel());
        assertEquals(2, dataSet.getFeatures().length);
        assertArrayEquals(featuresEntity1.getAvailableFeatures(), dataSet.getFeatures()[0], 0);
        assertArrayEquals(featuresEntity2.getAvailableFeatures(), dataSet.getFeatures()[1], 0);
        assertEquals(sessionEntity.label, dataSet.getLabel(), 0);
    }

    @Test
    public void testAdd() {
        // Prepare
        String appId = FLS_APP_ID_CONNECTED;
        DataSet dataSet = DataSet.builder().groupLabel("BSSID-1").features(
                        new float[][]{{0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f},
                                {1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f}})
                .label(1.0f)
                .build();
        long timestamp = System.currentTimeMillis();
        // Action
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TEST);

        // Check
        Stream<DataSet> dataStream = mAccessor.get(appId, FLTrainingDataAccessor.DataType.TEST);
        DataSet data = dataStream.findFirst().get();

        String groupLabel = data.getGroupLabel();
        float label = data.getLabel();
        float[][] features = data.getFeatures();

        // Check
        assertEquals("BSSID-1", groupLabel);
        assertEquals(1.0f, label, 0);
        assertEquals(1.0f, features[0][9], 0);
        assertEquals(2.0f, features[1][9], 0);
    }

    @Test
    public void testGet() {
        String appId = FLS_APP_ID_CONNECTED;
        DataSet dataSet = DataSet.builder().groupLabel("BSSID-1").features(
                        new float[][]{{0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f},
                                {1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f}})
                .label(1.0f)
                .build();
        long timestamp = System.currentTimeMillis();

        // Action
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TEST);
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TRAINING);
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TRAINING);

        // Check
        Stream<DataSet> testData = mAccessor.get(appId, FLTrainingDataAccessor.DataType.TEST);
        assertEquals(1, testData.count());

        Stream<DataSet> trainData = mAccessor.get(appId, FLTrainingDataAccessor.DataType.TRAINING);
        assertEquals(2, trainData.count());

        Stream<DataSet> allData = mAccessor.get(appId,
                FLTrainingDataAccessor.DataType.TRAINING_AND_TEST);
        assertEquals(3, allData.count());
    }

    @Test
    public void testCount() {
        // Prepare
        String appId = FLS_APP_ID_CONNECTED;
        DataSet dataSet = DataSet.builder().groupLabel("BSSID-1").features(
                        new float[][]{{0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f},
                                {1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f}})
                .label(1.0f)
                .build();
        long timestamp = System.currentTimeMillis();

        // Action
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TEST);
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TRAINING);
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TRAINING);

        //Check
        assertEquals(1, mAccessor.count(appId, FLTrainingDataAccessor.DataType.TEST));
        assertEquals(2, mAccessor.count(appId, FLTrainingDataAccessor.DataType.TRAINING));
        assertEquals(3, mAccessor.count(appId, FLTrainingDataAccessor.DataType.TRAINING_AND_TEST));
    }

    @Test
    public void testCountForPositiveLabel() {
        // Prepare
        String appId = FLS_APP_ID_CONNECTED;
        DataSet.Builder dataSetBuilder = DataSet.builder().groupLabel("BSSID-1").features(
                new float[][]{{0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f},
                        {1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f}});
        long timestamp = System.currentTimeMillis();

        // Action
        DataSet dataSet = dataSetBuilder.label(0.0f).build();
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TRAINING);
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TEST);
        dataSet = dataSetBuilder.label(0.5f).build();
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TRAINING);
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TEST);
        dataSet = dataSetBuilder.label(1.0f).build();
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TRAINING);
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TEST);

        // Check
        assertEquals(6, mAccessor.count(appId, 0.0f));
        assertEquals(4, mAccessor.count(appId, 0.49f));
        assertEquals(4, mAccessor.count(appId, 0.5f));
        assertEquals(2, mAccessor.count(appId, 0.51f));
        assertEquals(2, mAccessor.count(appId, 1.0f));
    }

    @Test
    public void testGetAverageOfLabel() {
        // Prepare
        String appId = FLS_APP_ID_CONNECTED;
        DataSet.Builder dataSetBuilder = DataSet.builder().groupLabel("BSSID-1").features(
                new float[][]{{0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f},
                        {1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f}});
        long timestamp = System.currentTimeMillis();

        // Action
        DataSet dataSet = dataSetBuilder.label(0.0f).build();
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TEST);
        dataSet = dataSetBuilder.label(0.2f).build();
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TRAINING);
        dataSet = dataSetBuilder.label(0.4f).build();
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TEST);
        dataSet = dataSetBuilder.label(0.6f).build();
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TRAINING);
        dataSet = dataSetBuilder.label(0.8f).build();
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TEST);
        dataSet = dataSetBuilder.label(1.0f).build();
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TRAINING);

        // Check
        assertEquals(0.6, mAccessor.getAverageOfLabel(appId), 1e-6);
    }

    @Test
    public void testSetDataRetentionPolicy() {
        // Prepare
        String appId = FLS_APP_ID_CONNECTED;
        int appIdNum = Objects.requireNonNull(FLS_APP_ID_INT_NUM_MAP.get(appId));

        // Action
        mAccessor.setDataRetentionPolicy(appId, 100, 10, 5);

        // Check
        assertEquals(TimeUnit.DAYS.toMillis(5),
                mAccessor.mDataRetentionPeriodMap.get(appIdNum).longValue());
        assertEquals(100, mAccessor.mMaxNumOfDataMap.get(appIdNum).intValue());
        assertEquals(10, mAccessor.mMaxNumOfDataPerGroupLabelMap.get(appIdNum).intValue());
    }

    @Test
    public void testDeleteDataIfRetentionPeriodExpired() {
        // Prepare
        String appId = FLS_APP_ID_CONNECTED;
        DataSet dataSet = DataSet.builder().groupLabel("BSSID-1").features(
                        new float[][]{{0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f},
                                {1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f}})
                .label(1.0f)
                .build();
        long timestamp = System.currentTimeMillis();
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TEST);

        timestamp -= TimeUnit.DAYS.toMillis(10);
        mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TEST);

        // Action
        mAccessor.setDataRetentionPolicy(appId, 100, 10, 5);

        // Check
        assertEquals(1, mAccessor.get(appId, FLTrainingDataAccessor.DataType.TEST).count());
    }

    @Test
    public void testDeleteDataIfExceedsGroupLabelMaxNum() {
        // Prepare
        String appId = FLS_APP_ID_CONNECTED;
        DataSet dataSet = DataSet.builder().groupLabel("BSSID-1").features(
                        new float[][]{{0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f},
                                {1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f}})
                .label(1.0f)
                .build();
        long timestamp = System.currentTimeMillis();
        mAccessor.setDataRetentionPolicy(appId, 100, 5, 5);


        // Action
        for (int i = 0; i < 10; i++) {
            mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TEST);
        }

        for (int i = 0; i < 3; i++) {
            dataSet = DataSet.builder().groupLabel("BSSID-2").features(
                            new float[][]{{0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f,
                                    1.0f},
                                    {1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f}})
                    .label(1.0f)
                    .build();
            mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TEST);
        }

        // Check
        assertEquals(5 + 3,
                mAccessor.count(appId, FLTrainingDataAccessor.DataType.TRAINING_AND_TEST));
    }

    @Test
    public void testDeleteDataIfExceedsMaxNum() {
        // Prepare
        String appId = FLS_APP_ID_CONNECTED;
        DataSet dataSet = DataSet.builder().groupLabel("BSSID-1").features(
                        new float[][]{{0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f},
                                {1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f}})
                .label(1.0f)
                .build();
        long timestamp = System.currentTimeMillis();
        mAccessor.setDataRetentionPolicy(appId, 10, 10, 5);

        for (int i = 0; i < 10; i++) {
            mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TEST);
        }

        for (int i = 0; i < 10; i++) {
            dataSet = DataSet.builder().groupLabel("BSSID-2").features(
                            new float[][]{{0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f,
                                    1.0f},
                                    {1.1f, 1.2f, 1.3f, 1.4f, 1.5f, 1.6f, 1.7f, 1.8f, 1.9f, 2.0f}})
                    .label(1.0f)
                    .build();
            mAccessor.add(appId, dataSet, timestamp, FLTrainingDataAccessor.DataType.TEST);
        }

        // Check
        assertEquals(10,
                mAccessor.count(appId, FLTrainingDataAccessor.DataType.TRAINING_AND_TEST));
    }
}
