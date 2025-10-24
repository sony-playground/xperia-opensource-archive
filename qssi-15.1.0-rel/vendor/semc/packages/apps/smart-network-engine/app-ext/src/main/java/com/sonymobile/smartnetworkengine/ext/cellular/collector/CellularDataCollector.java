/*
 * Copyright 2020, 2024 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.ext.cellular.collector;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.ConnectivityManager.NetworkCallback;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.telephony.CellSignalStrength;
import android.telephony.CellSignalStrengthLte;
import android.telephony.CellSignalStrengthNr;
import android.telephony.PhysicalChannelConfig;
import android.telephony.ServiceState;
import android.telephony.SignalStrength;
import android.telephony.SubscriptionManager;
import android.telephony.TelephonyCallback;
import android.telephony.TelephonyManager;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.sonymobile.smartnetworkengine.ext.util.Log;

import java.util.List;

/**
 * Monitor for changes in Cellular data/Network status and collect Cellular Data from APIs.
 */
public class CellularDataCollector {
    private static final String TAG = CellularDataCollector.class.getSimpleName();

    private final ConnectivityManager mConnectivityManager;
    private final TelephonyManager mTelephonyManager;

    private final Context mContext;

    private int mDataSubId;
    private boolean mIsLteCa;
    private int mLteCellBandwidthDownlinkKhz = Integer.MAX_VALUE;

    private boolean mStarted;

    @NonNull
    private CellularRawData.Builder mCellularRawDataBuilder = CellularRawData.builder();

    public CellularDataCollector(@NonNull Context context) {
        mContext = context;
        mConnectivityManager = (ConnectivityManager) context.getSystemService(
                Context.CONNECTIVITY_SERVICE);
        mTelephonyManager = (TelephonyManager) context.getSystemService(
                Context.TELEPHONY_SERVICE);
    }

    public synchronized void start() {
        if (!mStarted) {
            mConnectivityManager.registerDefaultNetworkCallback(mNetworkCallback);
            mDataSubId = SubscriptionManager.getDefaultDataSubscriptionId();
            mTelephonyManager.createForSubscriptionId(mDataSubId).registerTelephonyCallback(
                    mContext.getMainExecutor(), mTelephonyCallback);
            mStarted = true;
        }
    }

    public synchronized void stop() {
        if (mStarted) {
            mConnectivityManager.unregisterNetworkCallback(mNetworkCallback);
            mTelephonyManager.createForSubscriptionId(mDataSubId).unregisterTelephonyCallback(
                    mTelephonyCallback);
            mCellularRawDataBuilder = CellularRawData.builder();
            mStarted = false;
        }
    }

    @NonNull
    public synchronized CellularRawData getCellularRawData() {
        return mCellularRawDataBuilder.build();
    }

    /**
     * Return whether LTE Carrier Aggregation is used or not
     */
    public synchronized boolean isLteCa() {
        return mIsLteCa;
    }

    /**
     * Return downlink cell bandwidth of LTE
     */
    public synchronized int getLteCellBandwidthDownlinkKhz() {
        return mLteCellBandwidthDownlinkKhz;
    }

    /**
     * Default network callback
     */
    private final NetworkCallback mNetworkCallback = new NetworkCallback() {
        @Override
        public void onCapabilitiesChanged(@NonNull Network network,
                @NonNull NetworkCapabilities networkCapabilities) {
            super.onCapabilitiesChanged(network, networkCapabilities);
            synchronized (CellularDataCollector.this) {
                if (!mStarted) return;
                if (networkCapabilities.hasTransport(NetworkCapabilities.TRANSPORT_CELLULAR)) {
                    mCellularRawDataBuilder.networkCapabilities(networkCapabilities);
                } else {
                    mCellularRawDataBuilder.networkCapabilities(null);
                }
            }
        }
    };

    private final TelephonyCallback mTelephonyCallback = new CellularDataCollectorCallback();

    /**
     * Telephony callback to collect cellular data
     */
    private class CellularDataCollectorCallback extends TelephonyCallback implements
            TelephonyCallback.SignalStrengthsListener,
            TelephonyCallback.PhysicalChannelConfigListener {

        @Override
        public void onSignalStrengthsChanged(SignalStrength signalStrength) {
            synchronized (CellularDataCollector.this) {
                if (!mStarted) return;

                // Get CellSignalStrength List from SignalStrength
                List<CellSignalStrength> cssList = signalStrength.getCellSignalStrengths();
                Log.v(TAG, "onSignalStrengthsChanged: css list size: " + cssList.size());
                CellSignalStrengthLte cssLte = null;
                CellSignalStrengthNr cssNr = null;
                // Extract and Update CellSignalStrength
                for (CellSignalStrength css : cssList) {
                    Log.v(TAG, "onSignalStrengthsChanged: " + css.toString());
                    if (css instanceof CellSignalStrengthLte && cssLte == null) {
                        cssLte = (CellSignalStrengthLte) css;
                    } else if (css instanceof CellSignalStrengthNr && cssNr == null) {
                        cssNr = (CellSignalStrengthNr) css;
                    }
                }
                mCellularRawDataBuilder.cellSignalStrengthLte(cssLte);
                mCellularRawDataBuilder.cellSignalStrengthNr(cssNr);
            }
        }

        @Override
        public void onPhysicalChannelConfigChanged(List<PhysicalChannelConfig> pccList) {
            synchronized (CellularDataCollector.this) {
                if (!mStarted) return;

                Log.v(TAG, "onPhysicalChannelConfigChanged: pcc list size: " + pccList.size());
                boolean isLteCa = false;
                int lteCellBandwidthDownlinkKhz = Integer.MAX_VALUE;
                for (PhysicalChannelConfig pcc : pccList) {
                    Log.v(TAG, "onPhysicalChannelConfigChanged: " + pcc.toString());
                    int networkType = pcc.getNetworkType();
                    if (networkType == TelephonyManager.NETWORK_TYPE_LTE_CA && !isLteCa) {
                        isLteCa = true;
                    }
                    if (pcc.getConnectionStatus()
                            == PhysicalChannelConfig.CONNECTION_PRIMARY_SERVING && (
                            networkType == TelephonyManager.NETWORK_TYPE_LTE
                                    || networkType == TelephonyManager.NETWORK_TYPE_LTE_CA)) {
                        int cellbandwidth = pcc.getCellBandwidthDownlinkKhz();
                        if (cellbandwidth > 0) {
                            lteCellBandwidthDownlinkKhz = cellbandwidth;
                        }
                    }
                }
                mIsLteCa = isLteCa;
                mLteCellBandwidthDownlinkKhz = lteCellBandwidthDownlinkKhz;
                Log.v(TAG, "onPhysicalChannelConfigChanged: CellBandwidthDownlinkKhz: "
                        + mLteCellBandwidthDownlinkKhz + ", CA: " + mIsLteCa);
            }
        }
    }

    public static class CellularRawData {
        private NetworkCapabilities mNetworkCapabilities;
        private CellSignalStrengthLte mCellSignalStrengthLte;
        private CellSignalStrengthNr mCellSignalStrengthNr;

        private CellularRawData(NetworkCapabilities networkCapabilities,
                CellSignalStrengthLte cellSignalStrengthLte,
                CellSignalStrengthNr cellSignalStrengthNr) {
            mNetworkCapabilities = networkCapabilities;
            mCellSignalStrengthLte = cellSignalStrengthLte;
            mCellSignalStrengthNr = cellSignalStrengthNr;
        }

        @Nullable
        public NetworkCapabilities getNetworkCapabilities() {
            return mNetworkCapabilities;
        }

        @Nullable
        public CellSignalStrengthLte getCellSignalStrengthLte() {
            return mCellSignalStrengthLte;
        }

        @Nullable
        public CellSignalStrengthNr getCellSignalStrengthNr() {
            return mCellSignalStrengthNr;
        }

        /**
         * Return a builder instance.
         */
        static Builder builder() {
            return new Builder();
        }

        /**
         * A builder class to construct {@link CellularRawData} instance.
         */
        static class Builder {
            private NetworkCapabilities mNetworkCapabilities;
            private CellSignalStrengthLte mCellSignalStrengthLte;
            private CellSignalStrengthNr mCellSignalStrengthNr;

            Builder networkCapabilities(NetworkCapabilities networkCapabilities) {
                mNetworkCapabilities = networkCapabilities;
                return this;
            }

            Builder cellSignalStrengthLte(CellSignalStrengthLte cellSignalStrengthLte) {
                mCellSignalStrengthLte = cellSignalStrengthLte;
                return this;
            }


            Builder cellSignalStrengthNr(CellSignalStrengthNr cellSignalStrengthNr) {
                mCellSignalStrengthNr = cellSignalStrengthNr;
                return this;
            }

            CellularRawData build() {
                return new CellularRawData(mNetworkCapabilities, mCellSignalStrengthLte,
                        mCellSignalStrengthNr);
            }
        }
    }
}
