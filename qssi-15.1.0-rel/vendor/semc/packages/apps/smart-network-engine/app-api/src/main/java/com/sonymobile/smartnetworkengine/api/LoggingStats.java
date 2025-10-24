/*
 * Copyright 2020 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.api;

import android.os.Parcel;
import android.os.Parcelable;

import androidx.annotation.IntDef;
import androidx.annotation.NonNull;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

/**
 * A class to hold the statistics Smart Network Engine application collects.
 */
public final class LoggingStats implements Parcelable {

    private Wifi mWifi;

    private TcpProtocol mTcpProtocol;

    private Sensor mSensor;

    private Activity mActivity;

    private InferenceResult mInferenceResult;

    private LoggingStats(Wifi wifi, TcpProtocol tcpProtocol, Sensor sensor, Activity activity,
            InferenceResult inferenceResult) {
        mWifi = wifi;
        mTcpProtocol = tcpProtocol;
        mSensor = sensor;
        mActivity = activity;
        mInferenceResult = inferenceResult;
    }

    private LoggingStats() {
    }

    public Wifi getWifi() {
        return mWifi;
    }

    public TcpProtocol getTcpProtocol() {
        return mTcpProtocol;
    }

    public Sensor getSensor() {
        return mSensor;
    }

    public Activity getActivity() {
        return mActivity;
    }

    public InferenceResult getInferenceResult() {
        return mInferenceResult;
    }

    @NonNull
    @Override
    public String toString() {
        return "LoggingStats(wifi=" + getWifi() + ", tcpProtocol=" + getTcpProtocol()
                + ", sensor=" + getSensor() + ", activity=" + getActivity()
                + ", inferenceResult=" + getInferenceResult() + ")";
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeParcelable(mWifi, flags);
        dest.writeParcelable(mTcpProtocol, flags);
        dest.writeParcelable(mSensor, flags);
        dest.writeParcelable(mActivity, flags);
        dest.writeParcelable(mInferenceResult, flags);
    }

    public static final Creator<LoggingStats> CREATOR = new Creator<LoggingStats>() {
        @Override
        public LoggingStats createFromParcel(Parcel in) {
            LoggingStats loggingStats = new LoggingStats();
            loggingStats.mWifi = in.readParcelable(Wifi.class.getClassLoader());
            loggingStats.mTcpProtocol = in.readParcelable(TcpProtocol.class.getClassLoader());
            loggingStats.mSensor = in.readParcelable(Sensor.class.getClassLoader());
            loggingStats.mActivity = in.readParcelable(Activity.class.getClassLoader());
            loggingStats.mInferenceResult = in.readParcelable(
                    InferenceResult.class.getClassLoader());
            return loggingStats;
        }

        @Override
        public LoggingStats[] newArray(int size) {
            return new LoggingStats[size];
        }
    };

    /**
     * Return a builder instance.
     */
    public static Builder builder() {
        return new Builder();
    }

    /**
     * A builder class to construct {@link LoggingStats} instance.
     */
    public static class Builder {

        private Wifi mWifi;

        private TcpProtocol mTcpProtocol;

        private Sensor mSensor;

        private Activity mActivity;

        private InferenceResult mInferenceResult;

        public Builder wifi(Wifi wifi) {
            mWifi = wifi;
            return this;
        }

        public Builder tcpProtocol(TcpProtocol tcpProtocol) {
            mTcpProtocol = tcpProtocol;
            return this;
        }

        public Builder sensor(Sensor sensor) {
            mSensor = sensor;
            return this;
        }

        public Builder activity(Activity activity) {
            mActivity = activity;
            return this;
        }

        public Builder inferenceResult(InferenceResult inferenceResult) {
            mInferenceResult = inferenceResult;
            return this;
        }

        public LoggingStats build() {
            return new LoggingStats(mWifi, mTcpProtocol, mSensor, mActivity, mInferenceResult);
        }
    }

    public static class Wifi implements Parcelable {

        private int mLinkSpeed;

        private int mFrequency;

        private String mChannelWidth;

        private int mRssi;

        private int mScore;

        private long mTxBad;

        private long mTxRetries;

        private long mTxSuccess;

        private long mRxSuccess;

        private long mTxTime;

        private long mRxTime;

        private long mOnTime;

        private long mCcaBusyTime;

        private long mContentionAverageTime;

        private long mContentionNumOfSamples;

        private long mNumOfTxTriesInDriver;

        private int mIntegralUsedDescriptorInDriver;

        private int mWifiGeneration;

        private long mIpLinkVerifierResult;

        /** The number of TX packets (diff value & from TrafficStats) */
        private long mTxPackets;

        /** The number of RX packets (diff value & from TrafficStats) */
        private long mRxPackets;

        private Wifi(int linkSpeed, int frequency, String channelWidth, int rssi, int score,
                long txBad, long txRetries, long txSuccess, long rxSuccess, long txTime,
                long rxTime, long onTime, long ccaBusyTime, long contentionAverageTime,
                long contentionNumOfSamples, long numOfTxTriesInDriver,
                int integralUsedDescriptorInDriver, int wifiGeneration, long ipLinkVerifierResult,
                long txPackets, long rxPackets) {
            mLinkSpeed = linkSpeed;
            mFrequency = frequency;
            mChannelWidth = channelWidth;
            mRssi = rssi;
            mScore = score;
            mTxBad = txBad;
            mTxRetries = txRetries;
            mTxSuccess = txSuccess;
            mRxSuccess = rxSuccess;
            mTxTime = txTime;
            mRxTime = rxTime;
            mOnTime = onTime;
            mCcaBusyTime = ccaBusyTime;
            mContentionAverageTime = contentionAverageTime;
            mContentionNumOfSamples = contentionNumOfSamples;
            mNumOfTxTriesInDriver = numOfTxTriesInDriver;
            mIntegralUsedDescriptorInDriver = integralUsedDescriptorInDriver;
            mWifiGeneration = wifiGeneration;
            mIpLinkVerifierResult = ipLinkVerifierResult;
            mTxPackets = txPackets;
            mRxPackets = rxPackets;
        }

        private Wifi() {
        }

        public int getLinkSpeed() {
            return mLinkSpeed;
        }

        public int getFrequency() {
            return mFrequency;
        }

        public String getChannelWidth() {
            return mChannelWidth;
        }

        public int getRssi() {
            return mRssi;
        }

        public int getScore() {
            return mScore;
        }

        public long getTxBad() {
            return mTxBad;
        }

        public long getTxRetries() {
            return mTxRetries;
        }

        public long getTxSuccess() {
            return mTxSuccess;
        }

        public long getRxSuccess() {
            return mRxSuccess;
        }

        public long getTxTime() {
            return mTxTime;
        }

        public long getRxTime() {
            return mRxTime;
        }

        public long getOnTime() {
            return mOnTime;
        }

        public long getCcaBusyTime() {
            return mCcaBusyTime;
        }

        public long getContentionAverageTime() {
            return mContentionAverageTime;
        }

        public long getContentionNumOfSamples() {
            return mContentionNumOfSamples;
        }

        public long getNumOfTxTriesInDriver() {
            return mNumOfTxTriesInDriver;
        }

        public int getIntegralUsedDescriptorInDriver() {
            return mIntegralUsedDescriptorInDriver;
        }

        public int getWifiGeneration() {
            return mWifiGeneration;
        }

        public long getIpLinkVerifierResult() {
            return mIpLinkVerifierResult;
        }

        public long getTxPackets() {
            return mTxPackets;
        }

        public long getRxPackets() {
            return mRxPackets;
        }

        @NonNull
        @Override
        public String toString() {
            return "LoggingStats.Wifi(linkSpeed=" + getLinkSpeed() + ", frequency="
                    + getFrequency() + ", channelWidth=" + getChannelWidth() + ", rssi="
                    + getRssi() + ", score=" + getScore() + ", txBad=" + getTxBad()
                    + ", txRetries=" + getTxRetries() + ", txSuccess=" + getTxSuccess()
                    + ", rxSuccess=" + getRxSuccess() + ", txTime=" + getTxTime()
                    + ", rxTime=" + getRxTime() + ", onTime=" + getOnTime()
                    + ", ccaBusyTime=" + getCcaBusyTime() + ", contentionAverageTime="
                    + getContentionAverageTime() + ", contentionNumOfSamples="
                    + getContentionNumOfSamples() + ", numOfTxTriesInDriver="
                    + getNumOfTxTriesInDriver() + ", integralUsedDescriptorInDriver="
                    + getIntegralUsedDescriptorInDriver() + ", wifiGeneration="
                    + getWifiGeneration() + ", ipLinkVerifierResult="
                    + getIpLinkVerifierResult() + ", txPackets=" + getTxPackets()
                    + ", rxPackets=" + getRxPackets() + ")";
        }

        @Override
        public int describeContents() {
            return 0;
        }

        @Override
        public void writeToParcel(Parcel dest, int flags) {
            dest.writeInt(mLinkSpeed);
            dest.writeInt(mFrequency);
            dest.writeString(mChannelWidth);
            dest.writeInt(mRssi);
            dest.writeInt(mScore);
            dest.writeLong(mTxBad);
            dest.writeLong(mTxRetries);
            dest.writeLong(mTxSuccess);
            dest.writeLong(mRxSuccess);
            dest.writeLong(mTxTime);
            dest.writeLong(mRxTime);
            dest.writeLong(mOnTime);
            dest.writeLong(mCcaBusyTime);
            dest.writeLong(mContentionAverageTime);
            dest.writeLong(mContentionNumOfSamples);
            dest.writeLong(mNumOfTxTriesInDriver);
            dest.writeInt(mIntegralUsedDescriptorInDriver);
            dest.writeInt(mWifiGeneration);
            dest.writeLong(mIpLinkVerifierResult);
            dest.writeLong(mTxPackets);
            dest.writeLong(mRxPackets);
        }

        public static final Creator<Wifi> CREATOR = new Creator<Wifi>() {
            @Override
            public Wifi createFromParcel(Parcel in) {
                Wifi wifi = new Wifi();
                wifi.mLinkSpeed = in.readInt();
                wifi.mFrequency = in.readInt();
                wifi.mChannelWidth = in.readString();
                wifi.mRssi = in.readInt();
                wifi.mScore = in.readInt();
                wifi.mTxBad = in.readLong();
                wifi.mTxRetries = in.readLong();
                wifi.mTxSuccess = in.readLong();
                wifi.mRxSuccess = in.readLong();
                wifi.mTxTime = in.readLong();
                wifi.mRxTime = in.readLong();
                wifi.mOnTime = in.readLong();
                wifi.mCcaBusyTime = in.readLong();
                wifi.mContentionAverageTime = in.readLong();
                wifi.mContentionNumOfSamples = in.readLong();
                wifi.mNumOfTxTriesInDriver = in.readLong();
                wifi.mIntegralUsedDescriptorInDriver = in.readInt();
                wifi.mWifiGeneration = in.readInt();
                wifi.mIpLinkVerifierResult = in.readLong();
                wifi.mTxPackets = in.readLong();
                wifi.mRxPackets = in.readLong();
                return wifi;
            }

            @Override
            public Wifi[] newArray(int size) {
                return new Wifi[size];
            }
        };

        /**
         * Return a builder instance.
         */
        public static Builder builder() {
            return new Builder();
        }

        /**
         * A builder class to construct {@link Wifi} instance.
         */
        public static class Builder {

            private int mLinkSpeed;

            private int mFrequency;

            private String mChannelWidth;

            private int mRssi;

            private int mScore;

            private long mTxBad;

            private long mTxRetries;

            private long mTxSuccess;

            private long mRxSuccess;

            private long mTxTime;

            private long mRxTime;

            private long mOnTime;

            private long mCcaBusyTime;

            private long mContentionAverageTime;

            private long mContentionNumOfSamples;

            private long mNumOfTxTriesInDriver;

            private int mIntegralUsedDescriptorInDriver;

            private int mWifiGeneration;

            private long mIpLinkVerifierResult;

            private long mTxPackets;

            private long mRxPackets;

            public Builder linkSpeed(int linkSpeed) {
                mLinkSpeed = linkSpeed;
                return this;
            }

            public Builder frequency(int frequency) {
                mFrequency = frequency;
                return this;
            }

            public Builder channelWidth(String channelWidth) {
                mChannelWidth = channelWidth;
                return this;
            }

            public Builder rssi(int rssi) {
                mRssi = rssi;
                return this;
            }

            public Builder score(int score) {
                mScore = score;
                return this;
            }

            public Builder txBad(long txBad) {
                mTxBad = txBad;
                return this;
            }

            public Builder txRetries(long txRetries) {
                mTxRetries = txRetries;
                return this;
            }

            public Builder txSuccess(long txSuccess) {
                mTxSuccess = txSuccess;
                return this;
            }

            public Builder rxSuccess(long rxSuccess) {
                mRxSuccess = rxSuccess;
                return this;
            }

            public Builder txTime(long txTime) {
                mTxTime = txTime;
                return this;
            }

            public Builder rxTime(long rxTime) {
                mRxTime = rxTime;
                return this;
            }

            public Builder onTime(long onTime) {
                mOnTime = onTime;
                return this;
            }

            public Builder ccaBusyTime(long ccaBusyTime) {
                mCcaBusyTime = ccaBusyTime;
                return this;
            }

            public Builder contentionAverageTime(long contentionAverageTime) {
                mContentionAverageTime = contentionAverageTime;
                return this;
            }

            public Builder contentionNumOfSamples(long contentionNumOfSamples) {
                mContentionNumOfSamples = contentionNumOfSamples;
                return this;
            }

            public Builder numOfTxTriesInDriver(long numOfTxTriesInDriver) {
                mNumOfTxTriesInDriver = numOfTxTriesInDriver;
                return this;
            }

            public Builder integralUsedDescriptorInDriver(
                    int integralUsedDescriptorInDriver) {
                mIntegralUsedDescriptorInDriver = integralUsedDescriptorInDriver;
                return this;
            }

            public Builder wifiGeneration(int wifiGeneration) {
                mWifiGeneration = wifiGeneration;
                return this;
            }

            public Builder ipLinkVerifierResult(long ipLinkVerifierResult) {
                mIpLinkVerifierResult = ipLinkVerifierResult;
                return this;
            }

            public Builder txPackets(long txPackets) {
                mTxPackets = txPackets;
                return this;
            }

            public Builder rxPackets(long rxPackets) {
                mRxPackets = rxPackets;
                return this;
            }

            public Wifi build() {
                return new Wifi(mLinkSpeed, mFrequency, mChannelWidth, mRssi, mScore, mTxBad,
                        mTxRetries, mTxSuccess, mRxSuccess, mTxTime, mRxTime, mOnTime, mCcaBusyTime,
                        mContentionAverageTime, mContentionNumOfSamples, mNumOfTxTriesInDriver,
                        mIntegralUsedDescriptorInDriver, mWifiGeneration, mIpLinkVerifierResult,
                        mTxPackets,
                        mRxPackets);
            }
        }
    }

    // Note this metrics is calculated from all network interfaces (not only wifi).
    public static class TcpProtocol implements Parcelable {

        /** TCPLossUndo (diff value) */
        private int mTcpLossUndo;

        /** TCPLossFailures (diff value) */
        private int mTcpLossFailures;

        /** TCPLostRetransmit (diff value) */
        private int mTcpLostRetransmit;

        /** TCPRetransFail (diff value) */
        private int mTcpRetransFail;

        /** TCPTimeouts (diff value) */
        private int mTcpTimeouts;

        private TcpProtocol(int tcpLossUndo, int tcpLossFailures, int tcpLostRetransmit,
                int tcpRetransFail, int tcpTimeouts) {
            mTcpLossUndo = tcpLossUndo;
            mTcpLossFailures = tcpLossFailures;
            mTcpLostRetransmit = tcpLostRetransmit;
            mTcpRetransFail = tcpRetransFail;
            mTcpTimeouts = tcpTimeouts;
        }

        private TcpProtocol() {
        }

        public int getTcpLossUndo() {
            return mTcpLossUndo;
        }

        public int getTcpLossFailures() {
            return mTcpLossFailures;
        }

        public int getTcpLostRetransmit() {
            return mTcpLostRetransmit;
        }

        public int getTcpRetransFail() {
            return mTcpRetransFail;
        }

        public int getTcpTimeouts() {
            return mTcpTimeouts;
        }

        @NonNull
        @Override
        public String toString() {
            return "LoggingStats.TcpProtocol(tcpLossUndo=" + getTcpLossUndo()
                    + ", tcpLossFailures=" + getTcpLossFailures() + ", tcpLostRetransmit="
                    + getTcpLostRetransmit() + ", tcpRetransFail=" + getTcpRetransFail()
                    + ", tcpTimeouts=" + getTcpTimeouts() + ")";
        }

        @Override
        public int describeContents() {
            return 0;
        }

        @Override
        public void writeToParcel(Parcel dest, int flags) {
            dest.writeInt(mTcpLossUndo);
            dest.writeInt(mTcpLossFailures);
            dest.writeInt(mTcpLostRetransmit);
            dest.writeInt(mTcpRetransFail);
            dest.writeInt(mTcpTimeouts);
        }

        public static final Creator<TcpProtocol> CREATOR = new Creator<TcpProtocol>() {
            @Override
            public TcpProtocol createFromParcel(Parcel in) {
                TcpProtocol tcpProtocol = new TcpProtocol();
                tcpProtocol.mTcpLossUndo = in.readInt();
                tcpProtocol.mTcpLossFailures = in.readInt();
                tcpProtocol.mTcpLostRetransmit = in.readInt();
                tcpProtocol.mTcpRetransFail = in.readInt();
                tcpProtocol.mTcpTimeouts = in.readInt();
                return tcpProtocol;
            }

            @Override
            public TcpProtocol[] newArray(int size) {
                return new TcpProtocol[size];
            }
        };

        /**
         * Return a builder instance.
         */
        public static Builder builder() {
            return new Builder();
        }

        /**
         * A builder class to construct {@link TcpProtocol} instance.
         */
        public static class Builder {

            private int mTcpLossUndo;

            private int mTcpLossFailures;

            private int mTcpLostRetransmit;

            private int mTcpRetransFail;

            private int mTcpTimeouts;

            public Builder tcpLossUndo(int tcpLossUndo) {
                mTcpLossUndo = tcpLossUndo;
                return this;
            }

            public Builder tcpLossFailures(int tcpLossFailures) {
                mTcpLossFailures = tcpLossFailures;
                return this;
            }

            public Builder tcpLostRetransmit(int tcpLostRetransmit) {
                mTcpLostRetransmit = tcpLostRetransmit;
                return this;
            }

            public Builder tcpRetransFail(int tcpRetransFail) {
                mTcpRetransFail = tcpRetransFail;
                return this;
            }

            public Builder tcpTimeouts(int tcpTimeouts) {
                mTcpTimeouts = tcpTimeouts;
                return this;
            }

            public TcpProtocol build() {
                return new TcpProtocol(mTcpLossUndo, mTcpLossFailures, mTcpLostRetransmit,
                        mTcpRetransFail, mTcpTimeouts);
            }
        }
    }

    public static class Sensor implements Parcelable {

        /** An acceleration value (cf. SensorCollector) */
        private float mAcceleration;

        /** A step count (diff value) */
        private int mStepCount;

        private Sensor(float acceleration, int stepCount) {
            mAcceleration = acceleration;
            mStepCount = stepCount;
        }

        private Sensor() {
        }

        public float getAcceleration() {
            return mAcceleration;
        }

        @Deprecated
        public int getStepCount() {
            return mStepCount;
        }

        @NonNull
        @Override
        public String toString() {
            return "LoggingStats.Sensor(acceleration=" + getAcceleration() + ", stepCount="
                    + getStepCount() + ")";
        }

        @Override
        public int describeContents() {
            return 0;
        }

        @Override
        public void writeToParcel(Parcel dest, int flags) {
            dest.writeFloat(mAcceleration);
            dest.writeInt(mStepCount);
        }

        public static final Creator<Sensor> CREATOR = new Creator<Sensor>() {
            @Override
            public Sensor createFromParcel(Parcel in) {
                Sensor sensor = new Sensor();
                sensor.mAcceleration = in.readFloat();
                sensor.mStepCount = in.readInt();
                return sensor;
            }

            @Override
            public Sensor[] newArray(int size) {
                return new Sensor[size];
            }
        };

        /**
         * Return a builder instance.
         */
        public static Builder builder() {
            return new Builder();
        }

        /**
         * A builder class to construct {@link Sensor} instance.
         */
        public static class Builder {

            private float mAcceleration;

            private int mStepCount;

            public Builder acceleration(float acceleration) {
                mAcceleration = acceleration;
                return this;
            }

            @Deprecated
            public Builder stepCount(int stepCount) {
                mStepCount = stepCount;
                return this;
            }

            public Sensor build() {
                return new Sensor(mAcceleration, mStepCount);
            }
        }
    }

    public static class Activity implements Parcelable {

        @Retention(RetentionPolicy.SOURCE)
        @IntDef({TYPE_IN_VEHICLE,
                TYPE_ON_BICYCLE,
                TYPE_ON_FOOT,
                TYPE_STILL,
                TYPE_UNKNOWN,
                TYPE_TILTING,
                TYPE_WALKING,
                TYPE_RUNNING,
                TYPE_NO_RESULT})
        public @interface Type {
        }

        // Constants for detected activity
        public static final int TYPE_IN_VEHICLE = 0;
        public static final int TYPE_ON_BICYCLE = 1;
        public static final int TYPE_ON_FOOT = 2;
        public static final int TYPE_STILL = 3;
        public static final int TYPE_UNKNOWN = 4;
        public static final int TYPE_TILTING = 5;
        public static final int TYPE_WALKING = 7;
        public static final int TYPE_RUNNING = 8;
        public static final int TYPE_NO_RESULT = -1;

        /** A detected activity (from Activity Recognition API) */
        private int mType = TYPE_NO_RESULT;

        /** A confidence of detected activity (from Activity Recognition API) */
        private int mConfidence;

        /** Whether device is moving or not (from SNE Moving detector) */
        private boolean mIsMoving;

        private Activity(@Type int type, int confidence, boolean isMoving) {
            mType = type;
            mConfidence = confidence;
            mIsMoving = isMoving;
        }

        private Activity() {
        }

        @Deprecated
        @Type
        public int getType() {
            return mType;
        }

        @Deprecated
        public int getConfidence() {
            return mConfidence;
        }

        public boolean isMoving() {
            return mIsMoving;
        }

        @NonNull
        @Override
        public String toString() {
            return "LoggingStats.Activity(type=" + getType() + ", confidence="
                    + getConfidence() + ", isMoving=" + isMoving() + ")";
        }

        @Override
        public int describeContents() {
            return 0;
        }

        @Override
        public void writeToParcel(Parcel dest, int flags) {
            dest.writeInt(mType);
            dest.writeInt(mConfidence);
            dest.writeInt(mIsMoving ? 1 : 0);
        }

        public static final Creator<Activity> CREATOR = new Creator<Activity>() {
            @Override
            public Activity createFromParcel(Parcel in) {
                Activity activity = new Activity();
                activity.mType = in.readInt();
                activity.mConfidence = in.readInt();
                activity.mIsMoving = in.readInt() == 1;
                return activity;
            }

            @Override
            public Activity[] newArray(int size) {
                return new Activity[size];
            }
        };

        /**
         * Return a builder instance.
         */
        public static Builder builder() {
            return new Builder();
        }

        /**
         * A builder class to construct {@link Activity} instance.
         */
        public static class Builder {

            private int mType = TYPE_NO_RESULT;

            private int mConfidence;

            private boolean mIsMoving;

            @Deprecated
            public Builder type(@Type int type) {
                mType = type;
                return this;
            }

            @Deprecated
            public Builder confidence(int confidence) {
                mConfidence = confidence;
                return this;
            }

            public Builder isMoving(boolean isMoving) {
                mIsMoving = isMoving;
                return this;
            }

            public Activity build() {
                return new Activity(mType, mConfidence, mIsMoving);
            }
        }
    }

    public static class InferenceResult implements Parcelable {

        /** An inference result from primary engine */
        private float mPrimary;

        /** An inference result from secondary engine */
        private float mSecondary;

        private InferenceResult(float primary, float secondary) {
            mPrimary = primary;
            mSecondary = secondary;
        }

        private InferenceResult() {
        }

        public float getPrimary() {
            return mPrimary;
        }

        public float getSecondary() {
            return mSecondary;
        }

        @NonNull
        @Override
        public String toString() {
            return "LoggingStats.InferenceResult(primary=" + getPrimary() + ", secondary="
                    + getSecondary() + ")";
        }

        @Override
        public int describeContents() {
            return 0;
        }

        @Override
        public void writeToParcel(Parcel dest, int flags) {
            dest.writeFloat(mPrimary);
            dest.writeFloat(mSecondary);
        }

        public static final Creator<InferenceResult> CREATOR = new Creator<InferenceResult>() {
            @Override
            public InferenceResult createFromParcel(Parcel in) {
                InferenceResult inferenceResult = new InferenceResult();
                inferenceResult.mPrimary = in.readFloat();
                inferenceResult.mSecondary = in.readFloat();
                return inferenceResult;
            }

            @Override
            public InferenceResult[] newArray(int size) {
                return new InferenceResult[size];
            }
        };

        /**
         * Return a builder instance.
         */
        public static Builder builder() {
            return new Builder();
        }

        /**
         * A builder class to construct {@link InferenceResult} instance.
         */
        public static class Builder {

            private float mPrimary;

            private float mSecondary;

            public Builder primary(float primary) {
                mPrimary = primary;
                return this;
            }

            public Builder secondary(float secondary) {
                mSecondary = secondary;
                return this;
            }

            public InferenceResult build() {
                return new InferenceResult(mPrimary, mSecondary);
            }
        }
    }
}
