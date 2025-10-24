#include <fstream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "LinearHLCR/LinearHLCR_JNIF.h"
#include "LinearHLCR/LinearHLCR.h"
#include "FLException.h"

TEST(TestFLExceptionForJNIF, Training_Success)
{
    std::vector<double> vector_double_A { 101.1, 201.1, 201.1, 202.2 };
    int dim_A = 2;

    std::vector<double> vector_double_B { 101.1, 201.1 };

    ASSERT_NO_THROW({
        auto symmetric_matrix = linear_hlcr::SymmetricMatrix::create(vector_double_A, dim_A);
        linear_hlcr::DoubleVector double_vector(vector_double_B);

        try {
            std::unique_ptr<linear_hlcr::LinearRegressionLocalModel> local_model = linear_hlcr::LinearRegressionLocalModel::create(symmetric_matrix, double_vector);
        }
        catch (FLException& ex) {
            const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
            std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
            FAIL();
        }
    });
}

TEST(TestFLExceptionForJNIF, Training_InvalidTensorMap)
{
    auto params_initialize = R"(
        {
          "method": "Initialize",
          "parameters": {
            "internal": {
              "clusterMap": null
            },
            "server": {
              "globalWeight": "../../resources/LinearHLCR/SNE/LinearHLCRGlobalWeight.json",
              "linearModels": [
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel0.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel1.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel2.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel3.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel4.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel5.json"
              ]
            }
          }
        }
    )"_json;

    // Initialize
    linear_hlcr::LinearHLCR* model_ptr = (linear_hlcr::LinearHLCR*)linear_hlcr::LinearHLCR_JNIF::Initialize(params_initialize);
    ASSERT_NE((linear_hlcr::LinearHLCR*)0, model_ptr);

    auto data1 = R"(
        {"x":{"value":[1,1,1,1,1], "shape":[5]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}}
    )"_json;
    auto data2 = R"(
        #{"x":{"value":[2,2,2,2,2], "shape":[5]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}}
    )";    // invalid JSON
    std::ofstream d("/tmp/Data.jsonl");
    std::ofstream i("/tmp/data.txt");
    std::string data;
    int size;
    data = data1.dump();
    size = data.size();
    d << data << std::endl;
    i << "000000000" << std::endl;
    data = data2;
    d << data << std::endl;
    i << "000000" << (size + 1) << std::endl;

    auto params_training = R"(
        {
          "method": "Training",
          "parameters": {
            "client": {
              "dataSet": "{\"save_result\":\"success\",\"tensor_map_file\":\"/tmp/Data.jsonl\",\"tensor_map_index_file\":\"/tmp/data.txt\"}",
              "output": "../../resources/TrainManagerRoot/fl/task-train"
            },
            "server": {
              "hyperParams": "../../resources/LinearHLCR/back_up/LinearHLCRTrainHyperParams.json",
              "output": "../../resources/output"
            }
          }
        }
    )"_json;

    // Training
    auto results = linear_hlcr::LinearHLCR_JNIF::Training(model_ptr, params_training);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 1);
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("\\[json\\.exception\\.parse_error\\.101\\] parse error at line 1, column 1: syntax error while parsing value - unexpected end of input; expected '\\[', '\\{', or a literal>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}

TEST(TestFLExceptionForJNIF, Evaluation_InvalidJson)
{
    auto params_initialize = R"(
        {
          "method": "Initialize",
          "parameters": {
            "internal": {
              "clusterMap": null
            },
            "server": {
              "globalWeight": "../../resources/LinearHLCR/SNE/LinearHLCRGlobalWeight.json",
              "linearModels": [
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel0.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel1.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel2.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel3.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel4.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel5.json"
              ]
            }
          }
        }
    )"_json;

    // Initialize
    linear_hlcr::LinearHLCR* model_ptr = (linear_hlcr::LinearHLCR*)linear_hlcr::LinearHLCR_JNIF::Initialize(params_initialize);
    ASSERT_NE((linear_hlcr::LinearHLCR*)0, model_ptr);

    auto params_evaluation = R"(
        {
          "method": "Training",
          "parameters": {
            "client": {
              "XdataSet": "{\"save_result\":\"success\",\"tensor_map_file\":\"/tmp/Data.jsonl\",\"tensor_map_index_file\":\"/tmp/data.txt\"}"
            },
            "server": {
              "output": "../../resources/output"
            }
          }
        }
    )"_json;

    // Evaluation
    auto results = linear_hlcr::LinearHLCR_JNIF::Evaluation(model_ptr, params_evaluation);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 1);
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("\\[json\\.exception\\.type_error\\.302\\] type must be string, but is (object|number|null)>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}

TEST(TestFLExceptionForJNIF, Evaluation_InvalidMetadata)
{
    auto params_initialize = R"(
        {
          "method": "Initialize",
          "parameters": {
            "internal": {
              "clusterMap": null
            },
            "server": {
              "globalWeight": "../../resources/LinearHLCR/SNE/LinearHLCRGlobalWeight.json",
              "linearModels": [
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel0.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel1.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel2.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel3.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel4.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel5.json"
              ]
            }
          }
        }
    )"_json;

    // Initialize
    linear_hlcr::LinearHLCR* model_ptr = (linear_hlcr::LinearHLCR*)linear_hlcr::LinearHLCR_JNIF::Initialize(params_initialize);
    ASSERT_NE((linear_hlcr::LinearHLCR*)0, model_ptr);

    auto params_evaluation = R"(
        {
          "method": "Training",
          "parameters": {
            "client": {
              "dataSet": "{}"
            },
            "server": {
              "output": "../../resources/output"
            }
          }
        }
    )"_json;

    // Evaluation
    auto results = linear_hlcr::LinearHLCR_JNIF::Evaluation(model_ptr, params_evaluation);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 1);
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("failed to open data file: \\.\\./\\.\\./resources/output/Evaluation_Result\\.jsonl \\[tensor/data_serializer\\.cc:[0-9]+\\]>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}

TEST(TestFLExceptionForJNIF, Prediction_InvalidJson)
{
    auto params_initialize = R"(
        {
          "method": "Initialize",
          "parameters": {
            "internal": {
              "clusterMap": null
            },
            "server": {
              "globalWeight": "../../resources/LinearHLCR/SNE/LinearHLCRGlobalWeight.json",
              "linearModels": [
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel0.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel1.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel2.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel3.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel4.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel5.json"
              ]
            }
          }
        }
    )"_json;

    // Initialize
    linear_hlcr::LinearHLCR* model_ptr = (linear_hlcr::LinearHLCR*)linear_hlcr::LinearHLCR_JNIF::Initialize(params_initialize);
    ASSERT_NE((linear_hlcr::LinearHLCR*)0, model_ptr);

    auto params_prediction = R"(
        {
          "method": "Training",
          "parameters": {
            "application": {
              "Xdata": "{\"save_result\":\"success\",\"tensor_map_file\":\"/tmp/Data.jsonl\",\"tensor_map_index_file\":\"/tmp/data.txt\"}"
            }
          }
        }
    )"_json;

    // Prediction
    auto results = linear_hlcr::LinearHLCR_JNIF::Prediction(model_ptr, params_prediction);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 1);
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("\\[json\\.exception\\.type_error\\.302\\] type must be string, but is (object|number|null)>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}
