/*
 * Copyright 2020, 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.api;

import android.os.Bundle;
import com.sonymobile.smartnetworkengine.api.ISneLoggingEventCallback;
import com.sonymobile.smartnetworkengine.api.ISneNetworkDecisionEventCallback;
import com.sonymobile.smartnetworkengine.api.WifiStats;

/**
 * Interface for receiving various events from application.
 */
interface ISneEventManager
{
    Bundle getAppConfigurations();

    void setLoggingEventCallback(ISneLoggingEventCallback callback);

    void setNetworkDecisionEventCallback(ISneNetworkDecisionEventCallback callback);

    WifiStats refreshAndGetWifiStats();
}
