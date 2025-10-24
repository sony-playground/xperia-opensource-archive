/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.data;

import androidx.room.Dao;
import androidx.room.Insert;
import androidx.room.Query;
import androidx.room.Transaction;

import java.util.List;

@Dao
public abstract class FLTrainingDataDao {

    @Transaction
    @Query("SELECT * FROM session WHERE app_id_num = :appIdNum")
    public abstract List<FLTrainingData> getData(int appIdNum);

    @Transaction
    @Query("SELECT * FROM session WHERE app_id_num = :appIdNum AND test = :test")
    public abstract List<FLTrainingData> getData(int appIdNum, boolean test);

    @Query("SELECT COUNT(id) FROM session WHERE app_id_num = :appIdNum")
    public abstract int getNumOfData(int appIdNum);

    @Query("SELECT COUNT(id) FROM session WHERE app_id_num = :appIdNum AND test = :test")
    public abstract int getNumOfData(int appIdNum, boolean test);

    @Query("SELECT COUNT(id) FROM session WHERE app_id_num = :appIdNum AND group_label = "
            + ":groupLabel")
    public abstract int getNumOfData(int appIdNum, String groupLabel);

    @Query("SELECT COUNT(id) FROM session WHERE app_id_num = :appIdNum AND label >= "
            + ":labelThreshold")
    public abstract int getNumOfData(int appIdNum, float labelThreshold);

    @Query("SELECT DISTINCT group_label FROM session WHERE app_id_num = :appIdNum")
    public abstract List<String> getGroupLabelList(int appIdNum);

    @Query("SELECT AVG(label) FROM session WHERE app_id_num = :appIdNum AND test = 0")
    public abstract float getAverageOfLabel(int appIdNum);

    @Transaction
    public void addData(FLTrainingDataSessionEntity sessionEntity,
            List<FLTrainingDataFeaturesEntity> featuresEntities) {
        // Insert tne session entity into 'session' table
        long sessionId = addSessionData(sessionEntity);
        // Insert the features entities into 'features' table
        featuresEntities.forEach(e -> e.sessionId = sessionId);
        addFeaturesData(featuresEntities);
    }

    @Insert
    public abstract long addSessionData(FLTrainingDataSessionEntity sessionEntity);

    @Insert
    public abstract void addFeaturesData(List<FLTrainingDataFeaturesEntity> featuresEntities);

    @Transaction
    @Query("DELETE FROM session WHERE app_id_num = :appIdNum AND timestamp <= :timestamp")
    public abstract void deleteOldData(int appIdNum, long timestamp);

    @Transaction
    @Query("DELETE FROM session WHERE id IN (SELECT id FROM session WHERE app_id_num = :appIdNum "
            + "ORDER BY timestamp ASC LIMIT :numOfData)")
    public abstract void deleteData(int appIdNum, int numOfData);

    @Transaction
    @Query("DELETE FROM session WHERE id IN (SELECT id FROM session WHERE app_id_num = :appIdNum "
            + "AND group_label = :groupLabel ORDER BY timestamp ASC LIMIT :numOfData)")
    public abstract void deleteData(int appIdNum, String groupLabel, int numOfData);
}
