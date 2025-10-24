/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls;

import static com.sonymobile.smartnetworkengine.fls.FLPreferenceAccessor.KEY_CLIENT_CONFIG_AS_STRING;

import static java.nio.charset.StandardCharsets.ISO_8859_1;

import android.content.SharedPreferences;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;

import com.google.protobuf.InvalidProtocolBufferException;
import com.sonymobile.smartnetworkengine.Constants;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.AppidSpecificConfig;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.ClientConfig;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.GeneralConfiguration;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.GeneralConfiguration.OperationMode;
import com.sonymobile.smartnetworkengine.util.Log;

// TODO: consider to use not shared_prefs but file as storage
public class FLClientConfigAccessor {

    private static final String TAG = FLClientConfigAccessor.class.getSimpleName();

    @VisibleForTesting
    static final String PRESET_CONFIGURATION_NAME = "Preset configuration";

    private final SharedPreferences mSharedPreferences;

    @Nullable
    private ClientConfig mClientConfig;

    FLClientConfigAccessor(@NonNull SharedPreferences sharedPreferences) {
        mSharedPreferences = sharedPreferences;
    }

    @NonNull
    public synchronized ClientConfig get() {
        // Return cached client config if exist
        if (mClientConfig != null) {
            return mClientConfig;
        }
        try {
            String clientConfigStr = mSharedPreferences.getString(KEY_CLIENT_CONFIG_AS_STRING,
                    null);
            if (clientConfigStr != null) {
                // Return saved client config
                mClientConfig = ClientConfig.parseFrom(clientConfigStr.getBytes(ISO_8859_1));
            } else {
                // Return default client config
                mClientConfig = getDefault();
            }
            return mClientConfig;
        } catch (InvalidProtocolBufferException e) {
            Log.e(TAG, "failed to restore: " + e);
            return getDefault();
        }
    }

    synchronized void clearCache() {
        mClientConfig = null;
    }

    synchronized SharedPreferences.Editor saveToEditor(@NonNull ClientConfig clientConfig) {
        return mSharedPreferences.edit().putString(KEY_CLIENT_CONFIG_AS_STRING,
                new String(clientConfig.toByteArray(), ISO_8859_1));
    }

    /**
     * Return the default client config. This config is used when the device has never
     * downloaded the config from server yet.
     */
    private ClientConfig getDefault() {
        // General configuration
        GeneralConfiguration generalConfiguration = GeneralConfiguration.newBuilder()
                .setOperationMode(OperationMode.SERVER_ACCESS_ONLY)
                .setClientPollingFrequencyMins(4320 /* 3 days */)
                .setUploadablePeriodHours(168 /* 7 days */)
                .build();

        // AppId specific configuration(s)
        AppidSpecificConfig appidSpecificConfigForConnected = AppidSpecificConfig.newBuilder()
                .setAppId(Constants.FLS_APP_ID_CONNECTED) // for connected
                .setInferenceEnabled(false)
                .setInferenceThreshold(Float.MAX_VALUE)
                .setTrainingDataCollectionRatio(100)
                .setMaxNumOfTrainingSession(1)
                .setMaxNumOfTrainingSessionPerBssid(1)
                .setMaxPeriodDaysOfTrainingSession(1 /* 1 day */)
                .setDataCountThreshold(Integer.MAX_VALUE)
                .setPeriodicCalibrationFrequencyDays(0)
                .setPositiveLabelThreshold(1.0f)
                .setPositiveRateThreshold(1.0f)
                .build();

        AppidSpecificConfig appidSpecificConfigForEntry = AppidSpecificConfig.newBuilder()
                .setAppId(Constants.FLS_APP_ID_ENTRY) // for entry
                .setInferenceEnabled(false)
                .setInferenceThreshold(Float.MAX_VALUE)
                .setTrainingDataCollectionRatio(100)
                .setMaxNumOfTrainingSession(1)
                .setMaxNumOfTrainingSessionPerBssid(1)
                .setMaxPeriodDaysOfTrainingSession(1 /* 1 day */)
                .setDataCountThreshold(Integer.MAX_VALUE)
                .setPeriodicCalibrationFrequencyDays(0)
                .setPositiveLabelThreshold(1.0f)
                .setPositiveRateThreshold(1.0f)
                .build();

        // Client config
        return ClientConfig.newBuilder()
                .setConfigurationName(PRESET_CONFIGURATION_NAME)
                .setGeneralConfiguration(generalConfiguration)
                .addAppidSpecificConfigs(appidSpecificConfigForConnected)
                .addAppidSpecificConfigs(appidSpecificConfigForEntry)
                .build();
    }
}
