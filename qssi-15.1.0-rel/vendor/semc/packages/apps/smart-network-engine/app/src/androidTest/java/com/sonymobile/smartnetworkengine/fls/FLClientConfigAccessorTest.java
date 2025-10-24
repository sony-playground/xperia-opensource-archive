/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls;

import static androidx.test.platform.app.InstrumentationRegistry.getInstrumentation;

import static com.sonymobile.smartnetworkengine.fls.FLClientConfigAccessor.PRESET_CONFIGURATION_NAME;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNotSame;
import static org.junit.Assert.assertSame;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.ClientConfig;
import com.sonymobile.smartnetworkengine.fls.comm.FLClientConfigData.GeneralConfiguration.OperationMode;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.MockitoAnnotations;

/**
 * Verify {@link FLClientConfigAccessor} implementation.
 */
@RunWith(AndroidJUnit4.class)
public class FLClientConfigAccessorTest {

    private FLClientConfigAccessor mAccessor;

    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);
        mAccessor = newAccessorInstance();
    }

    @After
    public void tearDown() {
        getSharedPreferences().edit().clear().apply();
    }

    @Test
    public void testGet() {
        ClientConfig config = createConfig("test1");
        newAccessorInstance().saveToEditor(config).apply();

        // Action
        ClientConfig fetchedConfig = mAccessor.get();

        // Check
        assertEquals(config.getConfigurationName(), fetchedConfig.getConfigurationName());
    }

    @Test
    public void testGet_default() {
        // Action
        ClientConfig config = mAccessor.get();

        // Check
        assertNotNull(config);
        assertEquals(PRESET_CONFIGURATION_NAME, config.getConfigurationName());
        assertEquals(OperationMode.SERVER_ACCESS_ONLY,
                config.getGeneralConfiguration().getOperationMode());
    }

    @Test
    public void testSaveToEditor() {
        // Action
        mAccessor.saveToEditor(createConfig("test1")).apply();

        // Check
        assertEquals("test1", newAccessorInstance().get().getConfigurationName());

        // Action (Overwrite)
        mAccessor.saveToEditor(createConfig("test2")).apply();

        // Check
        assertEquals("test2", newAccessorInstance().get().getConfigurationName());
    }

    @Test
    public void testCaching() {
        ClientConfig config = createConfig("test1");
        newAccessorInstance().saveToEditor(config).apply();

        // Action
        ClientConfig fetchedConfig = mAccessor.get();

        // Check
        assertNotSame(config, fetchedConfig);
        assertEquals("test1", fetchedConfig.getConfigurationName());

        // Action (cache)
        ClientConfig fetchedConfig2 = mAccessor.get();

        // Check
        assertSame(fetchedConfig, fetchedConfig2);

        // Action (clear cache)
        mAccessor.clearCache();
        fetchedConfig2 = mAccessor.get();

        // Check
        assertNotSame(fetchedConfig, fetchedConfig2);
        assertEquals("test1", fetchedConfig2.getConfigurationName());

        // Action (pre-update)
        config = createConfig("test2");
        Editor editor = mAccessor.saveToEditor(config);
        fetchedConfig = mAccessor.get();

        // Check
        assertNotSame(config, fetchedConfig);
        assertEquals("test1", fetchedConfig.getConfigurationName());
        assertEquals("test1", newAccessorInstance().get().getConfigurationName());

        // Action (update)
        editor.apply();
        mAccessor.clearCache();
        fetchedConfig2 = mAccessor.get();

        // Check
        assertNotSame(fetchedConfig, fetchedConfig2);
        assertEquals("test2", fetchedConfig2.getConfigurationName());
        assertEquals("test2", newAccessorInstance().get().getConfigurationName());
    }

    private ClientConfig createConfig(String configurationName) {
        return FLClientConfigData.ClientConfig.newBuilder()
                .setConfigurationName(configurationName)
                .build();
    }

    // This method is typically used when config caching in |mAccessor| needs to be avoided
    private FLClientConfigAccessor newAccessorInstance() {
        return new FLClientConfigAccessor(getSharedPreferences());
    }

    private SharedPreferences getSharedPreferences() {
        return getInstrumentation().getTargetContext().getSharedPreferences(
                FLClientConfigAccessorTest.class.getSimpleName(), Context.MODE_PRIVATE);
    }
}
