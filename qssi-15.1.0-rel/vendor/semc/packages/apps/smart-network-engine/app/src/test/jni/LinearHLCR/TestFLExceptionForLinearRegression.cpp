#include <fstream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "LinearHLCR/LinearHLCR_JNIF.h"
#include "LinearHLCR/LinearHLCR.h"
#include "FLException.h"

TEST(TestFLExceptionForLinearRegression, Initialize_Success)
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
// LinearRegression.cpp:29:    if (D != w.size() + 1 || D * D != H.size()) THROW_FL_EXCEPTION(str_format("D, w, and H are not matched. (D:%d w.size:%d H.size:%d)", D, w.size(), H.size()));
//
TEST(TestFLExceptionForLinearRegression, Initialize_Failed1)
{
    // generate invalid HyperParams.json
    auto global_model = R"(
        {
          "H": [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
          "w": [1.0,1.0,1.0,1.0,1.0,1.0],
          "b": 1.0,
          "d": 6
        }
    )"_json;    // 'w' invalid
    std::ofstream o("/tmp/GlobalModel.json");
    o << global_model.dump() << std::endl;

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
                "/tmp/GlobalModel.json"
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
// LinearRegression.cpp:29:    if (D != w.size() + 1 || D * D != H.size()) THROW_FL_EXCEPTION(str_format("D, w, and H are not matched. (D:%d w.size:%d H.size:%d)", D, w.size(), H.size()));
//
TEST(TestFLExceptionForLinearRegression, Initialize_Failed2)
{
    // generate invalid HyperParams.json
    auto global_model = R"(
        {
          "H": [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
          "w": [1.0,1.0,1.0,1.0,1.0],
          "b": 1.0,
          "d": 6
        }
    )"_json;    // 'H' invalid
    std::ofstream o("/tmp/GlobalModel.json");
    o << global_model.dump() << std::endl;

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
                "/tmp/GlobalModel.json"
              ]
            }
          }
        }
    )"_json;

    // Initialize
    linear_hlcr::LinearHLCR* model_ptr = (linear_hlcr::LinearHLCR*)linear_hlcr::LinearHLCR_JNIF::Initialize(params_initialize);
    ASSERT_EQ((linear_hlcr::LinearHLCR*)0, model_ptr);
}

TEST(TestFLExceptionForLinearRegression, Training_Success)
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

//
// LinearRegression.cpp:41:    if (D.getDim() != c.getDim()) THROW_FL_EXCEPTION(str_format("Dimensions D and c do not match. (D:%d c:%d)", D.getDim(), c.getDim()));
//
TEST(TestFLExceptionForLinearRegression, Training_Failed)
{
    std::vector<double> vector_double_A { 101.1, 201.1, 201.1, 202.2 };
    int dim_A = 2;

    std::vector<double> vector_double_B { 101.1, 201.1, 201.1, 202.2, 301.1 };

    ASSERT_NO_THROW({

        auto symmetric_matrix = linear_hlcr::SymmetricMatrix::create(vector_double_A, dim_A);

        linear_hlcr::DoubleVector double_vector(vector_double_B);

        try {
            std::unique_ptr<linear_hlcr::LinearRegressionLocalModel> local_model = linear_hlcr::LinearRegressionLocalModel::create(symmetric_matrix, double_vector);
        }
        catch (FLException& ex) {
            const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
            std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
            ASSERT_THAT(ex.what(), testing::MatchesRegex("Dimensions D and c do not match\\. \\(D:2 c:5\\) \\[LinearHLCR/LinearRegression\\.cpp:[0-9]+\\]"));
        }
    });
}

TEST(TestFLExceptionForLinearRegression, InvalidTrainHyperParams)
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
              "hyperParams": "../../resources/LinearHLCR/back_up/Invalid_LinearHLCRTrainHyperParams.json",
              "output": "../../resources/output"
            }
          }
        }
    )"_json;

    // Training
    auto results = linear_hlcr::LinearHLCR_JNIF::Training(model_ptr, params_training);
    std::cerr << results.dump(2) << std::endl;

    ASSERT_EQ(results["results"]["state"], 1);
    ASSERT_THAT(results["results"]["description"], testing::MatchesRegex("Caught: json exception \\[\\[json\\.exception\\.type_error\\.302\\] type must be number, but is null\\] \\[LinearHLCR/LinearHLCR\\.cpp:[0-9]+\\]>>\\[LinearHLCR/LinearHLCR_JNIF\\.cpp:[0-9]+\\]"));
}

TEST(TestFLExceptionForLinearRegression, fromJson_NoDim)
{
    auto global_model = R"(
        {
          "D": 1,
          "H": 2.0,
          "w": 3.0,
          "b": 4.0
        }
    )"_json;    // no 'd'

    try {
        auto json = linear_hlcr::LinearRegressionGlobalModel::fromJson(global_model.dump());
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Caught: json exception \\[\\[json\\.exception\\.type_error\\.305\\] cannot use operator\\[\\] with a string argument with string\\] \\[LinearHLCR/LinearRegression\\.cpp:[0-9]+\\]"));
    }
}

TEST(TestFLExceptionForLinearRegression, fromJson_NoH)
{
    auto global_model = R"(
        {
          "d": 1,
          "h": 2.0,
          "w": 3.0,
          "b": 4.0
        }
    )"_json;    // no 'H'

    try {
        auto json = linear_hlcr::LinearRegressionGlobalModel::fromJson(global_model.dump());
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Caught: json exception \\[\\[json\\.exception\\.type_error\\.305\\] cannot use operator\\[\\] with a string argument with string\\] \\[LinearHLCR/LinearRegression\\.cpp:[0-9]+\\]"));
    }
}

TEST(TestFLExceptionForLinearRegression, fromJson_NoW)
{
    auto global_model = R"(
        {
          "d": 1,
          "H": 2.0,
          "W": 3.0,
          "b": 4.0
        }
    )"_json;    // no 'w'

    try {
        auto json = linear_hlcr::LinearRegressionGlobalModel::fromJson(global_model.dump());
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Caught: json exception \\[\\[json\\.exception\\.type_error\\.305\\] cannot use operator\\[\\] with a string argument with string\\] \\[LinearHLCR/LinearRegression\\.cpp:[0-9]+\\]"));
    }
}

TEST(TestFLExceptionForLinearRegression, fromJson_NoB)
{
    auto global_model = R"(
        {
          "d": 1,
          "H": 2.0,
          "w": 3.0,
          "B": 4.0
        }
    )"_json;    // no 'b'

    try {
        auto json = linear_hlcr::LinearRegressionGlobalModel::fromJson(global_model.dump());
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Caught: json exception \\[\\[json\\.exception\\.type_error\\.305\\] cannot use operator\\[\\] with a string argument with string\\] \\[LinearHLCR/LinearRegression\\.cpp:[0-9]+\\]"));
    }
}

TEST(TestFLExceptionForLinearRegression, fromJson_InvalidDim)
{
    auto global_model = R"(
        {
          "d": "1",
          "H": 2.0,
          "w": 3.0,
          "b": 4.0
        }
    )"_json;    // 'd': 1

    try {
        auto json = linear_hlcr::LinearRegressionGlobalModel::fromJson(global_model.dump());
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Caught: json exception \\[\\[json\\.exception\\.type_error\\.305\\] cannot use operator\\[\\] with a string argument with string\\] \\[LinearHLCR/LinearRegression\\.cpp:[0-9]+\\]"));
    }
}

TEST(TestFLExceptionForLinearRegression, fromJson_InvalidH)
{
    auto global_model = R"(
        {
          "d": 1,
          "H": "2.0",
          "w": 3.0,
          "b": 4.0
        }
    )"_json;

    try {
        auto json = linear_hlcr::LinearRegressionGlobalModel::fromJson(global_model.dump());
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Caught: json exception \\[\\[json\\.exception\\.type_error\\.305\\] cannot use operator\\[\\] with a string argument with string\\] \\[LinearHLCR/LinearRegression\\.cpp:[0-9]+\\]"));
    }
}

TEST(TestFLExceptionForLinearRegression, fromJson_InvalidW)
{
    auto global_model = R"(
        {
          "d": 1,
          "H": 2.0,
          "w": "3.0",
          "b": 4.0
        }
    )"_json;

    try {
        auto json = linear_hlcr::LinearRegressionGlobalModel::fromJson(global_model.dump());
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Caught: json exception \\[\\[json\\.exception\\.type_error\\.305\\] cannot use operator\\[\\] with a string argument with string\\] \\[LinearHLCR/LinearRegression\\.cpp:[0-9]+\\]"));
    }
}

TEST(TestFLExceptionForLinearRegression, fromJson_InvalidB)
{
    auto global_model = R"(
        {
          "d": 1,
          "H": 2.0,
          "w": 3.0,
          "b": "4.0"
        }
    )"_json;

    try {
        auto json = linear_hlcr::LinearRegressionGlobalModel::fromJson(global_model.dump());
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Caught: json exception \\[\\[json\\.exception\\.type_error\\.305\\] cannot use operator\\[\\] with a string argument with string\\] \\[LinearHLCR/LinearRegression\\.cpp:[0-9]+\\]"));
    }
}
