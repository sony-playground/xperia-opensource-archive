package com.sony.fl.utils;

import java.util.Base64;

/**
 * @author Masanobu Jimbo
 */

public class Base64Wrapper {
    public static String encode(byte[] src) {
        return Base64.getEncoder().encodeToString(src);
    }

    public static byte[] decode(String src) {
        return Base64.getDecoder().decode(src);
    }
}