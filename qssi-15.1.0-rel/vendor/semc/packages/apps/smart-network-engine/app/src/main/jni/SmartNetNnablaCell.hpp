/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#include <nbla_utils/nnp.hpp>

#include <cstring>
#include <iostream>
#include <memory>
#include <string>

class SmartNetNnablaCell{
private:
    // NN input
    float* mInput;

    // NN output
    const float* mOutput;

    std::shared_ptr<nbla::utils::nnp::Executor> mExecutor;

    nbla::Context mContext{{"cpu:float"}, "CpuCachedArray", "0"};

    float* getInputData(){
        nbla::CgVariablePtr x = mExecutor->get_data_variables().at(0).variable;
        return(x->variable()->cast_data_and_get_pointer<float>(mContext));
    }

    const float* getOutputData(){
        nbla::CgVariablePtr y = mExecutor->get_output_variables().at(0).variable;
        return(y->variable()->get_data_pointer<float>(mContext));
    }

public:
    // Initialize NN with input NNP file.
    bool initialize(std::string nnpFile){
        // Load NNP file and get Executor for inference.
        nbla::utils::nnp::Nnp nnp(mContext);
        nnp.add(nnpFile);
        mExecutor = nnp.get_executor("Executor");

        // Get the nodes for inputting data to NN and initialize them.
        mInput = getInputData();

        return true;
    }

    // Perform inference with input parameters and return its result.
    float predict(const float* in, int len) {
        // Copy input parameters such as WiFi info etc. to the input node.
        std::memcpy(mInput, in, sizeof(float)*len);

        // Perform inference.
        mExecutor->execute();

        // Get necessary ouput nodes from Executor.
        mOutput = getOutputData();

        return *mOutput;
    }
};
