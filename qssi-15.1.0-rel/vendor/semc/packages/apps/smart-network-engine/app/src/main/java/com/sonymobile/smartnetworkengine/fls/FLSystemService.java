/*
 * Copyright 2021, 2022, 2023, 2024 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls;

import static com.sonymobile.smartnetworkengine.Constants.ACTION_FLS_FORCE_DOWNLOAD;
import static com.sonymobile.smartnetworkengine.Constants.FLS_APP_ID_LIST;
import static com.sonymobile.smartnetworkengine.Constants.FLS_CDN_CLIENT_CONFIG_FILENAME;
import static com.sonymobile.smartnetworkengine.Constants.FLS_DATA_DIR;
import static com.sonymobile.smartnetworkengine.Constants.FLS_INFERENCE_THRESHOLD_OVERRIDE_PROP_GENERATOR;
import static com.sonymobile.smartnetworkengine.Constants.PROP_FLS_SERVER_ENV;
import static com.sonymobile.smartnetworkengine.Constants.PROP_FLS_TEST_CLIENT_CONFIG_FILE;
import static com.sonymobile.smartnetworkengine.fls.FLPreferenceAccessor.KEY_CLIENT_CONFIG_AS_STRING;
import static com.sonymobile.smartnetworkengine.fls.FLPreferenceAccessor.KEY_COMPLETED_FL_TASK_ID_LIST;
import static com.sonymobile.smartnetworkengine.fls.FLPreferenceAccessor.KEY_DOWNLOAD_RETRY_BACKOFF_COUNT;
import static com.sonymobile.smartnetworkengine.fls.FLPreferenceAccessor.KEY_DOWNLOAD_START_TIME;
import static com.sonymobile.smartnetworkengine.fls.FLPreferenceAccessor.KEY_PENDING_FL_TASK_INDEX_LIST;
import static com.sonymobile.smartnetworkengine.fls.FLPreferenceAccessor.KEY_PENDING_PRIORITY_FL_TASK_INDEX_LIST;
import static com.sonymobile.smartnetworkengine.fls.FLPreferenceAccessor.KEY_PENDING_UPLOAD_FL_TASK_INDEX_LIST;
import static com.sonymobile.smartnetworkengine.fls.FLPreferenceAccessor.KEY_PREFS_VERSION;
import static com.sonymobile.smartnetworkengine.fls.FLPreferenceAccessor.KEY_SKIPPED_CLIENT_CONFIG_AS_HASH;
import static com.sonymobile.smartnetworkengine.fls.FLPreferenceAccessor.KEY_UPLOAD_PERIOD_END_TIME;
import static com.sonymobile.smartnetworkengine.fls.FLPreferenceAccessor.KEY_UPLOAD_PERIOD_START_TIME;
import static com.sonymobile.smartnetworkengine.fls.FLPreferenceAccessor.KEY_UPLOAD_RETRY_BACKOFF_COUNT;
import static com.sonymobile.smartnetworkengine.fls.FLPreferenceAccessor.LAST_CALIBRATION_TIME_KEY_GENERATOR;
import static com.sonymobile.smartnetworkengine.fls.FLPreferenceAccessor.MODEL_TYPE_KEY_GENERATOR;
import static com.sonymobile.smartnetworkengine.fls.FLPreferenceAccessor.MODEL_VERSION_KEY_GENERATOR;
import static com.sonymobile.smartnetworkengine.fls.FLPreferenceAccessor.toCommaSeparatedString;

import android.annotation.SuppressLint;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.SharedPreferences.Editor;
import android.database.Cursor;
import android.database.sqlite.SQLiteDiskIOException;
import android.database.sqlite.SQLiteFullException;
import android.net.ConnectivityManager;
import android.net.ConnectivityManager.NetworkCallback;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.Uri;
import android.os.BatteryManager;
import android.os.Build;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;
import android.os.PowerManager;
import android.os.SystemProperties;
import android.text.TextUtils;
import android.util.Pair;
import android.util.SparseArray;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;

import com.android.internal.util.MessageUtils;
import com.android.internal.util.State;
import com.android.internal.util.StateMachine;

import com.google.common.primitives.Floats;
import com.google.gson.GsonBuilder;
import com.sony.fl.Configuration;
import com.sony.fl.DeployManager;
import com.sony.fl.PredictManager;
import com.sony.fl.PredictManager.PredictResult;
import com.sony.fl.TrainManager;
import com.sony.fl.TrainManager.EvaluationResult;
import com.sony.fl.TrainManager.TrainResult;
import com.sony.fl.algorithm.LinearFedHLCRClient;
import com.sony.fl.algorithm.NNFedHLCRClient;
import com.sony.fl.exception.FLException;
import com.sony.fl.pb.TaskInfo.ModelType;
import com.sony.fl.pb.TaskInfo.PBTaskInfo;
import com.sony.fl.pb.TaskResult.PBTaskResult;
import com.sony.fl.tensor.DataMetadata;
import com.sony.fl.tensor.Tensor;
import com.sony.fl.tensor.TensorMap;
import com.sony.fl.tensor.TensorShape;
import com.sonymobile.smartnetworkengine.R;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.AppidSpecificConfig;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.ClientConfig;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.FLTask;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.GeneralConfiguration.OperationMode;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigDownloader;
import com.sonymobile.smartnetworkengine.fls.comm.FLResultUploader;
import com.sonymobile.smartnetworkengine.fls.data.FLFileManager;
import com.sonymobile.smartnetworkengine.fls.data.FLTrainingDataAccessor;
import com.sonymobile.smartnetworkengine.fls.data.FLTrainingDataAccessor.DataSet;
import com.sonymobile.smartnetworkengine.fls.data.FLTrainingDataAccessor.DataType;
import com.sonymobile.smartnetworkengine.util.ExponentialBackoff;
import com.sonymobile.smartnetworkengine.util.Log;

import org.apache.commons.io.file.PathUtils;

import java.io.FileDescriptor;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.file.Path;
import java.security.PrivateKey;
import java.security.cert.X509Certificate;
import java.time.Instant;
import java.time.ZoneId;
import java.time.ZonedDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Optional;
import java.util.Random;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.TimeUnit;
import java.util.function.Function;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import javax.security.auth.DestroyFailedException;

/**
 * This class takes responsibility for Federated-Learning specific processing and also implements
 * {@link FLSystemManager} interface.
 *
 * IMPLEMENTATION NOTE:
 *
 * 1. This class should only have Federated-Learning specific code and this class should NOT have
 * use case specific code such as the logic related to the entry and the connected specification.
 *
 * 2. Be careful about concurrent access to FL library. The library doesn't support concurrent
 * access in any case (regardless of over different classes, over different instances). The library
 * just returns error on subsequent calls if concurrent access happens.
 */
public class FLSystemService extends StateMachine implements FLSystemManager {

    private static final String TAG = FLSystemService.class.getSimpleName();

    private static final boolean DEBUG_BUILD = Build.TYPE.equals("userdebug");

    // Message what to string mapping (for message logging)
    private static final SparseArray<String> WHAT_TO_STRING = MessageUtils.findMessageNames(
            new Class[]{FLSystemService.class}, new String[]{"MSG_"});

    private static final DateTimeFormatter DUMP_DATETIME_FORMATTER = DateTimeFormatter.ofPattern(
            "yyyy-MM-dd HH:mm z");

    private static final String PREDICT_MANAGER_DATA_DIR = "lib_predict";
    private static final String TRAIN_MANAGER_DATA_DIR = "lib_train";
    private static final String TASK_DATA_TOP_DIR = "task_data";
    private static final String UPLOAD_DATA_TOP_DIR = "upload_data";
    private static final String CALIBRATION_TOP_DIR = "calibration";

    /** A ratio between 'training' and 'evaluation' data */
    private static final int TRAINING_DATA_RATIO = 80; // train : eval = 80% : 20%

    private static final int MAX_SIZE_OF_COMPLETED_FL_TASK_ID_LIST = 10 * FLS_APP_ID_LIST.size();

    private static final long FL_TASK_START_INTERVAL = TimeUnit.MINUTES.toMillis(3);

    // Event messages handled by the state machine
    /** Event: Feature status(enabled/disabled) changed */
    private static final int MSG_FEATURE_STATUS_CHANGED = 1;

    // For the enabled and child states
    /** Event: Usable Wifi network found (for upload/download) */
    private static final int MSG_USABLE_WIFI_NETWORK_AVAILABLE = 11;
    /** Event: Usable Wifi network lost (for upload/download) */
    private static final int MSG_USABLE_WIFI_NETWORK_LOST = 12;
    /** Event: Request to add training data */
    private static final int MSG_ADD_TRAINING_DATA = 13;
    /** Event: Request to update system status */
    private static final int MSG_UPDATE_SYSTEM_STATUS = 14;
    /** Event: FL task can be runnable (if condition met) */
    private static final int MSG_FL_TASK_CONDITION_RUNNABLE = 15;
    /** Event: Check conditions for running the FL task */
    private static final int MSG_FL_TASK_CONDITION_CHECK = 16;
    /** Event: Screen Off */
    private static final int MSG_SCREEN_OFF = 17;

    // For the normal state
    /** Event: Trigger to run the pending FL task (if condition met) */
    private static final int MSG_PROCESS_PENDING_FL_TASK_TRIGGER = 31;
    /** Event: Trigger to start upload/download sequence (if condition met) */
    private static final int MSG_UPLOAD_AND_DOWNLOAD_TRIGGER = 32;
    /** Event: Trigger to start download sequence forcibly (for debugging purpose) */
    private static final int MSG_FORCE_DOWNLOAD_TRIGGER = 33;

    // For the download state
    /** Event: Download succeeded */
    private static final int MSG_DOWNLOAD_STATUS_SUCCESS = 41;
    /** Event: Download skipped */
    private static final int MSG_DOWNLOAD_STATUS_SKIP = 42;
    /** Event: Download failed */
    private static final int MSG_DOWNLOAD_STATUS_FAILURE = 43;

    // For the upload state
    /** Event: Upload succeeded */
    private static final int MSG_UPLOAD_STATUS_SUCCESS = 51;
    /** Event: Upload failed */
    private static final int MSG_UPLOAD_STATUS_FAILURE = 52;

    // For the deploy state
    /** Event: Model deploy succeeded */
    private static final int MSG_DEPLOY_STATUS_SUCCESS = 61;
    /** Event: Model deploy failed */
    private static final int MSG_DEPLOY_STATUS_FAILURE = 62;

    // For the training state
    /** Event: Training succeeded */
    private static final int MSG_TRAINING_STATUS_SUCCESS = 71;
    /** Event: Training failed */
    private static final int MSG_TRAINING_STATUS_FAILURE = 72;

    // For the evaluation state
    /** Event: Evaluation succeeded */
    private static final int MSG_EVALUATION_STATUS_SUCCESS = 81;
    /** Event: Evaluation failed */
    private static final int MSG_EVALUATION_STATUS_FAILURE = 82;

    // For the calibration state
    /** Event: Calibration succeeded */
    private static final int MSG_CALIBRATION_STATUS_SUCCESS = 91;
    /** Event: Calibration failed */
    private static final int MSG_CALIBRATION_STATUS_FAILURE = 92;

    // For the delete state
    /** Event: Delete succeeded */
    private static final int MSG_DELETE_STATUS_SUCCESS = 101;
    /** Event: Delete failed */
    private static final int MSG_DELETE_STATUS_FAILURE = 102;

    // For the disabled state
    /** Event: Trigger to check if FL system should be enabled */
    private static final int MSG_ENABLED_CHECK_TRIGGER = 111;

    /** State: Top parent state */
    private final State mDefaultState = new DefaultState();
    /** State: Enabled all functions (parent state) */
    private final State mEnabledState = new EnabledState();
    /** State: Predictable state (parent state) */
    private final State mPredictableState = new PredictableState();
    /** State: Normal/Idle state for prediction */
    private final State mNormalState = new NormalState();
    /** State: Download state to fetch latest configuration and model */
    private final State mDownloadState = new DownloadState();
    /** State: Upload state to upload training/evaluation result */
    private final State mUploadState = new UploadState();
    /** State: Deploy state to deploy model for prediction */
    private final State mDeployState = new DeployState();
    /** State: Training state to perform train */
    private final State mTrainingState = new TrainingState();
    /** State: Evaluation state to perform evaluation */
    private final State mEvaluateState = new EvaluateState();
    /** State: Calibration state to perform calibration */
    private final State mCalibrateState = new CalibrateState();
    /** State: Delete state to perform delete */
    private final State mDeleteState = new DeleteState();
    /** State: Disabled all functions */
    private final State mDisabledState = new DisabledState();

    private final Context mContext;

    private final Handler mFLMainHandler;

    private final Handler mFLLibHandler;

    private final Path mPredictManagerDataDir;

    private final Path mTrainManagerDataDir;

    private final FLFileManager mFileManager;

    private final ConnectivityManager mConnectivityManager;

    private final PowerManager mPowerManager;

    private final FLClientConfigAccessor mClientConfigAccessor;

    private final FLTrainingDataAccessor mTrainingDataAccessor;

    private final CertificateAccessor mCertificateAccessor;

    private final PowerManager.WakeLock mWakeLock;

    private final Map<String, PredictorImpl> mPredictorMap;

    private final Map<String, Boolean> mFeatureStatusMap;

    private final Map<String, Boolean> mDcPrConditions;

    private final Set<String> mCalibrationRequiredAppIds = new HashSet<>();

    private final Map<FLSystemStatusListener, String> mSystemStatusListeners = new HashMap<>();

    @NonNull
    private FLSystemStatus mSystemStatus = FLSystemStatus.builder().build();

    @Nullable
    private Network mUsableWifiNetwork;

    private boolean mIsFLTaskRunnable;

    public FLSystemService(@NonNull Context context) {
        super(TAG);
        mContext = context;
        // Create a handler which is associated to the thread created by StateMachine
        Looper entryLooper = getHandler().getLooper();
        mFLMainHandler = new Handler(entryLooper);
        // Create a handler which is associated to the thread for FL library time-consuming process
        HandlerThread handlerThread = new HandlerThread("FLLib@" + TAG);
        handlerThread.start();
        mFLLibHandler = new Handler(handlerThread.getLooper());

        // Build directory path for FL library
        Path dataRootDir = context.getFilesDir().toPath().resolve(FLS_DATA_DIR);
        mPredictManagerDataDir = dataRootDir.resolve(PREDICT_MANAGER_DATA_DIR);
        mTrainManagerDataDir = dataRootDir.resolve(TRAIN_MANAGER_DATA_DIR);
        mFileManager = new FLFileManager(dataRootDir.resolve(TASK_DATA_TOP_DIR),
                dataRootDir.resolve(UPLOAD_DATA_TOP_DIR), dataRootDir.resolve(CALIBRATION_TOP_DIR));

        // Update dependency for FL library
        Configuration.DB_FACTORY_FQCN =
                "com.sonymobile.smartnetworkengine.fls.lib.AndroidSQLiteFactory";
        Configuration.LOGGER_FQCN = "com.sonymobile.smartnetworkengine.fls.lib.Logger";

        // Obtain system services
        mConnectivityManager = context.getSystemService(ConnectivityManager.class);
        mPowerManager = (PowerManager) context.getSystemService(Context.POWER_SERVICE);
        // Initialize components
        mClientConfigAccessor = new FLClientConfigAccessor(
                FLPreferenceAccessor.getSharedPreferences());
        mTrainingDataAccessor = new FLTrainingDataAccessor(context);
        mCertificateAccessor = new CertificateAccessor(mContext);
        // Prepare a wake lock for upload and download communication
        mWakeLock = mPowerManager.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK,
                "com.sonymobile.smartnetworkengine:fls_comm_wakelock");
        mWakeLock.setReferenceCounted(false);

        // Create predictors
        Map<String, PredictorImpl> predictorMap = new HashMap<>();
        FLS_APP_ID_LIST.forEach(e -> predictorMap.put(e,
                new PredictorImpl(new PredictManagerWrapper(e, mPredictManagerDataDir), this)));
        mPredictorMap = Collections.unmodifiableMap(predictorMap);

        mFeatureStatusMap = new ConcurrentHashMap<>();
        FLS_APP_ID_LIST.forEach(e -> mFeatureStatusMap.put(e, false));

        mDcPrConditions = new ConcurrentHashMap<>();
        FLS_APP_ID_LIST.forEach(e -> mDcPrConditions.put(e, false));

        //@formatter:off
        addState(mDefaultState);
            addState(mEnabledState, mDefaultState);
                addState(mPredictableState, mEnabledState);
                    addState(mNormalState, mPredictableState);
                    addState(mDownloadState, mPredictableState);
                    addState(mUploadState, mPredictableState);
                addState(mDeployState, mEnabledState);
                addState(mTrainingState, mEnabledState);
                addState(mEvaluateState, mEnabledState);
                addState(mCalibrateState, mEnabledState);
                addState(mDeleteState, mEnabledState);
            addState(mDisabledState, mDefaultState);
        //@formatter:on
        setInitialState(mDisabledState);

        // For state machine logging
        setLogRecSize(100);
        setLogOnlyTransitions(false);
    }

    @NonNull
    @Override
    public Predictor getPredictor(@NonNull String appId) {
        if (!FLS_APP_ID_LIST.contains(appId)) {
            throw new IllegalArgumentException("invalid appId: " + appId);
        }
        return Objects.requireNonNull(mPredictorMap.get(appId));
    }

    @Override
    public void setFeatureEnabled(@NonNull String appId, boolean enabled) {
        if (!FLS_APP_ID_LIST.contains(appId)) {
            throw new IllegalArgumentException("invalid appId: " + appId);
        }
        mFeatureStatusMap.put(appId, enabled);
        sendMessage(MSG_FEATURE_STATUS_CHANGED);
    }

    @NonNull
    @Override
    public FLSystemStatus getSystemStatus() {
        return mSystemStatus;
    }

    @Override
    public void addSystemStatusListener(@NonNull FLSystemStatusListener listener,
            @NonNull String appId) {
        synchronized (mSystemStatusListeners) {
            mSystemStatusListeners.put(listener, appId);
        }
    }

    @Override
    public void removeSystemStatusListener(@NonNull FLSystemStatusListener listener) {
        synchronized (mSystemStatusListeners) {
            mSystemStatusListeners.remove(listener);
        }
    }

    @Override
    public boolean checkDcCondition(String appId) {
        return mTrainingDataAccessor.count(appId, DataType.TRAINING) >= getAppidSpecificConfig(
                appId).getDataCountThreshold();
    }

    @Override
    public float getPositiveRate(String appId) {
        int numOfData = mTrainingDataAccessor.count(appId, DataType.TRAINING_AND_TEST);
        if (numOfData != 0) {
            float numOfPositiveLabel = mTrainingDataAccessor.count(appId,
                    getAppidSpecificConfig(appId).getPositiveLabelThreshold());
            return (numOfPositiveLabel / numOfData);
        }
        return 0f;
    }

    @Override
    public void dump(FileDescriptor fd, PrintWriter writer, String[] args) {
        boolean verbose = args.length > 0 && "-v".equals(args[0]);
        writer.println("\n<<< FL System >>>\n");
        // Dump the current state of the state machine
        super.dump(fd, writer, args);
        // Dump the server configuration
        String testFile = SystemProperties.get(PROP_FLS_TEST_CLIENT_CONFIG_FILE,
                mContext.getResources().getString(
                        R.string.config_fl_system_test_client_config_file));
        writer.println("Server:");
        writer.println(" Environment: " + SystemProperties.get(PROP_FLS_SERVER_ENV,
                mContext.getResources().getString(R.string.config_fl_system_server_env)));
        writer.println(" Config file: " + (!testFile.isEmpty() ? testFile
                : FLS_CDN_CLIENT_CONFIG_FILENAME));
        // Dump the current client configuration
        ClientConfig clientConfig = mClientConfigAccessor.get();
        writer.println("Client config:");
        writer.println(" Name: <" + clientConfig.getConfigurationName() + ">");
        writer.println(" Mode: " + clientConfig.getGeneralConfiguration().getOperationMode());
        if (verbose) {
            writer.println(new GsonBuilder().setPrettyPrinting().create().toJson(clientConfig));
        }
        // Dump AppID specific status
        writer.println("AppID status:");
        FLS_APP_ID_LIST.forEach(appId -> {
            FLFeatureStatus featureStatus = mSystemStatus.getFeatureStatus(appId);
            writer.println(" " + appId + ":");
            writer.println("  Prediction: " + (featureStatus.isPredictionEnabled() ? "enabled"
                    : "disabled") + (getAppidSpecificConfig(appId).getInferenceEnabled() ? ""
                    : " (by config)"));
            writer.println(
                    "  Model type: " + ModelType.valueOf(FLPreferenceAccessor.getModelType(appId)));
            writer.println("  Model version: " + FLPreferenceAccessor.getModelVersion(appId));
            writer.println(String.format("  DC/PR condition: %s (DC threshold %s, PR threshold %s)",
                    isDcPrConditionPassed(appId) ? "passed" : "not passed",
                    getAppidSpecificConfig(appId).getDataCountThreshold(),
                    getAppidSpecificConfig(appId).getPositiveRateThreshold()));
            writer.println("  Data collection session: " + featureStatus.isDataCollectionSession());
        });
        // Dump the preferences
        writer.println("Preferences:");
        FLPreferenceAccessor.getSharedPreferences().getAll().entrySet().stream()
                // Remove binary entry
                .filter(e -> !e.getKey().equals(KEY_CLIENT_CONFIG_AS_STRING))
                .sorted(Map.Entry.comparingByKey())
                .forEach(e -> {
                    if (e.getKey().endsWith("_TIME") || e.getKey().contains("_TIME@")) {
                        Instant instant = Instant.ofEpochMilli((long) e.getValue());
                        ZonedDateTime zonedDateTime = ZonedDateTime.ofInstant(instant,
                                ZoneId.systemDefault());
                        writer.format(" %s: %s (%s)\n", e.getKey(), e.getValue(),
                                zonedDateTime.format(DUMP_DATETIME_FORMATTER));
                    } else {
                        writer.format(" %s: %s\n", e.getKey(), e.getValue());
                    }
                });
        // Dump misc information
        writer.println("UsageDataCollection: " + (usageDataCollectionAllowed() ? "allowed"
                : "not allowed"));
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
        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            // Delete internal data except training DB when preference format version is changed.
            // E.g, this runs at T-OSV (Nagara S -> Nagara T). And also runs at first boot as
            // |getPrefsVersion| doesn't return CURRENT_VERSION in this case.
            if (FLPreferenceAccessor.getPrefsVersion() != FLPreferenceAccessor.CURRENT_VERSION) {
                Log.v(TAG, "Cleanup internal data (as certain updates or first boot detected)");
                // Remove all values first and set format version to current version.
                FLPreferenceAccessor.getSharedPreferences().edit()
                        .putInt(KEY_PREFS_VERSION, FLPreferenceAccessor.CURRENT_VERSION)
                        .clear()
                        .apply();
                mClientConfigAccessor.clearCache(); // Clear internal cache just in case
                // Delete entire data directory
                Path dataRootDir = mContext.getFilesDir().toPath().resolve(FLS_DATA_DIR);
                try {
                    PathUtils.deleteDirectory(dataRootDir);
                } catch (IOException ignored) {
                }
            }

            // Setup the directories for FL library
            //noinspection ResultOfMethodCallIgnored
            mPredictManagerDataDir.toFile().mkdirs();
            //noinspection ResultOfMethodCallIgnored
            mTrainManagerDataDir.toFile().mkdirs();
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            return HANDLED;
        }

        @Override
        public void exit() {
            Log.v(TAG, getName() + " exited");
        }
    }

    private class EnabledState extends State {
        private final Random mRandom = new Random();

        /**
         * This callback is mainly used to detect wifi connection event for upload/download
         * trigger. Needs to be placed at the enabled state to ensure |mUsableWifiNetwork| is
         * always up to date at all child states.
         */
        private final NetworkCallback mDefaultNetworkCallback = new NetworkCallback() {
            @Override
            public void onCapabilitiesChanged(@NonNull Network network,
                    @NonNull NetworkCapabilities nc) {
                super.onCapabilitiesChanged(network, nc);
                if (nc.hasTransport(NetworkCapabilities.TRANSPORT_WIFI)
                        // The capabilities set by default in |NetworkCapabilities|
                        && nc.hasCapability(NetworkCapabilities.NET_CAPABILITY_NOT_RESTRICTED)
                        && nc.hasCapability(NetworkCapabilities.NET_CAPABILITY_TRUSTED)
                        && nc.hasCapability(NetworkCapabilities.NET_CAPABILITY_NOT_VPN)
                        // The capabilities required for us - internet reachability and not metered
                        && nc.hasCapability(NetworkCapabilities.NET_CAPABILITY_INTERNET)
                        && nc.hasCapability(NetworkCapabilities.NET_CAPABILITY_VALIDATED)
                        && nc.hasCapability(NetworkCapabilities.NET_CAPABILITY_NOT_METERED)) {
                    if (mUsableWifiNetwork == null) {
                        mUsableWifiNetwork = network;
                        sendMessage(MSG_USABLE_WIFI_NETWORK_AVAILABLE);
                    }
                } else {
                    if (mUsableWifiNetwork != null) {
                        mUsableWifiNetwork = null;
                        sendMessage(MSG_USABLE_WIFI_NETWORK_LOST);
                    }
                }
            }

            @Override
            public void onLost(@NonNull Network network) {
                super.onLost(network);
                if (mUsableWifiNetwork != null) {
                    mUsableWifiNetwork = null;
                    sendMessage(MSG_USABLE_WIFI_NETWORK_LOST);
                }
            }
        };

        /**
         * This callback is used to detect screen and battery charging event to check conditions for
         * running the FL task(s)
         */
        private final BroadcastReceiver mConditionChangeReceiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                if (Intent.ACTION_SCREEN_OFF.equals(intent.getAction())) {
                    sendMessage(MSG_SCREEN_OFF);
                }
                checkFLTaskCondition();
            }
        };

        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            ClientConfig clientConfig = mClientConfigAccessor.get();
            Log.v(TAG, "Using client config: <" + clientConfig.getConfigurationName() + ">");
            Log.v(TAG, "Current operation mode: " + clientConfig.getGeneralConfiguration()
                    .getOperationMode());

            FLS_APP_ID_LIST.forEach(appId -> {
                AppidSpecificConfig config = getAppidSpecificConfig(appId);
                // Update the data retention policy as it may be changed
                try {
                    mTrainingDataAccessor.setDataRetentionPolicy(appId,
                            config.getMaxNumOfTrainingSession(),
                            config.getMaxNumOfTrainingSessionPerBssid(),
                            config.getMaxPeriodDaysOfTrainingSession());
                    // Update DC/PR condition as threshold may be changed, and
                    // set calibration required flag if DC/PR condition is now changed
                    boolean preCondition = isDcPrConditionPassed(appId);
                    boolean curCondition = checkDcPrCondition(appId);
                    if (preCondition != curCondition) {
                        // Change DC/PR condition
                        mDcPrConditions.put(appId, curCondition);
                        updateCalibrationStatus(appId, true /* skipIntervalCheck */);
                    }
                } catch (SQLiteDiskIOException e) {
                    Log.e(TAG, "Failed to open database: " + e);
                    transitionTo(mDisabledState);
                    return;
                }
            });

            // Register default network callback for upload/download sequence trigger
            mConnectivityManager.registerDefaultNetworkCallback(mDefaultNetworkCallback,
                    mFLMainHandler);
            // Register screen and battery charging callback for checking FL task(s) conditions
            IntentFilter intentFilter = new IntentFilter();
            intentFilter.addAction(Intent.ACTION_SCREEN_ON);
            intentFilter.addAction(Intent.ACTION_SCREEN_OFF);
            intentFilter.addAction(Intent.ACTION_POWER_CONNECTED);
            intentFilter.addAction(Intent.ACTION_POWER_DISCONNECTED);
            mContext.registerReceiver(mConditionChangeReceiver, intentFilter);
            // Initial conditions check for running FL task
            checkFLTaskCondition();
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            boolean handleStatus = HANDLED;
            switch (message.what) {
                case MSG_FEATURE_STATUS_CHANGED:
                    if (!mFeatureStatusMap.containsValue(true)) {
                        transitionTo(mDisabledState);
                    }
                    break;
                case MSG_ADD_TRAINING_DATA: {
                    @SuppressWarnings("unchecked")
                    Pair<String, DataSet> pair = (Pair<String, DataSet>) message.obj;
                    String appId = pair.first;
                    DataSet trainingData = pair.second;
                    try {
                        // Store the data for training/evaluation
                        mTrainingDataAccessor.add(appId, trainingData, System.currentTimeMillis(),
                                determineTrainingOrEvaluationData());
                        // Update average value of label
                        Objects.requireNonNull(mPredictorMap.get(appId)).setAverageOfLabel(
                                mTrainingDataAccessor.getAverageOfLabel(appId));
                        // Check DC/PR condition
                        boolean preCondition = isDcPrConditionPassed(appId);
                        boolean curCondition = checkDcPrCondition(appId);
                        if (preCondition != curCondition) {
                            // Change DC/PR condition
                            mDcPrConditions.put(appId, curCondition);
                            updateCalibrationStatus(appId, true /* skipIntervalCheck */);
                            transitionTo(mDisabledState);
                        }
                    } catch (SQLiteFullException | SQLiteDiskIOException e) {
                        Log.e(TAG, "Failed to open database: " + e);
                    }
                    break;
                }
                case MSG_UPDATE_SYSTEM_STATUS:
                    updateSystemStatus();
                    break;
                case MSG_FL_TASK_CONDITION_CHECK:
                    if (!mIsFLTaskRunnable) {
                        mIsFLTaskRunnable = true;
                        sendMessage(MSG_FL_TASK_CONDITION_RUNNABLE);
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
            removeMessages(MSG_FL_TASK_CONDITION_CHECK);
            mConnectivityManager.unregisterNetworkCallback(mDefaultNetworkCallback);
            mContext.unregisterReceiver(mConditionChangeReceiver);
            mUsableWifiNetwork = null;
            mIsFLTaskRunnable = false;
        }

        private DataType determineTrainingOrEvaluationData() {
            return TRAINING_DATA_RATIO >= (mRandom.nextInt(100) + 1) ? DataType.TRAINING
                    : DataType.TEST;
        }

        private void checkFLTaskCondition() {
            if (!mPowerManager.isInteractive() && isBatteryCharging()) {
                Log.v(TAG, "sendMessageDelayed: MSG_FL_TASK_CONDITION_CHECK");
                sendMessageDelayed(MSG_FL_TASK_CONDITION_CHECK, FL_TASK_START_INTERVAL);
            } else {
                mIsFLTaskRunnable = false;
                Log.v(TAG, "removeMessages: MSG_FL_TASK_CONDITION_CHECK");
                removeMessages(MSG_FL_TASK_CONDITION_CHECK);
            }
        }

        private boolean isBatteryCharging() {
            IntentFilter intentFilter = new IntentFilter(Intent.ACTION_BATTERY_CHANGED);
            Intent batteryStatus = mContext.registerReceiver(null, intentFilter);
            return batteryStatus.getIntExtra(BatteryManager.EXTRA_PLUGGED, -1) > 0;
        }
    }

    // Don't access FL library in this state (except |enter| and |exit|)
    // PredictManagerWrapper and PredictorImpl classes/instances can only be accessed under
    // PredictableState
    private class PredictableState extends State {
        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            OperationMode mode = mClientConfigAccessor.get().getGeneralConfiguration()
                    .getOperationMode();
            if (mode == OperationMode.NORMAL && getFirstPendingPriorityFLTask() == null) {
                // Configure all predictors
                mPredictorMap.forEach((appId, impl) -> {
                    String modelVersion = FLPreferenceAccessor.getModelVersion(appId);
                    ModelType modelType = ModelType.valueOf(
                            FLPreferenceAccessor.getModelType(appId));
                    // Update the predictor parameters as they may be changed
                    AppidSpecificConfig config = getAppidSpecificConfig(appId);
                    impl.setInferenceThreshold(config.getInferenceThreshold());
                    impl.setDataCollectionSessionRatio(
                            isDcPrConditionPassed(appId) ? config.getTrainingDataCollectionRatio()
                                    : 100 /* Always data collection session */);
                    impl.setModelVersion(modelVersion);
                    impl.setModelType(modelType);
                    // Set initial average value of label
                    try {
                        impl.setAverageOfLabel(mTrainingDataAccessor.getAverageOfLabel(appId));
                    } catch (SQLiteDiskIOException e) {
                        Log.e(TAG, "Failed to open database: " + e);
                        transitionTo(mDisabledState);
                        return;
                    }
                    // Enable prediction for this appId if condition met
                    if (modelVersion != null && config.getInferenceEnabled()) {
                        // Create PredictManager instance as model may be changed
                        impl.mWrapper.setPredictManager();
                    } else {
                        Log.v(TAG, "prediction is disabled for " + appId);
                    }
                });
                // Enable entire prediction from here (Don't access FL library from here)
                //  Note: prediction is not enabled for the appId(s) whose corresponding
                //  |setPredictManager| is not called in the above code.
                PredictManagerWrapper.setEntirePredictionEnabled(true);
            } else {
                if (mode != OperationMode.NORMAL) {
                    Log.v(TAG, "entire prediction is disabled (due to operation mode)");
                } else {
                    Log.v(TAG, "entire prediction is disabled (due to pending priority task)");
                }
            }
            updateSystemStatus(); // for prediction status change
        }

        @Override
        public void exit() {
            Log.v(TAG, getName() + " exited");
            // Disable entire prediction from here (Can access FL library from here)
            PredictManagerWrapper.setEntirePredictionEnabled(false);
            // Destroy PredictManager instances
            mPredictorMap.values().forEach(e -> e.mWrapper.releasePredictManager());
            updateSystemStatus(); // for prediction status change
        }
    }

    // Don't access FL library in this state
    private class NormalState extends State {

        /** This callback is used to detect the debug command for force download trigger */
        private final BroadcastReceiver mForceDownloadCommandReceiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                sendMessage(MSG_FORCE_DOWNLOAD_TRIGGER);
            }
        };

        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");

            // Register the debug command event for force download sequence trigger
            if (DEBUG_BUILD) {
                mContext.registerReceiver(mForceDownloadCommandReceiver,
                        new IntentFilter(ACTION_FLS_FORCE_DOWNLOAD),
                        Context.RECEIVER_EXPORTED);
            }

            // Run pending FL task(s) immediately if condition met
            //  The reason why this needs to be performed 'immediately' is deploy task should be
            //  handled as soon as corresponding client config is applied. This is to avoid
            //  any inconsistency with inference parameter(s) such as inference threshold.
            sendMessageAtFrontOfQueue(MSG_PROCESS_PENDING_FL_TASK_TRIGGER);
            // Start upload/download sequence if needed
            sendMessage(MSG_UPLOAD_AND_DOWNLOAD_TRIGGER);
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            boolean handleStatus = HANDLED;
            switch (message.what) {
                /* Pending FL task(s) and Calibration handling */
                case MSG_FL_TASK_CONDITION_RUNNABLE:
                case MSG_PROCESS_PENDING_FL_TASK_TRIGGER: {
                    State state = shouldRunFLTask();
                    if (state != null) {
                        transitionTo(state);
                    } else if (shouldStartCalibration()) {
                        transitionTo(mCalibrateState);
                    }
                    break;
                }
                /* Upload and Download handling */
                case MSG_UPLOAD_AND_DOWNLOAD_TRIGGER:
                case MSG_USABLE_WIFI_NETWORK_AVAILABLE:
                case MSG_SCREEN_OFF:
                    // Check if we should start the upload or download sequence
                    if (shouldStartUpload()) {
                        transitionTo(mUploadState);
                    } else if (shouldStartDownload()) {
                        transitionTo(mDownloadState);
                    }
                    break;
                case MSG_FORCE_DOWNLOAD_TRIGGER:
                    // Start download sequence forcibly
                    transitionTo(mDownloadState);
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
            if (DEBUG_BUILD) {
                mContext.unregisterReceiver(mForceDownloadCommandReceiver);
            }
        }

        private State shouldRunFLTask() {
            // The following conditions need to be fulfilled.
            //  1. Operation mode is NORMAL
            //  2. Any pending task exists
            //  3. FL task is runnable (only for train and evaluation)
            //  4. DC/PR condition (only for train and evaluation)
            OperationMode mode = mClientConfigAccessor.get().getGeneralConfiguration()
                    .getOperationMode();
            if (mode == OperationMode.NORMAL) {
                FLTask flTask = getFirstPendingPriorityFLTask();
                if (flTask != null) {
                    if (flTask.getTaskInfo().hasDeployInfo()) {
                        return mDeployState;
                    } else if (flTask.getTaskInfo().hasDeleteInfo()) {
                        return mDeleteState;
                    }
                }
                if (mIsFLTaskRunnable) {
                    flTask = getFirstPendingFLTask();
                    if (flTask != null) {
                        if (isDcPrConditionPassed(flTask.getTaskInfo().getAppID())) {
                            if (flTask.getTaskInfo().hasTrainInfo()) {
                                return mTrainingState;
                            } else if (flTask.getTaskInfo().hasEvaluationInfo()) {
                                return mEvaluateState;
                            }
                        }
                    }
                }
            }
            return null;
        }

        private boolean shouldStartCalibration() {
            // The following conditions need to be fulfilled.
            //  1. Operation mode is NORMAL
            //  2. FL task is runnable (maintain screen off and battery charging for a certain time)
            //  3. At least one of appIds requires calibration
            OperationMode mode = mClientConfigAccessor.get().getGeneralConfiguration()
                    .getOperationMode();
            FLS_APP_ID_LIST.forEach(appId -> updateCalibrationStatus(appId, false));
            return mode == OperationMode.NORMAL
                    && mIsFLTaskRunnable
                    && !mCalibrationRequiredAppIds.isEmpty();
        }

        private boolean shouldStartUpload() {
            // The following conditions need to be fulfilled.
            //  1. Operation mode is NORMAL
            //  2. Connected to non-metered wifi network
            //  3. Any upload data exists
            //  4. Entered the uploadable period
            //  5. User has given permission for data upload
            OperationMode mode = mClientConfigAccessor.get().getGeneralConfiguration()
                    .getOperationMode();
            long current = System.currentTimeMillis();
            return mode == OperationMode.NORMAL
                    && mUsableWifiNetwork != null
                    && !FLPreferenceAccessor.getPendingUploadFLTaskIndexList().isEmpty()
                    && current >= FLPreferenceAccessor.getUploadPeriodStartTime()
                    && current < FLPreferenceAccessor.getUploadPeriodEndTime()
                    && usageDataCollectionAllowed();
        }

        private boolean shouldStartDownload() {
            // The following conditions need to be fulfilled.
            //  1. Connected to non-metered wifi network
            //  2. Elapsed the download polling interval
            long current = System.currentTimeMillis();
            return mUsableWifiNetwork != null
                    && current >= FLPreferenceAccessor.getDownloadStartTime();
        }
    }

    // Don't access FL library in this state
    private class DownloadState extends State {
        private FLClientConfigDownloader mClientConfigDownloader;

        // 0.75h/1.5h/3h/6h/12h/24h/2d/4d/8d/16d/1m/1m...
        private final ExponentialBackoff mRetryDelayBackoff = new ExponentialBackoff(45, 10);

        private final FLClientConfigDownloader.StatusListener mStatusListener =
                new FLClientConfigDownloader.StatusListener() {
                    @Override
                    public void onSuccess(@NonNull ClientConfig clientConfig,
                            @Nullable Map<FLTask, byte[]> taskDataMap) {
                        sendMessage(MSG_DOWNLOAD_STATUS_SUCCESS,
                                Pair.create(clientConfig, taskDataMap));
                    }

                    @Override
                    public void onSkip(@Nullable String clientConfigHash) {
                        sendMessage(MSG_DOWNLOAD_STATUS_SKIP, clientConfigHash);
                    }

                    @Override
                    public void onFailure() {
                        sendMessage(MSG_DOWNLOAD_STATUS_FAILURE);
                    }
                };

        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            if (mClientConfigDownloader == null) {
                mClientConfigDownloader = new FLClientConfigDownloader(mContext);
            }

            mRetryDelayBackoff.setBackoffCount(
                    FLPreferenceAccessor.getDownloadRetryBackoffCount());

            // Start download sequence
            if (mUsableWifiNetwork != null) {
                mWakeLock.acquire(TimeUnit.SECONDS.toMillis(60)); // May not necessarily
                mClientConfigDownloader.download(mClientConfigAccessor.get(),
                        FLPreferenceAccessor.getSkippedClientConfigAsHash(), mStatusListener,
                        mUsableWifiNetwork);
            } else {
                sendMessage(MSG_DOWNLOAD_STATUS_FAILURE); // Could never happen
            }
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            boolean handleStatus = HANDLED;
            switch (message.what) {
                case MSG_DOWNLOAD_STATUS_SUCCESS: {
                    @SuppressWarnings("unchecked")
                    Pair<ClientConfig, Map<FLTask, byte[]>> pair =
                            (Pair<ClientConfig, Map<FLTask, byte[]>>) message.obj;
                    ClientConfig clientConfig = pair.first;
                    Map<FLTask, byte[]> taskDataMap = pair.second;
                    long currentTime = System.currentTimeMillis();

                    // Store latest client config
                    Editor editor = mClientConfigAccessor.saveToEditor(clientConfig);

                    // Store new task data if available
                    if (taskDataMap != null) {
                        // Delete the remaining upload data if exists
                        mFileManager.deleteAllUploadData();
                        editor.remove(KEY_PENDING_UPLOAD_FL_TASK_INDEX_LIST);
                        // Update upload period for task result upload
                        long uploadablePeriod = TimeUnit.HOURS.toMillis(
                                clientConfig.getGeneralConfiguration().getUploadablePeriodHours());
                        long uploadEndTime = addSafely(currentTime, uploadablePeriod);
                        editor.putLong(KEY_UPLOAD_PERIOD_START_TIME, currentTime)
                                .putLong(KEY_UPLOAD_PERIOD_END_TIME, uploadEndTime);
                        // Select task data to store only those for supported appId
                        // TODO: unnecessary task data should not be downloaded
                        taskDataMap = taskDataMap.entrySet().stream()
                                .filter(e -> FLS_APP_ID_LIST.contains(
                                        e.getKey().getTaskInfo().getAppID()))
                                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
                        // Delete the existing files first then store the new ones
                        if (!mFileManager.saveTaskData(taskDataMap)) {
                            Log.e(TAG, "Download post processing has not been completed (task data"
                                    + " update error)");
                            // Clean up the pending task lists as corresponding data have probably
                            // already been deleted (by |deleteAllUploadData| and |saveTaskData|)
                            FLPreferenceAccessor.getSharedPreferences().edit()
                                    .remove(KEY_PENDING_UPLOAD_FL_TASK_INDEX_LIST)
                                    .remove(KEY_PENDING_FL_TASK_INDEX_LIST)
                                    .remove(KEY_PENDING_PRIORITY_FL_TASK_INDEX_LIST)
                                    .apply();
                            updateDownloadStartTimeForFailure();
                            transitionTo(mNormalState);
                            break;
                        }
                        // Update the pending task list
                        editor.remove(KEY_PENDING_FL_TASK_INDEX_LIST)
                                .remove(KEY_PENDING_PRIORITY_FL_TASK_INDEX_LIST);
                        if (clientConfig.getFlTasksCount() > 0) {
                            List<Integer> pendingList = new ArrayList<>();
                            List<Integer> priorityPendingList = new ArrayList<>();
                            for (int i = 0; i < clientConfig.getFlTasksCount(); i++) {
                                FLTask flTask = clientConfig.getFlTasks(i);
                                PBTaskInfo pbTaskInfo = flTask.getTaskInfo();
                                if (!FLS_APP_ID_LIST.contains(pbTaskInfo.getAppID())) {
                                    Log.v(TAG, "Skip task due to unsupported appId: "
                                            + pbTaskInfo.getTaskID());
                                    continue;
                                }
                                if (pbTaskInfo.hasDeployInfo()) {
                                    String modelVersion = FLPreferenceAccessor.getModelVersion(
                                            pbTaskInfo.getAppID());
                                    if (modelVersion != null && modelVersion.equals(
                                            pbTaskInfo.getTaskID())) {
                                        Log.v(TAG, "Skip deploy due to duplicate model version: "
                                                + modelVersion);
                                        mFileManager.deleteTaskData(flTask);
                                    } else {
                                        // For deploy task which needs to be prioritized
                                        priorityPendingList.add(i);
                                    }
                                } else {
                                    List<String> completedTaskIdList =
                                            FLPreferenceAccessor.getCompletedFLTaskIdList();
                                    if (completedTaskIdList.contains(pbTaskInfo.getTaskID())) {
                                        Log.v(TAG, "Skip task because it has been completed: "
                                                + pbTaskInfo.getTaskID());
                                        mFileManager.deleteTaskData(flTask);
                                    } else if (pbTaskInfo.hasDeleteInfo()) {
                                        // For delete task which needs to be prioritized
                                        priorityPendingList.add(i);
                                    } else {
                                        // For other tasks
                                        pendingList.add(i);
                                    }
                                }
                            }
                            if (!pendingList.isEmpty()) {
                                editor.putString(KEY_PENDING_FL_TASK_INDEX_LIST,
                                        toCommaSeparatedString(pendingList));
                            }
                            if (!priorityPendingList.isEmpty()) {
                                editor.putString(KEY_PENDING_PRIORITY_FL_TASK_INDEX_LIST,
                                        toCommaSeparatedString(priorityPendingList));
                            }
                        }
                    } // else - there is no difference from current version

                    // Calculate start time for next download
                    long pollFreq = TimeUnit.MINUTES.toMillis(clientConfig
                            .getGeneralConfiguration().getClientPollingFrequencyMins());
                    long downloadStartTime = addSafely(currentTime, pollFreq);

                    // Update start time and failure count before going to other state
                    editor.putLong(KEY_DOWNLOAD_START_TIME, downloadStartTime)
                            .remove(KEY_DOWNLOAD_RETRY_BACKOFF_COUNT)
                            .remove(KEY_SKIPPED_CLIENT_CONFIG_AS_HASH);

                    // Update all related preferences at once
                    editor.commit();
                    mClientConfigAccessor.clearCache();

                    // Go to the disabled state once so that latest configuration will be
                    // reflected properly.
                    // NOTE: This will disable prediction for a moment so it might be better to
                    // get rid of this limitation if possible.
                    transitionTo(mDisabledState);
                    break;
                }
                case MSG_DOWNLOAD_STATUS_SKIP: {
                    String hash = (String) message.obj;
                    Editor editor = FLPreferenceAccessor.getSharedPreferences().edit();
                    if (hash != null) {
                        editor.putString(KEY_SKIPPED_CLIENT_CONFIG_AS_HASH, hash);
                    }
                    // Calculate start time for next download
                    long pollFreq = TimeUnit.MINUTES.toMillis(mClientConfigAccessor.get()
                            .getGeneralConfiguration().getClientPollingFrequencyMins());
                    long downloadStartTime = addSafely(System.currentTimeMillis(), pollFreq);
                    editor.putLong(KEY_DOWNLOAD_START_TIME, downloadStartTime)
                            .remove(KEY_DOWNLOAD_RETRY_BACKOFF_COUNT)
                            .apply();
                    transitionTo(mNormalState); // No new config found
                    break;
                }
                case MSG_DOWNLOAD_STATUS_FAILURE: {
                    updateDownloadStartTimeForFailure();
                    transitionTo(mNormalState);
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
            if (mWakeLock.isHeld()) {
                mWakeLock.release();
            }
        }

        private void updateDownloadStartTimeForFailure() {
            // Update start time for next download (retry)
            long retryDelay = TimeUnit.MINUTES.toMillis(mRetryDelayBackoff.nextBackoff());
            long downloadStartTime = addSafely(System.currentTimeMillis(), retryDelay);
            FLPreferenceAccessor.getSharedPreferences().edit()
                    .putLong(KEY_DOWNLOAD_START_TIME, downloadStartTime)
                    .putInt(KEY_DOWNLOAD_RETRY_BACKOFF_COUNT,
                            mRetryDelayBackoff.getBackoffCount())
                    .apply();
        }
    }

    // Don't access FL library in this state
    private class UploadState extends State {
        private FLTask mUploadFLTask;

        /** The private key of the client certificate used for mTLS authentication */
        @Nullable
        private PrivateKey mPrivateKey;

        private FLResultUploader mResultUploader;

        // 0.75h/1.5h/3h/6h/12h/24h/2d/4d/4d...
        private final ExponentialBackoff mRetryDelayBackoff = new ExponentialBackoff(45, 7);

        private final FLResultUploader.StatusListener mStatusListener =
                new FLResultUploader.StatusListener() {
                    @Override
                    public void onSuccess() {
                        sendMessage(MSG_UPLOAD_STATUS_SUCCESS);
                    }

                    @Override
                    public void onFailure(boolean retryable) {
                        sendMessage(MSG_UPLOAD_STATUS_FAILURE, retryable ? 1 : 0);
                    }
                };

        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            if (mResultUploader == null) {
                mResultUploader = new FLResultUploader(mContext);
            }

            mRetryDelayBackoff.setBackoffCount(FLPreferenceAccessor.getUploadRetryBackoffCount());

            // Start upload sequence
            mUploadFLTask = getFirstPendingUploadFLTask();
            Path uploadDataPath = mFileManager.getUploadDataPath(mUploadFLTask);
            X509Certificate clientCertificate = mCertificateAccessor.getCertificate();
            mPrivateKey = mCertificateAccessor.getKey();
            if (mUsableWifiNetwork != null && mUploadFLTask != null && uploadDataPath != null
                    && clientCertificate != null && mPrivateKey != null) {
                mWakeLock.acquire(TimeUnit.SECONDS.toMillis(60)); // May not necessarily
                mResultUploader.upload(mUploadFLTask, uploadDataPath, mStatusListener,
                        clientCertificate, mPrivateKey, mUsableWifiNetwork);
            } else {
                if (clientCertificate == null || mPrivateKey == null) {
                    // This device probably doesn't have correct setup of SecureDataManager.
                    Log.e(TAG, "failed to access SecureDataManager");
                }
                sendMessage(MSG_UPLOAD_STATUS_FAILURE);
            }
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            boolean handleStatus = HANDLED;
            switch (message.what) {
                case MSG_UPLOAD_STATUS_SUCCESS:
                    // Update pending upload list as current upload has been completed
                    markAsUploadCompleted();
                    transitionTo(mNormalState);
                    break;
                case MSG_UPLOAD_STATUS_FAILURE: {
                    boolean retryable = (message.arg1 == 1);
                    if (retryable) {
                        // Update start time for next upload (retry)
                        long retryDelay = TimeUnit.MINUTES.toMillis(
                                mRetryDelayBackoff.nextBackoff());
                        long startTime = addSafely(System.currentTimeMillis(), retryDelay);
                        FLPreferenceAccessor.getSharedPreferences().edit()
                                .putLong(KEY_UPLOAD_PERIOD_START_TIME, startTime)
                                .putInt(KEY_UPLOAD_RETRY_BACKOFF_COUNT,
                                        mRetryDelayBackoff.getBackoffCount())
                                .apply();
                    } else {
                        // Update pending upload list to avoid current upload retry
                        markAsUploadCompleted();
                    }
                    transitionTo(mNormalState);
                    break;
                }
                case MSG_FEATURE_STATUS_CHANGED:
                case MSG_ADD_TRAINING_DATA:
                    // To prevent state transition while upload is in progress
                    deferMessage(message);
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
            mUploadFLTask = null;
            if (mWakeLock.isHeld()) {
                mWakeLock.release();
            }
            // Wipe out the private key on memory
            if (mPrivateKey != null) {
                try {
                    mPrivateKey.destroy();
                } catch (DestroyFailedException ignored) {
                    // |destroy| method seems to be not implemented so the exception is thrown
                    // every time on current platform.
                }
                mPrivateKey = null;
            }
        }

        private void markAsUploadCompleted() {
            if (mUploadFLTask != null) {
                mFileManager.deleteUploadData(mUploadFLTask);
                List<Integer> idxList = FLPreferenceAccessor.getPendingUploadFLTaskIndexList();
                idxList.remove(Integer.valueOf(getFLTaskIndex(mUploadFLTask)));
                FLPreferenceAccessor.getSharedPreferences().edit()
                        .putString(KEY_PENDING_UPLOAD_FL_TASK_INDEX_LIST,
                                toCommaSeparatedString(idxList))
                        // Reset the counter only when upload has been completed
                        .remove(KEY_UPLOAD_RETRY_BACKOFF_COUNT)
                        .apply();
            }
        }
    }

    private class DeployState extends State {

        private static final int ERROR_LIB_DEPLOY = 1;
        private static final int ERROR_LIB_CONSTRUCT = 2;
        private static final int ERROR_WRITE_DATA = 3;
        private static final int ERROR_INVALID_STATE = 4;
        private static final int ERROR_RUNTIME_EXCEPTION = 5;

        private FLTask mFLDeployTask;

        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            // Take first pending deploy task
            // (Note that the task will be removed even if result is failure. This is to prevent
            // possible failure loop)
            FLTask flTask = takeFirstPendingPriorityFLTask();
            Path taskDataPath = mFileManager.getTaskDataPath(flTask);
            if (flTask != null && flTask.getTaskInfo().hasDeployInfo() && taskDataPath != null) {
                mFLDeployTask = flTask;
                mFLLibHandler.post(() -> { // Perform deploy on the separate thread
                    boolean success = false;
                    int errCode = 0, errSubCode = 0;
                    PBTaskInfo pbTaskInfo = mFLDeployTask.getTaskInfo();
                    try {
                        DeployManager deployManager = new DeployManager(mTrainManagerDataDir,
                                mPredictManagerDataDir);
                        // Create the all data file for calibration
                        Stream<DataSet> dataSetStream = applyModifier(pbTaskInfo.getAppID(),
                                mTrainingDataAccessor.get(pbTaskInfo.getAppID(),
                                        DataType.TRAINING_AND_TEST));
                        DataMetadata dataMetadata = mFileManager.writeDataFile(mFLDeployTask,
                                dataSetStream);
                        if (dataMetadata != null) {
                            // Delete old model information
                            int ret = deployManager.stop(pbTaskInfo.getAppID());
                            if (ret != 0) {
                                Log.w(TAG, "failed to stop: " + ret);
                            }
                            // Deploy the model
                            ret = deployManager.deploy(pbTaskInfo.getFLID(), pbTaskInfo.getTaskID(),
                                    dataMetadata, pbTaskInfo.getDeployInfo(), taskDataPath);
                            if (ret == 0) {
                                success = true;
                            } else {
                                Log.e(TAG, "failed to complete deploy: " + ret);
                                errCode = ERROR_LIB_DEPLOY;
                                errSubCode = ret;
                            }
                        } else {
                            Log.e(TAG, "failed to create calibration data file");
                            errCode = ERROR_WRITE_DATA;
                        }
                    } catch (FLException e) {
                        Log.e(TAG, "failed to create deploy manager: " + e);
                        errCode = ERROR_LIB_CONSTRUCT;
                    } catch (RuntimeException e) {
                        Log.e(TAG, "unexpected runtime exception happened: " + e);
                        errCode = ERROR_RUNTIME_EXCEPTION;
                    }

                    if (success) {
                        sendMessage(MSG_DEPLOY_STATUS_SUCCESS);
                    } else {
                        sendMessage(MSG_DEPLOY_STATUS_FAILURE, errCode, errSubCode);
                    }
                });
            } else { // Should never happen
                sendMessage(MSG_DEPLOY_STATUS_FAILURE, ERROR_INVALID_STATE);
            }
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            boolean handleStatus = HANDLED;
            switch (message.what) {
                case MSG_DEPLOY_STATUS_SUCCESS: {
                    // Update model version and last calibration time
                    PBTaskInfo taskInfo = mFLDeployTask.getTaskInfo();
                    String appId = taskInfo.getAppID();
                    FLPreferenceAccessor.getSharedPreferences().edit()
                            .putInt(MODEL_TYPE_KEY_GENERATOR.apply(appId),
                                    taskInfo.getDeployInfo().getModelType().getNumber())
                            .putString(MODEL_VERSION_KEY_GENERATOR.apply(appId),
                                    taskInfo.getTaskID())
                            .putLong(LAST_CALIBRATION_TIME_KEY_GENERATOR.apply(appId),
                                    System.currentTimeMillis())
                            .apply();
                    transitionTo(mNormalState);
                    break;
                }
                case MSG_DEPLOY_STATUS_FAILURE: {
                    int code = message.arg1, subCode = message.arg2;
                    Log.e(TAG, "failed to deploy (code=" + code + ", subCode=" + subCode + ")");
                    // TODO: need to consider what should do for this case
                    if (code == ERROR_LIB_DEPLOY) {
                        // Remove model version and last calibration time as model is
                        // most likely released
                        String appId = mFLDeployTask.getTaskInfo().getAppID();
                        FLPreferenceAccessor.getSharedPreferences().edit()
                                .remove(MODEL_TYPE_KEY_GENERATOR.apply(appId))
                                .remove(MODEL_VERSION_KEY_GENERATOR.apply(appId))
                                .remove(LAST_CALIBRATION_TIME_KEY_GENERATOR.apply(appId))
                                .apply();
                    }
                    transitionTo(mNormalState);
                    break;
                }
                case MSG_FEATURE_STATUS_CHANGED:
                case MSG_ADD_TRAINING_DATA:
                    // To prevent state transition while deploy is in progress
                    deferMessage(message);
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
            if (mFLDeployTask != null) {
                mFileManager.deleteTaskData(mFLDeployTask);
                mFLDeployTask = null;
            }
        }
    }

    private class TrainingState extends State {

        private static final int ERROR_LIB_TRAIN = 1;
        private static final int ERROR_LIB_CONSTRUCT = 2;
        private static final int ERROR_PREPARE_UPLOAD_DIR = 3;
        private static final int ERROR_WRITE_DATA = 4;
        private static final int ERROR_SAVE_UPLOAD_DATA = 5;
        private static final int ERROR_INVALID_STATE = 6;
        private static final int ERROR_RUNTIME_EXCEPTION = 7;

        private FLTask mFLTrainTask;

        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            // Take first pending training task
            // (Note that the task will be removed even if result is failure. This is to prevent
            // possible failure loop)
            FLTask flTask = takeFirstPendingFLTask();
            Path taskDataPath = mFileManager.getTaskDataPath(flTask);
            if (flTask != null && flTask.getTaskInfo().hasTrainInfo() && taskDataPath != null) {
                mFLTrainTask = flTask;
                mFLLibHandler.post(() -> { // Perform training on the separate thread
                    boolean success = false;
                    int errCode = 0, errSubCode = 0;
                    PBTaskInfo pbTaskInfo = mFLTrainTask.getTaskInfo();
                    try {
                        TrainManager trainManager = new TrainManager(mTrainManagerDataDir);
                        // Create output directory
                        boolean ret = mFileManager.prepareUploadDataPath(mFLTrainTask);
                        Path outputPath = mFileManager.getUploadDataOutputPath(mFLTrainTask);
                        if (ret && outputPath != null) {
                            // Create training data file
                            Stream<DataSet> dataSetStream = applyModifier(pbTaskInfo.getAppID(),
                                    mTrainingDataAccessor.get(pbTaskInfo.getAppID(),
                                            DataType.TRAINING));
                            DataMetadata dataMetadata = mFileManager.writeDataFile(mFLTrainTask,
                                    dataSetStream);
                            if (dataMetadata != null) {
                                // Train the model
                                TrainResult result = trainManager.train(pbTaskInfo.getFLID(),
                                        pbTaskInfo.getTaskID(), dataMetadata,
                                        pbTaskInfo.getTrainInfo(), taskDataPath, outputPath);
                                if (result.getStatus() == 0) {
                                    // Create and Save PBTaskResult object
                                    PBTaskResult pbTaskResult = PBTaskResult.newBuilder()
                                            .setFLLibVersion(pbTaskInfo.getFLLibVersion())
                                            .setFLID(pbTaskInfo.getFLID())
                                            .setTaskID(pbTaskInfo.getTaskID())
                                            .setTrainResult(result.getTrainResult())
                                            .build();
                                    if (mFileManager.saveUploadPBTaskResultData(mFLTrainTask,
                                            pbTaskResult)) {
                                        success = true;
                                    } else {
                                        Log.e(TAG, "failed to save pb task result data");
                                        errCode = ERROR_SAVE_UPLOAD_DATA;
                                    }
                                } else {
                                    errCode = ERROR_LIB_TRAIN;
                                    errSubCode = result.getStatus();
                                }
                            } else {
                                Log.e(TAG, "failed to create training data file");
                                errCode = ERROR_WRITE_DATA;
                            }
                        } else {
                            Log.e(TAG, "failed to prepare output directory");
                            errCode = ERROR_PREPARE_UPLOAD_DIR;
                        }
                    } catch (FLException e) {
                        Log.e(TAG, "failed to create train manager: " + e);
                        errCode = ERROR_LIB_CONSTRUCT;
                    } catch (RuntimeException e) {
                        Log.e(TAG, "unexpected runtime exception happened: " + e);
                        errCode = ERROR_RUNTIME_EXCEPTION;
                    }

                    if (success) {
                        sendMessage(MSG_TRAINING_STATUS_SUCCESS);
                    } else {
                        mFileManager.deleteUploadData(mFLTrainTask);
                        sendMessage(MSG_TRAINING_STATUS_FAILURE, errCode, errSubCode);
                    }
                });
            } else { // Should never happen
                sendMessage(MSG_TRAINING_STATUS_FAILURE, ERROR_INVALID_STATE);
            }
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            boolean handleStatus = HANDLED;
            switch (message.what) {
                case MSG_TRAINING_STATUS_SUCCESS: {
                    // Update pending upload list for uploading training result
                    List<Integer> idxList = FLPreferenceAccessor.getPendingUploadFLTaskIndexList();
                    idxList.add(getFLTaskIndex(mFLTrainTask));
                    FLPreferenceAccessor.getSharedPreferences().edit()
                            .putString(KEY_PENDING_UPLOAD_FL_TASK_INDEX_LIST,
                                    toCommaSeparatedString(idxList))
                            .apply();
                    transitionTo(mNormalState);
                    break;
                }
                case MSG_TRAINING_STATUS_FAILURE: {
                    int code = message.arg1, subCode = message.arg2;
                    Log.e(TAG, "failed to train (code=" + code + ", subCode=" + subCode + ")");
                    // TODO: need to consider what should do for this case
                    transitionTo(mNormalState);
                    break;
                }
                case MSG_FEATURE_STATUS_CHANGED:
                case MSG_ADD_TRAINING_DATA:
                    // To prevent state transition while training is in progress
                    deferMessage(message);
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
            if (mFLTrainTask != null) {
                // Update completed taskId list to prevent duplicate training
                List<String> taskIdList = FLPreferenceAccessor.getCompletedFLTaskIdList();
                addCompletedFLTaskIdList(taskIdList, mFLTrainTask.getTaskInfo().getTaskID());
                FLPreferenceAccessor.getSharedPreferences().edit()
                        .putString(KEY_COMPLETED_FL_TASK_ID_LIST, String.join(",", taskIdList))
                        .apply();
                mFileManager.deleteTaskData(mFLTrainTask);
                mFLTrainTask = null;
            }
        }
    }

    private class EvaluateState extends State {

        private static final int ERROR_LIB_EVALUATION = 1;
        private static final int ERROR_LIB_CONSTRUCT = 2;
        private static final int ERROR_PREPARE_UPLOAD_DIR = 3;
        private static final int ERROR_WRITE_DATA = 4;
        private static final int ERROR_SAVE_UPLOAD_DATA = 5;
        private static final int ERROR_INVALID_STATE = 6;
        private static final int ERROR_RUNTIME_EXCEPTION = 7;

        private FLTask mFLEvaluationTask;

        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            // Take first pending evaluation task
            // (Note that the task will be removed even if result is failure. This is to prevent
            // possible failure loop)
            FLTask flTask = takeFirstPendingFLTask();
            Path taskDataPath = mFileManager.getTaskDataPath(flTask);
            if (flTask != null && flTask.getTaskInfo().hasEvaluationInfo()
                    && taskDataPath != null) {
                mFLEvaluationTask = flTask;
                mFLLibHandler.post(() -> { // Perform evaluation on the separate thread
                    boolean success = false;
                    int errCode = 0, errSubCode = 0;
                    PBTaskInfo pbTaskInfo = mFLEvaluationTask.getTaskInfo();
                    try {
                        TrainManager trainManager = new TrainManager(mTrainManagerDataDir);
                        // Create output directory
                        boolean ret = mFileManager.prepareUploadDataPath(mFLEvaluationTask);
                        Path outputPath = mFileManager.getUploadDataOutputPath(mFLEvaluationTask);
                        if (ret && outputPath != null) {
                            // Create evaluation data file
                            Stream<DataSet> dataSetStream = applyModifier(pbTaskInfo.getAppID(),
                                    mTrainingDataAccessor.get(pbTaskInfo.getAppID(),
                                            DataType.TEST));
                            DataMetadata dataMetadata = mFileManager.writeDataFile(
                                    mFLEvaluationTask, dataSetStream);
                            if (dataMetadata != null) {
                                // Evaluate the model
                                EvaluationResult result = trainManager.evaluation(
                                        pbTaskInfo.getFLID(), dataMetadata,
                                        pbTaskInfo.getEvaluationInfo(), taskDataPath, outputPath);
                                if (result.getStatus() == 0) {
                                    // Create and Save PBTaskResult object
                                    PBTaskResult pbTaskResult = PBTaskResult.newBuilder()
                                            .setFLLibVersion(pbTaskInfo.getFLLibVersion())
                                            .setFLID(pbTaskInfo.getFLID())
                                            .setTaskID(pbTaskInfo.getTaskID())
                                            .setEvaluationResult(result.getEvaluationResult())
                                            .build();
                                    if (mFileManager.saveUploadPBTaskResultData(mFLEvaluationTask,
                                            pbTaskResult)) {
                                        success = true;
                                    } else {
                                        Log.e(TAG, "failed to save pb task result data");
                                        errCode = ERROR_SAVE_UPLOAD_DATA;
                                    }
                                } else {
                                    errCode = ERROR_LIB_EVALUATION;
                                    errSubCode = result.getStatus();
                                }
                            } else {
                                Log.e(TAG, "failed to create evaluation data file");
                                errCode = ERROR_WRITE_DATA;
                            }
                        } else {
                            Log.e(TAG, "failed to prepare output directory");
                            errCode = ERROR_PREPARE_UPLOAD_DIR;
                        }
                    } catch (FLException e) {
                        Log.e(TAG, "failed to create train manager: " + e);
                        errCode = ERROR_LIB_CONSTRUCT;
                    } catch (RuntimeException e) {
                        Log.e(TAG, "unexpected runtime exception happened: " + e);
                        errCode = ERROR_RUNTIME_EXCEPTION;
                    }

                    if (success) {
                        sendMessage(MSG_EVALUATION_STATUS_SUCCESS);
                    } else {
                        mFileManager.deleteUploadData(mFLEvaluationTask);
                        sendMessage(MSG_EVALUATION_STATUS_FAILURE, errCode, errSubCode);
                    }
                });
            } else { // Should never happen
                sendMessage(MSG_EVALUATION_STATUS_FAILURE, ERROR_INVALID_STATE);
            }
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            boolean handleStatus = HANDLED;
            switch (message.what) {
                case MSG_EVALUATION_STATUS_SUCCESS: {
                    // Update pending upload list for uploading evaluation result
                    List<Integer> idxList = FLPreferenceAccessor.getPendingUploadFLTaskIndexList();
                    idxList.add(getFLTaskIndex(mFLEvaluationTask));
                    FLPreferenceAccessor.getSharedPreferences().edit()
                            .putString(KEY_PENDING_UPLOAD_FL_TASK_INDEX_LIST,
                                    toCommaSeparatedString(idxList))
                            .apply();
                    transitionTo(mNormalState);
                    break;
                }
                case MSG_EVALUATION_STATUS_FAILURE: {
                    int code = message.arg1, subCode = message.arg2;
                    Log.e(TAG, "failed to evaluate (code=" + code + ", subCode=" + subCode + ")");
                    // TODO: need to consider what should do for this case
                    transitionTo(mNormalState);
                    break;
                }
                case MSG_FEATURE_STATUS_CHANGED:
                case MSG_ADD_TRAINING_DATA:
                    // To prevent state transition while evaluation is in progress
                    deferMessage(message);
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
            if (mFLEvaluationTask != null) {
                // Update completed taskId list to prevent duplicate evaluation
                List<String> taskIdList = FLPreferenceAccessor.getCompletedFLTaskIdList();
                addCompletedFLTaskIdList(taskIdList, mFLEvaluationTask.getTaskInfo().getTaskID());
                FLPreferenceAccessor.getSharedPreferences().edit()
                        .putString(KEY_COMPLETED_FL_TASK_ID_LIST, String.join(",", taskIdList))
                        .apply();
                mFileManager.deleteTaskData(mFLEvaluationTask);
                mFLEvaluationTask = null;
            }
        }
    }

    private class CalibrateState extends State {

        private static final int ERROR_LIB_CALIBRATION = 1;
        private static final int ERROR_LIB_CONSTRUCT = 2;
        private static final int ERROR_PREPARE_DIR = 3;
        private static final int ERROR_WRITE_DATA = 4;
        private static final int ERROR_INVALID_STATE = 5;
        private static final int ERROR_RUNTIME_EXCEPTION = 6;

        private String mAppId;

        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            // Take any calibration required appId
            // (Note that the calibration required status for the appId will be cleared even if
            // result is failure. This is to prevent possible failure loop)
            mAppId = takeAnyCalibrationRequiredAppId();
            if (mAppId != null) {
                mFLLibHandler.post(() -> {
                    boolean success = false;
                    int errCode = 0, errSubCode = 0;
                    try {
                        PredictManager predictManager = new PredictManager(
                                mPredictManagerDataDir, mAppId);
                        // Create a tentative directory which stores the all data file
                        Path calibrationPath = mFileManager.prepareCalibrationPath();
                        if (calibrationPath != null) {
                            // Create the all data file for calibration
                            Stream<DataSet> dataSetStream = applyModifier(mAppId,
                                    mTrainingDataAccessor.get(mAppId, DataType.TRAINING_AND_TEST));
                            DataMetadata dataMetadata = mFileManager.writeDataFile(dataSetStream,
                                    Objects.requireNonNull(ModelType.valueOf(
                                            FLPreferenceAccessor.getModelType(mAppId))));
                            if (dataMetadata != null) {
                                // Perform calibration
                                int ret = predictManager.calibrate(dataMetadata);
                                if (ret == 0) {
                                    success = true;
                                } else {
                                    Log.e(TAG, "failed to complete calibration: " + ret);
                                    errCode = ERROR_LIB_CALIBRATION;
                                    errSubCode = ret;
                                }
                            } else {
                                Log.e(TAG, "failed to create calibration data file");
                                errCode = ERROR_WRITE_DATA;
                            }
                        } else {
                            Log.e(TAG, "failed to prepare tentative data directory");
                            errCode = ERROR_PREPARE_DIR;
                        }
                    } catch (FLException e) {
                        Log.e(TAG, "failed to create PredictManager instance: " + e);
                        errCode = ERROR_LIB_CONSTRUCT;
                    } catch (RuntimeException e) {
                        Log.e(TAG, "unexpected runtime exception happened: " + e);
                        errCode = ERROR_RUNTIME_EXCEPTION;
                    }

                    if (success) {
                        sendMessage(MSG_CALIBRATION_STATUS_SUCCESS);
                    } else {
                        sendMessage(MSG_CALIBRATION_STATUS_FAILURE, errCode, errSubCode);
                    }
                });
            } else { // Should never happen
                sendMessage(MSG_CALIBRATION_STATUS_FAILURE, ERROR_INVALID_STATE);
            }
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            boolean handleStatus = HANDLED;
            switch (message.what) {
                case MSG_CALIBRATION_STATUS_SUCCESS:
                    // Update last calibration time
                    FLPreferenceAccessor.getSharedPreferences().edit()
                            .putLong(LAST_CALIBRATION_TIME_KEY_GENERATOR.apply(mAppId),
                                    System.currentTimeMillis())
                            .apply();
                    transitionTo(mNormalState);
                    break;
                case MSG_CALIBRATION_STATUS_FAILURE: {
                    int code = message.arg1, subCode = message.arg2;
                    Log.e(TAG, "failed to calibrate (code=" + code + ", subCode=" + subCode + ")");
                    // TODO: need to consider what should do for this case
                    transitionTo(mNormalState);
                    break;
                }
                case MSG_FEATURE_STATUS_CHANGED:
                case MSG_ADD_TRAINING_DATA:
                    // To prevent state transition while calibration is in progress
                    deferMessage(message);
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
            if (mAppId != null) {
                mFileManager.deleteCalibrationData();
                mAppId = null;
            }
        }
    }

    private class DeleteState extends State {

        private static final int ERROR_LIB_DELETE = 1;
        private static final int ERROR_LIB_CONSTRUCT = 2;
        private static final int ERROR_INVALID_STATE = 3;
        private static final int ERROR_RUNTIME_EXCEPTION = 4;

        private FLTask mFLDeleteTask;

        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            // Take first pending delete task
            // (Note that the task will be removed even if result is failure. This is to prevent
            // possible failure loop)
            FLTask flTask = takeFirstPendingPriorityFLTask();
            if (flTask != null && flTask.getTaskInfo().hasDeleteInfo()) {
                mFLDeleteTask = flTask;
                mFLLibHandler.post(() -> {
                    boolean success = false;
                    int errCode = 0, errSubCode = 0;
                    PBTaskInfo pbTaskInfo = mFLDeleteTask.getTaskInfo();
                    try {
                        TrainManager trainManager = new TrainManager(mTrainManagerDataDir);
                        // Delete all data of FL library for given FLID
                        int ret = trainManager.delete(pbTaskInfo.getFLID(),
                                pbTaskInfo.getDeleteInfo());
                        if (ret == 0) {
                            success = true;
                        } else {
                            Log.e(TAG, "failed to complete delete: " + ret);
                            errCode = ERROR_LIB_DELETE;
                            errSubCode = ret;
                        }
                    } catch (FLException e) {
                        Log.e(TAG, "failed to create train manager: " + e);
                        errCode = ERROR_LIB_CONSTRUCT;
                    } catch (RuntimeException e) {
                        Log.e(TAG, "unexpected runtime exception happened: " + e);
                        errCode = ERROR_RUNTIME_EXCEPTION;
                    }

                    if (success) {
                        sendMessage(MSG_DELETE_STATUS_SUCCESS);
                    } else {
                        sendMessage(MSG_DELETE_STATUS_FAILURE, errCode, errSubCode);
                    }
                });
            } else { // Should never happen
                sendMessage(MSG_DELETE_STATUS_FAILURE, ERROR_INVALID_STATE);
            }
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            boolean handleStatus = HANDLED;
            switch (message.what) {
                case MSG_DELETE_STATUS_SUCCESS:
                    transitionTo(mNormalState);
                    break;
                case MSG_DELETE_STATUS_FAILURE: {
                    int code = message.arg1, subCode = message.arg2;
                    Log.e(TAG, "failed to delete (code=" + code + ", subCode=" + subCode + ")");
                    // TODO: need to consider what should do for this case
                    transitionTo(mNormalState);
                    break;
                }
                case MSG_FEATURE_STATUS_CHANGED:
                case MSG_ADD_TRAINING_DATA:
                    // To prevent state transition while deploy is in progress
                    deferMessage(message);
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
            if (mFLDeleteTask != null) {
                // Update completed taskId list to prevent duplicate delete
                List<String> taskIdList = FLPreferenceAccessor.getCompletedFLTaskIdList();
                addCompletedFLTaskIdList(taskIdList, mFLDeleteTask.getTaskInfo().getTaskID());
                FLPreferenceAccessor.getSharedPreferences().edit()
                        .putString(KEY_COMPLETED_FL_TASK_ID_LIST, String.join(",", taskIdList))
                        .apply();
                mFLDeleteTask = null;
            }
        }
    }

    private class DisabledState extends State {
        @Override
        public void enter() {
            Log.v(TAG, getName() + " entered");
            updateSystemStatus(); // for FLS start-up and client config update cases
            sendMessage(MSG_ENABLED_CHECK_TRIGGER);
        }

        @Override
        public boolean processMessage(Message message) {
            Log.v(TAG, getName() + " processes message: " + getWhatToString(message.what));
            boolean handleStatus = HANDLED;
            switch (message.what) {
                case MSG_ENABLED_CHECK_TRIGGER:
                case MSG_FEATURE_STATUS_CHANGED: {
                    OperationMode mode = mClientConfigAccessor.get().getGeneralConfiguration()
                            .getOperationMode();
                    if (mode != OperationMode.ENTIRE_FEATURE_KILLED
                            && mFeatureStatusMap.containsValue(true)) {
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

    private AppidSpecificConfig getAppidSpecificConfig(String appId) {
        Optional<AppidSpecificConfig> configOpt =
                mClientConfigAccessor.get().getAppidSpecificConfigsList().stream()
                        .filter(e -> e.getAppId().equals(appId))
                        .findFirst();
        return configOpt.orElseThrow(() -> new IllegalArgumentException(
                "unknown appId: " + appId)); // Should never happen
    }

    private boolean checkDcPrCondition(String appId) {
        float positiveRateThreshold = getAppidSpecificConfig(appId).getPositiveRateThreshold();
        boolean checkPrCondition = true;
        if (positiveRateThreshold != 0) {
            checkPrCondition = getPositiveRate(appId) >= positiveRateThreshold;
        }
        return checkDcCondition(appId) && checkPrCondition;
    }

    private boolean isDcPrConditionPassed(String appId) {
        return Objects.requireNonNull(mDcPrConditions.get(appId));
    }

    /**
     * Retrieves and removes any of the appId that required calibration, or returns null if there is
     * no such appId.
     */
    @SuppressLint("ApplySharedPref")
    @Nullable
    private String takeAnyCalibrationRequiredAppId() {
        Iterator<String> iterator = mCalibrationRequiredAppIds.iterator();
        if (!iterator.hasNext()) {
            return null;
        }
        String appId = iterator.next();
        // Remove appId from |mCalibrationRequiredAppIds|
        iterator.remove();
        // Remove last calibration time
        String keyLastCalibrationTime = LAST_CALIBRATION_TIME_KEY_GENERATOR.apply(appId);
        FLPreferenceAccessor.getSharedPreferences().edit()
                .remove(keyLastCalibrationTime)
                // Intentionally use |commit| to avoid crash loop for the case when crash happens
                // as soon as this method returns. |apply| takes a little time to complete disk
                // write.
                .commit();
        return appId;
    }

    /**
     * Update the calibration required status for the given appId.
     */
    private void updateCalibrationStatus(String appId, boolean skipIntervalCheck) {
        // The following conditions need to be fulfilled.
        //  1. DC/PR condition passed
        //  2. Model deployed
        //  3. Elapsed calibration interval - if |skipIntervalCheck| is true
        if (isDcPrConditionPassed(appId) && FLPreferenceAccessor.getModelVersion(appId) != null) {
            if (!skipIntervalCheck) {
                long lastTime = FLPreferenceAccessor.getLastCalibrationTime(appId);
                long pollFreq = TimeUnit.DAYS.toMillis(
                        getAppidSpecificConfig(appId).getPeriodicCalibrationFrequencyDays());
                if (lastTime != 0 && pollFreq != 0) {
                    long startTime = addSafely(lastTime, pollFreq);
                    if (System.currentTimeMillis() >= startTime) {
                        mCalibrationRequiredAppIds.add(appId);
                    }
                }
            } else {
                mCalibrationRequiredAppIds.add(appId);
            }
        } else {
            mCalibrationRequiredAppIds.remove(appId);
        }
    }

    /**
     * Retrieves, but does not remove, the head of the pending 'deploy' and 'delete' tasks,
     * or returns null if there is no such pending task.
     */
    @Nullable
    private FLTask getFirstPendingPriorityFLTask() {
        List<Integer> pendingList = FLPreferenceAccessor.getPendingPriorityFLTaskIndexList();
        return pendingList.isEmpty() ? null : mClientConfigAccessor.get().getFlTasks(
                pendingList.get(0));
    }

    /**
     * Retrieves and removes the head of the pending 'deploy' and 'delete' tasks, or returns null
     * if there is no such pending task.
     */
    @SuppressLint("ApplySharedPref")
    @Nullable
    private FLTask takeFirstPendingPriorityFLTask() {
        List<Integer> pendingList = FLPreferenceAccessor.getPendingPriorityFLTaskIndexList();
        if (pendingList.isEmpty()) {
            return null;
        }
        FLTask flTask = mClientConfigAccessor.get().getFlTasks(pendingList.remove(0) /* remove */);
        FLPreferenceAccessor.getSharedPreferences().edit()
                .putString(KEY_PENDING_PRIORITY_FL_TASK_INDEX_LIST,
                        toCommaSeparatedString(pendingList))
                // Intentionally use |commit| to avoid crash loop for the case when crash happens
                // as soon as this method returns. |apply| takes a little time to complete disk
                // write.
                .commit();
        return flTask;
    }

    /**
     * Retrieves, but does not remove, the head of the pending tasks (not incl. priority tasks), or
     * returns null if there is no such pending task.
     */
    @Nullable
    private FLTask getFirstPendingFLTask() {
        List<Integer> pendingList = FLPreferenceAccessor.getPendingFLTaskIndexList();
        return pendingList.isEmpty() ? null : mClientConfigAccessor.get().getFlTasks(
                pendingList.get(0));
    }

    /**
     * Retrieves and removes the head of the pending tasks (not incl. priority tasks), or returns
     * null if there is no such pending task.
     */
    @SuppressLint("ApplySharedPref")
    @Nullable
    private FLTask takeFirstPendingFLTask() {
        List<Integer> pendingList = FLPreferenceAccessor.getPendingFLTaskIndexList();
        if (pendingList.isEmpty()) {
            return null;
        }
        FLTask flTask = mClientConfigAccessor.get().getFlTasks(pendingList.remove(0) /* remove */);
        FLPreferenceAccessor.getSharedPreferences().edit()
                .putString(KEY_PENDING_FL_TASK_INDEX_LIST, toCommaSeparatedString(pendingList))
                // Intentionally use |commit| to avoid crash loop for the case when crash happens
                // as soon as this method returns. |apply| takes a little time to complete disk
                // write.
                .commit();
        return flTask;
    }

    /**
     * Retrieves the head of the pending uploads (corresponding tasks), or returns null if there is
     * no such pending upload.
     */
    @Nullable
    private FLTask getFirstPendingUploadFLTask() {
        List<Integer> pendingList = FLPreferenceAccessor.getPendingUploadFLTaskIndexList();
        return pendingList.isEmpty() ? null : mClientConfigAccessor.get().getFlTasks(
                pendingList.get(0));
    }

    /**
     * Returns the index of the given FL task.
     */
    private int getFLTaskIndex(FLTask flTask) {
        // A supplied FL task object needs to be taken from |ClientConfigAccessor| as |equals| is
        // used at |indexOf| to compare objects.
        int index = mClientConfigAccessor.get().getFlTasksList().indexOf(flTask);
        if (index < 0) { // Should never happen
            throw new IllegalStateException("unable to find corresponding task index");
        }
        return index;
    }

    private void addCompletedFLTaskIdList(List<String> taskList, String taskId) {
        if (MAX_SIZE_OF_COMPLETED_FL_TASK_ID_LIST <= taskList.size()) {
            taskList.remove(0);
        }
        taskList.add(taskId);
    }

    private void updateSystemStatus() {
        boolean systemEnabled = mClientConfigAccessor.get().getGeneralConfiguration()
                .getOperationMode() != OperationMode.ENTIRE_FEATURE_KILLED;
        Map<String, FLFeatureStatus> featureStatusMap = mPredictorMap.entrySet().stream()
                .collect(Collectors.toMap(Map.Entry::getKey,
                        e -> FLFeatureStatus.builder()
                                .feature(e.getKey())
                                .predictionEnabled(e.getValue().mWrapper.isPredictionEnabled())
                                .dataCollectionSession(e.getValue().isDataCollectionSession())
                                .build()));
        // Construct system status object with latest information
        FLSystemStatus systemStatus = FLSystemStatus.builder()
                .systemEnabled(systemEnabled)
                .featureStatusMap(featureStatusMap)
                .build();
        if (!systemStatus.equals(mSystemStatus)) {
            FLSystemStatus previous = mSystemStatus;
            mSystemStatus = systemStatus;
            Log.v(TAG, "System status changed: from " + previous + " to " + mSystemStatus);
            synchronized (mSystemStatusListeners) {
                // Identify the target to be notified of updates
                boolean all = !previous.toBuilder().clearFeatureStatus().build().equals(
                        mSystemStatus.toBuilder().clearFeatureStatus().build());
                List<String> updatedAppIds = FLS_APP_ID_LIST.stream()
                        .filter(e -> !previous.getFeatureStatus(e).equals(
                                mSystemStatus.getFeatureStatus(e)))
                        .collect(Collectors.toList());
                // Notify clients of this change
                mSystemStatusListeners.forEach((l, appId) -> {
                    if (all || updatedAppIds.contains(appId)) {
                        l.onConfigurationChanged(mSystemStatus);
                    }
                });
            }
        }
    }

    private boolean usageDataCollectionAllowed() {
        final Uri uri = Uri.parse(
                "content://com.sonyericsson.idd.agent.IDDAgentProvider/datadisclaimer");
        final String COLUMN_IDD_PERSONAL_DATA_STATE = "PersonalDataState";
        boolean personalDataState = false;
        try (Cursor cursor = mContext.getContentResolver().query(uri, null, null, null, null)) {
            if (cursor != null) {
                int index = cursor.getColumnIndex(COLUMN_IDD_PERSONAL_DATA_STATE);
                while (cursor.moveToNext()) {
                    personalDataState = Boolean.parseBoolean(cursor.getString(index));
                }
            } else {
                Log.w(TAG, "unable to fetch personal data state");
            }
        }
        return personalDataState;
    }

    // Only for "positive" value addition
    private long addSafely(long a, long b) {
        try {
            return Math.addExact(a, b);
        } catch (ArithmeticException e) {
            return Long.MAX_VALUE;
        }
    }

    private Stream<DataSet> applyModifier(String appId, Stream<DataSet> dataSetStream) {
        Function<DataSet, DataSet> modifier = Objects.requireNonNull(
                mPredictorMap.get(appId)).mTrainingDataModifier;
        return modifier != null ? dataSetStream.map(modifier) : dataSetStream;
    }

    /**
     * A wrapper for a {@link com.sony.fl.PredictManager} instance to:
     * - Avoid concurrent access to {@link com.sony.fl.PredictManager} across all instances
     * - Control prediction on/off across all instances at a time
     */
    @VisibleForTesting
    static class PredictManagerWrapper {

        /**
         * The static lock object to avoid concurrent access to {@link com.sony.fl.PredictManager}
         * across different instances of the class.
         */
        private static final Object sLock = new Object();

        /**
         * The static flag to control prediction on/off(PredictManager access OK/NG) across
         * different instances of the class at a time.
         */
        private static boolean sEntirePredictionEnabled = false;

        private final String mAppId;

        private final Path mDataDir;

        @VisibleForTesting
        @Nullable
        PredictManager mPredictManager;

        public PredictManagerWrapper(@NonNull String appId, @NonNull Path dataDir) {
            mAppId = appId;
            mDataDir = dataDir;
        }

        @Nullable
        public PredictResult predict(@NonNull TensorMap tensorMap) {
            synchronized (sLock) {
                if (sEntirePredictionEnabled && mPredictManager != null) {
                    return mPredictManager.predict(tensorMap);
                }
            }
            return null; // prediction is disabled
        }

        public void setPredictManager() {
            synchronized (sLock) {
                if (sEntirePredictionEnabled) {
                    throw new IllegalStateException("prediction is enabled");
                }
                try {
                    releasePredictManager();
                    mPredictManager = new PredictManager(mDataDir, mAppId);
                } catch (FLException e) {
                    Log.e(TAG, "failed to create PredictManager instance: " + e);
                    mPredictManager = null;
                }
            }
        }

        public void releasePredictManager() {
            synchronized (sLock) {
                if (sEntirePredictionEnabled) {
                    throw new IllegalStateException("prediction is enabled");
                }
                if (mPredictManager != null) {
                    mPredictManager.finalize(); // Explicitly release resources
                    mPredictManager = null;
                }
            }
        }

        public boolean isPredictionEnabled() {
            synchronized (sLock) {
                return sEntirePredictionEnabled && mPredictManager != null;
            }
        }

        public static void setEntirePredictionEnabled(boolean enabled) {
            synchronized (sLock) {
                sEntirePredictionEnabled = enabled;
            }
        }

        @NonNull
        public String getAppId() {
            return mAppId;
        }
    }

    @VisibleForTesting
    static class PredictorImpl implements Predictor {

        private final PredictManagerWrapper mWrapper;

        @Nullable
        private final StateMachine mFLStateMachine;

        private final Random mRandom = new Random();

        private final String mInferenceThresholdOverridePropName;

        private int mDataCollectionSessionRatio = 0;

        private float mInferenceThreshold = 1.0f;

        private float mAverageOfLabel = 0;

        private String mModelVersion;

        private ModelType mModelType; // Once set, should never be changed

        @Nullable
        private Function<DataSet, DataSet> mTrainingDataModifier = null;

        // To collect non-biased data for next Federated-Learning
        private boolean mDataCollectionSession;

        PredictorImpl(@NonNull PredictManagerWrapper wrapper, @Nullable StateMachine stateMachine) {
            mWrapper = wrapper;
            mFLStateMachine = stateMachine;
            mInferenceThresholdOverridePropName =
                    FLS_INFERENCE_THRESHOLD_OVERRIDE_PROP_GENERATOR.apply(wrapper.getAppId());
        }

        // NOTE: FL library access for prediction is performed on caller thread.
        @NonNull
        @Override
        public synchronized PredictionResult predict1d(@NonNull List<Float> features,
                @NonNull String groupLabel) {
            return predict2d(List.of(features), groupLabel);
        }

        // NOTE: FL library access for prediction is performed on caller thread.
        @NonNull
        @Override
        public synchronized PredictionResult predict2d(@NonNull List<List<Float>> features,
                @NonNull String groupLabel) {
            PredictionResult.Builder builder = PredictionResult.builder().scoreUsable(false);
            float[][] dataSequence = to2dArray(features);
            if (mWrapper.isPredictionEnabled()) {
                TensorMap tensorMap = toTensorMap(dataSequence, groupLabel);
                if (tensorMap != null) {
                    PredictResult result = Objects.requireNonNull(mWrapper.predict(tensorMap));
                    if (result.getStatus() == 0) {
                        if (!mDataCollectionSession) { // Normal case
                            builder.scoreUsable(true);
                        } else { // Data collection session
                            builder.scoreUnusableReason("data collection session").extraData(
                                    createIncompleteTrainingData(groupLabel, dataSequence));
                        }
                        builder.score(getPredictLabel(result.getResult()), getInferenceThreshold());
                    } else { // Prediction NG (from FL library)
                        builder.scoreUnusableReason("error status [" + result.getStatus() + "]");
                    }
                    builder.modelVersion(mModelVersion);
                } else {
                    builder.scoreUnusableReason("Cannot prediction due to input format error");
                }
            } else {
                builder.scoreUnusableReason("prediction is disabled");
            }
            return builder.build();
        }

        @Override
        public synchronized void reset() {
            updateDataCollectionSession();
        }

        @Override
        public synchronized void addTrainingData(@NonNull PredictionResult result, float label) {
            DataSet.Builder dataSetBuilder = (DataSet.Builder) result.getExtraData();
            if (dataSetBuilder != null && mFLStateMachine != null) {
                mFLStateMachine.sendMessage(MSG_ADD_TRAINING_DATA,
                        Pair.create(mWrapper.getAppId(), dataSetBuilder.label(label).build()));
            } else {
                if (dataSetBuilder == null) {
                    Log.v(TAG, "training data is missing in " + result);
                }
            }
        }

        @Override
        public float getAverageOfLabel() {
            return mAverageOfLabel;
        }

        @Override
        public void setTrainingDataModifier(@Nullable Function<DataSet, DataSet> modifier) {
            mTrainingDataModifier = modifier;
        }

        synchronized void setAverageOfLabel(float averageOfLabel) {
            mAverageOfLabel = averageOfLabel;
        }

        synchronized void setDataCollectionSessionRatio(int ratio) {
            mDataCollectionSessionRatio = ratio;
            updateDataCollectionSession();
        }

        synchronized void setInferenceThreshold(float threshold) {
            mInferenceThreshold = threshold;
        }

        synchronized void setModelVersion(String modelVersion) {
            mModelVersion = modelVersion;
        }

        synchronized void setModelType(ModelType modelType) {
            mModelType = modelType;
        }

        synchronized boolean isDataCollectionSession() {
            return mWrapper.isPredictionEnabled() && mDataCollectionSession;
        }

        private void updateDataCollectionSession() {
            boolean previous = mDataCollectionSession;
            mDataCollectionSession = shouldBeDataCollectionSession();
            if (mDataCollectionSession != previous && mFLStateMachine != null) {
                mFLStateMachine.sendMessage(MSG_UPDATE_SYSTEM_STATUS);
            }
        }

        @VisibleForTesting
        boolean shouldBeDataCollectionSession() {
            return mDataCollectionSessionRatio >= (mRandom.nextInt(100) + 1);
        }

        private float getInferenceThreshold() {
            String value = SystemProperties.get(mInferenceThresholdOverridePropName);
            if (!TextUtils.isEmpty(value)) {
                try {
                    return Float.parseFloat(value);
                } catch (NumberFormatException e) {
                    Log.w(TAG, "unable to parse inference_threshold_override prop:" + value);
                }
            }
            return mInferenceThreshold;
        }

        /**
         * Create the {@link DataSet.Builder} instance to be set to {@link PredictionResult}. Not
         * all of the fields are fulfilled and the rest of them will be handled in {@link
         * #addTrainingData(PredictionResult, float)}.
         */
        private DataSet.Builder createIncompleteTrainingData(String groupLabel,
                float[][] features) {
            return DataSet.builder()
                    .groupLabel(groupLabel)
                    .features(features);
        }

        @VisibleForTesting
        float[][] to2dArray(List<List<Float>> value) {
            return value.stream()
                    .map(Floats::toArray)
                    .toArray(float[][]::new);
        }

        private TensorMap toTensorMap(float[][] dataSequence, String groupLabel) {
            int timeSeriesLength = dataSequence.length;
            int numOfFeatures = 0;
            if (timeSeriesLength != 0) {
                numOfFeatures = dataSequence[0].length;
            }
            Double[] featuresArray = Tensor.toDoubleArrayFrom(dataSequence);
            TensorMap tensorMap = null;
            // Generation of TensorMap depends on the model specification used in appId
            if (mModelType == ModelType.LinerHLCR) {
                TensorShape tensorShape = TensorShape.createShape(numOfFeatures);
                if (tensorShape != null && featuresArray != null) {
                    tensorMap = TensorMap.newInstance();
                    tensorMap.set(LinearFedHLCRClient.TENSOR_X,
                            Tensor.newTensor(tensorShape, featuresArray));
                    tensorMap.set(LinearFedHLCRClient.TENSOR_GROUP_LABEL,
                            Tensor.newTensor(groupLabel));
                }
            } else if (mModelType == ModelType.NNHLCR) {
                TensorShape tensorShape = TensorShape.createShape(timeSeriesLength, numOfFeatures);
                if (tensorShape != null && featuresArray != null) {
                    tensorMap = TensorMap.newInstance();
                    tensorMap.set(NNFedHLCRClient.TENSOR_SEQUENCE_DATA,
                            Tensor.newTensor(tensorShape, featuresArray));
                    tensorMap.set(NNFedHLCRClient.TENSOR_NUM_OF_FEATURES,
                            Tensor.newTensor(numOfFeatures));
                    tensorMap.set(NNFedHLCRClient.TENSOR_GROUP_LABEL, Tensor.newTensor(groupLabel));
                }
            } else {
                throw new RuntimeException("Unsupported modelType");
            }
            return tensorMap;
        }

        private float getPredictLabel(TensorMap tensorMap) {
            Tensor<?> tensor;
            if (mModelType == ModelType.LinerHLCR) {
                tensor = tensorMap.get(LinearFedHLCRClient.TENSOR_Y_PRED);
            } else if (mModelType == ModelType.NNHLCR) {
                tensor = tensorMap.get(NNFedHLCRClient.TENSOR_Y_PRED);
            } else {
                throw new RuntimeException("Unsupported modelType");
            }
            return ((Double) tensor.getValue()).floatValue();
        }
    }
}
