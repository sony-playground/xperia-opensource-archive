/*
 * Copyright (C) 2019 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.ui.provider;

import static android.provider.SearchIndexablesContract.COLUMN_INDEX_RAW_INTENT_ACTION;
import static android.provider.SearchIndexablesContract.COLUMN_INDEX_RAW_INTENT_TARGET_CLASS;
import static android.provider.SearchIndexablesContract.COLUMN_INDEX_RAW_INTENT_TARGET_PACKAGE;
import static android.provider.SearchIndexablesContract.COLUMN_INDEX_RAW_KEY;
import static android.provider.SearchIndexablesContract.COLUMN_INDEX_RAW_KEYWORDS;
import static android.provider.SearchIndexablesContract.COLUMN_INDEX_RAW_SCREEN_TITLE;
import static android.provider.SearchIndexablesContract.COLUMN_INDEX_RAW_TITLE;
import static android.provider.SearchIndexablesContract.INDEXABLES_RAW_COLUMNS;
import static android.provider.SearchIndexablesContract.INDEXABLES_XML_RES_COLUMNS;
import static android.provider.SearchIndexablesContract.NON_INDEXABLES_KEYS_COLUMNS;

import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.database.MatrixCursor;
import android.provider.SearchIndexablesProvider;

import com.sonymobile.smartnetworkengine.R;
import com.sonymobile.smartnetworkengine.ui.SettingsActivity;

/***
 * This provides the information of Smart Network Settings for Search in Settings.
 */
public class SettingsSearchIndexablesProvider extends SearchIndexablesProvider {

    private static final String KEY_PREF_SMARTNET = "smart_network_engine";

    @Override
    public boolean onCreate() {
        // May need Log.v()
        return true;
    }

    @Override
    public Cursor queryRawData(String[] strings) {
        MatrixCursor cursor = new MatrixCursor(INDEXABLES_RAW_COLUMNS);
        Context context = getContext();
        if (context != null) {
            Object[] ref = new Object[INDEXABLES_RAW_COLUMNS.length];
            ref[COLUMN_INDEX_RAW_TITLE] = context.getString(R.string.smart_network_settings_title);
            ref[COLUMN_INDEX_RAW_KEYWORDS] = context.getString(
                    R.string.smart_network_settings_msg);
            ref[COLUMN_INDEX_RAW_SCREEN_TITLE] = context.getString(
                    R.string.smart_network_settings_title);
            ref[COLUMN_INDEX_RAW_INTENT_ACTION] = Intent.ACTION_MAIN;
            ref[COLUMN_INDEX_RAW_INTENT_TARGET_PACKAGE] = context.getApplicationInfo().packageName;
            ref[COLUMN_INDEX_RAW_INTENT_TARGET_CLASS] = SettingsActivity.class.getName();
            ref[COLUMN_INDEX_RAW_KEY] = KEY_PREF_SMARTNET;
            cursor.addRow(ref);
        }
        return cursor;
    }

    @Override
    public Cursor queryXmlResources(String[] strings) {
        // Empty.
        return new MatrixCursor(INDEXABLES_XML_RES_COLUMNS);
    }

    @Override
    public Cursor queryNonIndexableKeys(String[] strings) {
        // Empty.
        return new MatrixCursor(NON_INDEXABLES_KEYS_COLUMNS);
    }
}
