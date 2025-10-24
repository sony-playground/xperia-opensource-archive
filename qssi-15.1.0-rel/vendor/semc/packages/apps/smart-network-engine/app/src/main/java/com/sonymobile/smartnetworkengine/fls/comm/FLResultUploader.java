/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.comm;

import static com.sony.fl.pb.TaskInfo.PBTaskInfo;
import static com.sony.fl.pb.TaskInfo.TaskType;
import static com.sonymobile.smartnetworkengine.Constants.FLS_EVALUATION_UPLOAD_API_ENDPOINT_URL_GENERATOR;
import static com.sonymobile.smartnetworkengine.Constants.FLS_TRAINING_UPLOAD_API_ENDPOINT_URL_GENERATOR;
import static com.sonymobile.smartnetworkengine.Constants.PROP_FLS_SERVER_ENV;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.Network;
import android.os.SystemProperties;

import androidx.annotation.NonNull;
import androidx.annotation.VisibleForTesting;

import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.FLTask;
import com.sonymobile.smartnetworkengine.util.Log;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Path;
import java.security.KeyPair;
import java.security.PrivateKey;
import java.security.cert.X509Certificate;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

import okhttp3.MediaType;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;
import okhttp3.tls.HandshakeCertificates;
import okhttp3.tls.HeldCertificate;

/**
 * This is an uploader of the training / evaluation result to server-side.
 * <p>
 * These API's are not thread safe and should only be used from the FL state machine thread.
 */
public class FLResultUploader {

    private final ConnectivityManager mConnectivityManager;

    @VisibleForTesting
    /* private */ final ExecutorService mExecutorService;

    private volatile boolean mUploading;

    public FLResultUploader(@NonNull Context context) {
        mConnectivityManager = (ConnectivityManager) context.getSystemService(
                Context.CONNECTIVITY_SERVICE);
        mExecutorService = Executors.newSingleThreadExecutor();
    }

    public void upload(@NonNull FLTask flTask, @NonNull Path uploadDataPath,
            @NonNull StatusListener listener, @NonNull X509Certificate clientCertificate,
            @NonNull PrivateKey privateKey, @NonNull Network network) {
        if (mUploading) {
            throw new IllegalStateException("upload is already in progress");
        }
        PBTaskInfo pbTaskInfo = flTask.getTaskInfo();
        if (pbTaskInfo.getTaskType() != TaskType.Train
                && pbTaskInfo.getTaskType() != TaskType.Evaluation) {
            throw new IllegalStateException("Unexpected task type: " + pbTaskInfo.getTaskType());
        }
        // Binds the current process to network. This affects all sockets newly created
        // inside the process, which should be no problem for our use cases.
        // TODO: consider Builder#socketFactory in OkHttp
        // TODO: handle return value of bindProcessToNetwork
        mConnectivityManager.bindProcessToNetwork(network);
        mUploading = true;
        mExecutorService.execute(new FLUploadTask(clientCertificate, privateKey,
                pbTaskInfo, uploadDataPath, new StatusListener() {
            @Override
            public void onSuccess() {
                mUploading = false;
                listener.onSuccess();
            }

            @Override
            public void onFailure(boolean retryable) {
                mUploading = false;
                listener.onFailure(retryable);
            }
        }));
    }

    static class FLUploadTask implements Runnable {

        private static final String TAG = FLUploadTask.class.getSimpleName();

        private static final MediaType OCTET_STREAM = MediaType.parse("application/octet-stream");

        private static final String FL_ID_HEADER_NAME = "X-Sne-Fl-Id";

        private static final String TASK_ID_HEADER_NAME = "X-Sne-Task-Id";

        private static final String APP_ID_HEADER_NAME = "X-Sne-App-Id";

        private final X509Certificate mClientCertificate;

        private final PrivateKey mPrivateKey;

        private final PBTaskInfo mPBTaskInfo;

        private final Path mUploadDataPath;

        private final StatusListener mListener;

        FLUploadTask(@NonNull X509Certificate clientCertificate, @NonNull PrivateKey privateKey,
                @NonNull PBTaskInfo pbTaskInfo, @NonNull Path uploadDataPath,
                @NonNull StatusListener listener) {
            mClientCertificate = clientCertificate;
            mPrivateKey = privateKey;
            mPBTaskInfo = pbTaskInfo;
            mUploadDataPath = uploadDataPath;
            mListener = listener;
        }

        @Override
        public void run() {
            // Need to make sure that callback is always invoked so let's catch runtime
            // exception here, because unexpected runtime exception might happen.
            try {
                runInternal();
            } catch (RuntimeException e) {
                Log.w(TAG, "unexpected runtime exception happened: " + e);
                mListener.onFailure(false);
            }
        }

        private void runInternal() {
            // 1. Create zip file to be uploaded in body
            byte[] zipContent;
            try (ByteArrayOutputStream baos = new ByteArrayOutputStream();
                 ZipOutputStream zipos = new ZipOutputStream(baos)) {
                // Create zip structure
                addDirectoryToZip(mUploadDataPath, zipos, mUploadDataPath);
                // To byte array
                zipos.close();
                zipContent = baos.toByteArray();
            } catch (IOException e) {
                Log.w(TAG, "exception happened while creating content: " + e);
                mListener.onFailure(false);
                return;
            }

            // 2. Upload the content to server
            RequestBody body = RequestBody.create(OCTET_STREAM, zipContent);
            Request request = new Request.Builder()
                    .url(getUploadApiEndpointUrl(mPBTaskInfo))
                    .header(FL_ID_HEADER_NAME, mPBTaskInfo.getFLID())
                    .header(TASK_ID_HEADER_NAME, mPBTaskInfo.getTaskID())
                    .header(APP_ID_HEADER_NAME, mPBTaskInfo.getAppID())
                    .post(body)
                    .build();

            HeldCertificate clientCertificate = new HeldCertificate(
                    new KeyPair(null, mPrivateKey), mClientCertificate);
            HandshakeCertificates handshakeCertificates = new HandshakeCertificates.Builder()
                    // for TLS "server" authentication
                    .addPlatformTrustedCertificates()
                    // for TLS "client" authentication
                    .heldCertificate(clientCertificate)
                    .build();

            OkHttpClient client = OkHttpClientFactory.getOkHttpClient().newBuilder()
                    .sslSocketFactory(handshakeCertificates.sslSocketFactory(),
                            handshakeCertificates.trustManager())
                    .build();
            try (Response response = client.newCall(request).execute()) {
                if (response.isSuccessful()) {
                    mListener.onSuccess();
                } else {
                    Log.w(TAG, "unsuccessful status code received: " + response.code());
                    boolean retryable = response.code() == 429 // Too Many Requests
                            || (500 <= response.code() && response.code() <= 599); // 5xx server err
                    mListener.onFailure(retryable);
                }
            } catch (IOException e) {
                Log.w(TAG, "exception happened while communicating with server: " + e);
                mListener.onFailure(true);
            }
        }

        private void addDirectoryToZip(Path srcDir, ZipOutputStream destZip, Path baseDir)
                throws IOException {
            File[] files = srcDir.toFile().listFiles();
            if (files == null) {
                throw new IllegalStateException("unable to list files: " + srcDir);
            }
            for (File file : files) {
                Path relativePath = baseDir.relativize(file.toPath());
                if (file.isDirectory()) {
                    destZip.putNextEntry(new ZipEntry(relativePath.toString() + "/"));
                    addDirectoryToZip(file.toPath(), destZip, baseDir); // recursive call
                } else {
                    destZip.putNextEntry(new ZipEntry(relativePath.toString()));
                    try (FileInputStream fis = new FileInputStream(file)) {
                        fis.transferTo(destZip);
                    }
                }
            }
        }

        private String getUploadApiEndpointUrl(PBTaskInfo pbTaskInfo) {
            String env = SystemProperties.get(PROP_FLS_SERVER_ENV, "prod");
            if (!env.equalsIgnoreCase("prod")) {
                // Change server environment to stage/dev.
                env = "." + env;
            } else {
                env = ""; // for prod
            }
            if (pbTaskInfo.getTaskType() == TaskType.Train) {
                return FLS_TRAINING_UPLOAD_API_ENDPOINT_URL_GENERATOR.apply(env);
            } else if (pbTaskInfo.getTaskType() == TaskType.Evaluation) {
                return FLS_EVALUATION_UPLOAD_API_ENDPOINT_URL_GENERATOR.apply(env);
            } else {
                throw new IllegalStateException("Unexpected task type");
            }
        }
    }

    /**
     * Interface for callback invocation on upload event.
     */
    public interface StatusListener {
        /**
         * Invoked when the upload has been successfully completed.
         */
        void onSuccess();

        /**
         * Invoked when there was an error performing the upload.
         *
         * @param retryable True if this is not permanent error, false otherwise.
         */
        void onFailure(boolean retryable);
    }
}
