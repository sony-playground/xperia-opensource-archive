/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.api;

import android.os.Parcel;
import android.os.Parcelable;

import androidx.annotation.NonNull;

/**
 * A class to hold the statistics Smart Network Engine application collects.
 */
public final class WifiStats implements Parcelable {
    private long mSeqNo;

    private int mFrequency;

    private int mRssi;

    private int mTxLinkSpeed;

    private int mRxLinkSpeed;

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

    private int mWifiGeneration;

    private int mChannelWidth;

    private WifiStats(long seqNo, int frequency, int rssi, int txLinkSpeed, int rxLinkSpeed,
            long txBad, long txRetries, long txSuccess, long rxSuccess, long txTime,
            long rxTime, long onTime, long ccaBusyTime, long contentionAverageTime,
            long contentionNumOfSamples, int wifiGeneration, int channelWidth) {
        mSeqNo = seqNo;
        mFrequency = frequency;
        mRssi = rssi;
        mTxLinkSpeed = txLinkSpeed;
        mRxLinkSpeed = rxLinkSpeed;
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
        mWifiGeneration = wifiGeneration;
        mChannelWidth = channelWidth;
    }

    private WifiStats() {
    }

    public long getSeqNo() {
        return mSeqNo;
    }

    public int getFrequency() {
        return mFrequency;
    }

    public int getRssi() {
        return mRssi;
    }

    public int getTxLinkSpeed() {
        return mTxLinkSpeed;
    }

    public int getRxLinkSpeed() {
        return mRxLinkSpeed;
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

    public int getWifiGeneration() {
        return mWifiGeneration;
    }

    public int getChannelWidth() {
        return mChannelWidth;
    }

    @NonNull
    @Override
    public String toString() {
        return "WifiStats(seqNo=" + getSeqNo() + ", frequency=" + getFrequency()
                + ", rssi=" + getRssi()
                + ", txLinkSpeed=" + getTxLinkSpeed() + ", rxLinkSpeed=" + getRxLinkSpeed()
                + ", txBad=" + getTxBad()
                + ", txRetries=" + getTxRetries() + ", txSuccess=" + getTxSuccess()
                + ", rxSuccess=" + getRxSuccess() + ", txTime=" + getTxTime()
                + ", rxTime=" + getRxTime() + ", onTime=" + getOnTime()
                + ", ccaBusyTime=" + getCcaBusyTime() + ", contentionAverageTime="
                + getContentionAverageTime() + ", contentionNumOfSamples="
                + getContentionNumOfSamples() + ", wifiGeneration="
                + getWifiGeneration() + ", channelWidth=" + getChannelWidth() + ")";
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeLong(mSeqNo);
        dest.writeInt(mFrequency);
        dest.writeInt(mRssi);
        dest.writeInt(mTxLinkSpeed);
        dest.writeInt(mRxLinkSpeed);
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
        dest.writeInt(mWifiGeneration);
        dest.writeInt(mChannelWidth);
    }

    public static final Creator<WifiStats> CREATOR = new Creator<WifiStats>() {
        @Override
        public WifiStats createFromParcel(Parcel in) {
            WifiStats wifi = new WifiStats();
            wifi.mSeqNo = in.readLong();
            wifi.mFrequency = in.readInt();
            wifi.mRssi = in.readInt();
            wifi.mTxLinkSpeed = in.readInt();
            wifi.mRxLinkSpeed = in.readInt();
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
            wifi.mWifiGeneration = in.readInt();
            wifi.mChannelWidth = in.readInt();
            return wifi;
        }

        @Override
        public WifiStats[] newArray(int size) {
            return new WifiStats[size];
        }
    };

    /**
     * Return a builder instance.
     */
    public static Builder builder() {
        return new Builder();
    }

    /**
     * A builder class to construct {@link WifiStats} instance.
     */
    public static class Builder {

        private long mSeqNo;

        private int mFrequency;

        private int mRssi;

        private int mTxLinkSpeed;

        private int mRxLinkSpeed;

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

        private int mWifiGeneration;

        private int mChannelWidth;

        public Builder seqNo(long seqNo) {
            mSeqNo = seqNo;
            return this;
        }

        public Builder frequency(int frequency) {
            mFrequency = frequency;
            return this;
        }

        public Builder rssi(int rssi) {
            mRssi = rssi;
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

        public Builder wifiGeneration(int wifiGeneration) {
            mWifiGeneration = wifiGeneration;
            return this;
        }

        public Builder channelWidth(int channelWidth) {
            mChannelWidth = channelWidth;
            return this;
        }

        public WifiStats build() {
            return new WifiStats(mSeqNo, mFrequency, mRssi, mTxLinkSpeed, mRxLinkSpeed, mTxBad,
                    mTxRetries, mTxSuccess, mRxSuccess, mTxTime, mRxTime, mOnTime, mCcaBusyTime,
                    mContentionAverageTime, mContentionNumOfSamples, mWifiGeneration,
                    mChannelWidth);
        }
    }
}