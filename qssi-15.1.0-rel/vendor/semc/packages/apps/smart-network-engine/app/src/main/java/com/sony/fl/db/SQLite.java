package com.sony.fl.db;

import java.nio.file.Path;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import com.sony.fl.logger.FLLogger;

/**
 * @author Masanobu Jimbo
 */

public class SQLite implements DB {
    private final static String SQLITE_DB_NAME = "/sqlight.db";
    private final String mURI;

    public SQLite(Path dbFolderPath) {
        StringBuilder sb = new StringBuilder(); 
        String uri = sb.append("jdbc:sqlite:").append(dbFolderPath)
                .append(SQLITE_DB_NAME).toString();
        FLLogger.d("SQlite DB URI = " + uri);
        mURI = uri;
    }

    public BooleanAndStatus tableExist(String tableName) {
        int statusCode = 0;
        boolean existTable = false;
        String query = "select * from sqlite_master where type='table'";
        Connection conn = null;
        Statement stmt = null;
        try{
            conn = DriverManager.getConnection(mURI);
            stmt = conn.createStatement();
            FLLogger.d(query);
            ResultSet rs = stmt.executeQuery(query);
            while(rs.next()) {
                if (rs.getString("name").equals(tableName)) {
                    existTable = true;
                    break;
                }
            }
            rs.close();
        } catch (SQLException e) {
            FLLogger.e(e.toString());
            statusCode = 1;
        } finally {
            try {
                if (stmt != null) {
                    stmt.close();
                }
            } catch (SQLException e) {
                FLLogger.e(e.toString());
                statusCode = 1;
            } finally {
                try {
                    if (conn != null) {
                        conn.close();
                    }
                } catch (SQLException e) {
                    FLLogger.e(e.toString());
                    statusCode = 1;
                }
            }
        }
        return new BooleanAndStatus(new Status(statusCode), existTable);
    }

    public StringAndStatus getStringByPrimaryKey(String tableName, 
            String primaryKey, String keyValue, String columnName) {
        int statusCode = 0;
        String ret = null;
        String query = "select * from " + tableName 
                + " where " + primaryKey + "='"+ keyValue + "'";
        Connection conn = null;
        Statement stmt = null;
        try {
            conn = DriverManager.getConnection(mURI);
            stmt = conn.createStatement();
            FLLogger.d(query);
            ResultSet rs = stmt.executeQuery(query);
            ret = rs.getString(columnName);
            rs.close();
        } catch (SQLException e) {
            FLLogger.w(e.toString());
            statusCode = 1;
        } finally {
            try {
                if (stmt != null) {
                    stmt.close();
                }
            } catch (SQLException e) {
                FLLogger.e(e.toString());
                statusCode = 1;
            } finally {
                try {
                    if (conn != null) {
                        conn.close();
                    }
                } catch (SQLException e) {
                    FLLogger.e(e.toString());
                    statusCode = 1;
                }
            }
        }
        return new StringAndStatus(new Status(statusCode), ret);
    }

    public IntAndStatus getIntegerByPrimaryKey(String tableName,
            String primaryKey, String keyValue, String columnName) {
        int statusCode = 0;
        int ret = 0;
        String query = "select * from " + tableName 
                + " where " + primaryKey + "='"+ keyValue + "'";
        Connection conn = null;
        Statement stmt = null;
        try {
            conn = DriverManager.getConnection(mURI);
            stmt = conn.createStatement();
            FLLogger.d(query);
            ResultSet rs = stmt.executeQuery(query);
            ret = rs.getInt(columnName);
            rs.close();
        } catch (SQLException e) {
            FLLogger.w(e.toString());
            statusCode = 1;
        } finally {
            try {
                if (stmt != null) {
                    stmt.close();
                }
            } catch (SQLException e) {
                FLLogger.e(e.toString());
                statusCode = 1;
            } finally {
                try {
                    if (conn != null) {
                        conn.close();
                    }
                } catch (SQLException e) {
                    FLLogger.e(e.toString());
                    statusCode = 1;
                }
            }
        }
        return new IntAndStatus(new Status(statusCode), ret);
    }

    private BooleanAndStatus rowExist(String tableName, String primaryKey, String keyValue) {
        int statusCode = 0;
        boolean existRow = false;
        String query = "SELECT * FROM " + tableName 
                + " WHERE " + primaryKey + "='" + keyValue + "'";
        Connection conn = null;
        Statement stmt = null;
        try{
            conn = DriverManager.getConnection(mURI);
            stmt = conn.createStatement();
            FLLogger.d(query);
            ResultSet rs = stmt.executeQuery(query);
            if (rs.next()) {
                existRow = true; 
            }
            rs.close();
        } catch (SQLException e) {
            FLLogger.e(e.toString());
            statusCode = 1;
        } finally {
            try {
                if (stmt != null) {
                    stmt.close();
                }
            } catch (SQLException e) {
                FLLogger.e(e.toString());
                statusCode = 1;
            } finally {
                try {
                    if (conn != null) {
                        conn.close();
                    }
                } catch (SQLException e) {
                    FLLogger.e(e.toString());
                    statusCode = 1;
                }
            }
        }
        return new BooleanAndStatus(new Status(statusCode), existRow);
    }

    public Status updateRow(String tableName,
            String primaryKey, String keyValue,
            String[] fields, String[] newValues) {
        int statusCode = 0;
        if (fields.length != newValues.length) {
            FLLogger.e("Inputs are invalid.");
            return new Status(1);
        }
        BooleanAndStatus bas = rowExist(tableName, primaryKey, keyValue);
        if (bas.getStatus().getStatusCode() != 0) {
            FLLogger.e("columnExist was failed.");
            return new Status(1);
        }
        String query = null;
        if (bas.getResult()) {
            // update
            StringBuffer stringBuilder = new StringBuffer()
                    .append("UPDATE ")
                    .append(tableName)
                    .append(" SET ");
            for (int i = 0;i < fields.length; i++) {
                stringBuilder.append(fields[i])
                        .append("='")
                        .append(newValues[i])
                        .append("'");
                if (i != fields.length - 1) {
                    stringBuilder.append(",");
                }
            }
            stringBuilder.append(" WHERE ")
                    .append(primaryKey)
                    .append("='")
                    .append(keyValue)
                    .append("'");
            query = stringBuilder.toString();
        } else {
            StringBuffer stringBuilder = new StringBuffer()
                    .append("INSERT INTO ")
                    .append(tableName)
                    .append(" VALUES(");
            stringBuilder.append("'")
                    .append(keyValue)
                    .append("',");
            for (int i = 0;i < fields.length; i++) {
                stringBuilder.append("'")
                        .append(newValues[i])
                        .append("'");
                if (i != fields.length - 1) {
                    stringBuilder.append(",");
                }
            }
            stringBuilder.append(")");
            query = stringBuilder.toString();
        }
        Connection conn = null;
        Statement stmt = null;
        try {
            conn = DriverManager.getConnection(mURI);
            stmt = conn.createStatement();
            FLLogger.d(query);
            stmt.executeUpdate(query);
        } catch (SQLException e) {
            FLLogger.e("Failed to execute query");
            statusCode = 1;
        } finally {
            try {
                if (stmt != null) {
                    stmt.close();
                }
            } catch (SQLException e) {
                FLLogger.e(e.toString());
                statusCode = 1;
            } finally {
                try {
                    if (conn != null) {
                        conn.close();
                    }
                } catch (SQLException e) {
                    FLLogger.e(e.toString());
                    statusCode = 1;
                }
            }
        }
        return new Status(statusCode);
    }

    public Status deleteRow(String tableName, 
            String primaryKey, String keyValue) {
        String query = "DELETE FROM " + tableName + " WHERE " + primaryKey + "='" + keyValue + "'";
        int statusCode = 0;
        Connection conn = null;
        Statement stmt = null;
        try {
            conn = DriverManager.getConnection(mURI);
            stmt = conn.createStatement();
            FLLogger.d(query);
            stmt.executeUpdate(query);
        } catch (SQLException e) {
            FLLogger.e("Failed to close result set");
            statusCode = 1;
        } finally {
            try {
                if (stmt != null) {
                    stmt.close();
                }
            } catch (SQLException e) {
                FLLogger.e(e.toString());
                statusCode = 1;
            } finally {
                try {
                    if (conn != null) {
                        conn.close();
                    }
                } catch (SQLException e) {
                    FLLogger.e(e.toString());
                    statusCode = 1;
                }
            }
        }
        return new Status(statusCode);
    }

    public Status createTable(String tableName,
			String primaryKey, String typeOfPrimaryKey,
			String[] fields, String[] typeOfFields) {
        int statusCode = 0;
        if (fields.length != typeOfFields.length) {
            FLLogger.e("Inputs are invalid.");
            return new Status(1);
        }
        BooleanAndStatus bas = tableExist(tableName);
        if (bas.getStatus().getStatusCode() != 0) {
            FLLogger.e("exist table was failed.");
            return new Status(1);
        }
        if (!bas.getResult()) {
            StringBuffer queryBuilder = new StringBuffer()
                    .append("CREATE TABLE ")
                    .append(tableName)
                    .append(" (")
                    .append(primaryKey)
                    .append(" ")
                    .append(typeOfPrimaryKey)
                    .append(", ");
            for (int i = 0; i < fields.length; i++) {
                queryBuilder.append(fields[i])
                    .append(" ")
                    .append(typeOfFields[i])
                    .append(", ");
            }
            queryBuilder.append("PRIMARY KEY (")
                    .append(primaryKey)
                    .append("))");
            String query = queryBuilder.toString();
            Connection conn = null;
            Statement stmt = null;
            try {
                conn = DriverManager.getConnection(mURI);
                stmt = conn.createStatement();
                FLLogger.d(query);
                stmt.executeUpdate(query); // should we check return value?
            } catch (SQLException e) {
                FLLogger.e(e.toString());
                statusCode = 1;
            } finally {
                try {
                    if (stmt != null) {
                        stmt.close();
                    }
                } catch (SQLException e) {
                    FLLogger.e(e.toString());
                    statusCode = 1;
                } finally {
                    try {
                        if (conn != null) {
                            conn.close();
                        }
                    } catch (SQLException e) {
                        FLLogger.e(e.toString());
                        statusCode = 1;
                    }
                }
            }
        } else {
            FLLogger.d(tableName + " already exists.");
        }
        return new Status(statusCode);
    }
}