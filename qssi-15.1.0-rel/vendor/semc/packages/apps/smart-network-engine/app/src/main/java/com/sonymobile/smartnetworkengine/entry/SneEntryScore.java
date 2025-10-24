/*
 * Copyright 2020, 2021, 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.entry;

import static com.sonymobile.smartnetworkengine.Constants.ENTRY_SCORE_JUDGE_TIMEOUT_SEC;

import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.ConnectivityManager;
import android.net.ConnectivityManager.NetworkCallback;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkRequest;
import android.net.wifi.SupplicantState;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Message;
import android.provider.Settings;
import android.util.SparseArray;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.android.internal.util.MessageUtils;
import com.android.internal.util.State;
import com.android.internal.util.StateMachine;

import com.sonymobile.smartnetworkengine.DefaultNetworkController;
import com.sonymobile.smartnetworkengine.DefaultNetworkController.StatusListener;
import com.sonymobile.smartnetworkengine.fls.Predictor.PredictionResult;
import com.sonymobile.smartnetworkengine.util.Log;

import java.util.Arrays;
import java.util.Optional;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;
import java.util.function.Consumer;
import java.util.function.Predicate;

public class SneEntryScore extends StateMachine {
    private static final String TAG = SneEntryScore.class.getSimpleName();

    private static final long AWAITING_WIFI_DEFAULT_NW_DURATION = TimeUnit.SECONDS.toMillis(3);

    // Message what to string mapping (for message logging)
    private static final SparseArray<String> WHAT_TO_STRING = MessageUtils.findMessageNames(
            new Class[]{SneEntryScore.class}, new String[]{"MSG_"});

    // Event messages handled by the state machine
    /** Event: Trigger to enable default network control */
    private static final int MSG_ENABLE_DEFAULT_NETWORK_CONTROL = 11;
    /** Event: Trigger to disable default network control */
    private static final int MSG_DISABLE_DEFAULT_NETWORK_CONTROL = 12;
    /** Event: Trigger to judge default network switch */
    private static final int MSG_JUDGE_DEFAULT_NETWORK = 13;
    /** Event: Trigger to switch default network to wifi */
    private static final int MSG_FORCE_SWITCH_TO_WIFI = 14;

    /** Event: Wifi connected */
    private static final int MSG_WIFI_CONNECTED = 21;
    /** Event: Wifi disconnected */
    private static final int MSG_WIFI_DISCONNECTED = 22;
    /** Event: Wifi changed to default network */
    private static final int MSG_WIFI_DEFAULT_NETWORK = 23;

    /** Event: Awaiting wifi default network timeout */
    private static final int MSG_AWAITING_WIFI_DEFAULT_NW_TIMEOUT = 31;

    /**
     * State: Top parent state
     */
    private final State mDefaultState = new DefaultState();
    /**
     * State: Disabled default network control function
     */
    private final State mDisabledState = new DisabledState();
    /**
     * State: Enabled default network control function (parent state of other 3 states)
     */
    private final State mEnabledState = new EnabledState();
    /**
     * State: Awaiting new wifi connection for judging to block wifi default network
     */
    private final State mStandbyState = new StandbyState();
    /**
     * State: Blocking wifi default network
     */
    private final State mWifiDefaultNetworkBlockingState = new WifiDefaultNetworkBlockingState();
    /**
     * State: Awaiting default network changed to wifi
     */
    private final State mAwaitingWifiDefaultNetworkState = new AwaitingWifiDefaultNetworkState();

    private final Context mContext;

    private final DefaultNetworkController mDefaultNetworkController;

    private final ConnectivityManager mConnectivityManager;

    private final WifiManager mWifiManager;

    // This network request and callback are required to prevent wifi from disconnection which
    // occurs when sending score 49 to wifi framework immediately after wifi connection. This
    // is kind of workaround of connectivity framework behavior.
    private final NetworkRequest mWifiRequest = new NetworkRequest.Builder().addTransportType(
            NetworkCapabilities.TRANSPORT_WIFI).build();
    private final NetworkCallback mNetworkCallback = new NetworkCallback();

    @Nullable
    private Predicate<WifiConfiguration> mBlockCondition;

    public SneEntryScore(@NonNull Context context, @NonNull DefaultNetworkController controller) {
        // Create new thread for SneEntryScore state machine.
        super(TAG);

        mContext = context;
        mDefaultNetworkController = controller;
        mConnectivityManager = (ConnectivityManager) context.getSystemService(
                Context.CONNECTIVITY_SERVICE);
        mWifiManager = (WifiManager) context.getSystemService(Context.WIFI_SERVICE);

        //@formatter:off
        addState(mDefaultState);
            addState(mDisabledState, mDefaultState);
            addState(mEnabledState, mDefaultState);
                addState(mStandbyState, mEnabledState);
                addState(mWifiDefaultNetworkBlockingState, mEnabledState);
                addState(mAwaitingWifiDefaultNetworkState, mEnabledState);
        //@formatter:on
        setInitialState(mDisabledState);
    }

    public void setDefaultNetworkControlCondition(
            @Nullable Predicate<WifiConfiguration> condition) {
        Log.v(TAG, "setDefaultNetworkControlCondition()");
        mBlockCondition = condition;
    }

    public void enableDefaultNetworkControl() {
        Log.v(TAG, "enableDefaultNetworkControl()");
        sendMessage(MSG_ENABLE_DEFAULT_NETWORK_CONTROL);
    }

    public void disableDefaultNetworkControl() {
        Log.v(TAG, "disableDefaultNetworkControl()");
        sendMessage(MSG_DISABLE_DEFAULT_NETWORK_CONTROL);
    }

    /**
     * Force switch default network to Wifi.
     */
    public void forceSwitchToWifi() {
        Log.v(TAG, "forceSwitchToWifi()");
        sendMessage(MSG_FORCE_SWITCH_TO_WIFI);
    }

    /**
     * Judge inference result and switch default network if necessary.
     */
    @Nullable
    public JudgeResult judgeAndSwitchDefaultNetwork(@NonNull PredictionResult predictionResult) {
        Log.v(TAG, "judgeAndSwitchDefaultNetwork()");
        // Use single instance array to make this variable final so that listener can access it.
        final JudgeResult[] judgeResultArray = new JudgeResult[1];
        final CountDownLatch countDownLatch = new CountDownLatch(1);
        JudgeRequest judgeRequest = new JudgeRequest(predictionResult, (result) -> {
            judgeResultArray[0] = result;
            countDownLatch.countDown();
        });

        // send judge request to state machine and wait for result
        sendMessage(MSG_JUDGE_DEFAULT_NETWORK, judgeRequest);
        try {
            countDownLatch.await(ENTRY_SCORE_JUDGE_TIMEOUT_SEC, TimeUnit.SECONDS);
        } catch (InterruptedException e) {
            Log.w(TAG, "Interrupted while judgeAndSwitchDefaultNetwork(): " + e);
            judgeResultArray[0] = null;
        }

        return judgeResultArray[0];
    }

    /**
     * Return whether default network control is allowed on specified wifi network.
     */
    public boolean isDefaultNetworkControlAllowed(@NonNull WifiConfiguration wifiConfig) {
        return ((mBlockCondition == null || mBlockCondition.test(wifiConfig))
                && entryConditionMet());
    }

    @Override
    protected boolean recordLogRec(Message msg) {
        return Log.getLogLevel() == Log.Level.DEBUG;
    }

    @Override
    protected String getWhatToString(int what) {
        return WHAT_TO_STRING.get(what);
    }

    public enum JudgeResult {
        KEEP_NON_WIFI,
        SWITCH_TO_WIFI,
        INFERENCE_IGNORED
    }

    private static class JudgeRequest {
        PredictionResult predictionResult;
        Consumer<JudgeResult> listener;

        JudgeRequest(PredictionResult predictionResult, Consumer<JudgeResult> listener) {
            this.predictionResult = predictionResult;
            this.listener = listener;
        }
    }

    private class DefaultState extends State {
        // This is needed for the case where wifi is already connected upon entering this state.
        private boolean mSkipWifiConnectionEvent;

        /**
         * Wifi connection/disconnection event listener
         */
        private final StatusListener mWifiConnectionListener = new StatusListener() {
            @Override
            public void onStart() {
                if (mSkipWifiConnectionEvent) {
                    Log.v(TAG, "Skip wifi connection event since wifi already connected");
                    mSkipWifiConnectionEvent = false;
                    return;
                }

                // Obtain a current wifi network configuration
                WifiConfiguration wifiConfig = null;
                WifiInfo wifiInfo = mWifiManager.getConnectionInfo();
                if (wifiInfo != null) {
                    Optional<WifiConfiguration> configOpt =
                            // WARNING: the passwords in plaintext are returned.
                            mWifiManager.getPrivilegedConfiguredNetworks().stream()
                                    .filter(e -> e.networkId == wifiInfo.getNetworkId())
                                    .findFirst();
                    wifiConfig = configOpt.orElse(null);
                }

                sendMessage(MSG_WIFI_CONNECTED, wifiConfig);
            }

            @Override
            public void onStop() {
                sendMessage(MSG_WIFI_DISCONNECTED);
            }
        };

        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            // Check if wifi is already connected or not with sticky intent and if connected,
            // |onStart| callback is ignored once (to avoid starting EntryScore for this session)
            IntentFilter filter = new IntentFilter(WifiManager.SUPPLICANT_STATE_CHANGED_ACTION);
            Intent intent = mContext.registerReceiver(null, filter);
            if (intent != null) {
                SupplicantState state = intent.getParcelableExtra(WifiManager.EXTRA_NEW_STATE);
                if (state != null && isConnectingOrConnected(state)) {
                    mSkipWifiConnectionEvent = true;
                }
            }
            mDefaultNetworkController.registerStatusListener(mWifiConnectionListener);
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            switch (message.what) {
                case MSG_JUDGE_DEFAULT_NETWORK: {
                    // if judge is called other than |WifiDefaultNetworkBlocking| state, notify
                    // caller of inference being ignored. This could occur e.g. when wifi is only
                    // available network.
                    JudgeRequest request = (JudgeRequest) message.obj;
                    request.listener.accept(JudgeResult.INFERENCE_IGNORED);
                    break;
                }
                default:
                    Log.v(TAG, "Unhandled message received: " + getWhatToString(message.what));
                    break;
            }
            return HANDLED;
        }

        @Override
        public void exit() {
            Log.v(TAG, getName() + " exited");
            mDefaultNetworkController.unregisterStatusListener(mWifiConnectionListener);
        }

        /**
         * This method is created referring to SupplicantState.isConnecting() which is hidden.
         */
        private boolean isConnectingOrConnected(SupplicantState state) {
            switch (state) {
                case AUTHENTICATING:
                case ASSOCIATING:
                case ASSOCIATED:
                case FOUR_WAY_HANDSHAKE:
                case GROUP_HANDSHAKE:
                case COMPLETED:
                    return true;
                default:
                    return false;
            }
        }
    }

    private class EnabledState extends State {
        /**
         * This callback is mainly to clear network request when wifi becomes default network
         */
        private final NetworkCallback mDefaultNetworkCallback =
                new NetworkCallback() {
                    @Override
                    public void onCapabilitiesChanged(@NonNull Network network,
                            @NonNull NetworkCapabilities nc) {
                        super.onCapabilitiesChanged(network, nc);
                        if (nc.hasTransport(NetworkCapabilities.TRANSPORT_WIFI)) {
                            sendMessage(MSG_WIFI_DEFAULT_NETWORK);
                        }
                    }
                };

        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            mConnectivityManager.registerDefaultNetworkCallback(mDefaultNetworkCallback);
        }

        @Override
        public void exit() {
            Log.v(TAG, getName() + " exited");
            mConnectivityManager.unregisterNetworkCallback(mDefaultNetworkCallback);
        }
    }

    private class StandbyState extends State {
        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            boolean handleStatus = HANDLED;
            switch (message.what) {
                case MSG_WIFI_CONNECTED: {
                    WifiConfiguration wifiConfig = (WifiConfiguration) message.obj;
                    if (isDefaultNetworkControlAllowed(wifiConfig)) {
                        transitionTo(mWifiDefaultNetworkBlockingState);
                    } else {
                        Log.v(TAG, "Skip wifi block since conditions are not met.");
                    }
                    break;
                }
                case MSG_DISABLE_DEFAULT_NETWORK_CONTROL:
                    transitionTo(mDisabledState);
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
        }
    }

    private class WifiDefaultNetworkBlockingState extends State {
        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            mConnectivityManager.requestNetwork(mWifiRequest, mNetworkCallback);
            mDefaultNetworkController.preferNonWifiNetwork();
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            boolean handlStatus = HANDLED;
            switch (message.what) {
                case MSG_JUDGE_DEFAULT_NETWORK: {
                    JudgeResult result = JudgeResult.KEEP_NON_WIFI;
                    JudgeRequest request = (JudgeRequest) message.obj;
                    if (!(request.predictionResult.isScoreUsable()
                            && request.predictionResult.aboveScoreThreshold())) {
                        // ok to switch default network to wifi
                        result = JudgeResult.SWITCH_TO_WIFI;
                        transitionTo(mAwaitingWifiDefaultNetworkState);
                    }
                    request.listener.accept(result);
                    break;
                }
                case MSG_DISABLE_DEFAULT_NETWORK_CONTROL:
                case MSG_WIFI_DISCONNECTED:
                case MSG_WIFI_DEFAULT_NETWORK:
                    deferMessage(message);
                    // fall through
                case MSG_FORCE_SWITCH_TO_WIFI:
                    transitionTo(mAwaitingWifiDefaultNetworkState);
                    break;
                default:
                    handlStatus = NOT_HANDLED;
                    break;
            }
            return handlStatus;
        }

        @Override
        public void exit() {
            Log.v(TAG, getName() + " exited");
        }
    }

    private class AwaitingWifiDefaultNetworkState extends State {
        // Need to track if |DisabledState| is requested since transition to DisabledState should
        // not immediately take place in |WifiDefaultNetworkBlockingState| - otherwise wifi
        // disconnection occurs.
        private boolean mDisabledStateRequested;

        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            mDisabledStateRequested = false;
            mDefaultNetworkController.preferWifiNetwork();
            sendMessageDelayed(MSG_AWAITING_WIFI_DEFAULT_NW_TIMEOUT,
                    AWAITING_WIFI_DEFAULT_NW_DURATION);
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            boolean handleStatus = HANDLED;
            switch (message.what) {
                case MSG_DISABLE_DEFAULT_NETWORK_CONTROL:
                    mDisabledStateRequested = true;
                    break;
                case MSG_ENABLE_DEFAULT_NETWORK_CONTROL:
                    mDisabledStateRequested = false;
                    break;
                case MSG_WIFI_DEFAULT_NETWORK:
                case MSG_WIFI_DISCONNECTED:
                case MSG_AWAITING_WIFI_DEFAULT_NW_TIMEOUT:
                    if (mDisabledStateRequested) {
                        transitionTo(mDisabledState);
                    } else {
                        transitionTo(mStandbyState);
                    }
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
            removeMessages(MSG_AWAITING_WIFI_DEFAULT_NW_TIMEOUT);
            mConnectivityManager.unregisterNetworkCallback(mNetworkCallback);
        }
    }

    private class DisabledState extends State {
        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            boolean handleStatus = HANDLED;
            switch (message.what) {
                case MSG_ENABLE_DEFAULT_NETWORK_CONTROL:
                    transitionTo(mStandbyState);
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
        }
    }

    private boolean entryConditionMet() {
        // Get wifi network capabilities
        Optional<NetworkCapabilities> ncOpt = Arrays.stream(
                        mConnectivityManager.getAllNetworks())
                .map(mConnectivityManager::getNetworkCapabilities)
                .filter(nc -> nc.hasTransport(NetworkCapabilities.TRANSPORT_WIFI))
                .findFirst();
        NetworkCapabilities nc = ncOpt.orElse(null);

        boolean hasValidCapabilities = nc != null
                && nc.hasCapability(NetworkCapabilities.NET_CAPABILITY_INTERNET)
                && nc.hasCapability(NetworkCapabilities.NET_CAPABILITY_TRUSTED)
                && nc.hasCapability(NetworkCapabilities.NET_CAPABILITY_NOT_RESTRICTED)
                && nc.hasCapability(NetworkCapabilities.NET_CAPABILITY_NOT_VPN);

        boolean isCaptivePortalSettingEnabled =
                Settings.Global.CAPTIVE_PORTAL_MODE_IGNORE != Settings.Global.getInt(
                        mContext.getContentResolver(),
                        Settings.Global.CAPTIVE_PORTAL_MODE,
                        Settings.Global.CAPTIVE_PORTAL_MODE_PROMPT);

        boolean conditionOk = hasValidCapabilities && isCaptivePortalSettingEnabled;
        Log.v(TAG, "entry condition check -> " + (conditionOk ? "OK" : "NG")
                + " (valid capabilities: " + hasValidCapabilities + ", captive portal enabled: "
                + isCaptivePortalSettingEnabled + ")");

        return conditionOk;
    }
}
