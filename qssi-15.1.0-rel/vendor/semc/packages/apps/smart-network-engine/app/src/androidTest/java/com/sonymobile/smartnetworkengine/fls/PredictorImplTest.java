/*
 * Copyright 2022 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.fls;

import static androidx.test.platform.app.InstrumentationRegistry.getInstrumentation;

import static org.junit.Assert.assertArrayEquals;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.doReturn;
import static org.mockito.Mockito.spy;

import androidx.test.ext.junit.runners.AndroidJUnit4;

import com.sony.fl.PredictManager;
import com.sony.fl.algorithm.LinearFedHLCRClient;
import com.sony.fl.algorithm.NNFedHLCRClient;
import com.sony.fl.pb.TaskInfo.ModelType;
import com.sony.fl.tensor.Tensor;
import com.sony.fl.tensor.TensorMap;
import com.sonymobile.smartnetworkengine.fls.FLSystemService.PredictManagerWrapper;
import com.sonymobile.smartnetworkengine.fls.FLSystemService.PredictorImpl;
import com.sonymobile.smartnetworkengine.fls.Predictor.PredictionResult;

import org.apache.commons.io.file.PathUtils;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.mockito.Mock;
import org.mockito.MockitoAnnotations;

import java.io.IOException;
import java.lang.reflect.Constructor;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.List;

@RunWith(AndroidJUnit4.class)
public class PredictorImplTest {

    private static final String DUMMY_DATA_DIR = "predict_dummy";

    private Path mDummyDataDir;

    private PredictManagerWrapper mPredictManagerWrapper;

    @Mock
    private PredictManager mMockPredictManager;

    @SuppressWarnings("ResultOfMethodCallIgnored")
    @Before
    public void setUp() {
        MockitoAnnotations.initMocks(this);
        // Create a wrapper instance
        mDummyDataDir = getInstrumentation().getTargetContext().getFilesDir().toPath().resolve(
                DUMMY_DATA_DIR);
        mDummyDataDir.toFile().mkdirs();
        mPredictManagerWrapper = new PredictManagerWrapper("dummy_app_id", mDummyDataDir);
        mPredictManagerWrapper.mPredictManager = mMockPredictManager;
        PredictManagerWrapper.setEntirePredictionEnabled(true);
    }

    @After
    public void tearDown() throws IOException {
        PathUtils.deleteDirectory(mDummyDataDir);
    }

    @Test
    public void testDataCollectionSessionForNNHLCR() {
        final List<List<Float>> features = Arrays.asList(
                Arrays.asList(0.1f, 0.2f, 0.3f, 0.4f, 0.5f),
                Arrays.asList(1.1f, 1.2f, 1.3f, 1.4f, 1.5f));
        final float score = 0.5f;

        TensorMap tensorMap = TensorMap.newInstance();
        tensorMap.set(NNFedHLCRClient.TENSOR_Y_PRED, Tensor.newTensor((double) score));
        PredictManager.PredictResult predictResult = newPredictResult(0, tensorMap);
        doReturn(predictResult).when(mMockPredictManager).predict(any());

        // Action (ratio is 100%)
        PredictorImpl predictor = new PredictorImpl(mPredictManagerWrapper, null);
        predictor.setModelType(ModelType.NNHLCR);
        predictor.setDataCollectionSessionRatio(100);
        PredictionResult result = predictor.predict2d(features, "");

        // Check
        assertTrue(result.isScored());
        assertFalse(result.isScoreUsable());
        assertEquals(score, result.getScore(), 0);

        // Action (ratio is 0%)
        predictor = new PredictorImpl(mPredictManagerWrapper, null);
        predictor.setModelType(ModelType.NNHLCR);
        predictor.setDataCollectionSessionRatio(0);
        result = predictor.predict2d(features, "");

        // Check
        assertTrue(result.isScored());
        assertTrue(result.isScoreUsable());
        assertEquals(score, result.getScore(), 0);
    }

    @Test
    public void testDataCollectionSessionForLinerHLCR() {
        final List<Float> features = Arrays.asList(0.1f, 0.2f, 0.3f, 0.4f, 0.5f);
        final float score = 0.5f;

        TensorMap tensorMap = TensorMap.newInstance();
        tensorMap.set(LinearFedHLCRClient.TENSOR_Y_PRED, Tensor.newTensor((double) score));
        PredictManager.PredictResult predictResult = newPredictResult(0, tensorMap);
        doReturn(predictResult).when(mMockPredictManager).predict(any());

        // Action (ratio is 100%)
        PredictorImpl predictor = new PredictorImpl(mPredictManagerWrapper, null);
        predictor.setModelType(ModelType.LinerHLCR);
        predictor.setDataCollectionSessionRatio(100);
        PredictionResult result = predictor.predict1d(features, "");

        // Check
        assertTrue(result.isScored());
        assertFalse(result.isScoreUsable());
        assertEquals(score, result.getScore(), 0);

        // Action (ratio is 0%)
        predictor = new PredictorImpl(mPredictManagerWrapper, null);
        predictor.setModelType(ModelType.LinerHLCR);
        predictor.setDataCollectionSessionRatio(0);
        result = predictor.predict1d(features, "");

        // Check
        assertTrue(result.isScored());
        assertTrue(result.isScoreUsable());
        assertEquals(score, result.getScore(), 0);
    }

    @Test
    public void testResetDataCollectionSessionForNNHLCR() {
        final List<List<Float>> features = Arrays.asList(
                Arrays.asList(0.1f, 0.2f, 0.3f, 0.4f, 0.5f),
                Arrays.asList(1.1f, 1.2f, 1.3f, 1.4f, 1.5f));
        final float score = 0.5f;

        TensorMap tensorMap = TensorMap.newInstance();
        tensorMap.set(NNFedHLCRClient.TENSOR_Y_PRED, Tensor.newTensor((double) score));
        PredictManager.PredictResult predictResult = newPredictResult(0, tensorMap);
        doReturn(predictResult).when(mMockPredictManager).predict(any());
        PredictorImpl predictor = spy(new PredictorImpl(mPredictManagerWrapper, null));
        predictor.setModelType(ModelType.NNHLCR);
        predictor.setDataCollectionSessionRatio(0);

        // Action (ratio is 100% after |reset|)
        doReturn(true).when(predictor).shouldBeDataCollectionSession();
        predictor.reset();
        PredictionResult result = predictor.predict2d(features, "");

        // Check
        assertTrue(result.isScored());
        assertFalse(result.isScoreUsable());
        assertEquals(score, result.getScore(), 0);

        // Action (reset is not called)
        result = predictor.predict2d(features, "");

        // Check
        assertTrue(result.isScored());
        assertFalse(result.isScoreUsable());
        assertEquals(score, result.getScore(), 0);

        // Action (ratio is 0% after |reset|)
        doReturn(false).when(predictor).shouldBeDataCollectionSession();
        predictor.reset();
        result = predictor.predict2d(features, "");

        // Check
        assertTrue(result.isScored());
        assertTrue(result.isScoreUsable());
        assertEquals(score, result.getScore(), 0);

        // Action (reset is not called)
        result = predictor.predict2d(features, "");

        // Check
        assertTrue(result.isScored());
        assertTrue(result.isScoreUsable());
        assertEquals(score, result.getScore(), 0);
    }

    @Test
    public void testResetDataCollectionSessionForLinerHLCR() {
        final List<Float> features = Arrays.asList(1.1f, 1.2f, 1.3f, 1.4f, 1.5f);
        final float score = 0.5f;

        TensorMap tensorMap = TensorMap.newInstance();
        tensorMap.set(LinearFedHLCRClient.TENSOR_Y_PRED, Tensor.newTensor((double) score));
        PredictManager.PredictResult predictResult = newPredictResult(0, tensorMap);
        doReturn(predictResult).when(mMockPredictManager).predict(any());
        PredictorImpl predictor = spy(new PredictorImpl(mPredictManagerWrapper, null));
        predictor.setModelType(ModelType.LinerHLCR);
        predictor.setDataCollectionSessionRatio(0);

        // Action (ratio is 100% after |reset|)
        doReturn(true).when(predictor).shouldBeDataCollectionSession();
        predictor.reset();
        PredictionResult result = predictor.predict1d(features, "");

        // Check
        assertTrue(result.isScored());
        assertFalse(result.isScoreUsable());
        assertEquals(score, result.getScore(), 0);

        // Action (reset is not called)
        result = predictor.predict1d(features, "");

        // Check
        assertTrue(result.isScored());
        assertFalse(result.isScoreUsable());
        assertEquals(score, result.getScore(), 0);

        // Action (ratio is 0% after |reset|)
        doReturn(false).when(predictor).shouldBeDataCollectionSession();
        predictor.reset();
        result = predictor.predict1d(features, "");

        // Check
        assertTrue(result.isScored());
        assertTrue(result.isScoreUsable());
        assertEquals(score, result.getScore(), 0);

        // Action (reset is not called)
        result = predictor.predict1d(features, "");

        // Check
        assertTrue(result.isScored());
        assertTrue(result.isScoreUsable());
        assertEquals(score, result.getScore(), 0);
    }

    @Test
    public void testTo2dArray() {
        final List<List<Float>> valueList = Arrays.asList(
                Arrays.asList(0.1f, 0.2f),
                Arrays.asList(1.1f, 1.2f));

        // Action
        PredictorImpl predictor = new PredictorImpl(mPredictManagerWrapper, null);
        float[][] valueArray = predictor.to2dArray(valueList);

        // Check
        assertArrayEquals(new float[][]{{0.1f, 0.2f}, {1.1f, 1.2f}}, valueArray);
    }

    private PredictManager.PredictResult newPredictResult(int status, TensorMap tensorMap) {
        try {
            Constructor<?> constructor = PredictManager.PredictResult.class.getDeclaredConstructor(
                    int.class, TensorMap.class);
            constructor.setAccessible(true);
            return (PredictManager.PredictResult) constructor.newInstance(status, tensorMap);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
