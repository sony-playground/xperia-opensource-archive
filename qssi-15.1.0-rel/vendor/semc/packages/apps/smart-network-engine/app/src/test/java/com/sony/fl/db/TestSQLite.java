package com.sony.fl.db;

import static org.junit.Assert.assertEquals;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import com.sony.fl.db.DB.BooleanAndStatus;
import com.sony.fl.db.DB.IntAndStatus;
import com.sony.fl.db.DB.StringAndStatus;

import org.apache.commons.io.file.PathUtils;
import org.junit.Test;

public class TestSQLite {
    
    @Test
    public void TestGetDB() {
        Path path1 = Paths.get("src/test/resources/db/sample1");
        SQLite db_A = (SQLite)new SQLiteFactory().getDB(path1);
        SQLite db_B = (SQLite)new SQLiteFactory().getDB(path1);
        Path path2 = Paths.get("src/test/resources/db/sample2");
        SQLite db_C = (SQLite)new SQLiteFactory().getDB(path2);
        assertEquals(true, db_A == db_B);
        assertEquals(false,db_A == db_C);
        Path badPath = Paths.get("bad/path");
        assertEquals(true, ((SQLite)new SQLiteFactory().getDB(badPath)) == null);
    }

    @Test
    public void testSQLite() {
        String tableName = "sample_table";
        String primaryKey = "key";
        String typeOfPrimaryKey = "TEXT";
        String[] fields = {"str","num"};
        String[] typeOfFields = {"TEXT","INTEGER"};
        Path samplePath = Paths.get("src/test/resources/db/sample");
        try {
            Files.createDirectories(samplePath);
        } catch (IOException e) {
            assertEquals(0, 1);
        }
        // create DB
        SQLite db = (SQLite)new SQLiteFactory().getDB(samplePath);
        assertEquals(false, db == null);
        // create a table
        assertEquals(0, db.createTable(
                tableName, primaryKey, typeOfPrimaryKey, fields, typeOfFields).getStatusCode());
        // search for the table
        BooleanAndStatus bas = db.tableExist(tableName);
        assertEquals(0, bas.getStatus().getStatusCode());
        assertEquals(true, bas.getResult());
        // saerch for a dummy table
        String dummyTableName = "dummy";
        bas = db.tableExist(dummyTableName);
        assertEquals(0, bas.getStatus().getStatusCode());
        assertEquals(false, bas.getResult());
        // create 2 new rows
        assertEquals(0, db.updateRow(tableName, primaryKey, "key1", 
                fields, new String[]{"str1","1"}).getStatusCode());
        assertEquals(0, db.updateRow(tableName, primaryKey, "key2", 
                fields, new String[]{"str2","2"}).getStatusCode());
        // search the 2 rows
        StringAndStatus sas = db.getStringByPrimaryKey(tableName, primaryKey, "key1", "str");
        assertEquals(0, sas.getStatus().getStatusCode());
        assertEquals(true, sas.getResult().equals("str1"));
        IntAndStatus ias = db.getIntegerByPrimaryKey(tableName, primaryKey, "key2", "num");
        assertEquals(0, ias.getStatus().getStatusCode());
        assertEquals(2, ias.getResult());
        // update the 2 rows
        assertEquals(0, db.updateRow(tableName, primaryKey, "key1", 
                fields, new String[]{"str100","1"}).getStatusCode());
        assertEquals(0, db.updateRow(tableName, primaryKey, "key2", 
                fields, new String[]{"str2","200"}).getStatusCode());
        // search the 2 rows
        sas = db.getStringByPrimaryKey(tableName, primaryKey, "key1", "str");
        assertEquals(0, sas.getStatus().getStatusCode());
        assertEquals(true, sas.getResult().equals("str100"));
        ias = db.getIntegerByPrimaryKey(tableName, primaryKey, "key2", "num");
        assertEquals(0, ias.getStatus().getStatusCode());
        assertEquals(200, ias.getResult());
        // delete a row
        assertEquals(0, db.deleteRow(tableName, primaryKey, "key1").getStatusCode());
        sas = db.getStringByPrimaryKey(tableName, primaryKey, "key1", "str");
        assertEquals(1, sas.getStatus().getStatusCode());
        ias = db.getIntegerByPrimaryKey(tableName, primaryKey, "key1", "num");
        assertEquals(1, ias.getStatus().getStatusCode());
        try {
            PathUtils.deleteDirectory(samplePath);
        } catch (IOException e) {
            assertEquals(0, 1);
        }
    }


}