/*
 * Copyright 2018, 2023 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.debug;

import android.app.Service;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PixelFormat;
import android.graphics.Point;
import android.graphics.Typeface;
import android.net.ConnectivityManager;
import android.net.NetworkCapabilities;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.IBinder;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;

import androidx.annotation.NonNull;

import com.sonyericsson.idd.probe.android.smartnetworkengine.WifiPredictionData;
import com.sonymobile.smartnetworkengine.PreferenceAccessor;
import com.sonymobile.smartnetworkengine.R;
import com.sonymobile.smartnetworkengine.SneUtils;
import com.sonymobile.smartnetworkengine.connected.logger.LoggerService;

/**
 * This class outputs logging data in real time.
 */
public class DebugViewService extends Service {

    public static final int DEBUG_VIEW_TYPE_DISABLE = -1;
    public static final int DEBUG_VIEW_TYPE_FULL = 0;
    public static final int DEBUG_VIEW_TYPE_SIMPLE = 1;
    private Context mContext;
    private LoggerService mLoggerService;
    private View mView;
    private WindowManager mWindowManager;
    private Point mDisplaySize;
    private WifiInfo mWifiInfo;
    private ConnectivityManager mConnectivityManager;
    private WifiManager mWifiManager;
    private WifiPredictionData.SneRuntimeStats mSneRuntimeStats;

    private int mLineHeight;

    @Override
    public void onCreate() {
        super.onCreate();
        mContext = this;
        Intent loggerServiceIntent = new Intent();
        loggerServiceIntent.setClass(mContext, LoggerService.class);
        bindService(loggerServiceIntent, mLoggerServiceConnection, 0);
        mWindowManager = (WindowManager) getSystemService(WINDOW_SERVICE);
        mView = new RefreshView(this);
        WindowManager.LayoutParams params = new WindowManager.LayoutParams(
                WindowManager.LayoutParams.MATCH_PARENT,
                WindowManager.LayoutParams.WRAP_CONTENT,
                WindowManager.LayoutParams.TYPE_APPLICATION_OVERLAY,
                WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE |
                        WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE,
                PixelFormat.TRANSLUCENT);
        params.gravity = Gravity.END | Gravity.TOP;
        mWindowManager.addView(mView, params);
        mConnectivityManager = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        mWifiManager = (WifiManager) getSystemService(Context.WIFI_SERVICE);
    }

    @Override
    public void onDestroy() {
        mWindowManager.removeView(mView);
        if (mLoggerService != null) {
            mLoggerService.unregisterStatsUpdateListener(mListener);
        }
        unbindService(mLoggerServiceConnection);
        super.onDestroy();
    }

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    private class RefreshView extends View {
        private Paint mTextPaint;
        private Paint mBackGroundColor;

        public RefreshView(Context context) {
            super(context);
            setPadding(4, 4, 4, 4);
            mDisplaySize = new Point();
            mWindowManager.getDefaultDisplay().getSize(mDisplaySize);
            mLineHeight = getResources().getDimensionPixelSize(R.dimen.text_size);
            mTextPaint = new Paint();
            mTextPaint.setAntiAlias(true);
            mTextPaint.setColor(Color.WHITE);
            mTextPaint.setTextAlign(Paint.Align.RIGHT);
            mTextPaint.setTypeface(Typeface.MONOSPACE);
            mTextPaint.setTextSize(mLineHeight);
            mBackGroundColor = new Paint();
            mBackGroundColor.setColor(Color.BLACK);
            mBackGroundColor.setAlpha(180);
            invalidate();
        }

        @Override
        protected void onDraw(Canvas canvas) {
            super.onDraw(canvas);
            if (!shouldDoDraw()) {
                return;
            }

            final int monitorType;
            switch (PreferenceAccessor.getDebugViewType()) {
                case R.id.RadioButtonDebugViewFull:
                    monitorType = DEBUG_VIEW_TYPE_FULL;
                    break;
                case R.id.RadioButtonDebugViewSimple:
                    monitorType = DEBUG_VIEW_TYPE_SIMPLE;
                    break;
                default:
                    return;
            }

            try {
                final int right = mDisplaySize.x - 20;
                final int top = 0;
                final int height_coefficient = (monitorType == DEBUG_VIEW_TYPE_FULL) ? 36 : 17;
                int idx = 2;

                WifiPredictionData.SneWifiInfo sneWifiInfo = mSneRuntimeStats.getWifiInfo();
                WifiPredictionData.SneWifiTrafficStats sneWifiTrafficStats =
                        mSneRuntimeStats.getWifiTrafficStats();
                WifiPredictionData.SneTcpStats sneTcpStats = mSneRuntimeStats.getTcpStats();
                WifiPredictionData.SneSensorData sneSensorData = mSneRuntimeStats.getSensorData();
                WifiPredictionData.SneInferenceResult sneInferenceResult =
                        mSneRuntimeStats.getInferenceResult();

                // background size
                canvas.drawRect(mDisplaySize.x, top + mLineHeight * height_coefficient,
                        mDisplaySize.x / 2, top + 11, mBackGroundColor);
                // DebugView output
                canvas.drawText(" ", right, top + 10, mTextPaint);
                canvas.drawText("SmartNetworkLogger", right, top
                        + mLineHeight * idx++, mTextPaint);
                canvas.drawText("------------------", right, top
                        + mLineHeight * idx++, mTextPaint);
                String newTypeName = "";
                final NetworkCapabilities nc = mConnectivityManager.getNetworkCapabilities
                        (mConnectivityManager.getActiveNetwork());
                if (nc != null) {
                    if (nc.hasTransport(NetworkCapabilities.TRANSPORT_WIFI)) {
                        newTypeName = "WIFI";
                    } else if (nc.hasTransport(NetworkCapabilities.TRANSPORT_CELLULAR)) {
                        newTypeName = "Cellular";
                    } else {
                        newTypeName = "Unknown";
                    }
                }
                canvas.drawText("Active Network: " + newTypeName,
                        right, top + mLineHeight * idx++, mTextPaint);
                canvas.drawText(
                        "CellNetworkType: " + mSneRuntimeStats.getCellularInfo().getNetworkType(),
                        right, top + mLineHeight * idx++, mTextPaint);
                if (monitorType == DEBUG_VIEW_TYPE_FULL) {
                    canvas.drawText("TxLinkSpeed: " + sneWifiInfo.getLinkSpeed(),
                            right, top + mLineHeight * idx++, mTextPaint);
                    canvas.drawText("RxLinkSpeed: " + sneWifiInfo.getRxLinkSpeed(),
                            right, top + mLineHeight * idx++, mTextPaint);
                }
                canvas.drawText("Freq: " + sneWifiInfo.getFrequency(),
                        right, top + mLineHeight * idx++, mTextPaint);
                canvas.drawText("SSID: " + mWifiInfo.getSSID(),
                        right, top + mLineHeight * idx++, mTextPaint);
                canvas.drawText("BSSID: " + mWifiInfo.getBSSID(),
                        right, top + mLineHeight * idx++, mTextPaint);
                canvas.drawText("RSSI: " + sneWifiInfo.getRssi(),
                        right, top + mLineHeight * idx++, mTextPaint);
                canvas.drawText("Score: " + sneWifiInfo.getScore(),
                        right, top + mLineHeight * idx++, mTextPaint);
                if (monitorType == DEBUG_VIEW_TYPE_FULL) {
                    canvas.drawText("txBad: " + sneWifiTrafficStats.getTxBad(),
                            right, top + mLineHeight * idx++, mTextPaint);
                    canvas.drawText("txRetries: " + sneWifiTrafficStats.getTxRetries(),
                            right, top + mLineHeight * idx++, mTextPaint);
                    canvas.drawText("txSuccess: " + sneWifiTrafficStats.getTxSuccess(),
                            right, top + mLineHeight * idx++, mTextPaint);
                    canvas.drawText("rxSuccess: " + sneWifiTrafficStats.getRxSuccess(),
                            right, top + mLineHeight * idx++, mTextPaint);
                    canvas.drawText("txTime: "
                                    + sneWifiInfo.getTxTime(),
                            right, top + mLineHeight * idx++, mTextPaint);
                    canvas.drawText("rxTime: "
                                    + sneWifiInfo.getRxTime(),
                            right, top + mLineHeight * idx++, mTextPaint);
                    canvas.drawText("onTime: "
                                    + sneWifiInfo.getOnTime(),
                            right, top + mLineHeight * idx++, mTextPaint);
                    canvas.drawText("ccaBusyTime: "
                                    + sneWifiInfo.getCcaBusyTime(),
                            right, top + mLineHeight * idx++, mTextPaint);
                    canvas.drawText("contentionAveTime: "
                                    + sneWifiInfo.getContentionAverageTime(),
                            right, top + mLineHeight * idx++, mTextPaint);
                    canvas.drawText("contentionNumOfSample: "
                                    + sneWifiInfo.getContentionNumOfSamples(),
                            right, top + mLineHeight * idx++, mTextPaint);
                    canvas.drawText("integralUsedDesc: "
                                    + sneWifiTrafficStats.getIntegralUsedDescriptorInDriver(),
                            right, top + mLineHeight * idx++, mTextPaint);
                }
                if (monitorType == DEBUG_VIEW_TYPE_FULL) {
                    canvas.drawText("TxPkts: " + sneWifiTrafficStats.getTxPkt(),
                            right, top + mLineHeight * idx++, mTextPaint);
                    canvas.drawText("RxPkts: " + sneWifiTrafficStats.getRxPkt(),
                            right, top + mLineHeight * idx++, mTextPaint);
                }
                if (SneUtils.isSmartNetworkConnectedSettingsEnabled()) {
                    canvas.drawText("InferenceResult1: " + sneInferenceResult.getPrimary(),
                            right, top + mLineHeight * idx++, mTextPaint);
                    canvas.drawText("InferenceResult2: " + sneInferenceResult.getSecondary(),
                            right, top + mLineHeight * idx++, mTextPaint);
                    canvas.drawText("SneAospScore: " + sneInferenceResult.getVelocityBasedScore(),
                            right, top + mLineHeight * idx++, mTextPaint);
                    canvas.drawText("InferenceResultCell: " + sneInferenceResult.getCellular(),
                            right, top + mLineHeight * idx++, mTextPaint);
                    canvas.drawText("wifiPreferred: " + sneInferenceResult.getWifiPreferred(),
                            right, top + mLineHeight * idx++, mTextPaint);
                }
                if (monitorType == DEBUG_VIEW_TYPE_FULL) {
                    canvas.drawText("sensor accel: " + sneSensorData.getSensorAcceleration(),
                            right, top + mLineHeight * idx++, mTextPaint);
                }
                canvas.drawText("moving: " + sneSensorData.getIsMoving(),
                        right, top + mLineHeight * idx++, mTextPaint);
                canvas.drawText("------------------",
                        right, top + mLineHeight * idx++, mTextPaint);
            } catch (NullPointerException | NumberFormatException e) {
                e.printStackTrace();
            }
        }

        private boolean shouldDoDraw() {
            if (mWifiInfo == null) {
                return false;
            }
            return true;
        }
    }

    public LoggerService.StatsUpdateListener mListener = new LoggerService.StatsUpdateListener() {
        @Override
        public void onRuntimeStatsUpdated(
                @NonNull WifiPredictionData.SneRuntimeStats runtimeStats) {
            mSneRuntimeStats = runtimeStats;
            mWifiInfo = mWifiManager.getConnectionInfo();
            mView.invalidate();
        }
    };

    private ServiceConnection mLoggerServiceConnection = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder service) {
            mLoggerService = ((LoggerService.LocalBinder) service).getService();
            mLoggerService.registerStatsUpdateListener(mListener);
        }

        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            mLoggerService = null;
        }
    };
}
