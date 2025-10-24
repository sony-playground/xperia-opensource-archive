package com.sony.fl.db;

import java.nio.file.Path;

import com.sony.fl.db.DB.StringAndStatus;
import com.sony.fl.exception.FLException;
import com.sony.fl.logger.FLLogger;

/**
 * @author Masanobu Jimbo
 */

public class DBForTrainManager {
    public final static String TABLE_NAME = "TrainManager";
    public final static String PRIMARY_KEY = "FLID";
    public final static String TYPE_OF_PRIMARY_KEY = "TEXT";
    public final static String[] FIELDS = {"path_of_backup"};
    public final static String[] TYPE_OF_FIELDS = {"TEXT"};

    private DB mDB;
    public DBForTrainManager(DBFactory dbFactory, Path dirPath) throws FLException {
        mDB = dbFactory.getDB(dirPath);
        if (mDB == null) {
            FLLogger.e("Creating DB was failed.");
            throw new FLException("Creating DB was failed.");
        }
        if (mDB.createTable(TABLE_NAME, PRIMARY_KEY, 
                TYPE_OF_PRIMARY_KEY, FIELDS, TYPE_OF_FIELDS).getStatusCode() != 0) {
            FLLogger.e("Creating table was failed.");
            throw new FLException("Creating table was failed.");
        }
    }

    public String searchForBackUpPathFromDB(String FLID) {
        StringAndStatus sas = mDB.getStringByPrimaryKey(TABLE_NAME, 
             PRIMARY_KEY, FLID, FIELDS[0]);
        if (sas.getStatus().getStatusCode() != 0) {
            FLLogger.w("Searching Path from DB was failed.");
            return null;
        }
        return sas.getResult();
    }

    public int deleteBackUpFromDB(String FLID) {
        return mDB.deleteRow(TABLE_NAME, PRIMARY_KEY, FLID).getStatusCode();
    }

    public int updateBackUpPathOnDB(String FLID, String newBackUpPathStr) {
        String[] values = {newBackUpPathStr};
        return mDB.updateRow(TABLE_NAME, PRIMARY_KEY, FLID, FIELDS, values).getStatusCode();
    }

}