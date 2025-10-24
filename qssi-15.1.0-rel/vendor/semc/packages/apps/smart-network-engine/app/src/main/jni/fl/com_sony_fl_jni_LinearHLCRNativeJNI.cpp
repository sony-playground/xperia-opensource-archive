#include "com_sony_fl_jni_LinearHLCRNativeJNI.h"
#include "LinearHLCR/LinearHLCR_JNIF.h"
#include "LinearHLCR/LinearHLCR.h"
#include <iostream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "FLException.h"
#include "tensor/tensor.h"
#include "tensor/tensor_map.h"
#include "tensor/tensor_shape.h"
#include "evaluation/evaluation.h"

#ifdef DEBUG
#define DEBUG_MSG(str) { std::cerr << "file:" << __FILE__ << " line:" << __LINE__ << ":" << str << std::endl; }
#else
#define DEBUG_MSG(str) { } 
#endif

JNIEXPORT jlong JNICALL Java_com_sony_fl_jni_LinearHLCRNativeJNI_Initialize
  (JNIEnv *env, jobject jObj, jstring jJsonParams)
{
    DEBUG_MSG("##### Java_com_sony_fl_jni_LinearHLCRNativeJNI_Initialize");

    const char* jsonParamsString;
    json jsonParams;
    try {
        jsonParamsString = env->GetStringUTFChars(jJsonParams, NULL);
        jsonParams = json::parse(jsonParamsString);
        env->ReleaseStringUTFChars(jJsonParams, jsonParamsString);
    }
    catch (json::exception& ex) {
        try { env->ReleaseStringUTFChars(jJsonParams, jsonParamsString); } catch (...) {}
        // std::cerr << "Caught nlohmann json exception:" << ex.what() << std::endl;
        DEBUG_MSG(std::string("Caught nlohmann json exception:") + ex.what());
        return (jlong)-1;
    }
    catch (...) {
        try { env->ReleaseStringUTFChars(jJsonParams, jsonParamsString); } catch (...) {}
        // std::cerr << "Caught unknown exception" << std::endl;
        DEBUG_MSG("Caught unknown exception");
        return (jlong)-1;
    }

    // Initialize
    return (jlong)linear_hlcr::LinearHLCR_JNIF::Initialize(jsonParams);
}

JNIEXPORT jstring JNICALL Java_com_sony_fl_jni_LinearHLCRNativeJNI_Training
  (JNIEnv *env, jobject jObj, jlong jMlObj, jstring jJsonParams)
{
    DEBUG_MSG("##### Java_com_sony_fl_jni_LinearHLCRNativeJNI_Training");
    DEBUG_MSG(std::string("##### mlObj:") + std::to_string(jMlObj));
    linear_hlcr::LinearHLCR* model_ptr = (linear_hlcr::LinearHLCR*)jMlObj;

    const char* jsonParamsString;
    json jsonParams;
    try {
        jsonParamsString = env->GetStringUTFChars(jJsonParams, NULL);
        jsonParams = json::parse(jsonParamsString);
        env->ReleaseStringUTFChars(jJsonParams, jsonParamsString);
    }
    catch (json::exception& ex) {
        try { env->ReleaseStringUTFChars(jJsonParams, jsonParamsString); } catch (...) {}
        // std::cerr << "Caught nlohmann json exception:" << ex.what() << std::endl;
        try {
            auto errorResults = R"({"method":"Training","results":{"state":1,"description":"unknown"}})"_json;
            errorResults["results"]["description"] = ex.what();
            DEBUG_MSG(std::string("##### Results\n") + errorResults.dump(2));
            return env->NewStringUTF(errorResults.dump().c_str());
        }
        catch (...) {
            // std::cerr << "Caught unknown exception" << std::endl;
            auto errorResults = R"({"method":"Training","results":{"state":1,"description":"unknown"}})";
            return env->NewStringUTF(errorResults);
        }
    }
    catch (...) {
        // std::cerr << "Caught unknown exception" << std::endl;
        auto errorResults = R"({"method":"Training","results":{"state":1,"description":"unknown"}})";
        try {
            env->ReleaseStringUTFChars(jJsonParams, jsonParamsString);
            DEBUG_MSG(std::string("##### Results\n") + errorResults);
        }
        catch (...) {}
        return env->NewStringUTF(errorResults);
    }

    // Training
    auto jsonResults = linear_hlcr::LinearHLCR_JNIF::Training(model_ptr, jsonParams);
    DEBUG_MSG(std::string("##### Results\n") + jsonResults.dump(2));

    return env->NewStringUTF(jsonResults.dump().c_str());
}

JNIEXPORT jstring JNICALL Java_com_sony_fl_jni_LinearHLCRNativeJNI_Evaluation
  (JNIEnv *env, jobject jObj, jlong jMlObj, jstring jJsonParams)
{
    DEBUG_MSG("##### Java_com_sony_fl_jni_LinearHLCRNativeJNI_Evaluation");
    DEBUG_MSG(std::string("##### mlObj:") + std::to_string(jMlObj));
    linear_hlcr::LinearHLCR* model_ptr = (linear_hlcr::LinearHLCR*)jMlObj;

    const char* jsonParamsString;
    json jsonParams;
    try {
        jsonParamsString = env->GetStringUTFChars(jJsonParams, NULL);
        jsonParams = json::parse(jsonParamsString);
        env->ReleaseStringUTFChars(jJsonParams, jsonParamsString);
    }
    catch (json::exception& ex) {
        try { env->ReleaseStringUTFChars(jJsonParams, jsonParamsString); } catch (...) {}
        // std::cerr << "Caught nlohmann json exception:" << ex.what() << std::endl;
        try {
            auto errorResults = R"(
                {
                  "method": "Evaluation",
                  "results": {
                    "state": 1,
                    "description": "unknown"
                  }
                }
            )"_json;
            errorResults["results"]["description"] = ex.what();
            DEBUG_MSG(std::string("##### Results\n") + errorResults.dump(2));
            return env->NewStringUTF(errorResults.dump().c_str());
        }
        catch (...) {
            // std::cerr << "Caught unknown exception" << std::endl;
            auto errorResults = R"({"method":"Evaluation","results":{"state":1,"description":"unknown"}})";
            return env->NewStringUTF(errorResults);
        }
    }
    catch (...) {
        // std::cerr << "Caught unknown exception" << std::endl;
        auto errorResults = R"({"method":"Evaluation","results":{"state":1,"description":"unknown"}})";
        try {
            env->ReleaseStringUTFChars(jJsonParams, jsonParamsString);
            DEBUG_MSG(std::string("##### Results\n") + errorResults);
        }
        catch (...) {}
        return env->NewStringUTF(errorResults);
    }

    // Evaluation
    auto jsonResults = linear_hlcr::LinearHLCR_JNIF::Evaluation(model_ptr, jsonParams);

    return env->NewStringUTF(jsonResults.dump().c_str());
}

JNIEXPORT jstring JNICALL Java_com_sony_fl_jni_LinearHLCRNativeJNI_Prediction
  (JNIEnv *env, jobject jObj, jlong jMlObj, jstring jJsonParams)
{
    DEBUG_MSG("##### Java_com_sony_fl_jni_LinearHLCRNativeJNI_Prediction");
    DEBUG_MSG(std::string("##### mlObj:") + std::to_string(jMlObj));
    linear_hlcr::LinearHLCR* model_ptr = (linear_hlcr::LinearHLCR*)jMlObj;

    const char* jsonParamsString;
    json jsonParams;
    try {
        jsonParamsString = env->GetStringUTFChars(jJsonParams, NULL);
        jsonParams = json::parse(jsonParamsString);
        env->ReleaseStringUTFChars(jJsonParams, jsonParamsString);
    }
    catch (json::exception& ex) {
        try { env->ReleaseStringUTFChars(jJsonParams, jsonParamsString); } catch (...) {}
        // std::cerr << "Caught nlohmann json exception:" << ex.what() << std::endl;
        try {
            auto errorResults = R"(
                {
                  "method": "Prediction",
                  "results": {
                    "state": 1,
                    "description": "unknown"
                  }
                }
            )"_json;
            errorResults["results"]["description"] = ex.what();
            DEBUG_MSG(std::string("##### Results\n") + errorResults.dump(2));
            return env->NewStringUTF(errorResults.dump().c_str());
        }
        catch (...) {
            // std::cerr << "Caught unknown exception" << std::endl;
            auto errorResults = R"({"method":"Prediction","results":{"state":1,"description":"unknown"}})";
            return env->NewStringUTF(errorResults);
        }
    }
    catch (...) {
        // std::cerr << "Caught unknown exception" << std::endl;
        auto errorResults = R"({"method":"Prediction","results":{"state":1,"description":"unknown"}})";
        try {
            env->ReleaseStringUTFChars(jJsonParams, jsonParamsString);
            DEBUG_MSG(std::string("##### Results\n") + errorResults);
        }
        catch (...) {}
        return env->NewStringUTF(errorResults);
    }

    // Prediction
    auto jsonResults = linear_hlcr::LinearHLCR_JNIF::Prediction(model_ptr, jsonParams);

    return env->NewStringUTF(jsonResults.dump().c_str());
}

JNIEXPORT void JNICALL Java_com_sony_fl_jni_LinearHLCRNativeJNI_Finalize
  (JNIEnv *env, jobject jObj, jlong jMlObj)
{
    DEBUG_MSG("##### Java_com_sony_fl_jni_LinearHLCRNativeJNI_Finalize");
    DEBUG_MSG(std::string("##### mlObj:") + std::to_string(jMlObj));
    linear_hlcr::LinearHLCR* model_ptr = (linear_hlcr::LinearHLCR*)jMlObj;

    linear_hlcr::LinearHLCR_JNIF::Finalize(model_ptr);
}

JNIEXPORT jstring JNICALL Java_com_sony_fl_jni_LinearHLCRNativeJNI_UpdateInfo
  (JNIEnv *env, jobject jObj, jlong jMlObj, jstring jJsonParams)
{
    DEBUG_MSG("##### Java_com_sony_fl_jni_LinearHLCRNativeJNI_UpdateInfo");
    DEBUG_MSG(std::string("##### mlObj:") + std::to_string(jMlObj));
    linear_hlcr::LinearHLCR* model_ptr = (linear_hlcr::LinearHLCR*)jMlObj;

    const char* jsonParamsString;
    json jsonParams;
    try {
        jsonParamsString = env->GetStringUTFChars(jJsonParams, NULL);
        jsonParams = json::parse(jsonParamsString);
        env->ReleaseStringUTFChars(jJsonParams, jsonParamsString);
    }
    catch (json::exception& ex) {
        try { env->ReleaseStringUTFChars(jJsonParams, jsonParamsString); } catch (...) {}
        // std::cerr << "Caught nlohmann json exception:" << ex.what() << std::endl;
        try {
            auto errorResults = R"(
                {
                  "method": "UpdateInfo",
                  "results": {
                    "state": 1,
                    "description": "unknown"
                  }
                }
            )"_json;
            errorResults["results"]["description"] = ex.what();
            DEBUG_MSG(std::string("##### Results\n") + errorResults.dump(2));
            return env->NewStringUTF(errorResults.dump().c_str());
        }
        catch (...) {
            // std::cerr << "Caught unknown exception" << std::endl;
            auto errorResults = R"({"method":"UpdateInfo","results":{"state":1,"description":"unknown"}})";
            return env->NewStringUTF(errorResults);
        }
    }
    catch (...) {
        // std::cerr << "Caught unknown exception" << std::endl;
        auto errorResults = R"({"method":"UpdateInfo","results":{"state":1,"description":"unknown"}})";
        try {
            env->ReleaseStringUTFChars(jJsonParams, jsonParamsString);
            DEBUG_MSG(std::string("##### Results\n") + errorResults);
        }
        catch (...) {}
        return env->NewStringUTF(errorResults);
    }

    // UpdateInfo
    auto jsonResults = linear_hlcr::LinearHLCR_JNIF::UpdateInfo(model_ptr, jsonParams);

    return env->NewStringUTF(jsonResults.dump().c_str());
}
