/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <jni.h>
#include "SmartNetNnabla.hpp"
#include "SmartNetNnablaCell.hpp"

static SmartNetNnabla sPrimaryInstance;
static SmartNetNnabla sSecondaryInstance;

//cellular neural network instance array
//sInstanceCell[0]: LTE
//sInstanceCell[1]: LTE_NR
//sInstanceCell[2]: LTE_NR_CONNECTED
//sInstanceCell[3]: LTE_NR_NOT_RESTRICTED
static SmartNetNnablaCell sInstanceCell[4];

extern "C"
JNIEXPORT void JNICALL
Java_com_sonymobile_smartnetworkengine_connected_prediction_PredictionManager_nativeCreateNeuralNetworks(
        JNIEnv *env, jobject instance, jstring primaryPath, jstring secondaryPath) {
    // Initialize primary neural network instance.
    const char *primaryPathChars = env->GetStringUTFChars(primaryPath, 0);
    sPrimaryInstance.initialize(primaryPathChars);
    env->ReleaseStringUTFChars(primaryPath, primaryPathChars);

    // Initialize secondary neural network instance.
    const char *secondaryPathChars = env->GetStringUTFChars(secondaryPath, 0);
    sSecondaryInstance.initialize(secondaryPathChars);
    env->ReleaseStringUTFChars(secondaryPath, secondaryPathChars);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_sonymobile_smartnetworkengine_connected_prediction_PredictionManager_nativeResetRecurrentInputs(
        JNIEnv *env, jobject instance) {
    sPrimaryInstance.resetRecurrentInputs();
    sSecondaryInstance.resetRecurrentInputs();
}

extern "C"
JNIEXPORT jfloatArray JNICALL
Java_com_sonymobile_smartnetworkengine_connected_prediction_PredictionManager_nativeInference(
        JNIEnv *env, jobject instance, jfloatArray primaryInput, jfloatArray secondaryInput) {
    // Invoke inference for primary neural network.
    jfloat *primaryParams = env->GetFloatArrayElements(primaryInput, 0);
    jsize primaryParamNum = env->GetArrayLength(primaryInput);
    float primaryResult = sPrimaryInstance.predict(&primaryParams[0], primaryParamNum);
    env->ReleaseFloatArrayElements(primaryInput, primaryParams, 0);

    // Invoke inference for secondary neural network.
    jfloat *secondaryParams = env->GetFloatArrayElements(secondaryInput, 0);
    jsize secondaryParamNum = env->GetArrayLength(secondaryInput);
    float secondaryResult = sSecondaryInstance.predict(&secondaryParams[0], secondaryParamNum);
    env->ReleaseFloatArrayElements(secondaryInput, secondaryParams, 0);

    // Return a pair of inference results.
    std::vector<float> tmpResults = {primaryResult, secondaryResult};
    jfloatArray ret = env->NewFloatArray(tmpResults.size());
    env->SetFloatArrayRegion(ret, 0, 2, &tmpResults[0]);
    return ret;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_sonymobile_smartnetworkengine_connected_prediction_PredictionManager_nativeCreateNeuralNetworkCell(
        JNIEnv *env, jobject instance, jint nnCellId, jstring nnpPathCell) {
    // Initialize cellular neural network instance.
    const char *pathCharsCell = env->GetStringUTFChars(nnpPathCell, 0);
    sInstanceCell[nnCellId].initialize(pathCharsCell);
    env->ReleaseStringUTFChars(nnpPathCell, pathCharsCell);
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_com_sonymobile_smartnetworkengine_connected_prediction_PredictionManager_nativeInferenceCell(
        JNIEnv *env, jobject instance, jint nnCellId, jfloatArray cellInput) {
    // Invoke inference for cellular neural network.
    jfloat *cellParams = env->GetFloatArrayElements(cellInput, 0);
    jsize cellParamNum = env->GetArrayLength(cellInput);
    return(sInstanceCell[nnCellId].predict(&cellParams[0], cellParamNum));
}
