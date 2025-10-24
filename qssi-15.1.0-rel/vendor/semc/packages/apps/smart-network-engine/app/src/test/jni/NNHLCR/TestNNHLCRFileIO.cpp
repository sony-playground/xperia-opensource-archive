#include <gtest/gtest.h>
#include "NNHLCR/NNHLCR_file_IO.h"
#include "tensor/data_serializer.h"
#include "tensor/data_metadata.h"
#include "tensor/tensor.h"
#include "tensor/tensor_map.h"
#include "tensor/tensor_shape.h"

#define FL_TEST_DATA_DIR   "Testing/Temporary/"

class TestNNHLCRFileIO: public ::testing::Test
{
public:
    std::string jsonl_file;
    std::string index_file;

    std::string case_name;
    std::string test_suite_name;
    std::string name;

private:
    void cleanup() {
        system((std::string("/usr/bin/rm -f ") + std::string(FL_TEST_DATA_DIR) + this->case_name + std::string(".*")).c_str());
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

TEST_F(TestNNHLCRFileIO, newConstructorInputs)
{
  ConstructorInputs ci = ConstructorInputs(string("hoge"));
  EXPECT_EQ(0, ci.isValid);
}

TEST_F(TestNNHLCRFileIO, testDeploy_NNHLCR_NoReadPermitToCalibrateParamsFile)
{
    auto tensorMapJson = R"(
        {
            "num_of_features": {
                "shape": [1],
                "value": [13]
            },
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

    std::shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::fromJsonString(tensorMapJson.dump()));

    fl::DataSerializer serializer = fl::DataSerializer::createFor(this->jsonl_file, this->index_file);
    serializer.save(*(tensor_map.get()));
    fl::DataMetadata meta = serializer.getMetadata();

    std::stringstream ss;
    ss << std::string(FL_TEST_DATA_DIR) + this->case_name + ".preprocess_params_file" << std::endl;
    ss << std::string(FL_TEST_DATA_DIR) + this->case_name + ".update_param_file" << std::endl;
    ss << std::string(FL_TEST_DATA_DIR) + this->case_name + ".output_folder" << std::endl;
    string updateClusterMapInfo = ss.str();

    std::cout << updateClusterMapInfo << std::endl;

    UpdateClusterMapInputs ucmi = UpdateClusterMapInputs(meta, updateClusterMapInfo);
    ASSERT_FALSE(ucmi.isValid);
}
