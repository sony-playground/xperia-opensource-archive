/*
 * Copyright 2021 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls;

import static androidx.test.platform.app.InstrumentationRegistry.getInstrumentation;

import static org.junit.Assert.assertArrayEquals;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import org.junit.Test;
import org.junit.runner.RunWith;

import java.security.spec.PKCS8EncodedKeySpec;

import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

@RunWith(AndroidJUnit4.class)
public class CertificateAccessorTest {

    @Test
    public void testDestroyIvParameterSpec() {
        CertificateAccessor accessor = new CertificateAccessor(
                getInstrumentation().getTargetContext());
        byte[] iv = new byte[]{0x01, 0x02, 0x03};

        // Action
        IvParameterSpec ivParameterSpec = new IvParameterSpec(iv);

        // Check
        assertArrayEquals(new byte[]{0x01, 0x02, 0x03}, ivParameterSpec.getIV());

        // Action
        accessor.destroy(ivParameterSpec);

        // Check
        assertArrayEquals(new byte[]{0x00, 0x00, 0x00}, ivParameterSpec.getIV());
    }

    @Test
    public void testDestroySecretKeySpec() {
        CertificateAccessor accessor = new CertificateAccessor(
                getInstrumentation().getTargetContext());
        byte[] key = new byte[]{0x01, 0x02, 0x03};

        // Action
        SecretKeySpec secretKeySpec = new SecretKeySpec(key, "AES");

        // Check
        assertArrayEquals(new byte[]{0x01, 0x02, 0x03}, secretKeySpec.getEncoded());

        // Action
        accessor.destroy(secretKeySpec);

        // Check
        assertArrayEquals(new byte[]{0x00, 0x00, 0x00}, secretKeySpec.getEncoded());
    }

    @Test
    public void testDestroyEncodedKeySpec() {
        CertificateAccessor accessor = new CertificateAccessor(
                getInstrumentation().getTargetContext());
        byte[] key = new byte[]{0x01, 0x02, 0x03};

        // Action
        PKCS8EncodedKeySpec encodedKeySpec = new PKCS8EncodedKeySpec(key);

        // Check
        assertArrayEquals(new byte[]{0x01, 0x02, 0x03}, encodedKeySpec.getEncoded());

        // Action
        accessor.destroy(encodedKeySpec);

        // Check
        assertArrayEquals(new byte[]{0x00, 0x00, 0x00}, encodedKeySpec.getEncoded());
    }

    @Test
    public void testDestroyBytes() {
        CertificateAccessor accessor = new CertificateAccessor(
                getInstrumentation().getTargetContext());
        byte[] key = new byte[]{0x01, 0x02, 0x03};

        // Action
        accessor.destroy(key);

        // Check
        assertArrayEquals(new byte[]{0x00, 0x00, 0x00}, key);
    }
}
