#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "evaluation/evaluation.h"
#include "tensor/tensor.h"

#define TEMP_FOLDER std::string("./Testing/Temporary")

TEST(test_Evaluator, BasicAssertions) {
    fl::Evaluator evaluator = fl::Evaluator::createFor(TEMP_FOLDER);
    
    std::vector<int> intvec = {1,2,3,4,5};
    std::vector<double> doublevec = {1.1,2.2,3.3,4.4,5.5};

    for (int i = 0; i < 5; i++) {
        auto label = std::shared_ptr<fl::Tensor>(fl::Tensor::newTensor(intvec[i]));
        auto pred = std::shared_ptr<fl::Tensor>(fl::Tensor::newTensor(doublevec[i]));

        evaluator.addResult(label, pred);
    }

    auto metadata = evaluator.getRawResult();
    fl::DataDeserializer deserializer = fl::DataDeserializer::createFor(metadata);

    for (int i = 0; i < 5; i++) {
        auto tensor_map = deserializer.get(i+1);
        auto label = tensor_map->get(fl::Evaluator::KEY_OF_TARGET)->intValue();
        auto pred = tensor_map->get(fl::Evaluator::KEY_OF_PREDICTION_RESULT)->doubleValue();

        EXPECT_EQ(intvec[i], label);
        EXPECT_DOUBLE_EQ(doublevec[i], pred);
    }

}