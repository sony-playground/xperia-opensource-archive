/*
 * Copyright 2019, 2020, 2021, 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine;

import java.util.List;
import java.util.Map;
import java.util.function.BinaryOperator;
import java.util.function.UnaryOperator;

/**
 * Constants definition for Smart Network Engine application
 */
public class Constants {

    // ---------- "FL System" related definitions ----------

    public static final BinaryOperator<String> FLS_CDN_BASE_URL_GENERATOR =
            (stg, path) -> String.format("https://cdn%s.fls.smartnet.sony.net/v2/%s", stg, path);

    public static final String FLS_CDN_CLIENT_CONFIG_FILENAME = "fls_client_configuration.dat";

    public static final UnaryOperator<String> FLS_TRAINING_UPLOAD_API_ENDPOINT_URL_GENERATOR =
            stg -> String.format("https://api%s.fls.smartnet.sony.net/v1/training-results", stg);

    public static final UnaryOperator<String> FLS_EVALUATION_UPLOAD_API_ENDPOINT_URL_GENERATOR =
            stg -> String.format("https://api%s.fls.smartnet.sony.net/v1/evaluation-results", stg);

    public static final int FLS_CLIENT_CONFIG_MAX_SIZE = 512 * 1024; // 0.5 MB;

    public static final int FLS_TASK_DATA_FILE_MAX_SIZE = 2560 * 1024; // 2.5 MB;

    public static final String FLS_APP_ID_CONNECTED = "connected_user_intention";

    public static final String FLS_APP_ID_ENTRY = "entry";

    /** AppId and the internal identifier mapping */
    public static final Map<String, Integer> FLS_APP_ID_INT_NUM_MAP = Map.of(
            FLS_APP_ID_CONNECTED, 1 /* Don't change once assigned */,
            FLS_APP_ID_ENTRY, 2);

    public static final List<String> FLS_APP_ID_LIST = List.of(
            FLS_APP_ID_CONNECTED,
            FLS_APP_ID_ENTRY);

    public static final String FLS_DATA_DIR = "fls";

    /** A broadcast intent action indicating that force download has been requested */
    public static final String ACTION_FLS_FORCE_DOWNLOAD =
            "com.sonymobile.smartnetworkengine.intent.action.FLS_FORCE_DOWNLOAD";

    // ---------- "Entry" feature related definitions ----------

    public static final long ENTRY_SCORE_JUDGE_TIMEOUT_SEC = 3;

    /** The identifier of IDD probe */
    public static final String IDD_PROBE_WIFI_SELECTION =
            "com.sonymobile.smartnetworkengine.ext.fllogger";

    /** The max size(byte) allowed to upload to IDD per day. */
    public static final int WIFI_SELECTION_LOGGER_IDD_DAILY_UPLOAD_LIMIT_SIZE = 15 * 1024; // 15KB

    public static final String ENTRY_ASSET_DIR = "fl_entry";

    public static final String ENTRY_MEAN_FILENAME = "mean.csv";

    public static final String ENTRY_VAR_FILENAME = "var.csv";

    public static final String ENTRY_LABEL_MEAM_VAR_FILENAME = "label_mean_var.csv";

    // ---------- "Connected" feature related definitions ----------

    public static final int CELL_NETWORK_TYPE_UNKNOWN = 0;
    public static final int CELL_NETWORK_TYPE_LTE = 1;
    public static final int CELL_NETWORK_TYPE_NR = 2;
    public static final int CELL_NETWORK_TYPE_LTE_NR_CONNECTED = 3;
    public static final int CELL_NETWORK_TYPE_LTE_NR_NOT_RESTRICTED = 4;

    /**
     * The identifier of primary neural network. This needs to be matched with the directory name
     * under 'assets' which manages primary neural network configuration.
     */
    public static final String NN_PRIMARY = "nn_congestion";

    /**
     * The identifier of secondary neural network. This needs to be matched with the directory name
     * under 'assets' which manages secondary neural network configuration.
     */
    public static final String NN_SECONDARY = "nn_disconnection";

    /**
     * The identifier of cellular neural network. This needs to be matched with the directory
     * name under 'assets' which manages lte neural network configuration.
     */
    public static final String NN_LTE = "nn_lte";
    public static final String NN_NR = "nn_nr";
    public static final String NN_LTE_NR_CONNECTED = "nn_lte_nr_connected";
    public static final String NN_LTE_NR_NOT_RESTRICTED = "nn_lte_nr_not_restricted";

    public static final int RSSI_CAP_THRESHOLD = -70;

    /**
     * A packet rate(packets per second) that should be considered acceptable for staying on wifi,
     * no matter how bad the RSSI gets.
     */
    public static final int WIFI_PPS_THRESHOLD = 100;

    /**
     * Stay on wifi when rssi is above threshold.
     */
    public static final int WIFI_RSSI_THRESHOLD = -78;

    public static final int WIFI_RSSI_THRESHOLD_6GHZ_AOSP = -77;

    public static final int WIFI_TRANSITION_SCORE = 50;

    public static final int AVOID_FLAPPING_RSSI_RANGE = 3;

    /**
     * The max size(byte) allowed to upload to IDD per day.
     */
    public static final int IDD_DAILY_UPLOAD_LIMIT_SIZE = 15 * 1024; // 15 KB

    /**
     * The max size(byte) allowed to upload to IDD per day (for userdebug).
     */
    public static final int IDD_DAILY_UPLOAD_LIMIT_SIZE_FOR_DEBUG = Integer.MAX_VALUE; // 2 GB

    /**
     * The time of IDD upload restriction period
     */
    public static final long IDD_UPLOAD_LIMIT_PERIOD_MSEC = 26 * 60 * 60 * 1000; // 26 hours

    /**
     * The identifier of IDD probe package
     */
    public static final String IDD_PROBE_PKG =
            "com.sonyericsson.idd.probe.android.smartnetworkengine";

    /**
     * The identifier of IDD probe name for connected
     */
    public static final String IDD_PROBE_NAME_CONNECTED = "SneWifiEvent";

    // ---------- Settings provider key definitions ----------

    public static final String SETTINGS_SMARTNET_CONNECTED_ENABLED =
            "somc.smartnet_connected_enabled";

    public static final String SETTINGS_SMARTNET_ENTRY_ENABLED =
            "somc.smartnet_entry_enabled";

    public static final String SETTINGS_VERBOSE_LOGGING_ENABLED =
            "somc.smartnet_verbose_logging_enabled";

    /** Settings to enable/disable the home network detection */
    public static final String SETTINGS_HOME_NETWORK_DETECTION_ENABLED =
            "somc.smartnet_home_network_detection_enabled";

    /** Settings to set device id for client config matching */
    public static final String SETTINGS_FLS_CLIENT_CONFIG_DEVICE_ID =
            "somc.smartnet_fls_client_config_device_id";

    // ---------- System property definitions ----------

    /**
     * The system property to enable/disable the IDD debug mode (IDD data is written into file)
     */
    public static final String PROP_IDD_DEBUG_MODE_ENABLED =
            "persist.somc.smartnet.idd.debug_mode_enabled";

    /**
     * The system property to enable/disable the always prefer non wifi network mode
     */
    public static final String PROP_ALWAYS_PREFER_NON_WIFI = "somc.smartnet.always_prefer_non_wifi";

    /**
     * The system property to specify test fl system client config file which will be accessed to.
     * If specified, base directory on server will change to 'test' directory.
     */
    public static final String PROP_FLS_TEST_CLIENT_CONFIG_FILE =
            "persist.somc.smartnet.fls_test_client_config_file";

    /**
     * The system property to specify fl system server environment - i.e. prod/stage/dev.
     */
    public static final String PROP_FLS_SERVER_ENV = "persist.somc.smartnet.fls_server_env";

    /**
     * The system property to override the inference threshold of specified AppID
     */
    public static final UnaryOperator<String> FLS_INFERENCE_THRESHOLD_OVERRIDE_PROP_GENERATOR =
            appId -> String.format("persist.somc.smartnet.fls_%s_inference_threshold_override",
                    appId);

    /**
     * The system property to specify directory from which neural network configuration is read
     * instead of 'assets'. It must be relative path from top of application's data directory.
     */
    public static final String PROP_NN_DIR_OVERRIDE = "persist.somc.smartnet.nn_dir_override";

    /**
     * The system property to override cellular inference result, value range (0,100)
     * it is used by dividing 100f
     */
    public static final String PROP_NN_CELL_INFERENCE_RESULT_OVERRIDE =
            "somc.smartnet.cell_inference_result_override";
}
