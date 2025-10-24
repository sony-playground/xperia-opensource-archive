/*
 * Copyright (C) 2018 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#include <nbla_utils/nnp.hpp>

#include <cstring>
#include <iostream>
#include <memory>
#include <string>

#if defined(__ANDROID__)
#include <android/log.h>
#define LOG_TAG "SmartNetworkEngineNative"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#endif // defined(__ANDROID__)

class SmartNetNnabla{
private:
    // NN input
    float* mInput1;
    float* mInput2;
    float* mInput3;

    // NN output
    const float* mOutput1;
    const float* mOutput2;
    const float* mOutput3;

    std::shared_ptr<nbla::utils::nnp::Executor> mExecutor;
    nbla::Context mContext{{"cpu:float"}, "CpuCachedArray", "0"};

    const int kHiddenSize = 100;

    // NOTE: This program expects Input and Output nodes with the following names are placed
    // in NNP file. Otherwise, unexpected behavior - such as crash, could occur.
    const std::vector<std::string> kInputNodeNames = {"Input", "Input_2", "Input_3"};
    const std::vector<std::string> kOutputNodeNames =
                                    {"Sigmoid_Output", "Mul2_OutputGate", "Add2_C"};


    float* getInputData(int index){
        float* ret = nullptr;
        for(auto x : mExecutor->get_data_variables()){
            if(x.variable_name == kInputNodeNames[index]){
                 ret = x.variable->variable()->cast_data_and_get_pointer<float>(mContext);
                 break;
            }
        }
        return ret;
    }

    const float* getOutputData(int index){
        const float* ret = nullptr;
        for(auto y : mExecutor->get_output_variables()){
            if(y.variable_name == kOutputNodeNames[index]){
                 y.variable->set_persistent(true);
                 ret = y.variable->variable()->get_data_pointer<float>(mContext);
                 break;
            }
        }
        return ret;
    }

public:
    // Initialize NN with input NNP file.
    bool initialize(std::string nnpFile){
        // Load NNP file and get Executor for inference.
        nbla::utils::nnp::Nnp nnp(mContext);
        nnp.add(nnpFile);
        mExecutor = nnp.get_executor("Executor");

        // Get the nodes for inputting data to NN and initialize them.
        mInput1 = getInputData(0);
        mInput2 = getInputData(1);
        mInput3 = getInputData(2);

        resetRecurrentInputs();
        return true;
    }

    // Reset recurrent inputs to clear past memory of NN.
    void resetRecurrentInputs(){
        std::memset(mInput2, 0, sizeof(float)*kHiddenSize);
        std::memset(mInput3, 0, sizeof(float)*kHiddenSize);
    }

    // Perform inference with input parameters and return its result.
    float predict(const float* in, int len){
        // Copy input parameters such as WiFi info etc. to the input node.
        std::memcpy(mInput1, in, sizeof(float)*len);

        // Perform inference.
        mExecutor->execute();

        // Get necessary ouput nodes from Executor.
        mOutput1 = getOutputData(0);
        mOutput2 = getOutputData(1);
        mOutput3 = getOutputData(2);

        // For LSTM - i.e. recurrent NN, copy intermediate output to corresponding
        // input nodes.
        std::memcpy(mInput2, mOutput2, sizeof(float)*kHiddenSize);
        std::memcpy(mInput3, mOutput3, sizeof(float)*kHiddenSize);

#ifdef DEBUG_SMARTNET_NNABLA
        LOGD("mOutput1 = %f", *mOutput1);
#endif
        return *mOutput1;
    }
};
