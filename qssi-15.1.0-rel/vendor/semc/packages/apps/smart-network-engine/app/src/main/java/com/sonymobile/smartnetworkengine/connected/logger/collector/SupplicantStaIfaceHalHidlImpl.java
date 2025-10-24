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
 *     packages/modules/Wifi/service/java/com/android/server/wifi/SupplicantStaIfaceHalHidlImpl.java
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

import android.hardware.wifi.supplicant.V1_0.ISupplicantCallback;
import android.hardware.wifi.supplicant.V1_0.ISupplicantIface;
import android.hardware.wifi.supplicant.V1_0.IfaceType;
import android.hardware.wifi.supplicant.V1_0.SupplicantStatus;
import android.hardware.wifi.supplicant.V1_0.SupplicantStatusCode;
import android.hardware.wifi.supplicant.V1_1.ISupplicant;
import android.hardware.wifi.supplicant.V1_4.ISupplicantStaIfaceCallback;
import android.hidl.manager.V1_0.IServiceManager;
import android.hidl.manager.V1_0.IServiceNotification;
import android.os.HwBinder;
import android.os.RemoteException;

import androidx.annotation.Nullable;

import com.sonymobile.smartnetworkengine.util.Log;

import java.util.ArrayList;
import java.util.List;

/**
 * Hal calls for bring up/shut down of the supplicant daemon and for
 * sending requests to the supplicant daemon
 */
public class SupplicantStaIfaceHalHidlImpl extends SupplicantStaIfaceHal {

    private static final String TAG = SupplicantStaIfaceHalHidlImpl.class.getSimpleName();
    private final Object mLock = new Object();
    private final List<String> mIfaceList = new ArrayList<>();
    private IServiceManager mIServiceManager = null;
    private final IServiceNotification mServiceNotificationCallback =
            new IServiceNotification.Stub() {
                public void onRegistration(String fqName, String name, boolean preexisting) {
                    Log.v(TAG, "onRegistration/in");
                    try {
                        android.hardware.wifi.supplicant.V1_0.ISupplicant iSupplicantV1_0
                                = android.hardware.wifi.supplicant.V1_0.ISupplicant.getService();
                        if (iSupplicantV1_0 != null) {
                            iSupplicantV1_0.registerCallback(new SupplicantCallback());
                        }
                        setupIfaceAndCallback("wlan0");
                        // This is necessary for when wlan1 is being used as PrimaryInterface.
                        setupIfaceAndCallback("wlan1");
                    } catch (RemoteException e) {
                        Log.e(TAG, "ISupplicant.registerCallback failed "
                                + "with remote exception: " + e);
                    }
                    Log.v(TAG, "onRegistration/out");
                }
            };

    /**
     * Registers a service notification for the ISupplicant service, which triggers intialization of
     * the ISupplicantStaIface
     */
    @Override
    public void initialize() {
        Log.v(TAG, "initialize/in");
        synchronized (mLock) {
            try {
                mIServiceManager = IServiceManager.getService();
                if (mIServiceManager != null) {
                    mIServiceManager.registerForNotifications(
                            ISupplicant.kInterfaceName, "", mServiceNotificationCallback);
                }
            } catch (RemoteException e) {
                Log.e(TAG, "IServiceManager.registerForNotifications failed "
                        + "with remote exception: " + e);
            }
        }
        Log.v(TAG, "initialize/out");
    }

    private boolean isV1_4() {
        try {
            return mIServiceManager.getTransport(
                    android.hardware.wifi.supplicant.V1_4.ISupplicant.kInterfaceName, "default")
                    != IServiceManager.Transport.EMPTY;
        } catch (RemoteException e) {
            return false;
        }
    }

    /**
     * Setup a STA interface for the specified iface name and register Callback.
     */
    private void setupIfaceAndCallback(String ifaceName) {
        synchronized (mLock) {
            try {
                HwBinder.configureRpcThreadpool(4, true);
                android.hardware.wifi.supplicant.V1_0.ISupplicant iSupplicantV1_0
                        = android.hardware.wifi.supplicant.V1_0.ISupplicant.getService();
                if (iSupplicantV1_0 != null) {
                    ISupplicant iSupplicantV1_1 = ISupplicant.castFrom(iSupplicantV1_0);
                    if (iSupplicantV1_1 != null) {
                        ISupplicant.IfaceInfo ifaceInfo = new ISupplicant.IfaceInfo();
                        ifaceInfo.name = ifaceName;
                        ifaceInfo.type = IfaceType.STA;
                        Mutable<ISupplicantIface> iSupplicantIface = new Mutable<>();
                        iSupplicantV1_1.getInterface(ifaceInfo,
                                (SupplicantStatus status, ISupplicantIface iface) -> {
                                    if (status.code != SupplicantStatusCode.SUCCESS
                                            && status.code
                                            != SupplicantStatusCode.FAILURE_IFACE_EXISTS) {
                                        return;
                                    }
                                    iSupplicantIface.value = iface;
                                });
                        ISupplicantIface ifaceHwBinder = iSupplicantIface.value;
                        if (ifaceHwBinder != null) {
                            if (isV1_4()) {
                                android.hardware.wifi.supplicant.V1_4.ISupplicantStaIface iface
                                        = android.hardware.wifi.supplicant.V1_4.ISupplicantStaIface
                                        .asInterface(ifaceHwBinder.asBinder());
                                if (iface != null) {
                                    iface.registerCallback_1_4(
                                            new SupplicantStaIfaceCallbackHidlImpl(ifaceName));
                                }
                            } else {
                                android.hardware.wifi.supplicant.V1_3.ISupplicantStaIface iface
                                        = android.hardware.wifi.supplicant.V1_3.ISupplicantStaIface
                                        .asInterface(ifaceHwBinder.asBinder());
                                if (iface != null) {
                                    iface.registerCallback_1_3(
                                            new SupplicantStaIfaceCallbackHidlImpl(ifaceName));
                                }
                            }
                            mIfaceList.add(ifaceName);
                        }
                    }
                }
            } catch (RemoteException e) {
            }
        }
    }

    private static class Mutable<E> {
        public E value;

        Mutable() {
            value = null;
        }

        Mutable(E value) {
            this.value = value;
        }
    }

    private class SupplicantCallback extends ISupplicantCallback.Stub {
        @Override
        public void onInterfaceCreated(String ifName) {
            if (ifName != null && ifName.matches("wlan\\d") && !mIfaceList.contains(ifName)) {
                setupIfaceAndCallback(ifName);
            }
        }

        @Override
        public void onInterfaceRemoved(String ifName) {
            mIfaceList.remove(ifName);
        }

        @Override
        public void onTerminating() {
        }
    }

    private class SupplicantStaIfaceCallbackHidlImpl extends ISupplicantStaIfaceCallback.Stub {
        private final String mIfaceName;

        public SupplicantStaIfaceCallbackHidlImpl(String ifaceName) {
            mIfaceName = ifaceName;
        }

        @Override
        public void onNetworkAdded(int id) {
        }

        @Override
        public void onNetworkRemoved(int id) {
        }

        @Override
        public void onStateChanged_1_3(int newState, byte[/* 6 */] bssid, int id,
                ArrayList<Byte> ssid, boolean filsHlpSent) {
        }

        @Override
        public void onAnqpQueryDone(byte[/* 6 */] bssid,
                android.hardware.wifi.supplicant.V1_0.ISupplicantStaIfaceCallback.AnqpData data,
                Hs20AnqpData hs20Data) {

        }

        @Override
        public void onHs20IconQueryDone(byte[/* 6 */] bssid, String fileName,
                ArrayList<Byte> data) {
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
        public void onAssociationRejected(byte[/* 6 */] bssid, int statusCode, boolean timedOut) {
        }

        @Override
        public void onAssociationRejected_1_4(AssociationRejectionData assocRejectData) {
        }

        @Override
        public void onAuthenticationTimeout(byte[/* 6 */] bssid) {
        }

        @Override
        public void onBssidChanged(byte reason, byte[/* 6 */] bssid) {
        }

        @Override
        public void onEapFailure() {
        }

        @Override
        public void onEapFailure_1_1(int code) {
        }

        @Override
        public void onWpsEventSuccess() {
        }

        @Override
        public void onWpsEventFail(byte[/* 6 */] bssid, short configError, short errorInd) {
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
        public void onEapFailure_1_3(int code) {
        }

        @Override
        public void onBssTmHandlingDone(BssTmData tmData) {
        }

        @Override
        public void onDppFailure_1_3(int code, String ssid, String channelList,
                ArrayList<Short> bandList) {
        }

        @Override
        public void onDppProgress_1_3(int code) {
        }

        @Override
        public void onDppSuccess(int code) {
        }

        @Override
        public void onPmkCacheAdded(long expirationTimeInSec, ArrayList<Byte> serializedEntry) {
        }

        @Override
        public void onDppFailure(int code) {
        }

        @Override
        public void onDppProgress(int code) {
        }

        @Override
        public void onDppSuccessConfigSent() {
        }

        @Override
        public void onDppSuccessConfigReceived(ArrayList<Byte> ssid, String password,
                byte[] psk, int securityAkm) {
        }

        @Override
        public void onStateChanged(int newState, byte[/* 6 */] bssid, int id,
                ArrayList<Byte> ssid) {
        }

        @Override
        public void onAnqpQueryDone_1_4(byte[/* 6 */] bssid, AnqpData data, Hs20AnqpData hs20Data) {
        }

        @Override
        public void onNetworkNotFound(ArrayList<Byte> ssid) {
        }

        @Override
        public void onHs20TermsAndConditionsAcceptanceRequestedNotification(byte[/* 6 */] bssid,
                String url) {
        }
    }
}
