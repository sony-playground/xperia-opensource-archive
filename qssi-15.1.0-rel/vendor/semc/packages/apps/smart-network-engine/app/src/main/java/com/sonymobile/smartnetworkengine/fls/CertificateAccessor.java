/*
 * Copyright 2021 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls;

import static com.sonymobile.smartnetworkengine.Constants.ENTRY_ASSET_DIR;

import android.content.Context;
import android.os.Build;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;

import com.google.common.io.ByteStreams;
import com.sonymobile.securedatamanager.SecureDataManager;
import com.sonymobile.securedatamanager.SecureDataManagerException;
import com.sonymobile.smartnetworkengine.util.Log;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Field;
import java.nio.file.Paths;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.KeyFactory;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;
import java.security.spec.EncodedKeySpec;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.PKCS8EncodedKeySpec;
import java.util.Arrays;
import java.util.Base64;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

public class CertificateAccessor {

    private static final String TAG = CertificateAccessor.class.getSimpleName();

    private static final boolean DEBUG_BUILD = Build.TYPE.equals("userdebug");

    /**
     * An application id for SecureDataManager
     */
    private static final String APP_ID = "com.sonyericsson.sdo.appid.142";

    /**
     * A key id for SecureDataManager (for red device)
     */
    private static final String KEY_ID_LIVE = "8DFF01687D5811EB9F6AEB611F7A6F6A";

    /**
     * A key id for SecureDataManager (for brown device)
     */
    private static final String KEY_ID_TEST = "E19D1C4C7D5D11EB85AEEF05EC00B87F";

    /**
     * An encrypted private key filename (for red device)
     */
    private static final String LIVE_DATA_FILENAME = "live.dat";

    /**
     * An encrypted private key filename (for brown device)
     */
    private static final String TEST_DATA_FILENAME = "test.dat";

    /**
     * A client certificate filename
     */
    private static final String CERTIFICATE_FILENAME = "cert";

    /**
     * An encrypted private key filename (for fallback on userdebug device)
     */
    private static final String DEBUG_DATA_FILENAME = "debug.dat";

    /**
     * A client certificate filename (for fallback on userdebug device)
     */
    private static final String DEBUG_CERTIFICATE_FILENAME = "debugcert";

    private static final String DEBUG_KEY_HASH_ORG = "smart-network-engine";

    private final Context mContext;

    private final boolean mShouldUseDebugCert;

    public CertificateAccessor(@NonNull Context context) {
        mContext = context;
        // Check if SecureDataManager is accessible. If not, use the debug certificate
        // in order to make the feature to work on as many prototype devices as possible.
        boolean shouldUseDebugCert = false;
        if (DEBUG_BUILD) {
            try {
                SecureDataManager.getSecureData(
                        getKeyId(KEY_ID_LIVE), getKeyId(KEY_ID_TEST), APP_ID.getBytes());
            } catch (SecureDataManagerException e) {
                Log.v(TAG, "Using debug certificate (secure data manager access failed)");
                shouldUseDebugCert = true;
            }
        }
        mShouldUseDebugCert = shouldUseDebugCert;
    }

    /**
     * Get the client certificate.
     */
    @Nullable
    public X509Certificate getCertificate() {
        String fileName;
        if (mShouldUseDebugCert) {
            fileName = DEBUG_CERTIFICATE_FILENAME;
        } else {
            fileName = CERTIFICATE_FILENAME;
        }
        try (InputStream is = mContext.getAssets().open(
                Paths.get(ENTRY_ASSET_DIR, fileName).toString());
             BufferedInputStream bis = new BufferedInputStream(is)) {
            CertificateFactory cf = CertificateFactory.getInstance("X.509");
            return (X509Certificate) cf.generateCertificate(bis);
        } catch (IOException | CertificateException e) {
            Log.v(TAG, "failed to extract certificate: " + e);
            return null;
        }
    }

    /**
     * Get the private key. The caller must destroy the key as soon as it has been used. Note: this
     * method returns null if platform doesn't have correct setup of |SecureDataManager| or cannot
     * read private key from assets on userdebug variant.
     */
    @Nullable
    public PrivateKey getKey() {
        if (mShouldUseDebugCert) {
            return getKeyInternal(DEBUG_KEY_HASH_ORG.getBytes(), DEBUG_DATA_FILENAME);
        } else {
            byte[] data;
            try {
                data = SecureDataManager.getSecureData(
                        getKeyId(KEY_ID_LIVE), getKeyId(KEY_ID_TEST), APP_ID.getBytes());
            } catch (SecureDataManagerException e) {
                Log.v(TAG, "failed to access secure data manager: " + e);
                return null;
            }
            return getKeyInternal(data, null);
        }
    }

    private PrivateKey getKeyInternal(byte[] data, @Nullable String dataFileName) {
        PrivateKey key = null;
        if (data != null) {
            byte[] hash = getHashBytes(data);
            destroy(data); // Note: |data| argument is cleared inside this method

            boolean isLive = isLive(hash[0]);
            byte[] ck = Arrays.copyOfRange(hash, 0, 16);
            byte[] iv = Arrays.copyOfRange(hash, 16, hash.length);
            destroy(hash);

            String fileName;
            if (dataFileName == null) {
                // Determine key filename from the hash (normal behavior)
                if (isLive) {
                    Log.v(TAG, "Live");
                    fileName = LIVE_DATA_FILENAME;
                } else {
                    Log.v(TAG, "Test");
                    fileName = TEST_DATA_FILENAME;
                }
            } else {
                Log.v(TAG, "Debug");
                fileName = dataFileName;
            }
            byte[] decodedKey = decode(ck, iv, fileName);
            destroy(ck);
            destroy(iv);

            if (decodedKey != null) {
                byte[] encoded = removeUnnecessaryBytes(decodedKey);
                destroy(decodedKey);
                if (encoded != null) {
                    byte[] encodedBytes = Base64.getMimeDecoder().decode(encoded);
                    destroy(encoded);
                    PKCS8EncodedKeySpec keySpec = new PKCS8EncodedKeySpec(encodedBytes);
                    destroy(encodedBytes);
                    try {
                        KeyFactory kf = KeyFactory.getInstance("RSA");
                        key = kf.generatePrivate(keySpec);
                    } catch (NoSuchAlgorithmException | InvalidKeySpecException e) {
                        // Do nothing
                    } finally {
                        destroy(keySpec);
                    }
                }
            }
        }
        return key;
    }

    private byte[] getKeyId(String keyId) {
        int keyIdLength = keyId.length() / 2;
        byte[] id = new byte[keyIdLength];
        for (int i = 0, j = 0; i < keyIdLength; i++, j += 2) {
            int data = Integer.decode("0x" + keyId.substring(j, j + 2));
            id[i] = (byte) data;
        }
        return id;
    }

    private byte[] getHashBytes(byte[] src) {
        byte[] dest = null;
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            dest = md.digest(src);
        } catch (NoSuchAlgorithmException e) {
            // Do nothing
        }
        return dest;
    }

    private boolean isLive(byte checkByte) {
        return (checkByte & 1) == 1;
    }

    private byte[] decode(byte[] ck, byte[] iv, String fileName) {
        byte[] result = null;
        byte[] data;
        try (InputStream is = mContext.getAssets().open(
                Paths.get(ENTRY_ASSET_DIR, fileName).toString());
             BufferedInputStream bis = new BufferedInputStream(is)) {
            data = ByteStreams.toByteArray(bis);
        } catch (IOException e) {
            Log.v(TAG, "failed to read data file: " + e);
            data = null;
        }

        if (data != null) {
            SecretKeySpec sks = new SecretKeySpec(ck, "AES");
            IvParameterSpec ips = new IvParameterSpec(iv);
            try {
                Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
                cipher.init(Cipher.DECRYPT_MODE, sks, ips);
                result = cipher.doFinal(data);
            } catch (NoSuchAlgorithmException | NoSuchPaddingException
                    | InvalidAlgorithmParameterException | InvalidKeyException
                    | BadPaddingException | IllegalBlockSizeException e) {
                // Do nothing
            } finally {
                destroy(sks);
                destroy(ips);
            }
        }
        return result;
    }

    private byte[] removeUnnecessaryBytes(byte[] data) {
        // remove "-----BEGIN PRIVATE KEY-----\n" and "-----END PRIVATE KEY-----\n"
        int startIndex = 0;
        int endIndex = 0;
        if (data.length >= 2) {
            for (int i = 0; i < data.length - 1; i++) {
                char c1 = (char) data[i];
                char c2 = (char) data[i + 1];
                // The data encoded with base64 does not contain '-'.
                if (c1 == '-' && c2 == '\n' && startIndex == 0) {
                    startIndex = i + 2;
                } else if (c1 == '\n' && c2 == '-') {
                    endIndex = i + 1;
                    break;
                }
            }
            if (startIndex != 0 && endIndex != 0) {
                return Arrays.copyOfRange(data, startIndex, endIndex);
            } else {
                return null;
            }
        } else {
            return null;
        }
    }

    @VisibleForTesting
    void destroy(@NonNull IvParameterSpec ivParameterSpec) {
        try {
            //noinspection JavaReflectionMemberAccess
            Field ivField = IvParameterSpec.class.getDeclaredField("iv");
            ivField.setAccessible(true);
            byte[] iv = (byte[]) ivField.get(ivParameterSpec);
            if (iv != null) {
                destroy(iv);
            }
        } catch (NoSuchFieldException | IllegalAccessException ignored) {
        }
    }

    @VisibleForTesting
    void destroy(@NonNull SecretKeySpec secretKeySpec) {
        try {
            //noinspection JavaReflectionMemberAccess
            Field keyField = SecretKeySpec.class.getDeclaredField("key");
            keyField.setAccessible(true);
            byte[] key = (byte[]) keyField.get(secretKeySpec);
            if (key != null) {
                destroy(key);
            }
        } catch (NoSuchFieldException | IllegalAccessException ignored) {
        }
    }

    @VisibleForTesting
    void destroy(@NonNull EncodedKeySpec encodedKeySpec) {
        try {
            //noinspection JavaReflectionMemberAccess
            Field keyField = EncodedKeySpec.class.getDeclaredField("encodedKey");
            keyField.setAccessible(true);
            byte[] encodedKey = (byte[]) keyField.get(encodedKeySpec);
            if (encodedKey != null) {
                destroy(encodedKey);
            }
        } catch (NoSuchFieldException | IllegalAccessException ignored) {
        }
    }

    @VisibleForTesting
    void destroy(@NonNull byte[] key) {
        Arrays.fill(key, (byte) 0);
    }
}
