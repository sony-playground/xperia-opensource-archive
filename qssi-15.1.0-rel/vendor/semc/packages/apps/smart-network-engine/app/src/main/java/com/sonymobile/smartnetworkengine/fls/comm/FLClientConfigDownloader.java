/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.comm;

import static com.sonymobile.smartnetworkengine.Constants.FLS_APP_ID_LIST;
import static com.sonymobile.smartnetworkengine.Constants.FLS_CDN_BASE_URL_GENERATOR;
import static com.sonymobile.smartnetworkengine.Constants.FLS_CDN_CLIENT_CONFIG_FILENAME;
import static com.sonymobile.smartnetworkengine.Constants.FLS_CLIENT_CONFIG_MAX_SIZE;
import static com.sonymobile.smartnetworkengine.Constants.FLS_TASK_DATA_FILE_MAX_SIZE;
import static com.sonymobile.smartnetworkengine.Constants.PROP_FLS_SERVER_ENV;
import static com.sonymobile.smartnetworkengine.Constants.PROP_FLS_TEST_CLIENT_CONFIG_FILE;
import static com.sonymobile.smartnetworkengine.Constants.SETTINGS_FLS_CLIENT_CONFIG_DEVICE_ID;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.Network;
import android.os.Build;
import android.os.SystemProperties;
import android.provider.Settings;
import android.text.TextUtils;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.annotation.VisibleForTesting;

import com.google.gson.GsonBuilder;
import com.google.protobuf.InvalidProtocolBufferException;
import com.sonymobile.smartnetworkengine.R;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.ClientConfig;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.ClientConfigRoot;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.FLTask;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.TargetDevice;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.TargetDevice.DeviceType;
import com.sonymobile.smartnetworkengine.util.Log;

import java.io.IOException;
import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.ListIterator;
import java.util.Map;
import java.util.Optional;
import java.util.Random;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.function.Predicate;
import java.util.regex.Pattern;
import java.util.regex.PatternSyntaxException;

import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;
import okhttp3.ResponseBody;

/**
 * This is a downloader of the Federated-Learning system's client configuration from server-side.
 * <p>
 * These API's are not thread safe and should only be used from the FL state machine thread.
 */
public class FLClientConfigDownloader {

    private static final boolean DEBUG_BUILD = Build.TYPE.equals("userdebug");

    private final ConnectivityManager mConnectivityManager;

    @VisibleForTesting
    /* private */ final ExecutorService mExecutorService;

    @NonNull
    private Context mContext;

    private volatile boolean mDownloading;

    public FLClientConfigDownloader(@NonNull Context context) {
        mConnectivityManager = (ConnectivityManager) context.getSystemService(
                Context.CONNECTIVITY_SERVICE);
        mContext = context;
        mExecutorService = Executors.newSingleThreadExecutor();
    }

    public void download(@Nullable ClientConfig currentClientConfig,
            @Nullable String skippedClientConfigHash, @NonNull StatusListener listener,
            @NonNull Network network) {
        if (mDownloading) {
            throw new IllegalStateException("download is already in progress");
        }
        // Binds the current process to network. This affects all sockets newly created
        // inside the process, which should be no problem for our use cases.
        // TODO: consider Builder#socketFactory in OkHttp
        // TODO: handle return value of bindProcessToNetwork
        mConnectivityManager.bindProcessToNetwork(network);
        mDownloading = true;
        mExecutorService.execute(
                new FLDownloadTask(mContext, currentClientConfig, skippedClientConfigHash,
                        new StatusListener() {
                            @Override
                            public void onSuccess(@NonNull ClientConfig clientConfig,
                                    @Nullable Map<FLTask, byte[]> taskDataMap) {
                                mDownloading = false;
                                listener.onSuccess(clientConfig, taskDataMap);
                            }

                            @Override
                            public void onSkip(@Nullable String clientConfigHash) {
                                mDownloading = false;
                                listener.onSkip(clientConfigHash);
                            }

                            @Override
                            public void onFailure() {
                                mDownloading = false;
                                listener.onFailure();
                            }
                        }));
    }

    static class FLDownloadTask implements Runnable {

        private static final String TAG = FLDownloadTask.class.getSimpleName();

        @NonNull
        private final Context mContext;

        @Nullable
        private final ClientConfig mCurrentClientConfig;

        @Nullable
        private final String mSkippedClientConfigHash;

        @NonNull
        private final StatusListener mListener;

        private static final Random RANDOM_INSTANCE = new Random();

        FLDownloadTask(@NonNull Context context, @Nullable ClientConfig currentClientConfig,
                @Nullable String skippedClientConfigHash, @NonNull StatusListener listener) {
            mContext = context;
            mCurrentClientConfig = currentClientConfig;
            mSkippedClientConfigHash = skippedClientConfigHash;
            mListener = listener;
        }

        @Override
        public void run() {
            // Need to make sure that callback is always invoked so let's catch runtime
            // exception here, because unexpected runtime exception might happen.
            try {
                runInternal();
            } catch (RuntimeException e) {
                Log.e(TAG, "unexpected runtime exception happened: " + e);
                mListener.onFailure();
            }
        }

        private void runInternal() {
            // 1. Fetch client configuration bundle first
            // TODO: ETag should be utilized?
            Request request = new Request.Builder()
                    .url(getClientConfigurationUrl())
                    .build();

            byte[] contentByte = fetchFromServer(request, FLS_CLIENT_CONFIG_MAX_SIZE);
            if (contentByte == null) {
                mListener.onFailure();
                return;
            }

            ClientConfigRoot clientConfigRoot;
            try {
                clientConfigRoot = ClientConfigRoot.parseFrom(contentByte);
            } catch (InvalidProtocolBufferException e) {
                Log.w(TAG, "failed to deserialize input object: " + e);
                mListener.onFailure();
                return;
            }

            if (DEBUG_BUILD) {
                // Log the deserialized downloaded data for debugging purpose
                Log.v(TAG, new GsonBuilder().setPrettyPrinting().create().toJson(clientConfigRoot));
            }

            // 2. Validate downloaded data
            try {
                FLClientConfigDataValidator.validateRoot(clientConfigRoot);
            } catch (IllegalArgumentException e) {
                Log.w(TAG, "failed to validate input object: " + e);
                mListener.onFailure();
                return;
            }

            // 3. Lookup a corresponding client configuration
            Optional<ClientConfig> clientConfigOpt;
            try {
                clientConfigOpt = clientConfigRoot.getClientConfigsList().stream()
                        .filter(targetDeviceFilter(mContext))
                        .findFirst();
            } catch (PatternSyntaxException e) {
                Log.w(TAG, "invalid syntax detected: " + e);
                mListener.onFailure();
                return;
            }
            if (!clientConfigOpt.isPresent()) {
                Log.w(TAG, "corresponding entry not found");
                mListener.onFailure();
                return;
            }
            ClientConfig clientConfig = clientConfigOpt.get();
            Log.v(TAG, "Found client config: <" + clientConfig.getConfigurationName() + ">");

            // 4. Validate corresponding clientConfig
            try {
                FLClientConfigDataValidator.validate(clientConfig, FLS_APP_ID_LIST, false);
            } catch (IllegalArgumentException e) {
                Log.w(TAG, "failed to validate corresponding clientConfig: " + e);
                mListener.onFailure();
                return;
            }

            // 5. Check there is a difference between current and downloaded client configs
            if (mCurrentClientConfig != null && Arrays.equals(mCurrentClientConfig.toByteArray(),
                    clientConfig.toByteArray())) {
                Log.v(TAG, "no new version of client config is available");
                mListener.onSkip(null);
                return;
            }

            // 6. Roll the dice and skip the client config due to device ratio.
            String hash;
            try {
                byte[] hashBytes = MessageDigest.getInstance("SHA-256").digest(
                        clientConfig.toByteArray());
                hash = new BigInteger(1, hashBytes).toString(16);
            } catch (NoSuchAlgorithmException e) {
                Log.e(TAG, "failed to find 'SHA-256' algorithm: " + e); // could never happen
                mListener.onFailure();
                return;
            }
            if (hash.equals(mSkippedClientConfigHash)) {
                Log.v(TAG, "The client config has already been decided to be skipped");
                mListener.onSkip(null);
                return;
            }
            if (clientConfig.getTargetDevice().getDeviceRatio() <
                    RANDOM_INSTANCE.nextInt(100) + 1) {
                Log.v(TAG, "skip client config since not hitting the 'device ratio' lottery");
                mListener.onSkip(hash);
                return;
            }

            // 7. Check there is a difference between current and downloaded configs under 'flTasks'
            Map<FLTask, byte[]> taskData = null;
            if (mCurrentClientConfig == null || !taskListEquals(
                    mCurrentClientConfig.getFlTasksList(), clientConfig.getFlTasksList())) {
                Log.v(TAG, "starting task data download (as new version is available)");
                // 8. Fetch the task data file(s)
                taskData = new HashMap<>();
                for (FLTask flTask : clientConfig.getFlTasksList()) {
                    String taskDataFile = flTask.getTaskDataFile();
                    if (!TextUtils.isEmpty(taskDataFile)) {
                        request = new Request.Builder()
                                .url(getTaskDataUrl(taskDataFile))
                                .build();

                        contentByte = fetchFromServer(request, FLS_TASK_DATA_FILE_MAX_SIZE);
                        if (contentByte == null) {
                            mListener.onFailure();
                            return;
                        }

                        // 9. Validate the task data
                        try {
                            FLClientConfigDataValidator.validateTaskData(contentByte);
                        } catch (IllegalArgumentException e) {
                            Log.w(TAG, "failed to validate input object: " + e);
                            mListener.onFailure();
                            return;
                        }

                        taskData.put(flTask, contentByte);
                    }
                }
            } else {
                Log.v(TAG, "skipping task data download (as no new version is available)");
            }

            mListener.onSuccess(clientConfig, taskData);
        }

        private byte[] fetchFromServer(Request request, int maxBodySize) {
            OkHttpClient client = OkHttpClientFactory.getOkHttpClient();
            try (Response response = client.newCall(request).execute()) {
                boolean success = response.isSuccessful();
                ResponseBody body = response.body();
                if (success && body != null) {
                    // Limit on certain size to ignore an unexpected large body
                    ResponseBody peekedBody = response.peekBody(maxBodySize + 1);
                    long contentLength = peekedBody.contentLength();
                    if (contentLength > maxBodySize) {
                        Log.w(TAG, "exceeds response body size limit");
                        return null;
                    }
                    // Check zero-length
                    if (contentLength <= 0) {
                        Log.w(TAG, "zero-length response body detected");
                        return null;
                    }
                    return peekedBody.bytes();
                }
            } catch (IOException e) {
                Log.w(TAG, "exception happened while communicating with server: " + e);
            }
            return null;
        }

        private String getClientConfigurationUrl() {
            String configPath = FLS_CDN_CLIENT_CONFIG_FILENAME;
            String testFile = SystemProperties.get(PROP_FLS_TEST_CLIENT_CONFIG_FILE,
                    mContext.getResources().getString(
                            R.string.config_fl_system_test_client_config_file));
            if (!testFile.isEmpty()) {
                // Replace client config file path to specified test file under 'test'.
                configPath = "test/" + testFile;
            }
            return FLS_CDN_BASE_URL_GENERATOR.apply(getEnvironmentParameter(), configPath);
        }

        private String getTaskDataUrl(String fileName) {
            String dataPath = fileName;
            String testFile = SystemProperties.get(PROP_FLS_TEST_CLIENT_CONFIG_FILE,
                    mContext.getResources().getString(
                            R.string.config_fl_system_test_client_config_file));
            if (!testFile.isEmpty()) {
                // Change the directory path under 'test' directory.
                dataPath = "test/" + fileName;
            }
            return FLS_CDN_BASE_URL_GENERATOR.apply(getEnvironmentParameter(), dataPath);
        }

        private String getEnvironmentParameter() {
            String env = SystemProperties.get(PROP_FLS_SERVER_ENV,
                    mContext.getResources().getString(R.string.config_fl_system_server_env));
            if (!env.equalsIgnoreCase("prod")) {
                // Change server environment to stage/dev.
                return "." + env;
            }
            return ""; // for prod
        }

        /**
         * Target device filter to find out the entry which is applicable for current device.
         *
         * @throws PatternSyntaxException If the expression's syntax in the config is invalid
         */
        private static Predicate<ClientConfig> targetDeviceFilter(Context context) {
            // 1. Build#ID     (e.g. 58.1.B.2.31) for "sw_label_regex"
            // 2. Build#TAGS   (e.g. release-keys) for "device_type"
            //     This contains platform signing configuration defined in
            //     https://source.android.com/compatibility/11/android-11-cdd.pdf
            //     -> 3.2.2. Build Parameters
            //     (i.e. indicates whether live-signed or not)
            // 3. SETTINGS_FLS_CLIENT_CONFIG_DEVICE_ID  (e.g. 123e4567-e89b-12d3-a456-426614174000)
            //      manually set uuid for "device_id"
            String devId = Settings.Global.getString(context.getContentResolver(),
                    SETTINGS_FLS_CLIENT_CONFIG_DEVICE_ID);
            return targetDeviceFilter(Build.ID, Build.TAGS, devId != null ? devId : "");
        }

        // Accept 3 args for unit testing
        @VisibleForTesting
        static Predicate<ClientConfig> targetDeviceFilter(String id, String tags, String devId) {
            return clientConfig -> {
                TargetDevice targetDevice = clientConfig.getTargetDevice();
                boolean deviceTypeMatched =
                        targetDevice.getDeviceType() == DeviceType.LIVE_AND_TEST || (
                                (targetDevice.getDeviceType() == DeviceType.LIVE) == Arrays.asList(
                                        tags.split(",")).contains("release-keys"));
                boolean deviceIdMatched = targetDevice.getDeviceIdsCount() == 0 ||
                        targetDevice.getDeviceIdsList().stream()
                                .anyMatch(s -> s.equalsIgnoreCase(devId));
                return Pattern.matches(targetDevice.getSwLabelRegex(), id) && deviceTypeMatched
                        && deviceIdMatched;
            };
        }

        // Based on |AbstractList#equals| implementation
        @VisibleForTesting
        static boolean taskListEquals(List<FLTask> a, List<FLTask> b) {
            ListIterator<FLTask> m1 = a.listIterator();
            ListIterator<FLTask> m2 = b.listIterator();
            while (m1.hasNext() && m2.hasNext()) {
                byte[] b1 = m1.next().toByteArray();
                byte[] b2 = m2.next().toByteArray();
                if (!(b1 == null ? b2 == null : Arrays.equals(b1, b2))) {
                    return false;
                }
            }
            return !(m1.hasNext() || m2.hasNext());
        }
    }

    /**
     * Interface for callback invocation on download event.
     */
    public interface StatusListener {
        /**
         * Invoked when the new version of the client config has been successfully downloaded.
         *
         * @param clientConfig the new version of the client config
         * @param taskDataMap  the task data contents (in zip file format) if there is any
         *                     difference from current version in 'flTasks' config regardless of
         *                     task data file availability (thus this may be empty map), or null if
         *                     there is no difference
         */
        void onSuccess(@NonNull ClientConfig clientConfig,
                @Nullable Map<FLTask, byte[]> taskDataMap);

        /**
         * Invoked when no new version of the client config is available or when the new version is
         * available but not hitting the 'device ratio' lottery.
         *
         * @param clientConfigHash the hash of the client config in case that not hitting the
         *                         'device ratio' lottery, null otherwise.
         */
        void onSkip(@Nullable String clientConfigHash);

        /**
         * Invoked when there was an error performing the download.
         */
        void onFailure();
    }
}
