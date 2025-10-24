/*
 * Copyright 2018, 2024 Sony Corporation
 */

package com.sonymobile.smartnetworkengine;

import static com.sonymobile.smartnetworkengine.Constants.SETTINGS_SMARTNET_CONNECTED_ENABLED;
import static com.sonymobile.smartnetworkengine.Constants.SETTINGS_SMARTNET_ENTRY_ENABLED;

import android.app.Activity;
import android.content.Context;
import android.os.Build;
import android.provider.Settings;

import androidx.annotation.NonNull;
import androidx.core.graphics.Insets;
import androidx.core.view.ViewCompat;
import androidx.core.view.WindowCompat;
import androidx.core.view.WindowInsetsCompat;

public class SneUtils {

    /**
     * Whether forcible release build or not. See {@link #setForcibleReleaseBuild(boolean)}.
     */
    private static boolean sForcibleReleaseBuild = false;

    /**
     * Return true if SETTINGS_SMARTNET_CONNECTED_ENABLED is 1 or default value(null)
     */
    public static boolean isSmartNetworkConnectedSettingsEnabled() {
        return isSmartNetworkConnectedSettingsEnabled(SneApplication.getContext());
    }

    /**
     * Return true if SETTINGS_SMARTNET_ENTRY_ENABLED is 1 or default value(null)
     */
    public static boolean isSmartNetworkEntrySettingsEnabled() {
        return isSmartNetworkEntrySettingsEnabled(SneApplication.getContext());
    }

    /**
     * Return true if SETTINGS_SMARTNET_CONNECTED_ENABLED is 1 or default value(null)
     * <p>
     * This method is intended to be used from the provider class which is potentially invoked
     * earlier than initializing {@link SneApplication} class.
     */
    public static boolean isSmartNetworkConnectedSettingsEnabled(@NonNull Context context) {
        return Settings.Global.getInt(context.getContentResolver(),
                SETTINGS_SMARTNET_CONNECTED_ENABLED, 1) == 1;
    }

    /**
     * Return true if SETTINGS_SMARTNET_ENTRY_ENABLED is 1 or default value(null)
     * <p>
     * This method is intended to be used from the provider class which is potentially invoked
     * earlier than initializing {@link SneApplication} class.
     */
    public static boolean isSmartNetworkEntrySettingsEnabled(@NonNull Context context) {
        return Settings.Global.getInt(context.getContentResolver(),
                SETTINGS_SMARTNET_ENTRY_ENABLED, 1) == 1;
    }

    /**
     * Return true if build variant is "userdebug".
     */
    public static boolean isDebugBuild() {
        return Build.TYPE.equals("userdebug") && !sForcibleReleaseBuild;
    }

    /**
     * Forcibly set build variant to "user".
     * <p>
     * This method should be used for debugging purpose only.
     */
    public static void setForcibleReleaseBuild(boolean enable) {
        sForcibleReleaseBuild = enable;
    }

    /**
     * Enable new edge to edge feature.
     *
     * @param activity the Activity need to setup the edge to edge feature.
     */
    public static void setupEdgeToEdge(Activity activity) {
        WindowCompat.setDecorFitsSystemWindows(activity.getWindow(), false);
        ViewCompat.setOnApplyWindowInsetsListener(activity.findViewById(android.R.id.content),
                (v, windowInsets) -> {
                    Insets insets = windowInsets.getInsets(WindowInsetsCompat.Type.systemBars());
                    // Apply the insets paddings to the view.
                    v.setPadding(insets.left, insets.top, insets.right, insets.bottom);
                    return WindowInsetsCompat.CONSUMED;
                });
    }
}
