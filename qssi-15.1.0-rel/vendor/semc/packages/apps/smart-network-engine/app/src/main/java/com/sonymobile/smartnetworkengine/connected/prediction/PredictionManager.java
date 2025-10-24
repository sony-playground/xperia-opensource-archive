/*
 * Copyright 2018 Sony Corporation
 */

package com.sonymobile.smartnetworkengine.connected.prediction;

import static com.sonymobile.smartnetworkengine.Constants.CELL_NETWORK_TYPE_UNKNOWN;
import static com.sonymobile.smartnetworkengine.Constants.NN_LTE;
import static com.sonymobile.smartnetworkengine.Constants.NN_LTE_NR_CONNECTED;
import static com.sonymobile.smartnetworkengine.Constants.NN_LTE_NR_NOT_RESTRICTED;
import static com.sonymobile.smartnetworkengine.Constants.NN_NR;
import static com.sonymobile.smartnetworkengine.Constants.NN_PRIMARY;
import static com.sonymobile.smartnetworkengine.Constants.NN_SECONDARY;

import android.content.Context;

import androidx.annotation.NonNull;

import com.sonymobile.smartnetworkengine.util.Log;
import com.sonymobile.smartnetworkengine.util.NeuralNetworkConfiguration;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Initialize neural networks and invoke inferences through native interfaces.
 */
public class PredictionManager {

    static {
        System.loadLibrary("smartnet_jni");
    }

    private static final String TAG = PredictionManager.class.getSimpleName();

    /**
     * Neural network parameters for primary engine
     */
    private final NeuralNetworkConfiguration mPrimaryConfig;
    /**
     * Neural network parameters for secondary engine
     */
    private final NeuralNetworkConfiguration mSecondaryConfig;
    /**
     * Neural network parameters for cellular engines
     */
    private final NeuralNetworkConfiguration mConfigCell[] = new NeuralNetworkConfiguration[4];

    public PredictionManager(@NonNull Context context) {
        mPrimaryConfig = new NeuralNetworkConfiguration(context, NN_PRIMARY);
        mSecondaryConfig = new NeuralNetworkConfiguration(context, NN_SECONDARY);
        mConfigCell[0] = new NeuralNetworkConfiguration(context, NN_LTE);
        mConfigCell[1] = new NeuralNetworkConfiguration(context, NN_NR);
        mConfigCell[2] = new NeuralNetworkConfiguration(context, NN_LTE_NR_CONNECTED);
        mConfigCell[3] = new NeuralNetworkConfiguration(context, NN_LTE_NR_NOT_RESTRICTED);
    }

    public void initializeNeuralNetworks() {
        String primaryNnpPath = mPrimaryConfig.getNnpPath().toString();
        String secondaryNnpPath = mSecondaryConfig.getNnpPath().toString();
        Log.v(TAG, "nnp path(primary): " + primaryNnpPath + ", nnp path(secondary): "
                + secondaryNnpPath);
        nativeCreateNeuralNetworks(primaryNnpPath, secondaryNnpPath);
        for (int i = 0; i < mConfigCell.length; i++) {
            String nnpPath = mConfigCell[i].getNnpPath().toString();
            Log.v(TAG, "cellular nnp path [" + i + "]: " + nnpPath);
            nativeCreateNeuralNetworkCell(i, nnpPath);
        }
    }

    public void resetRecurrentInputs() {
        nativeResetRecurrentInputs();
    }

    /**
     * Run inference.
     */
    public float[] doInference(@NonNull List wifiInfoForPrimaryInput,
            @NonNull List wifiInfoForSecondaryInput, @NonNull List trafficData) {

        float[] primaryInputParameters = createInputParameters(wifiInfoForPrimaryInput,
                trafficData, mPrimaryConfig.getMean(), mPrimaryConfig.getStd());
        float[] secondaryInputParameters = createInputParameters(wifiInfoForSecondaryInput,
                trafficData, mSecondaryConfig.getMean(), mSecondaryConfig.getStd());

        // Log parameters for debugging purpose
        logInferenceParameters("primary", wifiInfoForPrimaryInput, trafficData,
                primaryInputParameters);
        logInferenceParameters("secondary", wifiInfoForSecondaryInput, trafficData,
                secondaryInputParameters);

        return nativeInference(primaryInputParameters, secondaryInputParameters);
    }

    public float doInferenceCell(int networkType, List cellInfo) {
        if (networkType == CELL_NETWORK_TYPE_UNKNOWN || cellInfo == null) {
            return -1f;
        }

        //convert networkType to cellular neural network id
        int nnCellId = networkType - 1;

        float[] inputParametersCell = createInputParametersCell(cellInfo,
                mConfigCell[nnCellId].getMean(),
                mConfigCell[nnCellId].getStd());
        Log.v(TAG, "NN Cell [" + nnCellId + "]: cellInfo = " + cellInfo.toString());
        Log.v(TAG,
                "NN Cell [" + nnCellId + "]: inputInfo = " + Arrays.toString(inputParametersCell));

        return nativeInferenceCell(nnCellId, inputParametersCell);
    }

    private float[] createInputParameters(List wifiInfoData, List trafficData, List<Float> mean,
            List<Float> std) {
        List runtimeDataList = new ArrayList();
        runtimeDataList.addAll(wifiInfoData);
        runtimeDataList.addAll(trafficData);

        float[] params = new float[runtimeDataList.size()];
        for (int i = 0; i < runtimeDataList.size(); i++) {
            params[i] = normalize(String.valueOf(runtimeDataList.get(i)), mean.get(i), std.get(i));
        }
        return params;
    }

    private float[] createInputParametersCell(List cellInfo, List<Float> mean, List<Float> std) {
        float[] params = new float[cellInfo.size()];
        for (int i = 0; i < cellInfo.size(); i++) {
            params[i] = normalize(String.valueOf(cellInfo.get(i)), mean.get(i), std.get(i));
        }
        return params;
    }

    private float normalize(String runtimeData, double mean, double std) {
        return ((Float.parseFloat(runtimeData) - (float) mean) / (float) std);
    }

    private void logInferenceParameters(String engineTag, List wifiInfoData, List trafficData,
            float[] inputParameters) {
        Log.v(TAG, "NN(" + engineTag + "): wifiInfo = " + wifiInfoData.toString());
        Log.v(TAG, "NN(" + engineTag + "): trafficStats = " + trafficData.toString());
        Log.v(TAG, "NN(" + engineTag + "): inputParameters = " + Arrays.toString(inputParameters));
    }

    /**
     * JNI interface: Setup neural networks.
     *
     * @param primaryPath   NNP path for primary neural network
     * @param secondaryPath NNP path for secondary neural network.
     */
    private native void nativeCreateNeuralNetworks(String primaryPath, String secondaryPath);

    /**
     * JNI interface: Reset recurrent inputs to clear past memory of NN.
     */
    private native void nativeResetRecurrentInputs();

    /**
     * JNI interface: Invoke inference of neural network.
     *
     * @param primaryInput   input parameters to primary neural network
     * @param secondaryInput input parameters to secondary neural network
     * @return a pair of inference results
     */
    private native float[] nativeInference(float[] primaryInput, float[] secondaryInput);

    /**
     * JNI interface: Setup neural networks.
     *
     * @param nnCellId Cellular neural network id (= cell networkType -1)
     * @param nnpPath  NNP path for cellular neural network.
     */
    private native void nativeCreateNeuralNetworkCell(int nnCellId, String nnpPath);

    /**
     * JNI interface: Invoke inference of neural network for cellular.
     *
     * @param nnCellId  Cellular neural network id (= cell networkType -1)
     * @param cellInput Input parameters to cellular neural network
     * @return cellular inference results
     */
    private native float nativeInferenceCell(int nnCellId, float[] cellInput);
}
