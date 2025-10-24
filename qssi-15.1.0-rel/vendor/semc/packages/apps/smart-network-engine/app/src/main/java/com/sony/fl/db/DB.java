package com.sony.fl.db;

/**
 * @author Masanobu Jimbo
 */

public interface DB {
    abstract public BooleanAndStatus tableExist(String tableName);
    abstract public StringAndStatus getStringByPrimaryKey(String tableName,
            String primaryKey, String keyValue, String columnName);
    abstract public IntAndStatus getIntegerByPrimaryKey(String tableName,
			String primaryKey, String keyValue, String columnName);
    abstract public Status updateRow(String tableName,
            String primaryKey, String keyValue,
            String fields[], String newValues[]);
    abstract public Status deleteRow(String tableName, 
            String primaryKey, String keyValue);
    abstract public Status createTable(String tableName,
			String primaryKey, String typeOfPrimaryKey,
			String[] fields, String[] typeOfFields);

    public class Status {
        private int statusCode; // 0:success 1:failed
        public Status(int code) {
            statusCode = code;
        }
        public int getStatusCode() {
            return statusCode;
        }
    }

    public class IntAndStatus {
        private int result;
        private Status status;
        public IntAndStatus(Status status, int result) {
            this.result = result;
            this.status = status;
        }
        public int getResult() {
            return result;
        }
        public Status getStatus() {
            return status;
        }
    }

    public class BooleanAndStatus {
        private boolean result;
        private Status status;
        public BooleanAndStatus(Status status, boolean result) {
            this.result = result;
            this.status = status;
        }
        public boolean getResult() {
            return result;
        }
        public Status getStatus() {
            return status;
        }
    }

    public class StringAndStatus {
        private String result;
        private Status status;
        public StringAndStatus(Status status, String result) {
            this.result = result;
            this.status = status;
        }
        public String getResult() {
            return result;
        }
        public Status getStatus() {
            return status;
        }
    }

}