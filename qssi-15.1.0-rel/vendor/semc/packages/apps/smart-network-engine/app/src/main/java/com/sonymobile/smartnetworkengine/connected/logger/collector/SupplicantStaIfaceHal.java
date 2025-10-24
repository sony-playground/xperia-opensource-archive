/*
 * Copyright 2023 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.connected.logger.collector;

import androidx.annotation.Nullable;

/**
 * Abstraction of Supplicant STA Iface HAL interface
 */
public abstract class SupplicantStaIfaceHal {
    protected final Object mLock = new Object();
    protected SupplicantListener mSupplicantListener;

    /**
     * Begin initializing the ISupplicantStaIfaceHal object. Specific initialization
     * logic differs between the HIDL and AIDL implementations.
     */
    public abstract void initialize();

    /**
     * Set a listener to receive callback invocation on Supplicant.
     */
    public void setListener(@Nullable SupplicantListener listener) {
        synchronized (mLock) {
            mSupplicantListener = listener;
        }
    }

    /**
     * Interface for callback invocation on Supplicant
     */
    public interface SupplicantListener {
        void onDisconnected(boolean locallyGenerated, int reasonCode, String ifaceName);
    }
}
