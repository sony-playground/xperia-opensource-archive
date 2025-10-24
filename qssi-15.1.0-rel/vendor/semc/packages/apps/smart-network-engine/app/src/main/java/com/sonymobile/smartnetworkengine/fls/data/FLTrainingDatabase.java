/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.data;

import android.content.Context;

import androidx.annotation.Nullable;
import androidx.room.Database;
import androidx.room.Room;
import androidx.room.RoomDatabase;

@Database(entities = {FLTrainingDataSessionEntity.class,
        FLTrainingDataFeaturesEntity.class}, version = 2, exportSchema = false)
public abstract class FLTrainingDatabase extends RoomDatabase {

    private static final String DATABASE_NAME = "FlsTrainingData.db";

    private static final Object sLock = new Object();

    @Nullable
    private static FLTrainingDatabase sInstance;

    // follow the singleton design pattern because RoomDatabase instance is fairly expensive.
    public static FLTrainingDatabase getInstance(Context context) {
        synchronized (sLock) {
            if (sInstance == null) {
                // Note : fallbackToDestructiveMigration
                // If there is an old version of the DB, it will be deleted and regenerated.

                // If you want to migrate the old version of the DB without deleting it,
                // you need to use the Migration class.
                sInstance = Room.databaseBuilder(context, FLTrainingDatabase.class,
                        DATABASE_NAME).fallbackToDestructiveMigration().build();
            }
            return sInstance;
        }
    }

    public abstract FLTrainingDataDao trainingDataDao();
}
