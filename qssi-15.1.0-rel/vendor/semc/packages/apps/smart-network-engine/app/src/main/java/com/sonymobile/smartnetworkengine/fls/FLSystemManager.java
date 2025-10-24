/*
 * Copyright 2022, 2023 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls;

import static com.sonymobile.smartnetworkengine.Constants.FLS_APP_ID_LIST;

import androidx.annotation.NonNull;

import com.sonymobile.smartnetworkengine.Constants;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Objects;

/**
 * This class provides the Federated-Learning system APIs to the clients in order to access its
 * functionality such as {@link Predictor} so that they can easily integrate Federated-Learning into
 * their supported use cases.
 */
public interface FLSystemManager {

    String FEATURE_CONNECTED = Constants.FLS_APP_ID_CONNECTED;

    String FEATURE_ENTRY = Constants.FLS_APP_ID_ENTRY;

    /**
     * Returns {@link Predictor} instance for specified feature.
     */
    @NonNull
    Predictor getPredictor(@NonNull String feature /* appId */);

    /**
     * Enables or disables specified feature. This informs FLS that client requires FLS for the
     * feature.
     */
    void setFeatureEnabled(@NonNull String feature /* appId */, boolean enabled);

    /**
     * Returns current system status.
     */
    @NonNull
    FLSystemStatus getSystemStatus();

    /**
     * Adds a callback for {@link FLSystemStatusListener}. A callback will be invoked only when the
     * status of specified feature is changed.
     */
    void addSystemStatusListener(@NonNull FLSystemStatusListener listener,
            @NonNull String feature /* appId */);

    /**
     * Removes a previously set callback for {@link FLSystemStatusListener}.
     */
    void removeSystemStatusListener(@NonNull FLSystemStatusListener listener);

    /**
     * Return whether training data count exceeds the threshold (dataCountThreshold).
     */
    boolean checkDcCondition(String appId);

    /**
     * Return ratio of positive label (poor quality WiFi) in "training" and "evaluation" data
     * on the device.
     */
    float getPositiveRate(String appId);

    /**
     * This represents overall system status.
     */
    class FLSystemStatus {

        private final boolean mSystemEnabled;

        @NonNull
        private final Map<String, FLFeatureStatus> mFeatureStatusMap;

        private FLSystemStatus(boolean systemEnabled,
                @NonNull Map<String, FLFeatureStatus> featureStatusMap) {
            mSystemEnabled = systemEnabled;
            mFeatureStatusMap = featureStatusMap;
        }

        /**
         * Returns whether FLS is enabled or disabled.
         */
        public boolean isSystemEnabled() {
            return mSystemEnabled;
        }

        /**
         * Returns specified feature status.
         */
        @NonNull
        public FLFeatureStatus getFeatureStatus(@NonNull String feature /* appId */) {
            if (!FLS_APP_ID_LIST.contains(feature)) {
                throw new IllegalArgumentException("invalid feature: " + feature);
            }
            return Objects.requireNonNull(mFeatureStatusMap.get(feature));
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            FLSystemStatus that = (FLSystemStatus) o;
            return mSystemEnabled == that.mSystemEnabled && mFeatureStatusMap.equals(
                    that.mFeatureStatusMap);
        }

        @Override
        public int hashCode() {
            return Objects.hash(mSystemEnabled, mFeatureStatusMap);
        }

        @NonNull
        @Override
        public String toString() {
            return "FLSystemStatus(systemEnabled=" + mSystemEnabled +
                    ", featureStatusMap=" + mFeatureStatusMap + ')';
        }

        /**
         * Return a builder instance.
         */
        public static Builder builder() {
            return new Builder();
        }

        /**
         * Return a builder instance initialized with the current instance.
         */
        public Builder toBuilder() {
            return new Builder()
                    .systemEnabled(mSystemEnabled)
                    .featureStatusMap(mFeatureStatusMap);
        }

        /**
         * A builder class to construct {@link FLSystemStatus} instance.
         */
        public static class Builder {

            private boolean mSystemEnabled = false;

            @NonNull
            private final Map<String, FLFeatureStatus> mFeatureStatusMap;

            public Builder() {
                mFeatureStatusMap = new HashMap<>();
                FLS_APP_ID_LIST.forEach(e -> mFeatureStatusMap.put(e,
                        FLFeatureStatus.builder().feature(e).build()));
            }

            public Builder systemEnabled(boolean enabled) {
                mSystemEnabled = enabled;
                return this;
            }

            public Builder featureStatusMap(
                    @NonNull Map<String, FLFeatureStatus> featureStatusMap) {
                if (!featureStatusMap.keySet().equals(new HashSet<>(FLS_APP_ID_LIST))) {
                    throw new IllegalArgumentException("invalid features: " + featureStatusMap);
                }
                mFeatureStatusMap.putAll(featureStatusMap);
                return this;
            }

            public Builder clearFeatureStatus() {
                mFeatureStatusMap.clear();
                return this;
            }

            public FLSystemStatus build() {
                return new FLSystemStatus(mSystemEnabled, mFeatureStatusMap);
            }
        }
    }

    /**
     * This represents a specific feature status.
     */
    class FLFeatureStatus {

        @NonNull
        private final String mFeature;

        private final boolean mPredictionEnabled;

        private final boolean mDataCollectionSession;

        private FLFeatureStatus(@NonNull String feature /* appId */, boolean predictionEnabled,
                boolean dataCollectionSession) {
            mFeature = feature;
            mPredictionEnabled = predictionEnabled;
            mDataCollectionSession = dataCollectionSession;
        }

        /**
         * Returns feature string.
         */
        @NonNull
        public String getFeature() {
            return mFeature;
        }

        /**
         * Returns whether prediction is enabled or disabled.
         */
        public boolean isPredictionEnabled() {
            return mPredictionEnabled;
        }

        /**
         * Returns whether current session is for data collection.
         */
        public boolean isDataCollectionSession() {
            return mDataCollectionSession;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            FLFeatureStatus that = (FLFeatureStatus) o;
            return mPredictionEnabled == that.mPredictionEnabled
                    && mDataCollectionSession == that.mDataCollectionSession && mFeature.equals(
                    that.mFeature);
        }

        @Override
        public int hashCode() {
            return Objects.hash(mFeature, mPredictionEnabled, mDataCollectionSession);
        }

        @NonNull
        @Override
        public String toString() {
            return "FLFeatureStatus(feature=" + mFeature +
                    ", predictionEnabled=" + mPredictionEnabled +
                    ", dataCollectionSession=" + mDataCollectionSession + ')';
        }

        /**
         * Return a builder instance.
         */
        public static Builder builder() {
            return new Builder();
        }

        /**
         * A builder class to construct {@link FLFeatureStatus} instance.
         */
        public static class Builder {

            private String mFeature;

            private boolean mPredictionEnabled = false;

            private boolean mDataCollectionSession = false;

            public Builder feature(@NonNull String feature /* appId */) {
                if (!FLS_APP_ID_LIST.contains(feature)) {
                    throw new IllegalArgumentException("invalid feature: " + feature);
                }
                mFeature = feature;
                return this;
            }

            public Builder predictionEnabled(boolean enabled) {
                mPredictionEnabled = enabled;
                return this;
            }

            public Builder dataCollectionSession(boolean dataCollectionSession) {
                mDataCollectionSession = dataCollectionSession;
                return this;
            }

            public FLFeatureStatus build() {
                if (mFeature == null) {
                    throw new IllegalStateException("feature is not set");
                }
                return new FLFeatureStatus(mFeature, mPredictionEnabled, mDataCollectionSession);
            }
        }
    }

    interface FLSystemStatusListener {
        /**
         * Called when system status is changed.
         */
        void onConfigurationChanged(@NonNull FLSystemStatus status);
    }
}
