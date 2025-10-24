/*
 * Copyright (C) 2019 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.api;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;

import androidx.annotation.Nullable;

import com.sonymobile.smartnetworkengine.api.debug.ISneDebugManager;
import com.sonymobile.smartnetworkengine.api.debug.SneDebugManager;

/**
 * The main entry point for the Smart Network Engine services.
 *
 * This class provides the methods for applications to obtain instances of
 * the manager interface that is connected to the Smart Network Engine service.
 *
 * <p> Your application can retrieve the interface through {@link ConnectionCallbacks}
 * interface. Call {@link #connect(String, ConnectionCallbacks)} with your implementation
 * of {@link ConnectionCallbacks} first. If the result of your connection request is
 * successful, {@link ConnectionCallbacks#onConnected(String, Object)} is called and then
 * it's passed through the argument of this method.
 *
 * <p> When your application is done using the interfaces, call {@link #disconnect()},
 * even if the async result from {@link #connect(String, ConnectionCallbacks)} has
 * not yet been delivered.
 *
 * <p> You should instantiate a client object in your Activity's onCreate(Bundle)
 * method and then call {@link #connect(String, ConnectionCallbacks)} in onStart()
 * and {@link #disconnect()} in onStop(), regardless of the state.
 */
public final class SneApiClient {

    /**
     * The name of the Smart Network Engine event service.
     * Use with {@link #connect} to retrieve a {@link SneEventManager}.
     *
     * @see #connect
     * @see SneEventManager
     */
    public static final String SNE_EVENT_SERVICE = "sne_event";

    /**
     * The name of the Smart Network Engine debug service.
     * Use with {@link #connect} to retrieve a {@link SneDebugManager}.
     *
     * @see #connect
     * @see SneDebugManager
     */
    public static final String SNE_DEBUG_SERVICE = "sne_debug";

    private static final String SNE_PACKAGE_NAME = "com.sonymobile.smartnetworkengine";

    private static final String SNE_ACTION_TO_EVENT_MANAGER =
            "com.sonymobile.smartnetworkengine.intent.action.ISneEventManager";

    private static final String SNE_ACTION_TO_DEBUG_MANAGER =
            "com.sonymobile.smartnetworkengine.intent.action.ISneDebugManager";

    private final Context mContext;
    @Nullable
    private ServiceConnection mConnectionToEvent;
    @Nullable
    private ServiceConnection mConnectionToDebug;
    @Nullable
    private SneEventManager mSneEventManager;
    @Nullable
    private SneDebugManager mSneDebugManager;

    /**
     * Constructor
     */
    public SneApiClient(Context context) {
        if (context == null) {
            throw new IllegalArgumentException("context cannot be null");
        }
        mContext = context;
    }

    /**
     * Connects to the specified service. If the connection is successful,
     * {@link ConnectionCallbacks#onConnected(String, Object)} is called.
     *
     * <p> If the client is already connected or connecting, this method
     * does nothing.
     *
     * @param name     the name of the service that you want to connect to.
     * @param listener the listener where the results of the asynchronous
     *                 {@link ConnectionCallbacks#onConnected(String, Object)}
     *                 call are delivered. It must not be null.
     * @see #SNE_EVENT_SERVICE
     * @see #SNE_DEBUG_SERVICE
     */
    public synchronized void connect(String name, ConnectionCallbacks listener) {
        if (name == null || listener == null) {
            throw new IllegalArgumentException("name/listener cannot be null");
        } else if (isConnectedOrConnecting(name)) {
            return;
        }
        // Connect to service
        if (name.equals(SNE_EVENT_SERVICE)) {
            mConnectionToEvent = new ServiceConnectionImpl(name, listener);
            Intent intent = new Intent(SNE_ACTION_TO_EVENT_MANAGER);
            intent.setPackage(SNE_PACKAGE_NAME);
            mContext.bindService(intent, mConnectionToEvent, Context.BIND_AUTO_CREATE);
        } else if (name.equals(SNE_DEBUG_SERVICE)) {
            mConnectionToDebug = new ServiceConnectionImpl(name, listener);
            Intent intent = new Intent(SNE_ACTION_TO_DEBUG_MANAGER);
            intent.setPackage(SNE_PACKAGE_NAME);
            mContext.bindService(intent, mConnectionToDebug, Context.BIND_AUTO_CREATE);
        } else {
            throw new IllegalArgumentException("unknown service name: " + name);
        }
    }

    /**
     * Closes all connections to the service. No calls can be made using the
     * manager interface previously obtained after calling this method.
     */
    public synchronized void disconnect() {
        if (mSneEventManager != null) {
            mSneEventManager.release();
            mSneEventManager = null;
        }
        if (mSneDebugManager != null) {
            mSneDebugManager.release();
            mSneDebugManager = null;
        }
        if (mConnectionToEvent != null) {
            mContext.unbindService(mConnectionToEvent);
            mConnectionToEvent = null;
        }
        if (mConnectionToDebug != null) {
            mContext.unbindService(mConnectionToDebug);
            mConnectionToDebug = null;
        }
    }

    private boolean isConnectedOrConnecting(String name) {
        if (name.equals(SNE_EVENT_SERVICE)) {
            return mConnectionToEvent != null;
        } else if (name.equals(SNE_DEBUG_SERVICE)) {
            return mConnectionToDebug != null;
        }
        return false;
    }

    private class ServiceConnectionImpl implements ServiceConnection {

        private final String mName;
        private final ConnectionCallbacks mListener;

        ServiceConnectionImpl(String name, ConnectionCallbacks listener) {
            mName = name;
            mListener = listener;
        }

        @Override
        public void onServiceConnected(ComponentName unused, IBinder binder) {
            synchronized (SneApiClient.this) {
                Object service = null;
                if (mName.equals(SNE_EVENT_SERVICE)) {
                    mSneEventManager = new SneEventManager(
                            ISneEventManager.Stub.asInterface(binder));
                    service = mSneEventManager;
                } else if (mName.equals(SNE_DEBUG_SERVICE)) {
                    mSneDebugManager = new SneDebugManager(
                            ISneDebugManager.Stub.asInterface(binder));
                    service = mSneDebugManager;
                }
                mListener.onConnected(mName, service);
            }
        }

        @Override
        public void onServiceDisconnected(ComponentName unused) {
            synchronized (SneApiClient.this) {
                if (mName.equals(SNE_EVENT_SERVICE)) {
                    if (mSneEventManager != null) {
                        mSneEventManager.release();
                        mSneEventManager = null;
                    }
                } else if (mName.equals(SNE_DEBUG_SERVICE)) {
                    if (mSneDebugManager != null) {
                        mSneDebugManager.release();
                        mSneDebugManager = null;
                    }
                }
                mListener.onDisconnected(mName);
            }
        }
    }

    /**
     * Provides callbacks that are called when the client is connected or
     * disconnected from the service.
     *
     * @see #connect
     */
    public interface ConnectionCallbacks {

        /**
         * After calling {@link SneApiClient#connect}, this method will be
         * invoked asynchronously when the connect to the service request has
         * successfully completed. The application can obtain an instance of
         * either {@link SneEventManager} or {@link SneDebugManager}
         * through the second argument of this method.
         *
         * @param name    the name of the service that has been connected.
         * @param service the instance of the manager interface that is connected
         *                to the service.
         */
        void onConnected(String name, Object service);

        /**
         * Called when a connection to the service has been lost. This typically
         * happens when the process hosting the service has crashed or been killed.
         * The binding to the service will remain active, and you will receive a call
         * to {@link #onConnected} when the service is next running.
         *
         * @param name the name of the service that has been disconnected.
         */
        void onDisconnected(String name);
    }
}
