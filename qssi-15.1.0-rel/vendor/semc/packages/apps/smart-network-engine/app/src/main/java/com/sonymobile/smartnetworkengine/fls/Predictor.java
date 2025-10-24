/*
 * Copyright 2021, 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.sonymobile.smartnetworkengine.fls.data.FLTrainingDataAccessor.DataSet;

import java.util.List;
import java.util.function.Function;

/**
 * A prediction interface for the clients that utilizes the Federated-Learning system
 */
public interface Predictor {

    /**
     * Perform prediction with specified One-dimensional features and return result.
     */
    @NonNull
    PredictionResult predict1d(@NonNull List<Float> features, @NonNull String groupLabel);

    /**
     * Perform prediction with specified Two-dimensional features and return result.
     */
    @NonNull
    PredictionResult predict2d(@NonNull List<List<Float>> features, @NonNull String groupLabel);

    /**
     * Reset prediction state. Actual behavior depends on the algorithm used by the module. For
     * instance, if Recurrent Neural Network is used, this method may clear recurrent inputs.
     * <p/>
     * This must be called every time when prediction session is ended. This is needed for the
     * Federated-Learning system to be able to run pending operations such as model update.
     */
    void reset();

    /**
     * Adds specified data for training and evaluation.
     *
     * @param result the prediction result returned from {@link #predict(List, String)} call. The
     *               features and group label passed at that time will be added as training data
     *               with the supplied label.
     * @param label  the label for the data associated with the supplied {@link PredictionResult}.
     */
    void addTrainingData(@NonNull PredictionResult result, float label);

    /**
     * Returns average label value (not 'label average') of training data.
     */
    float getAverageOfLabel();

    /**
     * Set modifier method to modify DataSet for deploy, training, evaluation and calibration.
     * If null is set to modifier, the DataSet is not modified.
     */
    void setTrainingDataModifier(@Nullable Function<DataSet, DataSet> modifier);

    class PredictionResult {

        @Nullable
        private final Float mScore;

        private final float mScoreThreshold;

        private final boolean mScoreUsable;

        @Nullable
        private final String mScoreUnusableReason;

        @Nullable
        private final String mModelVersion;

        @Nullable
        private final Object mExtraData;

        private PredictionResult(@Nullable Float score, float scoreThreshold, boolean scoreUsable,
                @Nullable String scoreUnusableReason, @Nullable String modelVersion,
                @Nullable Object extraData) {
            mScore = score;
            mScoreThreshold = scoreThreshold;
            mScoreUsable = scoreUsable;
            mScoreUnusableReason = scoreUnusableReason;
            mModelVersion = modelVersion;
            mExtraData = extraData;
        }

        /**
         * Return the prediction result. {@link Float#NaN} is returned if {@link #isScored()}
         * returns false.
         */
        public float getScore() {
            return mScore != null ? mScore : Float.NaN;
        }

        /**
         * Indicate whether prediction has been performed and {@link #getScore()} can return result.
         */
        public boolean isScored() {
            return mScore != null;
        }

        /**
         * Indicate whether the prediction result is above the threshold.
         */
        public boolean aboveScoreThreshold() {
            return isScored() && getScore() > mScoreThreshold;
        }

        /**
         * Indicate whether client can utilize {@link #getScore()} result. If false is returned, it
         * should only be used for e.g. IDD data collection.
         */
        public boolean isScoreUsable() {
            return mScoreUsable;
        }

        @Nullable
        public String getScoreUnusableReason() {
            return mScoreUnusableReason;
        }

        /**
         * Return current model version. null may be returned if {@link #isScored()} is false.
         */
        @Nullable
        public String getModelVersion() {
            return mModelVersion;
        }

        @Nullable
        Object getExtraData() {
            return mExtraData;
        }

        @NonNull
        @Override
        public String toString() {
            return "PredictionResult(score=" + mScore + ", isScored=" + isScored()
                    + ", scoreThreshold=" + mScoreThreshold + ", aboveScoreThreshold="
                    + aboveScoreThreshold() + ", scoreUsable=" + mScoreUsable
                    + ", scoreUnusableReason='" + mScoreUnusableReason + ", modelVersion='"
                    + mModelVersion + "')";
        }

        /**
         * Return a builder instance.
         */
        public static Builder builder() {
            return new Builder();
        }

        /**
         * A builder class to construct {@link PredictionResult} instance.
         */
        public static class Builder {

            private Float mScore = null;

            private float mScoreThreshold;

            private boolean mScoreUsable = false;

            private String mScoreUnusableReason = null;

            private String mModelVersion = null;

            private Object mExtraData = null;

            public Builder score(float score, float scoreThreshold) {
                mScore = score;
                mScoreThreshold = scoreThreshold;
                return this;
            }

            public Builder scoreUsable(boolean scoreUsable) {
                mScoreUsable = scoreUsable;
                return this;
            }

            public Builder scoreUnusableReason(String scoreUnusableReason) {
                mScoreUnusableReason = scoreUnusableReason;
                return this;
            }

            public Builder modelVersion(String modelVersion) {
                mModelVersion = modelVersion;
                return this;
            }

            public Builder extraData(Object extraData) {
                mExtraData = extraData;
                return this;
            }

            public PredictionResult build() {
                return new PredictionResult(mScore, mScoreThreshold, mScoreUsable,
                        mScoreUnusableReason, mModelVersion, mExtraData);
            }
        }
    }
}
