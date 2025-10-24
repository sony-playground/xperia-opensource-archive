#ifndef NNHLCR_FILE_IO_H_
#define NNHLCR_FILE_IO_H_
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

#include "tensor/data_metadata.h"
#include "tensor/data_deserializer.h"

using namespace std;

class ConstructorInputs {
    const int MIN_K = 1;
    const int MAX_K = 100;
    public:
        ConstructorInputs(string modelInfo);
        ~ConstructorInputs();
        int K = 0;
        int max_length = 0;
        int num_of_normalized_features = 0;
        vector<string> nntxt_files;
        vector<string> protobuf_files;
        vector<float> global_weights;
        unordered_map<string, int> cluster_map;
        bool isValid = false;
    private:
        bool loadHLCRParamsFile(string filename);
        bool loadClusterMapFile(string filename);
};

// class PredictInputs {
//     const int MAX_NUM_OF_FEATURES = 100;
//     public:
//         PredictInputs(string predictInfo);
//         ~PredictInputs();
//         int num_of_features = 0;
//         vector<float> averages;
//         vector<float> variances;
//         int min_data_count = 0;
//         bool isValid = false;
//     private:
//         bool loadPreprocessParamsFile(string filename);
// };

class UpdateClusterMapInputs {
    const string CLUSTER_MAP_FILE_NAME = "ClusterMap.dat";
    const int MAX_NUM_OF_DATA = 10000;
    const int MAX_NUM_OF_FEATURES = 100;
    const int NUM_OF_FEATURES_FOR_SNE = 13;
    const int MIN_LENGTH = 1;
    const int MAX_LENGTH = 30;
    public:
        UpdateClusterMapInputs(fl::DataMetadata metaData, string updateClusterMapInfo);
        ~UpdateClusterMapInputs();
        shared_ptr<float> x;
        shared_ptr<float> y;
        shared_ptr<string> groupLabel;
        int num_of_data = 0;
        shared_ptr<int> lengths;
        int num_of_features = 0;
        float alpha = 0.0;
        float beta = 0.0;
        float delta = 0.0;
        float sigma = 0.0;
        string output_file = "";
        bool isValid = false;
        int getMaxLength();
    private:
        bool loadDataFile(fl::DataMetadata metaData);
        // bool loadPreprocessParamsFile(string filename);
        bool loadUpdateClusterMapParamsFile(string filename);
};

class UpdateClusterMapOutputs {
    public:
        bool saveClusterMap(string file_name, unordered_map<string, int> cluster_map);
};

class TrainInputs {
    const int MAX_NUM_OF_DATA = 10000;
    const int MAX_NUM_OF_FEATURES = 100;
    const int NUM_OF_FEATURES_FOR_SNE = 13;
    const int MIN_LENGTH = 1;
    const int MAX_LENGTH = 30;
    public:
        const string CLUSTER_MAP_FILE_NAME = "ClusterMap.dat";
        const string NN_FILE_PREFIX = "cluster";
        const string NN_FILE_EXTENSION = ".protobuf";
        const string LCR_FILE_NAME = "HLCR_Param.dat";
        const string VALIDATION_FILE_NAME = "validation_metrix.dat";
        TrainInputs(fl::DataMetadata metaData, string trainInfo, int K);
        ~TrainInputs();
        shared_ptr<float> x;
        shared_ptr<float> y;
        shared_ptr<string> groupLabel;
        int num_of_data = 0;
        shared_ptr<int> lengths;
        int num_of_features = 0;
        float alpha = 0.0;
        float beta = 0.0;
        float delta = 0.0;
        float sigma = 0.0;
        float learning_rate = 0.0;
        int batch_size = 0;
        int num_of_epoch = 0;
        vector<string> output_nn_files;
        string output_lcr_file = "";
        string output_cluster_map_file = "";
        string output_valid_file = "";
        bool isValid = false;
        int getMaxLength() {return MAX_LENGTH;};
    private:
        bool loadDataFile(fl::DataMetadata metaData);
        // bool loadPreprocessParamsFile(string filename);
        bool loadTrainParamsFile(string filename);
};

class TrainOutputs {
    public:
        bool saveValidationResults(string file_name, int num_of_data, float loss);
};

class EvaluationInputs {
    const int MAX_NUM_OF_DATA = 10000;
    const int MAX_NUM_OF_FEATURES = 100;
    const int NUM_OF_FEATURES_FOR_SNE = 13;
    const int MIN_LENGTH = 1;
    const int MAX_LENGTH = 30;
    public:
        const string EVALUATION_RESULT_FILE_NAME = "evaluation_result.dat";
        EvaluationInputs(fl::DataMetadata metaData, string trainInfo);
        ~EvaluationInputs();
        string output_eval_file = "";
        shared_ptr<float> x;
        shared_ptr<float> y;
        shared_ptr<string> groupLabel;
        int num_of_data = 0;
        shared_ptr<int> lengths;
        int num_of_features = 0;
        bool isValid = false;
        int getMaxLength() {return MAX_LENGTH;};
    private:
        bool loadDataFile(fl::DataMetadata metaData);
        // bool loadPreprocessParamsFile(string filename);
};

class EvaluationOutputs {
    public:
        bool saveEvaluationResults(string file_name, int num_of_data , float *y, float *y_pred);
};
#endif  // NNHLCR_FILE_IO_H_
