/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.data;

import androidx.room.Embedded;
import androidx.room.Relation;

import java.util.List;

public class FLTrainingData {
    @Embedded
    public FLTrainingDataSessionEntity sessionEntity;

    @Relation(
            parentColumn = "id",
            entityColumn = "session_id"
    )
    public List<FLTrainingDataFeaturesEntity> featuresEntities;
}
