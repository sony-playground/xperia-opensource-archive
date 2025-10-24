/*
 * Copyright (C) 2019 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

package com.sonymobile.smartnetworkengine.api.debug;

/**
 * Interface for debugging application.
 */
interface ISneDebugManager
{
    void setForcibleReleaseBuild(boolean enable);

    void setIddUploadedSize(long size);
}
