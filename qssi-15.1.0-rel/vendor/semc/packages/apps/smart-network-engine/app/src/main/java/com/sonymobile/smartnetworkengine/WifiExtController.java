/*
 * Copyright 2020, 2023 Sony Corporation
 */

package com.sonymobile.smartnetworkengine;

import androidx.annotation.NonNull;

public interface WifiExtController {

    /**
     * Request wifi statistics update. Wifi framework will try to update some statistics
     * which can be accessed through {@link android.net.wifi.WifiInfo} and
     * {@link android.net.wifi.WifiUsabilityStatsEntry}.
     * <p>
     * Note: the request is ignored if wifi connection is not established.
     */
    void requestWifiStatsUpdate();

    /**
     * Blocklist current BSSID. Wifi framework will add current BSSID to the block list
     * so that the BSSID is blocked(not auto-connected) for a certain period of time.
     */
    void blocklistCurrentBssid();

    /**
     * Request wifi framework to trigger a NUD (Neighbor Unreachability Detection) operation.
     */
    void requestNudOperation();

    /**
     * Indicate whether current Wi-Fi network is selected by the user.
     */
    boolean isUserSelected();

    // STA+STA concurrency information APIs

    /**
     * Interface for STA+STA Concurrency status update.
     */
    interface StaStaConcurrencyListener {
        /**
         * Called when STA+STA Concurrency status is changed.
         *
         * @param concurrent True if STA+STA concurrent started(multiple wifi network connected),
         *                   false otherwise.
         */
        void onStatusChanged(boolean concurrent);
    }

    /**
     * Register listener for STA+STA Concurrency status update.
     *
     * @param listener to listen the status.
     */
    void registerStaStaConcurrencyListener(@NonNull StaStaConcurrencyListener listener);

    /**
     * Unregister listener for STA+STA Concurrency status update.
     *
     * @param listener to be unregistered.
     */
    void unregisterStaStaConcurrencyListener(@NonNull StaStaConcurrencyListener listener);

    /**
     * Indicate whether STA+STA concurrent or not.
     *
     * @return True if STA+STA concurrent started(multiple wifi network connected), false otherwise.
     */
    boolean isStaStaConcurrent();

    /**
     * Return current primary interface name (e.g. wlan0). If wifi is not default network(e.g. wifi
     * is disconnected), previous primary interface name is returned.
     */
    @NonNull
    String getPrimaryInterfaceName();

    /**
     * Return whether Wifi is preferred as default network.
     *
     * @return true if Wifi is preferred as default network.
     */
    boolean isWifiPreferred();

}
