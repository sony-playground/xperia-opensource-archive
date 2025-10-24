/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.debug;

import static com.sonymobile.smartnetworkengine.SneUtils.isDebugBuild;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

public class SecretCodeReceiver extends BroadcastReceiver {

    private final static String SECRET_CODE = "android.provider.Telephony.SECRET_CODE";

    @Override
    public void onReceive(Context context, Intent intent) {
        if (!isDebugBuild()) {
            return;
        }

        if (intent.getAction() != null && intent.getAction().equals(SECRET_CODE)) {
            Intent secretIntent = new Intent(context, SecretMenuActivity.class);
            secretIntent.setFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_NEW_TASK);
            context.startActivity(secretIntent);
        }
    }
}
