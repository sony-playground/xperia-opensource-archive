/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.api;

import com.sonymobile.smartnetworkengine.api.LoggingStats;

/**
 * Interface for callback invocation on logging event.
 */
oneway interface ISneLoggingEventCallback
{
    void onStarted();

    void onStopped(int reason);

    void onStatsUpdated(in LoggingStats stats);
}
