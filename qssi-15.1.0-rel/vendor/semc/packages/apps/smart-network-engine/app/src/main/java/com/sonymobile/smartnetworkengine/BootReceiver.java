/*
 * Copyright 2017 Sony Corporation
 */

package com.sonymobile.smartnetworkengine;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.UserManager;

public class BootReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent) {
        if (Intent.ACTION_BOOT_COMPLETED.equals(intent.getAction())) {
            UserManager userManager = context.getSystemService(UserManager.class);
            if (userManager.isSystemUser()) {
                context.startService(new Intent(context, CoreService.class));
            }
        }
    }
}
