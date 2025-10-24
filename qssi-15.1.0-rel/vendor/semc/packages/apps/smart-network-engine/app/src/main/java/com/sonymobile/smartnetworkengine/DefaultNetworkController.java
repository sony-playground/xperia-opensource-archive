/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine;


import androidx.annotation.NonNull;

public interface DefaultNetworkController {

    /**
     * Interface for callback invocation on default network controller start-up and shutdown.
     */
    interface StatusListener {
        /**
         * DefaultNetworkController started - nearly equal to wifi connected.
         */
        void onStart();

        /**
         * DefaultNetworkController stopped - nearly equal to wifi disconnected.
         */
        void onStop();

        /**
         * Default network preference changed - this enables caller to get notified of wifi
         * preference change reported to framework. Caller can get actual preference via {@link
         * DefaultNetworkController#isWifiNetworkPreferred()}.
         */
        default void onPreferenceChanged() {
        }
    }

    /**
     * Register listener for controller status.
     *
     * @param statusListener to listen controller status.
     */
    void registerStatusListener(@NonNull StatusListener statusListener);

    /**
     * Unregister listener for controller status.
     *
     * @param statusListener to be unregistered.
     */
    void unregisterStatusListener(@NonNull StatusListener statusListener);

    /**
     * Prefer to use Wifi as default network.
     *
     * @return true if accepted. False otherwise(E.g. Wifi network score support is disabled).
     */
    boolean preferWifiNetwork();

    /**
     * Prefer to use non-Wifi (mostly LTE) as default network.
     *
     * @return true if accepted. False otherwise(E.g. Wifi network score support is disabled).
     */
    boolean preferNonWifiNetwork();

    /**
     * Prefer to use non-Wifi (mostly LTE) as default network.
     *
     * @param durationMs duration in milliseconds to preference is reset. I.e. After this duration,
     *                   Wifi will be preferred as default network. If this method is called within
     *                   the duration specified by previous call, it will be replaced with new
     *                   duration. Preference will never be reset if duration is 0 or less.
     * @return true if accepted. False otherwise(E.g. Wifi network score support is disabled).
     */
    boolean preferNonWifiNetwork(long durationMs);

    /**
     * Return whether Wifi is preferred as default network.
     *
     * @return true if Wifi is preferred as default network.
     */
    boolean isWifiNetworkPreferred();
}
