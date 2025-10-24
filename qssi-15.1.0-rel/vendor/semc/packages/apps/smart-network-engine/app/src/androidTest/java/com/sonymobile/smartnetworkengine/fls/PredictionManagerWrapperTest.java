/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls;

import static androidx.test.platform.app.InstrumentationRegistry.getInstrumentation;

import static org.junit.Assert.assertNull;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.never;
import static org.mockito.Mockito.verify;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sony.fl.PredictManager;
import com.sony.fl.PredictManager.PredictResult;
import com.sony.fl.tensor.TensorMap;
import com.sonymobile.smartnetworkengine.fls.FLSystemService.PredictManagerWrapper;

import org.apache.commons.io.file.PathUtils;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

import java.io.IOException;
import java.nio.file.Path;

@RunWith(AndroidJUnit4.class)
public class PredictionManagerWrapperTest {

    private static final String DUMMY_DATA_DIR = "predict_dummy";

    private static final String DUMMY_DATA_DIR2 = "predict_dummy2";

    private Path mDummyDataDir;

    private Path mDummyDataDir2;

    private PredictManagerWrapper mPredictManagerWrapper;

    private PredictManagerWrapper mPredictManagerWrapper2;

    @Mock
    private PredictManager mMockPredictManager;

    @Mock
    private PredictManager mMockPredictManager2;

    @SuppressWarnings("ResultOfMethodCallIgnored")
    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);
        // Setup the directories for FL library
        mDummyDataDir = getInstrumentation().getTargetContext().getFilesDir().toPath().resolve(
                DUMMY_DATA_DIR);
        mDummyDataDir2 = getInstrumentation().getTargetContext().getFilesDir().toPath().resolve(
                DUMMY_DATA_DIR2);
        mDummyDataDir.toFile().mkdirs();
        mDummyDataDir2.toFile().mkdirs();
        // Setup 2 wrapper instances
        mPredictManagerWrapper = new PredictManagerWrapper("dummy_app_id", mDummyDataDir);
        mPredictManagerWrapper2 = new PredictManagerWrapper("dummy_app_id2", mDummyDataDir2);
        mPredictManagerWrapper.mPredictManager = mMockPredictManager;
        mPredictManagerWrapper2.mPredictManager = mMockPredictManager2;
    }

    @After
    public void tearDown() throws IOException {
        PathUtils.deleteDirectory(mDummyDataDir);
        PathUtils.deleteDirectory(mDummyDataDir2);
    }

    @Test
    public void testSetPredictionEnabled() {
        //Prepare
        TensorMap tensorMap = TensorMap.newInstance();

        // Action
        PredictResult result = mPredictManagerWrapper.predict(tensorMap);
        PredictResult result2 = mPredictManagerWrapper2.predict(tensorMap);

        // Check (prediction is disabled as default)
        assertNull(result);
        assertNull(result2);
        verify(mMockPredictManager, never()).predict(any());
        verify(mMockPredictManager2, never()).predict(any());

        // Action
        PredictManagerWrapper.setEntirePredictionEnabled(true);
        mPredictManagerWrapper.predict(tensorMap);
        mPredictManagerWrapper2.predict(tensorMap);

        // Check
        verify(mMockPredictManager).predict(any());
        verify(mMockPredictManager2).predict(any());

        // Action
        PredictManagerWrapper.setEntirePredictionEnabled(false);
        result = mPredictManagerWrapper.predict(tensorMap);
        result2 = mPredictManagerWrapper2.predict(tensorMap);

        // Check
        assertNull(result);
        assertNull(result2);
        verify(mMockPredictManager).predict(any()); // not called
        verify(mMockPredictManager2).predict(any()); // not called
    }
}
