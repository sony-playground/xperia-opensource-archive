/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.data;

import static com.sonymobile.smartnetworkengine.Constants.FLS_APP_ID_INT_NUM_MAP;

import android.content.Context;

import androidx.annotation.NonNull;
import androidx.annotation.VisibleForTesting;

import com.sonymobile.smartnetworkengine.util.Log;

import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.concurrent.TimeUnit;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * This class manages the training/evaluation data for the Federated-Learning system.
 */
public class FLTrainingDataAccessor {

    private static final String TAG = FLTrainingDataAccessor.class.getSimpleName();

    private final FLTrainingDatabase mTrainingDatabase;

    private final FLTrainingDataDao mTrainingDataDao;

    @VisibleForTesting
    /*private*/ final Map<Integer, Long> mDataRetentionPeriodMap = new HashMap<>();

    @VisibleForTesting
    /*private*/ final Map<Integer, Integer> mMaxNumOfDataMap = new HashMap<>();

    @VisibleForTesting
    /*private*/ final Map<Integer, Integer> mMaxNumOfDataPerGroupLabelMap = new HashMap<>();

    public FLTrainingDataAccessor(@NonNull Context context) {
        mTrainingDatabase = FLTrainingDatabase.getInstance(context);
        mTrainingDataDao = mTrainingDatabase.trainingDataDao();
    }

    // For testing
    FLTrainingDataAccessor(FLTrainingDatabase database, FLTrainingDataDao dao) {
        mTrainingDatabase = database;
        mTrainingDataDao = dao;
    }

    /**
     * Sets the data retention policy parameters for the training/evaluation data.
     */
    public void setDataRetentionPolicy(@NonNull String appId, int maxNumOfData,
            int maxNumOfDataPerGroupLabel, int maxPeriodDays) {
        int appIdNum = Objects.requireNonNull(FLS_APP_ID_INT_NUM_MAP.get(appId));
        mMaxNumOfDataMap.put(appIdNum, maxNumOfData);
        mMaxNumOfDataPerGroupLabelMap.put(appIdNum, maxNumOfDataPerGroupLabel);
        mDataRetentionPeriodMap.put(appIdNum, TimeUnit.DAYS.toMillis(maxPeriodDays));
        deleteDataIfNeeded(appIdNum);
    }

    /**
     * Adds the training/evaluation data to the database.
     */
    public void add(@NonNull String appId, @NonNull DataSet dataSet, long timestamp,
            @NonNull DataType dataType) {
        // Build a session entity
        FLTrainingDataSessionEntity sessionEntity = new FLTrainingDataSessionEntity();
        int appIdNum = Objects.requireNonNull(FLS_APP_ID_INT_NUM_MAP.get(appId));
        sessionEntity.appIdNum = appIdNum;
        sessionEntity.groupLabel = dataSet.getGroupLabel();
        sessionEntity.timestamp = timestamp;
        sessionEntity.label = dataSet.getLabel();
        if (dataType == DataType.TRAINING) {
            sessionEntity.test = false;
        } else if (dataType == DataType.TEST) {
            sessionEntity.test = true;
        } else {
            throw new IllegalStateException("Unexpected value: " + dataType);
        }
        // Build features entities
        List<FLTrainingDataFeaturesEntity> featuresEntities = Arrays.stream(dataSet.getFeatures())
                .map(FLTrainingDataFeaturesEntity::new)
                .collect(Collectors.toList());
        // Insert into the database
        mTrainingDataDao.addData(sessionEntity, featuresEntities);
        deleteDataIfNeeded(appIdNum);
    }

    /**
     * Loads the training/evaluation data from the database.
     */
    @NonNull
    public Stream<DataSet> get(@NonNull String appId, @NonNull DataType dataType) {
        int appIdNum = Objects.requireNonNull(FLS_APP_ID_INT_NUM_MAP.get(appId));
        List<FLTrainingData> trainingData;
        switch (dataType) {
            case TRAINING:
                trainingData = mTrainingDataDao.getData(appIdNum, false);
                break;
            case TEST:
                trainingData = mTrainingDataDao.getData(appIdNum, true);
                break;
            case TRAINING_AND_TEST:
                trainingData = mTrainingDataDao.getData(appIdNum);
                break;
            default:
                throw new IllegalStateException("Unexpected value: " + dataType);
        }
        // Create a DataSet stream from the list of the training data
        // (Note: consider lazy loading from the database if it takes a long time to load)
        return trainingData.stream().map(this::toDataSet);
    }

    /**
     * Returns the number of training/evaluation data in the database.
     */
    public int count(@NonNull String appId, @NonNull DataType dataType) {
        int appIdNum = Objects.requireNonNull(FLS_APP_ID_INT_NUM_MAP.get(appId));
        switch (dataType) {
            case TRAINING:
                return mTrainingDataDao.getNumOfData(appIdNum, false);
            case TEST:
                return mTrainingDataDao.getNumOfData(appIdNum, true);
            case TRAINING_AND_TEST:
                return mTrainingDataDao.getNumOfData(appIdNum);
            default:
                throw new IllegalStateException("Unexpected value: " + dataType);
        }
    }

    /**
     * Returns the number of data which has label above the threshold.
     */
    public int count(@NonNull String appId, float labelThreshold) {
        int appIdNum = Objects.requireNonNull(FLS_APP_ID_INT_NUM_MAP.get(appId));
        return mTrainingDataDao.getNumOfData(appIdNum, labelThreshold);
    }

    /**
     * Returns average label value (not 'label average') of training data for specific appId.
     */
    public float getAverageOfLabel(@NonNull String appId) {
        int appIdNum = Objects.requireNonNull(FLS_APP_ID_INT_NUM_MAP.get(appId));
        return mTrainingDataDao.getAverageOfLabel(appIdNum);
    }

    @VisibleForTesting
    DataSet toDataSet(FLTrainingData trainingData) {
        return DataSet.builder()
                .groupLabel(trainingData.sessionEntity.groupLabel)
                .features(trainingData.featuresEntities.stream()
                        .map(FLTrainingDataFeaturesEntity::getAvailableFeatures)
                        .toArray(float[][]::new))
                .label(trainingData.sessionEntity.label)
                .build();
    }

    private void deleteDataIfNeeded(int appIdNum) {
        deleteDataIfRetentionPeriodExpired(appIdNum);
        deleteDataIfExceedGroupLabelMaxNum(appIdNum);
        deleteDataIfExceedsMaxNum(appIdNum);
    }

    private void deleteDataIfRetentionPeriodExpired(int appIdNum) {
        Long period = mDataRetentionPeriodMap.get(appIdNum);
        if (period != null) {
            long thresholdTime = System.currentTimeMillis() - period;
            mTrainingDataDao.deleteOldData(appIdNum, thresholdTime);
        } else {
            Log.e(TAG, "Skip delete data because retention Period has not been set.");
        }
    }

    private void deleteDataIfExceedsMaxNum(int appIdNum) {
        Integer maxNumOfData = mMaxNumOfDataMap.get(appIdNum);
        if (maxNumOfData != null) {
            int dataCount = mTrainingDataDao.getNumOfData(appIdNum);
            if (dataCount > maxNumOfData) {
                mTrainingDataDao.deleteData(appIdNum, dataCount - maxNumOfData);
            }
        } else {
            Log.e(TAG, "Skip delete data because max num has not been set.");
        }
    }

    private void deleteDataIfExceedGroupLabelMaxNum(int appIdNum) {
        Integer maxNumOfGroupLabel = mMaxNumOfDataPerGroupLabelMap.get(appIdNum);
        if (maxNumOfGroupLabel != null) {
            List<String> allGroupLabel = mTrainingDataDao.getGroupLabelList(appIdNum);
            for (String groupLabel : allGroupLabel) {
                int count = mTrainingDataDao.getNumOfData(appIdNum, groupLabel);
                if (count > maxNumOfGroupLabel) {
                    mTrainingDataDao.deleteData(appIdNum, groupLabel, count - maxNumOfGroupLabel);
                }
            }
        } else {
            Log.e(TAG, "Skip delete data because max num of group label has not been set.");
        }
    }

    /**
     * The enum constants to represent data type - training or evaluation
     */
    public enum DataType {

        /** Indicates that this data is for 'training' */
        TRAINING(0),
        /** Indicates that this data is for 'evaluation' */
        TEST(1),
        /** Indicates that this data is for both 'training' and 'evaluation' */
        TRAINING_AND_TEST(2);

        private final int mValue;

        DataType(int value) {
            mValue = value;
        }

        /**
         * Returns the corresponding integer value used in the database.
         */
        int getValue() {
            return mValue;
        }
    }

    /**
     * A simple data class to carry the training/evaluation 'one session' data
     */
    public static class DataSet {

        @NonNull
        private final String mGroupLabel;

        @NonNull
        private final float[][] mFeatures;

        private final float mLabel;

        private DataSet(@NonNull String groupLabel, @NonNull float[][] features, float label) {
            mGroupLabel = groupLabel;
            mFeatures = features;
            mLabel = label;
        }

        @NonNull
        public String getGroupLabel() {
            return mGroupLabel;
        }

        @NonNull
        public float[][] getFeatures() {
            return mFeatures;
        }

        public float getLabel() {
            return mLabel;
        }

        @NonNull
        @Override
        public String toString() {
            return "DataSet(groupLabel=" + mGroupLabel + ", features=" + Arrays.deepToString(
                    mFeatures) + ", label='" + mLabel + "')";
        }

        /**
         * Return a builder instance.
         */
        public static Builder builder() {
            return new Builder();
        }

        /**
         * A builder class to construct {@link DataSet} instance.
         */
        public static class Builder {

            private String mGroupLabel = null;

            private float[][] mFeatures = null;

            private float mLabel;

            public Builder groupLabel(String groupLabel) {
                mGroupLabel = groupLabel;
                return this;
            }

            public Builder features(float[][] features) {
                // Might be better to copy 2d array here (No issues exist on current code)
                mFeatures = features;
                return this;
            }

            public Builder label(float label) {
                mLabel = label;
                return this;
            }

            public DataSet build() {
                return new DataSet(mGroupLabel, mFeatures, mLabel);
            }
        }
    }
}
