/*
 * Copyright (C) 2019 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.ui.provider;

import android.content.ContentProvider;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;

import com.sonymobile.smartnetworkengine.R;

/**
 * Provider stores message according to smart network settings value for Settings summary.
 */
public class SettingsSummaryContentProvider extends ContentProvider {

    private static final String META_DATA_PREFERENCE_SUMMARY = "com.android.settings.summary";
    private static final String SUMMARY = "summary";

    @Override
    public Bundle call(String method, String uri, Bundle extras) {
        if (!SUMMARY.equals(method)) {
            return null;
        }

        Context context = getContext();
        // Override summary text
        String summary = context.getString(R.string.smart_network_settings_desc_summary);

        Bundle bundle = new Bundle();
        bundle.putString(META_DATA_PREFERENCE_SUMMARY, summary);
        return bundle;
    }


    @Override
    public boolean onCreate() {
        return true;
    }

    @Override
    public Cursor query(Uri uri, String[] strings, String s, String[] strings1, String s1) {
        return null;
    }

    @Override
    public String getType(Uri uri) {
        return null;
    }

    @Override
    public Uri insert(Uri uri, ContentValues contentValues) {
        return null;
    }

    @Override
    public int delete(Uri uri, String s, String[] strings) {
        return 0;
    }

    @Override
    public int update(Uri uri, ContentValues contentValues, String s, String[] strings) {
        return 0;
    }
}
