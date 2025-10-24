#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "LinearHLCR/LinearRegression.h"

TEST(test_LinearRegressionGlobalModel_fromJson, BasicAssertions) {
    auto input = R"({"H":[1.0,2.0,3.0,2.0,3.0,4.0,3.0,4.0,5.0],"w":[0.5, 0.4],"b":0.8,"d":3})"_json;
    auto model = linear_hlcr::LinearRegressionGlobalModel::fromJson(input);
    auto H = model->getH();
    auto W = model->getW();
    auto B = model->getB();
    
    std::vector<double> h = H->getMatrix();
    EXPECT_DOUBLE_EQ(1.0, h[0]);
    EXPECT_DOUBLE_EQ(2.0, h[1]); 
    EXPECT_DOUBLE_EQ(3.0, h[2]);
    EXPECT_DOUBLE_EQ(2.0, h[3]); 
    EXPECT_DOUBLE_EQ(3.0, h[4]); 
    EXPECT_DOUBLE_EQ(4.0, h[5]); 
    EXPECT_DOUBLE_EQ(3.0, h[6]); 
    EXPECT_DOUBLE_EQ(4.0, h[7]); 
    EXPECT_DOUBLE_EQ(5.0, h[8]); 

    std::vector<double> w = W->getVector();
    EXPECT_DOUBLE_EQ(0.5, w[0]);
    EXPECT_DOUBLE_EQ(0.4, w[1]);
    EXPECT_DOUBLE_EQ(0.8, B); 
}

TEST(test_LinearRegressionLocalModel_save, BasicAssertions) {
    linear_hlcr::SymmetricMatrix D = 
        linear_hlcr::SymmetricMatrix::create(std::vector<double>({1,2,3,2,3,4,3,4,5}), 3);
    linear_hlcr::DoubleVector c = 
            linear_hlcr::DoubleVector(std::vector<double>({1.1,2.2,3.3}));
    auto model = linear_hlcr::LinearRegressionLocalModel::create(D, c);
    std::string output = model->save()->dump();
    std::cout << output << std::endl;
    EXPECT_TRUE(output == "{\"D\":[1.0,2.0,3.0,2.0,3.0,4.0,3.0,4.0,5.0],\"c\":[1.1,2.2,3.3],\"d\":3}");
}