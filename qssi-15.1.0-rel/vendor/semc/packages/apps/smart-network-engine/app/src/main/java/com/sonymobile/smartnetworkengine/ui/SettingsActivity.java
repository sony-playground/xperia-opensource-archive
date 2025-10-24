/*
 * Copyright 2018, 2024 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.ui;

import static com.sonymobile.smartnetworkengine.Constants.SETTINGS_SMARTNET_CONNECTED_ENABLED;
import static com.sonymobile.smartnetworkengine.Constants.SETTINGS_SMARTNET_ENTRY_ENABLED;

import android.app.ActionBar;
import android.app.Activity;
import android.os.Bundle;
import android.provider.Settings;
import android.view.MenuItem;
import android.view.View;
import android.widget.Switch;
import android.widget.TextView;

import androidx.annotation.Nullable;

import com.sonymobile.smartnetworkengine.R;
import com.sonymobile.smartnetworkengine.SneUtils;

public class SettingsActivity extends Activity {

    private Switch mConnectedSettingSwitch;

    @Nullable
    private Switch mEntrySettingSwitch;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);
        SneUtils.setupEdgeToEdge(this);
        prepareActionBar();

        // "connected" setting
        // Set title and description
        View connectedSettingView = findViewById(R.id.preference_switch_connected);
        TextView connectedSettingTitleView = connectedSettingView.findViewById(R.id.title);
        connectedSettingTitleView.setText(R.string.smart_network_settings_connected_switch_title);
        TextView connectedSettingDescView = connectedSettingView.findViewById(R.id.desc);
        connectedSettingDescView.setText(R.string.smart_network_settings_connected_switch_desc);
        mConnectedSettingSwitch = connectedSettingView.findViewById(R.id.switch_widget);
        // Set listener for touch area
        View connectedSettingTouchArea = connectedSettingView.findViewById(
                R.id.switch_widget_frame);
        connectedSettingTouchArea.setOnClickListener(view -> {
            mConnectedSettingSwitch.setChecked(!mConnectedSettingSwitch.isChecked());
            Settings.Global.putInt(getContentResolver(), SETTINGS_SMARTNET_CONNECTED_ENABLED,
                    mConnectedSettingSwitch.isChecked() ? 1 : 0);
        });

        // "entry" setting
        if (getResources().getBoolean(R.bool.config_fl_system_enabled)) {
            // Set title and description
            View entrySettingView = findViewById(R.id.preference_switch_entry);
            TextView entrySettingTitleView = entrySettingView.findViewById(R.id.title);
            entrySettingTitleView.setText(R.string.smart_network_settings_entry_switch_title);
            TextView entrySettingDescView = entrySettingView.findViewById(R.id.desc);
            entrySettingDescView.setText(R.string.smart_network_settings_entry_switch_desc);
            mEntrySettingSwitch = entrySettingView.findViewById(R.id.switch_widget);
            // Set listener for touch area
            View entrySettingTouchArea = entrySettingView.findViewById(R.id.switch_widget_frame);
            entrySettingTouchArea.setOnClickListener(view -> {
                mEntrySettingSwitch.setChecked(!mEntrySettingSwitch.isChecked());
                Settings.Global.putInt(getContentResolver(), SETTINGS_SMARTNET_ENTRY_ENABLED,
                        mEntrySettingSwitch.isChecked() ? 1 : 0);
            });
            // Make it visible
            entrySettingView.setVisibility(View.VISIBLE);
        }
    }

    /**
     * Called when option menu item selected.
     */
    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        boolean result = true;
        switch (item.getItemId()) {
            case android.R.id.home:
                finish();
                break;
            default:
                result = super.onOptionsItemSelected(item);
        }
        return result;
    }

    @Override
    public void onResume() {
        super.onResume();
        mConnectedSettingSwitch.setChecked(SneUtils.isSmartNetworkConnectedSettingsEnabled());
        if (mEntrySettingSwitch != null) {
            mEntrySettingSwitch.setChecked(SneUtils.isSmartNetworkEntrySettingsEnabled());
        }
    }

    private void prepareActionBar() {
        final ActionBar actionBar = getActionBar();
        if (actionBar != null) {
            actionBar.setDisplayHomeAsUpEnabled(true);
            actionBar.setElevation(0);
        }
    }
}
