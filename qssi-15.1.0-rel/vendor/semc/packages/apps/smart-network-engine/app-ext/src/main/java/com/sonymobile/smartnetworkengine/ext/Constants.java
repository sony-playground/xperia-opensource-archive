/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.ext;

public class Constants {

    /** The identifier of IDD probe package for cellular */
    public static final String IDD_PROBE_PKG_CELLULAR =
            "com.sonyericsson.idd.probe.android.smartnetworkengine";

    /** The identifier of IDD probe name for cellular */
    public static final String IDD_PROBE_NAME_CELLULAR = "SneCellularEvent";

    /** The max size(byte) allowed to upload to IDD per day. */
    public static final int IDD_DAILY_UPLOAD_LIMIT_SIZE = 45 * 1024; // 45 KB

    /** The time of IDD upload restriction period */
    public static final long IDD_UPLOAD_LIMIT_PERIOD_MSEC = 26 * 60 * 60 * 1000; // 26 hours

    /** The number of samples used for throughput assessment */
    public static final int THROUGHPUT_CHECK_PERIOD = 60;

    /** The number of over-threshold samples which is required for IDD data collection */
    public static final int THROUGHPUT_CHECK_OVER_THRESHOLD = 10;

    /** The throughput threshold for valid samples (byte-per-sec) */
    public static final int THROUGHPUT_THRESHOLD = 500 * 1000 / 8; // 500 kbps

    // ---------- Settings provider key definitions ----------

    public static final String SETTINGS_VERBOSE_LOGGING_ENABLED =
            "somc.smartnet_verbose_logging_enabled";
}
