/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.lib;

import android.content.ContentValues;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;

import androidx.annotation.NonNull;
import androidx.annotation.VisibleForTesting;

import com.sony.fl.db.DB;
import com.sonymobile.smartnetworkengine.util.Log;

import java.io.File;

public class AndroidSQLite implements DB {

    private static final String TAG = AndroidSQLite.class.getSimpleName();

    private static final int SUCCESS = 0;
    private static final int FAILURE = 1;

    @VisibleForTesting
    /* private */ final SQLiteDatabase mDatabase;

    public AndroidSQLite(@NonNull File databaseFile) {
        mDatabase = SQLiteDatabase.openOrCreateDatabase(databaseFile, null);
    }

    @Override
    public BooleanAndStatus tableExist(String tableName) {
        try (Cursor c = mDatabase.rawQuery(
                "SELECT name FROM sqlite_master WHERE type='table' AND name=?;",
                new String[]{tableName})) {
            return new BooleanAndStatus(new Status(SUCCESS), c.getCount() == 1);
        }
    }

    @Override
    public StringAndStatus getStringByPrimaryKey(String tableName, String primaryKey,
            String keyValue, String columnName) {
        // --> "SELECT column_name FROM table_name WHERE primary_key = key_value;"
        try (Cursor c = mDatabase.query(tableName, new String[]{columnName}, primaryKey + "=?",
                new String[]{keyValue}, null, null, null)) {
            if (c.moveToFirst()) {
                return new StringAndStatus(new Status(SUCCESS), c.getString(0));
            } else {
                // SQLite class returns 1(FAILURE) in case a column doesn't exist.
                return new StringAndStatus(new Status(FAILURE), null);
            }
        }
    }

    @Override
    public IntAndStatus getIntegerByPrimaryKey(String tableName, String primaryKey, String keyValue,
            String columnName) {
        // --> "SELECT column_name FROM table_name WHERE primary_key = key_value;"
        try (Cursor c = mDatabase.query(tableName, new String[]{columnName}, primaryKey + "=?",
                new String[]{keyValue}, null, null, null)) {
            if (c.moveToFirst()) {
                return new IntAndStatus(new Status(SUCCESS), c.getInt(0));
            } else {
                // SQLite class returns 1(FAILURE) in case a column doesn't exist.
                return new IntAndStatus(new Status(FAILURE), 0);
            }
        }
    }

    @Override
    public Status updateRow(String tableName, String primaryKey, String keyValue, String[] fields,
            String[] newValues) {
        if (fields.length != newValues.length) {
            Log.w(TAG, "invalid length of fields/newValues variables");
            return new Status(FAILURE);
        }
        ContentValues contentValues = new ContentValues();
        contentValues.put(primaryKey, keyValue);
        for (int i = 0; i < fields.length; i++) {
            contentValues.put(fields[i], newValues[i]);
        }
        mDatabase.replaceOrThrow(tableName, null, contentValues);
        return new Status(SUCCESS);
    }

    @Override
    public Status deleteRow(String tableName, String primaryKey, String keyValue) {
        // --> "DELETE FROM table_name WHERE primary_key = key_value;"
        mDatabase.delete(tableName, primaryKey + "=?", new String[]{keyValue});
        return new Status(SUCCESS);
    }

    @Override
    public Status createTable(String tableName, String primaryKey, String typeOfPrimaryKey,
            String[] fields, String[] typeOfFields) {
        if (fields.length != typeOfFields.length) {
            Log.w(TAG, "invalid length of fields/typeOfFields variables");
            return new Status(FAILURE);
        }

        // SQLite class returns 0(SUCCESS) in case table already exists so use 'IF NOT EXISTS'
        // statement to behave the same way.
        StringBuilder queryBuilder = new StringBuilder()
                // --> "CREATE TABLE IF NOT EXISTS table_name"
                .append("CREATE TABLE IF NOT EXISTS ").append(tableName)
                // --> " (column_1 data_type PRIMARY KEY"
                .append(" (").append(primaryKey).append(" ").append(typeOfPrimaryKey).append(
                        " PRIMARY KEY");
        // --> ", column_2 data_type, column_3 data_type, ..., column_X data_type);"
        for (int i = 0; i < fields.length; i++) {
            queryBuilder.append(",").append(fields[i]).append(" ").append(typeOfFields[i]);
        }
        queryBuilder.append(");");

        try {
            mDatabase.execSQL(queryBuilder.toString());
        } catch (SQLException e) {
            return new Status(FAILURE);
        }
        return new Status(SUCCESS);
    }
}
