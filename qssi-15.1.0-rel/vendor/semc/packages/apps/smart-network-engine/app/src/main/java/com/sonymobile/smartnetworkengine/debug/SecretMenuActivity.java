/*
 * Copyright 2018, 2024 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.debug;

import android.app.ActionBar;
import android.app.Activity;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.view.View;
import android.widget.CheckBox;
import android.widget.RadioGroup;

import com.sonymobile.smartnetworkengine.PreferenceAccessor;
import com.sonymobile.smartnetworkengine.R;
import com.sonymobile.smartnetworkengine.SneUtils;

public class SecretMenuActivity extends Activity {

    private RadioGroup mDebugViewDataType;
    private CheckBox mDebugViewEnabledCheckBox;
    private WifiManager mWifiManager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.secretmenu);
        SneUtils.setupEdgeToEdge(this);
        prepareActionBar();

        mDebugViewEnabledCheckBox = findViewById(R.id.DebugViewCheckBox);
        mDebugViewDataType = findViewById(R.id.RadioGroupDebugViewType);
        mDebugViewDataType.setVisibility(View.INVISIBLE);
        mWifiManager = (WifiManager) getSystemService(WIFI_SERVICE);

        // Check current status
        viewCurrentDataStatus();

        mDebugViewEnabledCheckBox.setOnClickListener(v -> {
            if (mDebugViewEnabledCheckBox.isChecked()) {
                mDebugViewDataType.setVisibility(View.VISIBLE);
            } else {
                mDebugViewDataType.clearCheck();
                mDebugViewDataType.setVisibility(View.INVISIBLE);
            }
        });

        mDebugViewDataType.setOnCheckedChangeListener(
                (radioGroup, checkedId) -> PreferenceAccessor.setDebugViewType(checkedId));

    }

    @Override
    protected void onResume() {
        super.onResume();
        viewCurrentDataStatus();
    }

    @Override
    protected void onDestroy() {
        PreferenceAccessor.setDebugViewType(DebugViewService.DEBUG_VIEW_TYPE_DISABLE);
        super.onDestroy();
    }

    private void viewCurrentDataStatus() {
        long debugViewType = PreferenceAccessor.getDebugViewType();

        if (debugViewType != DebugViewService.DEBUG_VIEW_TYPE_DISABLE) {
            mDebugViewEnabledCheckBox.setChecked(true);
            mDebugViewDataType.setVisibility(View.VISIBLE);
            mDebugViewDataType.check((int) debugViewType);
        }
        WifiInfo wifiInfo = mWifiManager.getConnectionInfo();
        if (wifiInfo != null && wifiInfo.getIpAddress() != 0) {
            mDebugViewEnabledCheckBox.setEnabled(false);
        } else {
            mDebugViewEnabledCheckBox.setEnabled(true);
        }
    }

    private void prepareActionBar() {
        final ActionBar actionBar = getActionBar();
        if (actionBar != null) {
            actionBar.setElevation(0);
        }
    }
}
