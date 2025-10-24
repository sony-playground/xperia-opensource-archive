/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.lib;

import static androidx.test.platform.app.InstrumentationRegistry.getInstrumentation;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteException;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sony.fl.db.DB;
import com.sony.fl.db.DB.IntAndStatus;
import com.sony.fl.db.DB.Status;
import com.sony.fl.db.DB.StringAndStatus;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import java.io.File;

@RunWith(AndroidJUnit4.class)
public class AndroidSQLiteTest {

    private static final String DB_NAME = "test.db";

    private static final String TABLE_NAME = "test_table";

    private static final String PRIMARY_KEY = "id";

    private static final String PRIMARY_KEY_TYPE = "INTEGER";

    private static final String DATA_TEXT_KEY = "data_text";

    private static final String DATA_TEXT_KEY_TYPE = "TEXT";

    private static final String DATA_INTEGER_KEY = "data_integer";

    private static final String DATA_INTEGER_KEY_TYPE = "INTEGER";

    private File mDbFile;

    private AndroidSQLite mAndroidSQLite;

    @Before
    public void setUp() {
        mDbFile = getInstrumentation().getTargetContext().getDatabasePath(DB_NAME);
        mAndroidSQLite = new AndroidSQLite(mDbFile);
        mAndroidSQLite.createTable(TABLE_NAME, PRIMARY_KEY, PRIMARY_KEY_TYPE,
                new String[]{DATA_TEXT_KEY, DATA_INTEGER_KEY},
                new String[]{DATA_TEXT_KEY_TYPE, DATA_INTEGER_KEY_TYPE});
    }

    @After
    public void tearDown() {
        //noinspection ResultOfMethodCallIgnored
        mDbFile.delete();
    }

    @Test
    public void testGetStringByPrimaryKeyTest() {
        final int id = 123;
        final String data = "data_123";
        ContentValues contentValues = new ContentValues();
        contentValues.put(PRIMARY_KEY, id);
        contentValues.put(DATA_TEXT_KEY, data);
        mAndroidSQLite.mDatabase.insert(TABLE_NAME, null, contentValues);

        // Action
        StringAndStatus result = mAndroidSQLite.getStringByPrimaryKey(TABLE_NAME, PRIMARY_KEY,
                String.valueOf(id), DATA_TEXT_KEY);

        // Check
        assertEquals(0, result.getStatus().getStatusCode());
        assertEquals(data, result.getResult());

        // Action
        result = mAndroidSQLite.getStringByPrimaryKey(TABLE_NAME, PRIMARY_KEY,
                String.valueOf(id + 1), DATA_TEXT_KEY);

        // Check
        assertEquals(1, result.getStatus().getStatusCode());
        assertNull(result.getResult());
    }

    @Test
    public void testGetIntegerByPrimaryKey() {
        final int id = 123;
        final int data = 999_123;
        ContentValues contentValues = new ContentValues();
        contentValues.put(PRIMARY_KEY, id);
        contentValues.put(DATA_INTEGER_KEY, data);
        mAndroidSQLite.mDatabase.insert(TABLE_NAME, null, contentValues);

        // Action
        IntAndStatus result = mAndroidSQLite.getIntegerByPrimaryKey(TABLE_NAME, PRIMARY_KEY,
                String.valueOf(id), DATA_INTEGER_KEY);

        // Check
        assertEquals(0, result.getStatus().getStatusCode());
        assertEquals(data, result.getResult());

        // Action
        result = mAndroidSQLite.getIntegerByPrimaryKey(TABLE_NAME, PRIMARY_KEY,
                String.valueOf(id + 1), DATA_INTEGER_KEY);

        // Check
        assertEquals(1, result.getStatus().getStatusCode());
        assertEquals(0, result.getResult());
    }

    @Test
    public void testUpdateRow() {
        ContentValues contentValues = new ContentValues();
        contentValues.put(PRIMARY_KEY, 123);
        mAndroidSQLite.mDatabase.insert(TABLE_NAME, null, contentValues);

        final int id = 456;
        final String dataStr = "data_456";
        final int dataInt1 = 999_456;
        final int dataInt2 = 999_456_2;

        // Action (insert)
        Status result = mAndroidSQLite.updateRow(TABLE_NAME, PRIMARY_KEY, String.valueOf(id),
                new String[]{DATA_TEXT_KEY, DATA_INTEGER_KEY},
                new String[]{dataStr, String.valueOf(dataInt1)});

        // Check
        assertEquals(0, result.getStatusCode());
        try (Cursor c = mAndroidSQLite.mDatabase.query(TABLE_NAME,
                new String[]{DATA_TEXT_KEY, DATA_INTEGER_KEY}, null, null, null, null,
                PRIMARY_KEY + " DESC")) {
            assertEquals(2, c.getCount());
            if (c.moveToFirst()) {
                assertEquals(dataStr, c.getString(0));
                assertEquals(dataInt1, c.getInt(1));
            } else {
                fail();
            }
        }

        // Action (update)
        result = mAndroidSQLite.updateRow(TABLE_NAME, PRIMARY_KEY, String.valueOf(id),
                new String[]{DATA_TEXT_KEY, DATA_INTEGER_KEY},
                new String[]{dataStr, String.valueOf(dataInt2)});

        // Check
        assertEquals(0, result.getStatusCode());
        try (Cursor c = mAndroidSQLite.mDatabase.query(TABLE_NAME,
                new String[]{DATA_TEXT_KEY, DATA_INTEGER_KEY}, null, null, null, null,
                PRIMARY_KEY + " DESC")) {
            assertEquals(2, c.getCount());
            if (c.moveToFirst()) {
                assertEquals(dataStr, c.getString(0));
                assertEquals(dataInt2, c.getInt(1));
            } else {
                fail();
            }
        }

        // Action (update partially - not supported)
        result = mAndroidSQLite.updateRow(TABLE_NAME, PRIMARY_KEY, String.valueOf(id),
                new String[]{DATA_INTEGER_KEY},
                new String[]{String.valueOf(dataInt1)});

        // Check
        assertEquals(0, result.getStatusCode());
        try (Cursor c = mAndroidSQLite.mDatabase.query(TABLE_NAME,
                new String[]{DATA_TEXT_KEY, DATA_INTEGER_KEY}, null, null, null, null,
                PRIMARY_KEY + " DESC")) {
            assertEquals(2, c.getCount());
            if (c.moveToFirst()) {
                assertNull(c.getString(0)); // No data returned
                assertEquals(dataInt1, c.getInt(1));
            } else {
                fail();
            }
        }
    }

    @Test
    public void testDeleteRow() {
        final int id = 123;
        final int data = 999_123;
        ContentValues contentValues = new ContentValues();
        contentValues.put(PRIMARY_KEY, id);
        contentValues.put(DATA_INTEGER_KEY, data);
        mAndroidSQLite.mDatabase.insert(TABLE_NAME, null, contentValues);

        final int id2 = 456;
        final int data2 = 999_456;
        contentValues = new ContentValues();
        contentValues.put(PRIMARY_KEY, id2);
        contentValues.put(DATA_INTEGER_KEY, data2);
        mAndroidSQLite.mDatabase.insert(TABLE_NAME, null, contentValues);

        // Action
        Status result = mAndroidSQLite.deleteRow(TABLE_NAME, PRIMARY_KEY, String.valueOf(id2));

        // Check
        assertEquals(0, result.getStatusCode());
        try (Cursor c = mAndroidSQLite.mDatabase.query(TABLE_NAME, new String[]{PRIMARY_KEY}, null,
                null, null, null, null)) {
            assertEquals(1, c.getCount());
            if (c.moveToFirst()) {
                assertEquals(id, c.getInt(0));
            } else {
                fail();
            }
        }
    }

    @Test
    public void testCreateTable() {
        // Check
        // --> "SELECT 1 FROM table_name LIMIT 1;"
        try (Cursor notUsed = mAndroidSQLite.mDatabase.query(TABLE_NAME, new String[]{"1"}, null,
                null, null, null, null, "1")) {
        } catch (SQLiteException e) {
            fail();
        }

        // Action (table already exists)
        Status result = mAndroidSQLite.createTable(TABLE_NAME, PRIMARY_KEY, PRIMARY_KEY_TYPE,
                new String[]{}, new String[]{});

        // Check
        assertEquals(0, result.getStatusCode());
    }

    @Test
    public void testTableExist() {
        // Action
        DB.BooleanAndStatus result = mAndroidSQLite.tableExist(TABLE_NAME);

        // Check
        assertEquals(0, result.getStatus().getStatusCode());
        assertTrue(result.getResult());

        // Action
        result = mAndroidSQLite.tableExist("non_existent_" + TABLE_NAME);

        // Check
        assertEquals(0, result.getStatus().getStatusCode());
        assertFalse(result.getResult());
    }
}
