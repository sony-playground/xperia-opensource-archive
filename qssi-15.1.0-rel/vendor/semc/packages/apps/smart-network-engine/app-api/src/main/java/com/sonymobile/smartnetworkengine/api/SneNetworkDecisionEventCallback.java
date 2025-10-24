/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.api;

import androidx.annotation.NonNull;

/**
 * Interface for callback invocation on network decision event.
 */
public interface SneNetworkDecisionEventCallback {

    /**
     * Invoked when network decision was made.
     *
     * @param wifiUsable True if Wifi network is usable, false otherwise.
     * @param sourceStats The statistics used for this decision.
     */
    void onDecisionMade(boolean wifiUsable, @NonNull LoggingStats sourceStats);
}
