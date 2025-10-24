#include <fstream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "FLException.h"
#include "tensor/tensor_map.h"

TEST(TestTensorMap, newInstance)                                // 正 get
{
    std::shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::newInstance());
    ASSERT_TRUE(NULL != tensor_map.get());

    std::string jsonString = tensor_map->toJsonString();
    ASSERT_EQ("{}", jsonString);
}


TEST(TestTensorMap, fromJsonString_tensor_does_not_contained)   // 正 tensor x 0, get
{
    auto tensorMapJson = R"({})"_json;

    std::shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::fromJsonString(tensorMapJson.dump()));
    ASSERT_TRUE(NULL != tensor_map.get());

    std::string jsonString = tensor_map->toJsonString();
    ASSERT_EQ("{}", jsonString);
}

TEST(TestTensorMap, fromJsonString_tensor_x1)                   // 正 tensor x 1, get
{
    auto tensorMapJson = R"(
        {
            "tensor": {
                "shape": [
                    2, 3
                ],
                "value": [
                    11, 12, 13,
                    21, 22, 23
                ]
            }
        }
    )"_json;

    std::shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::fromJsonString(tensorMapJson.dump()));
    ASSERT_TRUE(NULL != tensor_map.get());
}

TEST(TestTensorMap, fromJsonString_tensor_xN)                   // 正 tensor x N, get
{
    auto tensorMapJson = R"(
        {
            "doubleScalar": { "shape": [1], "value": [1.7976931348623157E308] },
            "longScalar": {"shape":[1], "value": [9223372036854775807] },
            "floatScalar": {"shape": [1], "value": [3.4028235E38] },
            "stringScalar": {"shape":[1], "value": ["Goodbye, Hello"] },
            "integerScalar": {"shape":[1], "value": [2147483647] }
        }
    )"_json;

    std::shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::fromJsonString(tensorMapJson.dump()));
    ASSERT_TRUE(NULL != tensor_map.get());

    std::shared_ptr<fl::Tensor> intScalar = tensor_map->get("integerScalar");
    ASSERT_EQ(2147483647, intScalar->intValue());

    std::shared_ptr<fl::Tensor> longScalar = tensor_map->get("longScalar");
    ASSERT_EQ(9223372036854775807, longScalar->longValue());

    std::shared_ptr<fl::Tensor> floatScalar = tensor_map->get("floatScalar");
    ASSERT_FLOAT_EQ(340282346638528860000000000000000000000.000000, floatScalar->floatValue());

    std::shared_ptr<fl::Tensor> doubleScalar = tensor_map->get("doubleScalar");
    ASSERT_DOUBLE_EQ(179769313486231570000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.000000, doubleScalar->doubleValue());
}

TEST(TestTensorMap, newInstance_toJsonString)                   // 正 newInstance, set, get, toJsonString
{
    std::shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::newInstance());
    const int scalar_int = 2147483647;  // Java Integer.MAX_VALUE
    const long scalar_long = 9223372036854775807;  // Java Long.MAX_VALUE
    const float scalar_float = 340282346638528860000000000000000000000.000000;  // Java Float.MAX_VALUE
    const double scalar_double = 179769313486231570000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.000000;  // Java Double.MAX_VALUE
    const std::string scalar_string = "Hello, Goodbye";
    std::shared_ptr<fl::Tensor> tensor_int(fl::Tensor::newTensor(scalar_int));
    tensor_map->set("integerScalar", tensor_int);
    std::shared_ptr<fl::Tensor> tensor_long(fl::Tensor::newTensor(scalar_long));
    tensor_map->set("longScalar", tensor_long);
    std::shared_ptr<fl::Tensor> tensor_float(fl::Tensor::newTensor(scalar_float));
    tensor_map->set("floatScalar", tensor_float);
    std::shared_ptr<fl::Tensor> tensor_double(fl::Tensor::newTensor(scalar_double));
    tensor_map->set("doubleScalar", tensor_double);
    std::shared_ptr<fl::Tensor> tensor_string(fl::Tensor::newTensor(scalar_string));
    tensor_map->set("stringScalar", tensor_string);
    std::cout << "Write to ..." << std::endl;
    std::cout << tensor_map->toJsonString() << std::endl;
}

TEST(TestTensorMap, fromJsonString_toJsonString)                // 正 fromJsonString, set, get, toJsonString
{
    auto tensorMapJson = R"(
        {
            "group_label": {
                "shape": [1],
                "value": ["2"]
            },
            "y": {
                "shape": [1],
                "value": [0]
            },
            "x": {
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
        }
    )"_json;

    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::fromJsonString(tensorMapJson.dump()));
        ASSERT_TRUE(NULL != tensor_map.get());

        std::shared_ptr<fl::Tensor> tensor_group_label = tensor_map->get("group_label");
        ASSERT_EQ("2", tensor_group_label->textValue());

        std::shared_ptr<fl::Tensor> tensor_y = tensor_map->get("y");
        ASSERT_EQ(0, tensor_y->intValue());

        std::shared_ptr<fl::Tensor> tensor_x = tensor_map->get("x");
        std::vector<float> x = tensor_x->floatVector();
        ASSERT_FLOAT_EQ(0.00919959, x[0]);
        ASSERT_FLOAT_EQ(0.02026040, x[13]);
        ASSERT_FLOAT_EQ(0.00529535, x[117]);
        ASSERT_FLOAT_EQ(0.0, x[129]);

        std::string jsonString = tensor_map->toJsonString();
        ASSERT_EQ(R"({"group_label":{"shape":[1],"value":["2"]},"x":{"shape":[10,13],"value":[0.00919959,0.00590052,-71.3668,101.957,0.128208,48.1664,505.955,4.12031,2.46073,1.0,0.0,3.0,0.0,0.0202604,0.00388882,-72.3655,69.8636,0.0901836,48.3598,453.684,12.016,6.63711,1.0,0.0,-1.0,0.0,0.0174706,0.0038549,-71.3841,91.0585,0.112977,56.2462,342.2,8.13061,4.31444,1.0,1.0,0.0,1.0,0.00490104,0.0101582,-73.2754,38.3956,0.149034,41.7677,259.172,10.4285,5.40658,1.0,0.0,1.0,0.0,0.00790976,0.00219026,-67.799,78.8058,0.0912105,26.992,445.377,7.08194,21.8015,1.0,1.0,0.0,0.0,0.00485115,0.000657603,-72.7487,86.0242,0.102338,22.6156,434.731,13.5037,3.66407,0.0,1.0,-1.0,1.0,0.00423836,0.00426443,-72.4268,179.499,0.0634936,64.3289,341.561,15.2144,3.56458,0.0,0.0,6.0,0.0,0.0015758,0.00191592,-68.9584,248.222,0.0431619,40.8806,849.286,4.76397,3.16666,0.0,1.0,1.0,1.0,0.00356906,0.00846033,-66.9629,25.365,0.0925546,66.9877,918.402,5.48834,3.5512,0.0,0.0,0.0,0.0,0.00529535,0.00177342,-71.5594,214.483,0.0530862,41.3451,728.858,2.70741,13.6214,0.0,1.0,3.0,0.0]},"y":{"shape":[1],"value":[0]}})", jsonString);
    });
}

////////////////////////////////////////////////////////////////////////////////

TEST(TestTensorMap, fromJsonString_invalid_tensor1)             // 異 tensor x 1 invalid tensor
{
    // NOTE: 'y' value is not array
    auto tensorMapJson = R"(
        {
            "group_label": {
                "shape": [1],
                "value": ["2"]
            },
            "y": {
                "shape": [1],
                "value": 0
            },
            "x": {
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
        }
    )"_json;

    try {
        std::shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::fromJsonString(tensorMapJson.dump()));
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Failed to create tensor\\. Unknown json string\\. \\(\\{\"shape\":\\[1\\],\"value\":0\\}\\) \\[tensor/tensor\\.cc:[0-9]+\\]"));
    }
}

TEST(TestTensorMap, fromJsonString_invalid_tensor2)             // 異 tensor x 1 invalid tensor
{
    // NOTE: 'group_label' shape is not array
    auto tensorMapJson = R"(
        {
            "group_label": {
                "shape": 1,
                "value": ["2"]
            },
            "y": {
                "shape": [1],
                "value": [0]
            },
            "x": {
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
        }
    )"_json;

    try {
        std::shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::fromJsonString(tensorMapJson.dump()));
        FAIL();
    }
    catch (json::exception& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_STREQ("[json.exception.type_error.302] type must be array, but is number", ex.what());
    }
}

TEST(TestTensorMap, fromJsonString_invalid_tensor3)             // 異 tensor x 1 invalid tensor
{
    // NOTE: 'x' value element not enough
    auto tensorMapJson = R"(
        {
            "group_label": {
                "shape": [1],
                "value": ["2"]
            },
            "y": {
                "shape": [1],
                "value": [0]
            },
            "x": {
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
                    0.00529535, 0.001773420, -71.5594, 214.4830, 0.0530862, 41.3451, 728.858,  2.70741, 13.62140, 0.0, 1.0,  3.0, 0.0
                ]
            }
        }
    )"_json;

    try {
        std::shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::fromJsonString(tensorMapJson.dump()));
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Failed to create tensor\\. unmatch size\\. \\(117 != 130\\) \\[tensor/tensor\\.cc:[0-9]+\\]"));
    }
}

TEST(TestTensorMap, fromJsonString_invalid_tensor4)             // 異 tensor x 1 invalid tensor
{
    // NOTE: 'x' value invalid json
    auto tensorMapJson = R"(
        {
            "group_label": {
                "shape": [1],
                "value": ["2"]
            },
            "y": {
                "shape": [1],
                "value": [0]
            },
            "x": {
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
                    0.00529535, 0.001773420, -71.5594, 214.4830, 0.0530862, 41.3451, 728.858,  2.70741, 13.62140, 0.0, 1.0,  3.0, 0.0,
                ]
            }
        }
    )";

    try {
        std::shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::fromJsonString(tensorMapJson));
        FAIL();
    }
    catch (json::exception& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_STREQ("[json.exception.parse_error.101] parse error at line 23, column 17: syntax error while parsing value - unexpected ']'; expected '[', '{', or a literal", ex.what());
    }
}

TEST(TestTensorMap, fromJsonString_invalid_tensor5)             // 異 tensor x 1 invalid tensor
{
    // NOTE: 'x' shape invalid json
    auto tensorMapJson = R"(
        {
            "group_label": {
                "shape": [1],
                "value": ["2"]
            },
            "y": {
                "shape": [1],
                "value": [0]
            },
            "x": {
                "shape": {10, 13},
                "value": [
                    0.00919959, 0.005900520, -71.3668, 101.9570, 0.1282080, 48.1664, 505.955,  4.12031,  2.46073, 1.0, 0.0,  3.0, 0.0,
                    0.02026040, 0.003888820, -72.3655,  69.8636, 0.0901836, 48.3598, 453.684, 12.01600,  6.63711, 1.0, 0.0, -1.0, 0.0,
                    0.01747060, 0.003854900, -71.3841,  91.0585, 0.1129770, 56.2462, 342.200,  8.13061,  4.31444, 1.0, 1.0,  0.0, 1.0, 
                    0.00490104, 0.010158200, -73.2754,  38.3956, 0.1490340, 41.7677, 259.172, 10.42850,  5.40658, 1.0, 0.0,  1.0, 0.0, 
                    0.00790976, 0.002190260, -67.7990,  78.8058, 0.0912105, 26.9920, 445.377,  7.08194, 21.80150, 1.0, 1.0,  0.0, 0.0, 
                    0.00485115, 0.000657603, -72.7487,  86.0242, 0.1023380, 22.6156, 434.731, 13.50370,  3.66407, 0.0, 1.0, -1.0, 1.0, 
                    0.00423836, 0.004264430, -72.4268, 179.4990, 0.0634936, 64.3289, 341.561, 15.21440,  3.56458, 0.0, 0.0,  6.0, 0.0, 
                    0.00157580, 0.001915920, -68.9584, 248.2220, 0.0431619, 40.8806, 849.286,  4.76397,  3.16666, 0.0, 1.0,  1.0, 1.0, 
                    0.00529535, 0.001773420, -71.5594, 214.4830, 0.0530862, 41.3451, 728.858,  2.70741, 13.62140, 0.0, 1.0,  3.0, 0.0
                ]
            }
        }
    )";

    try {
        std::shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::fromJsonString(tensorMapJson));
        FAIL();
    }
    catch (json::exception& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_STREQ("[json.exception.parse_error.101] parse error at line 12, column 28: syntax error while parsing object key - unexpected number literal; expected string literal", ex.what());
    }
}

TEST(TestTensorMap, fromJsonString_invalid_tensor6)             // 異 tensor x 1 invalid tensor
{
    // NOTE: 'group_label' value type not support
    auto tensorMapJson = R"(
        {
            "group_label": {
                "shape": [1],
                "value": [true]
            },
            "y": {
                "shape": [1],
                "value": [0]
            },
            "x": {
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
                    0.00529535, 0.001773420, -71.5594, 214.4830, 0.0530862, 41.3451, 728.858,  2.70741, 13.62140, 0.0, 1.0,  3.0, 0.0
                ]
            }
        }
    )";

    try {
        std::shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::fromJsonString(tensorMapJson));
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Failed to create tensor\\. Unknown json string\\. \\(\\{\"shape\":\\[1\\],\"value\":\\[true\\]\\}\\) \\[tensor/tensor\\.cc:[0-9]+\\]"));
    }
}
