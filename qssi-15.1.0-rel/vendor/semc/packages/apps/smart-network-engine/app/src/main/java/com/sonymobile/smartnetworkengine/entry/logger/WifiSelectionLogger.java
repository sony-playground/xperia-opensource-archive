/*
 * Copyright 2020, 2021, 2022, 2023, 2024 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.entry.logger;

import static com.sonymobile.smartnetworkengine.Constants.ENTRY_ASSET_DIR;
import static com.sonymobile.smartnetworkengine.Constants.ENTRY_LABEL_MEAM_VAR_FILENAME;
import static com.sonymobile.smartnetworkengine.Constants.FLS_APP_ID_ENTRY;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.res.AssetManager;
import android.net.ConnectivityDiagnosticsManager;
import android.net.ConnectivityDiagnosticsManager.ConnectivityDiagnosticsCallback;
import android.net.ConnectivityDiagnosticsManager.ConnectivityReport;
import android.net.ConnectivityManager;
import android.net.ConnectivityManager.NetworkCallback;
import android.net.Network;
import android.net.NetworkCapabilities;
import android.net.NetworkRequest;
import android.net.wifi.ScanResult;
import android.net.wifi.SupplicantState;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.net.wifi.WifiScanner;
import android.net.wifi.WifiUsabilityStatsEntry;
import android.os.Handler;
import android.os.HandlerExecutor;
import android.os.HandlerThread;
import android.os.PowerManager;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.sonymobile.smartnetworkengine.SneApplication;
import com.sonymobile.smartnetworkengine.WifiExtController;
import com.sonymobile.smartnetworkengine.api.LoggingStats;
import com.sonymobile.smartnetworkengine.api.SneApiClient;
import com.sonymobile.smartnetworkengine.api.SneEventManager;
import com.sonymobile.smartnetworkengine.api.SneLoggingEventCallback;
import com.sonymobile.smartnetworkengine.entry.logger.collector.WifiLinkLayerStatsCollector;
import com.sonymobile.smartnetworkengine.fls.FLSystemManager;
import com.sonymobile.smartnetworkengine.fls.Predictor;
import com.sonymobile.smartnetworkengine.fls.Predictor.PredictionResult;
import com.sonymobile.smartnetworkengine.util.HomeNetworkDetector;
import com.sonymobile.smartnetworkengine.util.Log;
import com.sonymobile.smartnetworkengine.util.WifiChecker;
import com.sonymobile.snewifiscan.SneScanDataHolder;
import com.sonymobile.snewifiscan.SneWifiScanner;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.file.Paths;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

public class WifiSelectionLogger {

    private static final String TAG = WifiSelectionLogger.class.getSimpleName();

    public static final String LOGGER_VERSION = "2.1.0";

    private static final String IDD_FORMAT_VERSION = "1.3.4";

    private static final int MAX_QUEUE_LENGTH = 20;

    private static final int USABILITY_STATS_TIMEOUT_MSEC = 3000;

    private final Context mContext;

    private final WifiExtController mWifiExtController;

    private final Handler mHandler;

    private final PowerManager mPowerManager;

    private final SneWifiScanner mSneWifiScanner;

    private final WifiManager mWifiManager;

    private final ConnectivityManager mConnectivityManager;

    private final ConnectivityDiagnosticsManager mConnectivityDiagnosticsManager;

    private final WifiLinkLayerStatsCollector mLinkLayerStatsCollector;

    private final WifiSelectionLogParser mWifiSelectionLogParser;

    @Nullable
    private SneApiClient mSneApiClient;

    @Nullable
    private SneEventManager mSneEventManager;

    @Nullable
    private Predictor mPredictor;

    @Nullable
    private LoggerEventListener mLoggerEventListener;

    @Nullable
    private PredictionResult mPredictionResult;

    private boolean mStarted;

    private boolean mLoggingStarted;

    private boolean mWifiValidated;

    private boolean mWifiReValidating;

    private Network mWifiNetwork;

    private boolean mAlreadyWifiBecomeDefaultNw;

    private boolean mHomeNetworkDetected;

    private boolean mReInferenceOccurred;

    private float mMean;

    private float mVar;

    private final WifiUsabilityStatsListener mWifiUsabilityStatsListener;

    private final Queue<ScanResultInfo> mScanResultsInfoBeforeValidationQueue = new ArrayDeque<>();

    private final Queue<LoggingStatsInfo> mLoggingStatsInfoQueue = new ArrayDeque<>();

    private final Queue<ConnectStatsInfo> mConnectStatsQueue = new ArrayDeque<>();

    private final Queue<ValidationCompleteStatsInfo> mValidationCompleteStatsInfoQueue =
            new ArrayDeque<>();

    private final List<String> mConnectedBssids = new ArrayList<>();

    // Note: the callback methods are invoked on main thread.
    private final SneApiClient.ConnectionCallbacks mSneConnectionCallbacks =
            new SneApiClient.ConnectionCallbacks() {
                @Override
                public void onConnected(String name, Object service) {
                    mHandler.post(() -> {
                        mSneEventManager = (SneEventManager) service;
                        if (mLoggingStarted) {
                            mSneEventManager.setLoggingEventCallback(mSneLoggingEventCallback);
                        }
                    });
                }

                @Override
                public void onDisconnected(String name) {
                    mHandler.post(() -> mSneEventManager = null);
                }
            };

    /**
     * A broadcast receiver to control logging start and stop
     */
    private final BroadcastReceiver mLoggingOnOffController = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final boolean wifiOn = mWifiManager.isWifiEnabled();
            final boolean screenOn = mPowerManager.isInteractive();
            if (wifiOn && screenOn) {
                Log.v(TAG, "[Event] Logging should be on");
                startLogging();
            } else {
                Log.v(TAG, "[Event] Logging should be off (wifi off: " + !wifiOn + ", screen off: "
                        + !screenOn + ")");
                sendLoggedData();
                stopLogging();
            }
        }
    };

    public WifiSelectionLogger(@NonNull Context context) {
        mContext = context;
        mWifiExtController = ((SneApplication) context.getApplicationContext())
                .getWifiExtController();
        mPowerManager = (PowerManager) mContext.getSystemService(Context.POWER_SERVICE);
        mSneWifiScanner = mContext.getSystemService(SneWifiScanner.class);
        mWifiManager = (WifiManager) mContext.getSystemService(Context.WIFI_SERVICE);
        mConnectivityManager = (ConnectivityManager) mContext.getSystemService(
                Context.CONNECTIVITY_SERVICE);
        mConnectivityDiagnosticsManager =
                mContext.getSystemService(ConnectivityDiagnosticsManager.class);
        mLinkLayerStatsCollector = new WifiLinkLayerStatsCollector();

        mWifiSelectionLogParser = new WifiSelectionLogParser(context);

        // Create a dedicated thread for all event handling
        HandlerThread handlerThread = new HandlerThread(TAG);
        handlerThread.start();
        mHandler = new Handler(handlerThread.getLooper());

        mWifiUsabilityStatsListener = new WifiUsabilityStatsListener();
        // TODO: REFACTOR - should not run on main thread
        loadMeanAndVarForLabelAverage(context.getAssets());
    }

    public void start() {
        mHandler.post(() -> {
            if (!mStarted) {
                connectToSneEventService();
                IntentFilter filter = new IntentFilter();
                filter.addAction(WifiManager.WIFI_STATE_CHANGED_ACTION); // Sticky intent
                filter.addAction(Intent.ACTION_SCREEN_ON);
                filter.addAction(Intent.ACTION_SCREEN_OFF);
                mContext.registerReceiver(mLoggingOnOffController, filter, null, mHandler);
                NetworkRequest networkRequest = new NetworkRequest.Builder()
                        .addTransportType(NetworkCapabilities.TRANSPORT_WIFI)
                        .build();
                mConnectivityManager.registerNetworkCallback(networkRequest, mWifiNetworkCallback,
                        mHandler);
                mConnectivityManager.registerDefaultNetworkCallback(mDefaultNetworkCallback,
                        mHandler);
                mStarted = true;
            }
        });
    }

    public void stop() {
        mHandler.post(() -> {
            if (mStarted) {
                stopLogging();
                mConnectivityManager.unregisterNetworkCallback(mDefaultNetworkCallback);
                mConnectivityManager.unregisterNetworkCallback(mWifiNetworkCallback);
                mContext.unregisterReceiver(mLoggingOnOffController);
                disconnectFromSneEventService();
                resetConnectionStatus();
                mStarted = false;
            }
        });
    }

    public void setPredictor(@Nullable Predictor predictor) {
        mHandler.post(() -> mPredictor = predictor);
    }

    public void setLoggerEventListener(@Nullable LoggerEventListener listener) {
        mHandler.post(() -> mLoggerEventListener = listener);
    }

    public void requestLoggingStatusUpdate() {
        mHandler.post(() -> {
            if (mLoggerEventListener != null) {
                mLoggerEventListener.onLoggingStatusChanged(mLoggingStarted);
            }
        });
    }

    public float calcLabelAverage(float avg) {
        final float sd = (float) Math.sqrt(mVar);
        float labelAverage;
        if (!Float.isNaN(avg) && sd != 0) {
            labelAverage = (avg - mMean) / sd;
        } else {
            labelAverage = 0;
            Log.w(TAG, "cannot calculate the label average");
        }
        return labelAverage;
    }

    private void startLogging() {
        if (!mLoggingStarted) {
            Log.v(TAG, "Logging goes on");
            // Set callback for wifi scan event
            mSneWifiScanner.setWifiScanResultCallback(new HandlerExecutor(mHandler),
                    mSneWifiScanResultCallback);

            // Register broadcast receiver for wifi connection event (L2 ready and roaming)
            IntentFilter filter = new IntentFilter(
                    WifiManager.SUPPLICANT_STATE_CHANGED_ACTION); // Sticky intent
            mContext.registerReceiver(mWifiConnectionReceiver, filter, null, mHandler);

            // Register Re-validation complete callback
            NetworkRequest networkRequest = new NetworkRequest.Builder()
                    .addTransportType(NetworkCapabilities.TRANSPORT_WIFI)
                    .build();
            mConnectivityDiagnosticsManager.registerConnectivityDiagnosticsCallback(
                    networkRequest, new HandlerExecutor(mHandler),
                    mConnectivityDiagnosticsCallback);

            // Start to receive onStatsUpdated callback
            if (mSneEventManager != null) {
                mSneEventManager.setLoggingEventCallback(mSneLoggingEventCallback);
            }

            // Prepare to read WifiUsabilityStats value
            mWifiUsabilityStatsListener.wifiStatsEntry = null;
            mWifiManager.addOnWifiUsabilityStatsListener(
                    mContext.getMainExecutor(), mWifiUsabilityStatsListener);

            // Initialize data structures
            clearLoggedData();

            mLoggingStarted = true;
            // Notify status change
            if (mLoggerEventListener != null) {
                mLoggerEventListener.onLoggingStatusChanged(true);
            }
        }
    }

    private void stopLogging() {
        if (mLoggingStarted) {
            Log.v(TAG, "Logging goes off");
            mWifiManager.removeOnWifiUsabilityStatsListener(mWifiUsabilityStatsListener);
            if (mSneEventManager != null) {
                mSneEventManager.setLoggingEventCallback(null);
            }
            mConnectivityDiagnosticsManager.unregisterConnectivityDiagnosticsCallback(
                    mConnectivityDiagnosticsCallback);
            mContext.unregisterReceiver(mWifiConnectionReceiver);
            mSneWifiScanner.clearWifiScanResultCallback();
            clearLoggedData();
            mLoggingStarted = false;
            // Notify status change
            if (mLoggerEventListener != null) {
                mLoggerEventListener.onLoggingStatusChanged(false);
            }
        }
    }

    private void connectToSneEventService() {
        if (mSneApiClient == null) {
            // Connect to the SNE event service
            mSneApiClient = new SneApiClient(mContext);
            mSneApiClient.connect(SneApiClient.SNE_EVENT_SERVICE, mSneConnectionCallbacks);
        }
    }

    private void disconnectFromSneEventService() {
        if (mSneApiClient != null) {
            mSneApiClient.disconnect();
            mSneApiClient = null;
            mSneEventManager = null;
        }
    }

    private void resetConnectionStatus() {
        mAlreadyWifiBecomeDefaultNw = false;
        mWifiNetwork = null;
        mWifiValidated = false;
        mWifiReValidating = false;
    }

    private void clearLoggedData() {
        mWifiSelectionLogParser.clearData();
        mHomeNetworkDetected = false;
        mReInferenceOccurred = false;
        mScanResultsInfoBeforeValidationQueue.clear();
        mLoggingStatsInfoQueue.clear();
        mConnectStatsQueue.clear();
        mValidationCompleteStatsInfoQueue.clear();
        mConnectedBssids.clear();
        mPredictionResult = null;
    }

    private boolean doInferenceIfNeeded() {
        boolean inferenceDone = false;
        mPredictionResult = null;
        mHomeNetworkDetected = HomeNetworkDetector.isHomeNetwork(mContext);
        Log.v(TAG, "home network detection: " + (mHomeNetworkDetected ? "Home" : "Non-home"));
        mLinkLayerStatsCollector.refresh(mWifiExtController.getPrimaryInterfaceName());
        ValidationCompleteStatsInfo validationCompleteStatsInfo = new ValidationCompleteStatsInfo(
                mWifiManager, mWifiUsabilityStatsListener,
                mLinkLayerStatsCollector.getRadioTimeInfo(), mWifiExtController);
        mValidationCompleteStatsInfoQueue.add(validationCompleteStatsInfo);
        mWifiSelectionLogParser.putValidationCompleteStatsInfo(validationCompleteStatsInfo);
        if (mPredictor != null) {
            mWifiSelectionLogParser.putLabelAverage(
                    calcLabelAverage(mPredictor.getAverageOfLabel()));
            List<Float> parsedFeatures = mWifiSelectionLogParser.parseFeatures();
            String groupLabel = validationCompleteStatsInfo.getBssid();
            if (parsedFeatures != null && groupLabel != null) {
                mPredictionResult = mPredictor.predict1d(parsedFeatures, groupLabel);
            }

            // Notify parsed features
            if (mLoggerEventListener != null) {
                mLoggerEventListener.onInferenceDone(mPredictionResult);
            }
            inferenceDone = true;
        }
        return inferenceDone;
    }

    private void loadMeanAndVarForLabelAverage(AssetManager assetManager) {
        try (InputStream inputStream = assetManager.open(
                Paths.get(ENTRY_ASSET_DIR, ENTRY_LABEL_MEAM_VAR_FILENAME).toString());
             InputStreamReader reader = new InputStreamReader(inputStream);
             BufferedReader bufferedReader = new BufferedReader(reader)) {

            String values = bufferedReader.readLine();
            if (values != null) {
                String[] meanAndVar = values.split(",");
                try {
                    mMean = Float.parseFloat(meanAndVar[0]);
                    mVar = Float.parseFloat(meanAndVar[1]);
                } catch (NumberFormatException e) {
                    Log.e(TAG, "cannot read csv data for normalization (NumberFormatException)");
                }
            } else {
                Log.e(TAG, "cannot read csv data for normalization (File format error)");
            }
        } catch (IOException e) {
            Log.e(TAG, "cannot read csv data for normalization");
        }
    }

    // Here are the callbacks for metrics collection

    private final NetworkCallback mWifiNetworkCallback = new NetworkCallback() {
        /** This is called after validated event */
        @Override
        public void onCapabilitiesChanged(Network network,
                NetworkCapabilities networkCapabilities) {
            super.onCapabilitiesChanged(network, networkCapabilities);
            if (networkCapabilities.hasCapability(NetworkCapabilities.NET_CAPABILITY_VALIDATED)
                    && !mWifiValidated) {
                Log.v(TAG, "[Event] Validated");
                mWifiValidated = true;
                mWifiNetwork = network;
                if (mLoggingStarted) {
                    doInferenceIfNeeded();
                }
            }
        }

        /** This is called after disconnected event */
        @Override
        public void onLost(Network network) {
            super.onLost(network);
            Log.v(TAG, "[Event] Disconnected");
            resetConnectionStatus();
            sendLoggedData();
        }
    };

    private final NetworkCallback mDefaultNetworkCallback = new NetworkCallback() {
        @Override
        public void onCapabilitiesChanged(@NonNull Network network,
                @NonNull NetworkCapabilities nc) {
            super.onCapabilitiesChanged(network, nc);
            if (nc.hasTransport(NetworkCapabilities.TRANSPORT_WIFI)) {
                if (!mAlreadyWifiBecomeDefaultNw) {
                    // This flag is used for condition as
                    // - Wi-Fi connection is validated for this SSID at least once
                    // - The Wi-Fi has been judged as "Good" for this SSID at least once
                    mAlreadyWifiBecomeDefaultNw = true;
                    // Once default network becomes Wi-Fi, mWifiReValidating will be no longer used.
                    // So it should be initialized.
                    mWifiReValidating = false;
                }
            } else {
                // If the default network is non-Wifi (Cellular), there are two cases.
                // 1) EntryScore returns as "Bad".
                // 2) EntryScore returns as "Good", but ConnectedScore returns "Bad" after that.
                // To avoid triggering re-validation process in case 2),
                // mAlreadyWifiBecomeDefaultNw flag should NOT be cleared here.
            }
        }
    };

    private final SneWifiScanner.SneWifiScanResultCallback mSneWifiScanResultCallback =
            new SneWifiScanner.SneWifiScanResultCallback() {
                @Override
                public void onResult(SneScanDataHolder scanResult) {
                    if (!mWifiValidated) {
                        Log.v(TAG, "[Event] Scan Done (Before Validated)");
                        mLinkLayerStatsCollector.refresh(
                                mWifiExtController.getPrimaryInterfaceName());
                        ScanResultInfo scanResultInfo = new ScanResultInfo(
                                scanResult.getScanDataList(),
                                mLinkLayerStatsCollector.getRadioTimeInfo());
                        if (mScanResultsInfoBeforeValidationQueue.size() > MAX_QUEUE_LENGTH) {
                            // If the length of queue is over the limitation, remove the first
                            // element.
                            mScanResultsInfoBeforeValidationQueue.remove();
                        }
                        mScanResultsInfoBeforeValidationQueue.add(scanResultInfo);
                        mWifiSelectionLogParser.putScanResultInfoBeforeValidation(scanResultInfo);
                    }
                }
            };

    /**
     * This receiver is called when wifi connected as L2 level (Default NW is not changed)
     */
    private final BroadcastReceiver mWifiConnectionReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            SupplicantState state = intent.getParcelableExtra(WifiManager.EXTRA_NEW_STATE);
            WifiInfo wifiInfo = mWifiManager.getConnectionInfo();
            if (wifiInfo == null) { // Should never happen but just in case
                Log.w(TAG, "wifiInfo is not valid");
                return;
            }
            String bssid = wifiInfo.getBSSID();
            if (state == SupplicantState.COMPLETED
                    && bssid != null /* To ignore old event due to sticky behavior */
                    && !mAlreadyWifiBecomeDefaultNw /* To ignore event after connected startup */) {
                // Check if new connection established or roaming completed
                if (mConnectedBssids.isEmpty()) {
                    Log.v(TAG, "[Event] Connected: " + bssid);
                    ConnectStatsInfo connectStatsInfo = new ConnectStatsInfo(
                            mWifiManager, mWifiUsabilityStatsListener,
                            mLinkLayerStatsCollector.getRadioTimeInfo(), mWifiExtController);
                    mConnectStatsQueue.add(connectStatsInfo);
                    mConnectedBssids.add(bssid);
                    mWifiSelectionLogParser.putConnectStatsInfo(connectStatsInfo);
                    mWifiSelectionLogParser.putConnectedBssid(bssid);
                } else if (!mConnectedBssids.get(mConnectedBssids.size() - 1).equals(bssid)) {
                    Log.v(TAG, "[Event] Roamed: "
                            + bssid + " from " + mConnectedBssids.get(mConnectedBssids.size() - 1));
                    ConnectStatsInfo connectStatsInfo = new ConnectStatsInfo(
                            mWifiManager, mWifiUsabilityStatsListener,
                            mLinkLayerStatsCollector.getRadioTimeInfo(), mWifiExtController);
                    mConnectStatsQueue.add(connectStatsInfo);
                    mConnectedBssids.add(bssid);
                    mWifiSelectionLogParser.putConnectStatsInfo(connectStatsInfo);
                    mWifiSelectionLogParser.putConnectedBssid(bssid);
                    // Trigger re-validation only when
                    // - Already validated once
                    // - Default NW has not become Wi-Fi yet (Previous prediction returns as bad-AP)
                    // - Wi-Fi roaming occurred
                    // - There is no another running re-validation
                    if (mWifiNetwork != null && !mAlreadyWifiBecomeDefaultNw &&
                            !mWifiReValidating) {
                        if (mLoggerEventListener != null &&
                                (WifiChecker.is6GHz(wifiInfo.getFrequency())
                                        || WifiChecker.isMloConnection(wifiInfo))) {
                            Log.v(TAG, "Roaming to 6Ghz WiFi or WiFi with MLO, stop re-validation");
                            mLoggerEventListener.onInferenceDone(null);
                            return;
                        }

                        Log.v(TAG, "[Event] Trigger Re-validation");
                        mWifiReValidating = true;
                        mConnectivityManager.reportNetworkConnectivity(mWifiNetwork, true);
                        mConnectivityManager.reportNetworkConnectivity(mWifiNetwork, false);
                    }
                }
            }
        }
    };

    private final ConnectivityDiagnosticsCallback mConnectivityDiagnosticsCallback =
            new ConnectivityDiagnosticsCallback() {
                @Override
                public void onConnectivityReportAvailable(@NonNull ConnectivityReport report) {
                    super.onConnectivityReportAvailable(report);
                    // Do additional inference only if
                    // - This is re-validation (Already validated once previously)
                    // - Default NW has not become Wi-Fi yet (Previous prediction returns as bad-AP)
                    // - All required input (scan/connect/validated) are available
                    if (mWifiReValidating && !mAlreadyWifiBecomeDefaultNw) {
                        Log.v(TAG, "[Event] Re-validated. Will execute additional inference");
                        mReInferenceOccurred = doInferenceIfNeeded();
                    }
                    mWifiReValidating = false;
                }
            };

    // Note: the callback method is invoked on the worker thread in the EventForwarder class.
    private final SneLoggingEventCallback mSneLoggingEventCallback = new SneLoggingEventCallback() {
        @Override
        public void onStatsUpdated(@NonNull LoggingStats loggingStats) {
            mHandler.post(() -> {
                if (mAlreadyWifiBecomeDefaultNw) {
                    Log.v(TAG, "SneLoggingEventCallback#onStatsUpdated: " + loggingStats);

                    WifiInfo wifiInfo = mWifiManager.getConnectionInfo();
                    if (mPredictionResult != null && WifiChecker.isMloConnection(wifiInfo)) {
                        // After default network switch to WiFi, then WiFi change from one
                        // link to multiple links, suspend collection of idd data
                        mPredictionResult = null;
                    }
                    LoggingStats.Wifi wifi = loggingStats.getWifi();
                    LoggingStatsInfo loggingStatsInfo = new LoggingStatsInfo(wifi, wifiInfo);
                    if (mLoggingStatsInfoQueue.size() < MAX_QUEUE_LENGTH) {
                        // If the queue length is over the limitation, do not insert the new one.
                        mLoggingStatsInfoQueue.add(loggingStatsInfo);
                    }
                    mWifiSelectionLogParser.putLoggingStatsInfo(loggingStatsInfo);
                }
            });
        }
    };

    private boolean hasLoggedDataToUpload() {
        return !mConnectStatsQueue.isEmpty() && !mScanResultsInfoBeforeValidationQueue.isEmpty()
                && !mLoggingStatsInfoQueue.isEmpty()
                && !mValidationCompleteStatsInfoQueue.isEmpty();
    }

    /**
     * Send Json data to IDD
     */
    private void sendLoggedData() {
        if (hasLoggedDataToUpload() && mLoggerEventListener != null) {
            Float label = mWifiSelectionLogParser.parseLabel();
            if (mPredictionResult != null && label != null) {
                JSONObject iddUploadJson = getFlLoggerJsonObject(label);
                mLoggerEventListener.onDataLogged(mPredictionResult, label, iddUploadJson);
            }
        } else {
            Log.v(TAG, "There is no data to be uploaded.");
        }
        clearLoggedData();
    }

    /**
     * Create FL json file.
     *
     * @param label The WiFi quality label.
     *
     * @return JSONObject which to be uploaded to Idd server.
     */
    private JSONObject getFlLoggerJsonObject(Float label) {
        JSONObject parentJsonObject = new JSONObject();
        try {
            // version
            parentJsonObject.put("version", IDD_FORMAT_VERSION);
            // home network detection
            parentJsonObject.put("home_network", mHomeNetworkDetected ? 1 : 0);

            // fl data information
            // This value can be changed in EntryPhaseManager.
            parentJsonObject.put("data_context", 0);

            // A flag whether re-inference after Wi-Fi roaming occurs or not
            parentJsonObject.put("re_inference", mReInferenceOccurred ? 1 : 0);

            if (mPredictionResult.isScored()) {
                // Model
                parentJsonObject.put("model_id", mPredictionResult.getModelVersion());
                // Inference score
                parentJsonObject.put("inference_score", mPredictionResult.getScore());
                // WiFi quality label
                parentJsonObject.put("label", label);

                FLSystemManager flSystemManager =
                        ((SneApplication) mContext.getApplicationContext()).getFLSystemManager();
                // Data count condition
                parentJsonObject.put("dc_condition", flSystemManager.checkDcCondition(
                        FLS_APP_ID_ENTRY));
                // Positive Rate
                parentJsonObject.put("positive_rate", flSystemManager.getPositiveRate(
                        FLS_APP_ID_ENTRY));
            }

            // for scan_info
            JSONArray scanInfoArrays = new JSONArray();
            while (!mScanResultsInfoBeforeValidationQueue.isEmpty()) {
                scanInfoArrays.put(getScanResultJsonArray(mScanResultsInfoBeforeValidationQueue));
            }
            parentJsonObject.put("scan_info", scanInfoArrays);

            // for connected_info
            JSONArray connectedInfoArrays = new JSONArray();
            while (!mConnectStatsQueue.isEmpty()) {
                connectedInfoArrays.put(getConnectedInfoJsonArray());
            }
            parentJsonObject.put("connected_info", connectedInfoArrays);

            // for validation_complete_info
            JSONArray validationCompleteInfoArrays = new JSONArray();
            while (!mValidationCompleteStatsInfoQueue.isEmpty()) {
                validationCompleteInfoArrays.put(getValidationCompleteInfoJsonArray());
            }
            parentJsonObject.put("validation_complete_info", validationCompleteInfoArrays);

            // for periodic_info
            JSONArray periodicInfoArrays = new JSONArray();
            while (!mLoggingStatsInfoQueue.isEmpty()) {
                periodicInfoArrays.put(getPeriodicInfoJsonArray());
            }
            parentJsonObject.put("periodic_info", periodicInfoArrays);

        } catch (JSONException e) {
            e.printStackTrace();
        }
        Log.v(TAG, "created json file: " + parentJsonObject.toString());
        return parentJsonObject;
    }

    private JSONArray getScanResultJsonArray(
            Queue<ScanResultInfo> scanResultInfoQueue) {
        // To find the same frequency to have connect
        ScanResultInfo scanResultInfo = scanResultInfoQueue.poll();
        if (scanResultInfo == null) {
            return new JSONArray(); // Should never happen
        }
        LoggingStatsInfo loggingStatsInfo = mLoggingStatsInfoQueue.peek();

        // search for a scan result to match connected wifi.
        JSONArray scanResultInfoArray = new JSONArray();
        for (ScanResult scanResult : scanResultInfo.getScanResults()) {
            if (loggingStatsInfo != null && mConnectedBssids.contains(scanResult.BSSID)) {
                List<ScanResult.InformationElement> informationElements =
                        scanResult.getInformationElements();
                InformationElementParser.BssLoad bssLoad = InformationElementParser.getBssLoadIE(
                        informationElements);
                WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo =
                        scanResultInfo.getRadioTimeInfo();
                JSONArray scanResultJson = new JSONArray();
                // add parameters to the array
                scanResultJson.put(scanResultInfo.getTimeStamp());
                scanResultJson.put(scanResultInfo.isFullScan() ? 1 : 0);
                scanResultJson.put(scanResult.SSID);
                scanResultJson.put(scanResult.BSSID);
                scanResultJson.put(scanResult.level);
                scanResultJson.put(scanResult.frequency);
                scanResultJson.put(scanResult.channelWidth);
                scanResultJson.put(scanResultInfo.getNumOfCoBSSs(scanResult.frequency,
                        scanResult.BSSID));
                scanResultJson.put(scanResultInfo.getMaxRssiOfCoChannel(scanResult.frequency,
                        scanResult.BSSID));
                scanResultJson.put(scanResultInfo.getNumOfInterBSSs(scanResult.frequency));
                scanResultJson.put(
                        scanResultInfo.getMaxRssiOfInterChannel(scanResult.frequency));
                scanResultJson.put(radioTimeInfo.getCcaBusyTimes().get(scanResult.frequency));
                scanResultJson.put(radioTimeInfo.getOnTimes().get(scanResult.frequency));
                scanResultJson.put(bssLoad.stationCount);
                scanResultJson.put(bssLoad.channelUtilization);
                scanResultJson.put(bssLoad.capacity);
                scanResultJson.put(-1); // num of BT (temporally filled with -1)
                scanResultJson.put(-1); // num of cell (temporally filled with -1)
                scanResultInfoArray.put(scanResultJson);
            }

        }
        return scanResultInfoArray;
    }

    private JSONArray getConnectedInfoJsonArray() {
        JSONArray connectedInfoArray = new JSONArray();
        ConnectStatsInfo connectStatsInfo = mConnectStatsQueue.poll();
        if (connectStatsInfo == null) {
            return connectedInfoArray; // Should never happen
        }
        WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo =
                connectStatsInfo.getRadioTimeInfo();
        LoggingStatsInfo loggingStatsInfo = mLoggingStatsInfoQueue.peek();
        if (loggingStatsInfo != null) {
            int frequency = connectStatsInfo.getFrequency();

            // add parameters to the array.
            connectedInfoArray.put(connectStatsInfo.getTimeStamp());
            connectedInfoArray.put(connectStatsInfo.getSsid().replace("\"", ""));
            connectedInfoArray.put(connectStatsInfo.getBssid());
            connectedInfoArray.put(connectStatsInfo.getRssi());
            connectedInfoArray.put(frequency);
            connectedInfoArray.put(connectStatsInfo.getTxLinkSpeed());
            connectedInfoArray.put(connectStatsInfo.getRxLinkSpeed());
            connectedInfoArray.put(connectStatsInfo.getRawTxSuccess());
            connectedInfoArray.put(connectStatsInfo.getRawTxRetries());
            connectedInfoArray.put(connectStatsInfo.getRawTxBad());
            connectedInfoArray.put(connectStatsInfo.getRawRxSuccess());
            connectedInfoArray.put(radioTimeInfo.getCcaBusyTimes().get(frequency));
            connectedInfoArray.put(radioTimeInfo.getOnTimes().get(frequency));
        }
        return connectedInfoArray;
    }

    private JSONArray getValidationCompleteInfoJsonArray() {
        JSONArray validationCompleteInfoArray = new JSONArray();
        ValidationCompleteStatsInfo validationCompleteInfo =
                mValidationCompleteStatsInfoQueue.poll();
        if (validationCompleteInfo == null) {
            return validationCompleteInfoArray; // Should never happen
        }
        WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo =
                validationCompleteInfo.getRadioTimeInfo();
        LoggingStatsInfo loggingStatsInfo = mLoggingStatsInfoQueue.peek();
        if (loggingStatsInfo != null) {
            int frequency = validationCompleteInfo.getFrequency();

            // add parameters to the array.
            validationCompleteInfoArray.put(validationCompleteInfo.getTimeStamp());
            validationCompleteInfoArray.put(validationCompleteInfo.getSsid().replace("\"", ""));
            validationCompleteInfoArray.put(validationCompleteInfo.getBssid());
            validationCompleteInfoArray.put(validationCompleteInfo.getRssi());
            validationCompleteInfoArray.put(frequency);
            validationCompleteInfoArray.put(validationCompleteInfo.getTxLinkSpeed());
            validationCompleteInfoArray.put(validationCompleteInfo.getRxLinkSpeed());
            validationCompleteInfoArray.put(validationCompleteInfo.getRawTxSuccess());
            validationCompleteInfoArray.put(validationCompleteInfo.getRawTxRetries());
            validationCompleteInfoArray.put(validationCompleteInfo.getRawTxBad());
            validationCompleteInfoArray.put(validationCompleteInfo.getRawRxSuccess());
            validationCompleteInfoArray.put(radioTimeInfo.getCcaBusyTimes().get(frequency));
            validationCompleteInfoArray.put(radioTimeInfo.getOnTimes().get(frequency));
        }
        return validationCompleteInfoArray;
    }

    private JSONArray getPeriodicInfoJsonArray() {
        LoggingStatsInfo loggingStatsInfo = mLoggingStatsInfoQueue.poll();
        if (loggingStatsInfo == null) {
            return new JSONArray(); // Should never happen
        }
        LoggingStats.Wifi wifi = loggingStatsInfo.getWifi();

        JSONArray periodicInfoJsonArray = new JSONArray();
        periodicInfoJsonArray.put(loggingStatsInfo.getTimeStamp());
        periodicInfoJsonArray.put(loggingStatsInfo.getSsid().replace("\"", ""));
        periodicInfoJsonArray.put(loggingStatsInfo.getBssid());
        periodicInfoJsonArray.put(wifi.getRssi());
        periodicInfoJsonArray.put(wifi.getFrequency());
        periodicInfoJsonArray.put(wifi.getLinkSpeed());
        periodicInfoJsonArray.put(wifi.getTxSuccess());
        periodicInfoJsonArray.put(wifi.getTxRetries());
        periodicInfoJsonArray.put(wifi.getTxBad());
        periodicInfoJsonArray.put(wifi.getRxSuccess());
        periodicInfoJsonArray.put(wifi.getCcaBusyTime());
        periodicInfoJsonArray.put(wifi.getOnTime());
        periodicInfoJsonArray.put(wifi.getNumOfTxTriesInDriver());
        periodicInfoJsonArray.put(wifi.getIntegralUsedDescriptorInDriver());
        periodicInfoJsonArray.put(""); // Previously used to store LoggingStats.Activity#getType
        periodicInfoJsonArray.put(""); // Previously used to store value of |getCurrentTopActivity|

        return periodicInfoJsonArray;
    }

    /**
     * This class holds information (scan result, radiotime info, num of BT device and cell) when
     * wi-fi scanning is done
     */
    public static class ScanResultInfo {
        private long mTimeStamp;
        private List<ScanResult> mScanResults;
        private boolean mIsFullScan;
        private int mNumOfCoBSSs;
        private int mMaxRssiOfCoChannel;
        private int mNumOfInterBSSs;
        private int mMaxRssiOfInterChannel;
        private WifiLinkLayerStatsCollector.RadioTimeInfo mRadioTimeInfo;

        ScanResultInfo(List<WifiScanner.ScanData> scanDataList,
                WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo) {
            mTimeStamp = System.currentTimeMillis();
            if (scanDataList.size() > 0) {
                WifiScanner.ScanData scanData = scanDataList.get(0);
                ScanResult[] scanResults = scanData.getResults();
                mScanResults = new ArrayList<>(Arrays.asList(scanResults));
                mIsFullScan = isFullScan(scanData.getScannedBands());
                Collections.sort(mScanResults, (scanResult, t1) -> t1.level - scanResult.level);
            }
            mRadioTimeInfo = radioTimeInfo;
        }

        ScanResultInfo(long timeStamp, List<ScanResult> scanResults, boolean isFullScan,
                int numOfCoBSSs, int maxRssiOfCoChannel, int numOfInterBSSs,
                int maxRssiOfInterChannel,
                WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo) {
            mTimeStamp = timeStamp;
            mScanResults = scanResults;
            mIsFullScan = isFullScan;
            mNumOfCoBSSs = numOfCoBSSs;
            mMaxRssiOfCoChannel = maxRssiOfCoChannel;
            mNumOfInterBSSs = numOfInterBSSs;
            mMaxRssiOfInterChannel = maxRssiOfInterChannel;
            mRadioTimeInfo = radioTimeInfo;
        }

        public long getTimeStamp() {
            return mTimeStamp;
        }

        public boolean isFullScan() {
            return mIsFullScan;
        }

        public List<ScanResult> getScanResults() {
            return mScanResults;
        }

        public int getNumOfCoBSSs(int frequency, String bssid) {
            List<ScanResult> matchedScanResult = extractCoChannelFromScanResults(frequency, bssid);
            mNumOfCoBSSs = matchedScanResult.size();
            return mNumOfCoBSSs;
        }

        public int getMaxRssiOfCoChannel(int frequency, String bssid) {
            List<ScanResult> matchedScanResults = extractCoChannelFromScanResults(frequency, bssid);
            Collections.sort(matchedScanResults, (scanResult, t1) -> t1.level - scanResult.level);
            if (!matchedScanResults.isEmpty()) {
                mMaxRssiOfCoChannel = matchedScanResults.get(0).level;
            } else {
                mMaxRssiOfCoChannel = -127;
            }
            return mMaxRssiOfCoChannel;
        }

        public int getNumOfInterBSSs(int frequency) {
            List<ScanResult> matchedScanResults = extractInterChannelFromScanResults(frequency);
            mNumOfInterBSSs = matchedScanResults.size();
            return mNumOfInterBSSs;
        }

        public int getMaxRssiOfInterChannel(int frequency) {
            List<ScanResult> matchedScanResults = extractInterChannelFromScanResults(frequency);
            Collections.sort(matchedScanResults, (scanResult, t1) -> t1.level - scanResult.level);
            if (!matchedScanResults.isEmpty()) {
                mMaxRssiOfInterChannel = matchedScanResults.get(0).level;
            } else {
                mMaxRssiOfInterChannel = -127;
            }
            return mMaxRssiOfInterChannel;
        }

        public WifiLinkLayerStatsCollector.RadioTimeInfo getRadioTimeInfo() {
            return mRadioTimeInfo;
        }

        private List<ScanResult> extractCoChannelFromScanResults(int frequency, String bssid) {
            List<ScanResult> matchedScanResult = new ArrayList<>();
            for (ScanResult scanResult : mScanResults) {
                if (scanResult.frequency == frequency && !scanResult.BSSID.equals(bssid)) {
                    matchedScanResult.add(scanResult);
                }
            }
            return matchedScanResult;
        }

        private List<ScanResult> extractInterChannelFromScanResults(int frequency) {
            List<ScanResult> matchedScanResults = new ArrayList<>();
            for (ScanResult scanResult : mScanResults) {
                if ((scanResult.frequency > frequency - 20) && (scanResult.frequency
                        < frequency + 20) && (scanResult.frequency != frequency)) {
                    matchedScanResults.add(scanResult);
                }
            }
            return matchedScanResults;
        }

        /**
         * This method refers to WifiScanner.isFullBandScan
         * Test if scan is a full scan. i.e. scanning all available bands.
         * For backward compatibility, since some apps don't include 6GHz or 60Ghz in their requests
         * yet, lacking 6GHz or 60Ghz band does not cause the result to be false.
         */
        private boolean isFullScan(int scannedBands) {
            Log.v(TAG, "scanned bands: " + Integer.toBinaryString(scannedBands));
            return (scannedBands & WifiScanner.WIFI_BAND_24_GHZ) != 0
                    && (scannedBands & WifiScanner.WIFI_BAND_5_GHZ) != 0
                    && (scannedBands & WifiScanner.WIFI_BAND_5_GHZ_DFS_ONLY) != 0;
        }

        public static Builder builder() {
            return new Builder();
        }

        public static class Builder {
            private long mTimeStamp;
            private List<ScanResult> mScanResults;
            private boolean mIsFullScan;
            private int mNumOfCoBSSs;
            private int mMaxRssiOfCoChannel;
            private int mNumOfInterBSSs;
            private int mMaxRssiOfInterChannel;
            private WifiLinkLayerStatsCollector.RadioTimeInfo mRadioTimeInfo;

            public Builder timeStamp(long timeStamp) {
                mTimeStamp = timeStamp;
                return this;
            }

            public Builder scanResults(List<ScanResult> scanResults) {
                mScanResults = scanResults;
                return this;
            }

            public Builder isFullScan(Boolean isFullScan) {
                mIsFullScan = isFullScan;
                return this;
            }

            public Builder numOfCoBSSs(int numOfInterBSSs) {
                mNumOfCoBSSs = numOfInterBSSs;
                return this;
            }

            public Builder maxRssiOfCoChannel(int maxRssiOfCoChannel) {
                mMaxRssiOfCoChannel = maxRssiOfCoChannel;
                return this;
            }

            public Builder numOfInterBSSs(int numOfInterBSSs) {
                mNumOfInterBSSs = numOfInterBSSs;
                return this;
            }

            public Builder maxRssiOfInterChannel(int maxRssiOfInterChannel) {
                mMaxRssiOfInterChannel = maxRssiOfInterChannel;
                return this;
            }

            public Builder radioTimeInfo(WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo) {
                mRadioTimeInfo = radioTimeInfo;
                return this;
            }

            public ScanResultInfo build() {
                return new ScanResultInfo(mTimeStamp, mScanResults, mIsFullScan, mNumOfCoBSSs,
                        mMaxRssiOfCoChannel, mNumOfInterBSSs, mMaxRssiOfInterChannel,
                        mRadioTimeInfo);
            }
        }
    }

    /**
     * This class involves parameters after connection.
     */
    public static class LoggingStatsInfo {
        private final long mTimeStamp;
        private final LoggingStats.Wifi mWifi;
        private final String mBssid;
        private final String mSsid;

        LoggingStatsInfo(LoggingStats.Wifi wifi, WifiInfo wifiInfo) {
            mTimeStamp = System.currentTimeMillis();
            mWifi = wifi;
            if (wifiInfo != null) {
                mBssid = wifiInfo.getBSSID();
                mSsid = wifiInfo.getSSID();
            } else {
                mBssid = "";
                mSsid = "";
            }
        }

        public long getTimeStamp() {
            return mTimeStamp;
        }

        public LoggingStats.Wifi getWifi() {
            return mWifi;
        }

        public String getBssid() {
            return mBssid;
        }

        public String getSsid() {
            return mSsid;
        }
    }

    /**
     * This class involves parameters about just connecting to wifi
     */
    public static class ConnectStatsInfo {
        private long mTimeStamp;
        private String mSsid = "";
        private String mBssid = "";
        private int mRssi = -127;
        private int mFrequency = -1;
        private int mTxLinkSpeed = -1;
        private int mRxLinkSpeed = -1;
        private long mRawTxSuccess = -1;
        private long mRawTxRetries = -1;
        private long mRawTxBad = -1;
        private long mRawRxSuccess = -1;
        private WifiLinkLayerStatsCollector.RadioTimeInfo mRadioTimeInfo;

        ConnectStatsInfo(WifiManager wifiManager,
                WifiUsabilityStatsListener wifiUsabilityStatsListener,
                WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo,
                WifiExtController wifiExtController) {
            mTimeStamp = System.currentTimeMillis();
            WifiInfo wifiInfo = wifiManager.getConnectionInfo();
            if (wifiInfo != null) {
                mSsid = wifiInfo.getSSID();
                mBssid = wifiInfo.getBSSID();
                mFrequency = wifiInfo.getFrequency();
            }
            fetchWifiUsabilityStats(wifiUsabilityStatsListener, wifiExtController);
            if (wifiUsabilityStatsListener.wifiStatsEntry != null) {
                mRssi = wifiUsabilityStatsListener.wifiStatsEntry.getRssi();
                mTxLinkSpeed = wifiUsabilityStatsListener.wifiStatsEntry.getLinkSpeedMbps();
                mRxLinkSpeed = wifiUsabilityStatsListener.wifiStatsEntry.getRxLinkSpeedMbps();
                mRawTxSuccess = wifiUsabilityStatsListener.wifiStatsEntry.getTotalTxSuccess();
                mRawTxRetries = wifiUsabilityStatsListener.wifiStatsEntry.getTotalTxRetries();
                mRawTxBad = wifiUsabilityStatsListener.wifiStatsEntry.getTotalTxBad();
                mRawRxSuccess = wifiUsabilityStatsListener.wifiStatsEntry.getTotalRxSuccess();
            }
            mRadioTimeInfo = radioTimeInfo;
        }

        ConnectStatsInfo(long timeStamp, String ssid, String bssid, int rssi, int frequency,
                int txLinkSpeed, int rxLinkSpeed, long rawTxSuccess, long rawTxRetries,
                long rawTxBad, long rawRxSuccess,
                WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo) {
            mTimeStamp = timeStamp;
            mSsid = ssid;
            mBssid = bssid;
            mRssi = rssi;
            mFrequency = frequency;
            mTxLinkSpeed = txLinkSpeed;
            mRxLinkSpeed = rxLinkSpeed;
            mRawTxSuccess = rawTxSuccess;
            mRawTxRetries = rawTxRetries;
            mRawTxBad = rawTxBad;
            mRawRxSuccess = rawRxSuccess;
            mRadioTimeInfo = radioTimeInfo;
        }

        public long getTimeStamp() {
            return mTimeStamp;
        }

        public WifiLinkLayerStatsCollector.RadioTimeInfo getRadioTimeInfo() {
            return mRadioTimeInfo;
        }

        public String getSsid() {
            return mSsid;
        }

        public String getBssid() {
            return mBssid;
        }

        public int getTxLinkSpeed() {
            return mTxLinkSpeed;
        }

        public int getRxLinkSpeed() {
            return mRxLinkSpeed;
        }

        public int getRssi() {
            return mRssi;
        }

        public int getFrequency() {
            return mFrequency;
        }

        public long getRawTxSuccess() {
            return mRawTxSuccess;
        }

        public long getRawTxRetries() {
            return mRawTxRetries;
        }

        public long getRawTxBad() {
            return mRawTxBad;
        }

        public long getRawRxSuccess() {
            return mRawRxSuccess;
        }

        public static Builder builder() {
            return new Builder();
        }
        public static class Builder {
            private long mTimeStamp;
            private String mSsid;
            private String mBssid;
            private int mRssi;
            private int mFrequency;
            private int mTxLinkSpeed;
            private int mRxLinkSpeed;
            private long mRawTxSuccess;
            private long mRawTxRetries;
            private long mRawTxBad;
            private long mRawRxSuccess;
            private WifiLinkLayerStatsCollector.RadioTimeInfo mRadioTimeInfo;
            public Builder timestamp(long timeStamp) {
                mTimeStamp = timeStamp;
                return this;
            }
            public Builder ssid(String ssid) {
                mSsid = ssid;
                return this;
            }
            public Builder bssid(String bssid) {
                mBssid = bssid;
                return this;
            }
            public Builder rssi(int rssi) {
                mRssi = rssi;
                return this;
            }
            public Builder frequency(int frequency) {
                mFrequency = frequency;
                return this;
            }
            public Builder txLinkSpeed(int txLinkSpeed) {
                mTxLinkSpeed = txLinkSpeed;
                return this;
            }
            public Builder rxLinkSpeed(int rxLinkSpeed) {
                mRxLinkSpeed = rxLinkSpeed;
                return this;
            }
            public Builder rawTxSuccess(int rawTxSuccess) {
                mRawTxSuccess = rawTxSuccess;
                return this;
            }
            public Builder rawTxRetries(int rawTxRetries) {
                mRawTxRetries = rawTxRetries;
                return this;
            }
            public Builder rawTxBad(int rawTxBad) {
                mRawTxBad = rawTxBad;
                return this;
            }
            public Builder rawRxSuccess(int rawRxSuccess) {
                mRawRxSuccess = rawRxSuccess;
                return this;
            }
            public Builder radioTimeInfo(WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo) {
                mRadioTimeInfo = radioTimeInfo;
                return this;
            }
            public ConnectStatsInfo build() {
                return new ConnectStatsInfo(mTimeStamp, mSsid, mBssid, mRssi, mFrequency,
                        mTxLinkSpeed, mRxLinkSpeed, mRawTxSuccess, mRawTxRetries, mRawTxBad,
                        mRawRxSuccess, mRadioTimeInfo);
            }
        }
    }

    /**
     * This class involves parameters about just validated.
     */
    public static class ValidationCompleteStatsInfo {
        private long mTimeStamp;
        private String mSsid = "";
        private String mBssid = "";
        private int mRssi = -127;
        private int mFrequency = -1;
        private int mTxLinkSpeed = -1;
        private int mRxLinkSpeed = -1;
        private long mRawTxSuccess = -1;
        private long mRawTxRetries = -1;
        private long mRawTxBad = -1;
        private long mRawRxSuccess = -1;
        private WifiLinkLayerStatsCollector.RadioTimeInfo mRadioTimeInfo;

        ValidationCompleteStatsInfo(WifiManager wifiManager,
                WifiUsabilityStatsListener wifiUsabilityStatsListener,
                WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo,
                WifiExtController wifiExtController) {
            mTimeStamp = System.currentTimeMillis();
            WifiInfo wifiInfo = wifiManager.getConnectionInfo();
            if (wifiInfo != null) {
                mSsid = wifiInfo.getSSID();
                mBssid = wifiInfo.getBSSID();
                mFrequency = wifiInfo.getFrequency();
            }
            fetchWifiUsabilityStats(wifiUsabilityStatsListener, wifiExtController);
            if (wifiUsabilityStatsListener.wifiStatsEntry != null) {
                mRssi = wifiUsabilityStatsListener.wifiStatsEntry.getRssi();
                mTxLinkSpeed = wifiUsabilityStatsListener.wifiStatsEntry.getLinkSpeedMbps();
                mRxLinkSpeed = wifiUsabilityStatsListener.wifiStatsEntry.getRxLinkSpeedMbps();
                mRawTxSuccess = wifiUsabilityStatsListener.wifiStatsEntry.getTotalTxSuccess();
                mRawTxRetries = wifiUsabilityStatsListener.wifiStatsEntry.getTotalTxRetries();
                mRawTxBad = wifiUsabilityStatsListener.wifiStatsEntry.getTotalTxBad();
                mRawRxSuccess = wifiUsabilityStatsListener.wifiStatsEntry.getTotalRxSuccess();
            }
            mRadioTimeInfo = radioTimeInfo;
        }

        ValidationCompleteStatsInfo(long timeStamp, String ssid, String bssid, int rssi,
                int frequency, int txLinkSpeed, int rxLinkSpeed, long rawTxSuccess,
                long rawTxRetries, long rawTxBad, long rawRxSuccess,
                WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo) {
            mTimeStamp = timeStamp;
            mSsid = ssid;
            mBssid = bssid;
            mRssi = rssi;
            mFrequency = frequency;
            mTxLinkSpeed = txLinkSpeed;
            mRxLinkSpeed = rxLinkSpeed;
            mRawTxSuccess = rawTxSuccess;
            mRawTxRetries = rawTxRetries;
            mRawTxBad = rawTxBad;
            mRawRxSuccess = rawRxSuccess;
            mRadioTimeInfo = radioTimeInfo;
        }

        public long getTimeStamp() {
            return mTimeStamp;
        }

        public WifiLinkLayerStatsCollector.RadioTimeInfo getRadioTimeInfo() {
            return mRadioTimeInfo;
        }

        public String getSsid() {
            return mSsid;
        }

        public String getBssid() {
            return mBssid;
        }

        public int getTxLinkSpeed() {
            return mTxLinkSpeed;
        }

        public int getRxLinkSpeed() {
            return mRxLinkSpeed;
        }

        public int getRssi() {
            return mRssi;
        }

        public int getFrequency() {
            return mFrequency;
        }

        public long getRawTxSuccess() {
            return mRawTxSuccess;
        }

        public long getRawTxRetries() {
            return mRawTxRetries;
        }

        public long getRawTxBad() {
            return mRawTxBad;
        }

        public long getRawRxSuccess() {
            return mRawRxSuccess;
        }

        public static Builder builder() {
            return new Builder();
        }
        public static class Builder {
            private long mTimeStamp;
            private String mSsid;
            private String mBssid;
            private int mRssi;
            private int mFrequency;
            private int mTxLinkSpeed;
            private int mRxLinkSpeed;
            private long mRawTxSuccess;
            private long mRawTxRetries;
            private long mRawTxBad;
            private long mRawRxSuccess;
            private WifiLinkLayerStatsCollector.RadioTimeInfo mRadioTimeInfo;
            public Builder timestamp(long timeStamp) {
                mTimeStamp = timeStamp;
                return this;
            }
            public Builder ssid(String ssid) {
                mSsid = ssid;
                return this;
            }
            public Builder bssid(String bssid) {
                mBssid = bssid;
                return this;
            }
            public Builder rssi(int rssi) {
                mRssi = rssi;
                return this;
            }
            public Builder frequency(int frequency) {
                mFrequency = frequency;
                return this;
            }
            public Builder txLinkSpeed(int txLinkSpeed) {
                mTxLinkSpeed = txLinkSpeed;
                return this;
            }
            public Builder rxLinkSpeed(int rxLinkSpeed) {
                mRxLinkSpeed = rxLinkSpeed;
                return this;
            }
            public Builder rawTxSuccess(int rawTxSuccess) {
                mRawTxSuccess = rawTxSuccess;
                return this;
            }
            public Builder rawTxRetries(int rawTxRetries) {
                mRawTxRetries = rawTxRetries;
                return this;
            }
            public Builder rawTxBad(int rawTxBad) {
                mRawTxBad = rawTxBad;
                return this;
            }
            public Builder rawRxSuccess(int rawRxSuccess) {
                mRawRxSuccess = rawRxSuccess;
                return this;
            }
            public Builder radioTimeInfo(WifiLinkLayerStatsCollector.RadioTimeInfo radioTimeInfo) {
                mRadioTimeInfo = radioTimeInfo;
                return this;
            }
            public ValidationCompleteStatsInfo build() {
                return new ValidationCompleteStatsInfo(mTimeStamp, mSsid, mBssid, mRssi, mFrequency,
                        mTxLinkSpeed, mRxLinkSpeed, mRawTxSuccess, mRawTxRetries, mRawTxBad,
                        mRawRxSuccess, mRadioTimeInfo);
            }
        }
    }

    private static void fetchWifiUsabilityStats(
            WifiUsabilityStatsListener wifiUsabilityStatsListener,
            WifiExtController wifiExtController) {
        wifiUsabilityStatsListener.countDownLatch = new CountDownLatch(1);
        wifiExtController.requestWifiStatsUpdate();
        try {
            wifiUsabilityStatsListener.countDownLatch.await(
                    USABILITY_STATS_TIMEOUT_MSEC, TimeUnit.MILLISECONDS);
        } catch (Exception e) {
            Log.e(TAG, "failed to update WifiUsabilityStats: " + e);
        }
    }

    static class WifiUsabilityStatsListener implements WifiManager.OnWifiUsabilityStatsListener {
        volatile WifiUsabilityStatsEntry wifiStatsEntry;
        volatile CountDownLatch countDownLatch;

        @Override
        public void onWifiUsabilityStats(int seqNum, boolean isSameBssidAndFreq,
                WifiUsabilityStatsEntry statsEntry) {
            wifiStatsEntry = statsEntry;
            if (countDownLatch != null) {
                countDownLatch.countDown();
            }
        }
    }

    public interface LoggerEventListener {
        /**
         * Called when logging is started or stopped.
         */
        void onLoggingStatusChanged(boolean started);

        /**
         * Called when all necessary metrics on current session are collected.
         */
        void onDataLogged(PredictionResult predictionResult, float label, JSONObject data);

        /**
         * Called when inference is completed.
         *
         * @param predictionResult prediction result or null if prediction was not performed
         *                         correctly (e.g, due to parser failure, missing group label).
         */
        void onInferenceDone(@Nullable PredictionResult predictionResult);
    }
}
