#include <fstream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tensor/data_metadata.h"
#include "LinearHLCR/LinearHLCR_JNIF.h"
#include "LinearHLCR/LinearHLCR.h"
#include "FLException.h"

//
// LinearHLCR.cpp:28:    if (beta <= 0 || sigma <= 0) THROW_FL_EXCEPTION(str_format("invalid beta(%d) or sigma(%d)", beta, sigma));
//
TEST(TestFLExceptionForLinearHLCR, Training_InvalidSigma)
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

    // generate invalid HyperParams.json
    auto hyper_params = R"(
        {
            "sigma": 0.0
        }
    )"_json;    // 'sigma' invalid
    std::ofstream o("/tmp/HyperParams.json");
    o << hyper_params.dump() << std::endl;

    auto params_training = R"(
        {
          "method": "Training",
          "parameters": {
            "client": {
              "dataSet": "{\"save_result\":\"success\",\"tensor_map_file\":\"../../resources/LinearHLCR/SNE/Data.jsonl\",\"tensor_map_index_file\":\"../../resources/LinearHLCR/SNE/data.txt\"}",
              "output": "../../resources/TrainManagerRoot/fl/task-train"
            },
            "server": {
              "hyperParams": "/tmp/HyperParams.json",
              "output": "../../resources/output"
            }
          }
        }
    )"_json;

    // Training
    auto results = linear_hlcr::LinearHLCR_JNIF::Training(model_ptr, params_training);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 1);
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("invalid sigma\\(0\\.000000\\) \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}

//
// LinearHLCR.cpp:53:    if (beta <= 0 || sigma <= 0) THROW_FL_EXCEPTION(str_format("invalid beta(%d) or sigma(%d)", beta, sigma));
//
TEST(TestFLExceptionForLinearHLCR, UpdateInfo_InvalidSigma)
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

    // generate invalid HyperParams.json
    auto hyper_params = R"(
        {
            "sigma": 0.0
        }
    )"_json;    // 'sigma' invalid
    std::ofstream o("/tmp/HyperParams.json");
    o << hyper_params.dump() << std::endl;

    auto params_updateInfo = R"(
        {
          "method": "UpdateInfo",
          "parameters": {
            "client": {
              "dataSet": "{\"save_result\":\"success\",\"tensor_map_file\":\"../../resources/LinearHLCR/SNE/Data.jsonl\",\"tensor_map_index_file\":\"../../resources/LinearHLCR/SNE/data.txt\"}",
              "output": "../../resources/TrainManagerRoot/fl/task-deploy"
            },
            "server": {
              "hyperParams": "/tmp/HyperParams.json"
            }
          }
        }
    )"_json;

    // UpdateInfo
    auto results = linear_hlcr::LinearHLCR_JNIF::UpdateInfo(model_ptr, params_updateInfo);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 1);
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("invalid sigma\\(0\\.000000\\) \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}

TEST(TestFLExceptionForLinearHLCR, CreateLocalModel_Success)
{
    ASSERT_NO_THROW({
        int K = 2;
        std::vector<int> local_count_vec(K);
        std::vector<std::shared_ptr<linear_hlcr::LinearRegressionLocalModel>> regression_model_vec(K);

        std::shared_ptr<linear_hlcr::LinearHLCRLocalModel> local_model = linear_hlcr::LinearHLCRLocalModel::create(linear_hlcr::IntVector(local_count_vec), regression_model_vec);
    });
}

//
// LinearHLCR.cpp:68:    if (local_count.getDim() != linear_models.size()) THROW_FL_EXCEPTION(str_format("unmatch model count. (local_count:%d liner_models:%d)", local_count.getDim(), linear_models.size()));
//
TEST(TestFLExceptionForLinearHLCR, CreateLocalModel_Failed)
{
    ASSERT_NO_THROW({
        std::vector<int> local_count_vec(2);
        std::vector<std::shared_ptr<linear_hlcr::LinearRegressionLocalModel>> regression_model_vec(3);

        try {
            std::shared_ptr<linear_hlcr::LinearHLCRLocalModel> local_model = linear_hlcr::LinearHLCRLocalModel::create(linear_hlcr::IntVector(local_count_vec), regression_model_vec);
            FAIL();
        }
        catch (FLException& ex) {
            const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
            std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
            ASSERT_THAT(ex.what(), testing::MatchesRegex("mismatch sizes of local_count and linear_models\\. \\(local_count:2 liner_models:3\\) \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]"));
        }
    });
}

// MEMO: Not used
// // LinearHLCR.cpp:112:        THROW_FL_EXCEPTION(str_format("invalid index:%d (max:%d)", index, this->_output_linear_models.size()));
// TEST(TestFLExceptionForLinearHLCR, InvalidIndex)
// {
// }

//
// LinearHLCR.cpp:126:    if (K != global_weight.getDim()) THROW_FL_EXCEPTION(str_format("unmatch K and global weight dimension. (K:%d global_weight.dim:%d)", K, global_weight.getDim()));
//
TEST(TestFLExceptionForLinearHLCR, Initialize_InvalidGlobalWeightDim)
{
    // generate invalid GlobalWeight.json
    auto global_weight = R"(
        {
            "global_weight": [0.2, 0.2, 0.2, 0.2, 0.1, 0.1, 9.9],
            "beta": 0.1
        }
    )"_json;
    std::ofstream o("/tmp/GlobalWeight.json");
    o << global_weight.dump() << std::endl;

    auto params_initialize = R"(
        {
          "method": "Initialize",
          "parameters": {
            "internal": {
              "clusterMap": null
            },
            "server": {
              "globalWeight": "/tmp/GlobalWeight.json",
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
    ASSERT_EQ((linear_hlcr::LinearHLCR*)0, model_ptr);
}

//
// LinearHLCR.cpp:196:            THROW_FL_EXCEPTION(str_format("invalid p.second:%d (max:%d)", p.second, K-1));
//
TEST(TestFLExceptionForLinearHLCR, Initialize_MinusSecond)
{
    // generate invalid cluster_map.json
    auto hyper_params = R"(
        {
            "K": 2,
            "cluster_map": {
                "group0": -1,
                "group1": 1
            }
        }
    )"_json;
    std::ofstream o("/tmp/cluster_map.json");
    o << hyper_params.dump() << std::endl;

    auto params_initialize = R"(
        {
          "method": "Initialize",
          "parameters": {
            "internal": {
              "clusterMap": "/tmp/cluster_map.json"
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
    ASSERT_EQ((linear_hlcr::LinearHLCR*)0, model_ptr);
}

//
// LinearHLCR.cpp:196:            THROW_FL_EXCEPTION(str_format("invalid p.second:%d (max:%d)", p.second, K-1));
//
TEST(TestFLExceptionForLinearHLCR, Initialize_TooBigSecond)
{
    // generate invalid cluster_map.json
    auto hyper_params = R"(
        {
            "K": 2,
            "cluster_map": {
                "group0": 1,
                "group1": 2
            }
        }
    )"_json;
    std::ofstream o("/tmp/cluster_map.json");
    o << hyper_params.dump() << std::endl;

    auto params_initialize = R"(
        {
          "method": "Initialize",
          "parameters": {
            "internal": {
              "clusterMap": "/tmp/cluster_map.json"
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
    ASSERT_EQ((linear_hlcr::LinearHLCR*)0, model_ptr);
}

TEST(TestFLExceptionForLinearHLCR, Prediction_Success)
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

    auto prediction_data = R"(
        {
          "g": {
            "shape": [1],
            "value": ["group0"]
          },
          "x": {
            "shape": [5],
            "value": [3, 3, 3, 3, 3]
          }
        }
    )"_json;

    auto params_prediction = R"(
        {
          "method": "Prediction",
          "parameters": {
            "application": {
              "data": ""
            }
          }
        }
    )"_json;

    params_prediction["parameters"]["application"]["data"] = prediction_data.dump();

    // Prediction
    auto results = linear_hlcr::LinearHLCR_JNIF::Prediction(model_ptr, params_prediction);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 0);
    ASSERT_NE(results["results"]["application"]["predictionResult"], "");

    std::string json_string = results["results"]["application"]["predictionResult"];
    json predictionResult = json::parse(json_string);
    ASSERT_EQ(predictionResult["y_pred"]["shape"][0], 1);
    ASSERT_NEAR(predictionResult["y_pred"]["value"][0], 0.118, 0.1);
}

//
// LinearHLCR.cpp:252:            THROW_FL_EXCEPTION(str_format("invalid tensor map. No 'x' or 'y' or 'g'"));
//
TEST(TestFLExceptionForLinearHLCR, Training_InvalidTensorMap_NotTestable1)
{
    // see. TEST(TestFLExceptionForLinearHLCR, Training_InvalidTensorMapX)
    // see. TEST(TestFLExceptionForLinearHLCR, Training_InvalidTensorMapY)
    // see. TEST(TestFLExceptionForLinearHLCR, Training_InvalidTensorMapG)
    SUCCEED();
}

//
// LinearHLCR.cpp:288:        THROW_FL_EXCEPTION(str_format("invalid tensor map. No 'x' or 'g'"));
//
TEST(TestFLExceptionForLinearHLCR, Prediction_NoX)
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

    auto prediction_data = R"(
        {
          "g": {
            "shape": [1],
            "value": ["group0"]
          },
          "X": {
            "shape": [5],
            "value": [3, 3, 3, 3, 3]
          }
        }
    )"_json;

    auto params_prediction = R"(
        {
          "method": "Prediction",
          "parameters": {
            "application": {
              "data": ""
            }
          }
        }
    )"_json;

    params_prediction["parameters"]["application"]["data"] = prediction_data.dump();

    // Prediction
    auto results = linear_hlcr::LinearHLCR_JNIF::Prediction(model_ptr, params_prediction);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 1);
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("invalid tensor map\\. 'x' or 'g' not included\\. \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}

//
// LinearHLCR.cpp:288:        THROW_FL_EXCEPTION(str_format("invalid tensor map. No 'x' or 'g'"));
//
TEST(TestFLExceptionForLinearHLCR, Prediction_NoG)
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

    auto prediction_data = R"(
        {
          "G": {
            "shape": [1],
            "value": ["group0"]
          },
          "x": {
            "shape": [5],
            "value": [3, 3, 3, 3, 3]
          }
        }
    )"_json;

    auto params_prediction = R"(
        {
          "method": "Prediction",
          "parameters": {
            "application": {
              "data": ""
            }
          }
        }
    )"_json;

    params_prediction["parameters"]["application"]["data"] = prediction_data.dump();

    // Prediction
    auto results = linear_hlcr::LinearHLCR_JNIF::Prediction(model_ptr, params_prediction);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 1);
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("invalid tensor map\\. 'x' or 'g' not included\\. \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}

// LinearHLCR.cpp:342:    if (new_model->getK() != this->_internal_model->getK()) THROW_FL_EXCEPTION(str_format("unmatch K. new_model:%d internal_model:%d", new_model->getK(), this->_internal_model->getK()));
TEST(TestFLExceptionForLinearHLCR, UpdateInfo_UnmatchK_DOES_NOT_OCCUR)
{
    // generate K=4 GlobalWeight.json
    auto global_weight_4 = R"(
        {
            "global_weight": [0.2, 0.2, 0.2, 0.2],
            "beta": 0.1
        }
    )"_json;
    std::ofstream o4("/tmp/GlobalWeight_4.json");
    o4 << global_weight_4.dump() << std::endl;

    auto params_initialize_4 = R"(
        {
          "method": "Initialize",
          "parameters": {
            "internal": {
              "clusterMap": null
            },
            "server": {
              "globalWeight": "/tmp/GlobalWeight_4.json",
              "linearModels": [
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel0.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel1.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel2.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel3.json"
              ]
            }
          }
        }
    )"_json;

    // generate K=6 GlobalWeight.json
    auto global_weight_6 = R"(
        {
            "global_weight": [0.2, 0.2, 0.2, 0.2, 0.1, 0.1],
            "beta": 0.1
        }
    )"_json;
    std::ofstream o6("/tmp/GlobalWeight_6.json");
    o6 << global_weight_6.dump() << std::endl;

    auto params_initialize_6 = R"(
        {
          "method": "Initialize",
          "parameters": {
            "internal": {
              "clusterMap": null
            },
            "server": {
              "globalWeight": "/tmp/GlobalWeight_6.json",
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

    ASSERT_NO_THROW({
        // Initialize K=4
        linear_hlcr::LinearHLCR* model_ptr_4 = (linear_hlcr::LinearHLCR*)linear_hlcr::LinearHLCR_JNIF::Initialize(params_initialize_4);
        ASSERT_NE((linear_hlcr::LinearHLCR*)0, model_ptr_4);

        auto params_updateInfo = R"(
            {
              "method": "UpdateInfo",
              "parameters": {
                "client": {
                  "dataSet": "{\"save_result\":\"success\",\"tensor_map_file\":\"../../resources/LinearHLCR/SNE/Data.jsonl\",\"tensor_map_index_file\":\"../../resources/LinearHLCR/SNE/data.txt\"}",
                  "output": "../../resources/TrainManagerRoot/fl/task-deploy"
                },
                "server": {
                  "hyperParams": "../../resources/LinearHLCR/back_up/LinearHLCRUpdateHyperParams.json"
                }
              }
            }
        )"_json;

        fl::DataMetadata data_metadata = fl::DataMetadata::fromJsonString(params_updateInfo["parameters"]["client"]["dataSet"]);
        std::unique_ptr<linear_hlcr::LinearHLCRUpdateHyperParams> update_hyper_params_ptr = linear_hlcr::LinearHLCRUpdateHyperParams::fromJson(params_updateInfo["parameters"]["server"]);
        std::unique_ptr<linear_hlcr::LinearHLCRInternalModel> new_internal_model_ptr = model_ptr_4->updateInternalModel(data_metadata, *update_hyper_params_ptr);

        // Initialize K=6
        linear_hlcr::LinearHLCR* model_ptr_6 = (linear_hlcr::LinearHLCR*)linear_hlcr::LinearHLCR_JNIF::Initialize(params_initialize_6);
        ASSERT_NE((linear_hlcr::LinearHLCR*)0, model_ptr_6);

        try {
            model_ptr_6->setInternalModel(std::move(new_internal_model_ptr));
            FAIL();
        }
        catch (FLException& ex) {
            const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
            std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
            ASSERT_THAT(ex.what(), testing::MatchesRegex("mismatch K of new_model and internal_model\\. \\(new_model:4 internal_model:6\\) \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]"));
        }
    });
}

//
// LinearHLCR.cpp:411:            THROW_FL_EXCEPTION(str_format("invalid tensor map. 'g' is not included."));
//
TEST(TestFLExceptionForLinearHLCR, Training_InvalidTensorMapG)
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
        {"x":{"value":[2,2,2,2,2], "shape":[5]}, "y":{"value":[0.6], "shape":[1]}, "G":{"value":["group1"], "shape":[1]}}
    )"_json;    // 'G' is invalid tensor
    std::ofstream d("/tmp/Data.jsonl");
    std::ofstream i("/tmp/data.txt");
    std::string data;
    int size;
    data = data1.dump();
    size = data.size();
    d << data << std::endl;
    i << "000000000" << std::endl;
    data = data2.dump();
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
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("invalid tensor map\\. 'g' is not included\\. \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}

//
// LinearHLCR.cpp:411:            THROW_FL_EXCEPTION(str_format("invalid tensor map. 'g' is not included."));
//
TEST(TestFLExceptionForLinearHLCR, UpdateInfo_InvalidTensorMapG)
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
        {"x":{"value":[2,2,2,2,2], "shape":[5]}, "y":{"value":[0.6], "shape":[1]}, "G":{"value":["group1"], "shape":[1]}}
    )"_json;    // 'G' is invalid tensor
    std::ofstream d("/tmp/Data.jsonl");
    std::ofstream i("/tmp/data.txt");
    std::string data;
    int size;
    data = data1.dump();
    size = data.size();
    d << data << std::endl;
    i << "000000000" << std::endl;
    data = data2.dump();
    d << data << std::endl;
    i << "000000" << (size + 1) << std::endl;

    auto params_updateInfo = R"(
        {
          "method": "UpdateInfo",
          "parameters": {
            "client": {
              "dataSet": "{\"save_result\":\"success\",\"tensor_map_file\":\"/tmp/Data.jsonl\",\"tensor_map_index_file\":\"/tmp/data.txt\"}",
              "output": "../../resources/TrainManagerRoot/fl/task-deploy"
            },
            "server": {
              "hyperParams": "../../resources/LinearHLCR/back_up/LinearHLCRUpdateHyperParams.json"
            }
          }
        }
    )"_json;

    // UpdateInfo
    auto results = linear_hlcr::LinearHLCR_JNIF::UpdateInfo(model_ptr, params_updateInfo);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 1);
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("invalid tensor map\\. 'g' is not included\\. \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}

//
// LinearHLCR.cpp:439:        THROW_FL_EXCEPTION(str_format("invalid tensor map. No 'x' or 'y'"));
//
TEST(TestFLExceptionForLinearHLCR, Training_InvalidTensorMapX)
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
        {"X":{"value":[2,2,2,2,2], "shape":[5]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}}
    )"_json;    // 'X' is invalid tensor
    std::ofstream d("/tmp/Data.jsonl");
    std::ofstream i("/tmp/data.txt");
    std::string data;
    int size;
    data = data1.dump();
    size = data.size();
    d << data << std::endl;
    i << "000000000" << std::endl;
    data = data2.dump();
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
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("invalid tensor map\\. 'x' or 'y' not included\\. \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}

//
// LinearHLCR.cpp:439:        THROW_FL_EXCEPTION(str_format("invalid tensor map. No 'x' or 'y'"));
//
TEST(TestFLExceptionForLinearHLCR, Training_InvalidTensorMapY)
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
        {"x":{"value":[2,2,2,2,2], "shape":[5]}, "Y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}}
    )"_json;    // 'Y' is invalid tensor
    std::ofstream d("/tmp/Data.jsonl");
    std::ofstream i("/tmp/data.txt");
    std::string data;
    int size;
    data = data1.dump();
    size = data.size();
    d << data << std::endl;
    i << "000000000" << std::endl;
    data = data2.dump();
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
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("invalid tensor map\\. 'x' or 'y' not included\\. \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}

//
// LinearHLCR.cpp:439:        THROW_FL_EXCEPTION(str_format("invalid tensor map. No 'x' or 'y'"));
//
TEST(TestFLExceptionForLinearHLCR, UpdateInfo_InvalidTensorMapX)
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
        {"X":{"value":[2,2,2,2,2], "shape":[5]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}}
    )"_json;    // 'X' is invalid tensor
    std::ofstream d("/tmp/Data.jsonl");
    std::ofstream i("/tmp/data.txt");
    std::string data;
    int size;
    data = data1.dump();
    size = data.size();
    d << data << std::endl;
    i << "000000000" << std::endl;
    data = data2.dump();
    d << data << std::endl;
    i << "000000" << (size + 1) << std::endl;

    auto params_updateInfo = R"(
        {
          "method": "UpdateInfo",
          "parameters": {
            "client": {
              "dataSet": "{\"save_result\":\"success\",\"tensor_map_file\":\"/tmp/Data.jsonl\",\"tensor_map_index_file\":\"/tmp/data.txt\"}",
              "output": "../../resources/TrainManagerRoot/fl/task-deploy"
            },
            "server": {
              "hyperParams": "../../resources/LinearHLCR/back_up/LinearHLCRUpdateHyperParams.json"
            }
          }
        }
    )"_json;

    // UpdateInfo
    auto results = linear_hlcr::LinearHLCR_JNIF::UpdateInfo(model_ptr, params_updateInfo);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 1);
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("invalid tensor map\\. 'x' or 'y' not included\\. \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}

//
// LinearHLCR.cpp:439:        THROW_FL_EXCEPTION(str_format("invalid tensor map. No 'x' or 'y'"));
//
TEST(TestFLExceptionForLinearHLCR, UpdateInfo_InvalidTensorMapY)
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
        {"x":{"value":[2,2,2,2,2], "shape":[5]}, "Y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}}
    )"_json;    // 'Y' is invalid tensor
    std::ofstream d("/tmp/Data.jsonl");
    std::ofstream i("/tmp/data.txt");
    std::string data;
    int size;
    data = data1.dump();
    size = data.size();
    d << data << std::endl;
    i << "000000000" << std::endl;
    data = data2.dump();
    d << data << std::endl;
    i << "000000" << (size + 1) << std::endl;

    auto params_updateInfo = R"(
        {
          "method": "UpdateInfo",
          "parameters": {
            "client": {
              "dataSet": "{\"save_result\":\"success\",\"tensor_map_file\":\"/tmp/Data.jsonl\",\"tensor_map_index_file\":\"/tmp/data.txt\"}",
              "output": "../../resources/TrainManagerRoot/fl/task-deploy"
            },
            "server": {
              "hyperParams": "../../resources/LinearHLCR/back_up/LinearHLCRUpdateHyperParams.json"
            }
          }
        }
    )"_json;

    // UpdateInfo
    auto results = linear_hlcr::LinearHLCR_JNIF::UpdateInfo(model_ptr, params_updateInfo);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 1);
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("invalid tensor map\\. 'x' or 'y' not included\\. \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}

//
// LinearHLCR.cpp:478:        if (std::abs(probs.sum() - 1.0) > thr) THROW_FL_EXCEPTION(str_format("This DoubleVector is not a probability distribution. (Sum of probs : %f).", probs.sum()));
//
TEST(TestFLExceptionForLinearHLCR, SampleGroupLabel_NotTestable)
{
    SUCCEED();

    // MEMO: Assume success because the exception message is correctly generated.
    //
    // file:LinearHLCR/LinearHLCR_JNIF.cpp line:125:Caught FLException: This DoubleVector is not a probability distribution. (Sum of probs : 1.000000). [LinearHLCR/LinearHLCR.cpp:478]
    // {
    //   "method": "Training",
    //   "results": {
    //     "description": "This DoubleVector is not a probability distribution. (Sum of probs : 1.000000). [LinearHLCR/LinearHLCR.cpp:478]",
    //     "state": 1
    //   }
    // }
}

//
// LinearHLCR.cpp:511:    if (global_model_ptr->getK() != internal_model_ptr->getK()) THROW_FL_EXCEPTION(str_format("unmatch K. global_model:%d internal_model:%d", global_model_ptr->getK(), internal_model_ptr->getK()));
//
TEST(TestFLExceptionForLinearHLCR, Initialize_UnmatchK)
{
    // generate invalid cluster_map.json
    auto hyper_params = R"(
        {
            "K": 2,
            "cluster_map": {
                "group0": 1,
                "group1": 1
            }
        }
    )"_json;
    std::ofstream o("/tmp/cluster_map.json");
    o << hyper_params.dump() << std::endl;

    auto params_initialize = R"(
        {
          "method": "Initialize",
          "parameters": {
            "internal": {
              "clusterMap": "/tmp/cluster_map.json"
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
    ASSERT_EQ((linear_hlcr::LinearHLCR*)0, model_ptr);
}

//
// LinearHLCR.cpp:511:    if (global_model_ptr->getK() != internal_model_ptr->getK()) THROW_FL_EXCEPTION(str_format("unmatch K. global_model:%d internal_model:%d", global_model_ptr->getK(), internal_model_ptr->getK()));
//
TEST(TestFLExceptionForLinearHLCR, Initialize_Success)
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
}

//
// LinearHLCR.cpp:528:            THROW_FL_EXCEPTION(str_format("invalid tensor map. No 'x' or 'y' or 'g'"));
//
TEST(TestFLExceptionForLinearHLCR, Training_InvalidTensorMap_NotTestable2)
{
    // see. TEST(TestFLExceptionForLinearHLCR, Training_InvalidTensorMapX)
    // see. TEST(TestFLExceptionForLinearHLCR, Training_InvalidTensorMapY)
    // see. TEST(TestFLExceptionForLinearHLCR, Training_InvalidTensorMapG)
    SUCCEED();
}

//
// LinearHLCR_JNIF.cpp:32:                = linear_hlcr::LinearHLCRInternalModel::fromJson(internal_model_json);
//
TEST(TestFLExceptionForLinearHLCR, Initialize_ParseErrorInternalModels)
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
                "../../resources/LinearHLCR/SNE/ParseError_LinearRegressionGlobalModel3.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel4.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel5.json"
              ]
            }
          }
        }
    )"_json;

    // Initialize
    linear_hlcr::LinearHLCR* model_ptr = (linear_hlcr::LinearHLCR*)linear_hlcr::LinearHLCR_JNIF::Initialize(params_initialize);
    ASSERT_EQ((linear_hlcr::LinearHLCR*)0, model_ptr);
}

//
// LinearHLCR_JNIF.cpp:32:                = linear_hlcr::LinearHLCRInternalModel::fromJson(internal_model_json);
//
TEST(TestFLExceptionForLinearHLCR, Initialize_InvalidInternalModels)
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
                "../../resources/LinearHLCR/SNE/Invalid_LinearRegressionGlobalModel2.json",
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
    ASSERT_EQ((linear_hlcr::LinearHLCR*)0, model_ptr);
}

//
// LinearHLCR_JNIF.cpp:32:                = linear_hlcr::LinearHLCRInternalModel::fromJson(internal_model_json);
//
TEST(TestFLExceptionForLinearHLCR, Initialize_NoFoundInternalModels)
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
                "../../resources/LinearHLCR/SNE/NoFound_LinearRegressionGlobalModel3.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel4.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel5.json"
              ]
            }
          }
        }
    )"_json;

    // Initialize
    linear_hlcr::LinearHLCR* model_ptr = (linear_hlcr::LinearHLCR*)linear_hlcr::LinearHLCR_JNIF::Initialize(params_initialize);
    ASSERT_EQ((linear_hlcr::LinearHLCR*)0, model_ptr);
}

//
// LinearHLCR_JNIF.cpp:32:                = linear_hlcr::LinearHLCRInternalModel::fromJson(internal_model_json);
//
TEST(TestFLExceptionForLinearHLCR, Training_Success)
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

    auto params_training = R"(
        {
          "method": "Training",
          "parameters": {
            "client": {
              "dataSet": "{\"save_result\":\"success\",\"tensor_map_file\":\"../../resources/LinearHLCR/SNE/Data.jsonl\",\"tensor_map_index_file\":\"../../resources/LinearHLCR/SNE/data.txt\"}",
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

    ASSERT_EQ(results["results"]["state"], 0);
}

//
// LinearHLCR_JNIF.cpp:27:            = linear_hlcr::LinearHLCRGlobalModel::fromJson(global_model_json);
//
TEST(TestFLExceptionForLinearHLCR, Initialize_ParseErrorGlobalModel)
{
    auto params_initialize = R"(
        {
          "method": "Initialize",
          "parameters": {
            "internal": {
              "clusterMap": null
            },
            "server": {
              "globalWeight": "../../resources/LinearHLCR/SNE/ParseError_LinearHLCRGlobalWeight.json",
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
    ASSERT_EQ((linear_hlcr::LinearHLCR*)0, model_ptr);
}

//
// LinearHLCR_JNIF.cpp:27:            = linear_hlcr::LinearHLCRGlobalModel::fromJson(global_model_json);
//
TEST(TestFLExceptionForLinearHLCR, Initialize_InvalidGlobalModel)
{
    auto params_initialize = R"(
        {
          "method": "Initialize",
          "parameters": {
            "internal": {
              "clusterMap": null
            },
            "server": {
              "globalWeight": "../../resources/LinearHLCR/SNE/Invalid_LinearHLCRGlobalWeight.json",
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
    ASSERT_EQ((linear_hlcr::LinearHLCR*)0, model_ptr);
}

//
// LinearHLCR_JNIF.cpp:27:            = linear_hlcr::LinearHLCRGlobalModel::fromJson(global_model_json);
//
TEST(TestFLExceptionForLinearHLCR, Initialize_NoFoundGlobalModel)
{
    auto params_initialize = R"(
        {
          "method": "Initialize",
          "parameters": {
            "internal": {
              "clusterMap": null
            },
            "server": {
              "globalWeight": "../../resources/LinearHLCR/SNE/NoFound_LinearHLCRGlobalWeight.json",
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
    ASSERT_EQ((linear_hlcr::LinearHLCR*)0, model_ptr);
}

//
// LinearHLCR_JNIF.cpp:27:            = linear_hlcr::LinearHLCRGlobalModel::fromJson(global_model_json);
//
TEST(TestFLExceptionForLinearHLCR, Initialize_UnmatchGlobalWeightDim)
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
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel5.json",
                "../../resources/LinearHLCR/SNE/LinearRegressionGlobalModel6.json"
              ]
            }
          }
        }
    )"_json;    // too many linearModels

    // Initialize
    ASSERT_NO_THROW({
        linear_hlcr::LinearHLCR* model_ptr = (linear_hlcr::LinearHLCR*)linear_hlcr::LinearHLCR_JNIF::Initialize(params_initialize);
        ASSERT_EQ((linear_hlcr::LinearHLCR*)0, model_ptr);
    });
}

//
// LinearHLCR_JNIF.cpp:27:            = linear_hlcr::LinearHLCRGlobalModel::fromJson(global_model_json);
//
TEST(TestFLExceptionForLinearHLCR, Initialize_InvlaidGlobalWeightBeta)
{
    auto global_weight = R"(
        {
            "global_weight": [0.2,0.2,0.2,0.2,0.1,0.1],
            "beta": 0.0
        }
    )"_json;
    std::ofstream o("/tmp/LinearHLCRGlobalWeight.json");
    o << global_weight.dump() << std::endl;

    auto params_initialize = R"(
        {
          "method": "Initialize",
          "parameters": {
            "internal": {
              "clusterMap": null
            },
            "server": {
              "globalWeight": "/tmp/LinearHLCRGlobalWeight.json",
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
    )"_json;    // invalid beta

    // Initialize
    ASSERT_NO_THROW({
        linear_hlcr::LinearHLCR* model_ptr = (linear_hlcr::LinearHLCR*)linear_hlcr::LinearHLCR_JNIF::Initialize(params_initialize);
        ASSERT_EQ((linear_hlcr::LinearHLCR*)0, model_ptr);
    });
}

//
// LinearHLCR_JNIF.cpp:74:            = linear_hlcr::LinearHLCRTrainHyperParams::fromJson(server_json);
//
TEST(TestFLExceptionForLinearHLCR, Training_ParseErrorTrainHyperParams)
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

    auto params_training = R"(
        {
          "method": "Training",
          "parameters": {
            "client": {
              "dataSet": "{\"save_result\":\"success\",\"tensor_map_file\":\"../../resources/LinearHLCR/SNE/Data.jsonl\",\"tensor_map_index_file\":\"../../resources/LinearHLCR/SNE/data.txt\"}",
              "output": "../../resources/TrainManagerRoot/fl/task-train"
            },
            "server": {
              "hyperParams": "../../resources/LinearHLCR/back_up/ParseError_LinearHLCRTrainHyperParams.json",
              "output": "../../resources/output"
            }
          }
        }
    )"_json;

    // Training
    auto results = linear_hlcr::LinearHLCR_JNIF::Training(model_ptr, params_training);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 1);
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("Caught: json exception \\[\\[json\\.exception\\.parse_error\\.101\\] parse error at line 1, column 1: syntax error while parsing value - invalid literal; last read: '#'\\] \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}

//
// LinearHLCR_JNIF.cpp:74:            = linear_hlcr::LinearHLCRTrainHyperParams::fromJson(server_json);
//
TEST(TestFLExceptionForLinearHLCR, Training_NoFoundTrainHyperParams)
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

    auto params_training = R"(
        {
          "method": "Training",
          "parameters": {
            "client": {
              "dataSet": "{\"save_result\":\"success\",\"tensor_map_file\":\"../../resources/LinearHLCR/SNE/Data.jsonl\",\"tensor_map_index_file\":\"../../resources/LinearHLCR/SNE/data.txt\"}",
              "output": "../../resources/TrainManagerRoot/fl/task-train"
            },
            "server": {
              "hyperParams": "../../resources/LinearHLCR/back_up/NoFound_LinearHLCRTrainHyperParams.json",
              "output": "../../resources/output"
            }
          }
        }
    )"_json;

    // Training
    auto results = linear_hlcr::LinearHLCR_JNIF::Training(model_ptr, params_training);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 1);
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("Caught: json exception \\[\\[json\\.exception\\.parse_error\\.101\\] parse error at line 1, column 1: syntax error while parsing value - unexpected end of input; expected '\\[', '\\{', or a literal\\] \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}

//
// LinearHLCR_JNIF.cpp:267:            = linear_hlcr::LinearHLCRUpdateHyperParams::fromJson(update_hyper_params_json);
//
TEST(TestFLExceptionForLinearHLCR, UpdateInfo_Success)
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

    auto params_updateInfo = R"(
        {
          "method": "UpdateInfo",
          "parameters": {
            "client": {
              "dataSet": "{\"save_result\":\"success\",\"tensor_map_file\":\"../../resources/LinearHLCR/SNE/Data.jsonl\",\"tensor_map_index_file\":\"../../resources/LinearHLCR/SNE/data.txt\"}",
              "output": "../../resources/TrainManagerRoot/fl/task-deploy"
            },
            "server": {
              "hyperParams": "../../resources/LinearHLCR/back_up/LinearHLCRUpdateHyperParams.json"
            }
          }
        }
    )"_json;

    // UpdateInfo
    auto results = linear_hlcr::LinearHLCR_JNIF::UpdateInfo(model_ptr, params_updateInfo);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 0);
}

//
// LinearHLCR_JNIF.cpp:267:            = linear_hlcr::LinearHLCRUpdateHyperParams::fromJson(update_hyper_params_json);
//
TEST(TestFLExceptionForLinearHLCR, UpdateInfo_ParseErrorUpdateHyperParams)
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

    auto params_updateInfo = R"(
        {
          "method": "UpdateInfo",
          "parameters": {
            "client": {
              "dataSet": "{\"save_result\":\"success\",\"tensor_map_file\":\"../../resources/LinearHLCR/train_and_eval/TestData.jsonl\",\"tensor_map_index_file\":\"../../resources/LinearHLCR/train_and_eval/TestData.txt\"}",
              "output": "../../resources/TrainManagerRoot/fl/task-deploy"
            },
            "server": {
              "hyperParams": "../../resources/LinearHLCR/back_up/ParseError_LinearHLCRUpdateHyperParams.json"
            }
          }
        }
    )"_json;

    // UpdateInfo
    auto results = linear_hlcr::LinearHLCR_JNIF::UpdateInfo(model_ptr, params_updateInfo);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 1);
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("Caught: json exception \\[\\[json\\.exception\\.parse_error\\.101\\] parse error at line 1, column 1: syntax error while parsing value - invalid literal; last read: '#'\\] \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}

//
// LinearHLCR_JNIF.cpp:267:            = linear_hlcr::LinearHLCRUpdateHyperParams::fromJson(update_hyper_params_json);
//
TEST(TestFLExceptionForLinearHLCR, UpdateInfo_InvalidUpdateHyperParams)
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

    auto params_updateInfo = R"(
        {
          "method": "UpdateInfo",
          "parameters": {
            "client": {
              "dataSet": "{\"save_result\":\"success\",\"tensor_map_file\":\"../../resources/LinearHLCR/train_and_eval/TestData.jsonl\",\"tensor_map_index_file\":\"../../resources/LinearHLCR/train_and_eval/TestData.txt\"}",
              "output": "../../resources/TrainManagerRoot/fl/task-deploy"
            },
            "server": {
              "hyperParams": "../../resources/LinearHLCR/back_up/Invalid_LinearHLCRUpdateHyperParams.json"
            }
          }
        }
    )"_json;

    // UpdateInfo
    auto results = linear_hlcr::LinearHLCR_JNIF::UpdateInfo(model_ptr, params_updateInfo);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 1);
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("Caught: json exception \\[\\[json\\.exception\\.type_error\\.302\\] type must be number, but is null\\] \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}

//
// LinearHLCR_JNIF.cpp:267:            = linear_hlcr::LinearHLCRUpdateHyperParams::fromJson(update_hyper_params_json);
//
TEST(TestFLExceptionForLinearHLCR, UpdateInfo_NoFoundUpdateHyperParams)
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

    auto params_updateInfo = R"(
        {
          "method": "UpdateInfo",
          "parameters": {
            "client": {
              "dataSet": "{\"save_result\":\"success\",\"tensor_map_file\":\"../../resources/LinearHLCR/train_and_eval/TestData.jsonl\",\"tensor_map_index_file\":\"../../resources/LinearHLCR/train_and_eval/TestData.txt\"}",
              "output": "../../resources/TrainManagerRoot/fl/task-deploy"
            },
            "server": {
              "hyperParams": "../../resources/LinearHLCR/back_up/NoFound_LinearHLCRUpdateHyperParams.json"
            }
          }
        }
    )"_json;

    // UpdateInfo
    auto results = linear_hlcr::LinearHLCR_JNIF::UpdateInfo(model_ptr, params_updateInfo);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 1);
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("Caught: json exception \\[\\[json\\.exception\\.parse_error\\.101\\] parse error at line 1, column 1: syntax error while parsing value - unexpected end of input; expected '\\[', '\\{', or a literal\\] \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
    const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
    std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << results["results"]["description"] << std::endl;
}
