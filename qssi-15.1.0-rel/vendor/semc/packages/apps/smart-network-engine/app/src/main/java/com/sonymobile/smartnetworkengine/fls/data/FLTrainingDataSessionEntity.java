/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.data;

import androidx.room.ColumnInfo;
import androidx.room.Entity;
import androidx.room.Index;
import androidx.room.PrimaryKey;

@Entity(tableName = "session", indices = {@Index(value = {"app_id_num", "test"})})
public class FLTrainingDataSessionEntity {
    @PrimaryKey(autoGenerate = true)
    @ColumnInfo(name = "id")
    public int id;

    @ColumnInfo(name = "app_id_num")
    public int appIdNum;

    @ColumnInfo(name = "group_label")
    public String groupLabel;

    @ColumnInfo(name = "timestamp")
    public long timestamp;

    @ColumnInfo(name = "label")
    public float label;

    @ColumnInfo(name = "test")
    public boolean test;
}
