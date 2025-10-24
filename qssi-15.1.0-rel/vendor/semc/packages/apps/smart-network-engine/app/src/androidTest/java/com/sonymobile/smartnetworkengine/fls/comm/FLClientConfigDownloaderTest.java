/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls.comm;

import static androidx.test.platform.app.InstrumentationRegistry.getInstrumentation;

import static com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.ClientConfig;

import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.TargetDevice;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.TargetDevice.DeviceType;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigDownloader.FLDownloadTask;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.MockitoAnnotations;

import java.util.Arrays;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.TimeUnit;
import java.util.function.Predicate;
import java.util.regex.PatternSyntaxException;

/**
 * Verify {@link FLClientConfigDownloader} implementation.
 */
@RunWith(AndroidJUnit4.class)
public class FLClientConfigDownloaderTest {

    private FLClientConfigDownloader mDownloader;

    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);
        mDownloader = new FLClientConfigDownloader(getInstrumentation().getTargetContext());
    }

    @After
    public void tearDown() {
        shutdownAndAwaitTermination(mDownloader.mExecutorService);
    }

    @Test
    public void testJustCallDownload() {
        mDownloader.download(null, null, new FLClientConfigDownloader.StatusListener() {
            @Override
            public void onSuccess(@NonNull FLClientConfigData.ClientConfig clientConfig,
                    @Nullable Map<FLClientConfigData.FLTask, byte[]> taskDataMap) {
            }

            @Override
            public void onSkip(@Nullable String clientConfigHash) {
            }

            @Override
            public void onFailure() {
            }
        }, null /*TODO: non-null value should be passed*/);
    }

/*
    @Test
    public void testTargetDeviceFilter() {
        Predicate<ClientConfig> filter = FLDownloadTask.targetDeviceFilter(
                // Device info
                "SO-52A",
                "58.1.B.2.31",
                "release-keys");

        TargetDevice targetDevice = TargetDevice.newBuilder()
                .setProductNameRegex("SO-52A") // One specific device match
                .setSwLabelRegex(".*")
                .setDeviceType(DeviceType.LIVE)
                .build();

        // Action and Check
        assertTrue(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        targetDevice = targetDevice.toBuilder()
                .setProductNameRegex("SOG02|SO-52A") // Multiple device match
                .setSwLabelRegex(".*")
                .build();

        // Action and Check
        assertTrue(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        targetDevice = targetDevice.toBuilder()
                .setProductNameRegex(".*")
                .setSwLabelRegex("58\\.1\\..+") // "58.1." label pattern match
                .build();

        // Action and Check
        assertTrue(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        targetDevice = targetDevice.toBuilder()
                .setProductNameRegex("SO-52A")  // One specific device match
                .setSwLabelRegex("58\\.1\\..+") // "58.1." label pattern match
                .build();

        // Action and Check
        assertTrue(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        targetDevice = targetDevice.toBuilder()
                .setProductNameRegex("SO-52A")  // One specific device match
                .setSwLabelRegex("58\\.0\\..+") // "58.0." label pattern match (no match)
                .build();

        // Action and Check
        assertFalse(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        targetDevice = targetDevice.toBuilder()
                .setProductNameRegex("SOG02")   // One specific device match (no match)
                .setSwLabelRegex("58\\.1\\..+") // "58.1." label pattern match
                .build();

        // Action and Check
        assertFalse(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        targetDevice = targetDevice.toBuilder()
                .setProductNameRegex(".*") // wildcard
                .setSwLabelRegex(".*")     // wildcard
                .build();

        // Action and Check
        assertTrue(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));
    }
*/

    @Test
    public void testTargetDeviceFilter_deviceType() {
        Predicate<ClientConfig> filter = FLDownloadTask.targetDeviceFilter(
                // Device info (production)
                "58.1.B.2.31",
                "release-keys",
                "");

        TargetDevice targetDevice = TargetDevice.newBuilder()
                .setSwLabelRegex(".*")
                .setDeviceType(DeviceType.LIVE)
                .build();

        // Action and Check
        assertTrue(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        targetDevice = targetDevice.toBuilder()
                .setDeviceType(DeviceType.TEST)
                .build();

        // Action and Check
        assertFalse(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        targetDevice = targetDevice.toBuilder()
                .setDeviceType(DeviceType.LIVE_AND_TEST)
                .build();

        // Action and Check
        assertTrue(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        filter = FLDownloadTask.targetDeviceFilter(
                // Device info (non-production)
                "58.1.B.2.31",
                "dev-keys",
                "");

        targetDevice = TargetDevice.newBuilder()
                .setSwLabelRegex(".*")
                .setDeviceType(DeviceType.LIVE)
                .build();

        // Action and Check
        assertFalse(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        targetDevice = targetDevice.toBuilder()
                .setDeviceType(DeviceType.TEST)
                .build();

        // Action and Check
        assertTrue(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        targetDevice = targetDevice.toBuilder()
                .setDeviceType(DeviceType.LIVE_AND_TEST)
                .build();

        // Action and Check
        assertTrue(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        filter = FLDownloadTask.targetDeviceFilter(
                // Device info (multiple tags)
                "58.1.B.2.31",
                "something,release-keys", // multiple tags
                "");

        targetDevice = TargetDevice.newBuilder()
                .setSwLabelRegex(".*")
                .setDeviceType(DeviceType.LIVE)
                .build();

        // Action and Check
        assertTrue(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        targetDevice = targetDevice.toBuilder()
                .setDeviceType(DeviceType.TEST)
                .build();

        // Action and Check
        assertFalse(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        targetDevice = targetDevice.toBuilder()
                .setDeviceType(DeviceType.LIVE_AND_TEST)
                .build();

        // Action and Check
        assertTrue(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));
    }

    @Test
    public void testTargetDeviceFilter_deviceId() {
        Predicate<ClientConfig> filter = FLDownloadTask.targetDeviceFilter(
                // Device info (w/o device id)
                "58.1.B.2.31",
                "release-keys",
                "");

        TargetDevice targetDevice = TargetDevice.newBuilder()
                .setSwLabelRegex(".*")
                .setDeviceType(DeviceType.LIVE_AND_TEST)
                .build();

        // Action and Check
        assertTrue(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        targetDevice = targetDevice.toBuilder()
                .addDeviceIds("50789176-9ad6-492d-99e6-123456789abc")
                .build();

        // Action and Check
        assertFalse(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        filter = FLDownloadTask.targetDeviceFilter(
                // Device info (w/ device id)
                "58.1.B.2.31",
                "release-keys",
                "50789176-9ad6-492d-99e6-123456789abc");

        targetDevice = TargetDevice.newBuilder()
                .setSwLabelRegex(".*")
                .setDeviceType(DeviceType.LIVE_AND_TEST)
                .build();

        // Action and Check
        assertTrue(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        targetDevice = targetDevice.toBuilder()
                .addDeviceIds("50789176-9ad6-492d-99e6-123456789abc")
                .build();

        // Action and Check
        assertTrue(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        targetDevice = targetDevice.toBuilder()
                .clearDeviceIds()
                // last character changed from 'c' to '0'
                .addDeviceIds("50789176-9ad6-492d-99e6-123456789ab0")
                .build();

        // Action and Check
        assertFalse(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        targetDevice = targetDevice.toBuilder()
                .clearDeviceIds()
                .addAllDeviceIds(Arrays.asList("abc", "50789176-9ad6-492d-99e6-123456789abc"))
                .build();

        // Action and Check
        assertTrue(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));

        targetDevice = targetDevice.toBuilder()
                .clearDeviceIds()
                .addAllDeviceIds(Arrays.asList("abc", "def"))
                .build();

        // Action and Check
        assertFalse(filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build()));
    }

    @Test
    public void testTargetDeviceFilter_exception() {
        Predicate<ClientConfig> filter = FLDownloadTask.targetDeviceFilter(
                // Device info
                "58.1.B.2.31",
                "release-keys",
                "");

        TargetDevice targetDevice = TargetDevice.newBuilder()
                .setSwLabelRegex("*") // invalid syntax
                .setDeviceType(DeviceType.LIVE_AND_TEST)
                .build();

        // Action and Check
        try {
            filter.test(ClientConfig.newBuilder().setTargetDevice(targetDevice).build());
            fail();
        } catch (PatternSyntaxException ignored) {
        }
    }

    // Here is the best way to shutdown an executor service (described in the javadoc).
    private void shutdownAndAwaitTermination(ExecutorService pool) {
        pool.shutdown(); // Disable new tasks from being submitted
        try {
            // Wait a while for existing tasks to terminate
            if (!pool.awaitTermination(60, TimeUnit.SECONDS)) {
                pool.shutdownNow(); // Cancel currently executing tasks
                // Wait a while for tasks to respond to being cancelled
                if (!pool.awaitTermination(60, TimeUnit.SECONDS)) {
                    System.err.println("Pool did not terminate");
                }
            }
        } catch (InterruptedException ie) {
            // (Re-)Cancel if current thread also interrupted
            pool.shutdownNow();
            // Preserve interrupt status
            Thread.currentThread().interrupt();
        }
    }
}
