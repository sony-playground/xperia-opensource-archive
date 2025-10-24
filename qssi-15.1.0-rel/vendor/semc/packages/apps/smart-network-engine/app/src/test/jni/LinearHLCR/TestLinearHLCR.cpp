#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "LinearHLCR/LinearHLCR.h"
#include "tensor/data_serializer.h"

#define TEMP_FOLDER std::string("./Testing/Temporary")
#define RESOURCE_FOLDER std::string("../../../test/resources/LinearHLCR")

TEST(test_LinearHLCRTrainHyperParams, BasicAssertions) {
    auto input = R"({"hyperParams":"../../../test/resources/LinearHLCR/back_up/LinearHLCRTrainHyperParams.json"})"_json;
    auto params = linear_hlcr::LinearHLCRTrainHyperParams::fromJson(input);
    
    EXPECT_DOUBLE_EQ(1, params->getSigma()); 
}

TEST(test_LinearHLCRUpdateHyperParams, BasicAssertions) {
    auto input = R"({"hyperParams":"../../../test/resources/LinearHLCR/back_up/LinearHLCRUpdateHyperParams.json"})"_json;    
    auto params = linear_hlcr::LinearHLCRUpdateHyperParams::fromJson(input);
    
    EXPECT_DOUBLE_EQ(1, params->getSigma()); 
}

TEST(test_LlinearHLCRLocalModel_save, BasicAssertions) {
    linear_hlcr::IntVector intVector = linear_hlcr::IntVector(std::vector<int>({1,2,3}));

    linear_hlcr::SymmetricMatrix D = 
        linear_hlcr::SymmetricMatrix::create(std::vector<double>({1,2,3,2,3,4,3,4,5}), 3);
    linear_hlcr::DoubleVector c = 
            linear_hlcr::DoubleVector(std::vector<double>({1.1,2.2,3.3}));

    std::vector<std::shared_ptr<linear_hlcr::LinearRegressionLocalModel>> model_vec(3);
    for (int k=0;k<3;k++) {
        model_vec[k] = linear_hlcr::LinearRegressionLocalModel::create(D, c);
    }

    auto model = linear_hlcr::LinearHLCRLocalModel::create(intVector, model_vec);
    EXPECT_TRUE(model->save(TEMP_FOLDER)->dump() == 
            std::string("{\"linearModels\":[\"") + TEMP_FOLDER + 
            std::string("/linear_model0.json\",\"") + TEMP_FOLDER + 
            std::string("/linear_model1.json\",\"") + TEMP_FOLDER + 
            std::string("/linear_model2.json\"],\"localCount\":\"") + TEMP_FOLDER + 
            std::string("/local_count.json\"}"));
}

TEST(test_LinearHLCRGlobalModel, BasicAssertions) {
    json input = 
        {
            {
                linear_hlcr::LinearHLCRGlobalModel::KEY_OF_GLOBAL_WEIGHT_FILE, 
                    RESOURCE_FOLDER + std::string("/SNE/LinearHLCRGlobalWeight.json")
            },
            {
                linear_hlcr::LinearHLCRGlobalModel::KEY_OF_LINEAR_MODEL_FILES,
                    {
                        RESOURCE_FOLDER + std::string("/SNE/LinearRegressionGlobalModel0.json"),
                        RESOURCE_FOLDER + std::string("/SNE/LinearRegressionGlobalModel1.json"),
                        RESOURCE_FOLDER + std::string("/SNE/LinearRegressionGlobalModel2.json"),
                        RESOURCE_FOLDER + std::string("/SNE/LinearRegressionGlobalModel3.json"),
                        RESOURCE_FOLDER + std::string("/SNE/LinearRegressionGlobalModel4.json"),
                        RESOURCE_FOLDER + std::string("/SNE/LinearRegressionGlobalModel5.json")
                    }
            }
        };
    std::cout << input.dump() << std::endl;
    auto model = linear_hlcr::LinearHLCRGlobalModel::fromJson(input);
    EXPECT_EQ(6, model->getK());

    std::vector<double> vec = model->getGlobalWeight().getVector();
    EXPECT_DOUBLE_EQ(0.2, vec[0]);
    EXPECT_DOUBLE_EQ(0.2, vec[1]); 
    EXPECT_DOUBLE_EQ(0.2, vec[2]);
    EXPECT_DOUBLE_EQ(0.2, vec[3]);
    EXPECT_DOUBLE_EQ(0.1, vec[4]);
    EXPECT_DOUBLE_EQ(0.1, vec[5]);

    auto model0 = model->getLinearModel(0);
    EXPECT_DOUBLE_EQ(0.17108477894388427, model0->getB());

    EXPECT_DOUBLE_EQ(1.0, model->getBeta());
}

TEST(test_LinearHLCRInternalModel_createInitialInternalModel, BasicAssertions) {
    auto model = linear_hlcr::LinearHLCRInternalModel::createInitialInternalModel(3);

    EXPECT_EQ(3, model->getK());

    auto str_list = model->getGroupList();
    EXPECT_EQ(0, str_list.size());

    auto local_count = model->calcLocalCount().getVector();
    EXPECT_EQ(0, local_count[0]);
    EXPECT_EQ(0, local_count[1]);
    EXPECT_EQ(0, local_count[2]);
}

TEST(test_LinearHLCRInternalModel_fromJson, BasicAssertions) {
    json input = 
        {
            {
                linear_hlcr::LinearHLCRInternalModel::KEY_OF_CLUSTER_MAP_FILE, 
                    RESOURCE_FOLDER + std::string("/calibrate/cluster_map.json")
            }
        };
    auto model = linear_hlcr::LinearHLCRInternalModel::fromJson(input);

    EXPECT_EQ(2, model->getK());
    EXPECT_EQ(1, model->getClusterID("group0"));
    EXPECT_EQ(1, model->getClusterID("group1"));
    EXPECT_EQ(linear_hlcr::LinearHLCRInternalModel::GROUP_ID_NOT_FOUND, model->getClusterID("group_?"));

    auto local_count = model->calcLocalCount().getVector();
    EXPECT_EQ(0, local_count[0]);
    EXPECT_EQ(2, local_count[1]);

    EXPECT_TRUE(model->save(TEMP_FOLDER)->dump() == "{\"clusterMap\":\"./Testing/Temporary/cluster_map.json\"}");
}

TEST(test_LinearHLCR_predict, BasicAssertions) {
    json input_for_global_model = 
        {
            {
                linear_hlcr::LinearHLCRGlobalModel::KEY_OF_GLOBAL_WEIGHT_FILE, 
                    RESOURCE_FOLDER + std::string("/python_test_case/global_weight.json")
            },
            {
                linear_hlcr::LinearHLCRGlobalModel::KEY_OF_LINEAR_MODEL_FILES,
                    {
                        RESOURCE_FOLDER + std::string("/python_test_case/model_S_0.json"),
                        RESOURCE_FOLDER + std::string("/python_test_case/model_S_1.json"),
                    }
            }
        };
    auto global_model = linear_hlcr::LinearHLCRGlobalModel::fromJson(input_for_global_model);

    json input_for_internal_model = 
        {
            {
                linear_hlcr::LinearHLCRInternalModel::KEY_OF_CLUSTER_MAP_FILE, 
                    RESOURCE_FOLDER + std::string("/python_test_case/cluster_map.json")
            }
        };
    auto internal_model = linear_hlcr::LinearHLCRInternalModel::fromJson(input_for_internal_model);

    auto linearHLCR = linear_hlcr::LinearHLCR::create(std::move(global_model), std::move(internal_model));

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(
            RESOURCE_FOLDER + std::string("/python_test_case/data_S.jsonl"),
            RESOURCE_FOLDER + std::string("/python_test_case/data_S.dat")
    );
    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);

    json predict_result_json;
    std::string predict_result_file_path = RESOURCE_FOLDER + std::string("/python_test_case/predict_result.json");
    std::ifstream pifs(predict_result_file_path);
    pifs >> predict_result_json;
    std::vector<double> predict_result_python = predict_result_json["y_pred"];

    for (int i = 1; i <= 10; i++) {
        std::shared_ptr<fl::TensorMap> record = data_deserializer.get(i);
        auto predict_result = linearHLCR->predict(*record);
        auto p_pred = predict_result->get(linear_hlcr::LinearHLCR::KEY_OF_PREDICTION_RESULT)->doubleValue();
        EXPECT_DOUBLE_EQ(predict_result_python[i-1], p_pred);
        std::cout << p_pred << " "  << predict_result_python[i-1] << std::endl;
    }

    delete linearHLCR;
}

TEST(test_LinearHLCR_train, BasicAssertions) {
    json input_for_global_model = 
        {
            {
                linear_hlcr::LinearHLCRGlobalModel::KEY_OF_GLOBAL_WEIGHT_FILE, 
                    RESOURCE_FOLDER + std::string("/python_test_case/global_weight.json")
            },
            {
                linear_hlcr::LinearHLCRGlobalModel::KEY_OF_LINEAR_MODEL_FILES,
                    {
                        RESOURCE_FOLDER + std::string("/python_test_case/model_S_0.json"),
                        RESOURCE_FOLDER + std::string("/python_test_case/model_S_1.json"),
                    }
            }
        };
    auto global_model = linear_hlcr::LinearHLCRGlobalModel::fromJson(input_for_global_model);

    json input_for_internal_model = 
        {
            {
                linear_hlcr::LinearHLCRInternalModel::KEY_OF_CLUSTER_MAP_FILE, 
                    RESOURCE_FOLDER + std::string("/python_test_case/cluster_map.json")
            }
        };
    auto internal_model = linear_hlcr::LinearHLCRInternalModel::fromJson(input_for_internal_model);

    auto linearHLCR = linear_hlcr::LinearHLCR::create(std::move(global_model), std::move(internal_model));

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(
            RESOURCE_FOLDER + std::string("/python_test_case/data_S.jsonl"),
            RESOURCE_FOLDER + std::string("/python_test_case/data_S.dat")
    );
    fl::DataMetadata data_metadata = data_serializer.getMetadata();

    auto input_for_hypara = R"({"hyperParams":"../../../test/resources/LinearHLCR/python_test_case/train_hyper_params.json"})"_json;
    auto params = linear_hlcr::LinearHLCRTrainHyperParams::fromJson(input_for_hypara);
    auto train_result = linearHLCR->train(data_metadata, *params);

    // TODO : fix to use stub for sampling
    int g0 = train_result.second->getClusterID("g0");
    int g1 = train_result.second->getClusterID("g1");
    for (int i = 0; i < 100 && (g0 != 0 || g1 != 1); i++) {
        train_result = linearHLCR->train(data_metadata, *params);
        g0 = train_result.second->getClusterID("g0");
        g1 = train_result.second->getClusterID("g1");
    }

    auto local_model = train_result.first;
    auto new_internal_model = train_result.second;

    // Sometimes failed due to sampling
    auto local_count = new_internal_model->calcLocalCount().getVector();
    EXPECT_EQ(1, local_count[0]);
    EXPECT_EQ(1, local_count[1]);

    std::string json_str = local_model->save(TEMP_FOLDER)->dump();
    std::cout << json_str << std::endl;
    EXPECT_TRUE(json_str == 
        std::string("{\"linearModels\":[\"") + 
        TEMP_FOLDER + std::string("/linear_model0.json\",\"") + 
        TEMP_FOLDER + std::string("/linear_model1.json\"],") +
        std::string("\"localCount\":\"") + 
        TEMP_FOLDER + std::string("/local_count.json\"}")
    );

    for (int i = 0; i < 2; i++) {
        std::string python_result_file = 
                RESOURCE_FOLDER + std::string("/python_test_case/train_result_model_") + 
                std::to_string(i) + std::string(".json");
        std::ifstream rifs(python_result_file);
        std::string python_result;
        rifs >> python_result;

        std::string result_file = 
                TEMP_FOLDER + std::string("/linear_model") +
                std::to_string(i) + std::string(".json");
        std::ifstream pifs(result_file);
        std::string result;
        pifs >> result;

        std::cout << result << std::endl;
        std::cout << python_result << std::endl;

        EXPECT_TRUE(result == python_result);
    }

    delete linearHLCR;
}

TEST(test_LinearHLCR_updateInternalModel, BasicAssertions) {
    json input_for_global_model = 
        {
            {
                linear_hlcr::LinearHLCRGlobalModel::KEY_OF_GLOBAL_WEIGHT_FILE, 
                    RESOURCE_FOLDER + std::string("/python_test_case/global_weight.json")
            },
            {
                linear_hlcr::LinearHLCRGlobalModel::KEY_OF_LINEAR_MODEL_FILES,
                    {
                        RESOURCE_FOLDER + std::string("/python_test_case/model_S_0.json"),
                        RESOURCE_FOLDER + std::string("/python_test_case/model_S_1.json"),
                    }
            }
        };
    auto global_model = linear_hlcr::LinearHLCRGlobalModel::fromJson(input_for_global_model);

    json input_for_internal_model = 
        {
            {
                linear_hlcr::LinearHLCRInternalModel::KEY_OF_CLUSTER_MAP_FILE, 
                    RESOURCE_FOLDER + std::string("/python_test_case/cluster_map_reverse.json")
            }
        };
    auto internal_model = linear_hlcr::LinearHLCRInternalModel::fromJson(input_for_internal_model);
    EXPECT_EQ(1, internal_model->getClusterID("g0"));
    EXPECT_EQ(0, internal_model->getClusterID("g1"));

    auto linearHLCR = linear_hlcr::LinearHLCR::create(std::move(global_model), std::move(internal_model));

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(
            RESOURCE_FOLDER + std::string("/python_test_case/data_S.jsonl"),
            RESOURCE_FOLDER + std::string("/python_test_case/data_S.dat")
    );
    fl::DataMetadata data_metadata = data_serializer.getMetadata();

    auto input_for_hypara = R"({"hyperParams":"../../../test/resources/LinearHLCR/python_test_case/train_hyper_params.json"})"_json;
    auto params = linear_hlcr::LinearHLCRUpdateHyperParams::fromJson(input_for_hypara);
    auto new_internal_model = linearHLCR->updateInternalModel(data_metadata, *params);

    EXPECT_EQ(0, new_internal_model->getClusterID("g0"));
    EXPECT_EQ(1, new_internal_model->getClusterID("g1"));

    delete linearHLCR;
}


TEST(test_LinearHLCR_calcLoss, BasicAssertions) {
    json input_for_global_model = 
        {
            {
                linear_hlcr::LinearHLCRGlobalModel::KEY_OF_GLOBAL_WEIGHT_FILE, 
                    RESOURCE_FOLDER + std::string("/python_test_case/global_weight.json")
            },
            {
                linear_hlcr::LinearHLCRGlobalModel::KEY_OF_LINEAR_MODEL_FILES,
                    {
                        RESOURCE_FOLDER + std::string("/python_test_case/model_S_0.json"),
                        RESOURCE_FOLDER + std::string("/python_test_case/model_S_1.json"),
                    }
            }
        };
    auto global_model = linear_hlcr::LinearHLCRGlobalModel::fromJson(input_for_global_model);

    json input_for_internal_model = 
        {
            {
                linear_hlcr::LinearHLCRInternalModel::KEY_OF_CLUSTER_MAP_FILE, 
                    RESOURCE_FOLDER + std::string("/python_test_case/cluster_map.json")
            }
        };
    auto internal_model = linear_hlcr::LinearHLCRInternalModel::fromJson(input_for_internal_model);

    auto linearHLCR = linear_hlcr::LinearHLCR::create(std::move(global_model), std::move(internal_model));

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(
            RESOURCE_FOLDER + std::string("/python_test_case/data_S.jsonl"),
            RESOURCE_FOLDER + std::string("/python_test_case/data_S.dat")
    );
    fl::DataMetadata data_metadata = data_serializer.getMetadata();

    json loss_json;
    std::string predict_result_file_path = RESOURCE_FOLDER + std::string("/python_test_case/label_error.json");
    std::ifstream pifs(predict_result_file_path);
    pifs >> loss_json;
    std::vector<double> label_error_python = loss_json["error"];

    auto loss = linearHLCR->calcLoss(data_metadata);
    auto loss_value = loss->get(linear_hlcr::LinearHLCR::KEY_OF_LOSS)->doubleValue();

    double sum_of_error = 0.0;
    for (int i = 0; i < 10; i++) {
        sum_of_error += label_error_python[i] * label_error_python[i];
    }
    EXPECT_NEAR(sum_of_error, loss_value, 1e-8);

    delete linearHLCR;
}

TEST(test_LinearHLCR_setInternalModel, BasicAssertions) {
    json input_for_global_model = 
        {
            {
                linear_hlcr::LinearHLCRGlobalModel::KEY_OF_GLOBAL_WEIGHT_FILE, 
                    RESOURCE_FOLDER + std::string("/python_test_case/global_weight.json")
            },
            {
                linear_hlcr::LinearHLCRGlobalModel::KEY_OF_LINEAR_MODEL_FILES,
                    {
                        RESOURCE_FOLDER + std::string("/python_test_case/model_S_0.json"),
                        RESOURCE_FOLDER + std::string("/python_test_case/model_S_1.json"),
                    }
            }
        };
    auto global_model = linear_hlcr::LinearHLCRGlobalModel::fromJson(input_for_global_model);

    json input_for_internal_model = 
        {
            {
                linear_hlcr::LinearHLCRInternalModel::KEY_OF_CLUSTER_MAP_FILE, 
                    RESOURCE_FOLDER + std::string("/python_test_case/cluster_map_reverse.json")
            }
        };
    auto internal_model = linear_hlcr::LinearHLCRInternalModel::fromJson(input_for_internal_model);
    auto linearHLCR = linear_hlcr::LinearHLCR::create(std::move(global_model), std::move(internal_model));


    json input_for_new_internal_model = 
        {
            {
                linear_hlcr::LinearHLCRInternalModel::KEY_OF_CLUSTER_MAP_FILE, 
                    RESOURCE_FOLDER + std::string("/python_test_case/cluster_map.json")
            }
        };
    auto new_internal_model = linear_hlcr::LinearHLCRInternalModel::fromJson(input_for_new_internal_model);
    linearHLCR->setInternalModel(std::move(new_internal_model));

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(
            RESOURCE_FOLDER + std::string("/python_test_case/data_S.jsonl"),
            RESOURCE_FOLDER + std::string("/python_test_case/data_S.dat")
    );
    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);

    json predict_result_json;
    std::string predict_result_file_path = RESOURCE_FOLDER + std::string("/python_test_case/predict_result.json");
    std::ifstream pifs(predict_result_file_path);
    pifs >> predict_result_json;
    std::vector<double> predict_result_python = predict_result_json["y_pred"];

    for (int i = 1; i <= 10; i++) {
        std::shared_ptr<fl::TensorMap> record = data_deserializer.get(i);
        auto predict_result = linearHLCR->predict(*record);
        auto p_pred = predict_result->get(linear_hlcr::LinearHLCR::KEY_OF_PREDICTION_RESULT)->doubleValue();
        EXPECT_DOUBLE_EQ(predict_result_python[i-1], p_pred);
        std::cout << p_pred << " "  << predict_result_python[i-1] << std::endl;
    }

    delete linearHLCR;
}
