/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.data;

import androidx.room.ColumnInfo;
import androidx.room.Entity;
import androidx.room.ForeignKey;
import androidx.room.Ignore;
import androidx.room.Index;
import androidx.room.PrimaryKey;

import java.util.Arrays;

@Entity(tableName = "features", foreignKeys = {
        @ForeignKey(entity = FLTrainingDataSessionEntity.class,
                parentColumns = {"id"}, childColumns = {"session_id"},
                onDelete = ForeignKey.CASCADE)}, indices = @Index(value = {"session_id"}))
public class FLTrainingDataFeaturesEntity {
    @PrimaryKey(autoGenerate = true)
    @ColumnInfo(name = "id")
    public int id;

    @ColumnInfo(name = "session_id")
    public long sessionId;

    @ColumnInfo(name = "feature_1")
    public Float feature1;

    @ColumnInfo(name = "feature_2")
    public Float feature2;

    @ColumnInfo(name = "feature_3")
    public Float feature3;

    @ColumnInfo(name = "feature_4")
    public Float feature4;

    @ColumnInfo(name = "feature_5")
    public Float feature5;

    @ColumnInfo(name = "feature_6")
    public Float feature6;

    @ColumnInfo(name = "feature_7")
    public Float feature7;

    @ColumnInfo(name = "feature_8")
    public Float feature8;

    @ColumnInfo(name = "feature_9")
    public Float feature9;

    @ColumnInfo(name = "feature_10")
    public Float feature10;

    @ColumnInfo(name = "feature_11")
    public Float feature11;

    @ColumnInfo(name = "feature_12")
    public Float feature12;

    @ColumnInfo(name = "feature_13")
    public Float feature13;

    @ColumnInfo(name = "feature_14")
    public Float feature14;

    @ColumnInfo(name = "feature_15")
    public Float feature15;

    @Ignore
    private float[] mAvailableFeatures;

    /**
     * Constructor for Room database
     */
    public FLTrainingDataFeaturesEntity() {
    }

    /**
     * Constructor for the accessor to make it easy to build entity for adding data
     */
    public FLTrainingDataFeaturesEntity(float[] availableFeatures) {
        setAvailableFeatures(availableFeatures);
    }

    /**
     * Returns all available features as an array.
     */
    public float[] getAvailableFeatures() {
        if (mAvailableFeatures == null) {
            float[] features = new float[15];
            int size = 0;
            // Once 'null' feature appears, all of the subsequent features should be null
            if (feature1 != null) features[size++] = feature1;
            if (feature2 != null) features[size++] = feature2;
            if (feature3 != null) features[size++] = feature3;
            if (feature4 != null) features[size++] = feature4;
            if (feature5 != null) features[size++] = feature5;
            if (feature6 != null) features[size++] = feature6;
            if (feature7 != null) features[size++] = feature7;
            if (feature8 != null) features[size++] = feature8;
            if (feature9 != null) features[size++] = feature9;
            if (feature10 != null) features[size++] = feature10;
            if (feature11 != null) features[size++] = feature11;
            if (feature12 != null) features[size++] = feature12;
            if (feature13 != null) features[size++] = feature13;
            if (feature14 != null) features[size++] = feature14;
            if (feature15 != null) features[size++] = feature15;
            mAvailableFeatures = Arrays.copyOf(features, size);
        }
        return mAvailableFeatures;
    }

    private void setAvailableFeatures(float[] availableFeatures) {
        mAvailableFeatures = availableFeatures.clone();
        int index = 0;
        if (index < mAvailableFeatures.length) feature1 = mAvailableFeatures[index++];
        if (index < mAvailableFeatures.length) feature2 = mAvailableFeatures[index++];
        if (index < mAvailableFeatures.length) feature3 = mAvailableFeatures[index++];
        if (index < mAvailableFeatures.length) feature4 = mAvailableFeatures[index++];
        if (index < mAvailableFeatures.length) feature5 = mAvailableFeatures[index++];
        if (index < mAvailableFeatures.length) feature6 = mAvailableFeatures[index++];
        if (index < mAvailableFeatures.length) feature7 = mAvailableFeatures[index++];
        if (index < mAvailableFeatures.length) feature8 = mAvailableFeatures[index++];
        if (index < mAvailableFeatures.length) feature9 = mAvailableFeatures[index++];
        if (index < mAvailableFeatures.length) feature10 = mAvailableFeatures[index++];
        if (index < mAvailableFeatures.length) feature11 = mAvailableFeatures[index++];
        if (index < mAvailableFeatures.length) feature12 = mAvailableFeatures[index++];
        if (index < mAvailableFeatures.length) feature13 = mAvailableFeatures[index++];
        if (index < mAvailableFeatures.length) feature14 = mAvailableFeatures[index++];
        if (index < mAvailableFeatures.length) feature15 = mAvailableFeatures[index++];
    }
}
