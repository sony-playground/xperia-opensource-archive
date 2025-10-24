/*
 * Copyright 2020, 2021, 2022, 2023, 2024 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.entry;

import static com.sonymobile.smartnetworkengine.Constants.IDD_PROBE_WIFI_SELECTION;
import static com.sonymobile.smartnetworkengine.Constants.IDD_UPLOAD_LIMIT_PERIOD_MSEC;
import static com.sonymobile.smartnetworkengine.Constants.SETTINGS_SMARTNET_ENTRY_ENABLED;
import static com.sonymobile.smartnetworkengine.Constants.WIFI_SELECTION_LOGGER_IDD_DAILY_UPLOAD_LIMIT_SIZE;
import static com.sonymobile.smartnetworkengine.entry.EntryPreferenceAccessor.KEY_LOGGER_DAILY_UPDATE_SIZE;
import static com.sonymobile.smartnetworkengine.entry.EntryPreferenceAccessor.KEY_LOGGER_START_TIME;
import static com.sonymobile.smartnetworkengine.entry.SneEntryScore.JudgeResult.INFERENCE_IGNORED;
import static com.sonymobile.smartnetworkengine.entry.SneEntryScore.JudgeResult.KEEP_NON_WIFI;
import static com.sonymobile.smartnetworkengine.entry.SneEntryScore.JudgeResult.SWITCH_TO_WIFI;
import static com.sonymobile.smartnetworkengine.fls.FLSystemManager.FEATURE_ENTRY;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.database.ContentObserver;
import android.net.ConnectivityManager;
import android.net.ConnectivityManager.NetworkCallback;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkInfo;
import android.net.NetworkRequest;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.provider.Settings;
import android.telephony.ServiceState;
import android.telephony.SubscriptionManager;
import android.telephony.TelephonyCallback;
import android.telephony.TelephonyManager;
import android.util.SparseArray;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.android.internal.util.MessageUtils;
import com.android.internal.util.State;
import com.android.internal.util.StateMachine;

import com.google.common.cache.Cache;
import com.google.common.cache.CacheBuilder;
import com.sonyericsson.idd.api.Idd;
import com.sonymobile.smartnetworkengine.DefaultNetworkController;
import com.sonymobile.smartnetworkengine.R;
import com.sonymobile.smartnetworkengine.SneApplication;
import com.sonymobile.smartnetworkengine.SneUtils;
import com.sonymobile.smartnetworkengine.WifiExtController;
import com.sonymobile.smartnetworkengine.WifiExtController.StaStaConcurrencyListener;
import com.sonymobile.smartnetworkengine.entry.SneEntryScore.JudgeResult;
import com.sonymobile.smartnetworkengine.entry.logger.WifiSelectionLogger;
import com.sonymobile.smartnetworkengine.fls.FLSystemManager;
import com.sonymobile.smartnetworkengine.fls.FLSystemManager.FLFeatureStatus;
import com.sonymobile.smartnetworkengine.fls.FLSystemManager.FLSystemStatus;
import com.sonymobile.smartnetworkengine.fls.FLSystemManager.FLSystemStatusListener;
import com.sonymobile.smartnetworkengine.fls.Predictor;
import com.sonymobile.smartnetworkengine.fls.Predictor.PredictionResult;
import com.sonymobile.smartnetworkengine.fls.data.FLTrainingDataAccessor.DataSet;
import com.sonymobile.smartnetworkengine.ui.NotificationEventReceiver;
import com.sonymobile.smartnetworkengine.ui.NotificationEventReceiver.NotificationEventListener;
import com.sonymobile.smartnetworkengine.ui.NotificationUtil;
import com.sonymobile.smartnetworkengine.util.HomeNetworkDetector;
import com.sonymobile.smartnetworkengine.util.Log;
import com.sonymobile.smartnetworkengine.util.WifiChecker;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.FileDescriptor;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;
import java.util.Optional;
import java.util.Set;
import java.util.concurrent.TimeUnit;
import java.util.function.Predicate;

/**
 * This class controls logger, predictor etc for entry wifi quality.
 */
public class EntryPhaseManager extends StateMachine {

    private static final String TAG = EntryPhaseManager.class.getSimpleName();

    private static final long DURATION_TO_WIFI_DISCONNECTION = TimeUnit.SECONDS.toMillis(28);

    // Note: this duration is used for fail safe in case that inference result does not come in any
    // reason. EntryPhaseManager waits for this period after wifi validation, and if a inference
    // hasn't been completed, it switches to Wi-Fi.
    private static final long DURATION_ENFORCE_SWITCH_TO_WIFI = TimeUnit.SECONDS.toMillis(3);

    // Message what to string mapping (for message logging)
    private static final SparseArray<String> WHAT_TO_STRING = MessageUtils.findMessageNames(
            new Class[]{EntryPhaseManager.class}, new String[]{"MSG_"});

    // Event messages handled by the state machine
    /** Event: FLS status(killed or not, prediction on/off) changed */
    private static final int MSG_FLS_STATUS_CHANGED = 11;
    /** Event: Entry feature setting(on/off) changed */
    private static final int MSG_ENTRY_SETTING_CHANGED = 12;
    /** Event: Roaming setting changed */
    private static final int MSG_ROAMING_SETTING_CHANGED = 13;
    /** Event: STA+STA Concurrency status changed */
    private static final int MSG_STASTA_CONCURRENCY_STATUS_CHANGED = 14;
    /** Event: Subscriptions changed */
    private static final int MSG_SUBSCRIPTIONS_CHANGED = 15;
    /** Event: Wifi connected */
    private static final int MSG_WIFI_CONNECTED = 16;
    /** Event: Wifi disconnected */
    private static final int MSG_WIFI_DISCONNECTED = 17;
    /** Event: Logger started or stopped */
    private static final int MSG_LOGGER_STATUS_CHANGED = 18;
    /** Event: Loggable data collected by the logger */
    private static final int MSG_LOGGER_DATA_LOGGED = 19;
    /** Event: Inference completed */
    private static final int MSG_LOGGER_INFERENCE_DONE = 20;

    // For the enabled and child states
    /** Event: Default network switched to wifi (for internal use only) */
    private static final int MSG_WIFI_DEFAULT_NETWORK_PRE_AVAILABLE = 21;
    /** Event: Default network switched to wifi */
    private static final int MSG_WIFI_DEFAULT_NETWORK_AVAILABLE = 22;
    /** Event: Default network switched to non-wifi */
    private static final int MSG_WIFI_DEFAULT_NETWORK_LOST = 23;

    // For the normal state
    /** Event: Screen On */
    private static final int MSG_SCREEN_ON = 31;
    /** Event: Trigger to disconnect current wifi connection */
    private static final int MSG_WIFI_DISCONNECT_TRIGGER = 32;
    /** Event: Connect anyway tapped on UI */
    private static final int MSG_CONNECT_ANYWAY_TAPPED = 33;
    /** Event: Captive portal detected for wifi */
    private static final int MSG_CAPTIVE_PORTAL_DETECTED = 34;
    /** Event: Trigger to switch to wifi for fail safe */
    private static final int MSG_ENFORCE_SWITCH_TO_WIFI_TRIGGER = 35;

    // For the disabled state
    /** Event: Trigger to check feature enabled */
    private static final int MSG_ENABLED_CHECK_TRIGGER = 41;

    /** State: Top parent state */
    private final State mDefaultState = new DefaultState();
    /** State: Enabled all functions (parent state of the other 4 states) */
    private final State mEnabledState = new EnabledState();
    /** State: Normal state for prediction and sequential-training */
    private final State mNormalState = new NormalState();
    /** State: Disabled all functions except IDD logging */
    private final State mDisabledState = new DisabledState();

    private final Context mContext;

    private final Handler mEntryHandler;

    private final ConnectivityManager mConnectivityManager;

    private final WifiManager mWifiManager;

    @NonNull
    private final FLSystemManager mFLSystemManager;

    private final WifiExtController mWifiExtController;

    private final SneEntryScore mSneEntryScore;

    private final WifiSelectionLogger mWifiSelectionLogger;

    private final NotificationUtil mNotificationUtil;

    private /*final*/ TelephonyManager mTelephonyManager;

    private final SubscriptionManager mSubscriptionManager;

    private final Predictor mPredictor;

    @Nullable
    private WifiConfiguration mCurrentWifiConfig;

    public EntryPhaseManager(@NonNull Context context,
            @NonNull DefaultNetworkController defaultNetworkController) {
        super(TAG);
        mContext = context;
        // Create a handler which is associated to the thread created by StateMachine
        Looper entryLooper = getHandler().getLooper();
        mEntryHandler = new Handler(entryLooper);
        // Obtain system services
        mConnectivityManager = (ConnectivityManager) context.getSystemService(
                Context.CONNECTIVITY_SERVICE);
        mWifiManager = (WifiManager) context.getSystemService(Context.WIFI_SERVICE);
        // Initialize default network switch related components
        mSneEntryScore = new SneEntryScore(mContext, defaultNetworkController);
        // Initialize other components
        mFLSystemManager = ((SneApplication) context.getApplicationContext()).getFLSystemManager();
        mWifiExtController = ((SneApplication) context.getApplicationContext())
                .getWifiExtController();
        mWifiSelectionLogger = new WifiSelectionLogger(mContext);
        mNotificationUtil = new NotificationUtil(mContext);
        mPredictor = mFLSystemManager.getPredictor(FEATURE_ENTRY);
        mPredictor.setTrainingDataModifier(this::mapper);

        mTelephonyManager = (TelephonyManager) context.getSystemService(Context.TELEPHONY_SERVICE);
        mSubscriptionManager = (SubscriptionManager) context.getSystemService(
                Context.TELEPHONY_SUBSCRIPTION_SERVICE);

        //@formatter:off
        addState(mDefaultState);
            addState(mEnabledState, mDefaultState);
                addState(mNormalState, mEnabledState);
            addState(mDisabledState, mDefaultState);
        //@formatter:on
        setInitialState(mDisabledState);

        // For state machine logging
        setLogRecSize(100);
        setLogOnlyTransitions(false);
    }

    @Override
    public void dump(FileDescriptor fd, PrintWriter writer, String[] args) {
        writer.println("\n<<< Entry >>>\n");
        // Dump the current state of the state machines
        super.dump(fd, writer, args);
        mSneEntryScore.dump(fd, writer, args);
    }

    @Override
    protected boolean recordLogRec(Message msg) {
        return Log.getLogLevel() == Log.Level.DEBUG;
    }

    @Override
    protected String getWhatToString(int what) {
        return WHAT_TO_STRING.get(what);
    }

    private class DefaultState extends State {

        /** Wifi connection/disconnection event receiver */
        private final BroadcastReceiver mWifiConnectionReceiver = new BroadcastReceiver() {
            private boolean mWifiConnected;

            @Override
            public void onReceive(Context context, Intent intent) {
                if (WifiManager.NETWORK_STATE_CHANGED_ACTION.equals(intent.getAction())) {
                    NetworkInfo networkInfo = (NetworkInfo) intent.getParcelableExtra(
                            WifiManager.EXTRA_NETWORK_INFO);
                    if (networkInfo != null) {
                        if (networkInfo.isConnected() && !mWifiConnected) {
                            mWifiConnected = true;
                            sendMessage(MSG_WIFI_CONNECTED);
                        } else if (!networkInfo.isConnected() && mWifiConnected) {
                            mWifiConnected = false;
                            sendMessage(MSG_WIFI_DISCONNECTED);
                        }
                    }
                }
            }
        };

        /** Logger event listener */
        private final WifiSelectionLogger.LoggerEventListener mLoggerEventListener =
                new WifiSelectionLogger.LoggerEventListener() {
                    @Override
                    public void onLoggingStatusChanged(boolean started) {
                        sendMessage(MSG_LOGGER_STATUS_CHANGED, started ? 1 : 0);
                    }

                    @Override
                    public void onDataLogged(PredictionResult predictionResult, float label,
                            JSONObject iddData) {
                        sendMessage(MSG_LOGGER_DATA_LOGGED,
                                List.of(predictionResult, label, iddData));
                    }

                    @Override
                    public void onInferenceDone(@Nullable PredictionResult predictionResult) {
                        Log.v(TAG, "Predictor#predict result: " + predictionResult);
                        sendMessage(MSG_LOGGER_INFERENCE_DONE, predictionResult);
                    }
                };

        /** FLS status(killed or not, prediction on/off) listener */
        private final FLSystemStatusListener mFLSystemStatusListener =
                status -> sendMessage(MSG_FLS_STATUS_CHANGED);

        /** Entry setting(on/off) observer */
        private final ContentObserver mSettingObserver = new ContentObserver(mEntryHandler) {
            @Override
            public void onChange(boolean selfChange) {
                sendMessage(MSG_ENTRY_SETTING_CHANGED);
            }
        };

        /** STA+STA Concurrency status listener */
        private final StaStaConcurrencyListener mStaStaConcurrencyListener =
                concurrent -> sendMessage(MSG_STASTA_CONCURRENCY_STATUS_CHANGED);

        /** Callback for checking mobile roaming state */
        private final TelephonyServiceStateCallback mTelephonyServiceStateCallback =
                new TelephonyServiceStateCallback();

        private class TelephonyServiceStateCallback extends TelephonyCallback implements
                TelephonyCallback.ServiceStateListener {
            private boolean mIsRoaming;

            @Override
            public void onServiceStateChanged(ServiceState serviceState) {
                boolean latest = (serviceState != null && serviceState.getRoaming());
                if (mIsRoaming != latest) {
                    sendMessage(MSG_ROAMING_SETTING_CHANGED);
                    mIsRoaming = latest;
                }
            }
        }

        /** OnSubscriptionsChangedListener for checking SIM settings changed */
        private final SubscriptionManager.OnSubscriptionsChangedListener
                mOnSubscriptionsChangedListener =
                new SubscriptionManager.OnSubscriptionsChangedListener() {
                    @Override
                    public void onSubscriptionsChanged() {
                        sendMessage(MSG_SUBSCRIPTIONS_CHANGED);
                    }
                };

        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            IntentFilter intentFilter = new IntentFilter(WifiManager.NETWORK_STATE_CHANGED_ACTION);
            mContext.registerReceiver(mWifiConnectionReceiver, intentFilter);
            mFLSystemManager.addSystemStatusListener(mFLSystemStatusListener, FEATURE_ENTRY);
            mContext.getContentResolver().registerContentObserver(
                    Settings.Global.getUriFor(SETTINGS_SMARTNET_ENTRY_ENABLED), false,
                    mSettingObserver);
            mWifiExtController.registerStaStaConcurrencyListener(mStaStaConcurrencyListener);
            // Note: the callback will be triggered once initially when calling this.
            mSubscriptionManager.addOnSubscriptionsChangedListener(mOnSubscriptionsChangedListener);
            mWifiSelectionLogger.setLoggerEventListener(mLoggerEventListener);
            mWifiSelectionLogger.start();
            mSneEntryScore.start();
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            switch (message.what) {
                case MSG_SUBSCRIPTIONS_CHANGED:
                    // Re-register callback with new TelephonyManager instance
                    // which may have a different subscription ID
                    mTelephonyManager.unregisterTelephonyCallback(mTelephonyServiceStateCallback);
                    mTelephonyManager = (TelephonyManager) mContext.getSystemService(
                            Context.TELEPHONY_SERVICE);
                    // Note: the callback will be triggered once initially when calling this.
                    mTelephonyManager.registerTelephonyCallback(mContext.getMainExecutor(),
                            mTelephonyServiceStateCallback);
                    break;
                case MSG_LOGGER_DATA_LOGGED:
                    if (getIddUploadLimitEnd(System.currentTimeMillis()) == 0) {
                        @SuppressWarnings("unchecked")
                        JSONObject iddUploadJson = (JSONObject) ((List<Object>) message.obj).get(2);
                        Idd.addAppDataJSON(IDD_PROBE_WIFI_SELECTION,
                                WifiSelectionLogger.LOGGER_VERSION, 0, iddUploadJson);
                        int jsonSize = iddUploadJson.toString()
                                .getBytes(StandardCharsets.UTF_8).length;
                        addIddUploadSize(System.currentTimeMillis(), jsonSize);
                    } else {
                        Log.v(TAG, "IDD limitation size is exceeded.");
                    }
                    break;
                default:
                    Log.v(TAG, "Unhandled message received: " + getWhatToString(message.what));
                    break;
            }
            return HANDLED;
        }

        @Override
        public void exit() {
            Log.v(TAG, getName() + " exited");
            mContext.unregisterReceiver(mWifiConnectionReceiver);
            mFLSystemManager.removeSystemStatusListener(mFLSystemStatusListener);
            mContext.getContentResolver().unregisterContentObserver(mSettingObserver);
            mWifiExtController.unregisterStaStaConcurrencyListener(mStaStaConcurrencyListener);
            mTelephonyManager.unregisterTelephonyCallback(mTelephonyServiceStateCallback);
            mSubscriptionManager.removeOnSubscriptionsChangedListener(
                    mOnSubscriptionsChangedListener);
            mWifiSelectionLogger.setLoggerEventListener(null);
            mWifiSelectionLogger.stop();
            mSneEntryScore.quit();
        }

        /**
         * Add IDD upload size to total size in SharedPreference.
         */
        private void addIddUploadSize(long currentTimeMillis, int size) {
            resetIddUploadLimitIfNeeded(currentTimeMillis);

            long orgSize = EntryPreferenceAccessor.getLoggerDailyUpdateSize();
            long updateSize = orgSize + size;
            EntryPreferenceAccessor.getSharedPreferences().edit()
                    .putLong(KEY_LOGGER_DAILY_UPDATE_SIZE, updateSize)
                    .apply();
            Log.v(TAG, "logging size: " + size + ", original total: " + orgSize
                    + ", updated total: " + updateSize);
        }

        /**
         * Get IDD upload limitation end time. If no limitation, 0 is returned.
         */
        private long getIddUploadLimitEnd(long currentTimeMillis) {
            resetIddUploadLimitIfNeeded(currentTimeMillis);

            long size = EntryPreferenceAccessor.getLoggerDailyUpdateSize();
            if (size < WIFI_SELECTION_LOGGER_IDD_DAILY_UPLOAD_LIMIT_SIZE) {
                return 0; // no limitation
            }

            long limitEnd = EntryPreferenceAccessor.getLoggerStartTime()
                    + IDD_UPLOAD_LIMIT_PERIOD_MSEC;
            return limitEnd - currentTimeMillis;
        }

        /**
         * Reset IDD upload limitation period and uploaded size.
         */
        private void resetIddUploadLimitIfNeeded(long currentTimeMillis) {
            long startTime = EntryPreferenceAccessor.getLoggerStartTime();
            if (currentTimeMillis > startTime + IDD_UPLOAD_LIMIT_PERIOD_MSEC) {
                Log.v(TAG, "Reset IDD upload size and limitation period.");
                EntryPreferenceAccessor.getSharedPreferences().edit()
                        .putLong(KEY_LOGGER_START_TIME, currentTimeMillis)
                        .remove(KEY_LOGGER_DAILY_UPDATE_SIZE)
                        .apply();
            }
        }
    }

    private class EnabledState extends State {
        private boolean mIsWifiDefaultNetwork;
        /**
         * This callback is mainly used to detect wifi connection event for upload/download
         * trigger. Needs to be placed at the enabled state to ensure |mCurrentWifiNetwork| is
         * always up to date at all child states.
         */
        private final NetworkCallback mDefaultNetworkCallback = new NetworkCallback() {
            @Override
            public void onCapabilitiesChanged(@NonNull Network network,
                    @NonNull NetworkCapabilities nc) {
                super.onCapabilitiesChanged(network, nc);
                if (nc.hasTransport(NetworkCapabilities.TRANSPORT_WIFI)
                        && nc.hasCapability(NetworkCapabilities.NET_CAPABILITY_VALIDATED)) {
                    if (!mIsWifiDefaultNetwork) {
                        mIsWifiDefaultNetwork = true;
                        sendMessage(MSG_WIFI_DEFAULT_NETWORK_PRE_AVAILABLE, network);
                    }
                } else {
                    if (mIsWifiDefaultNetwork) {
                        mIsWifiDefaultNetwork = false;
                        sendMessage(MSG_WIFI_DEFAULT_NETWORK_LOST);
                    }
                }
            }

            @Override
            public void onLost(@NonNull Network network) {
                super.onLost(network);
                if (mIsWifiDefaultNetwork) {
                    mIsWifiDefaultNetwork = false;
                    sendMessage(MSG_WIFI_DEFAULT_NETWORK_LOST);
                }
            }
        };

        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            // Tell FLS that we need you
            mFLSystemManager.setFeatureEnabled(FEATURE_ENTRY, true);

            // Register default network callback for upload/download sequence trigger
            mIsWifiDefaultNetwork = false;
            mConnectivityManager.registerDefaultNetworkCallback(mDefaultNetworkCallback);
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            boolean handleStatus = HANDLED;
            switch (message.what) {
                case MSG_FLS_STATUS_CHANGED:
                    if (!mFLSystemManager.getSystemStatus().isSystemEnabled()) {
                        transitionTo(mDisabledState);
                    }
                    break;
                case MSG_ENTRY_SETTING_CHANGED:
                    if (!SneUtils.isSmartNetworkEntrySettingsEnabled()) {
                        transitionTo(mDisabledState);
                    }
                    break;
                case MSG_ROAMING_SETTING_CHANGED:
                    ServiceState serviceState = mTelephonyManager.getServiceState();
                    if (serviceState != null && serviceState.getRoaming()) {
                        transitionTo(mDisabledState);
                    }
                    break;
                case MSG_STASTA_CONCURRENCY_STATUS_CHANGED:
                    // STA+STA Concurrency(especially MBB case) is not supported so disable the
                    // feature temporarily until the concurrent ends.
                    if (mWifiExtController.isStaStaConcurrent()) {
                        // Also stop the logger to avoid unexpected behaviors as the STA+STA
                        // concurrency is not considered in their implementation.
                        mWifiSelectionLogger.stop();
                        transitionTo(mDisabledState);
                    }
                    break;
                case MSG_WIFI_CONNECTED: {
                    // 6GHz Wi-Fi is not supported, the entry feature is disabled.
                    if (is6GHzWifiConnected() ||
                            WifiChecker.isMloConnection(mWifiManager.getConnectionInfo())) {
                        mWifiSelectionLogger.stop();
                        transitionTo(mDisabledState);
                    }
                    break;
                }
                case MSG_WIFI_DEFAULT_NETWORK_PRE_AVAILABLE: {
                    // Obtain a current wifi network configuration
                    mCurrentWifiConfig = getWifiConfiguration();
                    if (mCurrentWifiConfig == null) {
                        // Never happen?
                        break;
                    }
                    Log.v(TAG, "Usable wifi network available");
                    sendMessage(MSG_WIFI_DEFAULT_NETWORK_AVAILABLE);
                    break;
                }
                case MSG_WIFI_DEFAULT_NETWORK_LOST:
                    mCurrentWifiConfig = null;
                    break;
                default:
                    handleStatus = NOT_HANDLED;
                    break;
            }
            return handleStatus;
        }

        @Override
        public void exit() {
            Log.v(TAG, getName() + " exited");
            mFLSystemManager.setFeatureEnabled(FEATURE_ENTRY, false);
            mConnectivityManager.unregisterNetworkCallback(mDefaultNetworkCallback);
            mCurrentWifiConfig = null;
        }
    }

    private class NormalState extends State {
        /** Bit flags to be set in IDD data : for training data */
        private static final byte FL_TRAINING_DATA = 1; // 1 << 0

        /** Bit flags to be set in IDD data : for test data */
        private static final byte FL_TEST_DATA = 1 << 1; // Not used anymore

        /** Bit flags to be set in IDD data to indicate wifi roaming. */
        private static final byte FL_WIFI_ROAMING = 1 << 2;

        /** The list of blocked BSSIDs in current wifi session */
        private final Set<String> mBlockedBssids = new HashSet<>();

        /** The list of whitelisted Networks (Both key and value have same value - config key) */
        private final Cache<String, String> mNetworkWhiteList = CacheBuilder.newBuilder()
                .maximumSize(100)
                .expireAfterWrite(3, TimeUnit.HOURS)
                .build();

        /** The flag to show if captive portal is detected on current wifi session */
        private boolean mCaptivePortalDetected = false;

        /** The flag to show if network validation is completed or not */
        private boolean mWifiValidated = false;

        /** The flag to indicate whether data should be added to FLS as training data */
        private boolean mShouldStoreTrainingData = false;

        // Note: this interface method is invoked on both the internal thread in SneEntryScore
        // and the state machine thread here.
        private final Predicate<WifiConfiguration> mControlCondition = (wifiConfig) -> {
            if (wifiConfig != null) {
                // Home network check
                final boolean homeNetwork = HomeNetworkDetector.isHomeNetwork(mContext, wifiConfig);
                // Network whitelist check
                final boolean whiteListed = mNetworkWhiteList.getIfPresent(wifiConfig.getKey())
                        != null;
                // Explicitly selected check
                final boolean userSelected = mWifiExtController.isUserSelected();
                // True if it's ok to control default network by SneEntryScore
                final boolean okToControl = !homeNetwork && !whiteListed && !userSelected;
                Log.v(TAG, "Default network control condition -> " + (okToControl ? "OK" : "NG")
                        + " (homeNetwork: " + homeNetwork + ", whiteList: " + whiteListed
                        + ", userSelected: " + userSelected + ")");
                return okToControl;
            }
            return false;
        };

        /** This callback is used to check if captive portal is detected on current wifi session */
        private final NetworkCallback mWifiNetworkCallback = new NetworkCallback() {
            @Override
            public void onCapabilitiesChanged(@NonNull Network network,
                    @NonNull NetworkCapabilities nc) {
                super.onCapabilitiesChanged(network, nc);
                if (!mCaptivePortalDetected && nc.hasCapability(
                        NetworkCapabilities.NET_CAPABILITY_CAPTIVE_PORTAL)) {
                    mCaptivePortalDetected = true;
                    sendMessage(MSG_CAPTIVE_PORTAL_DETECTED);
                } else if (!mWifiValidated && nc.hasCapability(
                        NetworkCapabilities.NET_CAPABILITY_VALIDATED)) {
                    mWifiValidated = true;
                    sendMessageDelayed(MSG_ENFORCE_SWITCH_TO_WIFI_TRIGGER,
                            DURATION_ENFORCE_SWITCH_TO_WIFI);
                }
            }

            @Override
            public void onLost(@NonNull Network network) {
                super.onLost(network);
                mCaptivePortalDetected = false;
                mWifiValidated = false;
            }
        };

        /** This callback is used to detect screen on event for upload/download trigger */
        private final BroadcastReceiver mScreenOnReceiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                sendMessage(MSG_SCREEN_ON);
            }
        };

        /**
         * A listener for "CONNECT ANYWAY" is tapped
         */
        private final NotificationEventListener mNotificationEventListener = wifiConfig -> {
            Log.v(TAG, "CONNECT ANYWAY is clicked");
            sendMessage(MSG_CONNECT_ANYWAY_TAPPED, wifiConfig);
        };

        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            // Request to notify latest logging status for default network control on/off
            mWifiSelectionLogger.requestLoggingStatusUpdate();
            mWifiSelectionLogger.setPredictor(mPredictor);

            // Register wifi callback to detect captive portal and validated event.
            mCaptivePortalDetected = false;
            mWifiValidated = false;
            NetworkRequest wifiRequest = new NetworkRequest.Builder().addTransportType(
                    NetworkCapabilities.TRANSPORT_WIFI).build();
            mConnectivityManager.registerNetworkCallback(wifiRequest, mWifiNetworkCallback);
            // Set listener when a user taps "CONNECT ANYWAY" on a notification.
            NotificationEventReceiver.setNotificationEventListener(mNotificationEventListener);
            // Register screen event callback for upload/download sequence trigger
            mContext.registerReceiver(mScreenOnReceiver, new IntentFilter(Intent.ACTION_SCREEN_ON));
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            boolean handleStatus = HANDLED;
            switch (message.what) {
                case MSG_WIFI_CONNECTED:
                    // Should not be initialized upon wifi disconnection because it's accessed
                    // from MSG_LOGGER_DATA_LOGGED which may come after MSG_WIFI_DISCONNECTED.
                    mShouldStoreTrainingData = false;
                    // Allow parent state to perform similar initialization
                    handleStatus = NOT_HANDLED;
                    break;
                case MSG_WIFI_DISCONNECTED:
                    mBlockedBssids.clear();
                    mPredictor.reset();
                    endBlockingSection(false);
                    break;
                case MSG_WIFI_DISCONNECT_TRIGGER:
                    mWifiManager.disconnect();
                    break;
                case MSG_CONNECT_ANYWAY_TAPPED: {
                    WifiConfiguration wifiConfig = (WifiConfiguration) message.obj;
                    if (wifiConfig != null) { // Should never happen but just in case
                        // Add to the network whitelist
                        String configKey = wifiConfig.getKey();
                        mNetworkWhiteList.put(configKey, configKey /* any non-null value is ok */);
                        // Creating toast to show connecting AP
                        String ssid = WifiInfo.sanitizeSsid(wifiConfig.SSID);
                        Toast.makeText(mContext,
                                mContext.getString(R.string.smart_network_toast_connecting, ssid),
                                Toast.LENGTH_LONG).show();
                    }
                    endBlockingSection(true /* forceSwitchToWifi */);
                    // Close notification panel
                    mContext.sendBroadcast(new Intent(Intent.ACTION_CLOSE_SYSTEM_DIALOGS));
                    break;
                }
                case MSG_CAPTIVE_PORTAL_DETECTED:
                    Log.v(TAG, "captive portal detected, trigger force switch to wifi");
                    endBlockingSection(true /* forceSwitchToWifi */);
                    break;
                case MSG_ENFORCE_SWITCH_TO_WIFI_TRIGGER:
                    Log.w(TAG, "There is no response of inference, trigger force switch to wifi");
                    endBlockingSection(true /* forceSwitchToWifi */);
                    break;
                case MSG_LOGGER_INFERENCE_DONE: {
                    // Remove message since inference is successfully executed within a time.
                    removeMessages(MSG_ENFORCE_SWITCH_TO_WIFI_TRIGGER);
                    // |mCurrentWifiConfig| is not available yet so needs to fetch config here
                    WifiConfiguration wifiConfig = getWifiConfiguration();
                    // Determine default network with prediction result
                    PredictionResult predictionResult = (PredictionResult) message.obj;
                    JudgeResult result = null;
                    if (predictionResult != null) {
                        result = mSneEntryScore.judgeAndSwitchDefaultNetwork(predictionResult);
                    }
                    if (result == KEEP_NON_WIFI) {
                        // Set wifi disconnection timer in case of the first inference
                        if (mBlockedBssids.size() == 0) {
                            sendMessageDelayed(MSG_WIFI_DISCONNECT_TRIGGER,
                                    DURATION_TO_WIFI_DISCONNECTION);
                        }

                        WifiInfo wifiInfo = mWifiManager.getConnectionInfo();
                        if (wifiInfo == null) {
                            break; // Should never happen
                        }

                        // Blocklist current BSSID to avoid disconnect->connect->disconnect loop
                        if (!mBlockedBssids.contains(wifiInfo.getBSSID())) {
                            mWifiExtController.blocklistCurrentBssid();
                            // Add current BSSID to the own blocked list to prevent multiple call
                            // of |blocklistCurrentBssid()| API on same BSSID in current wifi
                            // connection. If it's called multiple times, block duration is getting
                            // very long because of the exponential backoff mechanism.
                            mBlockedBssids.add(wifiInfo.getBSSID());
                        }

                        // Display the notification
                        if (wifiConfig != null) {
                            mNotificationUtil.createEntryNotification(wifiConfig);
                        }
                    } else if (result == SWITCH_TO_WIFI || result == INFERENCE_IGNORED) {
                        if (result == SWITCH_TO_WIFI
                                || mSneEntryScore.isDefaultNetworkControlAllowed(wifiConfig)) {
                            mShouldStoreTrainingData = true;
                        }
                        endBlockingSection(false);
                    } else { /* result == null */
                        Log.w(TAG, "judge result is null, trigger force switch to wifi");
                        endBlockingSection(true /* forceSwitchToWifi */);
                        if (is6GHzWifiConnected() ||
                                WifiChecker.isMloConnection(mWifiManager.getConnectionInfo())) {
                            mWifiSelectionLogger.stop();
                            transitionTo(mDisabledState);
                        }
                    }
                    break;
                }
                case MSG_LOGGER_DATA_LOGGED: {
                    @SuppressWarnings("unchecked")
                    List<Object> objectList = (List<Object>) message.obj;
                    PredictionResult predictionResult = (PredictionResult) objectList.get(0);
                    Float label = (Float) objectList.get(1);
                    JSONObject iddData = (JSONObject) objectList.get(2);
                    int flDataInfo = 0;
                    if (mShouldStoreTrainingData) {
                        boolean inferenceDoneAfterWifiRoaming = isReInferenceExist(iddData);
                        if (!inferenceDoneAfterWifiRoaming) {
                            mPredictor.addTrainingData(predictionResult, label);
                            if (predictionResult.isScored() && !predictionResult.isScoreUsable()) {
                                flDataInfo |= FL_TRAINING_DATA;
                            }
                        } else {
                            // If wifi roaming case, this data is not used for training data.
                            Log.v(TAG, "Training data will not be added (wifi roaming happened)");
                            flDataInfo |= FL_WIFI_ROAMING;
                        }
                    } else {
                        Log.v(TAG, "Training data will not be added");
                    }
                    // Update "data_context" field in the idd data
                    setDataContext(iddData, flDataInfo);
                    // Allow parent state to handle IDD data collection
                    handleStatus = NOT_HANDLED;
                    break;
                }
                case MSG_FLS_STATUS_CHANGED:
                    // This will result in receiving |MSG_LOGGER_STATUS_CHANGED| message so that
                    // inference will be properly enabled or disabled with latest FLS status.
                    mWifiSelectionLogger.requestLoggingStatusUpdate();
                    handleStatus = NOT_HANDLED;
                    break;
                case MSG_LOGGER_STATUS_CHANGED: {
                    boolean loggingStarted = (message.arg1 == 1);
                    if (shouldEnableInference(loggingStarted)) {
                        // Enable default network control
                        mSneEntryScore.setDefaultNetworkControlCondition(mControlCondition);
                        mSneEntryScore.enableDefaultNetworkControl();
                    } else {
                        mSneEntryScore.setDefaultNetworkControlCondition(null);
                        mSneEntryScore.disableDefaultNetworkControl();
                    }
                    break;
                }
                case MSG_WIFI_DEFAULT_NETWORK_AVAILABLE:
                    // To make sure everything related to default network blocking (e.g. wifi
                    // disconnection timer) is properly released. For instance, this is needed
                    // for the case when screen is off during the blocking.
                    endBlockingSection(false);
                    break;
                default:
                    handleStatus = NOT_HANDLED;
                    break;
            }
            return handleStatus;
        }

        @Override
        public void exit() {
            Log.v(TAG, getName() + " exited");
            // Switch default network to wifi and cancel the notification
            mSneEntryScore.setDefaultNetworkControlCondition(null);
            mSneEntryScore.disableDefaultNetworkControl();
            endBlockingSection(false);
            mWifiSelectionLogger.setPredictor(null);
            mConnectivityManager.unregisterNetworkCallback(mWifiNetworkCallback);
            NotificationEventReceiver.setNotificationEventListener(null);
            mContext.unregisterReceiver(mScreenOnReceiver);
            mBlockedBssids.clear();
            mPredictor.reset();
            mShouldStoreTrainingData = false;
        }

        private boolean shouldEnableInference(boolean loggingStarted) {
            FLFeatureStatus featureStatus = mFLSystemManager.getSystemStatus().getFeatureStatus(
                    FEATURE_ENTRY);
            return featureStatus.isPredictionEnabled()
                    && !featureStatus.isDataCollectionSession()
                    && loggingStarted;
        }

        private void endBlockingSection(boolean forceSwitchToWifi) {
            // Clear enforce switch timer if exist
            removeMessages(MSG_ENFORCE_SWITCH_TO_WIFI_TRIGGER);
            if (forceSwitchToWifi) {
                mSneEntryScore.forceSwitchToWifi();
            }
            // Cancel the notification if necessary
            mNotificationUtil.cancelEntryNotification();
            // Clear wifi disconnection timer if exist
            removeMessages(MSG_WIFI_DISCONNECT_TRIGGER);
        }

        private boolean isReInferenceExist(JSONObject iddData) {
            try {
                return iddData.getInt("re_inference") == 1;
            } catch (JSONException e) {
                Log.w(TAG, "cannot read value of JSONObject");
            }
            return false;
        }

        private void setDataContext(JSONObject iddData, int dataContext) {
            try {
                iddData.put("data_context", dataContext);
            } catch (JSONException e) {
                Log.w(TAG, "cannot change value of JSONObject");
            }
        }
    }

    private class DisabledState extends State {
        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            sendMessage(MSG_ENABLED_CHECK_TRIGGER);
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            boolean handleStatus = HANDLED;
            switch (message.what) {
                case MSG_ENABLED_CHECK_TRIGGER:
                case MSG_FLS_STATUS_CHANGED:
                case MSG_ENTRY_SETTING_CHANGED:
                case MSG_ROAMING_SETTING_CHANGED:
                case MSG_STASTA_CONCURRENCY_STATUS_CHANGED:
                case MSG_WIFI_DISCONNECTED: {
                    FLSystemStatus systemStatus = mFLSystemManager.getSystemStatus();
                    ServiceState serviceState = mTelephonyManager.getServiceState();
                    if (systemStatus.isSystemEnabled()
                            && SneUtils.isSmartNetworkEntrySettingsEnabled()
                            && (serviceState == null || !serviceState.getRoaming())
                            && !is6GHzWifiConnected()
                            && !WifiChecker.isMloConnection(mWifiManager.getConnectionInfo())
                            && !mWifiExtController.isStaStaConcurrent()) {
                        // Start the logger if not started as it's disabled temporarily when
                        // STA+STA concurrent started.
                        mWifiSelectionLogger.start();
                        transitionTo(mNormalState);
                    }
                    break;
                }
                default:
                    handleStatus = NOT_HANDLED;
                    break;
            }
            return handleStatus;
        }

        @Override
        public void exit() {
            Log.v(TAG, getName() + " exited");
        }
    }

    @Nullable
    private WifiConfiguration getWifiConfiguration() {
        WifiInfo wifiInfo = mWifiManager.getConnectionInfo();
        if (wifiInfo != null) {
            Optional<WifiConfiguration> configOpt =
                    // WARNING: the passwords in plaintext are returned.
                    mWifiManager.getPrivilegedConfiguredNetworks().stream()
                            .filter(e -> e.networkId == wifiInfo.getNetworkId())
                            .findFirst();
            return configOpt.orElse(null);
        }
        return null;
    }

    private boolean is6GHzWifiConnected() {
        WifiInfo wifiInfo = mWifiManager.getConnectionInfo();
        return wifiInfo != null && WifiChecker.is6GHz(wifiInfo.getFrequency());
    }

    /**
     * Mapper method to modify DataSet for deploy, training, evaluation and calibration
     */
    private DataSet mapper(DataSet dataSet) {
        return DataSet.builder()
                .groupLabel(dataSet.getGroupLabel())
                .features(Arrays.stream(dataSet.getFeatures()).map(
                        this::updateLabelAverage).toArray(float[][]::new))
                .label(dataSet.getLabel())
                .build();
    }

    /**
     * Recalculate and overwrite label average in the feature
     */
    private float[] updateLabelAverage(float[] feature) {
        feature[1] = mWifiSelectionLogger.calcLabelAverage(mPredictor.getAverageOfLabel());
        return feature;
    }
}
