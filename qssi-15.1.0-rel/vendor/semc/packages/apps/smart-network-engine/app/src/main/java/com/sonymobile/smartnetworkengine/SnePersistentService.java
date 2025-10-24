/*
 * Copyright 2021, 2023 Sony Corporation
 */

package com.sonymobile.smartnetworkengine;

import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.IBinder;
import android.util.ArrayMap;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.sonymobile.smartnetworkengine.api.SnePersistentServiceApi;
import com.sonymobile.smartnetworkengine.util.Log;

import java.util.ArrayList;
import java.util.Map;

/**
 * A service to perform reverse bind to start SmartNetworkEngineExt as a persistent service.
 * This is to allow SmartNetworkEngineExt to get PERSISTENT_SERVICE_ADJ, and thus force the
 * system to more or less treat it as a persistent process without all the cons of being a
 * persistent process, i.e. allow google play updates.
 */
public class SnePersistentService extends Service {
    private static final String TAG = SnePersistentService.class.getSimpleName();

    /**
     * If package is restarted (for instance after running instrumentation tests, clearing data
     * or using force stop) then services will not be rebound if we don't listen for it and rebind.
     * Furthermore it is not possible to monitor this in the application affected.
     * (see documentation for {@link android.content.Intent#ACTION_PACKAGE_RESTARTED}).
     *
     * By matching uid in registered services (through package manager) we determine if we need
     * to rebind.
     */
    private final BroadcastReceiver mRestartedReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            int uid = intent.getIntExtra(Intent.EXTRA_UID, -1);
            PackageManager packageManager = getPackageManager();
            ArrayList<ComponentName> boundComponents = new ArrayList<>(
                    mServiceConnections.keySet());
            for (ComponentName componentName : boundComponents) {
                try {
                    ApplicationInfo info = packageManager.getApplicationInfo(
                            componentName.getPackageName(), 0);
                    if (uid == info.uid) {
                        Log.v(TAG, "Received " + intent.getAction() + " from application with" +
                                " bound service, rebinding");
                        unbindService(componentName);
                        bindService(componentName);
                    }
                } catch (PackageManager.NameNotFoundException e) {
                    Log.e(TAG, "Not able to find previously registered app. " + e);
                }
            }
        }
    };

    private final Map<ComponentName, ServiceConnection> mServiceConnections = new ArrayMap<>();

    @Override
    public void onCreate() {
        super.onCreate();
        IntentFilter filter = new IntentFilter(Intent.ACTION_PACKAGE_RESTARTED);
        filter.addDataScheme("package");
        registerReceiver(mRestartedReceiver, filter);
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        try {
            String action = intent != null ? intent.getAction() : null;
            if (intent != null && action != null) {
                if (SnePersistentServiceApi.ACTION_REVERSE_BIND.equals(action)) {
                    ComponentName componentName = componentNameFromExtras(intent);
                    if (componentName != null) {
                        unbindService(componentName);
                        bindService(componentName);
                    }
                } else if (SnePersistentServiceApi.ACTION_REVERSE_UNBIND.equals(action)) {
                    ComponentName componentName = componentNameFromExtras(intent);
                    if (componentName != null) {
                        unbindService(componentName);
                    }
                } else {
                    Log.w(TAG, "Unexpected action " + action);
                }
            }
        } catch (Throwable t) {
            Log.w(TAG, "Something went very wrong when starting service" + t);
        }

        return START_STICKY;
    }

    private ComponentName componentNameFromExtras(Intent intent) {
        String pkgName = intent.getStringExtra(SnePersistentServiceApi.EXTRA_ENABLER_PKG);
        String className = intent.getStringExtra(
                SnePersistentServiceApi.EXTRA_ENABLER_CLASS);
        if (pkgName == null || className == null) {
            Log.w(TAG, "Missing extras " + SnePersistentServiceApi.EXTRA_ENABLER_PKG + " " +
                    "or " + SnePersistentServiceApi.EXTRA_ENABLER_CLASS);
            return null;
        }
        return new ComponentName(pkgName, className);
    }

    @Override
    public void onDestroy() {
        super.onDestroy();

        unregisterReceiver(mRestartedReceiver);
        for (ServiceConnection conn : mServiceConnections.values()) {
            unbindService(conn);
        }
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    /**
     * Bind service if not already bound
     */
    private void bindService(@NonNull ComponentName componentName) {
        try {
            Intent intent = new Intent();
            intent.setComponent(componentName);
            TokenServiceConnection tokenServiceConnection = new TokenServiceConnection();

            boolean bound = bindService(intent, tokenServiceConnection,
                    Context.BIND_AUTO_CREATE | Context.BIND_IMPORTANT);
            if (bound) {
                mServiceConnections.put(componentName, tokenServiceConnection);
            } else {
                mServiceConnections.remove(componentName);
            }

            Log.i(TAG, "Bound service " + componentName + ": " + bound);
        } catch (SecurityException e) {
            Log.w(TAG, "Unable to bind service " + componentName + ": " + e);
        }
    }

    /**
     * Unbind service
     */
    private void unbindService(@NonNull ComponentName componentName) {
        ServiceConnection serviceConnection = mServiceConnections.remove(componentName);
        if (serviceConnection != null) {
            unbindService(serviceConnection);
            Log.i(TAG, "Unbound service " + componentName);
        }
    }

    /**
     * Since SnePersistentService onBind returns null we don't expect any of the callbacks to be
     * called. This instance is only used as a token for binding and unbinding the service.
     */
    private static class TokenServiceConnection implements ServiceConnection {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
        }
    }
}