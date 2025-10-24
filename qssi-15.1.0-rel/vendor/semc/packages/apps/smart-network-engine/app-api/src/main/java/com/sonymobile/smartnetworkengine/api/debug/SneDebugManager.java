/*
 * Copyright (C) 2019 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.api.debug;

import android.os.RemoteException;

import androidx.annotation.NonNull;

/**
 * The manager to provide the Smart Network Engine debug API.
 *
 * Get an instance of this class by calling
 * {@link com.sonymobile.smartnetworkengine.api.SneApiClient#connect}
 * with {@link com.sonymobile.smartnetworkengine.api.SneApiClient#SNE_DEBUG_SERVICE}.
 *
 * @see com.sonymobile.smartnetworkengine.api.SneApiClient
 */
public final class SneDebugManager {

    private ISneDebugManager mService;

    public SneDebugManager(@NonNull ISneDebugManager service) {
        mService = service;
    }

    public void release() {
        mService = null;
    }

    /**
     * Forcibly set build variant to "user" (i.e. release build).
     */
    @Deprecated
    public void setForcibleReleaseBuild(boolean enable) {
        validateConnection();
        try {
            mService.setForcibleReleaseBuild(enable);
        } catch (RemoteException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Update the size of the uploaded idd data.
     */
    public void setIddUploadedSize(long size) {
        validateConnection();
        try {
            mService.setIddUploadedSize(size);
        } catch (RemoteException e) {
            throw new RuntimeException(e);
        }
    }

    private void validateConnection() {
        if (mService == null) {
            throw new IllegalStateException("No service connection");
        }
    }
}
