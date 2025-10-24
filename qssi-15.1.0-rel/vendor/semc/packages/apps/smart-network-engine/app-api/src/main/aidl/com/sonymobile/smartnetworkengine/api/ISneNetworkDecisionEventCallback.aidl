/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.api;

import com.sonymobile.smartnetworkengine.api.LoggingStats;

/**
 * Interface for callback invocation on network decision event.
 */
oneway interface ISneNetworkDecisionEventCallback
{
    void onDecisionMade(boolean wifiUsable, in LoggingStats sourceStats);
}
