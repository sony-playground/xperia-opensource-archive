#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "LinearHLCR/MatrixAndVector.h"

TEST(test_SymmetricMatrix_create, BasicAssertions) {
    linear_hlcr::SymmetricMatrix symmetricMatrix = 
            linear_hlcr::SymmetricMatrix::create(std::vector<double>({1,2,3,2,3,4,3,4,5}), 3);
    EXPECT_EQ(3, symmetricMatrix.getDim());
    std::vector<double> matrix = symmetricMatrix.getMatrix();
    EXPECT_DOUBLE_EQ(1.0, matrix[0]);
    EXPECT_DOUBLE_EQ(2.0, matrix[1]); 
    EXPECT_DOUBLE_EQ(3.0, matrix[2]);
    EXPECT_DOUBLE_EQ(2.0, matrix[3]); 
    EXPECT_DOUBLE_EQ(3.0, matrix[4]); 
    EXPECT_DOUBLE_EQ(4.0, matrix[5]); 
    EXPECT_DOUBLE_EQ(3.0, matrix[6]); 
    EXPECT_DOUBLE_EQ(4.0, matrix[7]); 
    EXPECT_DOUBLE_EQ(5.0, matrix[8]); 
}

TEST(test_SymmetricMatrix_fromAndToTensor, BasicAssertions) {
    linear_hlcr::SymmetricMatrix symmetricMatrix = 
            linear_hlcr::SymmetricMatrix::create(std::vector<double>({1,2,2,3}), 2);
    std::unique_ptr<fl::Tensor> tensor_ptr = symmetricMatrix.toTensor();
    linear_hlcr::SymmetricMatrix copy = linear_hlcr::SymmetricMatrix::fromTensor(*tensor_ptr);
    std::vector<double> matrix = copy.getMatrix();
    EXPECT_DOUBLE_EQ(1.0, matrix[0]);
    EXPECT_DOUBLE_EQ(2.0, matrix[1]); 
    EXPECT_DOUBLE_EQ(2.0, matrix[2]);
    EXPECT_DOUBLE_EQ(3.0, matrix[3]);  
}


TEST(test_SymmetricMatrix_add, BasicAssertions) {
    linear_hlcr::SymmetricMatrix symmetricMatrix1 = 
            linear_hlcr::SymmetricMatrix::create(std::vector<double>({1.1,2.2,2.2,3.3}), 2);
    linear_hlcr::SymmetricMatrix symmetricMatrix2 = 
            linear_hlcr::SymmetricMatrix::create(std::vector<double>({5.1,-4.2,-4.2,1.1}), 2);
    linear_hlcr::SymmetricMatrix symmetricMatrix3 = symmetricMatrix1.add(symmetricMatrix2);
    std::vector<double> matrix = symmetricMatrix3.getMatrix();
    EXPECT_DOUBLE_EQ(6.2, matrix[0]);
    EXPECT_DOUBLE_EQ(-2.0, matrix[1]); 
    EXPECT_DOUBLE_EQ(-2.0, matrix[2]);
    EXPECT_DOUBLE_EQ(4.4, matrix[3]);  
}

TEST(test_IntVector_create, BasicAssertions) {
    linear_hlcr::IntVector intVector = linear_hlcr::IntVector(std::vector<int>({1,2,3}));
    EXPECT_EQ(3, intVector.getDim());
    std::vector<int> output_vec = intVector.getVector();
    EXPECT_EQ(1, output_vec[0]);
    EXPECT_EQ(2, output_vec[1]);
    EXPECT_EQ(3, output_vec[2]);   
}

TEST(test_IntVector_fromAndToTensor, BasicAssertions) {
    linear_hlcr::IntVector intVector = linear_hlcr::IntVector(std::vector<int>({1,2,3}));
    std::unique_ptr<fl::Tensor> tensor_ptr = intVector.toTensor();
    linear_hlcr::IntVector copy = linear_hlcr::IntVector::fromTensor(*tensor_ptr);
    std::vector<int> output_vec = copy.getVector();
    EXPECT_EQ(1, output_vec[0]);
    EXPECT_EQ(2, output_vec[1]);
    EXPECT_EQ(3, output_vec[2]);   
}

TEST(test_DoubleVector_create, BasicAssertions) {
    linear_hlcr::DoubleVector doubleVector = 
            linear_hlcr::DoubleVector(std::vector<double>({1.1,2.2,3.3}));
    EXPECT_EQ(3, doubleVector.getDim());
    std::vector<double> output_vec = doubleVector.getVector();
    EXPECT_DOUBLE_EQ(1.1, output_vec[0]);
    EXPECT_DOUBLE_EQ(2.2, output_vec[1]);
    EXPECT_DOUBLE_EQ(3.3, output_vec[2]);   
}

TEST(test_DoubleVector_fromAndToTensor, BasicAssertions) {
    linear_hlcr::DoubleVector doubleVector = 
            linear_hlcr::DoubleVector(std::vector<double>({1,2,3}));
    std::unique_ptr<fl::Tensor> tensor_ptr = doubleVector.toTensor();
    linear_hlcr::DoubleVector copy = linear_hlcr::DoubleVector::fromTensor(*tensor_ptr);
    std::vector<double> output_vec = copy.getVector();
    EXPECT_DOUBLE_EQ(1, output_vec[0]);
    EXPECT_DOUBLE_EQ(2, output_vec[1]);
    EXPECT_DOUBLE_EQ(3, output_vec[2]);   
}

TEST(test_DoubleVector_add_DoubleVector, BasicAssertions) {
    linear_hlcr::DoubleVector doubleVector1 = 
            linear_hlcr::DoubleVector(std::vector<double>({1.1,2.2,3.3}));
    linear_hlcr::DoubleVector doubleVector2 = 
            linear_hlcr::DoubleVector(std::vector<double>({1.5,2.5,3.5}));
    std::vector<double> output_vec = doubleVector1.add(doubleVector2).getVector();
    EXPECT_DOUBLE_EQ(2.6, output_vec[0]);
    EXPECT_DOUBLE_EQ(4.7, output_vec[1]);
    EXPECT_DOUBLE_EQ(6.8, output_vec[2]);   
}

TEST(test_DoubleVector_add_IntVector, BasicAssertions) {
    linear_hlcr::DoubleVector doubleVector = 
            linear_hlcr::DoubleVector(std::vector<double>({1.1,2.2,3.3}));
    linear_hlcr::IntVector intVector = linear_hlcr::IntVector(std::vector<int>({1,2,3}));
    std::vector<double> output_vec = doubleVector.add(intVector).getVector();
    EXPECT_DOUBLE_EQ(2.1, output_vec[0]);
    EXPECT_DOUBLE_EQ(4.2, output_vec[1]);
    EXPECT_DOUBLE_EQ(6.3, output_vec[2]);   
}


TEST(test_DoubleVector_add_Double, BasicAssertions) {
    linear_hlcr::DoubleVector doubleVector = 
            linear_hlcr::DoubleVector(std::vector<double>({1.1,2.2,3.3}));
    std::vector<double> output_vec = doubleVector.add(-1.5).getVector();
    EXPECT_DOUBLE_EQ(-0.4, output_vec[0]);
    EXPECT_DOUBLE_EQ(0.7, output_vec[1]);
    EXPECT_DOUBLE_EQ(1.8, output_vec[2]);   
}

TEST(test_DoubleVector_dot, BasicAssertions) {
    linear_hlcr::DoubleVector doubleVector1 = 
            linear_hlcr::DoubleVector(std::vector<double>({1.1,2.2,3.3}));
    linear_hlcr::DoubleVector doubleVector2 = 
            linear_hlcr::DoubleVector(std::vector<double>({1.5,2.5,3.5}));
    EXPECT_DOUBLE_EQ(18.7, doubleVector1.dot(doubleVector2));  
}

TEST(test_DoubleVector_mul_SymmetricMatrix, BasicAssertions) {
    linear_hlcr::DoubleVector doubleVector = 
            linear_hlcr::DoubleVector(std::vector<double>({1.1,2.2}));
    linear_hlcr::SymmetricMatrix symmetricMatrix = 
            linear_hlcr::SymmetricMatrix::create(std::vector<double>({1,2,2,3}), 2);
    linear_hlcr::DoubleVector output = doubleVector.mul(symmetricMatrix);
    std::vector<double> output_vec = output.getVector();
    EXPECT_DOUBLE_EQ(5.5, output_vec[0]);
    EXPECT_DOUBLE_EQ(8.8, output_vec[1]);
}

TEST(test_DoubleVector_mul_Double, BasicAssertions) {
    linear_hlcr::DoubleVector doubleVector = 
            linear_hlcr::DoubleVector(std::vector<double>({1.1,2.2,3.3}));
    std::vector<double> output_vec = doubleVector.mul(2).getVector();
    EXPECT_DOUBLE_EQ(2.2, output_vec[0]);
    EXPECT_DOUBLE_EQ(4.4, output_vec[1]);
    EXPECT_DOUBLE_EQ(6.6, output_vec[2]);   
}

TEST(test_DoubleVector_logsumexp, BasicAssertions) {
    linear_hlcr::DoubleVector doubleVector = 
            linear_hlcr::DoubleVector(std::vector<double>({1,2,3,4,5}));
    // Used scipy.special.logsumexp to create this tast case
    EXPECT_DOUBLE_EQ(5.451914395937593, doubleVector.logsumexp());
}

TEST(test_DoubleVector_selfOuterProduct, BasicAssertions) {
    linear_hlcr::DoubleVector doubleVector = 
            linear_hlcr::DoubleVector(std::vector<double>({1.1,2.2}));
    linear_hlcr::SymmetricMatrix symmetricMatrix =
            doubleVector.selfOuterProduct();
    std::vector<double> output_vec = symmetricMatrix.getMatrix();
    EXPECT_DOUBLE_EQ(1.21, output_vec[0]);
    EXPECT_DOUBLE_EQ(2.42, output_vec[1]);
    EXPECT_DOUBLE_EQ(2.42, output_vec[2]);  
    EXPECT_DOUBLE_EQ(4.84, output_vec[3]); 
}

TEST(test_DoubleVector_argmax, BasicAssertions) {
    linear_hlcr::DoubleVector doubleVector = 
            linear_hlcr::DoubleVector(std::vector<double>({1.1,2.2,3.3,2,2,1,1}));
    EXPECT_EQ(2, doubleVector.argmax());
}   

TEST(test_DoubleVector_max, BasicAssertions) {
    linear_hlcr::DoubleVector doubleVector = 
            linear_hlcr::DoubleVector(std::vector<double>({1.1,2.2,3.3,2,2,1,1}));
    EXPECT_DOUBLE_EQ(3.3, doubleVector.max());
}

TEST(test_DoubleVector_log, BasicAssertions) {
    linear_hlcr::DoubleVector doubleVector = 
            linear_hlcr::DoubleVector(std::vector<double>({1.1,2.2,3.3}));
    std::vector<double> output_vec = linear_hlcr::DoubleVector::log(doubleVector).getVector();
    // Used numpy to compute these test cases
    EXPECT_DOUBLE_EQ(0.09531017980432493, output_vec[0]);
    EXPECT_DOUBLE_EQ(0.7884573603642703, output_vec[1]);
    EXPECT_DOUBLE_EQ(1.1939224684724346, output_vec[2]);  
}

TEST(test_DoubleVector_exp, BasicAssertions) {
    linear_hlcr::DoubleVector doubleVector = 
            linear_hlcr::DoubleVector(std::vector<double>({1.1,2.2,3.3}));
    std::vector<double> output_vec = linear_hlcr::DoubleVector::exp(doubleVector).getVector();
    // Used numpy to compute these test cases
    EXPECT_DOUBLE_EQ(3.0041660239464334, output_vec[0]);
    EXPECT_DOUBLE_EQ(9.025013499434122, output_vec[1]);
    EXPECT_DOUBLE_EQ(27.112638920657883, output_vec[2]);  
}
