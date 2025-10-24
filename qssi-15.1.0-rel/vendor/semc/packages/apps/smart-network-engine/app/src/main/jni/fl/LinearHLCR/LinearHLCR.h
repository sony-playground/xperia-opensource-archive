#ifndef LINEARHLCR_H_
#define LINEARHLCR_H_

#include "LinearRegression.h"
#include "NormalDistribution.h"
#include "tensor/tensor_map.h"
#include "tensor/data_metadata.h"
#include "tensor/data_deserializer.h"

#include <nlohmann/json.hpp>
#include <memory>
#include <unordered_map>
#include <list>
#include <vector>
#include <utility>
#include <random>

using json = nlohmann::json;

namespace linear_hlcr {

class LinearHLCRTrainHyperParams {
    private:
        double _sigma;
        LinearHLCRTrainHyperParams(const double);

    public:
        double getSigma() const;

    public:
        static std::unique_ptr<linear_hlcr::LinearHLCRTrainHyperParams> fromJson(const json&);
        static const std::string KEY_OF_HYPER_PARAMS_FILE;   
        static const std::string KEY_OF_SIGMA;
};

class LinearHLCRUpdateHyperParams {
    private:
        double _sigma;
        LinearHLCRUpdateHyperParams(const double);

    public:
        double getSigma() const;

    public:
        static std::unique_ptr<linear_hlcr::LinearHLCRUpdateHyperParams> fromJson(const json&); 
        static const std::string KEY_OF_HYPER_PARAMS_FILE;   
        static const std::string KEY_OF_SIGMA;
};

class LinearHLCRLocalModel {
    private:
        int _K;
        linear_hlcr::IntVector _local_count;
        std::vector<std::shared_ptr<linear_hlcr::LinearRegressionLocalModel>> _local_linear_models;
        LinearHLCRLocalModel(
            const linear_hlcr::IntVector&,
            const std::vector<std::shared_ptr<linear_hlcr::LinearRegressionLocalModel>>&
        );

    public:
        std::shared_ptr<json> save(const std::string&) const;

    public:
        static std::shared_ptr<linear_hlcr::LinearHLCRLocalModel> create(
            const linear_hlcr::IntVector&,
            const std::vector<std::shared_ptr<linear_hlcr::LinearRegressionLocalModel>>&
        );
        static const std::string KEY_OF_LOCAL_COUNT_FILE;
        static const std::string KEY_OF_LINEAR_MODEL_FILES;
        static const std::string KEY_OF_LOCAL_COUNT;
        static const std::string LOCAL_COUNT_FILE_NAME;
        static const std::string LINEAR_MODEL_FILE_NAME_PREFIX;
        static const std::string LINEAR_MODEL_FILE_NAME_SUFFIX;       
};

class LinearHLCRGlobalModel {
    private:
        int _K;
        linear_hlcr::DoubleVector _global_weight;
        double _beta;
        std::vector<std::shared_ptr<linear_hlcr::LinearRegressionGlobalModel>> _output_linear_models;
        LinearHLCRGlobalModel(const DoubleVector&, const std::vector<std::shared_ptr<linear_hlcr::LinearRegressionGlobalModel>>&, double);
    public:
        int getK() const;
        double getBeta() const;
        linear_hlcr::DoubleVector getGlobalWeight() const;
        std::shared_ptr<linear_hlcr::LinearRegressionGlobalModel> getLinearModel(int) const;

    public:
        static std::unique_ptr<linear_hlcr::LinearHLCRGlobalModel> fromJson(const json&);
        static const std::string KEY_OF_GLOBAL_WEIGHT_FILE;
        static const std::string KEY_OF_LINEAR_MODEL_FILES;
        static const std::string KEY_OF_GLOBAL_WEIGHT;
        static const std::string KEY_OF_BETA;
};

class LinearHLCRInternalModel {
    private:
        int _K;
        std::unordered_map<std::string, int> _cluster_map;
        int _largest_cluster_ID; // We might not need to use this.
        LinearHLCRInternalModel(int, std::unordered_map<std::string, int>&, int);
    public:
        int getK() const;
        int getClusterID(const std::string&) const;
        std::list<std::string> getGroupList() const;
        IntVector calcLocalCount() const;
        std::shared_ptr<json> save(const std::string& /*path of folder*/) const;
    public:
        static std::unique_ptr<linear_hlcr::LinearHLCRInternalModel> create(int, std::unordered_map<std::string, int>&);
        static std::unique_ptr<linear_hlcr::LinearHLCRInternalModel> createInitialInternalModel(const int);
        static std::unique_ptr<linear_hlcr::LinearHLCRInternalModel> fromJson(const json&); 
        static const std::string KEY_OF_CLUSTER_MAP_FILE;
        static const std::string KEY_OF_K;
        static const std::string KEY_OF_CLUSTER_MAP;
        static const std::string CLUSTER_MAP_FILE_NAME;
        static const int GROUP_ID_NOT_FOUND;
};

class LinearHLCR {
    private:
        std::unique_ptr<linear_hlcr::LinearHLCRGlobalModel> _global_model;
        std::unique_ptr<linear_hlcr::LinearHLCRInternalModel> _internal_model;
        int _default_cluster_ID;
        LinearHLCR(      
            std::unique_ptr<LinearHLCRGlobalModel>, 
            std::unique_ptr<LinearHLCRInternalModel>,
            int);
        std::shared_ptr<linear_hlcr::LinearHLCRLocalModel> calcLocalModel(const fl::DataMetadata&, const std::unordered_map<std::string, int>&);
        std::unordered_map<std::string, DoubleVector> estimate_log_group_posteriour(const fl::DataMetadata&, const double, const double);
        DoubleVector estimate_log_numerator_group_prior(const double);
        std::unordered_map<std::string, DoubleVector> estimate_log_group_likelihood(const fl::DataMetadata&, const double);
        DoubleVector estimate_log_record_likelihood(const fl::TensorMap&, const double);
        std::unordered_map<std::string, int> sample_group_label(const std::unordered_map<std::string, DoubleVector>&);
        std::unordered_map<std::string, int> select_group_label(const std::unordered_map<std::string, DoubleVector>&);

    public:
        std::shared_ptr<fl::TensorMap> predict(const fl::TensorMap&);
        /*
        std::shared_ptr<fl::DataMetadata> predict(const fl::DataMetadata&);
        */
        std::pair<std::shared_ptr<linear_hlcr::LinearHLCRLocalModel>, std::shared_ptr<linear_hlcr::LinearHLCRInternalModel>> train(
            const fl::DataMetadata&, 
            const linear_hlcr::LinearHLCRTrainHyperParams&
        );
        std::unique_ptr<linear_hlcr::LinearHLCRInternalModel> updateInternalModel(
            const fl::DataMetadata&, 
            const linear_hlcr::LinearHLCRUpdateHyperParams&
        );
        void setInternalModel(std::unique_ptr<linear_hlcr::LinearHLCRInternalModel>);
        std::shared_ptr<fl::TensorMap> calcLoss(const fl::DataMetadata&);
    public:
        static const std::string KEY_OF_FEATURES;
        static const std::string KEY_OF_TARGET;
        static const std::string KEY_OF_GROUP_LABEL;
        static const std::string KEY_OF_PREDICTION_RESULT;
        static const std::string KEY_OF_DATA_SIZE;
        static const std::string KEY_OF_LOSS;
        static linear_hlcr::LinearHLCR* create(
            std::unique_ptr<LinearHLCRGlobalModel>, 
            std::unique_ptr<LinearHLCRInternalModel>
        );
};

} // namespace linear_hlcr
#endif  // LINEARHLCR_H_
