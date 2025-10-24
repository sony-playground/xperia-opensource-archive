#include "LinearHLCR.h"
#include "FLException.h"
// https://arxiv.org/pdf/2206.10783.pdf

namespace linear_hlcr {

LinearHLCRTrainHyperParams::LinearHLCRTrainHyperParams(const double sigma) {
    this->_sigma = sigma;
}

double LinearHLCRTrainHyperParams::getSigma() const {
    return _sigma;
}

std::unique_ptr<LinearHLCRTrainHyperParams> LinearHLCRTrainHyperParams::fromJson(const json& json_obj) {
    try {
        std::string file_path = json_obj[LinearHLCRTrainHyperParams::KEY_OF_HYPER_PARAMS_FILE];
        std::ifstream ifs(file_path);
        json hyper_params_json;
        ifs >> hyper_params_json;

        double sigma = hyper_params_json[LinearHLCRTrainHyperParams::KEY_OF_SIGMA];
        if (sigma <= 0) THROW_FL_EXCEPTION(str_format("invalid sigma(%f)", sigma));
        return std::unique_ptr<LinearHLCRTrainHyperParams>(new LinearHLCRTrainHyperParams(sigma));
    }
    catch (json::exception& ex) {
        THROW_FL_EXCEPTION(str_format("Caught: json exception [%s]", ex.what()));
    }
}

LinearHLCRUpdateHyperParams::LinearHLCRUpdateHyperParams(const double sigma) {
    this->_sigma = sigma;
}

double LinearHLCRUpdateHyperParams::getSigma() const {
    return _sigma;
}

std::unique_ptr<LinearHLCRUpdateHyperParams> LinearHLCRUpdateHyperParams::fromJson(const json& json_obj) {
    try {
        std::string file_path = json_obj[LinearHLCRUpdateHyperParams::KEY_OF_HYPER_PARAMS_FILE];
        std::ifstream ifs(file_path);
        json hyper_params_json;
        ifs >> hyper_params_json;

        double sigma = hyper_params_json[LinearHLCRUpdateHyperParams::KEY_OF_SIGMA];
        if (sigma <= 0) THROW_FL_EXCEPTION(str_format("invalid sigma(%f)", sigma));
        return std::unique_ptr<LinearHLCRUpdateHyperParams>(new LinearHLCRUpdateHyperParams(sigma));
    }
    catch (json::exception& ex) {
        THROW_FL_EXCEPTION(str_format("Caught: json exception [%s]", ex.what()));
    }
}

LinearHLCRLocalModel::LinearHLCRLocalModel(
    const linear_hlcr::IntVector& local_count,
    const std::vector<std::shared_ptr<linear_hlcr::LinearRegressionLocalModel>>& linear_models) :
    _local_count(local_count), _local_linear_models(linear_models) 
    {
        this->_K = local_count.getDim();
}

std::shared_ptr<LinearHLCRLocalModel> LinearHLCRLocalModel::create(
        const linear_hlcr::IntVector& local_count, 
        const std::vector<std::shared_ptr<LinearRegressionLocalModel>>& linear_models) {
    if (local_count.getDim() != linear_models.size()) THROW_FL_EXCEPTION(str_format("mismatch sizes of local_count and linear_models. (local_count:%d liner_models:%d)", local_count.getDim(), linear_models.size()));
    return std::shared_ptr<LinearHLCRLocalModel>(new LinearHLCRLocalModel(local_count, linear_models));
}

std::shared_ptr<json> LinearHLCRLocalModel::save(const std::string& path_of_folder) const {
    json local_count_json;
    local_count_json[LinearHLCRLocalModel::KEY_OF_LOCAL_COUNT] = this->_local_count.getVector();
    std::string local_count_file_path = path_of_folder + "/" + LinearHLCRLocalModel::LOCAL_COUNT_FILE_NAME;
    std::ofstream lc_ofs(local_count_file_path);
    lc_ofs << local_count_json;

    std::shared_ptr<json> ret_json(new json());
    (*ret_json)[LinearHLCRLocalModel::KEY_OF_LOCAL_COUNT_FILE] = local_count_file_path;

    std::vector<std::string> model_file_paths(this->_K);
    for (int k = 0; k < this->_K; k++) {
        model_file_paths[k] = path_of_folder + "/" 
                + LinearHLCRLocalModel::LINEAR_MODEL_FILE_NAME_PREFIX + std::to_string(k) 
                + LinearHLCRLocalModel::LINEAR_MODEL_FILE_NAME_SUFFIX;
        std::ofstream mf_ofs(model_file_paths[k]);
        mf_ofs << *(this->_local_linear_models[k]->save());
    }

    (*ret_json)[LinearHLCRLocalModel::KEY_OF_LINEAR_MODEL_FILES] = model_file_paths;
    return ret_json;
}

LinearHLCRGlobalModel::LinearHLCRGlobalModel(
    const DoubleVector& double_vector, 
    const std::vector<std::shared_ptr<LinearRegressionGlobalModel>>& model_vector,
    double beta) :
    _global_weight(double_vector), _output_linear_models(model_vector) {
        this->_K = double_vector.getDim();
        this->_beta = beta;
}

int LinearHLCRGlobalModel::getK() const {
    return _K;
}

double LinearHLCRGlobalModel::getBeta() const {
    return _beta;
}

DoubleVector LinearHLCRGlobalModel::getGlobalWeight() const {
    return _global_weight;
}

std::shared_ptr<linear_hlcr::LinearRegressionGlobalModel> LinearHLCRGlobalModel::getLinearModel(int index) const {
    if (index < 0 || index >= this->_output_linear_models.size()) {
        THROW_FL_EXCEPTION(str_format("invalid index:%d (max:%d)", index, this->_output_linear_models.size()));
    }
    return this->_output_linear_models[index];
}

std::unique_ptr<linear_hlcr::LinearHLCRGlobalModel> LinearHLCRGlobalModel::fromJson(const json& json_obj) {
    try {
        std::string global_weight_file = json_obj[LinearHLCRGlobalModel::KEY_OF_GLOBAL_WEIGHT_FILE];
        std::vector<std::string> linear_model_files = json_obj[LinearHLCRGlobalModel::KEY_OF_LINEAR_MODEL_FILES];
        int K = linear_model_files.size();

        std::ifstream ifs_g(global_weight_file);
        json global_weight_json;
        ifs_g >> global_weight_json;
        DoubleVector global_weight(global_weight_json[LinearHLCRGlobalModel::KEY_OF_GLOBAL_WEIGHT]);
        double beta = global_weight_json[LinearHLCRGlobalModel::KEY_OF_BETA];

        if (K != global_weight.getDim()) THROW_FL_EXCEPTION(str_format("mismatch dimensions of K and global_weight. (K:%d global_weight.dim:%d)", K, global_weight.getDim()));
        if (beta <= 0) THROW_FL_EXCEPTION(str_format("invalid beta(%f)", beta));

        std::vector<std::shared_ptr<linear_hlcr::LinearRegressionGlobalModel>> model_vector(K);
        for (int k = 0; k < K; k++) {
            std::ifstream ifs_l(linear_model_files[k]);
            json linear_model_json;
            ifs_l >> linear_model_json;
            std::unique_ptr<LinearRegressionGlobalModel> linear_regression_global_model = 
                    LinearRegressionGlobalModel::fromJson(linear_model_json);
            model_vector[k] = std::move(linear_regression_global_model);
        }

        return std::unique_ptr<LinearHLCRGlobalModel>(new LinearHLCRGlobalModel(global_weight, model_vector, beta));
    }
    catch (json::exception& ex) {
        THROW_FL_EXCEPTION(str_format("Caught: json exception [%s]", ex.what()));
    }
}


LinearHLCRInternalModel::LinearHLCRInternalModel(int K, std::unordered_map<std::string, int>& cluster_map, int max_id) {
    this->_K = K;
    this->_cluster_map = cluster_map;
    this->_largest_cluster_ID = max_id;
}

int LinearHLCRInternalModel::getK() const {
    return this->_K;
}

int LinearHLCRInternalModel::getClusterID(const std::string& key) const {
    if (this->_cluster_map.find(key) == this->_cluster_map.end()) {
        return LinearHLCRInternalModel::GROUP_ID_NOT_FOUND;
    }
    return this->_cluster_map.at(key);
}

std::list<std::string> LinearHLCRInternalModel::getGroupList() const {
    std::list<std::string> group_list;
    for (auto p : this->_cluster_map) {
        group_list.emplace_back(p.first);
    }
    return group_list;
}


IntVector LinearHLCRInternalModel::calcLocalCount() const {
    std::vector<int> _previous_local_count(_K);
    std::list<std::string> group_list = this->getGroupList();
    for (auto name : group_list) {
        int id = this->getClusterID(name);
        _previous_local_count[id]++;
    }
    return IntVector(_previous_local_count);
}

std::shared_ptr<json> LinearHLCRInternalModel::save(const std::string& path_of_folder) const{
    json json_obj;
    json_obj[LinearHLCRInternalModel::KEY_OF_K] = this->_K;
    json_obj[LinearHLCRInternalModel::KEY_OF_CLUSTER_MAP] = _cluster_map;
    
    std::string cluster_map_path = path_of_folder + "/" + LinearHLCRInternalModel::CLUSTER_MAP_FILE_NAME;
    std::ofstream ofs(cluster_map_path);
    ofs << json_obj;

    std::shared_ptr<json> ret_json(new json());
    (*ret_json)[LinearHLCRInternalModel::KEY_OF_CLUSTER_MAP_FILE] = cluster_map_path;
    return ret_json;
}

std::unique_ptr<LinearHLCRInternalModel> LinearHLCRInternalModel::create(int K, std::unordered_map<std::string, int>& cluster_map) {
    std::vector<int> count(K);
    for (auto p : cluster_map) {
        if (p.second < 0 || p.second >= K) {
            THROW_FL_EXCEPTION(str_format("invalid p.second:%d (max:%d)", p.second, K-1));
        }
        int index = p.second;
        count[index]++;
    }
    auto maxIt = std::max_element(count.begin(), count.end());
    int max_id = std::distance(count.begin(), maxIt);
    return std::unique_ptr<LinearHLCRInternalModel>(new LinearHLCRInternalModel(K, cluster_map, max_id));
}

std::unique_ptr<LinearHLCRInternalModel> LinearHLCRInternalModel::createInitialInternalModel(const int K) {
    std::unordered_map<std::string, int> empty_map;
    return std::unique_ptr<LinearHLCRInternalModel>(new LinearHLCRInternalModel(K, empty_map, 0));
}


std::unique_ptr<linear_hlcr::LinearHLCRInternalModel> LinearHLCRInternalModel::fromJson(const json& json_obj) {
    try {
        std::string cluster_map_file = json_obj[LinearHLCRInternalModel::KEY_OF_CLUSTER_MAP_FILE];
        std::ifstream ifs(cluster_map_file);
        json cluster_map_json;
        ifs >> cluster_map_json;

        int K = cluster_map_json[LinearHLCRInternalModel::KEY_OF_K];
        std::unordered_map<std::string, int> cluster_map = cluster_map_json[LinearHLCRInternalModel::KEY_OF_CLUSTER_MAP];
        return LinearHLCRInternalModel::create(K, cluster_map);
    }
    catch (json::exception& ex) {
        THROW_FL_EXCEPTION(str_format("Caught: json exception [%s]", ex.what()));
    }
}


LinearHLCR::LinearHLCR(
            std::unique_ptr<LinearHLCRGlobalModel> global_model_ptr, 
            std::unique_ptr<LinearHLCRInternalModel> internal_model_ptr,
            int default_cluster_ID
        ) : _global_model(std::move(global_model_ptr)), _internal_model(std::move(internal_model_ptr)) 
{
    this->_default_cluster_ID = default_cluster_ID;
}

std::shared_ptr<LinearHLCRLocalModel> LinearHLCR::calcLocalModel(const fl::DataMetadata& train_data, const std::unordered_map<std::string, int>& cluster_map) {
    int K = this->_global_model->getK();
    int dim = this->_global_model->getLinearModel(0)->getW()->getDim()+1;

    SymmetricMatrix zero_matrix = SymmetricMatrix::create(std::vector<double>(dim * dim), dim);
    DoubleVector zero_vec = DoubleVector(std::vector<double>(dim));

    std::vector<std::shared_ptr<SymmetricMatrix>> Ds(K);
    std::vector<std::shared_ptr<DoubleVector>> cs(K);
    for (int k = 0; k < K; k++) {
        Ds[k] = std::shared_ptr<SymmetricMatrix>(new SymmetricMatrix(zero_matrix));
        cs[k] = std::shared_ptr<DoubleVector>(new DoubleVector(zero_vec));
    }

    fl::DataDeserializer data_desirializer = fl::DataDeserializer::createFor(train_data);
    int num_of_data = data_desirializer.getNumOfData();

    for (int n = 1; n <= num_of_data; n++) {
        std::shared_ptr<fl::TensorMap> record = data_desirializer.get(n);
        std::shared_ptr<fl::Tensor> x_ptr = record->get(LinearHLCR::KEY_OF_FEATURES);
        std::shared_ptr<fl::Tensor> y_ptr = record->get(LinearHLCR::KEY_OF_TARGET);
        std::shared_ptr<fl::Tensor> g_ptr = record->get(LinearHLCR::KEY_OF_GROUP_LABEL);
        if (!x_ptr || !y_ptr || !g_ptr) {
            THROW_FL_EXCEPTION(str_format("invalid tensor map. 'x' or 'y' or 'g' not included."));
        }
        std::string g = g_ptr->textValue();
        int clusterID = cluster_map.at(g);
        DoubleVector x = DoubleVector::fromTensor(*x_ptr);
        std::vector<double> x_vec = x.getVector();
        x_vec.push_back(1.0);
        DoubleVector x_ext = DoubleVector(x_vec);
        double y = y_ptr->doubleValue();

        // We need to improve this performance...
        Ds[clusterID] = std::shared_ptr<SymmetricMatrix>(
                new SymmetricMatrix(Ds[clusterID]->add(x_ext.selfOuterProduct()))
        );
        cs[clusterID] = std::shared_ptr<DoubleVector>(
                new DoubleVector(cs[clusterID]->add(x_ext.mul(y)))
        );
    }

    std::vector<int> local_count_vec(K);
    for (auto p : cluster_map) {
        local_count_vec[p.second]++;
    }

    std::vector<std::shared_ptr<linear_hlcr::LinearRegressionLocalModel>> regression_model_vec(K);
    for (int k = 0; k < K; k++) {
        regression_model_vec[k] = std::move(LinearRegressionLocalModel::create(*(Ds[k]), *(cs[k])));
    }

    return LinearHLCRLocalModel::create(IntVector(local_count_vec), regression_model_vec);
}

std::shared_ptr<fl::TensorMap> LinearHLCR::predict(const fl::TensorMap& tensor_map) {
    std::shared_ptr<fl::Tensor> x_ptr = tensor_map.get(LinearHLCR::KEY_OF_FEATURES);
    std::shared_ptr<fl::Tensor> g_ptr = tensor_map.get(LinearHLCR::KEY_OF_GROUP_LABEL);
    if (!x_ptr || !g_ptr) {
        THROW_FL_EXCEPTION(str_format("invalid tensor map. 'x' or 'g' not included."));
    }
    std::string g = g_ptr->textValue(); // it may throw json type error
 
    int clusterID = this->_internal_model->getClusterID(g);
    if (clusterID == LinearHLCRInternalModel::GROUP_ID_NOT_FOUND) {
        clusterID = this->_default_cluster_ID;
    }
    DoubleVector x = linear_hlcr::DoubleVector::fromTensor(*x_ptr); // it may throw exception

    double pred = x.dot(*(this->_global_model->getLinearModel(clusterID)->getW()))
            + this->_global_model->getLinearModel(clusterID)->getB(); // it may throw exception

    std::shared_ptr<fl::TensorMap> ret = std::shared_ptr<fl::TensorMap>(fl::TensorMap::newInstance());
    ret->set(
            LinearHLCR::KEY_OF_PREDICTION_RESULT, 
            std::shared_ptr<fl::Tensor>(fl::Tensor::newTensor(pred)));
    return ret;
}

std::pair<std::shared_ptr<LinearHLCRLocalModel>, std::shared_ptr<LinearHLCRInternalModel>> LinearHLCR::train( 
        const fl::DataMetadata& train_data, 
        const linear_hlcr::LinearHLCRTrainHyperParams& hyper_params) {

    std::unordered_map<std::string, DoubleVector> log_group_posteriour = 
            this->estimate_log_group_posteriour(train_data, this->_global_model->getBeta(), hyper_params.getSigma());
    std::unordered_map<std::string, int> new_cluster_map = this->sample_group_label(log_group_posteriour);

    std::shared_ptr<linear_hlcr::LinearHLCRLocalModel> local_model_ptr 
            = this->calcLocalModel(train_data, new_cluster_map);
    std::shared_ptr<LinearHLCRInternalModel> internal_model_ptr 
            = LinearHLCRInternalModel::create(this->_global_model->getK(), new_cluster_map);

    return std::make_pair(local_model_ptr, internal_model_ptr);
}


/**
 * @brief 
 * Algorithm1
 * Note that l.6 and l.7 is skipped. We considers it is a good approximation if there is enough data.
 * 
 * @param data 
 * @param hyper_params 
 * @return std::shared_ptr<LinearHLCRInternalModel> 
 */
std::unique_ptr<LinearHLCRInternalModel> LinearHLCR::updateInternalModel(
            const fl::DataMetadata& data, 
            const LinearHLCRUpdateHyperParams& hyper_params) {
    std::unordered_map<std::string, DoubleVector> log_group_posteriour = 
            this->estimate_log_group_posteriour(data, this->_global_model->getBeta(), hyper_params.getSigma());

    std::unordered_map<std::string, int> new_cluster_map = this->select_group_label(log_group_posteriour);
    return LinearHLCRInternalModel::create(this->_global_model->getK() ,new_cluster_map);
}

void LinearHLCR::setInternalModel(std::unique_ptr<linear_hlcr::LinearHLCRInternalModel> new_model) {
    if (new_model->getK() != this->_internal_model->getK()) THROW_FL_EXCEPTION(str_format("mismatch K of new_model and internal_model. (new_model:%d internal_model:%d)", new_model->getK(), this->_internal_model->getK()));
    this->_internal_model = std::move(new_model);
}

/**
 * @brief 
 * l.9 in Algorithm1 or Formula (1)
 * Note that we compute logarithm of the probabirity to save the accuracy.
 * 
 * @param data 
 * @param beta 
 * @param sigma 
 * @return std::pair<std::string, DoubleVector> 
 */
std::unordered_map<std::string, DoubleVector> LinearHLCR::estimate_log_group_posteriour(const fl::DataMetadata& data, const double beta, const double sigma) {
    DoubleVector log_numerator_group_prior = 
            this->estimate_log_numerator_group_prior(beta); // Prior doesn't depends on group because we ignore l.6 and l.7.
    std::unordered_map<std::string, DoubleVector> log_group_likelihood = 
            this->estimate_log_group_likelihood(data, sigma);

    std::unordered_map<std::string, DoubleVector> log_group_posteriour;

    for (auto p=log_group_likelihood.begin(); p!=log_group_likelihood.end(); p++) {
        std::string group_name = p->first;
        DoubleVector _log_group_likelihood = p->second;
        DoubleVector _log_numerator_group_posteriour = _log_group_likelihood.add(log_numerator_group_prior);
        double _log_denominator_group_posteriour = _log_numerator_group_posteriour.logsumexp();
        log_group_posteriour.emplace(group_name, _log_numerator_group_posteriour.add(-_log_denominator_group_posteriour));
    }

    return log_group_posteriour;
}


/**
 * @brief 
 * l.3 in Algorithm1 or Formula(2)
 * Note that we calcurate only numerator of probability to reduce computation.
 * 
 * @param beta 
 * @return DoubleVector 
 */
DoubleVector LinearHLCR::estimate_log_numerator_group_prior(const double beta) {
    DoubleVector global_weight = this->_global_model->getGlobalWeight();
    IntVector _previous_local_count = this->_internal_model->calcLocalCount();
    return DoubleVector::log(global_weight.mul(beta).add(_previous_local_count));
}

/**
 * @brief 
 * l.9 in Algorithm1 or Formula(3)
 * Note that we calcurate log of probability.
 * 
 * @param data 
 * @param sigma 
 * @return std::unordered_map<std::string, DoubleVector> 
 */
std::unordered_map<std::string, DoubleVector> LinearHLCR::estimate_log_group_likelihood(
        const fl::DataMetadata& data, const double sigma) {
    std::unordered_map<std::string, DoubleVector> log_group_likelihood;
    fl::DataDeserializer data_desirializer = fl::DataDeserializer::createFor(data);
    int num_of_data = data_desirializer.getNumOfData();

    for (int n = 1; n <= num_of_data; n++) {
        std::shared_ptr<fl::TensorMap> record = data_desirializer.get(n);
        DoubleVector log_record_likelihood = this->estimate_log_record_likelihood(*record, sigma);

        std::shared_ptr<fl::Tensor> g_ptr = record->get(LinearHLCR::KEY_OF_GROUP_LABEL);
        if (!g_ptr) {
            THROW_FL_EXCEPTION(str_format("invalid tensor map. 'g' is not included."));
        }
        std::string g = g_ptr->textValue();

        if (log_group_likelihood.find(g) == log_group_likelihood.end()) {
            log_group_likelihood.emplace(g, log_record_likelihood);
        } else {
            log_group_likelihood.emplace(g, log_group_likelihood.at(g).add(log_record_likelihood));
        }
    }

    return log_group_likelihood;
}


/**
 * @brief 
 * Formula(4)
 * Note that we calcurate log of probability.
 * 
 * @param record 
 * @param sigma 
 * @return DoubleVector 
 */
DoubleVector LinearHLCR::estimate_log_record_likelihood(const fl::TensorMap& record, const double sigma) {
    std::shared_ptr<fl::Tensor> x_ptr = record.get(LinearHLCR::KEY_OF_FEATURES);
    std::shared_ptr<fl::Tensor> y_ptr = record.get(LinearHLCR::KEY_OF_TARGET);
    if (!x_ptr || !y_ptr) {
        THROW_FL_EXCEPTION(str_format("invalid tensor map. 'x' or 'y' not included."));
    }

    DoubleVector x = DoubleVector::fromTensor(*x_ptr);
    std::vector<double> x_vec = x.getVector();
    x_vec.push_back(1.0);
    DoubleVector x_ext = DoubleVector(x_vec);
    double y = y_ptr->doubleValue();
    int K = this->_global_model->getK();

    std::vector<double> log_record_likelihood(K);

    for (int k = 0; k < K; k++) {
        double pred = x.dot(*(this->_global_model->getLinearModel(k)->getW())) 
                + this->_global_model->getLinearModel(k)->getB(); // it may throw exception
        SymmetricMatrix H = *(this->_global_model->getLinearModel(k)->getH());
        double scale = std::sqrt(sigma + x_ext.dot(x_ext.mul(H)));
        log_record_likelihood[k] = NormalDistribution::log_probability(pred, y, scale);
    }

    return DoubleVector(log_record_likelihood);
}


std::unordered_map<std::string, int> LinearHLCR::sample_group_label(const std::unordered_map<std::string, DoubleVector>& log_probability) {
    std::unordered_map<std::string, int> new_cluster_map;
    double thr = 1e-5;

    //if it is slow, we can calc this seed from time or date.
    std::random_device randomDevice;
    std::vector<uint32_t> randomSeedVector(10);
    std::generate(randomSeedVector.begin(), randomSeedVector.end(), std::ref(randomDevice));
    std::seed_seq randomSeed(randomSeedVector.begin(), randomSeedVector.end());
    std::mt19937 randomEngine(randomSeed);

    for (auto p : log_probability) {
        std::string name = p.first;
        DoubleVector probs = DoubleVector::exp(p.second);

        if (std::abs(probs.sum() - 1.0) > thr) THROW_FL_EXCEPTION(str_format("This DoubleVector is not a probability distribution. (Sum of probs : %f).", probs.sum()));

        std::vector<double> prob_vec = probs.getVector();
        for (int i = 1; i < prob_vec.size(); i++) prob_vec[i] += prob_vec[i-1];

        std::uniform_real_distribution<double> randomDoubleDistribution(0.0, 1.0);
        double x = randomDoubleDistribution(randomEngine);

        auto itr = std::lower_bound(prob_vec.begin(), prob_vec.end(), x);
        int clusterID = std::distance(prob_vec.begin(), itr);
        if (clusterID == this->_global_model->getK()) clusterID--; // Should we throw error?

        new_cluster_map.emplace(name, clusterID);
    }
    return new_cluster_map;
}

std::unordered_map<std::string, int> LinearHLCR::select_group_label(const std::unordered_map<std::string, DoubleVector>& log_probability) {
    std::unordered_map<std::string, int> new_cluster_map;

    for (auto p : log_probability) {
        std::string name = p.first;
        int clusterID = p.second.argmax();
        new_cluster_map.emplace(name, clusterID);
    }

    return new_cluster_map;
}

LinearHLCR* LinearHLCR::create(
            std::unique_ptr<LinearHLCRGlobalModel> global_model_ptr, 
            std::unique_ptr<LinearHLCRInternalModel> internal_model_ptr
        ) {
    if (global_model_ptr->getK() != internal_model_ptr->getK()) THROW_FL_EXCEPTION(str_format("mismatch K of global_model and internal_model. (global_model:%d internal_model:%d)", global_model_ptr->getK(), internal_model_ptr->getK()));
    IntVector local_count = internal_model_ptr->calcLocalCount();
    DoubleVector global_weight = global_model_ptr->getGlobalWeight();
    int default_cluster_id = global_weight.mul(global_model_ptr->getBeta()).add(local_count).argmax();
    return new LinearHLCR(std::move(global_model_ptr), std::move(internal_model_ptr), default_cluster_id);
}


std::shared_ptr<fl::TensorMap> LinearHLCR::calcLoss(const fl::DataMetadata& data) {
    double loss = 0;

    fl::DataDeserializer data_desirializer = fl::DataDeserializer::createFor(data);
    int num_of_data = data_desirializer.getNumOfData();

    for (int n = 1; n <= num_of_data; n++) {
        std::shared_ptr<fl::TensorMap> record = data_desirializer.get(n);
        std::shared_ptr<fl::Tensor> x_ptr = record->get(LinearHLCR::KEY_OF_FEATURES);
        std::shared_ptr<fl::Tensor> y_ptr = record->get(LinearHLCR::KEY_OF_TARGET);
        std::shared_ptr<fl::Tensor> g_ptr = record->get(LinearHLCR::KEY_OF_GROUP_LABEL);
        if (!x_ptr || !y_ptr || !g_ptr) {
            THROW_FL_EXCEPTION(str_format("invalid tensor map. 'x' or 'y' or 'g' not included."));
        }
        std::string g = g_ptr->textValue();
        int clusterID = this->_internal_model->getClusterID(g);
        if (clusterID == LinearHLCRInternalModel::GROUP_ID_NOT_FOUND) {
            clusterID = this->_default_cluster_ID;
        }
        DoubleVector x = DoubleVector::fromTensor(*x_ptr);
        double y = y_ptr->doubleValue();

        double pred = x.dot(*(this->_global_model->getLinearModel(clusterID)->getW())) 
                + this->_global_model->getLinearModel(clusterID)->getB();

        loss += std::pow(pred - y, 2);
    }

    std::shared_ptr<fl::TensorMap> tensor_map 
            = std::shared_ptr<fl::TensorMap>(fl::TensorMap::newInstance());
    tensor_map->set(LinearHLCR::KEY_OF_DATA_SIZE, std::shared_ptr<fl::Tensor>(fl::Tensor::newTensor(num_of_data)));
    tensor_map->set(LinearHLCR::KEY_OF_LOSS, std::shared_ptr<fl::Tensor>(fl::Tensor::newTensor(loss)));
    return tensor_map;
}

const std::string LinearHLCR::KEY_OF_FEATURES = "x";
const std::string LinearHLCR::KEY_OF_TARGET = "y";
const std::string LinearHLCR::KEY_OF_GROUP_LABEL = "g";
const std::string LinearHLCR::KEY_OF_PREDICTION_RESULT = "y_pred";
const std::string LinearHLCR::KEY_OF_DATA_SIZE = "num_of_data";
const std::string LinearHLCR::KEY_OF_LOSS = "loss";

const std::string LinearHLCRTrainHyperParams::KEY_OF_HYPER_PARAMS_FILE = "hyperParams";
const std::string LinearHLCRTrainHyperParams::KEY_OF_SIGMA = "sigma";

const std::string LinearHLCRUpdateHyperParams::KEY_OF_HYPER_PARAMS_FILE = "hyperParams";
const std::string LinearHLCRUpdateHyperParams::KEY_OF_SIGMA = "sigma";

const std::string LinearHLCRLocalModel::KEY_OF_LOCAL_COUNT_FILE = "localCount";
const std::string LinearHLCRLocalModel::KEY_OF_LINEAR_MODEL_FILES = "linearModels";
const std::string LinearHLCRLocalModel::KEY_OF_LOCAL_COUNT = "local_count";
const std::string LinearHLCRLocalModel::LOCAL_COUNT_FILE_NAME = "local_count.json";
const std::string LinearHLCRLocalModel::LINEAR_MODEL_FILE_NAME_PREFIX = "linear_model";
const std::string LinearHLCRLocalModel::LINEAR_MODEL_FILE_NAME_SUFFIX = ".json";

const std::string LinearHLCRGlobalModel::KEY_OF_GLOBAL_WEIGHT_FILE = "globalWeight";
const std::string LinearHLCRGlobalModel::KEY_OF_LINEAR_MODEL_FILES = "linearModels";
const std::string LinearHLCRGlobalModel::KEY_OF_GLOBAL_WEIGHT = "global_weight";
const std::string LinearHLCRGlobalModel::KEY_OF_BETA = "beta";

const std::string LinearHLCRInternalModel::KEY_OF_CLUSTER_MAP_FILE = "clusterMap";
const std::string LinearHLCRInternalModel::KEY_OF_K = "K";
const std::string LinearHLCRInternalModel::KEY_OF_CLUSTER_MAP = "cluster_map";
const std::string LinearHLCRInternalModel::CLUSTER_MAP_FILE_NAME = "cluster_map.json";
const int LinearHLCRInternalModel::GROUP_ID_NOT_FOUND = -1;

}
