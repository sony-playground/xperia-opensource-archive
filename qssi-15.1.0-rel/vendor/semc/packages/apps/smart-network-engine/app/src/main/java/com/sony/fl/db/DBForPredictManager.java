package com.sony.fl.db;

import java.nio.file.Path;

import com.sony.fl.db.DB.StringAndStatus;
import com.sony.fl.exception.FLException;
import com.sony.fl.logger.FLLogger;
import com.sony.fl.utils.*;

/**
 * @author Masanobu Jimbo
 */

public class DBForPredictManager {
    public final static String TABLE_NAME = "PredictManager";
    public final static String PRIMARY_KEY = "AppID";
    public final static String TYPE_OF_PRIMARY_KEY = "TEXT";
    public final static String[] FIELDS = {"path_of_backup","modelInfo"};
    public final static String[] TYPE_OF_FIELDS = {"TEXT","TEXT"};

    private DB mDB;
    public DBForPredictManager(DBFactory dbFactory, Path dirPath) throws FLException {
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

    public String searchForBackUpPathFromDB(String appID) {
        StringAndStatus sas = mDB.getStringByPrimaryKey(TABLE_NAME, 
                PRIMARY_KEY, appID, FIELDS[0]);
        if (sas.getStatus().getStatusCode() != 0) {
            FLLogger.w("Searching Path from DB was failed.");
            return null;
        }
        return sas.getResult();
    }

    public byte[] searchForModelInfoFromDB(String appID) {
        StringAndStatus sas = mDB.getStringByPrimaryKey(TABLE_NAME, 
                PRIMARY_KEY, appID, FIELDS[1]);
        if (sas.getStatus().getStatusCode() != 0) {
            FLLogger.w("Searching ModelInfo from DB was failed.");
            return null;
        }
        return Base64Wrapper.decode(sas.getResult());
    }

    public int deleteBackUpFromDB(String appID) {
        return mDB.deleteRow(TABLE_NAME, PRIMARY_KEY, appID).getStatusCode();
    }

    public int updateAppInfoOnDB(String appID, String newBackUpPathStr, byte[] newModelInfo) {
        String[] values = {newBackUpPathStr, Base64Wrapper.encode(newModelInfo)};
        return mDB.updateRow(TABLE_NAME, PRIMARY_KEY, appID, FIELDS, values).getStatusCode();
    }

}