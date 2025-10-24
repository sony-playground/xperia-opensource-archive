/*
 * Copyright 2020, 2024 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.api;

import androidx.annotation.IntDef;
import androidx.annotation.NonNull;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

/**
 * Interface for callback invocation on logging event.
 */
public interface SneLoggingEventCallback {

    @Retention(RetentionPolicy.SOURCE)
    @IntDef({STOP_REASON_NORMAL,
            STOP_REASON_SCREENOFF,
            STOP_REASON_SHUTDOWN,
            STOP_REASON_SCOREOFF,
            STOP_REASON_SOFTAP_STARTED,
            STOP_REASON_STASTA_CONCURRENCY,
            STOP_REASON_MLO_CONNECTION,
            STOP_REASON_UNKNOWN})
    @interface StopReason {
    }

    int STOP_REASON_NORMAL = 0;
    int STOP_REASON_SCREENOFF = 1;
    int STOP_REASON_SHUTDOWN = 2;
    int STOP_REASON_SCOREOFF = 3;
    // STOP_REASON_VOICECALL(= 4) is no longer used, it is preserved for avoiding conflicting.
    int STOP_REASON_SOFTAP_STARTED = 5;
    int STOP_REASON_STASTA_CONCURRENCY = 6;
    int STOP_REASON_MLO_CONNECTION = 7;
    int STOP_REASON_UNKNOWN = -1;

    /**
     * Invoked when periodic stats update started.
     *
     * Note this is not invoked if logging is already started when callback is registered.
     */
    default void onStarted() {
    }

    /**
     * Invoked when periodic stats update stopped.
     */
    default void onStopped(@StopReason int reason) {
    }

    /**
     * Invoked when stats was updated.
     */
    default void onStatsUpdated(@NonNull LoggingStats stats) {
    }
}
