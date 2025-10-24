/**
 * reference
 * https://docs.oracle.com/javase/jp/8/docs/technotes/guides/jni/spec/functions.html#Get_PrimitiveType_ArrayElements_routines
 **/

#include <float.h>
#include <string>
#include "com_sony_fl_jni_NNHLCRNativeJNI.h"
#include "NNHLCR/lstm_lcr_model_nnabla.h"
#include "tensor/tensor.h"
#include "tensor/tensor_map.h"
// #include "tensor/data_metadata.h"

#include "NNHLCR/NNHLCR_JNIF.h"

//#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(str) { std::cerr << "file:" << __FILE__ << " line:" << __LINE__ << ":" << str << std::endl; }
#else
#define DEBUG_MSG(str) { } 
#endif

JNIEXPORT jlong JNICALL Java_com_sony_fl_jni_NNHLCRNativeJNI_Initialize
		(JNIEnv *env, jobject jObj, jstring jModelInfo)
{
    DEBUG_MSG("##### Java_com_sony_fl_jni_NNHLCRNativeJNI_Initialize");

	const char* modelInfo = env->GetStringUTFChars(jModelInfo, NULL);
	if (modelInfo == NULL) {
		DEBUG_MSG("jModelInfo is NULL.");
		return (jlong)0; // error handling
	}

	// Initialize
	long rcd = nn_hlcr::NNHLCR_JNIF::Initialize(modelInfo);

	env->ReleaseStringUTFChars(jModelInfo, modelInfo);

	return (jlong)rcd;
}

JNIEXPORT jstring JNICALL Java_com_sony_fl_jni_NNHLCRNativeJNI_Training
		(JNIEnv *env, jobject jObj, jlong jMlObj, jstring jMetadataJson, jstring jTrainInfo)
{
    DEBUG_MSG("##### Java_com_sony_fl_jni_NNHLCRNativeJNI_Training");

	LstmLCRModel* mlObj = (LstmLCRModel*)jMlObj;

	const char* metaDataJson = env->GetStringUTFChars(jMetadataJson, NULL);
	if (metaDataJson == NULL) {
		DEBUG_MSG("jMetadataJson is NULL.");
		char msg[1] = "";
		return env->NewStringUTF(msg);
	}

	const char* trainInfo = env->GetStringUTFChars(jTrainInfo, NULL);
	if (trainInfo == NULL) {
		DEBUG_MSG("jTrainInfo is NULL.");
		env->ReleaseStringUTFChars(jMetadataJson, metaDataJson);
		char msg[1]= "";
		return env->NewStringUTF(msg);
	}

	// Training
	auto results = nn_hlcr::NNHLCR_JNIF::Training(mlObj, metaDataJson, trainInfo);
	DEBUG_MSG(std::string("##### Results\n") + results);

	env->ReleaseStringUTFChars(jMetadataJson, metaDataJson);
	env->ReleaseStringUTFChars(jTrainInfo, trainInfo);

	return env->NewStringUTF(results.c_str());
}

JNIEXPORT jstring JNICALL Java_com_sony_fl_jni_NNHLCRNativeJNI_Evaluation
		(JNIEnv *env, jobject jObj, jlong jMlObj, jstring jMetadataJson, jstring jEvaluationInfo)
{
    DEBUG_MSG("##### Java_com_sony_fl_jni_NNHLCRNativeJNI_Evaluation");

	LstmLCRModel* mlObj = (LstmLCRModel*)jMlObj;

	const char* metaDataJson = env->GetStringUTFChars(jMetadataJson, NULL);
	if (metaDataJson == NULL) {
		DEBUG_MSG("jMetadataJson is NULL.");
		char msg[1] = "";
		return env->NewStringUTF(msg);
	}

	const char* evaluationInfo = env->GetStringUTFChars(jEvaluationInfo, NULL);
	if (evaluationInfo == NULL) {
		DEBUG_MSG("jEvaluationInfo is NULL.");
		env->ReleaseStringUTFChars(jMetadataJson, metaDataJson);
		char msg[1]= "";
		return env->NewStringUTF(msg);
	}

	// Evaluation
	auto results = nn_hlcr::NNHLCR_JNIF::Evaluation(mlObj, metaDataJson, evaluationInfo);

	env->ReleaseStringUTFChars(jMetadataJson, metaDataJson);
	env->ReleaseStringUTFChars(jEvaluationInfo, evaluationInfo);

	return env->NewStringUTF(results.c_str());
}

jstring buildResult(JNIEnv* env, float value)
{
	std::shared_ptr<fl::Tensor> predict(fl::Tensor::newTensor(value));
	std::shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::newInstance());
	tensor_map->set("y_pred", predict);
	return env->NewStringUTF(tensor_map->toJsonString().c_str());
}

JNIEXPORT jstring JNICALL Java_com_sony_fl_jni_NNHLCRNativeJNI_Prediction
		(JNIEnv *env, jobject jObj, jlong jMlObj, jstring jTensorMapJson)
{ 
    DEBUG_MSG("##### Java_com_sony_fl_jni_NNHLCRNativeJNI_Prediction");

	LstmLCRModel* mlObj = (LstmLCRModel*)jMlObj;

	//
	const char* tensorMapJson = env->GetStringUTFChars(jTensorMapJson, NULL);
	if (tensorMapJson == NULL) {
		DEBUG_MSG("jTensorMapJson is NULL.");
		return buildResult(env, -FLT_MAX);
	}

	// Prediction
	auto results = nn_hlcr::NNHLCR_JNIF::Prediction(mlObj, tensorMapJson);

	env->ReleaseStringUTFChars(jTensorMapJson, tensorMapJson);

	return buildResult(env, results);
}

JNIEXPORT jstring JNICALL Java_com_sony_fl_jni_NNHLCRNativeJNI_UpdateInfo
	(JNIEnv *env, jobject jObj, jlong jMlObj, jstring jMetadataJson, jstring jUpdateInfo)
{
    DEBUG_MSG("##### Java_com_sony_fl_jni_NNHLCRNativeJNI_UpdateInfo");

	LstmLCRModel* mlObj = (LstmLCRModel*)jMlObj;

	const char* metaDataJson = env->GetStringUTFChars(jMetadataJson, NULL);
	if (metaDataJson == NULL) {
		DEBUG_MSG("jMetadataJson is NULL.");
		char msg[1]= "";
		return env->NewStringUTF(msg);
	}

	const char* updateInfo = env->GetStringUTFChars(jUpdateInfo, NULL);
	if (updateInfo == NULL) {
		DEBUG_MSG("jUpdateInfo is NULL.");
		env->ReleaseStringUTFChars(jMetadataJson, metaDataJson);
		char msg[1]= "";
		return env->NewStringUTF(msg);
	}

	// UpdateInfo
	auto results = nn_hlcr::NNHLCR_JNIF::UpdateInfo(mlObj, metaDataJson, updateInfo);

	env->ReleaseStringUTFChars(jMetadataJson, metaDataJson);
	env->ReleaseStringUTFChars(jUpdateInfo, updateInfo);

	return env->NewStringUTF(results.c_str());
}

JNIEXPORT void JNICALL Java_com_sony_fl_jni_NNHLCRNativeJNI_Finalize
  	(JNIEnv *env, jobject jObj, jlong mlObj)
{
    DEBUG_MSG("##### Java_com_sony_fl_jni_NNHLCRNativeJNI_Finalize");

    nn_hlcr::NNHLCR_JNIF::Finalize((LstmLCRModel*)mlObj);
}
