/*
 * Copyright (C) 2021 The Android Open Source Project
 * Copyright (C) 2023 Sony Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * NOTE: This file contains code from:
 *
 *     packages/modules/Wifi/service/java/com/android/server/wifi/SupplicantStaIfaceHalAidlImpl.java
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * NOTE: This file has been modified by Sony Corporation
 * Modifications are licensed under the License.
 */

package com.sonymobile.smartnetworkengine.connected.logger.collector;

import android.hardware.wifi.supplicant.AnqpData;
import android.hardware.wifi.supplicant.AssociationRejectionData;
import android.hardware.wifi.supplicant.BssTmData;
import android.hardware.wifi.supplicant.DppConnectionKeys;
import android.hardware.wifi.supplicant.Hs20AnqpData;
import android.hardware.wifi.supplicant.ISupplicant;
import android.hardware.wifi.supplicant.ISupplicantCallback;
import android.hardware.wifi.supplicant.ISupplicantStaIface;
import android.hardware.wifi.supplicant.ISupplicantStaIfaceCallback;
import android.hardware.wifi.supplicant.QosPolicyData;
import android.os.IBinder;
import android.os.IServiceCallback;
import android.os.RemoteException;
import android.os.ServiceManager;
import android.os.ServiceSpecificException;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.sonymobile.smartnetworkengine.util.Log;

import java.util.HashMap;
import java.util.Map;
import java.util.NoSuchElementException;

/**
 * Hal calls for bring up/shut down of the supplicant daemon and for
 * sending requests to the supplicant daemon
 */
public class SupplicantStaIfaceHalAidlImpl extends SupplicantStaIfaceHal {

    private static final String TAG = SupplicantStaIfaceHalAidlImpl.class.getSimpleName();
    private static final String HAL_INSTANCE_NAME = ISupplicant.DESCRIPTOR + "/default";
    public Map<String, ISupplicantStaIface> mISupplicantStaIfaces = new HashMap<>();
    private ISupplicant mISupplicant = null;
    private final IServiceCallback mServiceCallback = new IServiceCallback.Stub() {
        @Override
        public void onRegistration(String name, IBinder binder) {
            Log.v(TAG, "onRegistration");
            try {
                if (!HAL_INSTANCE_NAME.equals(name)) return;
                mISupplicant = getSupplicant();
                if (mISupplicant == null) {
                    Log.e(TAG, "Unable to obtain ISupplicant binder.");
                    return;
                }
                mISupplicant.registerCallback(new SupplicantCallback());
                setupIfaceAndCallback("wlan0");
                setupIfaceAndCallback("wlan1");
            } catch (RemoteException e) {
                Log.e(TAG, "ISupplicant.registerCallback failed "
                        + "with remote exception: " + e);
            }
        }
    };

    /**
     * Registers a service notification for the ISupplicant service.
     */
    @Override
    public void initialize() {
        Log.v(TAG, "initialize/in");
        synchronized (mLock) {
            try {
                ServiceManager.registerForNotifications(HAL_INSTANCE_NAME, mServiceCallback);
            } catch (RemoteException e) {
                Log.e(TAG, "ServiceManager.registerForNotifications failed "
                        + "with remote exception: " + e);
            }
        }
        Log.v(TAG, "initialize/out");
    }

    /**
     * Wrapper functions to access HAL objects.
     */
    private ISupplicant getSupplicant() {
        synchronized (mLock) {
            try {
                return ISupplicant.Stub.asInterface(
                        ServiceManager.getService(HAL_INSTANCE_NAME));
            } catch (Exception e) {
                Log.e(TAG, "Unable to get ISupplicant service, " + e);
                return null;
            }
        }
    }

    /**
     * Setup a STA interface for the specified iface name.
     */
    private void setupIfaceAndCallback(String ifaceName) {
        synchronized (mLock) {
            if (getStaIface(ifaceName) != null) {
                Log.e(TAG, "Iface " + ifaceName + " already exists.");
                return;
            }
            ISupplicantStaIface iface = getIface(ifaceName);
            if (iface == null) {
                Log.e(TAG, "Unable to get iface " + ifaceName);
                return;
            }
            SupplicantStaIfaceCallbackAidlImpl callback = new SupplicantStaIfaceCallbackAidlImpl(
                    ifaceName);
            if (registerCallback(iface, callback)) {
                mISupplicantStaIfaces.put(ifaceName, iface);
            } else {
                Log.e(TAG, "Unable to register callback for iface " + ifaceName);
            }
        }
    }

    /**
     * Helper method to look up the specified iface.
     */
    private ISupplicantStaIface getStaIface(@NonNull String ifaceName) {
        synchronized (mLock) {
            return mISupplicantStaIfaces.get(ifaceName);
        }
    }

    /**
     * Get a STA interface for the specified iface name.
     *
     * @param ifaceName Name of the interface.
     * @return ISupplicantStaIface object on success, null otherwise.
     */
    private ISupplicantStaIface getIface(@Nullable String ifaceName) {
        synchronized (mLock) {
            try {
                return mISupplicant.getStaInterface(ifaceName);
            } catch (RemoteException e) {
                Log.e(TAG, "ISupplicantStaIface.getIface failed with remote exception: " + e);
            } catch (ServiceSpecificException e) {
                Log.e(TAG, "ISupplicantStaIface.getIface failed "
                        + "with service specific exception: " + e);
            } catch (NoSuchElementException | IllegalArgumentException e) {
                Log.e(TAG, "Encountered exception at getIface: " + e);
            }
            return null;
        }
    }

    private boolean registerCallback(ISupplicantStaIface iface, SupplicantStaIfaceCallbackAidlImpl
            callback) {
        synchronized (mLock) {
            if (iface == null) {
                return false;
            }
            try {
                iface.registerCallback(callback);
                return true;
            } catch (RemoteException e) {
                Log.e(TAG, "ISupplicantStaIface.registerCallback failed "
                        + "with service specific exception: " + e);
            } catch (ServiceSpecificException e) {
                Log.e(TAG, "ISupplicantStaIface.registerCallback failed "
                        + "service specific exception: " + e);
            }
        }
        return false;
    }

    private class SupplicantCallback extends ISupplicantCallback.Stub {
        @Override
        public void onInterfaceCreated(String ifName) {
            if (ifName != null && ifName.matches("wlan\\d")
                    && !mISupplicantStaIfaces.containsKey(ifName)) {
                setupIfaceAndCallback(ifName);
            }
        }

        @Override
        public void onInterfaceRemoved(String ifName) {
            mISupplicantStaIfaces.remove(ifName);
        }

        @Override
        public String getInterfaceHash() {
            return ISupplicantCallback.HASH;
        }

        @Override
        public int getInterfaceVersion() {
            return ISupplicantCallback.VERSION;
        }
    }

    private class SupplicantStaIfaceCallbackAidlImpl extends ISupplicantStaIfaceCallback.Stub {
        private final String mIfaceName;

        public SupplicantStaIfaceCallbackAidlImpl(String ifaceName) {
            mIfaceName = ifaceName;
        }

        @Override
        public void onNetworkAdded(int id) {
        }

        @Override
        public void onNetworkRemoved(int id) {
        }

        @Override
        public void onStateChanged(int newState, byte[/* 6 */] bssid, int id,
                byte[] ssid, boolean filsHlpSent) {
        }

        @Override
        public void onAnqpQueryDone(byte[/* 6 */] bssid, AnqpData data, Hs20AnqpData hs20Data) {
        }

        @Override
        public void onHs20IconQueryDone(byte[/* 6 */] bssid, String fileName, byte[] data) {
        }

        @Override
        public void onHs20SubscriptionRemediation(byte[/* 6 */] bssid, byte osuMethod, String url) {
        }

        @Override
        public void onHs20DeauthImminentNotice(byte[/* 6 */] bssid, int reasonCode,
                int reAuthDelayInSec, String url) {
        }

        /**
         * Used to indicate the disconnection from the currently connected
         * network on this iface.
         *
         * @param bssid            BSSID of the AP from which we disconnected.
         * @param locallyGenerated If the disconnect was triggered by wpa_supplicant.
         * @param reasonCode       802.11 code to indicate the disconnect reason
         *                         from access point. Refer to section 8.4.1.7 of IEEE802.11 spec.
         */
        @Override
        public void onDisconnected(byte[/* 6 */] bssid, boolean locallyGenerated, int reasonCode) {
            Log.v(TAG, "onDisconnected: locallyGenerated[" + locallyGenerated
                    + "], reasonCode[" + reasonCode + "], ifaceName[" + mIfaceName + "]");
            synchronized (mLock) {
                if (mSupplicantListener != null) {
                    mSupplicantListener.onDisconnected(locallyGenerated, reasonCode, mIfaceName);
                }
            }
        }

        @Override
        public void onAssociationRejected(AssociationRejectionData assocRejectData) {
        }

        @Override
        public void onAuthenticationTimeout(byte[/* 6 */] bssid) {
        }

        @Override
        public void onBssidChanged(byte reason, byte[/* 6 */] bssid) {
        }

        @Override
        public void onEapFailure(byte[/* 6 */] bssid, int errorCode) {
        }

        @Override
        public void onWpsEventSuccess() {
        }

        @Override
        public void onWpsEventFail(byte[/* 6 */] bssid, int configError, int errorInd) {
        }

        @Override
        public void onWpsEventPbcOverlap() {
        }

        @Override
        public void onExtRadioWorkStart(int id) {
        }

        @Override
        public void onExtRadioWorkTimeout(int id) {
        }

        @Override
        public void onDppSuccessConfigReceived(byte[] ssid, String password,
                byte[] psk, int securityAkm, DppConnectionKeys keys) {
        }

        @Override
        public void onDppSuccessConfigSent() {
        }

        @Override
        public void onDppProgress(int code) {
        }

        @Override
        public void onDppFailure(int code, String ssid, String channelList, char[] bandList) {
        }

        @Override
        public void onPmkCacheAdded(long expirationTimeInSec, byte[] serializedEntry) {
        }

        @Override
        public void onDppSuccess(int code) {
        }

        @Override
        public void onBssTmHandlingDone(BssTmData tmData) {
        }

        @Override
        public void onHs20TermsAndConditionsAcceptanceRequestedNotification(byte[/* 6 */] bssid,
                String url) {
        }

        @Override
        public void onNetworkNotFound(byte[] ssid) {
        }

        @Override
        public void onQosPolicyReset() {
        }

        @Override
        public void onQosPolicyRequest(int qosPolicyRequestId, QosPolicyData[] qosPolicyData) {
        }

        @Override
        public void onAuxiliarySupplicantEvent(int eventCode, byte[] bssid, String reasonString) {
        }

        @Override
        public String getInterfaceHash() {
            return ISupplicantStaIfaceCallback.HASH;
        }

        @Override
        public int getInterfaceVersion() {
            return ISupplicantStaIfaceCallback.VERSION;
        }
    }
}
