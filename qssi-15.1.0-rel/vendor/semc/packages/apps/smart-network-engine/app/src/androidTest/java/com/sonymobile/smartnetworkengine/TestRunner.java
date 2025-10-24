/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine;

import androidx.test.runner.AndroidJUnitRunner;

import com.sony.fl.Configuration;

public class TestRunner extends AndroidJUnitRunner {

    @Override
    public void onStart() {
        // Update dependency for FL library
        Configuration.DB_FACTORY_FQCN =
                "com.sonymobile.smartnetworkengine.fls.lib.AndroidSQLiteFactory";
        Configuration.LOGGER_FQCN = "com.sonymobile.smartnetworkengine.fls.lib.Logger";
        super.onStart();
    }
}
