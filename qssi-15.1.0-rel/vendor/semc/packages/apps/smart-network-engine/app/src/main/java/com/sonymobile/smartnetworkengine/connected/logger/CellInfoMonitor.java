/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.connected.logger;

import static com.sonymobile.smartnetworkengine.Constants.CELL_NETWORK_TYPE_LTE;
import static com.sonymobile.smartnetworkengine.Constants.CELL_NETWORK_TYPE_LTE_NR_CONNECTED;
import static com.sonymobile.smartnetworkengine.Constants.CELL_NETWORK_TYPE_LTE_NR_NOT_RESTRICTED;
import static com.sonymobile.smartnetworkengine.Constants.CELL_NETWORK_TYPE_NR;
import static com.sonymobile.smartnetworkengine.Constants.CELL_NETWORK_TYPE_UNKNOWN;

import android.content.Context;
import android.telephony.AccessNetworkConstants;
import android.telephony.CellIdentityLte;
import android.telephony.CellIdentityNr;
import android.telephony.CellSignalStrength;
import android.telephony.CellSignalStrengthLte;
import android.telephony.CellSignalStrengthNr;
import android.telephony.NetworkRegistrationInfo;
import android.telephony.PhysicalChannelConfig;
import android.telephony.ServiceState;
import android.telephony.SignalStrength;
import android.telephony.SubscriptionManager;
import android.telephony.TelephonyCallback;
import android.telephony.TelephonyManager;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;

import com.sonymobile.smartnetworkengine.util.Log;

import java.util.List;

/**
 * Monitor for changes in Cellular Network and update Cellular Info.
 */
public class CellInfoMonitor {

    private static final String TAG = CellInfoMonitor.class.getSimpleName();

    private final TelephonyManager mTelephonyManager;

    private final Context mContext;

    private CellIdentityLte mCellIdentityLte;
    private CellIdentityNr mCellIdentityNr;
    private CellSignalStrengthLte mCellSignalStrengthLte;
    private CellSignalStrengthNr mCellSignalStrengthNr;
    private boolean mDataConnected = false;
    private int mNetworkType = CELL_NETWORK_TYPE_UNKNOWN;
    private boolean mStarted;
    private int mDataSubId;
    private int mLteCellBandwidthDownlinkKhz;

    CellInfoMonitor(@NonNull Context context) {
        mContext = context;
        mTelephonyManager = (TelephonyManager) context.getSystemService(
                Context.TELEPHONY_SERVICE);
    }

    synchronized CellSignalStrengthLte getCellSignalStrengthLte() {
        return mCellSignalStrengthLte;
    }

    synchronized CellSignalStrengthNr getCellSignalStrengthNr() {
        return mCellSignalStrengthNr;
    }

    synchronized boolean getDataConnectionState() {
        return mDataConnected;
    }

    synchronized int getNetworkType() {
        return mNetworkType;
    }

    synchronized int getLteCellBandwidthDownlinkKhz() {
        return mLteCellBandwidthDownlinkKhz;
    }

    public synchronized void start() {
        mDataSubId = SubscriptionManager.getDefaultDataSubscriptionId();
        if (!mStarted) {
            mTelephonyManager.createForSubscriptionId(mDataSubId).registerTelephonyCallback(
                    mContext.getMainExecutor(), mCellInfoCallback);
            mStarted = true;
        }
    }

    public synchronized void stop() {
        if (mStarted) {
            mTelephonyManager.createForSubscriptionId(mDataSubId).unregisterTelephonyCallback(
                    mCellInfoCallback);
            mStarted = false;
        }
    }

    private synchronized void resetCellInfoMonitorOnSubIdChanged() {
        if (mStarted) {
            // reset each parameter
            mDataConnected = false;
            mNetworkType = CELL_NETWORK_TYPE_UNKNOWN;
            mCellIdentityLte = null;
            mCellSignalStrengthLte = null;
            mCellIdentityNr = null;
            mCellSignalStrengthNr = null;
            mLteCellBandwidthDownlinkKhz = PhysicalChannelConfig.CELL_BANDWIDTH_UNKNOWN;
            mTelephonyManager.createForSubscriptionId(mDataSubId).unregisterTelephonyCallback(
                    mCellInfoCallback);
            mDataSubId = SubscriptionManager.getDefaultDataSubscriptionId();
            mTelephonyManager.createForSubscriptionId(mDataSubId).registerTelephonyCallback(
                    mContext.getMainExecutor(), mCellInfoCallback);
        }
    }

    private final CellInfoCallback mCellInfoCallback = new CellInfoCallback();

    /**
     * Telephony callback to collect cellular info
     */
    private class CellInfoCallback extends TelephonyCallback implements
            TelephonyCallback.ServiceStateListener, TelephonyCallback.SignalStrengthsListener,
            TelephonyCallback.PhysicalChannelConfigListener,
            TelephonyCallback.ActiveDataSubscriptionIdListener {

        @Override
        public void onServiceStateChanged(ServiceState serviceState) {
            Log.v(TAG, "onServiceStateChanged");
            synchronized (CellInfoMonitor.this) {
                NetworkRegistrationInfo regInfo = serviceState.getNetworkRegistrationInfo(
                        NetworkRegistrationInfo.DOMAIN_PS,
                        AccessNetworkConstants.TRANSPORT_TYPE_WWAN);
                if (regInfo == null) {
                    Log.v(TAG, "onServiceStateChanged: cellular NRI is null");
                    mNetworkType = CELL_NETWORK_TYPE_UNKNOWN;
                    mDataConnected = false;
                } else {
                    Log.v(TAG, "onServiceStateChanged: network type:"
                            + regInfo.getAccessNetworkTechnology());
                    switch (regInfo.getAccessNetworkTechnology()) {
                        case TelephonyManager.NETWORK_TYPE_LTE:
                            mDataConnected = true;
                            int nrState = regInfo.getNrState();
                            Log.v(TAG, "onServiceStateChanged: nr state: " + nrState);
                            switch (nrState) {
                                case NetworkRegistrationInfo.NR_STATE_CONNECTED:
                                    mNetworkType = CELL_NETWORK_TYPE_LTE_NR_CONNECTED;
                                    break;
                                case NetworkRegistrationInfo.NR_STATE_NOT_RESTRICTED:
                                    mNetworkType = CELL_NETWORK_TYPE_LTE_NR_NOT_RESTRICTED;
                                    break;
                                default:
                                    mNetworkType = CELL_NETWORK_TYPE_LTE;
                                    break;
                            }
                            break;
                        case TelephonyManager.NETWORK_TYPE_NR:
                            mDataConnected = true;
                            mNetworkType = CELL_NETWORK_TYPE_NR;
                            break;
                        default:
                            mDataConnected = true;
                            mNetworkType = CELL_NETWORK_TYPE_UNKNOWN;
                            break;
                    }
                }
            }
        }

        @Override
        public void onSignalStrengthsChanged(SignalStrength signalStrength) {
            List<CellSignalStrength> listCss = signalStrength.getCellSignalStrengths();
            Log.v(TAG, "onSignalStrengthChanged: size " + listCss.size());
            synchronized (CellInfoMonitor.this) {
                boolean lteFound = false;
                boolean nrFound = false;
                for (CellSignalStrength css : listCss) {
                    if (css instanceof CellSignalStrengthLte && !lteFound) {
                        lteFound = true;
                        mCellSignalStrengthLte = (CellSignalStrengthLte) css;
                        Log.v(TAG, "onSignalStrengthChanged: "
                                + ((CellSignalStrengthLte) css).toString());
                    } else if (css instanceof CellSignalStrengthNr && !nrFound) {
                        nrFound = true;
                        mCellSignalStrengthNr = (CellSignalStrengthNr) css;
                        Log.v(TAG, "onSignalStrengthChanged: "
                                + ((CellSignalStrengthNr) css).toString());

                    }
                }
            }
        }

        @Override
        public void onActiveDataSubscriptionIdChanged(int subId) {
            Log.v(TAG, "onActiveDataSubscriptionIdChanged");
            // Case of SIM settings is changed
            int dataSubId = SubscriptionManager.getDefaultDataSubscriptionId();
            if (mDataSubId != dataSubId) {
                // If SIM setting is changed, reset CellInfoMonitor.
                Log.v(TAG, "SIM setting is changed. Restart.");
                resetCellInfoMonitorOnSubIdChanged();
            }
        }

        @Override
        public void onPhysicalChannelConfigChanged(@NonNull List<PhysicalChannelConfig> pccList) {
            Log.v(TAG, "onPhysicalChannelConfigChanged");
            synchronized (CellInfoMonitor.this) {
                for (PhysicalChannelConfig pcc : pccList) {
                    int networkType = pcc.getNetworkType();
                    if (pcc.getConnectionStatus()
                            == PhysicalChannelConfig.CONNECTION_PRIMARY_SERVING && (
                            networkType == TelephonyManager.NETWORK_TYPE_LTE
                                    || networkType == TelephonyManager.NETWORK_TYPE_LTE_CA)) {
                        mLteCellBandwidthDownlinkKhz = pcc.getCellBandwidthDownlinkKhz();
                        Log.v(TAG, "onPhysicalChannelConfigChanged: CellBandwidthDownlinkKhz: "
                                + mLteCellBandwidthDownlinkKhz);
                        break;
                    }
                }
            }
        }
    }
}
