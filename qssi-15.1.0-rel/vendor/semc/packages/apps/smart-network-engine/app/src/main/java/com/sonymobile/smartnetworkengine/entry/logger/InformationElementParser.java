/*
 * Copyright (C) 2015 The Android Open Source Project
 * Copyright (C) 2020 Sony Mobile Communications Inc. All rights reserved.
 * This file contains confidential and proprietary information of Sony Mobile
 * Communications Inc.
 *
 * NOTE: This file contains code from:
 *
 *     frameworks/opt/net/wifi/service/java/com/android/server/wifi/util/InformationElementUtil.java
 *
 * taken from The Android Open Source Project, which is licensed under the Apache
 * License, Version 2.0, which may be accessed at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Notwithstanding the foregoing, the entire contents of this file is licensed
 * under the Sony Mobile Communications Inc. End User License Agreement
 * ("EULA"). Any use of this file is subject to the terms of the EULA.
 */

package com.sonymobile.smartnetworkengine.entry.logger;

import android.net.wifi.ScanResult.InformationElement;

import androidx.annotation.NonNull;

import com.sonymobile.smartnetworkengine.util.Log;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.List;

public class InformationElementParser {

    private static final String TAG = InformationElementParser.class.getSimpleName();

    private static final int BYTE_MASK = 0xff;

    private static final int SHORT_MASK = 0xffff;

    private static final int EID_BSS_LOAD = 11;

    /**
     * Parse and retrieve the BSS Load information element from the list of IEs.
     */
    @NonNull
    public static BssLoad getBssLoadIE(List<InformationElement> ies) {
        BssLoad bssLoad = new BssLoad();
        if (ies != null) {
            for (InformationElement ie : ies) {
                if (ie != null && ie.getId() == EID_BSS_LOAD) {
                    try {
                        bssLoad.from(ie);
                    } catch (RuntimeException e) {
                        Log.w(TAG, "Failed to parse BSS Load IE: " + e.getMessage());
                    }
                }
            }
        }
        return bssLoad;
    }

    public static class BssLoad {

        public static final int INVALID = -1;

        public int stationCount = INVALID;

        public int channelUtilization = INVALID;

        public int capacity = INVALID;

        void from(@NonNull InformationElement ie) {
            if (ie.getId() != EID_BSS_LOAD) {
                throw new IllegalArgumentException("Element id is not BSS_LOAD: " + ie.getId());
            }
            if (ie.getBytes().capacity() != 5) {
                throw new IllegalArgumentException("BSS Load element length is not 5: "
                        + ie.getBytes().capacity());
            }
            ByteBuffer data = ie.getBytes().order(ByteOrder.LITTLE_ENDIAN);
            stationCount = data.getShort() & SHORT_MASK;
            channelUtilization = data.get() & BYTE_MASK;
            capacity = data.getShort() & SHORT_MASK;
        }
    }
}
