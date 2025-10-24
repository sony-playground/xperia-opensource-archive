/*
 *  Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.data;

import static org.junit.Assert.assertEquals;

import android.content.Context;

import androidx.room.Room;
import androidx.test.core.app.ApplicationProvider;
import androidx.test.ext.junit.runners.AndroidJUnit4;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@RunWith(AndroidJUnit4.class)
public class FLTrainingDataDaoTest {
    private FLTrainingDataDao mTrainingDataDao;

    @Before
    public void setUp() {
        Context context = ApplicationProvider.getApplicationContext();
        FLTrainingDatabase trainingDatabase = Room.inMemoryDatabaseBuilder(context,
                FLTrainingDatabase.class).build();
        mTrainingDataDao = trainingDatabase.trainingDataDao();
    }

    @Test
    public void testGetData() {
        // Prepare
        long timeStamp = 1;
        insertTestData(1, "BSSID-1", timeStamp, 30, false, 0.0f);
        insertTestData(2, "BSSID-1", timeStamp, 30, false, 0.0f);
        insertTestData(1, "BSSID-1", timeStamp, 20, true, 0.0f);
        timeStamp += 100;

        insertTestData(1, "BSSID-2", timeStamp, 30, false, 0.0f);
        insertTestData(1, "BSSID-2", timeStamp, 20, true, 0.0f);
        timeStamp += 100;

        insertTestData(1, "BSSID-3", timeStamp, 30, false, 0.0f);
        insertTestData(1, "BSSID-3", timeStamp, 20, true, 0.0f);

        // Action & Check
        List<FLTrainingData> trainData = mTrainingDataDao.getData(1, false);
        List<FLTrainingData> anotherAppIdData = mTrainingDataDao.getData(2, false);
        assertEquals(90, trainData.size());
        assertEquals(30, anotherAppIdData.size());

        for (FLTrainingData trainingData : trainData) {
            if (trainingData.sessionEntity.timestamp > 200) {
                assertEquals("BSSID-3", trainingData.sessionEntity.groupLabel);
                assertEquals(0.1f, trainingData.featuresEntities.get(0).feature1, 0);
                assertEquals(0.2f, trainingData.featuresEntities.get(0).feature2, 0);
                assertEquals(0.3f, trainingData.featuresEntities.get(0).feature3, 0);
            } else if (trainingData.sessionEntity.timestamp > 100) {
                assertEquals("BSSID-2", trainingData.sessionEntity.groupLabel);
            } else {
                assertEquals("BSSID-1", trainingData.sessionEntity.groupLabel);
            }
        }

        // Action & Check
        List<FLTrainingData> allData = mTrainingDataDao.getData(1);
        assertEquals(150, allData.size());
    }

    @Test
    public void testGetNumOfData() {
        // Prepare
        long timeStamp = 1;
        insertTestData(1, "BSSID-1", timeStamp, 30, false, 0.0f);
        insertTestData(1, "BSSID-1", timeStamp, 20, true, 0.0f);
        timeStamp += 100;

        insertTestData(1, "BSSID-2", timeStamp, 30, false, 0.0f);
        insertTestData(1, "BSSID-2", timeStamp, 20, true, 0.0f);

        timeStamp += 100;

        insertTestData(1, "BSSID-3", timeStamp, 30, false, 0.0f);
        insertTestData(1, "BSSID-3", timeStamp, 20, true, 0.0f);

        // Action
        int allDataSize = mTrainingDataDao.getNumOfData(1);
        int trainDataSize = mTrainingDataDao.getNumOfData(1, false);

        // Check
        assertEquals(150, allDataSize);
        assertEquals(90, trainDataSize);
    }

    @Test
    public void testDeleteOldData() {
        // Prepare
        long timeStamp = 1;
        insertTestData(1, "BSSID-1", timeStamp, 30, false, 0.0f);
        insertTestData(2, "BSSID-1", timeStamp, 30, false, 0.0f);
        timeStamp += 100;

        insertTestData(1, "BSSID-2", timeStamp, 30, false, 0.0f);
        insertTestData(2, "BSSID-2", timeStamp, 30, false, 0.0f);

        timeStamp += 100;

        insertTestData(1, "BSSID-3", timeStamp, 30, false, 0.0f);

        // Action
        mTrainingDataDao.deleteOldData(1, 200);

        // Check
        List<FLTrainingData> deletedData = mTrainingDataDao.getData(1);
        List<FLTrainingData> appId2Data = mTrainingDataDao.getData(2);
        assertEquals(90 - 30 - 30, deletedData.size());
        assertEquals("BSSID-3", deletedData.get(0).sessionEntity.groupLabel);
        assertEquals(201, deletedData.get(0).sessionEntity.timestamp);
        assertEquals(1, deletedData.get(0).sessionEntity.appIdNum);
        assertEquals(30 + 30, appId2Data.size());
    }

    @Test
    public void testDeleteData() {
        // Prepare
        long timeStamp = 1;
        insertTestData(2, "BSSID-1", timeStamp, 20, false, 0.0f);
        insertTestData(1, "BSSID-1", timeStamp, 30, false, 0.0f);
        timeStamp += 100;

        insertTestData(1, "BSSID-2", timeStamp, 30, false, 0.0f);
        timeStamp += 100;

        insertTestData(1, "BSSID-3", timeStamp, 30, false, 0.0f);

        // Action
        mTrainingDataDao.deleteData(1, 10);

        // Check
        List<FLTrainingData> deletedData = mTrainingDataDao.getData(1);
        assertEquals((30 - 10) + 30 + 30, deletedData.size());

    }

    @Test
    public void testDeleteDataPerGroupLabel() {
        // Prepare
        long timeStamp = 1;
        insertTestData(1, "BSSID-2", timeStamp, 40, false, 0.0f);
        insertTestData(1, "BSSID-1", timeStamp, 30, false, 0.0f);

        timeStamp += 100;

        insertTestData(2, "BSSID-2", timeStamp, 20, false, 0.0f);
        insertTestData(1, "BSSID-2", timeStamp, 30, false, 0.0f);

        timeStamp += 100;
        insertTestData(1, "BSSID-3", timeStamp, 30, false, 0.0f);

        // Action
        mTrainingDataDao.deleteData(1, "BSSID-1", 20);

        // Check
        List<FLTrainingData> deletedData = mTrainingDataDao.getData(1);
        assertEquals((30 - 20) + (40 + 30) + 30, deletedData.size());
        assertEquals("BSSID-2", deletedData.get(39).sessionEntity.groupLabel);
        assertEquals("BSSID-1", deletedData.get(40).sessionEntity.groupLabel);
        assertEquals(1, deletedData.get(40).sessionEntity.appIdNum);
        assertEquals(21, deletedData.get(40).sessionEntity.timestamp);
        assertEquals("BSSID-2", deletedData.get(50).sessionEntity.groupLabel);
    }

    @Test
    public void testGetGroupLabelList() {
        // Prepare
        long timeStamp = 1;
        insertTestData(1, "BSSID-1", timeStamp, 30, false, 0.0f);
        insertTestData(1, "BSSID-1", timeStamp, 30, false, 0.0f);
        insertTestData(1, "BSSID-2", timeStamp, 30, false, 0.0f);
        insertTestData(1, "BSSID-3", timeStamp, 30, false, 0.0f);
        insertTestData(2, "BSSID-4", timeStamp, 30, false, 0.0f);

        // Action
        List<String> groupLabelList = mTrainingDataDao.getGroupLabelList(1);

        // Check
        assertEquals(Arrays.asList("BSSID-1", "BSSID-2", "BSSID-3"), groupLabelList);
    }

    @Test
    public void testGetNumOfDataForPositiveLabel() {
        // Prepare
        long timeStamp = 1;
        insertTestData(1, "BSSID-1", timeStamp, 80, false, 0.0f);
        insertTestData(1, "BSSID-2", timeStamp, 70, false, 0.5f);
        insertTestData(1, "BSSID-3", timeStamp, 60, false, 1.0f);
        insertTestData(1, "BSSID-4", timeStamp, 50, true, 0.0f);
        insertTestData(1, "BSSID-5", timeStamp, 40, true, 0.5f);
        insertTestData(1, "BSSID-6", timeStamp, 30, true, 1.0f);
        insertTestData(2, "BSSID-7", timeStamp, 20, false, 0.5f);
        insertTestData(2, "BSSID-8", timeStamp, 10, true, 0.5f);

        // Action & Check
        assertEquals(330, mTrainingDataDao.getNumOfData(1, 0.0f));
        assertEquals(200, mTrainingDataDao.getNumOfData(1, 0.49f));
        assertEquals(200, mTrainingDataDao.getNumOfData(1, 0.5f));
        assertEquals(90, mTrainingDataDao.getNumOfData(1, 0.51f));
        assertEquals(90, mTrainingDataDao.getNumOfData(1, 1.0f));
    }

    @Test
    public void testGetAverageOfLabel() {
        // Prepare
        long timeStamp = 1;
        insertTestData(1, "BSSID-1", timeStamp, 10, true, 0.0f);
        insertTestData(1, "BSSID-2", timeStamp, 10, false, 0.2f);
        insertTestData(1, "BSSID-3", timeStamp, 10, true, 0.4f);
        insertTestData(1, "BSSID-3", timeStamp, 10, false, 0.6f);
        insertTestData(1, "BSSID-4", timeStamp, 10, true, 0.8f);
        insertTestData(1, "BSSID-5", timeStamp, 10, false, 1.0f);
        insertTestData(2, "BSSID-6", timeStamp, 10, false, 1.0f);

        // Action
        float avg = mTrainingDataDao.getAverageOfLabel(1);

        // Check
        assertEquals(0.6, avg, 1e-6);
    }

    private void insertTestData(int appIdNum, String bssid, long timestamp, int num, boolean test,
            float label) {
        for (int i = 0; i < num; i++) {
            FLTrainingDataSessionEntity trainingOneLineData = new FLTrainingDataSessionEntity();
            trainingOneLineData.appIdNum = appIdNum;
            trainingOneLineData.groupLabel = bssid;
            trainingOneLineData.timestamp = timestamp + i;
            trainingOneLineData.label = label;
            trainingOneLineData.test = test;
            List<FLTrainingDataFeaturesEntity> trainingTimeSeriesDataList = new ArrayList<>();
            for (int j = 0; j < num; j++) {
                FLTrainingDataFeaturesEntity trainingTimeSeriesData =
                        new FLTrainingDataFeaturesEntity();
                trainingTimeSeriesData.feature1 = 0.1f;
                trainingTimeSeriesData.feature2 = 0.2f;
                trainingTimeSeriesData.feature3 = 0.3f;
                trainingTimeSeriesData.feature4 = 0.4f;
                trainingTimeSeriesData.feature5 = 0.5f;
                trainingTimeSeriesData.feature6 = 0.6f;
                trainingTimeSeriesData.feature7 = 0.7f;
                trainingTimeSeriesData.feature8 = 0.8f;
                trainingTimeSeriesData.feature9 = 0.9f;
                trainingTimeSeriesData.feature10 = 1.0f;
                trainingTimeSeriesData.feature11 = 1.1f;
                trainingTimeSeriesData.feature12 = 1.2f;
                trainingTimeSeriesData.feature13 = 1.3f;
                trainingTimeSeriesData.feature14 = 1.4f;
                trainingTimeSeriesData.feature15 = 1.5f;

                trainingTimeSeriesDataList.add(trainingTimeSeriesData);
            }
            mTrainingDataDao.addData(trainingOneLineData, trainingTimeSeriesDataList);
        }
    }
}
