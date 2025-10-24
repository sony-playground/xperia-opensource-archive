#include "NNHLCR/NNHLCR_file_IO.h"
#include <fstream>
#include <sstream>
#include <istream>
#include <random>

//#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

using namespace std;

ConstructorInputs::ConstructorInputs(string modelInfo) {
    string hlcr_params_file;
    string cluster_map_file;
    stringstream ss(modelInfo);
    ss >> this->K;
#ifdef DEBUG
    cout << "K = " << K << endl;
#endif
    if (this->K < ConstructorInputs::MIN_K || this->K > ConstructorInputs::MAX_K) return;
    this->nntxt_files.resize(this->K);
    this->protobuf_files.resize(this->K);
    for (int i=0;i<this->K;i++) {
        ss >> this->nntxt_files[i];
#ifdef DEBUG
        cout << "nntxt_files[" << i << "] = " << nntxt_files[i] << endl;
#endif
    }
    for (int i=0;i<this->K;i++) {
        ss >> this->protobuf_files[i];
#ifdef DEBUG
        cout << "protobuf_files[" << i << "] = " << protobuf_files[i] << endl;
#endif
    }
    ss >> hlcr_params_file;
#ifdef DEBUG
    cout << "hlcr_params_file = " << hlcr_params_file << endl;
#endif
    ss >> cluster_map_file;
#ifdef DEBUG
    cout << "cluster_map_file = " << cluster_map_file << endl;
#endif
    if (!loadHLCRParamsFile(hlcr_params_file)) return;
    if (!loadClusterMapFile(cluster_map_file)) return;
    this->isValid = true;
}

ConstructorInputs::~ConstructorInputs() {}

bool ConstructorInputs::loadHLCRParamsFile(string file_name) {
    ifstream ifs(file_name);
    if (!ifs) return false;
    int K;
    ifs >> K;
    if (!ifs) return false;
    if (K != this->K) return false;
    this->global_weights.resize(this->K);
    for (int i=0;i<this->K;i++) {
        ifs >> this->global_weights[i];
        if (!ifs) return false;
#ifdef DEBUG
        cout << "global_weights[" << i << "] = " << global_weights[i] << endl;
#endif
        if (global_weights[i] < 0) return false;
    }
    ifs >> this->max_length;
    if (!ifs) return false;
#ifdef DEBUG
    cout << "max_length = " << max_length << endl;
#endif
    if (this->max_length < 0) return false;
    ifs >> this->num_of_normalized_features;
    if (!ifs) return false;
#ifdef DEBUG
    cout << "num_of_normalized_features = " << num_of_normalized_features << endl;
#endif
    if (this->num_of_normalized_features < 0) return false;
    return true;
}

bool ConstructorInputs::loadClusterMapFile(string file_name) {
    if (file_name.length() == 0) return true;
    ifstream ifs(file_name);
    if (!ifs) return false;
    int M;
    ifs >> M;
    if (!ifs) return false;
    string groupID;
    int clusterID;
#ifdef DEBUG
    cout << "Size of cluster map = " << M << endl;
#endif
    for (int i=0;i<M;i++) {
        ifs >> groupID >> clusterID;
        if (!ifs) return false;
        this->cluster_map[groupID] = clusterID;
#ifdef DEBUG
    cout << groupID << " : " << clusterID << endl;
#endif
    }
    return true;
}


// PredictInputs::PredictInputs(string predictInfo) {
//     string preprocess_params_file;
//     stringstream ss(predictInfo);
//     ss >> preprocess_params_file;
// #ifdef DEBUG
//     cout << "preprocess_params_file = " << preprocess_params_file << endl;
// #endif
//     //if (!loadPreprocessParamsFile(preprocess_params_file)) return;
//     isValid = true;
// }
//
// PredictInputs::~PredictInputs() {}
//
// bool PredictInputs::loadPreprocessParamsFile(string file_name) {
//     ifstream ifs(file_name);
//     if (!ifs) return false;
//     ifs >> this->num_of_features;
//     if (!ifs) return false;
// #ifdef DEBUG
//     cout << "num_of_features = " << this->num_of_features << endl;
// #endif
//     if (this->num_of_features <= 0 || this->num_of_features > this->MAX_NUM_OF_FEATURES) return false;
//     this->averages.resize(this->num_of_features);
//     this->variances.resize(this->num_of_features);
//     for (int i=0;i<this->num_of_features;i++) {
//         ifs >> this->averages[i] >> this->variances[i];
//         if (!ifs) return false;
// #ifdef DEBUG
//         cout << i << ": ave = " << this->averages[i] << " , var = " << this->variances[i] << endl;
// #endif
//         if (this->variances[i] < 0) return false;
//     }
//     ifs >> this->min_data_count;
//     if (!ifs) return false;
// #ifdef DEBUG
//     cout << "min_data_count = " << this->min_data_count << endl;
// #endif
//     if (this->min_data_count < 0) return false;
//     return true;
// }

UpdateClusterMapInputs::UpdateClusterMapInputs(fl::DataMetadata metaData,string updateClusterMapInfo) {
    string preprocess_params_file;
    string update_param_file;
    string output_folder;
    stringstream ss(updateClusterMapInfo);
    ss >> preprocess_params_file;
    ss >> update_param_file;
    ss >> output_folder;
    if (!ss) {
#ifdef DEBUG
        cout << "invalid updateClusterMapInfo. [" + updateClusterMapInfo + "]" << endl;
#endif
        return;
    }
#ifdef DEBUG
    cout << "preprocess_params_file = " << preprocess_params_file << endl;
    cout << "update_param_file = " << update_param_file << endl;
    cout << "output_folder = " << output_folder << endl;
#endif
    if (!loadDataFile(metaData)) return;
    // if (!loadPreprocessParamsFile(preprocess_params_file)) return;
    if (!loadUpdateClusterMapParamsFile(update_param_file)) return;
    output_file = output_folder + "/" + CLUSTER_MAP_FILE_NAME;
    isValid = true;
}

UpdateClusterMapInputs::~UpdateClusterMapInputs() {}

bool UpdateClusterMapInputs::loadDataFile(fl::DataMetadata metaData) {
    fl::DataDeserializer dataDeserializer = fl::DataDeserializer::createFor(metaData);
    num_of_data = dataDeserializer.getNumOfData();
    if (num_of_data == 0) {
#ifdef DEBUG
        cout << num_of_data << " is zero. no data." << endl;
#endif
        return true;
    }
    if (num_of_data < 0 || num_of_data > MAX_NUM_OF_DATA) {
#ifdef DEBUG
        cout << num_of_data << " is invalid num_of_data." << endl;
#endif
        return false;
    }
    std::shared_ptr<fl::Tensor> ts_num_of_features = dataDeserializer.get(1)->get("num_of_features");
    if (!ts_num_of_features) {
#ifdef DEBUG
        cout << "no num_of_features." << endl;
#endif
        return false;
    }
    num_of_features = ts_num_of_features->intValue();
    if (num_of_data > 0 && num_of_features != NUM_OF_FEATURES_FOR_SNE) { // tentative
#ifdef DEBUG
        cout << num_of_features << " is invalid num_of_features" << endl;
#endif
        return false;
    }
    int x_size = num_of_data * num_of_features * MAX_LENGTH;
    if (x_size < 0) {
#ifdef DEBUG
        cout << "Integer overflow" << endl;
#endif
        return false;
    }
    x = shared_ptr<float>(new float[x_size], default_delete<float[]>());
    y = shared_ptr<float>(new float[num_of_data], default_delete<float[]>());
    groupLabel = shared_ptr<string>(new string[num_of_data], default_delete<string[]>());
    lengths = shared_ptr<int>(new int[num_of_data], default_delete<int[]>());

    vector<int> v(num_of_data);
    iota(v.begin(), v.end(), 1);
    random_device seed_gen;
    mt19937 engine(seed_gen());
    shuffle(v.begin(), v.end(), engine);

    bool flag = true;
    for (int i = 0;i < num_of_data;i++) {
        shared_ptr<fl::TensorMap> tensorMap = dataDeserializer.get(v[i]);
        std::shared_ptr<fl::Tensor> ts_f = tensorMap->get("num_of_features");
        if (!ts_f) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << "no num_of_features." << endl;
#endif
            break;
        }
        num_of_features = ts_f->intValue();
        std::shared_ptr<fl::Tensor> ts_g = tensorMap->get("group_label");
        if (!ts_g) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << "no group_label." << endl;
#endif
            break;
        }
        groupLabel.get()[i] = ts_g->textValue();
        std::shared_ptr<fl::Tensor> ts_y = tensorMap->get("y");
        if (!ts_y) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << "no y." << endl;
#endif
            break;
        }
        y.get()[i] = ts_y->floatValue();
        std::shared_ptr<fl::Tensor> ts_x = tensorMap->get("x");
        if (!ts_x) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << "no x." << endl;
#endif
            break;
        }
        lengths.get()[i] = ts_x->size() / num_of_features;
        if (y.get()[i] != 0 && y.get()[i] != 1) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << y.get()[i] << " is invalid y." << endl;
#endif
            break;
        }
        if (lengths.get()[i] < MIN_LENGTH || lengths.get()[i] > MAX_LENGTH) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << lengths.get()[i] << " is invalid length." << endl;
#endif
            break;
        }
        vector<float> tensor_x = ts_x->floatVector();
        for (int t = 0;t < lengths.get()[i]; t++) {
            for (int f = 0;f < num_of_features; f++) {
                x.get()[i * (num_of_features * MAX_LENGTH) + t * num_of_features + f] = tensor_x.data()[(t * num_of_features) + f];
#ifdef DEBUG
                cout << x.get()[i * (num_of_features * MAX_LENGTH) + t * num_of_features + f] << " ";
#endif
            }
#ifdef DEBUG
            cout << endl;
#endif
        }
        lengths.get()[i]--;
    }
    return flag;
}

bool UpdateClusterMapInputs::loadUpdateClusterMapParamsFile(string update_param_file) {
    float _alpha, _beta, _delta, _sigma;
    ifstream ifs(update_param_file);
    if (!ifs) {
#ifdef DEBUG
        cout << update_param_file << " is not readable." << endl;
#endif
        return false;
    }
    ifs >> _alpha;
    ifs >> _beta;
    ifs >> _delta;
    ifs >> _sigma;
    // TODO : verification
    alpha = _alpha;
    beta = _beta;
    delta = _delta;
    sigma = _sigma;
    if (!ifs) return false;
    return true;
}

int UpdateClusterMapInputs::getMaxLength() {
    return MAX_LENGTH;
}

// TODO : we replace this function to LstmLCRModel::saveClusterMap
bool UpdateClusterMapOutputs::saveClusterMap(string file_name, unordered_map<string, int> cluster_map) {
    ofstream ofs(file_name);
    if (!ofs) return false;
    ofs << cluster_map.size() << endl;
    unordered_map<string, int>::iterator p;
    for (p=cluster_map.begin(); p!=cluster_map.end(); p++) {
        ofs << p->first << " " << p->second << endl;
    }
    if (!ofs) return false;
    return true;
}

TrainInputs::TrainInputs(fl::DataMetadata metaData, string trainInfo, int K) {
    stringstream ss(trainInfo);
    string train_param_file;
    string preprocess_param_file;
    string output_folder;
    string backup_folder;
    ss >> train_param_file;
    ss >> preprocess_param_file;
    ss >> output_folder;
    ss >> backup_folder;
    if (!ss) {
#ifdef DEBUG
        cout << "invalid trainInfo. [" + trainInfo + "]" << endl;
#endif
        return;
    }
    output_nn_files.resize(K);
    for (int i = 0; i < K; i++) {
        output_nn_files[i] = output_folder + "/" + NN_FILE_PREFIX + to_string(i+1) + NN_FILE_EXTENSION;
    }
    output_lcr_file = output_folder + "/" + LCR_FILE_NAME;
    output_valid_file = output_folder + "/" + VALIDATION_FILE_NAME;
    output_cluster_map_file = backup_folder + "/" + CLUSTER_MAP_FILE_NAME;
    if (!loadDataFile(metaData)) {
#ifdef DEBUG
        cout << "loadDataFile is failed." << endl;
#endif
        return;
    }
    if (!loadTrainParamsFile(train_param_file)) {
#ifdef DEBUG
        cout << "loadTrainParamsFile is failed." << endl;
#endif
        return;
    }
    // if (loadPreProcessParamFile(preprocess_param_file)) return;
    isValid = true;
}

TrainInputs::~TrainInputs() {}

// This is copy of UpdateClusterMapInputs::loadDataFile
// TODO : merge these functions
bool TrainInputs::loadDataFile(fl::DataMetadata metaData) {
	fl::DataDeserializer dataDeserializer = fl::DataDeserializer::createFor(metaData);
    num_of_data = dataDeserializer.getNumOfData();
    if (num_of_data == 0) {
#ifdef DEBUG
        cout << num_of_data << " is zero. no data." << endl;
#endif
        return true;
    }
    if (num_of_data < 0 || num_of_data > MAX_NUM_OF_DATA) {
#ifdef DEBUG
        cout << num_of_data << " is invalid num_of_data." << endl;
#endif
        return false;
    }
    std::shared_ptr<fl::Tensor> ts_num_of_features = dataDeserializer.get(1)->get("num_of_features");
    if (!ts_num_of_features) {
#ifdef DEBUG
        cout << "no num_of_features." << endl;
#endif
        return false;
    }
    num_of_features = ts_num_of_features->intValue();
    if (num_of_data > 0 && num_of_features != NUM_OF_FEATURES_FOR_SNE) { // tentative
#ifdef DEBUG
        cout << num_of_features << " is invalid num_of_features" << endl;
#endif
        return false;
    }
    // TODO: use unique_ptr
    x = shared_ptr<float>(new float[num_of_data * num_of_features * MAX_LENGTH], default_delete<float[]>());
    y = shared_ptr<float>(new float[num_of_data], default_delete<float[]>());
    groupLabel = shared_ptr<string>(new string[num_of_data], default_delete<string[]>());
    lengths = shared_ptr<int>(new int[num_of_data], default_delete<int[]>());

    vector<int> v(num_of_data);
    iota(v.begin(), v.end(), 1);
    random_device seed_gen;
    mt19937 engine(seed_gen());
    shuffle(v.begin(), v.end(), engine);

    bool flag = true;
    for (int i = 0;i < num_of_data;i++) {
        shared_ptr<fl::TensorMap> tensorMap = dataDeserializer.get(v[i]);
        std::shared_ptr<fl::Tensor> ts_f = tensorMap->get("num_of_features");
        if (!ts_f) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << "no num_of_features." << endl;
#endif
            break;
        }
        num_of_features = ts_f->intValue();
        std::shared_ptr<fl::Tensor> ts_g = tensorMap->get("group_label");
        if (!ts_g) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << "no group_label." << endl;
#endif
            break;
        }
        groupLabel.get()[i] = ts_g->textValue();
        std::shared_ptr<fl::Tensor> ts_y = tensorMap->get("y");
        if (!ts_y) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << "no y." << endl;
#endif
            break;
        }
        y.get()[i] = ts_y->floatValue();
        std::shared_ptr<fl::Tensor> ts_x = tensorMap->get("x");
        if (!ts_x) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << "no x." << endl;
#endif
            break;
        }
        lengths.get()[i] = ts_x->size() / num_of_features;
        if (y.get()[i] != 0 && y.get()[i] != 1) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << y.get()[i] << " is invalid y." << endl;
#endif
            break;
        }
        if (lengths.get()[i] < MIN_LENGTH || lengths.get()[i] > MAX_LENGTH) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << lengths.get()[i] << " is invalid length." << endl;
#endif
            break;
        }
        vector<float> tensor_x = ts_x->floatVector();
        for (int t = 0;t < lengths.get()[i]; t++) {
            for (int f = 0;f < num_of_features; f++) {
                x.get()[i * (num_of_features * MAX_LENGTH) + t * num_of_features + f] = tensor_x.data()[(t * num_of_features) + f];
#ifdef DEBUG
                cout << x.get()[i * (num_of_features * MAX_LENGTH) + t * num_of_features + f] << " ";
#endif
            }
#ifdef DEBUG
            cout << endl;
#endif
        }
        lengths.get()[i]--;
    }
    return flag;
}

bool TrainInputs::loadTrainParamsFile(string train_param_file) {
    float _alpha, _beta, _sigma, _delta, _learning_rate;
    int _batch_size, _num_of_epoch;
    ifstream ifs(train_param_file);
    if (!ifs) {
#ifdef DEBUG
        cout << train_param_file << " is not readable." << endl;
#endif
        return false;
    }
    ifs >> _alpha >> _beta >> _sigma >> _delta;
    ifs >> _learning_rate >> _batch_size >> _num_of_epoch;
    if (!ifs) {
#ifdef DEBUG
        cout << train_param_file << " is invalid format." << endl;
#endif
        return false;
    }
    if (_learning_rate <= 0) {
#ifdef DEBUG
        cout << "learning rate is invalid." << endl;
#endif
        return false;
    }
    if (_batch_size <= 0) {
#ifdef DEBUG
        cout << "batch size is invalid." << endl;
#endif
        return false;
    }
    if (_num_of_epoch <= 0) {
#ifdef DEBUG
        cout << "num of epoch is invalid." << endl;
#endif
        return false;
    }
    // TODO : verification
    alpha = _alpha;
    beta = _beta;
    sigma = _sigma;
    delta = _delta;
    learning_rate = _learning_rate;
    batch_size = _batch_size;
    num_of_epoch = _num_of_epoch;
    return true;
}

bool TrainOutputs::saveValidationResults(string file_name, int num_of_data, float loss) {
    ofstream ofs(file_name);
    if (!ofs) return false;
    ofs << num_of_data << " " << loss << endl;
    if (!ofs) return false;
    return true;
}

EvaluationInputs::EvaluationInputs(fl::DataMetadata metaData, string evaluationInfo) {
    stringstream ss(evaluationInfo);
    string preprocess_param_file;
    string output_folder;
    ss >> preprocess_param_file;
    ss >> output_folder;
    if (!ss) {
#ifdef DEBUG
        cout << "evaluationInfo is invalid." << endl;
#endif
        return;
    }
    if (!loadDataFile(metaData)) {
#ifdef DEBUG
        cout << "loadDataFile is failed." << endl;
#endif
        return;
    }
    // if (loadPreProcessParamFile(preprocess_param_file)) return;
    output_eval_file = output_folder + "/" + EVALUATION_RESULT_FILE_NAME;
    isValid = true;
}

EvaluationInputs::~EvaluationInputs() {}

// This is copy of UpdateClusterMapInputs::loadDataFile
// TODO : merge these functions
bool EvaluationInputs::loadDataFile(fl::DataMetadata metaData) {
	fl::DataDeserializer dataDeserializer = fl::DataDeserializer::createFor(metaData);
    num_of_data = dataDeserializer.getNumOfData();
    if (num_of_data == 0) {
#ifdef DEBUG
        cout << num_of_data << " is zero. no data." << endl;
#endif
        return true;
    }
    if (num_of_data < 0 || num_of_data > MAX_NUM_OF_DATA) {
#ifdef DEBUG
        cout << num_of_data << " is invalid num_of_data." << endl;
#endif
        return false;
    }
    std::shared_ptr<fl::Tensor> ts_num_of_features = dataDeserializer.get(1)->get("num_of_features");
    if (!ts_num_of_features) {
#ifdef DEBUG
        cout << "no num_of_features." << endl;
#endif
        return false;
    }
    num_of_features = ts_num_of_features->intValue();
    if (num_of_data > 0 && num_of_features != NUM_OF_FEATURES_FOR_SNE) { // tentative
#ifdef DEBUG
        cout << num_of_features << " is invalid num_of_features" << endl;
#endif
        return false;
    }
    x = shared_ptr<float>(new float[num_of_data * num_of_features * MAX_LENGTH], default_delete<float[]>());
    y = shared_ptr<float>(new float[num_of_data], default_delete<float[]>());
    groupLabel = shared_ptr<string>(new string[num_of_data], default_delete<string[]>());
    lengths = shared_ptr<int>(new int[num_of_data], default_delete<int[]>());

    bool flag = true;
    for (int i = 0;i < num_of_data;i++) {
        shared_ptr<fl::TensorMap> tensorMap = dataDeserializer.get(i+1);
        std::shared_ptr<fl::Tensor> ts_f = tensorMap->get("num_of_features");
        if (!ts_f) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << "no num_of_features." << endl;
#endif
            break;
        }
        num_of_features = ts_f->intValue();
        std::shared_ptr<fl::Tensor> ts_g = tensorMap->get("group_label");
        if (!ts_g) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << "no group_label." << endl;
#endif
            break;
        }
        groupLabel.get()[i] = ts_g->textValue();
        std::shared_ptr<fl::Tensor> ts_y = tensorMap->get("y");
        if (!ts_y) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << "no y." << endl;
#endif
            break;
        }
        y.get()[i] = ts_y->floatValue();
        std::shared_ptr<fl::Tensor> ts_x = tensorMap->get("x");
        if (!ts_x) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << "no x." << endl;
#endif
            break;
        }
        lengths.get()[i] = ts_x->size() / num_of_features;
        if (y.get()[i] != 0 && y.get()[i] != 1) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << y.get()[i] << " is invalid y." << endl;
#endif            
            break;
        }
        if (lengths.get()[i] < MIN_LENGTH || lengths.get()[i] > MAX_LENGTH) {
            flag = false;
#ifdef DEBUG
            cout << i << " : " << lengths.get()[i] << " is invalid length." << endl;
#endif
            break;
        }
        vector<float> tensor_x = ts_x->floatVector();
        for (int t = 0;t < lengths.get()[i]; t++) {
            for (int f = 0;f < num_of_features; f++) {
                x.get()[i * (num_of_features * MAX_LENGTH) + t * num_of_features + f] = tensor_x.data()[(t * num_of_features) + f];
#ifdef DEBUG
                cout << x.get()[i * (num_of_features * MAX_LENGTH) + t * num_of_features + f] << " ";
#endif
            }
#ifdef DEBUG
            cout << endl;
#endif
        }
        lengths.get()[i]--;
    }
    return flag;
}

bool EvaluationOutputs::saveEvaluationResults(string file_name, int num_of_data , float *y, float *y_pred) {
    ofstream ofs(file_name);
    if (!ofs) return false;
    ofs << num_of_data;
    for (int i = 0;i < num_of_data; i++) {
        ofs << endl;
        ofs << y[i] << " " << y_pred[i];
    }
    return true;
}
