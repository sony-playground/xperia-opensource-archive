/*
 * Copyright 2019 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.connected.logger.collector;

import static android.hardware.Sensor.TYPE_LINEAR_ACCELERATION;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.sonymobile.smartnetworkengine.util.Log;

/**
 * Collect following sensor data and provide getters to access it.
 * - Acceleration from motion sensor - i.e. L2 norm of 3-axis acceleration
 */
public class SensorCollector {

    private static final String TAG = SensorCollector.class.getSimpleName();

    // These micro seconds are passed to Google Play Services API, which are affected to sensor
    // latency and power usage. For consideration of less power usage, they are decided.
    private static final int MAX_REPORT_LATENCY_US = 3_000_000;
    private static final int SAMPLING_PERIOD_US = 1_000_000;

    private final SensorManager mSensorManager;

    @Nullable
    private final Sensor mAcceleration;

    private boolean mStarted;

    private float mAccelerationSum;
    private int mAccelerationUpdateCount;

    private final SensorEventListener mListener = new SensorEventListener() {
        @Override
        public void onSensorChanged(SensorEvent sensorEvent) {
            synchronized (SensorCollector.this) {
                if (!mStarted) {
                    return;
                }
                int sensorType = sensorEvent.sensor.getType();
                if (sensorType == TYPE_LINEAR_ACCELERATION) {
                    float acceleration = l2Norm(sensorEvent.values[0], sensorEvent.values[1],
                            sensorEvent.values[2]);
                    // Track acceleration sum and count of update to calculate average later.
                    mAccelerationSum += acceleration;
                    mAccelerationUpdateCount++;
                }
            }
        }

        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
            Log.v(TAG, "onAccuracyChanged:" + sensor + ", accuracy:" + accuracy);
        }
    };

    public SensorCollector(@NonNull Context context) {
        mSensorManager = (SensorManager) context.getSystemService(Context.SENSOR_SERVICE);
        mAcceleration = mSensorManager.getDefaultSensor(TYPE_LINEAR_ACCELERATION, false);
    }

    /**
     * Start receiving sensor update by registering listener to SensorManager.
     */
    public synchronized void start() {
        if (mStarted) {
            throw new IllegalStateException("already started");
        }

        if (mAcceleration == null) {
            Log.e(TAG, "Failed to acquire sensor - (acceleration)");
            return;
        }

        if (!mSensorManager.registerListener(mListener, mAcceleration,
                SAMPLING_PERIOD_US, MAX_REPORT_LATENCY_US)) {
            Log.e(TAG, "Failed to register listener for acceleration.");
        }

        mStarted = true;
    }

    /**
     * Stop receiving sensor update by unregistering listener from SensorManger.
     */
    public synchronized void stop() {
        if (mStarted) {
            Log.v(TAG, "Unregister listener for sensor.");
            mSensorManager.unregisterListener(mListener);
            mAccelerationSum = 0.0f;
            mAccelerationUpdateCount = 0;
            mStarted = false;
        }
    }

    /**
     * Return average acceleration since last call.
     *
     * NOTE that this API call resets internal stats used to calculate average.
     */
    public synchronized float getAcceleration() {
        // If there is no update, return 0. This case could not occur normally.
        if (mAccelerationUpdateCount == 0) {
            return 0.0f;
        }

        float average = mAccelerationSum / mAccelerationUpdateCount;

        // Reset internal variables used for average calculation.
        mAccelerationSum = 0.0f;
        mAccelerationUpdateCount = 0;
        return average;
    }

    private float l2Norm(float x, float y, float z) {
        return (float) Math.sqrt((x * x) + (y * y) + (z * z));
    }
}
