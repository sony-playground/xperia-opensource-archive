/*
 * Copyright 2020, 2024 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.ext.cellular;

import static com.sonymobile.smartnetworkengine.ext.Constants.IDD_DAILY_UPLOAD_LIMIT_SIZE;
import static com.sonymobile.smartnetworkengine.ext.Constants.IDD_UPLOAD_LIMIT_PERIOD_MSEC;
import static com.sonymobile.smartnetworkengine.ext.Constants.THROUGHPUT_CHECK_OVER_THRESHOLD;
import static com.sonymobile.smartnetworkengine.ext.Constants.THROUGHPUT_CHECK_PERIOD;
import static com.sonymobile.smartnetworkengine.ext.Constants.THROUGHPUT_THRESHOLD;

import android.app.ActivityManager;
import android.app.IActivityManager;
import android.app.IProcessObserver;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.net.ConnectivityManager;
import android.net.ConnectivityManager.NetworkCallback;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.Uri;
import android.os.Message;
import android.os.PowerManager;
import android.os.RemoteException;
import android.telephony.AccessNetworkConstants;
import android.provider.Telephony;
import android.telephony.CellSignalStrengthLte;
import android.telephony.CellSignalStrengthNr;
import android.telephony.NetworkRegistrationInfo;
import android.telephony.ServiceState;
import android.telephony.SubscriptionManager;
import android.telephony.TelephonyCallback;
import android.telephony.TelephonyManager;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.android.internal.util.State;
import com.android.internal.util.StateMachine;

import com.sonyericsson.idd.api.Idd;
import com.sonyericsson.idd.probe.android.smartnetworkengine.CellularPredictionData.SneCarrierInfo;
import com.sonyericsson.idd.probe.android.smartnetworkengine.CellularPredictionData.SneCellIdentityLte;
import com.sonyericsson.idd.probe.android.smartnetworkengine.CellularPredictionData.SneCellIdentityNr;
import com.sonyericsson.idd.probe.android.smartnetworkengine.CellularPredictionData.SneCellInfo;
import com.sonyericsson.idd.probe.android.smartnetworkengine.CellularPredictionData.SneCellInfoLte;
import com.sonyericsson.idd.probe.android.smartnetworkengine.CellularPredictionData.SneCellInfoNr;
import com.sonyericsson.idd.probe.android.smartnetworkengine.CellularPredictionData.SneCellularEvent;
import com.sonyericsson.idd.probe.android.smartnetworkengine.CellularPredictionData.SneCellularSample;
import com.sonyericsson.idd.probe.android.smartnetworkengine.CellularPredictionData.SneCellularSample.NetworkType;
import com.sonyericsson.idd.probe.android.smartnetworkengine.CellularPredictionData.SneCellularTrafficStats;
import com.sonyericsson.idd.probe.android.smartnetworkengine.CellularPredictionData.SneSignalStrengthLte;
import com.sonyericsson.idd.probe.android.smartnetworkengine.CellularPredictionData.SneSignalStrengthNr;
import com.sonymobile.smartnetworkengine.ext.PreferenceAccessor;
import com.sonymobile.smartnetworkengine.ext.R;
import com.sonymobile.smartnetworkengine.ext.cellular.collector.CellularDataCollector;
import com.sonymobile.smartnetworkengine.ext.cellular.collector.CellularDataCollector.CellularRawData;
import com.sonymobile.smartnetworkengine.ext.cellular.collector.TrafficStatsCollector;
import com.sonymobile.smartnetworkengine.ext.util.AccessNetworkUtils;
import com.sonymobile.smartnetworkengine.ext.util.Log;

import java.util.Collections;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

/**
 * StateMachine which implements logging function for cellular data.
 */
public class CellularLogger extends StateMachine {

    private static final String TAG = CellularLogger.class.getSimpleName();

    /**
     * Version of Cellular Logger
     */
    private static final String CELLULAR_LOGGER_VERSION = "2.1.4";
    /**
     * Logging interval time to collect sequential cellular data
     */
    private static final int LOGGING_INTERVAL_SEC = 1;
    /**
     * Size of Logging queue to store Cellular data
     */
    private static final int LOGGING_QUEUE_SIZE = THROUGHPUT_CHECK_PERIOD;

    private static final int STATE_MACHINE_QUIT_TIMEOUT_SEC = 3;

    // Messages which are handled by state machine.
    private static final int MSG_IDD_SIZE_CHECK_TRIGGER = 1;
    private static final int MSG_SCREEN_STATE_CHANGED = 2;
    private static final int MSG_APPLICATION_FOREGROUND_CHANGED = 3;
    private static final int MSG_DEFAULT_NETWORK_CHANGED = 4;
    private static final int MSG_CELLULAR_SERVICE_STATE_CHANGED = 5;
    private static final int MSG_PERIODIC_LOGGING_TRIGGER = 6;

    // States defined in state machine.
    // <Hierarchy>
    // DefaultState -> *IddSizeCheckState (initial)
    //              -> LoggingActiveState -> *LoggingStandbyState
    //                                    -> *LoggingEnabledState
    // NOTE: 3 states with '*' are directly transitioned to from another state.
    // Other 2 states are not directly transitioned to, but will be active when child is active.
    /**
     * Default parent state
     */
    private final State mDefaultState = new DefaultState();
    /**
     * Idd upload size check state.
     */
    private final State mIddSizeCheckState = new IddSizeCheckState();
    /**
     * Parent state for 2 logging states
     */
    private final State mLoggingActiveState = new LoggingActiveState();
    /**
     * Logging condition check state
     */
    private final State mLoggingStandbyState = new LoggingStandbyState();
    /**
     * Logging state (every second logging)
     */
    private final State mLoggingEnabledState = new LoggingEnabledState();

    private final CountDownLatch mQuitLatch = new CountDownLatch(1);

    private final Context mContext;

    private final Map<String, Integer> mAppNameUidMap = new HashMap<>();
    /**
     * Package name of foreground application
     */
    private String mAppPackageName;

    /**
     * global network type and nr state, shared using in several states.
     */
    private NetworkType mNetworkType = NetworkType.UNKNOWN;
    private int mNrState;

    private int mDataSubId;
    private int mNrFrequencyRange = -1;

    public CellularLogger(@NonNull Context context) {
        super(TAG);
        mContext = context;

        for (String name : context.getResources().getStringArray(R.array.package_names)) {
            mAppNameUidMap.put(name, getUidFromPackageName(name));
            Log.v(TAG, name + ": " + mAppNameUidMap.get(name));
        }

        //@formatter:off
        addState(mDefaultState);
            addState(mIddSizeCheckState, mDefaultState);
            addState(mLoggingActiveState, mDefaultState);
                addState(mLoggingStandbyState, mLoggingActiveState);
                addState(mLoggingEnabledState, mLoggingActiveState);
        setInitialState(mIddSizeCheckState);
        //@formatter:on
    }

    /**
     * Quit the state machine synchronously.
     */
    public void quitSync() {
        quitNow();
        try {
            if (!mQuitLatch.await(STATE_MACHINE_QUIT_TIMEOUT_SEC, TimeUnit.SECONDS)) {
                Log.w(TAG, "Timeout occurs while awaiting the state machine quit");
            }
        } catch (InterruptedException e) {
            Log.w(TAG, "Interrupted while awaiting the state machine quit: " + e);
        }
    }

    @Override
    protected void onQuitting() {
        Log.i(TAG, "Stopping the state machine");
        mQuitLatch.countDown();
    }

    private class DefaultState extends State {
        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
        }

        @Override
        public boolean processMessage(Message message) {
            Log.i(TAG, "Unhandled message received:" + message.what);
            return HANDLED;
        }
    }

    private class IddSizeCheckState extends State {
        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            sendMessage(MSG_IDD_SIZE_CHECK_TRIGGER);
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message:" + message.what);
            switch (message.what) {
                case MSG_IDD_SIZE_CHECK_TRIGGER:
                    long timeTolimitEnd = getIddUploadLimitEnd(System.currentTimeMillis());
                    if (timeTolimitEnd <= 0) {
                        transitionTo(mLoggingStandbyState);
                    } else {
                        sendMessageDelayed(MSG_IDD_SIZE_CHECK_TRIGGER, timeTolimitEnd);
                    }
                    break;
                default:
                    return NOT_HANDLED;
            }
            return HANDLED;
        }
    }

    /**
     * Check logging conditions and transition to LoggingEnabledState when fulfilled.
     */
    private class LoggingActiveState extends State {
        private ConnectivityManager mConnectivityManager;
        private ActivityManager mActivityManager;
        private IActivityManager mIActivityManager;
        private TelephonyManager mTelephonyManager;

        private boolean mScreenOn;
        private boolean mCellularDefault;

        /**
         * Broadcast receiver for screen state
         */
        private final BroadcastReceiver mScreenStateReceiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                final String action = intent.getAction();
                if (action.equals(Intent.ACTION_SCREEN_ON)) {
                    sendMessage(MSG_SCREEN_STATE_CHANGED, 1);
                } else if (action.equals(Intent.ACTION_SCREEN_OFF)) {
                    sendMessage(MSG_SCREEN_STATE_CHANGED, 0);
                }
            }
        };

        /**
         * Foreground app observer to detect if target application is foreground or not
         */
        private final IProcessObserver.Stub mProcessObserver = new IProcessObserver.Stub() {
            @Override
            public void onForegroundActivitiesChanged(int pid, int uid, boolean fg) {
                // Send message only if fg is true
                if (fg) {
                    String appPackageName = "";
                    for (Map.Entry<String, Integer> entry : mAppNameUidMap.entrySet()) {
                        if (entry.getValue() == uid) {
                            appPackageName = entry.getKey();
                        }
                    }
                    sendMessage(MSG_APPLICATION_FOREGROUND_CHANGED, appPackageName);
                }
            }

            @Override
            public void onForegroundServicesChanged(int pid, int uid, int fgServiceTypes) {
                // do nothing
            }

            @Override
            public void onProcessDied(final int pid, final int uid) {
                // do nothing
            }

            @Override
            public void onProcessStarted(int pid, int processUid, int packageUid,
                    String packageName, String processName) {
                // do nothing
            }
        };

        /**
         * Default network callback
         */
        private final NetworkCallback mNetworkCallback = new NetworkCallback() {
            @Override
            public void onAvailable(Network network) {
                super.onAvailable(network);
                sendMessage(MSG_DEFAULT_NETWORK_CHANGED, 1, 0/*unused*/, network);
            }

            /** Handle switch from cell to no default network (both WiFi and Cellular disabled) */
            @Override
            public void onLost(Network network) {
                super.onLost(network);
                sendMessage(MSG_DEFAULT_NETWORK_CHANGED, 0, 0/*unused*/, network);
            }
        };

        private final TelephonyCallback mTelephonyCallback = new CellularLoggerCallback();

        /**
         * Callback to check cellular connection including RAT type
         */
        private class CellularLoggerCallback extends TelephonyCallback implements
                TelephonyCallback.ServiceStateListener {

            @Override
            public void onServiceStateChanged(ServiceState serviceState) {
                NetworkRegistrationInfo regInfo = serviceState.getNetworkRegistrationInfo(
                        NetworkRegistrationInfo.DOMAIN_PS,
                        AccessNetworkConstants.TRANSPORT_TYPE_WWAN);
                NetworkType networkType = NetworkType.UNKNOWN;
                mNrFrequencyRange = -1;
                // update current network type
                if (regInfo != null) {
                    Log.v(TAG, "onServiceStateChanged: telephony network type: "
                            + regInfo.getAccessNetworkTechnology() + ", nr state: "
                            + regInfo.getNrState());
                    mNrState = regInfo.getNrState();
                    switch (regInfo.getAccessNetworkTechnology()) {
                        case TelephonyManager.NETWORK_TYPE_LTE:
                            switch (regInfo.getNrState()) {
                                case NetworkRegistrationInfo.NR_STATE_CONNECTED:
                                case NetworkRegistrationInfo.NR_STATE_NOT_RESTRICTED:
                                    networkType = NetworkType.LTE_NR;
                                    break;
                                default:
                                    networkType = NetworkType.LTE;
                                    break;
                            }
                            break;
                        case TelephonyManager.NETWORK_TYPE_NR:
                            networkType = NetworkType.NR;
                            int chNumber = serviceState.getChannelNumber();
                            mNrFrequencyRange = AccessNetworkUtils.getFrequencyRangeGroupFromNrBand(
                                    AccessNetworkUtils.getOperatingBandForNrarfcn(chNumber));
                            Log.v(TAG, "onServiceStateChanged chNumber = " + chNumber
                                    + " nrFrequencyRange = "
                                    + serviceState.frequencyRangeToString(mNrFrequencyRange));
                            break;
                        default:
                            break;
                    }
                }
                sendMessage(MSG_CELLULAR_SERVICE_STATE_CHANGED, networkType.getNumber());
            }
        }

        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");

            PowerManager pm = (PowerManager) mContext.getSystemService(Context.POWER_SERVICE);
            mConnectivityManager = (ConnectivityManager) mContext.getSystemService(
                    Context.CONNECTIVITY_SERVICE);
            mActivityManager = (ActivityManager) mContext.getSystemService(
                    Context.ACTIVITY_SERVICE);
            mIActivityManager = ActivityManager.getService();

            // For checking default data subscription id changed
            mDataSubId = SubscriptionManager.getDefaultDataSubscriptionId();
            mTelephonyManager = ((TelephonyManager) mContext.getSystemService(
                    Context.TELEPHONY_SERVICE)).createForSubscriptionId(mDataSubId);
            mTelephonyManager.registerTelephonyCallback(
                    mContext.getMainExecutor(), mTelephonyCallback);

            // For screen check
            mScreenOn = pm.isInteractive(); // need initial value
            IntentFilter intentFilter = new IntentFilter();
            intentFilter.addAction(Intent.ACTION_SCREEN_ON);
            intentFilter.addAction(Intent.ACTION_SCREEN_OFF);
            mContext.registerReceiver(mScreenStateReceiver, intentFilter);

            // For cellular default check
            mCellularDefault = false;
            mConnectivityManager.registerDefaultNetworkCallback(mNetworkCallback);

            // For target application foreground check
            if (Collections.frequency(mAppNameUidMap.values(), -1) == mAppNameUidMap.size()) {
                Log.w(TAG, "Cannot get uid of any target applications. Quit StateMachine.");
                quit(); // finish StateMachine gracefully.
            }
            // NOTE: IProcessObserver does not notify callback upon registration, but we decided to
            // avoid initial foreground check for edge case from simplicity/efficiency perspective.
            registerForegroundAppObserver();
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message:" + message.what);
            switch (message.what) {
                case MSG_SCREEN_STATE_CHANGED:
                    boolean screenOn = (message.arg1 == 1);
                    if (screenOn != mScreenOn) {
                        mScreenOn = screenOn;
                        transitionByLoggingCondition();
                    }
                    break;
                case MSG_APPLICATION_FOREGROUND_CHANGED:
                    String appPackageName = (String) message.obj;
                    if (!appPackageName.equals(mAppPackageName)) {
                        mAppPackageName = appPackageName;
                        transitionByLoggingCondition();
                    }
                    break;
                case MSG_DEFAULT_NETWORK_CHANGED:
                    Network network = (Network) message.obj;
                    NetworkCapabilities nc = mConnectivityManager.getNetworkCapabilities(network);
                    if (nc != null) {
                        boolean available = (message.arg1 == 1);
                        boolean cell = nc.hasTransport(NetworkCapabilities.TRANSPORT_CELLULAR);
                        boolean cellularDefault = (available && cell);
                        if (cellularDefault != mCellularDefault) {
                            mCellularDefault = cellularDefault;
                            transitionByLoggingCondition();
                        }
                    }
                    int dataSubId = SubscriptionManager.getDefaultDataSubscriptionId();
                    if (mDataSubId != dataSubId) {
                        mDataSubId = dataSubId;
                        transitionByLoggingCondition();
                    }
                    break;
                case MSG_CELLULAR_SERVICE_STATE_CHANGED:
                    NetworkType networkType = NetworkType.valueOf(message.arg1);
                    if (mNetworkType != networkType) {
                        mNetworkType = networkType;
                        transitionByLoggingCondition();
                    }
                    break;
                default:
                    return NOT_HANDLED;
            }

            return HANDLED;
        }

        @Override
        public void exit() {
            Log.v(TAG, getName() + " exited");
            mContext.unregisterReceiver(mScreenStateReceiver);
            mConnectivityManager.unregisterNetworkCallback(mNetworkCallback);
            unregisterForegroundAppObserver();
            mTelephonyManager.unregisterTelephonyCallback(mTelephonyCallback);
        }

        private boolean isAppValid(String appPackageName) {
            return appPackageName != null && !appPackageName.equals("");
        }

        private void transitionByLoggingCondition() {
            Log.v(TAG, "Screen:" + mScreenOn + ", Cellular:" + mCellularDefault
                    + ", Network Type:" + mNetworkType + ", App:" + mAppPackageName);

            boolean loggingConditionSatisfied = (mScreenOn && mCellularDefault
                    && mNetworkType != NetworkType.UNKNOWN && isAppValid(mAppPackageName));

            if (loggingConditionSatisfied) {
                transitionTo(mLoggingEnabledState);
            } else {
                transitionTo(mLoggingStandbyState);
            }
        }

        private void registerForegroundAppObserver() {
            try {
                mIActivityManager.registerProcessObserver(mProcessObserver);
            } catch (RemoteException e) {
                Log.w(TAG, "can not unregister processObserver");
            }
        }

        private void unregisterForegroundAppObserver() {
            try {
                mIActivityManager.unregisterProcessObserver(mProcessObserver);
            } catch (RemoteException e) {
                Log.w(TAG, "can not unregister processObserver");
            }
        }
    }

    /**
     * Logging condition check state.
     * NOTE: As kind of tricky implementation of android StateMachine, transition from child to
     * parent state causes exit of parent. To avoid it, this empty placeholder state is needed.
     */
    private class LoggingStandbyState extends State {
        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
        }

        @Override
        public void exit() {
            Log.v(TAG, getName() + " exited");
        }
    }

    private class LoggingEnabledState extends State {
        private final ThroughputChecker mThroughputChecker = new ThroughputChecker(
                THROUGHPUT_CHECK_PERIOD,
                THROUGHPUT_CHECK_OVER_THRESHOLD,
                THROUGHPUT_THRESHOLD * LOGGING_INTERVAL_SEC);
        private final TrafficStatsCollector mTrafficStatsCollector = new TrafficStatsCollector();
        private final Queue<SneCellularSample> mSneCellularSampleQueue = new LinkedList<>();
        private CellularDataCollector mCellularDataCollector;

        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            reset();
            if (mCellularDataCollector == null) {
                mCellularDataCollector = new CellularDataCollector(mContext);
            }
            mCellularDataCollector.start();
            sendMessage(MSG_PERIODIC_LOGGING_TRIGGER);
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message:" + message.what);
            switch (message.what) {
                case MSG_PERIODIC_LOGGING_TRIGGER:
                    mTrafficStatsCollector.update();
                    long mobileRxBytes = mTrafficStatsCollector.getMobileRxBytesDiff();
                    long mobileTxBytes = mTrafficStatsCollector.getMobileTxBytesDiff();
                    int mobileRxKbps = (int) mobileRxBytes / 1000 * 8;
                    int mobileTxKbps = (int) mobileTxBytes / 1000 * 8;
                    Log.v(TAG, "mobileRxKbps = " + mobileRxKbps);
                    Log.v(TAG, "mobileTxKbps = " + mobileTxKbps);

                    // Check mSneCellularSampleQueue size, remove head when queue is full.
                    if (mSneCellularSampleQueue.size() == LOGGING_QUEUE_SIZE) {
                        mSneCellularSampleQueue.poll();
                    }

                    CellularRawData cellularRawData = mCellularDataCollector.getCellularRawData();
                    SneCellularSample sneCellularSample = buildSneCellularSample(
                            mNetworkType,
                            mNrState,
                            mobileTxKbps,
                            mobileRxKbps,
                            cellularRawData.getNetworkCapabilities(),
                            cellularRawData.getCellSignalStrengthLte(),
                            cellularRawData.getCellSignalStrengthNr(),
                            mCellularDataCollector.getLteCellBandwidthDownlinkKhz(),
                            mCellularDataCollector.isLteCa(),
                            mNrFrequencyRange);

                    // Add New sneCellularSample to Queue
                    mSneCellularSampleQueue.offer(sneCellularSample);

                    boolean triggerNextLogging = true;
                    boolean activeThroughput = mThroughputChecker.addSample(mobileRxBytes);
                    if (activeThroughput) {
                        Log.v(TAG, "Throughput check passed, send to IDD.");

                        // Send Cellular Data to IDD with Protocol Buffer
                        SneCellularEvent cellularEvent = SneCellularEvent.newBuilder()
                                .setLoggerVersion(CELLULAR_LOGGER_VERSION)
                                .setAppVersion(getAppVersionName())
                                .addAllCellularSamples(mSneCellularSampleQueue)
                                .setCarrierInfo(buildSneCarrierInfo())
                                .setApplicationPackageName(mAppPackageName)
                                .build();
                        Idd.addEvent(cellularEvent);
                        Log.v(TAG, "Logging data has been sent to IDD daemon");

                        // Calculate IDD upload size
                        int iddUploadSize = cellularEvent.getSerializedSize();
                        long currentTimeMillis = System.currentTimeMillis();
                        addIddUploadSize(currentTimeMillis, iddUploadSize);

                        if (getIddUploadLimitEnd(currentTimeMillis) == 0) {
                            // If there is no limitation, reset and continue logging within this
                            // state.
                            reset();
                        } else {
                            // If there is limitation, get back to idd size check.
                            transitionTo(mIddSizeCheckState);
                            triggerNextLogging = false;
                        }
                    }

                    if (triggerNextLogging) {
                        sendMessageDelayed(MSG_PERIODIC_LOGGING_TRIGGER,
                                LOGGING_INTERVAL_SEC * 1000);
                    }
                    break;
                default:
                    return NOT_HANDLED;
            }
            return HANDLED;
        }

        @Override
        public void exit() {
            Log.v(TAG, getName() + " exited");
            removeMessages(MSG_PERIODIC_LOGGING_TRIGGER);
            mCellularDataCollector.stop();
        }

        private void reset() {
            mThroughputChecker.reset();
            mTrafficStatsCollector.reset();
            mSneCellularSampleQueue.clear();
        }

        private SneCarrierInfo buildSneCarrierInfo() {
            String apnName = "";
            int carrierId = -1;
            String carrierIdName = "";
            Cursor cursor = null;
            try {
                Uri uri = Uri.withAppendedPath(
                        Uri.parse("content://telephony/carriers/preferapn_no_update/subId/"),
                        Integer.toString(mDataSubId));
                cursor = mContext.getContentResolver().query(uri, null, null, null,
                        Telephony.Carriers.DEFAULT_SORT_ORDER);
                if (cursor != null && cursor.getCount() > 0) {
                    cursor.moveToFirst();
                    apnName = cursor.getString(cursor.getColumnIndexOrThrow("apn"));
                    if (apnName == null) {
                        apnName = "";
                    }
                }
            } finally {
                if (cursor != null) {
                    cursor.close();
                }
            }
            TelephonyManager telephonyManager = ((TelephonyManager) mContext.getSystemService(
                    Context.TELEPHONY_SERVICE)).createForSubscriptionId(mDataSubId);
            carrierId = telephonyManager.getSimCarrierId();
            carrierIdName = (String) telephonyManager.getSimCarrierIdName();
            if (carrierIdName == null) {
                carrierIdName = "";
            }

            return SneCarrierInfo.newBuilder()
                    .setApnName(apnName)
                    .setCarrierId(carrierId)
                    .setCarrierName(carrierIdName)
                    .build();
        }

        private SneCellularSample buildSneCellularSample(
                NetworkType networkType, int nrState, int txThroughputKbps, int rxThroughputKbps,
                @Nullable NetworkCapabilities nc,
                @Nullable CellSignalStrengthLte cssLte, @Nullable CellSignalStrengthNr cssNr,
                int lteCellBandwidthDownlinkKhz, boolean isLteCa, int nrFrequencyRange) {

            SneCellularTrafficStats.Builder cellularTrafficStatsBuilder =
                    SneCellularTrafficStats.newBuilder()
                            .setTxThroughputKbps(txThroughputKbps)
                            .setRxThroughputKbps(rxThroughputKbps);
            if (nc != null) {
                cellularTrafficStatsBuilder.setTxBandwidthKbps(nc.getLinkUpstreamBandwidthKbps());
                cellularTrafficStatsBuilder.setRxBandwidthKbps(nc.getLinkDownstreamBandwidthKbps());
            }

            SneCellInfoLte.Builder cellInfoLteBuilder = SneCellInfoLte.newBuilder();
            SneCellIdentityLte.Builder sneCellIdentityLte = SneCellIdentityLte.newBuilder();
            sneCellIdentityLte.setBandwidth(lteCellBandwidthDownlinkKhz);
            cellInfoLteBuilder.setCellIdentityLte(sneCellIdentityLte);

            if (cssLte != null) {
                SneSignalStrengthLte sneSignalStrengthLte = SneSignalStrengthLte.newBuilder()
                        .setAsuLevel(cssLte.getAsuLevel())
                        .setCqi(cssLte.getCqi())
                        .setDbm(cssLte.getDbm())
                        .setLevel(cssLte.getLevel())
                        .setRsrp(cssLte.getRsrp())
                        .setRsrq(cssLte.getRsrq())
                        .setRssi(cssLte.getRssi())
                        .setRssnr(cssLte.getRssnr())
                        .setTimingAdvance(cssLte.getTimingAdvance())
                        .build();
                cellInfoLteBuilder.setSignalStrengthLte(sneSignalStrengthLte);
            }
            cellInfoLteBuilder.setCarrierAggregation(isLteCa);

            SneCellInfoNr.Builder cellInfoNrBuilder = SneCellInfoNr.newBuilder();
            if (cssNr != null) {
                SneSignalStrengthNr sneSignalStrengthNr = SneSignalStrengthNr.newBuilder()
                        .setAsuLevel(nrFrequencyRange) // Temporally using AsuLevel field
                        .setCsiRsrp(cssNr.getCsiRsrp())
                        .setCsiRsrq(cssNr.getCsiRsrq())
                        .setCsiSinr(cssNr.getCsiSinr())
                        .setLevel(cssNr.getLevel())
                        .setSsRsrp(cssNr.getSsRsrp())
                        .setSsRsrq(cssNr.getSsRsrq())
                        .setSsSinr(cssNr.getSsSinr())
                        .build();
                cellInfoNrBuilder.setSignalStrengthNr(sneSignalStrengthNr);
            }

            SneCellInfo cellInfo = SneCellInfo.newBuilder()
                    .setCellInfoLte(cellInfoLteBuilder.build())
                    .setCellInfoNr(cellInfoNrBuilder.build())
                    .build();

            return SneCellularSample.newBuilder()
                    .setNetworkType(networkType)
                    .setCellularTrafficStats(cellularTrafficStatsBuilder.build())
                    .setCellInfo(cellInfo)
                    .setNrState(nrState)
                    .build();
        }

        // TODO: "BuildConfig" generated by Gradle should be used instead.
        private String getAppVersionName() {
            String versionName = "";
            PackageManager packageManager = mContext.getPackageManager();
            try {
                PackageInfo packageInfo =
                        packageManager.getPackageInfo(mContext.getPackageName(), 0);
                versionName = packageInfo.versionName;
            } catch (PackageManager.NameNotFoundException e) {
                Log.w(TAG, "versionName is not found");
            }
            return versionName;
        }
    }

    private int getUidFromPackageName(String packageName) {
        int uid = -1;
        PackageManager packageManager = mContext.getPackageManager();
        for (ApplicationInfo appInfo : packageManager.getInstalledApplications(0)) {
            if (packageName.equals(appInfo.packageName)) {
                try {
                    uid = packageManager.getPackageUid(packageName, 0);
                } catch (PackageManager.NameNotFoundException e) {
                    Log.w(TAG, "package name not found: " + packageName);
                }
            }
        }
        return uid;
    }

    /**
     * Add IDD upload size to total size in SharedPreference.
     */
    private void addIddUploadSize(long currentTimeMillis, int size) {
        resetIddUploadLimit(currentTimeMillis);

        long orgSize = PreferenceAccessor.getDailyUpdateSize();
        long updateSize = orgSize + size;
        PreferenceAccessor.setDailyUpdateSize(updateSize);
        Log.v(TAG, "logging size: " + size + ", original total: " + orgSize
                + ", updated total: " + updateSize);
    }

    /**
     * Get IDD upload limitation end time. If no limitation, 0 is returned.
     */
    private long getIddUploadLimitEnd(long currentTimeMillis) {
        resetIddUploadLimit(currentTimeMillis);

        long size = PreferenceAccessor.getDailyUpdateSize();
        if (size < IDD_DAILY_UPLOAD_LIMIT_SIZE) {
            return 0; // no limitation
        }

        long limitEnd = PreferenceAccessor.getStartTime() + IDD_UPLOAD_LIMIT_PERIOD_MSEC;
        long timeToLimitEnd = limitEnd - currentTimeMillis;
        return timeToLimitEnd;
    }

    /**
     * Reset IDD upload limitation period and uploaded size.
     */
    private void resetIddUploadLimit(long currentTimeMillis) {
        long startTime = PreferenceAccessor.getStartTime();
        if (currentTimeMillis > startTime + IDD_UPLOAD_LIMIT_PERIOD_MSEC) {
            Log.v(TAG, "Reset IDD upload size and limitation period.");
            PreferenceAccessor.setStartTime(currentTimeMillis);
            PreferenceAccessor.setDailyUpdateSize(0);
        }
    }
}
