#include <float.h>
#include <fstream>
#include <string>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "NNHLCR/NNHLCR_JNIF.h"

#define FL_TEST_DATA_DIR   "Testing/Temporary/"

class TestNNHLCR: public ::testing::Test
{
public:
    std::string jsonl_file;
    std::string index_file;

    std::string case_name;
    std::string test_suite_name;
    std::string name;

private:
    void cleanup() {
        system((std::string("/bin/rm -f ") + std::string(FL_TEST_DATA_DIR) + this->case_name + std::string(".*")).c_str());
    }

protected:
    virtual void SetUp() {
        const testing::TestInfo* ti = testing::UnitTest::GetInstance()->current_test_info();

        this->case_name = std::string(ti->test_suite_name()) + "." + std::string(ti->name());

        this->jsonl_file = std::string(FL_TEST_DATA_DIR) + this->case_name + ".tensor_map.jsonl";
        this->index_file = std::string(FL_TEST_DATA_DIR) + this->case_name + ".tensor_map.index";

        this->test_suite_name = std::string(ti->test_suite_name());
        this->name = std::string(ti->name());

        this->cleanup();
    }
    virtual void TearDown() {
        this->cleanup();
    }

    bool is_inside_container() {
        std::ifstream dockerenv("/.dockerenv");
        return dockerenv.good();
    }
};

TEST_F(TestNNHLCR, Initialize_ValidTensorMapJson)
{
    long rcd = nn_hlcr::NNHLCR_JNIF::Initialize(std::string("").c_str());
    ASSERT_TRUE(rcd == 0L);
}

TEST_F(TestNNHLCR, Training_InvalidMaxLength)
{
    std::string hlcr_param_dat = std::string(FL_TEST_DATA_DIR) + this->case_name + ".HLCR_Param.dat";
    std::ofstream ofs(hlcr_param_dat);
    ofs << "2" << std::endl;
    ofs << "0.99" << std::endl;
    ofs << "0.01" << std::endl;
    ofs << "29" << std::endl;
    ofs << "18" << std::endl;

    std::stringstream modelInfo;
    modelInfo << "2" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster1.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster2.protobuf" << std::endl;
    modelInfo << hlcr_param_dat << std::endl;
    modelInfo << "../../resources/NNHLCR/back_up/ClusterMap.dat" << std::endl;

    long rcd = nn_hlcr::NNHLCR_JNIF::Initialize(modelInfo.str().c_str());
    ASSERT_TRUE(rcd != 0L);

    LstmLCRModel* mlObj = (LstmLCRModel*)rcd;

    auto metaData = R"(
        {
            "save_result": "success",
            "tensor_map_file": "../../resources/NNHLCR/data/AllData.jsonl",
            "tensor_map_index_file": "../../resources/NNHLCR/data/AllData.txt"
        }
    )"_json;

    std::stringstream trainInfo;
    trainInfo << "../../resources/NNHLCR/task_info/Hyper_Param.dat" << std::endl;
    trainInfo << "../../resources/NNHLCR/task_info/preprocess_params.dat" << std::endl;
    trainInfo << std::string(FL_TEST_DATA_DIR) + this->case_name + ".output_folder" << std::endl;
    trainInfo << std::string(FL_TEST_DATA_DIR) + this->case_name + ".backup_folder" << std::endl;

    std::string result = nn_hlcr::NNHLCR_JNIF::Training(mlObj, metaData.dump().c_str(), trainInfo.str().c_str());
    ASSERT_EQ("", result);
}

TEST_F(TestNNHLCR, Training_InvalidTrainInfo)
{
    std::stringstream modelInfo;
    modelInfo << "2" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster1.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster2.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/HLCR_Param.dat" << std::endl;
    modelInfo << "../../resources/NNHLCR/back_up/ClusterMap.dat" << std::endl;

    long rcd = nn_hlcr::NNHLCR_JNIF::Initialize(modelInfo.str().c_str());
    ASSERT_TRUE(rcd != 0L);

    LstmLCRModel* mlObj = (LstmLCRModel*)rcd;

    auto metaData = R"(
        {
            "save_result": "success",
            "tensor_map_file": "../../resources/NNHLCR/data/AllData.jsonl",
            "tensor_map_index_file": "../../resources/NNHLCR/data/AllData.txt"
        }
    )"_json;

    std::stringstream trainInfo;
    trainInfo << "../../resources/NNHLCR/task_info/Hyper_Param.dat" << std::endl;
    trainInfo << "../../resources/NNHLCR/task_info/preprocess_params.dat" << std::endl;
    // trainInfo << std::string(FL_TEST_DATA_DIR) + this->case_name + ".output_folder" << std::endl;
    // trainInfo << std::string(FL_TEST_DATA_DIR) + this->case_name + ".backup_folder" << std::endl;

    std::string result = nn_hlcr::NNHLCR_JNIF::Training(mlObj, metaData.dump().c_str(), trainInfo.str().c_str());
    ASSERT_EQ("", result);
}

TEST_F(TestNNHLCR, Training_EmptyTrainInfo)
{
    std::stringstream modelInfo;
    modelInfo << "2" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster1.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster2.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/HLCR_Param.dat" << std::endl;
    modelInfo << "../../resources/NNHLCR/back_up/ClusterMap.dat" << std::endl;

    long rcd = nn_hlcr::NNHLCR_JNIF::Initialize(modelInfo.str().c_str());
    ASSERT_TRUE(rcd != 0L);

    LstmLCRModel* mlObj = (LstmLCRModel*)rcd;

    auto metaData = R"(
        {
            "save_result": "success",
            "tensor_map_file": "../../resources/NNHLCR/data/AllData.jsonl",
            "tensor_map_index_file": "../../resources/NNHLCR/data/AllData.txt"
        }
    )"_json;

    std::string result = nn_hlcr::NNHLCR_JNIF::Training(mlObj, metaData.dump().c_str(), std::string("").c_str());
    ASSERT_EQ("", result);
}


TEST_F(TestNNHLCR, Evaluation_InvalidMaxLength)
{
    std::string hlcr_param_dat = std::string(FL_TEST_DATA_DIR) + this->case_name + ".HLCR_Param.dat";
    std::ofstream ofs(hlcr_param_dat);
    ofs << "2" << std::endl;
    ofs << "0.99" << std::endl;
    ofs << "0.01" << std::endl;
    ofs << "29" << std::endl;
    ofs << "18" << std::endl;

    std::stringstream modelInfo;
    modelInfo << "2" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster1.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster2.protobuf" << std::endl;
    modelInfo << hlcr_param_dat << std::endl;
    modelInfo << "../../resources/NNHLCR/back_up/ClusterMap.dat" << std::endl;

    long rcd = nn_hlcr::NNHLCR_JNIF::Initialize(modelInfo.str().c_str());
    ASSERT_TRUE(rcd != 0L);

    LstmLCRModel* mlObj = (LstmLCRModel*)rcd;

    auto metaData = R"(
        {
            "save_result": "success",
            "tensor_map_file": "../../resources/NNHLCR/data/AllData.jsonl",
            "tensor_map_index_file": "../../resources/NNHLCR/data/AllData.txt"
        }
    )"_json;

    std::stringstream evaluationInfo;
    evaluationInfo << "../../resources/NNHLCR/task_info/preprocess_params.dat" << std::endl;
    evaluationInfo << std::string(FL_TEST_DATA_DIR) + this->case_name + ".output_folder" << std::endl;

    std::string result = nn_hlcr::NNHLCR_JNIF::Evaluation(mlObj, metaData.dump().c_str(), evaluationInfo.str().c_str());
    ASSERT_EQ("", result);
}

TEST_F(TestNNHLCR, Evaluation_OutputFailed)
{
    std::stringstream modelInfo;
    modelInfo << "2" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster1.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster2.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/HLCR_Param.dat" << std::endl;
    modelInfo << "../../resources/NNHLCR/back_up/ClusterMap.dat" << std::endl;

    long rcd = nn_hlcr::NNHLCR_JNIF::Initialize(modelInfo.str().c_str());
    ASSERT_TRUE(rcd != 0L);

    LstmLCRModel* mlObj = (LstmLCRModel*)rcd;

    auto metaData = R"(
        {
            "save_result": "success",
            "tensor_map_file": "../../resources/NNHLCR/data/AllData.jsonl",
            "tensor_map_index_file": "../../resources/NNHLCR/data/AllData.txt"
        }
    )"_json;

    std::stringstream evaluationInfo;
    evaluationInfo << "../../resources/NNHLCR/task_info/preprocess_params.dat" << std::endl;
    evaluationInfo << std::string(FL_TEST_DATA_DIR) + "root.d" << std::endl;

    std::string result = nn_hlcr::NNHLCR_JNIF::Evaluation(mlObj, metaData.dump().c_str(), evaluationInfo.str().c_str());
    ASSERT_EQ("", result);
}

TEST_F(TestNNHLCR, Evaluation_InvalidEvaluationInfo)
{
    std::stringstream modelInfo;
    modelInfo << "2" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster1.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster2.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/HLCR_Param.dat" << std::endl;
    modelInfo << "../../resources/NNHLCR/back_up/ClusterMap.dat" << std::endl;

    long rcd = nn_hlcr::NNHLCR_JNIF::Initialize(modelInfo.str().c_str());
    ASSERT_TRUE(rcd != 0L);

    LstmLCRModel* mlObj = (LstmLCRModel*)rcd;

    auto metaData = R"(
        {
            "save_result": "success",
            "tensor_map_file": "../../resources/NNHLCR/data/AllData.jsonl",
            "tensor_map_index_file": "../../resources/NNHLCR/data/AllData.txt"
        }
    )"_json;

    std::stringstream evaluationInfo;
    evaluationInfo << "../../resources/NNHLCR/task_info/preprocess_params.dat" << std::endl;
    // evaluationInfo << std::string(FL_TEST_DATA_DIR) + "root.d" << std::endl;

    std::string result = nn_hlcr::NNHLCR_JNIF::Evaluation(mlObj, metaData.dump().c_str(), evaluationInfo.str().c_str());
    ASSERT_EQ("", result);
}

TEST_F(TestNNHLCR, Prediction_InvalidTensorMapJson)
{
    std::stringstream modelInfo;
    modelInfo << "2" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster1.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster2.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/HLCR_Param.dat" << std::endl;
    modelInfo << "../../resources/NNHLCR/back_up/ClusterMap.dat" << std::endl;

    long rcd = nn_hlcr::NNHLCR_JNIF::Initialize(modelInfo.str().c_str());
    ASSERT_TRUE(rcd != 0L);

    LstmLCRModel* mlObj = (LstmLCRModel*)rcd;

    float y_pred = nn_hlcr::NNHLCR_JNIF::Prediction(mlObj, "");
    ASSERT_EQ(y_pred, -FLT_MAX);
}

TEST_F(TestNNHLCR, Prediction_ValidTensorMapJson)
{
    std::stringstream modelInfo;
    modelInfo << "2" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster1.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster2.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/HLCR_Param.dat" << std::endl;
    modelInfo << "../../resources/NNHLCR/back_up/ClusterMap.dat" << std::endl;

    long rcd = nn_hlcr::NNHLCR_JNIF::Initialize(modelInfo.str().c_str());
    ASSERT_TRUE(rcd != 0L);

    LstmLCRModel* mlObj = (LstmLCRModel*)rcd;

    auto tensorMap = R"(
        {
            "num_of_features": {
                "shape": [1],
                "value": [13]
            },
            "group_label": {
                "shape": [1],
                "value": ["2"]
            },
            "sequence_data": {
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

    float y_pred = nn_hlcr::NNHLCR_JNIF::Prediction(mlObj, tensorMap.dump().c_str());
    ASSERT_FLOAT_EQ(0.17291486, y_pred);
}

TEST_F(TestNNHLCR, Prediction_NoNumOfFeatures)
{
    std::stringstream modelInfo;
    modelInfo << "2" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster1.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster2.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/HLCR_Param.dat" << std::endl;
    modelInfo << "../../resources/NNHLCR/back_up/ClusterMap.dat" << std::endl;

    long rcd = nn_hlcr::NNHLCR_JNIF::Initialize(modelInfo.str().c_str());
    ASSERT_TRUE(rcd != 0L);

    LstmLCRModel* mlObj = (LstmLCRModel*)rcd;

    auto tensorMap = R"(
        {
            "group_label": {
                "shape": [1],
                "value": ["2"]
            },
            "sequence_data": {
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

    float y_pred = nn_hlcr::NNHLCR_JNIF::Prediction(mlObj, tensorMap.dump().c_str());
    ASSERT_EQ(y_pred, -FLT_MAX);
}

TEST_F(TestNNHLCR, Prediction_NoSequenceData)
{
    std::stringstream modelInfo;
    modelInfo << "2" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster1.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster2.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/HLCR_Param.dat" << std::endl;
    modelInfo << "../../resources/NNHLCR/back_up/ClusterMap.dat" << std::endl;

    long rcd = nn_hlcr::NNHLCR_JNIF::Initialize(modelInfo.str().c_str());
    ASSERT_TRUE(rcd != 0L);

    LstmLCRModel* mlObj = (LstmLCRModel*)rcd;

    auto tensorMap = R"(
        {
            "num_of_features": {
                "shape": [1],
                "value": [13]
            },
            "group_label": {
                "shape": [1],
                "value": ["2"]
            }
        }
    )"_json;

    float y_pred = nn_hlcr::NNHLCR_JNIF::Prediction(mlObj, tensorMap.dump().c_str());
    ASSERT_EQ(y_pred, -FLT_MAX);
}

TEST_F(TestNNHLCR, Prediction_NoGroupLabel)
{
    std::stringstream modelInfo;
    modelInfo << "2" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster1.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster2.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/HLCR_Param.dat" << std::endl;
    modelInfo << "../../resources/NNHLCR/back_up/ClusterMap.dat" << std::endl;

    long rcd = nn_hlcr::NNHLCR_JNIF::Initialize(modelInfo.str().c_str());
    ASSERT_TRUE(rcd != 0L);

    LstmLCRModel* mlObj = (LstmLCRModel*)rcd;

    auto tensorMap = R"(
        {
            "num_of_features": {
                "shape": [1],
                "value": [13]
            },
            "sequence_data": {
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

    float y_pred = nn_hlcr::NNHLCR_JNIF::Prediction(mlObj, tensorMap.dump().c_str());
    ASSERT_EQ(y_pred, -FLT_MAX);
}

TEST_F(TestNNHLCR, Prediction_InvalidSequenceData)
{
    std::stringstream modelInfo;
    modelInfo << "2" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster1.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster2.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/HLCR_Param.dat" << std::endl;
    modelInfo << "../../resources/NNHLCR/back_up/ClusterMap.dat" << std::endl;

    long rcd = nn_hlcr::NNHLCR_JNIF::Initialize(modelInfo.str().c_str());
    ASSERT_TRUE(rcd != 0L);

    LstmLCRModel* mlObj = (LstmLCRModel*)rcd;

    auto tensorMap = R"(
        {
            "num_of_features": {
                "shape": [1],
                "value": [13]
            },
            "group_label": {
                "shape": [1],
                "value": ["2"]
            },
            "sequence_data": {
                "shape": [13],
                "value": [
                    0.00919959, 0.005900520, -71.3668, 101.9570, 0.1282080, 48.1664, 505.955,  4.12031,  2.46073, 1.0, 0.0,  3.0, 0.0
                ]
            }
        }
    )"_json;

    float y_pred = nn_hlcr::NNHLCR_JNIF::Prediction(mlObj, tensorMap.dump().c_str());
    ASSERT_EQ(y_pred, -FLT_MAX);
}

TEST_F(TestNNHLCR, UpdateInfo_EmptyUpdateInfo)
{
    std::string hlcr_param_dat = std::string(FL_TEST_DATA_DIR) + this->case_name + ".HLCR_Param.dat";
    std::ofstream ofs(hlcr_param_dat);
    ofs << "2" << std::endl;
    ofs << "0.99" << std::endl;
    ofs << "0.01" << std::endl;
    ofs << "29" << std::endl;
    ofs << "18" << std::endl;

    std::stringstream modelInfo;
    modelInfo << "2" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster1.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster2.protobuf" << std::endl;
    modelInfo << hlcr_param_dat << std::endl;
    modelInfo << "../../resources/NNHLCR/back_up/ClusterMap.dat" << std::endl;

    long rcd = nn_hlcr::NNHLCR_JNIF::Initialize(modelInfo.str().c_str());
    ASSERT_TRUE(rcd != 0L);

    LstmLCRModel* mlObj = (LstmLCRModel*)rcd;

    auto metaData = R"(
        {
            "save_result": "success",
            "tensor_map_file": "../../resources/NNHLCR/data/AllData.jsonl",
            "tensor_map_index_file": "../../resources/NNHLCR/data/AllData.txt"
        }
    )"_json;

    std::string result = nn_hlcr::NNHLCR_JNIF::UpdateInfo(mlObj, metaData.dump().c_str(), std::string("").c_str());
    ASSERT_EQ("", result);
}

TEST_F(TestNNHLCR, UpdateInfo_InvalidMaxLength)
{
    std::string hlcr_param_dat = std::string(FL_TEST_DATA_DIR) + this->case_name + ".HLCR_Param.dat";
    std::ofstream ofs(hlcr_param_dat);
    ofs << "2" << std::endl;
    ofs << "0.99" << std::endl;
    ofs << "0.01" << std::endl;
    ofs << "29" << std::endl;
    ofs << "18" << std::endl;

    std::stringstream modelInfo;
    modelInfo << "2" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/graph.nntxt" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster1.protobuf" << std::endl;
    modelInfo << "../../resources/NNHLCR/task_info/cluster2.protobuf" << std::endl;
    modelInfo << hlcr_param_dat << std::endl;
    modelInfo << "../../resources/NNHLCR/back_up/ClusterMap.dat" << std::endl;

    long rcd = nn_hlcr::NNHLCR_JNIF::Initialize(modelInfo.str().c_str());
    ASSERT_TRUE(rcd != 0L);

    LstmLCRModel* mlObj = (LstmLCRModel*)rcd;

    auto metaData = R"(
        {
            "save_result": "success",
            "tensor_map_file": "../../resources/NNHLCR/data/AllData.jsonl",
            "tensor_map_index_file": "../../resources/NNHLCR/data/AllData.txt"
        }
    )"_json;

    std::stringstream updateInfo;
    updateInfo << "../../resources/NNHLCR/task_info/Hyper_Param.dat" << std::endl;
    updateInfo << "../../resources/NNHLCR/task_info/preprocess_params.dat" << std::endl;
    updateInfo << std::string(FL_TEST_DATA_DIR) + this->case_name + ".output_folder" << std::endl;

    std::string result = nn_hlcr::NNHLCR_JNIF::UpdateInfo(mlObj, metaData.dump().c_str(), updateInfo.str().c_str());
    ASSERT_EQ("", result);
}
