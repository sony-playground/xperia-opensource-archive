/*
 * Copyright 2020, 2024 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.event;

import android.net.wifi.ScanResult;
import android.os.RemoteException;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;

import com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData;
import com.sonymobile.smartnetworkengine.api.ISneLoggingEventCallback;
import com.sonymobile.smartnetworkengine.api.ISneNetworkDecisionEventCallback;
import com.sonymobile.smartnetworkengine.api.LoggingStats;
import com.sonymobile.smartnetworkengine.api.SneLoggingEventCallback;
import com.sonymobile.smartnetworkengine.connected.logger.LoggerService;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * The role of this class is to forward various events in Smart Network Engine application to the
 * Extension application via the event callback API.
 */
public class EventForwarder {

    @Nullable
    private volatile ISneLoggingEventCallback mISneLoggingEventCallback;

    @Nullable
    private volatile ISneNetworkDecisionEventCallback mISneNetworkDecisionEventCallback;

    // For clients to be able to return from noteFooBar methods as soon as possible.
    private final ExecutorService mExecutor = Executors.newSingleThreadExecutor();

    /**
     * Sets a logging event callback.
     */
    void setLoggingEventCallback(@Nullable ISneLoggingEventCallback callback) {
        mISneLoggingEventCallback = callback;
    }

    /**
     * Sets a network decision event callback.
     */
    void setNetworkDecisionEventCallback(@Nullable ISneNetworkDecisionEventCallback callback) {
        mISneNetworkDecisionEventCallback = callback;
    }

    /**
     * Notify periodic stats update started.
     */
    public void noteLoggingStart() {
        ISneLoggingEventCallback callback = mISneLoggingEventCallback;
        if (callback != null) {
            mExecutor.execute(() -> {
                try {
                    callback.onStarted();
                } catch (RemoteException ignored) {
                }
            });
        }
    }

    /**
     * Notify periodic stats update stopped.
     */
    public void noteLoggingStop(@NonNull LoggerService.StopReason reason) {
        ISneLoggingEventCallback callback = mISneLoggingEventCallback;
        if (callback != null) {
            mExecutor.execute(() -> {
                int reasonValue;
                switch (reason) {
                    case NORMAL:
                        reasonValue = SneLoggingEventCallback.STOP_REASON_NORMAL;
                        break;
                    case SCREENOFF:
                        reasonValue = SneLoggingEventCallback.STOP_REASON_SCREENOFF;
                        break;
                    case SHUTDOWN:
                        reasonValue = SneLoggingEventCallback.STOP_REASON_SHUTDOWN;
                        break;
                    case SCOREOFF:
                        reasonValue = SneLoggingEventCallback.STOP_REASON_SCOREOFF;
                        break;
                    case SOFTAP_STARTED:
                        reasonValue = SneLoggingEventCallback.STOP_REASON_SOFTAP_STARTED;
                        break;
                    case STASTA_CONCURRENCY:
                        reasonValue = SneLoggingEventCallback.STOP_REASON_STASTA_CONCURRENCY;
                        break;
                    case MLO_CONNECTION:
                        reasonValue = SneLoggingEventCallback.STOP_REASON_MLO_CONNECTION;
                        break;
                    default:
                        reasonValue = SneLoggingEventCallback.STOP_REASON_UNKNOWN;
                }
                try {
                    callback.onStopped(reasonValue);
                } catch (RemoteException ignored) {
                }
            });
        }
    }

    /**
     * Notify stats was updated.
     */
    public void noteLoggingStatsUpdate(@NonNull WifiPredictionData.SneRuntimeStats runtimeStats) {
        ISneLoggingEventCallback callback = mISneLoggingEventCallback;
        if (callback != null) {
            mExecutor.execute(() -> {
                LoggingStats loggingStats = toLoggingStats(runtimeStats);
                try {
                    callback.onStatsUpdated(loggingStats);
                } catch (RemoteException ignored) {
                }
            });
        }
    }

    /**
     * Notify network decision was made.
     */
    public void noteNetworkDecisionMade(boolean wifiUsable,
            @NonNull WifiPredictionData.SneRuntimeStats runtimeStats) {
        ISneNetworkDecisionEventCallback callback = mISneNetworkDecisionEventCallback;
        if (callback != null) {
            mExecutor.execute(() -> {
                LoggingStats loggingStats = toLoggingStats(runtimeStats);
                try {
                    callback.onDecisionMade(wifiUsable, loggingStats);
                } catch (RemoteException ignored) {
                }
            });
        }
    }

    /**
     * Create a {@link LoggingStats} from a {@link WifiPredictionData.SneRuntimeStats}. Most of
     * information is carried but not all.
     */
    @VisibleForTesting
    LoggingStats toLoggingStats(WifiPredictionData.SneRuntimeStats runtimeStats) {
        WifiPredictionData.SneWifiInfo sneWifiInfo = runtimeStats.getWifiInfo();
        WifiPredictionData.SneWifiTrafficStats sneWifiTrafficStats =
                runtimeStats.getWifiTrafficStats();
        WifiPredictionData.SneTcpStats sneTcpStats = runtimeStats.getTcpStats();
        WifiPredictionData.SneSensorData sneSensorData = runtimeStats.getSensorData();
        WifiPredictionData.SneInferenceResult sneInferenceResult =
                runtimeStats.getInferenceResult();
        // Wifi
        LoggingStats.Wifi wifi = LoggingStats.Wifi.builder()
                .linkSpeed(sneWifiInfo.getLinkSpeed())
                .frequency(sneWifiInfo.getFrequency())
                .channelWidth(toChannelWidthString(sneWifiInfo.getChannelWidth()))
                .rssi(sneWifiInfo.getRssi())
                .score(sneWifiInfo.getScore())
                .txBad(sneWifiTrafficStats.getTxBad())
                .txRetries(sneWifiTrafficStats.getTxRetries())
                .txSuccess(sneWifiTrafficStats.getTxSuccess())
                .rxSuccess(sneWifiTrafficStats.getRxSuccess())
                .txTime(sneWifiInfo.getTxTime())
                .rxTime(sneWifiInfo.getRxTime())
                .onTime(sneWifiInfo.getOnTime())
                .ccaBusyTime(sneWifiInfo.getCcaBusyTime())
                .contentionAverageTime(sneWifiInfo.getContentionAverageTime())
                .contentionNumOfSamples(sneWifiInfo.getContentionNumOfSamples())
                .numOfTxTriesInDriver(sneWifiTrafficStats.getNumOfTxTriesInDriver())
                .integralUsedDescriptorInDriver(
                        sneWifiTrafficStats.getIntegralUsedDescriptorInDriver())
                .wifiGeneration(sneWifiInfo.getWifiGeneration())
                .txPackets(sneWifiTrafficStats.getTxPkt())
                .rxPackets(sneWifiTrafficStats.getRxPkt())
                .build();

        // TcpProtocol
        LoggingStats.TcpProtocol tcpProtocol = LoggingStats.TcpProtocol.builder()
                .tcpLossUndo(sneTcpStats.getTcpLossUndo())
                .tcpLossFailures(sneTcpStats.getTcpLossFailures())
                .tcpLostRetransmit(sneTcpStats.getTcpLostRetransmit())
                .tcpRetransFail(sneTcpStats.getTcpRetransFail())
                .tcpTimeouts(sneTcpStats.getTcpTimeouts())
                .build();

        // Sensor
        LoggingStats.Sensor sensor = LoggingStats.Sensor.builder()
                .acceleration(sneSensorData.getSensorAcceleration())
                .stepCount(0) // No forward
                .build();

        // Activity
        LoggingStats.Activity activity = LoggingStats.Activity.builder()
                .type(LoggingStats.Activity.TYPE_NO_RESULT) // No forward
                .confidence(0) // No forward
                .isMoving(sneSensorData.getIsMoving())
                .build();

        // InferenceResult
        LoggingStats.InferenceResult inferenceResult = LoggingStats.InferenceResult.builder()
                .primary(sneInferenceResult.getPrimary())
                .secondary(sneInferenceResult.getSecondary())
                .build();

        return LoggingStats.builder()
                .wifi(wifi)
                .tcpProtocol(tcpProtocol)
                .sensor(sensor)
                .activity(activity)
                .inferenceResult(inferenceResult)
                .build();
    }

    @VisibleForTesting
    String toChannelWidthString(int channelWidth) {
        switch (channelWidth) {
            case ScanResult.CHANNEL_WIDTH_20MHZ:
                return "20";
            case ScanResult.CHANNEL_WIDTH_40MHZ:
                return "40";
            case ScanResult.CHANNEL_WIDTH_80MHZ:
                return "80";
            case ScanResult.CHANNEL_WIDTH_160MHZ:
                return "160";
            case ScanResult.CHANNEL_WIDTH_80MHZ_PLUS_MHZ:
                return "170";
            default:
                return "Unknown";
        }
    }
}
