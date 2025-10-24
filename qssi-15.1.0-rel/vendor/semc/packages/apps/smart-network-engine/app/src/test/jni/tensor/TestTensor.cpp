#include <fstream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tensor/tensor.h"
#include "FLException.h"

TEST(TestTensor, newTensor_Vector_Integer)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({5}));
    std::vector<int> vector_int { 1, 2, 3, 4, 5 };
    std::shared_ptr<fl::Tensor> tensor_int(fl::Tensor::newTensor(vector_int, shape));
    ASSERT_EQ(1, tensor_int->dims());
    ASSERT_EQ(5, tensor_int->getDim(0));

    auto output_int = tensor_int->intVector();
    ASSERT_EQ(5, output_int.size());

    ASSERT_EQ(1, output_int[0]);
    ASSERT_EQ(2, output_int[1]);
    ASSERT_EQ(3, output_int[2]);
    ASSERT_EQ(4, output_int[3]);
    ASSERT_EQ(5, output_int[4]);

    auto dims = tensor_int->getDims();
    ASSERT_EQ(5, dims[0]);
}

TEST(TestTensor, newTensor_Vector_Long)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({7}));
    std::vector<long> vector_long { 1, 2, 3, 4, 5, 6, 7 };
    std::shared_ptr<fl::Tensor> tensor_long(fl::Tensor::newTensor(vector_long, shape));
    ASSERT_EQ(1, tensor_long->dims());
    ASSERT_EQ(7, tensor_long->getDim(0));

    auto output_long = tensor_long->longVector();
    ASSERT_EQ(7, output_long.size());

    ASSERT_EQ(1, output_long[0]);
    ASSERT_EQ(2, output_long[1]);
    ASSERT_EQ(3, output_long[2]);
    ASSERT_EQ(4, output_long[3]);
    ASSERT_EQ(5, output_long[4]);
    ASSERT_EQ(6, output_long[5]);
    ASSERT_EQ(7, output_long[6]);

    auto dims = tensor_long->getDims();
    ASSERT_EQ(7, dims[0]);
}

TEST(TestTensor, newTensor_Vector_Double)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({2}));
    std::vector<double> vector_double { 1.1, 1.2 };
    std::shared_ptr<fl::Tensor> tensor_double(fl::Tensor::newTensor(vector_double, shape));
    ASSERT_EQ(1, tensor_double->dims());
    ASSERT_EQ(2, tensor_double->getDim(0));

    auto output_double = tensor_double->doubleVector();
    ASSERT_EQ(2, output_double.size());

    ASSERT_DOUBLE_EQ(1.1, output_double[0]);
    ASSERT_DOUBLE_EQ(1.2, output_double[1]);

    auto dims = tensor_double->getDims();
    ASSERT_EQ(2, dims[0]);
}

TEST(TestTensor, newTensor_Vector_Float)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({2}));
    std::vector<float> vector_float { 1.1, 1.2 };
    std::shared_ptr<fl::Tensor> tensor_float(fl::Tensor::newTensor(vector_float, shape));
    ASSERT_EQ(1, tensor_float->dims());
    ASSERT_EQ(2, tensor_float->getDim(0));

    auto output_float = tensor_float->floatVector();
    ASSERT_EQ(2, output_float.size());

    ASSERT_FLOAT_EQ(1.1, output_float[0]);
    ASSERT_FLOAT_EQ(1.2, output_float[1]);

    auto dims = tensor_float->getDims();
    ASSERT_EQ(2, dims[0]);
}

TEST(TestTensor, newTensor_Vector_String)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({3}));
    std::vector<std::string> vector_string { "V1", "V2", "V3" };
    std::shared_ptr<fl::Tensor> tensor_string(fl::Tensor::newTensor(vector_string, shape));
    ASSERT_EQ(1, tensor_string->dims());
    ASSERT_EQ(3, tensor_string->getDim(0));

    auto output_string = tensor_string->textVector();
    ASSERT_EQ(3, output_string.size());

    ASSERT_EQ("V1", output_string[0]);
    ASSERT_EQ("V2", output_string[1]);
    ASSERT_EQ("V3", output_string[2]);

    auto dims = tensor_string->getDims();
    ASSERT_EQ(3, dims[0]);
}

TEST(TestTensor, newTensor_2D_Integer)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({2, 3}));
    std::vector<int> vector_int { 11, 12, 13, 21, 22, 23 };
    std::shared_ptr<fl::Tensor> tensor_int(fl::Tensor::newTensor(vector_int, shape));
    ASSERT_EQ(2, tensor_int->dims());
    ASSERT_EQ(2, tensor_int->getDim(0));
    ASSERT_EQ(3, tensor_int->getDim(1));

    auto output_int = tensor_int->intVector();
    ASSERT_EQ(6, output_int.size());

    ASSERT_EQ(11, output_int[0]);
    ASSERT_EQ(12, output_int[1]);
    ASSERT_EQ(13, output_int[2]);
    ASSERT_EQ(21, output_int[3]);
    ASSERT_EQ(22, output_int[4]);
    ASSERT_EQ(23, output_int[5]);

    auto dims = tensor_int->getDims();
    ASSERT_EQ(2, dims[0]);
    ASSERT_EQ(3, dims[1]);
}

TEST(TestTensor, newTensor_2D_Long)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({3, 2}));
    std::vector<long> vector_long { 11, 12, 21, 22, 31, 32 };
    std::shared_ptr<fl::Tensor> tensor_long(fl::Tensor::newTensor(vector_long, shape));
    ASSERT_EQ(2, tensor_long->dims());
    ASSERT_EQ(3, tensor_long->getDim(0));
    ASSERT_EQ(2, tensor_long->getDim(1));

    auto output_long = tensor_long->longVector();
    ASSERT_EQ(6, output_long.size());

    ASSERT_EQ(11, output_long[0]);
    ASSERT_EQ(12, output_long[1]);
    ASSERT_EQ(21, output_long[2]);
    ASSERT_EQ(22, output_long[3]);
    ASSERT_EQ(31, output_long[4]);
    ASSERT_EQ(32, output_long[5]);

    auto dims = tensor_long->getDims();
    ASSERT_EQ(3, dims[0]);
    ASSERT_EQ(2, dims[1]);
}

TEST(TestTensor, newTensor_2D_Double)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({2, 3}));
    std::vector<double> vector_double { 1.1, 1.2, 1.3, 2.1, 2.2, 2.3 };
    std::shared_ptr<fl::Tensor> tensor_double(fl::Tensor::newTensor(vector_double, shape));
    ASSERT_EQ(2, tensor_double->dims());
    ASSERT_EQ(2, tensor_double->getDim(0));
    ASSERT_EQ(3, tensor_double->getDim(1));

    auto output_double = tensor_double->doubleVector();
    ASSERT_EQ(6, output_double.size());

    ASSERT_DOUBLE_EQ(1.1, output_double[0]);
    ASSERT_DOUBLE_EQ(1.2, output_double[1]);
    ASSERT_DOUBLE_EQ(1.3, output_double[2]);
    ASSERT_DOUBLE_EQ(2.1, output_double[3]);
    ASSERT_DOUBLE_EQ(2.2, output_double[4]);
    ASSERT_DOUBLE_EQ(2.3, output_double[5]);

    auto dims = tensor_double->getDims();
    ASSERT_EQ(2, dims[0]);
    ASSERT_EQ(3, dims[1]);
}

TEST(TestTensor, newTensor_2D_Float)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({2, 3}));
    std::vector<float> vector_float { 1.1, 1.2, 1.3, 2.1, 2.2, 2.3 };
    std::shared_ptr<fl::Tensor> tensor_float(fl::Tensor::newTensor(vector_float, shape));
    ASSERT_EQ(2, tensor_float->dims());
    ASSERT_EQ(2, tensor_float->getDim(0));
    ASSERT_EQ(3, tensor_float->getDim(1));

    auto output_float = tensor_float->floatVector();
    ASSERT_EQ(6, output_float.size());

    ASSERT_FLOAT_EQ(1.1, output_float[0]);
    ASSERT_FLOAT_EQ(1.2, output_float[1]);
    ASSERT_FLOAT_EQ(1.3, output_float[2]);
    ASSERT_FLOAT_EQ(2.1, output_float[3]);
    ASSERT_FLOAT_EQ(2.2, output_float[4]);
    ASSERT_FLOAT_EQ(2.3, output_float[5]);

    auto dims = tensor_float->getDims();
    ASSERT_EQ(2, dims[0]);
    ASSERT_EQ(3, dims[1]);
}

TEST(TestTensor, newTensor_2D_String)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({3, 2}));
    std::vector<std::string> vector_string { "C1R1", "C2R1", "C1R2", "C2R2", "C1R3", "C2R3" };
    std::shared_ptr<fl::Tensor> tensor_string(fl::Tensor::newTensor(vector_string, shape));
    ASSERT_EQ(2, tensor_string->dims());
    ASSERT_EQ(3, tensor_string->getDim(0));
    ASSERT_EQ(2, tensor_string->getDim(1));

    auto output_string = tensor_string->textVector();
    ASSERT_EQ(6, output_string.size());

    ASSERT_EQ("C1R1", output_string[0]);
    ASSERT_EQ("C2R1", output_string[1]);
    ASSERT_EQ("C1R2", output_string[2]);
    ASSERT_EQ("C2R2", output_string[3]);
    ASSERT_EQ("C1R3", output_string[4]);
    ASSERT_EQ("C2R3", output_string[5]);

    auto dims = tensor_string->getDims();
    ASSERT_EQ(3, dims[0]);
    ASSERT_EQ(2, dims[1]);
}

TEST(TestTensor, newTensor_Scalar_Integer)
{
    const int scalar_int = 2147483647;  // Java Integer.MAX_VALUE
    std::shared_ptr<fl::Tensor> tensor_int(fl::Tensor::newTensor(scalar_int));
    auto value_int = tensor_int->intValue();
    ASSERT_EQ(scalar_int, value_int);
}

TEST(TestTensor, newTensor_Scalar_Long)
{
    const long scalar_long = 9223372036854775807;   // Java Long.MAX_VALUE
    std::shared_ptr<fl::Tensor> tensor_long(fl::Tensor::newTensor(scalar_long));
    auto value_long = tensor_long->longValue();
    ASSERT_EQ(scalar_long, value_long);
}

TEST(TestTensor, newTensor_Scalar_Double)
{
    const double scalar_double = 179769313486231570000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.000000;  // Java Double.MAX_VALUE
    std::shared_ptr<fl::Tensor> tensor_double(fl::Tensor::newTensor(scalar_double));
    auto value_double = tensor_double->doubleValue();
    ASSERT_EQ(scalar_double, value_double);
}

TEST(TestTensor, newTensor_Scalar_Float)
{
    const float scalar_float = 340282346638528860000000000000000000000.000000;  // Java Float.MAX_VALUE
    std::shared_ptr<fl::Tensor> tensor_float(fl::Tensor::newTensor(scalar_float));
    auto value_float = tensor_float->floatValue();
    ASSERT_EQ(scalar_float, value_float);
}

TEST(TestTensor, newTensor_Scalar_String)
{
    const std::string scalar_string = "Hello";
    std::shared_ptr<fl::Tensor> tensor_string(fl::Tensor::newTensor(scalar_string));
    auto value_string = tensor_string->textValue();
    ASSERT_EQ(scalar_string, value_string);
}

TEST(TestTensor, getDim_Vector_BelowLowerLimit)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({5}));
    std::vector<int> vector_int { 1, 2, 3, 4, 5 };
    std::shared_ptr<fl::Tensor> tensor_int(fl::Tensor::newTensor(vector_int, shape));
    ASSERT_NO_THROW({
        tensor_int->getDim(0);
    });
    try {
        tensor_int->getDim(-1);
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Out of the range of Shape's dimensions\\. \\(d=-1\\) \\[tensor/tensor_shape\\.cc:[0-9]+\\]"));
    }
}

TEST(TestTensor, getDim_Vector_ExceededUpperLimit)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({5}));
    std::vector<int> vector_int { 1, 2, 3, 4, 5 };
    std::shared_ptr<fl::Tensor> tensor_int(fl::Tensor::newTensor(vector_int, shape));
    ASSERT_NO_THROW({
        tensor_int->getDim(0);
    });
    try {
        tensor_int->getDim(1);
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Out of the range of Shape's dimensions\\. \\(d=1\\) \\[tensor/tensor_shape\\.cc:[0-9]+\\]"));
    }
}

TEST(TestTensor, getDim_Matrix_BelowLowerLimit)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({2, 2}));
    std::vector<int> vector_int { 1, 2, 3, 4 };
    std::shared_ptr<fl::Tensor> tensor_int(fl::Tensor::newTensor(vector_int, shape));
    ASSERT_NO_THROW({
        tensor_int->getDim(0);
    });
    try {
        tensor_int->getDim(-1);
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Out of the range of Shape's dimensions\\. \\(d=-1\\) \\[tensor/tensor_shape\\.cc:[0-9]+\\]"));
    }
}

TEST(TestTensor, getDim_Matrix_ExceededUpperLimit)
{
    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({2, 2}));
    std::vector<int> vector_int { 1, 2, 3, 4 };
    std::shared_ptr<fl::Tensor> tensor_int(fl::Tensor::newTensor(vector_int, shape));
    ASSERT_NO_THROW({
        tensor_int->getDim(1);
    });
    try {
        tensor_int->getDim(2);
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Out of the range of Shape's dimensions\\. \\(d=2\\) \\[tensor/tensor_shape\\.cc:[0-9]+\\]"));
    }
}

TEST(TestTensor, fromJsonString_textValue)
{
    auto tensorJson = R"(
        {
            "shape": [1],
            "value": ["2"]
        }
    )";

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJsonString(tensorJson));
        ASSERT_TRUE(NULL != tensor);

        ASSERT_EQ("2", tensor->textValue());
        ASSERT_EQ(1, tensor->dims());
        ASSERT_EQ(1, tensor->getDim(0));
        ASSERT_EQ(1, tensor->size());
        ASSERT_EQ(1, tensor->getDims()[0]);
    });
}

TEST(TestTensor, fromJsonString_intValue)
{
    auto tensorJson = R"(
        {
            "shape": [1],
            "value": [0]
        }
    )";

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJsonString(tensorJson));
        ASSERT_TRUE(NULL != tensor);

        ASSERT_EQ(0, tensor->intValue());
        ASSERT_EQ(1, tensor->dims());
        ASSERT_EQ(1, tensor->getDim(0));
        ASSERT_EQ(1, tensor->size());
        ASSERT_EQ(1, tensor->getDims()[0]);
    });
}

TEST(TestTensor, fromJsonString_floatVector)
{
    auto tensorJson = R"(
        {
            "shape": [10, 13],
            "value": [
                0.00919959, 0.005900520, -71.3668, 101.9570, 0.1282080, 48.1664, 505.955,  4.12031,  2.46073, 1.0, 0.0,  3.0, 0.0,
                0.02026040, 0.003888820, -72.3655,  69.8636, 0.0901836, 48.3598, 453.684, 12.01600,  6.63711, 1.0, 0.0, -1.0, 0.0,
                0.01747060, 0.003854900, -71.3841,  91.0585, 0.1129770, 56.2462, 342.200,  8.13061,  4.31444, 1.0, 1.0,  0.0, 1.0, 
                0.00490104, 0.010158200, -73.2754,  38.3956, 0.1490340, 41.7677, 259.172, 10.42850,  5.40658, 1.0, 0.0,  1.0, 0.0, 
                0.00790976, 0.002190260, -67.7990,  78.8058, 0.0912105, 26.9920, 445.377,  7.08194, 21.80150, 1.0, 1.0,  0.0, 0.0, 
                0.00485115, 0.000657603, -72.7487,  86.0242, 0.1023380, 22.6156, 434.731, 13.50370,  3.66407, 0.0, 1.0, -1.0, 1.0, 
                0.00423836, 0.004264430, -72.4268, 179.4990, 0.0634936, 64.3289, 341.561, 15.21440,  3.56458, 0.0, 0.0,  6.0, 0.0, 
                0.00157580, 0.001915920, -68.9584, 248.2220, 0.0431619, 40.8806, 849.286,  4.76397,  3.16666, 0.0, 1.0,  1.0, 1.0, 
                0.00356906, 0.008460330, -66.9629,  25.3650, 0.0925546, 66.9877, 918.402,  5.48834,  3.55120, 0.0, 0.0,  0.0, 0.0, 
                0.00529535, 0.001773420, -71.5594, 214.4830, 0.0530862, 41.3451, 728.858,  2.70741, 13.62140, 0.0, 1.0,  3.0, 0.0
            ]
        }
    )";

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJsonString(tensorJson));
        ASSERT_TRUE(NULL != tensor);

        ASSERT_FLOAT_EQ(0.00919959, tensor->floatVector()[0]);
        ASSERT_FLOAT_EQ(0.005900520, tensor->floatVector()[1]);
        ASSERT_FLOAT_EQ(3.0, tensor->floatVector()[128]);
        ASSERT_FLOAT_EQ(0.0, tensor->floatVector()[129]);
        ASSERT_EQ(2, tensor->dims());
        ASSERT_EQ(10, tensor->getDim(0));
        ASSERT_EQ(13, tensor->getDim(1));
        ASSERT_EQ(130, tensor->size());
        ASSERT_EQ(10, tensor->getDims()[0]);
        ASSERT_EQ(13, tensor->getDims()[1]);
    });
}

TEST(TestTensor, fromJson_textValue)
{
    auto tensorJson = R"(
        {
            "shape": [1],
            "value": ["2"]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJson(tensorJson));
        ASSERT_TRUE(NULL != tensor);

        ASSERT_EQ("2", tensor->textValue());
        ASSERT_EQ(1, tensor->dims());
        ASSERT_EQ(1, tensor->getDim(0));
        ASSERT_EQ(1, tensor->size());
        ASSERT_EQ(1, tensor->getDims()[0]);
    });
}

TEST(TestTensor, fromJson_intValue)
{
    auto tensorJson = R"(
        {
            "shape": [1],
            "value": [0]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJson(tensorJson));
        ASSERT_TRUE(NULL != tensor);

        ASSERT_EQ(0, tensor->intValue());
        ASSERT_EQ(1, tensor->dims());
        ASSERT_EQ(1, tensor->getDim(0));
        ASSERT_EQ(1, tensor->size());
        ASSERT_EQ(1, tensor->getDims()[0]);
    });
}

TEST(TestTensor, fromJson_floatVector)
{
    auto tensorJson = R"(
        {
            "shape": [10, 13],
            "value": [
                0.00919959, 0.005900520, -71.3668, 101.9570, 0.1282080, 48.1664, 505.955,  4.12031,  2.46073, 1.0, 0.0,  3.0, 0.0,
                0.02026040, 0.003888820, -72.3655,  69.8636, 0.0901836, 48.3598, 453.684, 12.01600,  6.63711, 1.0, 0.0, -1.0, 0.0,
                0.01747060, 0.003854900, -71.3841,  91.0585, 0.1129770, 56.2462, 342.200,  8.13061,  4.31444, 1.0, 1.0,  0.0, 1.0, 
                0.00490104, 0.010158200, -73.2754,  38.3956, 0.1490340, 41.7677, 259.172, 10.42850,  5.40658, 1.0, 0.0,  1.0, 0.0, 
                0.00790976, 0.002190260, -67.7990,  78.8058, 0.0912105, 26.9920, 445.377,  7.08194, 21.80150, 1.0, 1.0,  0.0, 0.0, 
                0.00485115, 0.000657603, -72.7487,  86.0242, 0.1023380, 22.6156, 434.731, 13.50370,  3.66407, 0.0, 1.0, -1.0, 1.0, 
                0.00423836, 0.004264430, -72.4268, 179.4990, 0.0634936, 64.3289, 341.561, 15.21440,  3.56458, 0.0, 0.0,  6.0, 0.0, 
                0.00157580, 0.001915920, -68.9584, 248.2220, 0.0431619, 40.8806, 849.286,  4.76397,  3.16666, 0.0, 1.0,  1.0, 1.0, 
                0.00356906, 0.008460330, -66.9629,  25.3650, 0.0925546, 66.9877, 918.402,  5.48834,  3.55120, 0.0, 0.0,  0.0, 0.0, 
                0.00529535, 0.001773420, -71.5594, 214.4830, 0.0530862, 41.3451, 728.858,  2.70741, 13.62140, 0.0, 1.0,  3.0, 0.0
            ]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJson(tensorJson));
        ASSERT_TRUE(NULL != tensor);

        ASSERT_FLOAT_EQ(0.00919959, tensor->floatVector()[0]);
        ASSERT_FLOAT_EQ(0.005900520, tensor->floatVector()[1]);
        ASSERT_FLOAT_EQ(3.0, tensor->floatVector()[128]);
        ASSERT_FLOAT_EQ(0.0, tensor->floatVector()[129]);
        ASSERT_EQ(2, tensor->dims());
        ASSERT_EQ(10, tensor->getDim(0));
        ASSERT_EQ(13, tensor->getDim(1));
        ASSERT_EQ(130, tensor->size());
        ASSERT_EQ(10, tensor->getDims()[0]);
        ASSERT_EQ(13, tensor->getDims()[1]);
    });
}

TEST(TestTensor, fromJsonString_But_json)
{
    auto tensorJson = R"(
        {
            "shape": [1],
            "value": ["2"]
        }
    )"_json;

    try {
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJsonString(tensorJson));
        FAIL();
    }
    catch (json::exception& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_STREQ("[json.exception.type_error.302] type must be string, but is object", ex.what());
    }
}

TEST(TestTensor, fromJsonString_invalid1)
{
    // NOTE: value is not array
    auto tensorJson = R"(
        {
            "shape": [1],
            "value": "2"
        }
    )";

    try {
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJsonString(tensorJson));
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Failed to create tensor\\. Unknown json string\\. \\(\\{\"shape\":\\[1\\],\"value\":\"2\"\\}\\) \\[tensor/tensor\\.cc:[0-9]+\\]"));
    }
}

TEST(TestTensor, fromJsonString_invalid2)
{
    // NOTE: shape is not array
    auto tensorJson = R"(
        {
            "shape": 1,
            "value": ["2"]
        }
    )";

    try {
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJsonString(tensorJson));
        FAIL();
    }
    catch (json::exception& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_STREQ("[json.exception.type_error.302] type must be array, but is number", ex.what());
    }
}

TEST(TestTensor, fromJsonString_invalid3)
{
    // NOTE: value element not enough
    auto tensorJson = R"(
        {
            "shape": [2],
            "value": ["2"]
        }
    )";

    try {
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJsonString(tensorJson));
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Failed to create tensor\\. unmatch size\\. \\(1 != 2\\) \\[tensor/tensor\\.cc:[0-9]+\\]"));
    }
}

TEST(TestTensor, fromJsonString_invalid4)
{
    // NOTE: value invalid json
    auto tensorJson = R"(
        {
            "shape": [2],
            "value": ["1","2",]
        }
    )";

    try {
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJsonString(tensorJson));
        FAIL();
    }
    catch (json::exception& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_STREQ("[json.exception.parse_error.101] parse error at line 4, column 31: syntax error while parsing value - unexpected ']'; expected '[', '{', or a literal", ex.what());
    }
}

TEST(TestTensor, fromJsonString_invalid5)
{
    // NOTE: shape invalid json
    auto tensorJson = R"(
        {
            "shape": {2},
            "value": ["1","2"]
        }
    )";

    try {
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJsonString(tensorJson));
        FAIL();
    }
    catch (json::exception& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_STREQ("[json.exception.parse_error.101] parse error at line 3, column 23: syntax error while parsing object key - unexpected number literal; expected string literal", ex.what());
    }
}

TEST(TestTensor, fromJsonString_invalid6)
{
    // NOTE: value type not support
    auto tensorJson = R"(
        {
            "shape": [1],
            "value": [true]
        }
    )";

    try {
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJsonString(tensorJson));
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Failed to create tensor\\. Unknown json string\\. \\(\\{\"shape\":\\[1\\],\"value\":\\[true\\]\\}\\) \\[tensor/tensor\\.cc:[0-9]+\\]"));
    }
}

TEST(TestTensor, fromJson_But_jsonString)
{
    auto tensorJson = R"(
        {
            "shape": [1],
            "value": ["2"]
        }
    )"_json;

    try {
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJson(tensorJson.dump()));
        FAIL();
    }
    catch (json::exception& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_STREQ("[json.exception.type_error.305] cannot use operator[] with a string argument with string", ex.what());
    }
}


TEST(TestTensor, toJsonString_textValue)
{
    auto tensorJson = R"(
        {
            "shape": [1],
            "value": ["2"]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJson(tensorJson));
        ASSERT_TRUE(NULL != tensor);

        ASSERT_EQ("2", tensor->textValue());
        ASSERT_EQ(1, tensor->dims());
        ASSERT_EQ(1, tensor->getDim(0));
        ASSERT_EQ(1, tensor->size());
        ASSERT_EQ(1, tensor->getDims()[0]);

        std::string jsonString = tensor->toJsonString();
        ASSERT_EQ(R"({"shape":[1],"value":["2"]})", jsonString);
    });
}

TEST(TestTensor, toJsonString_intValue)
{
    auto tensorJson = R"(
        {
            "shape": [1],
            "value": [0]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJson(tensorJson));
        ASSERT_TRUE(NULL != tensor);

        ASSERT_EQ(0, tensor->intValue());
        ASSERT_EQ(1, tensor->dims());
        ASSERT_EQ(1, tensor->getDim(0));
        ASSERT_EQ(1, tensor->size());
        ASSERT_EQ(1, tensor->getDims()[0]);

        std::string jsonString = tensor->toJsonString();
        ASSERT_EQ(R"({"shape":[1],"value":[0]})", jsonString);
    });
}

TEST(TestTensor, toJsonString_floatVector)
{
    auto tensorJson = R"(
        {
            "shape": [10, 13],
            "value": [
                0.00919959, 0.005900520, -71.3668, 101.9570, 0.1282080, 48.1664, 505.955,  4.12031,  2.46073, 1.0, 0.0,  3.0, 0.0,
                0.02026040, 0.003888820, -72.3655,  69.8636, 0.0901836, 48.3598, 453.684, 12.01600,  6.63711, 1.0, 0.0, -1.0, 0.0,
                0.01747060, 0.003854900, -71.3841,  91.0585, 0.1129770, 56.2462, 342.200,  8.13061,  4.31444, 1.0, 1.0,  0.0, 1.0, 
                0.00490104, 0.010158200, -73.2754,  38.3956, 0.1490340, 41.7677, 259.172, 10.42850,  5.40658, 1.0, 0.0,  1.0, 0.0, 
                0.00790976, 0.002190260, -67.7990,  78.8058, 0.0912105, 26.9920, 445.377,  7.08194, 21.80150, 1.0, 1.0,  0.0, 0.0, 
                0.00485115, 0.000657603, -72.7487,  86.0242, 0.1023380, 22.6156, 434.731, 13.50370,  3.66407, 0.0, 1.0, -1.0, 1.0, 
                0.00423836, 0.004264430, -72.4268, 179.4990, 0.0634936, 64.3289, 341.561, 15.21440,  3.56458, 0.0, 0.0,  6.0, 0.0, 
                0.00157580, 0.001915920, -68.9584, 248.2220, 0.0431619, 40.8806, 849.286,  4.76397,  3.16666, 0.0, 1.0,  1.0, 1.0, 
                0.00356906, 0.008460330, -66.9629,  25.3650, 0.0925546, 66.9877, 918.402,  5.48834,  3.55120, 0.0, 0.0,  0.0, 0.0, 
                0.00529535, 0.001773420, -71.5594, 214.4830, 0.0530862, 41.3451, 728.858,  2.70741, 13.62140, 0.0, 1.0,  3.0, 0.0
            ]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJson(tensorJson));
        ASSERT_TRUE(NULL != tensor);

        ASSERT_FLOAT_EQ(0.00919959, tensor->floatVector()[0]);
        ASSERT_FLOAT_EQ(0.005900520, tensor->floatVector()[1]);
        ASSERT_FLOAT_EQ(3.0, tensor->floatVector()[128]);
        ASSERT_FLOAT_EQ(0.0, tensor->floatVector()[129]);
        ASSERT_EQ(2, tensor->dims());
        ASSERT_EQ(10, tensor->getDim(0));
        ASSERT_EQ(13, tensor->getDim(1));
        ASSERT_EQ(130, tensor->size());
        ASSERT_EQ(10, tensor->getDims()[0]);
        ASSERT_EQ(13, tensor->getDims()[1]);

        std::string jsonString = tensor->toJsonString();
        ASSERT_EQ(R"({"shape":[10,13],"value":[0.00919959,0.00590052,-71.3668,101.957,0.128208,48.1664,505.955,4.12031,2.46073,1.0,0.0,3.0,0.0,0.0202604,0.00388882,-72.3655,69.8636,0.0901836,48.3598,453.684,12.016,6.63711,1.0,0.0,-1.0,0.0,0.0174706,0.0038549,-71.3841,91.0585,0.112977,56.2462,342.2,8.13061,4.31444,1.0,1.0,0.0,1.0,0.00490104,0.0101582,-73.2754,38.3956,0.149034,41.7677,259.172,10.4285,5.40658,1.0,0.0,1.0,0.0,0.00790976,0.00219026,-67.799,78.8058,0.0912105,26.992,445.377,7.08194,21.8015,1.0,1.0,0.0,0.0,0.00485115,0.000657603,-72.7487,86.0242,0.102338,22.6156,434.731,13.5037,3.66407,0.0,1.0,-1.0,1.0,0.00423836,0.00426443,-72.4268,179.499,0.0634936,64.3289,341.561,15.2144,3.56458,0.0,0.0,6.0,0.0,0.0015758,0.00191592,-68.9584,248.222,0.0431619,40.8806,849.286,4.76397,3.16666,0.0,1.0,1.0,1.0,0.00356906,0.00846033,-66.9629,25.365,0.0925546,66.9877,918.402,5.48834,3.5512,0.0,0.0,0.0,0.0,0.00529535,0.00177342,-71.5594,214.483,0.0530862,41.3451,728.858,2.70741,13.6214,0.0,1.0,3.0,0.0]})", jsonString);
    });
}

TEST(TestTensor, toJson_textValue)
{
    auto tensorJson = R"(
        {
            "shape": [1],
            "value": ["2"]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJson(tensorJson));
        ASSERT_TRUE(NULL != tensor);

        ASSERT_EQ("2", tensor->textValue());
        ASSERT_EQ(1, tensor->dims());
        ASSERT_EQ(1, tensor->getDim(0));
        ASSERT_EQ(1, tensor->size());
        ASSERT_EQ(1, tensor->getDims()[0]);

        std::string jsonString = tensor->toJson().dump();
        ASSERT_EQ(R"({"shape":[1],"value":["2"]})", jsonString);
    });
}

TEST(TestTensor, toJson_intValue)
{
    auto tensorJson = R"(
        {
            "shape": [1],
            "value": [0]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJson(tensorJson));
        ASSERT_TRUE(NULL != tensor);

        ASSERT_EQ(0, tensor->intValue());
        ASSERT_EQ(1, tensor->dims());
        ASSERT_EQ(1, tensor->getDim(0));
        ASSERT_EQ(1, tensor->size());
        ASSERT_EQ(1, tensor->getDims()[0]);

        std::string jsonString = tensor->toJson().dump();
        ASSERT_EQ(R"({"shape":[1],"value":[0]})", jsonString);
    });
}

TEST(TestTensor, toJson_floatVector)
{
    auto tensorJson = R"(
        {
            "shape": [10, 13],
            "value": [
                0.00919959, 0.005900520, -71.3668, 101.9570, 0.1282080, 48.1664, 505.955,  4.12031,  2.46073, 1.0, 0.0,  3.0, 0.0,
                0.02026040, 0.003888820, -72.3655,  69.8636, 0.0901836, 48.3598, 453.684, 12.01600,  6.63711, 1.0, 0.0, -1.0, 0.0,
                0.01747060, 0.003854900, -71.3841,  91.0585, 0.1129770, 56.2462, 342.200,  8.13061,  4.31444, 1.0, 1.0,  0.0, 1.0, 
                0.00490104, 0.010158200, -73.2754,  38.3956, 0.1490340, 41.7677, 259.172, 10.42850,  5.40658, 1.0, 0.0,  1.0, 0.0, 
                0.00790976, 0.002190260, -67.7990,  78.8058, 0.0912105, 26.9920, 445.377,  7.08194, 21.80150, 1.0, 1.0,  0.0, 0.0, 
                0.00485115, 0.000657603, -72.7487,  86.0242, 0.1023380, 22.6156, 434.731, 13.50370,  3.66407, 0.0, 1.0, -1.0, 1.0, 
                0.00423836, 0.004264430, -72.4268, 179.4990, 0.0634936, 64.3289, 341.561, 15.21440,  3.56458, 0.0, 0.0,  6.0, 0.0, 
                0.00157580, 0.001915920, -68.9584, 248.2220, 0.0431619, 40.8806, 849.286,  4.76397,  3.16666, 0.0, 1.0,  1.0, 1.0, 
                0.00356906, 0.008460330, -66.9629,  25.3650, 0.0925546, 66.9877, 918.402,  5.48834,  3.55120, 0.0, 0.0,  0.0, 0.0, 
                0.00529535, 0.001773420, -71.5594, 214.4830, 0.0530862, 41.3451, 728.858,  2.70741, 13.62140, 0.0, 1.0,  3.0, 0.0
            ]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensor(fl::Tensor::fromJson(tensorJson));
        ASSERT_TRUE(NULL != tensor);

        ASSERT_FLOAT_EQ(0.00919959, tensor->floatVector()[0]);
        ASSERT_FLOAT_EQ(0.005900520, tensor->floatVector()[1]);
        ASSERT_FLOAT_EQ(3.0, tensor->floatVector()[128]);
        ASSERT_FLOAT_EQ(0.0, tensor->floatVector()[129]);
        ASSERT_EQ(2, tensor->dims());
        ASSERT_EQ(10, tensor->getDim(0));
        ASSERT_EQ(13, tensor->getDim(1));
        ASSERT_EQ(130, tensor->size());
        ASSERT_EQ(10, tensor->getDims()[0]);
        ASSERT_EQ(13, tensor->getDims()[1]);

        std::string jsonString = tensor->toJson().dump();
        ASSERT_EQ(R"({"shape":[10,13],"value":[0.00919959,0.00590052,-71.3668,101.957,0.128208,48.1664,505.955,4.12031,2.46073,1.0,0.0,3.0,0.0,0.0202604,0.00388882,-72.3655,69.8636,0.0901836,48.3598,453.684,12.016,6.63711,1.0,0.0,-1.0,0.0,0.0174706,0.0038549,-71.3841,91.0585,0.112977,56.2462,342.2,8.13061,4.31444,1.0,1.0,0.0,1.0,0.00490104,0.0101582,-73.2754,38.3956,0.149034,41.7677,259.172,10.4285,5.40658,1.0,0.0,1.0,0.0,0.00790976,0.00219026,-67.799,78.8058,0.0912105,26.992,445.377,7.08194,21.8015,1.0,1.0,0.0,0.0,0.00485115,0.000657603,-72.7487,86.0242,0.102338,22.6156,434.731,13.5037,3.66407,0.0,1.0,-1.0,1.0,0.00423836,0.00426443,-72.4268,179.499,0.0634936,64.3289,341.561,15.2144,3.56458,0.0,0.0,6.0,0.0,0.0015758,0.00191592,-68.9584,248.222,0.0431619,40.8806,849.286,4.76397,3.16666,0.0,1.0,1.0,1.0,0.00356906,0.00846033,-66.9629,25.365,0.0925546,66.9877,918.402,5.48834,3.5512,0.0,0.0,0.0,0.0,0.00529535,0.00177342,-71.5594,214.483,0.0530862,41.3451,728.858,2.70741,13.6214,0.0,1.0,3.0,0.0]})", jsonString);
    });
}

TEST(TestTensor, isSameSize_Tensor_Scalar)
{
    auto tensorJsonA = R"(
        {
            "shape": [1],
            "value": [0]
        }
    )"_json;
    auto tensorJsonB = R"(
        {
            "shape": [1],
            "value": [1]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensorA(fl::Tensor::fromJson(tensorJsonA));
        std::shared_ptr<fl::Tensor> tensorB(fl::Tensor::fromJson(tensorJsonB));

        ASSERT_EQ(1, tensorA->size());
        ASSERT_EQ(1, tensorB->size());

        auto is_same_size = tensorA->isSameSize(*tensorB);
        ASSERT_TRUE(is_same_size);
    });
}

TEST(TestTensor, isSameSize_Tensor_Vector)
{
    auto tensorJsonA = R"(
        {
            "shape": [2],
            "value": [0, 1]
        }
    )"_json;
    auto tensorJsonB = R"(
        {
            "shape": [2],
            "value": [2, 3]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensorA(fl::Tensor::fromJson(tensorJsonA));
        std::shared_ptr<fl::Tensor> tensorB(fl::Tensor::fromJson(tensorJsonB));

        ASSERT_EQ(2, tensorA->size());
        ASSERT_EQ(2, tensorB->size());

        auto is_same_size = tensorA->isSameSize(*tensorB);
        ASSERT_TRUE(is_same_size);
    });
}

TEST(TestTensor, isSameSize_Tensor_Matrix)
{
    auto tensorJsonA = R"(
        {
            "shape": [2, 3],
            "value": [0, 1, 2, 3, 4, 5]
        }
    )"_json;
    auto tensorJsonB = R"(
        {
            "shape": [2, 3],
            "value": [6, 7, 8, 9, 10, 11]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensorA(fl::Tensor::fromJson(tensorJsonA));
        std::shared_ptr<fl::Tensor> tensorB(fl::Tensor::fromJson(tensorJsonB));

        ASSERT_EQ(6, tensorA->size());
        ASSERT_EQ(2, tensorA->getDim(0));
        ASSERT_EQ(3, tensorA->getDim(1));

        ASSERT_EQ(6, tensorB->size());
        ASSERT_EQ(2, tensorB->getDim(0));
        ASSERT_EQ(3, tensorB->getDim(1));

        auto is_same_size = tensorA->isSameSize(*tensorB);
        ASSERT_TRUE(is_same_size);
    });
}

TEST(TestTensor, isSameSize_NotSame_Tensor_Vector)
{
    auto tensorJsonA = R"(
        {
            "shape": [2],
            "value": [0, 1]
        }
    )"_json;
    auto tensorJsonB = R"(
        {
            "shape": [3],
            "value": [2, 3, 4]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensorA(fl::Tensor::fromJson(tensorJsonA));
        std::shared_ptr<fl::Tensor> tensorB(fl::Tensor::fromJson(tensorJsonB));

        ASSERT_EQ(2, tensorA->size());
        ASSERT_EQ(3, tensorB->size());

        auto is_same_size = tensorA->isSameSize(*tensorB);
        ASSERT_FALSE(is_same_size);
    });
}

TEST(TestTensor, isSameSize_NotSame_Tensor_Matrix)
{
    auto tensorJsonA = R"(
        {
            "shape": [2, 3],
            "value": [0, 1, 2, 3, 4, 5]
        }
    )"_json;
    auto tensorJsonB = R"(
        {
            "shape": [3, 2],
            "value": [6, 7, 8, 9, 10, 11]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensorA(fl::Tensor::fromJson(tensorJsonA));
        std::shared_ptr<fl::Tensor> tensorB(fl::Tensor::fromJson(tensorJsonB));

        ASSERT_EQ(6, tensorA->size());
        ASSERT_EQ(2, tensorA->getDim(0));
        ASSERT_EQ(3, tensorA->getDim(1));

        ASSERT_EQ(6, tensorB->size());
        ASSERT_EQ(3, tensorB->getDim(0));
        ASSERT_EQ(2, tensorB->getDim(1));

        auto is_same_size = tensorA->isSameSize(*tensorB);
        ASSERT_FALSE(is_same_size);
    });
}

TEST(TestTensor, isSameSize_TensorShape_Scalar)
{
    auto tensorJsonA = R"(
        {
            "shape": [1],
            "value": [0]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensorA(fl::Tensor::fromJson(tensorJsonA));
        std::shared_ptr<fl::TensorShape> shapeB(fl::TensorShape::createShape({1}));

        ASSERT_EQ(1, tensorA->size());
        ASSERT_EQ(1, shapeB->size());

        auto is_same_size = tensorA->isSameSize(*shapeB);
        ASSERT_TRUE(is_same_size);
    });
}

TEST(TestTensor, isSameSize_TensorShape_Vector)
{
    auto tensorJsonA = R"(
        {
            "shape": [2],
            "value": [0, 1]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensorA(fl::Tensor::fromJson(tensorJsonA));
        std::shared_ptr<fl::TensorShape> shapeB(fl::TensorShape::createShape({2}));

        ASSERT_EQ(2, tensorA->size());
        ASSERT_EQ(2, shapeB->size());

        auto is_same_size = tensorA->isSameSize(*shapeB);
        ASSERT_TRUE(is_same_size);
    });
}

TEST(TestTensor, isSameSize_TensorShape_Matrix)
{
    auto tensorJsonA = R"(
        {
            "shape": [2, 3],
            "value": [0, 1, 2, 3, 4, 5]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensorA(fl::Tensor::fromJson(tensorJsonA));
        std::shared_ptr<fl::TensorShape> shapeB(fl::TensorShape::createShape({2, 3}));

        ASSERT_EQ(6, tensorA->size());
        ASSERT_EQ(2, tensorA->getDim(0));
        ASSERT_EQ(3, tensorA->getDim(1));

        ASSERT_EQ(6, shapeB->size());
        ASSERT_EQ(2, shapeB->getDim(0));
        ASSERT_EQ(3, shapeB->getDim(1));

        auto is_same_size = tensorA->isSameSize(*shapeB);
        ASSERT_TRUE(is_same_size);
    });
}

TEST(TestTensor, isSameSize_NotSame_TensorShape_Vector)
{
    auto tensorJsonA = R"(
        {
            "shape": [2],
            "value": [0, 1]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensorA(fl::Tensor::fromJson(tensorJsonA));
        std::shared_ptr<fl::TensorShape> shapeB(fl::TensorShape::createShape({3}));

        ASSERT_EQ(2, tensorA->size());
        ASSERT_EQ(3, shapeB->size());

        auto is_same_size = tensorA->isSameSize(*shapeB);
        ASSERT_FALSE(is_same_size);
    });
}

TEST(TestTensor, isSameSize_NotSame_TensorShape_Matrix)
{
    auto tensorJsonA = R"(
        {
            "shape": [2, 3],
            "value": [0, 1, 2, 3, 4, 5]
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::Tensor> tensorA(fl::Tensor::fromJson(tensorJsonA));
        std::shared_ptr<fl::TensorShape> shapeB(fl::TensorShape::createShape({3, 2}));

        ASSERT_EQ(6, tensorA->size());
        ASSERT_EQ(2, tensorA->getDim(0));
        ASSERT_EQ(3, tensorA->getDim(1));

        ASSERT_EQ(6, shapeB->size());
        ASSERT_EQ(3, shapeB->getDim(0));
        ASSERT_EQ(2, shapeB->getDim(1));

        auto is_same_size = tensorA->isSameSize(*shapeB);
        ASSERT_FALSE(is_same_size);
    });
}

