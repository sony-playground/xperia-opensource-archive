#include <fstream>
#include <memory>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tensor/tensor.h"
#include "tensor/tensor_shape.h"
#include "LinearHLCR/MatrixAndVector.h"
#include "FLException.h"

TEST(TestFLExceptionForMatrixAndVector, SymmetricMatrixFromTensor_Success1)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({1, 1}));
    std::vector<float> vector_float { 101.1 };
    std::unique_ptr<fl::Tensor> tensor(fl::Tensor::newTensor(vector_float, shape));

    ASSERT_NO_THROW({
        auto symmetric_matrix = linear_hlcr::SymmetricMatrix::fromTensor(*(tensor.get()));
    });
}

TEST(TestFLExceptionForMatrixAndVector, SymmetricMatrixFromTensor_Success2)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({2, 2}));
    std::vector<float> vector_float { 101.1, 101.2, 101.2, 201.2 };
    std::unique_ptr<fl::Tensor> tensor(fl::Tensor::newTensor(vector_float, shape));

    ASSERT_NO_THROW({
        auto symmetric_matrix = linear_hlcr::SymmetricMatrix::fromTensor(*(tensor.get()));
    });
}

//
// MatrixAndVector.cpp:14:        THROW_FL_EXCEPTION(str_format("Invalid tensor dimension. must be 2 (!= %d).", dims.size()));
//
TEST(TestFLExceptionForMatrixAndVector, SymmetricMatrixFromTensor_Failed1)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({2, 2, 2}));
    std::vector<float> vector_float { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0 };
    std::unique_ptr<fl::Tensor> tensor(fl::Tensor::newTensor(vector_float, shape));

    try {
        auto symmetric_matrix = linear_hlcr::SymmetricMatrix::fromTensor(*(tensor.get()));
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Invalid tensor dimension\\. must be 2 \\(!= 3\\)\\. \\[LinearHLCR/MatrixAndVector\\.cpp:[0-9]+\\]"));
    }
}

//
// MatrixAndVector.cpp:17:        THROW_FL_EXCEPTION(str_format("Element does not match. (%d != %d).", dims[0], dims[1]));
//
TEST(TestFLExceptionForMatrixAndVector, SymmetricMatrixFromTensor_Failed2)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({1, 2}));
    std::vector<float> vector_float { 101.1, 101.2 };
    std::unique_ptr<fl::Tensor> tensor(fl::Tensor::newTensor(vector_float, shape));

    try {
        auto symmetric_matrix = linear_hlcr::SymmetricMatrix::fromTensor(*(tensor.get()));
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Different size of row and column\\. \\(1 != 2\\)\\. \\[LinearHLCR/MatrixAndVector\\.cpp:[0-9]+\\]"));
    }
}

TEST(TestFLExceptionForMatrixAndVector, SymmetricMatrixFromTensor_Success3)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({2, 2}));
    std::vector<float> vector_float { 101.1, 201.1, 201.1, 202.2 };
    std::unique_ptr<fl::Tensor> tensor(fl::Tensor::newTensor(vector_float, shape));

    ASSERT_NO_THROW({
        auto symmetric_matrix = linear_hlcr::SymmetricMatrix::fromTensor(*(tensor.get()));
    });
}

//
// MatrixAndVector.cpp:24:                THROW_FL_EXCEPTION(str_format("Value does not match. (%f != %f)(i:%d j:%d dims[0]:%d", data[i*dims[0]+j], data[j*dims[0]+i], i, j, dims[0]));
//
TEST(TestFLExceptionForMatrixAndVector, SymmetricMatrixFromTensor_Failed3)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({2, 2}));
    std::vector<float> vector_float { 101.1, 101.2, 201.1, 202.2 };
    std::unique_ptr<fl::Tensor> tensor(fl::Tensor::newTensor(vector_float, shape));

    try {
        auto symmetric_matrix = linear_hlcr::SymmetricMatrix::fromTensor(*(tensor.get()));
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Value does not match\\. \\(101\\.199997 != 201\\.100006\\)\\(i:0 j:1 dims\\[0\\]:2 \\[LinearHLCR/MatrixAndVector\\.cpp:[0-9]+\\]"));
    }
}

TEST(TestFLExceptionForMatrixAndVector, SymmetricMatrixCreate_Success)
{
    std::vector<double> vector_double { 101.1, 201.1, 201.1, 202.2 };
    int dim = 2;

    ASSERT_NO_THROW({
        auto symmetric_matrix = linear_hlcr::SymmetricMatrix::create(vector_double, dim);
    });
}

//
// MatrixAndVector.cpp:33:        THROW_FL_EXCEPTION(str_format("Data size does not match. (data:%d dim:%d^2).", data.size(), dim));
//
TEST(TestFLExceptionForMatrixAndVector, SymmetricMatrixCreate_Failed1)
{
    std::vector<double> vector_double { 101.1, 201.1, 201.1, 202.2 };
    int dim = 3;

    try {
        auto symmetric_matrix = linear_hlcr::SymmetricMatrix::create(vector_double, dim);
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Data size does not match\\. \\(data:4 dim:3\\^2\\)\\. \\[LinearHLCR/MatrixAndVector\\.cpp:[0-9]+\\]"));
    }
}

//
// MatrixAndVector.cpp:38:                THROW_FL_EXCEPTION(str_format("Value does not match. (%f != %f)(i:%d j:%d dim:%d", data[i*dim+j], data[j*dim+i], i, j, dim));
//
TEST(TestFLExceptionForMatrixAndVector, SymmetricMatrixCreate_Failed2)
{
    std::vector<double> vector_double { 101.1, 101.2, 201.1, 202.2 };
    int dim = 2;

    try {
        auto symmetric_matrix = linear_hlcr::SymmetricMatrix::create(vector_double, dim);
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Value does not match. \\(101\\.200000 != 201\\.100000\\)\\(i:0 j:1 dim:2 \\[LinearHLCR/MatrixAndVector\\.cpp:[0-9]+\\]"));
    }
}

TEST(TestFLExceptionForMatrixAndVector, AddSymmetricMatrix_Success)
{
    std::vector<double> vector_double_A { 1.1, 2.2, 2.2, 3.3 };
    int dim_A = 2;

    std::vector<double> vector_double_B { 4.4, 5.5, 5.5, 6.6 };
    int dim_B = 2;

    ASSERT_NO_THROW({
        linear_hlcr::SymmetricMatrix symmetric_matrix_A = linear_hlcr::SymmetricMatrix::create(vector_double_A, dim_A);
        linear_hlcr::SymmetricMatrix symmetric_matrix_B = linear_hlcr::SymmetricMatrix::create(vector_double_B, dim_B);

        symmetric_matrix_A.add(symmetric_matrix_B);
    });
}

//
// MatrixAndVector.cpp:60:        THROW_FL_EXCEPTION(str_format("Dimension does not match. (input:%d this:%d).", input.getDim(), this->_dim));
//
TEST(TestFLExceptionForMatrixAndVector, AddSymmetricMatrix_Failed)
{
    std::vector<double> vector_double_A { 1.1, 2.2, 2.2, 3.3 };
    int dim_A = 2;

    std::vector<double> vector_double_B { 1.1, 2.2, 3.3, 2.2, 5.5, 6.6, 3.3, 6.6, 9.9 };
    int dim_B = 3;

    ASSERT_NO_THROW({
        linear_hlcr::SymmetricMatrix symmetric_matrix_A = linear_hlcr::SymmetricMatrix::create(vector_double_A, dim_A);
        linear_hlcr::SymmetricMatrix symmetric_matrix_B = linear_hlcr::SymmetricMatrix::create(vector_double_B, dim_B);

        try {
            symmetric_matrix_A.add(symmetric_matrix_B);
            FAIL();
        }
        catch (FLException& ex) {
            const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
            std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
            ASSERT_THAT(ex.what(), testing::MatchesRegex("Dimension does not match\\. \\(input:3 this:2\\)\\. \\[LinearHLCR/MatrixAndVector\\.cpp:[0-9]+\\]"));
        }
    });
}

TEST(TestFLExceptionForMatrixAndVector, IntVectorFromTensor_Success)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({2}));
    std::vector<int> vector_int { 1, 2 };
    std::unique_ptr<fl::Tensor> tensor(fl::Tensor::newTensor(vector_int, shape));

    ASSERT_NO_THROW({
        auto int_vector = linear_hlcr::IntVector::fromTensor(*(tensor.get()));
    });
}

//
// MatrixAndVector.cpp:87:        THROW_FL_EXCEPTION(str_format("Invalid tensor dimension. must be 1 (!= %d).", dims.size()));
//
TEST(TestFLExceptionForMatrixAndVector, IntVectorFromTensor_Failed)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({2, 2}));
    std::vector<int> vector_int { 1, 2, 3, 4 };
    std::unique_ptr<fl::Tensor> tensor(fl::Tensor::newTensor(vector_int, shape));

    try {
        auto int_vector = linear_hlcr::IntVector::fromTensor(*(tensor.get()));
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Invalid tensor dimension. must be 1 \\(!= 2\\)\\. \\[LinearHLCR/MatrixAndVector\\.cpp:[0-9]+\\]"));
    }
}

TEST(TestFLExceptionForMatrixAndVector, DoubleVectorFromTensor_Success)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({2}));
    std::vector<double> vector_double { 1, 2 };
    std::unique_ptr<fl::Tensor> tensor(fl::Tensor::newTensor(vector_double, shape));

    ASSERT_NO_THROW({
        auto double_vector = linear_hlcr::DoubleVector::fromTensor(*(tensor.get()));
    });
}

//
// MatrixAndVector.cpp:122:        THROW_FL_EXCEPTION(str_format("Invalid tensor dimension. must be 1 (!= %d).", dims.size()));
//
TEST(TestFLExceptionForMatrixAndVector, DoubleVectorFromTensor_Failed)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({2, 2}));
    std::vector<double> vector_int { 1.1, 2.2, 3.3, 4.4 };
    std::unique_ptr<fl::Tensor> tensor(fl::Tensor::newTensor(vector_int, shape));

    try {
        auto double_vector = linear_hlcr::DoubleVector::fromTensor(*(tensor.get()));
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Invalid tensor dimension. must be 1 \\(!= 2\\)\\. \\[LinearHLCR/MatrixAndVector\\.cpp:[0-9]+\\]"));
    }
}

TEST(TestFLExceptionForMatrixAndVector, AddDoubleVector_Success)
{
    std::vector<double> vector_double_A { 1.1, 2.2, 2.2, 3.3 };
    std::vector<double> vector_double_B { 4.4, 5.5, 5.5, 6.6 };

    ASSERT_NO_THROW({
        linear_hlcr::DoubleVector double_vector_A(vector_double_A);
        linear_hlcr::DoubleVector double_vector_B(vector_double_B);

        double_vector_A.add(double_vector_B);
    });
}

//
// MatrixAndVector.cpp:143:        THROW_FL_EXCEPTION(str_format("Dimension does not match. (input:%d this:%d).", input.getDim(), this->_dim));
//
TEST(TestFLExceptionForMatrixAndVector, AddDoubleVector_Failed)
{
    std::vector<double> vector_double_A { 1.1, 2.2, 2.2, 3.3 };
    std::vector<double> vector_double_B { 1.1, 2.2, 3.3, 2.2, 5.5, 6.6, 3.3, 6.6, 9.9 };

    ASSERT_NO_THROW({
        linear_hlcr::DoubleVector double_vector_A(vector_double_A);
        linear_hlcr::DoubleVector double_vector_B(vector_double_B);

        try {
            double_vector_A.add(double_vector_B);
            FAIL();
        }
        catch (FLException& ex) {
            const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
            std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
            ASSERT_THAT(ex.what(), testing::MatchesRegex("Dimension does not match\\. \\(input:9 this:4\\)\\. \\[LinearHLCR/MatrixAndVector\\.cpp:[0-9]+\\]"));
        }
    });
}

TEST(TestFLExceptionForMatrixAndVector, AddIntVectorToDoubleVector_Success)
{
    std::vector<double> vector_double { 1.1, 2.2, 2.2, 3.3 };
    std::vector<int> vector_int { 4, 5, 5, 6 };

    ASSERT_NO_THROW({
        linear_hlcr::DoubleVector double_vector(vector_double);
        linear_hlcr::IntVector int_vector(vector_int);

        double_vector.add(int_vector);
    });
}

//
// MatrixAndVector.cpp:155:        THROW_FL_EXCEPTION(str_format("Dimension does not match. (input:%d this:%d).", input.getDim(), this->_dim));
//
TEST(TestFLExceptionForMatrixAndVector, AddIntVectorToDoubleVector_Failed)
{
    std::vector<double> vector_double { 1.1, 2.2, 2.2, 3.3 };
    std::vector<int> vector_int { 4, 5 };

    ASSERT_NO_THROW({
        linear_hlcr::DoubleVector double_vector(vector_double);
        linear_hlcr::IntVector int_vector(vector_int);

        try {
            double_vector.add(int_vector);
            FAIL();
        }
        catch (FLException& ex) {
            const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
            std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
            ASSERT_THAT(ex.what(), testing::MatchesRegex("Dimension does not match\\. \\(input:2 this:4\\)\\. \\[LinearHLCR/MatrixAndVector\\.cpp:[0-9]+\\]"));
        }
    });
}

TEST(TestFLExceptionForMatrixAndVector, DotDoubleVector_Success)
{
    std::vector<double> vector_double_A { 1.1, 2.2, 2.2, 3.3 };
    std::vector<double> vector_double_B { 4.4, 5.5, 5.5, 6.6 };

    ASSERT_NO_THROW({
        linear_hlcr::DoubleVector double_vector_A(vector_double_A);
        linear_hlcr::DoubleVector double_vector_B(vector_double_B);

        double_vector_A.dot(double_vector_B);
    });
}

//
// MatrixAndVector.cpp:175:        THROW_FL_EXCEPTION(str_format("Dimension does not match. (input:%d this:%d).", input_vector.getDim(), this->_dim));
//
TEST(TestFLExceptionForMatrixAndVector, DotDoubleVector_Failed)
{
    std::vector<double> vector_double_A { 1.1, 2.2, 2.2, 3.3 };
    std::vector<double> vector_double_B { 1.1, 2.2, 3.3, 2.2, 5.5, 6.6, 3.3, 6.6, 9.9 };

    ASSERT_NO_THROW({
        linear_hlcr::DoubleVector double_vector_A(vector_double_A);
        linear_hlcr::DoubleVector double_vector_B(vector_double_B);

        try {
            double_vector_A.dot(double_vector_B);
            FAIL();
        }
        catch (FLException& ex) {
            const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
            std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
            ASSERT_THAT(ex.what(), testing::MatchesRegex("Dimension does not match\\. \\(input:9 this:4\\)\\. \\[LinearHLCR/MatrixAndVector\\.cpp:[0-9]+\\]"));
        }
    });
}

TEST(TestFLExceptionForMatrixAndVector, MulSymmetricMatrixToDoubleVector_Success)
{
    std::vector<double> vector_double_A { 1.1, 2.2 };
    std::vector<double> vector_double_B { 1.1, 2.2, 2.2, 3.3 };
    int dim_B = 2;

    ASSERT_NO_THROW({
        linear_hlcr::DoubleVector double_vector_A(vector_double_A);
        linear_hlcr::SymmetricMatrix symmetric_matrix_B = linear_hlcr::SymmetricMatrix::create(vector_double_B, dim_B);

        double_vector_A.mul(symmetric_matrix_B);
    });
}

//
// MatrixAndVector.cpp:187:        THROW_FL_EXCEPTION(str_format("Dimension does not match. (input:%d this:%d).", input.getDim(), this->_dim));
//
TEST(TestFLExceptionForMatrixAndVector, MulSymmetricMatrixToDoubleVector_Failed)
{
    std::vector<double> vector_double_A { 1.1, 2.2, 2.2, 3.3 };
    std::vector<double> vector_double_B { 1.1, 2.2, 2.2, 3.3 };
    int dim_B = 2;

    ASSERT_NO_THROW({
        linear_hlcr::DoubleVector double_vector_A(vector_double_A);
        linear_hlcr::SymmetricMatrix symmetric_matrix_B = linear_hlcr::SymmetricMatrix::create(vector_double_B, dim_B);

        try {
            double_vector_A.mul(symmetric_matrix_B);
        }
        catch (FLException& ex) {
            const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
            std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
            ASSERT_THAT(ex.what(), testing::MatchesRegex("Dimension does not match\\. \\(input:2 this:4\\)\\. \\[LinearHLCR/MatrixAndVector\\.cpp:[0-9]+\\]"));
        }
    });
}
