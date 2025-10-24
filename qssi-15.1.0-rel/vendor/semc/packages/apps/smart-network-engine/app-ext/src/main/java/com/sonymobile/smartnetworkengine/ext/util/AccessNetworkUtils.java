/*
 * Copyright 2024 Sony Corporation
 * copy from frameworks/base/telephony/java/android/telephony/AccessNetworkUtils.java
 */

package com.sonymobile.smartnetworkengine.ext.util;

import android.telephony.AccessNetworkConstants.NgranBands;
import android.telephony.ServiceState;

public class AccessNetworkUtils {

    public static final int INVALID_BAND = -1;

    /**
     * Gets the NR Operating band for a given downlink NRARFCN.
     *
     * <p>See 3GPP TS 38.104 Table 5.2-1 NR operating bands in FR1 and
     * Table 5.2-2 NR operating bands in FR2
     *
     * @param nrarfcn The downlink NRARFCN
     * @return Operating band number, or {@link #INVALID_BAND} if no corresponding band exists
     */
    public static int getOperatingBandForNrarfcn(int nrarfcn) {
        if (nrarfcn >= 422000 && nrarfcn <= 434000) {
            return NgranBands.BAND_1;
        } else if (nrarfcn >= 386000 && nrarfcn <= 398000) {
            return NgranBands.BAND_2;
        } else if (nrarfcn >= 361000 && nrarfcn <= 376000) {
            return NgranBands.BAND_3;
        } else if (nrarfcn >= 173800 && nrarfcn <= 178800) {
            return NgranBands.BAND_5;
        } else if (nrarfcn >= 524000 && nrarfcn <= 538000) {
            return NgranBands.BAND_7;
        } else if (nrarfcn >= 185000 && nrarfcn <= 192000) {
            return NgranBands.BAND_8;
        } else if (nrarfcn >= 145800 && nrarfcn <= 149200) {
            return NgranBands.BAND_12;
        } else if (nrarfcn >= 151600 && nrarfcn <= 153600) {
            return NgranBands.BAND_14;
        } else if (nrarfcn >= 172000 && nrarfcn <= 175000) {
            return NgranBands.BAND_18;
        } else if (nrarfcn >= 158200 && nrarfcn <= 164200) {
            return NgranBands.BAND_20;
        } else if (nrarfcn >= 386000 && nrarfcn <= 399000) {
            return NgranBands.BAND_25;
        } else if (nrarfcn >= 171800 && nrarfcn <= 178800) {
            return NgranBands.BAND_26;
        } else if (nrarfcn >= 151600 && nrarfcn <= 160600) {
            return NgranBands.BAND_28;
        } else if (nrarfcn >= 143400 && nrarfcn <= 145600) {
            return NgranBands.BAND_29;
        } else if (nrarfcn >= 470000 && nrarfcn <= 472000) {
            return NgranBands.BAND_30;
        } else if (nrarfcn >= 402000 && nrarfcn <= 405000) {
            return NgranBands.BAND_34;
        } else if (nrarfcn >= 514000 && nrarfcn <= 524000) {
            return NgranBands.BAND_38;
        } else if (nrarfcn >= 376000 && nrarfcn <= 384000) {
            return NgranBands.BAND_39;
        } else if (nrarfcn >= 460000 && nrarfcn <= 480000) {
            return NgranBands.BAND_40;
        } else if (nrarfcn >= 499200 && nrarfcn <= 537999) {
            return NgranBands.BAND_41;
        } else if (nrarfcn >= 743334 && nrarfcn <= 795000) {
            return NgranBands.BAND_46;
        } else if (nrarfcn >= 636667 && nrarfcn <= 646666) {
            return NgranBands.BAND_48;
        } else if (nrarfcn >= 286400 && nrarfcn <= 303400) {
            return NgranBands.BAND_50;
        } else if (nrarfcn >= 285400 && nrarfcn <= 286400) {
            return NgranBands.BAND_51;
        } else if (nrarfcn >= 496700 && nrarfcn <= 499000) {
            return NgranBands.BAND_53;
        } else if (nrarfcn >= 422000 && nrarfcn <= 440000) {
            return NgranBands.BAND_65; // BAND_66 has the same channels
        } else if (nrarfcn >= 399000 && nrarfcn <= 404000) {
            return NgranBands.BAND_70;
        } else if (nrarfcn >= 123400 && nrarfcn <= 130400) {
            return NgranBands.BAND_71;
        } else if (nrarfcn >= 295000 && nrarfcn <= 303600) {
            return NgranBands.BAND_74;
        } else if (nrarfcn >= 286400 && nrarfcn <= 303400) {
            return NgranBands.BAND_75;
        } else if (nrarfcn >= 285400 && nrarfcn <= 286400) {
            return NgranBands.BAND_76;
        } else if (nrarfcn >= 620000 && nrarfcn <= 680000) {
            return NgranBands.BAND_77;
        } else if (nrarfcn >= 620000 && nrarfcn <= 653333) {
            return NgranBands.BAND_78;
        } else if (nrarfcn >= 693334 && nrarfcn <= 733333) {
            return NgranBands.BAND_79;
        } else if (nrarfcn >= 499200 && nrarfcn <= 538000) {
            return NgranBands.BAND_90;
        } else if (nrarfcn >= 285400 && nrarfcn <= 286400) {
            return NgranBands.BAND_91;
        } else if (nrarfcn >= 286400 && nrarfcn <= 303400) {
            return NgranBands.BAND_92;
        } else if (nrarfcn >= 285400 && nrarfcn <= 286400) {
            return NgranBands.BAND_93;
        } else if (nrarfcn >= 286400 && nrarfcn <= 303400) {
            return NgranBands.BAND_94;
        } else if (nrarfcn >= 795000 && nrarfcn <= 875000) {
            return NgranBands.BAND_96;
        } else if (nrarfcn >= 2054166 && nrarfcn <= 2104165) {
            return NgranBands.BAND_257;
        } else if (nrarfcn >= 2016667 && nrarfcn <= 2070832) {
            return NgranBands.BAND_258;
        } else if (nrarfcn >= 2229166 && nrarfcn <= 2279165) {
            return NgranBands.BAND_260;
        } else if (nrarfcn >= 2070833 && nrarfcn <= 2084999) {
            return NgranBands.BAND_261;
        }
        return INVALID_BAND;
    }

    /**
     * Get ngran band from {@link PhysicalChannelConfig#getBand()}
     * 3GPP TS 38.104 Table 5.2-1 NR operating bands in FR1
     * 3GPP TS 38.104 Table 5.2-2 NR operating bands in FR2
     */
    public static int getFrequencyRangeGroupFromNrBand(int band) {
        switch (band) {
            case NgranBands.BAND_5:
            case NgranBands.BAND_8:
            case NgranBands.BAND_12:
            case NgranBands.BAND_14:
            case NgranBands.BAND_18:
            case NgranBands.BAND_20:
            case NgranBands.BAND_26:
            case NgranBands.BAND_28:
            case NgranBands.BAND_29:
            case NgranBands.BAND_71:
            case NgranBands.BAND_81:
            case NgranBands.BAND_82:
            case NgranBands.BAND_83:
            case NgranBands.BAND_89:
                return ServiceState.FREQUENCY_RANGE_LOW;
            case NgranBands.BAND_1:
            case NgranBands.BAND_2:
            case NgranBands.BAND_3:
            case NgranBands.BAND_7:
            case NgranBands.BAND_25:
            case NgranBands.BAND_30:
            case NgranBands.BAND_34:
            case NgranBands.BAND_38:
            case NgranBands.BAND_39:
            case NgranBands.BAND_40:
            case NgranBands.BAND_41:
            case NgranBands.BAND_50:
            case NgranBands.BAND_51:
            case NgranBands.BAND_53:
            case NgranBands.BAND_65:
            case NgranBands.BAND_66:
            case NgranBands.BAND_70:
            case NgranBands.BAND_74:
            case NgranBands.BAND_75:
            case NgranBands.BAND_76:
            case NgranBands.BAND_80:
            case NgranBands.BAND_84:
            case NgranBands.BAND_86:
            case NgranBands.BAND_90:
            case NgranBands.BAND_91:
            case NgranBands.BAND_92:
            case NgranBands.BAND_93:
            case NgranBands.BAND_94:
            case NgranBands.BAND_95:
                return ServiceState.FREQUENCY_RANGE_MID;
            case NgranBands.BAND_46:
            case NgranBands.BAND_48:
            case NgranBands.BAND_77:
            case NgranBands.BAND_78:
            case NgranBands.BAND_79:
                return ServiceState.FREQUENCY_RANGE_HIGH;
            case NgranBands.BAND_96:
            case NgranBands.BAND_257:
            case NgranBands.BAND_258:
            case NgranBands.BAND_260:
            case NgranBands.BAND_261:
                return ServiceState.FREQUENCY_RANGE_MMWAVE;
            default:
                return ServiceState.FREQUENCY_RANGE_UNKNOWN;
        }
    }
}