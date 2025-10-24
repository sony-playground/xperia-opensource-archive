#include <random>
#include <fstream>

#include "NNHLCR/lstm_lcr_model_nnabla.h"

//#define DEBUG

using namespace std;

LstmLCRModel::LstmLCRModel() {

}

LstmLCRModel::LstmLCRModel(int n_components, float alpha, float beta, float delta, float sigma,
                           int max_iter, int batch_size, int max_len, int n_features,
                           vector<string> &nntxt_files, vector<string> &protobuf_files,
                           vector<float> &global_weights, unordered_map<string, int> &cluster_mapping) {
  // WARNING : check the return group_likelihood!!!
  this->initialize(n_components, nntxt_files, protobuf_files, 
            global_weights, cluster_mapping, max_len, n_features);
}

LstmLCRModel::~LstmLCRModel() {
}

void LstmLCRModel::_make_group_indices(string g[], string u[]) {

}

void LstmLCRModel::_initialize_group_labels(string g[], string u[]) {
  std::random_device seed_gen;
  std::default_random_engine engine(seed_gen());
  std::uniform_int_distribution<> dist(0, this->n_components-1);

  for (int i = 0; i < 64; i++) { // TODO : fix this magic number 64!!!
    int sampled = dist(engine);
    this->cluster_mapping.insert(std::make_pair(g[i], sampled));
  }
}

void LstmLCRModel::_assign_record_labels(string g[], string u[], int num_of_data, int record_labels[]) {
  for (int n = 0; n < num_of_data; n++) {
    record_labels[n] = cluster_mapping[g[n]];
  }
}

bool LstmLCRModel::_update_cluster(float x[], float y[], string g[],
    string u[], int l[], int num_of_data, int t_len, int i_len) {

  unordered_map<string, vector<float>> log_group_likelihood{};
  bool flag = _estimate_log_group_likelihood(x, y, g, u, l, log_group_likelihood, num_of_data, t_len, i_len);
  if (!flag) {
#ifdef DEBUG
    cout << "_estimate_log_group_likelihood was failed." << endl;
#endif
    return false;
  }

  for (unordered_map<string, vector<float>>::iterator it = log_group_likelihood.begin();
       it != log_group_likelihood.end() ; ++it) {
    string g_id = it->first;
    vector<float> log_likelihood = it->second;
#ifdef DEBUG
      cout << "g_id = " << g_id << " log_group_likelihood" << endl;
#endif

    int cluster_id = -1;
    float max_log_posterior = -1e8;
    for (int k = 0; k < n_components; k++) {
#ifdef DEBUG
      cout << k << "-th model log_likelihood = " << log_likelihood[k] << endl;
#endif
      float log_posterior = log_likelihood[k] + log(this->global_weights[k]);
#ifdef DEBUG
      cout << k << "-th model log_posterior = " << log_posterior << endl;
#endif
      if (log_posterior > max_log_posterior) {
        cluster_id = k;
        max_log_posterior = log_posterior;
      }
    }

    cluster_mapping[g_id] = cluster_id;
  }
  if (!_update_local_nk()) {
    return false;
  }
  return true;
}

bool LstmLCRModel::_update_local_nk() {
  if (local_nk.size() != n_components) return false;
  for (int k = 0; k < n_components; k++) {
    local_nk[k] = 0;
  }
  for (auto p=cluster_mapping.begin(); p!=cluster_mapping.end(); p++) {
      int index = p->second;
      if (index < 0 || index >= n_components) return false;
      local_nk[index]++;
  }
  return true;
}

bool LstmLCRModel::_gibbs_sampling(unordered_map<string, vector<float>> &log_group_posterior) {
  cluster_mapping.clear();

  std::random_device seed_gen;
  std::mt19937 engine(seed_gen());

  for (unordered_map<string, vector<float>>::iterator it = log_group_posterior.begin();
       it != log_group_posterior.end() ; ++it) {
    string g_id = it->first;
    vector<float> log_posterior = it->second;

    std::discrete_distribution<std::size_t> dist(
      log_posterior.begin(),
      log_posterior.end()
    );

    cluster_mapping[g_id] = dist(engine);
#ifdef DEBUG
    std::cout << "sampled: " << g_id << " : " << cluster_mapping[g_id] << endl;
#endif
  }

  return true;
}

bool LstmLCRModel::_estimate_log_group_posterior(float x[], float y[], string g[], string u[], int l[],
  unordered_map<string, vector<float>> &log_group_posterior,
  int num_of_data, int t_len, int i_len) {

  vector<float> log_group_prior(n_components, 0);
  _estimate_log_group_prior(log_group_prior);

  unordered_map<string, vector<float>> log_group_likelihood{};
  bool flag = _estimate_log_group_likelihood(x, y, g, u, l, log_group_likelihood, num_of_data, t_len, i_len);
  if (!flag) {
#ifdef DEBUG
    cout << "_estimate_log_group_likelihood was failed." << endl;
#endif
    return false;
  }

  log_group_posterior.clear();
  for (unordered_map<string, vector<float>>::iterator it = log_group_likelihood.begin();
       it != log_group_likelihood.end() ; ++it) {
    string g_id = it->first;
    vector<float> log_likelihood = it->second;
#ifdef DEBUG
      cout << "g_id = " << g_id << " log_group_likelihood" << endl;
#endif

    vector<float> log_posterior(n_components, 0);
    for (int k = 0; k < n_components; k++) {
#ifdef DEBUG
      cout << k << "-th model log_likelihood = " << log_likelihood[k] << endl;
#endif
      log_posterior[k] = log_likelihood[k] + log_group_prior[k];
#ifdef DEBUG
      cout << k << "-th model log_posterior = " << log_posterior[k] << endl;
#endif
    }
    log_group_posterior[g_id] = log_posterior;
  }

  return true;
}

bool LstmLCRModel::_estimate_log_group_likelihood(float x[], float y[], string g[],
    string u[], int l[], unordered_map<string, vector<float>> &log_group_likelihood,
    int num_of_data, int t_len, int i_len) {

  shared_ptr<float> log_record_likelihood = shared_ptr<float>(new float[n_components*num_of_data], default_delete<float[]>());
  bool flag = _estimate_log_record_likelihood(x, y, l, log_record_likelihood.get(), num_of_data, t_len, i_len);
  if (!flag) {
#ifdef DEBUG
    cout << "_estimate_log_record_likelihood was failed." << endl;
#endif
    return false;
  }

  log_group_likelihood.clear();
  for (int b=0; b<num_of_data; b++) {
    string g_id(g[b]);
    if (log_group_likelihood.find(g_id) == log_group_likelihood.end()) {
      vector<float> empty_vector(n_components, 0);
      log_group_likelihood[g_id] = empty_vector;
    }
    for (int k=0; k<n_components; k++) {
      log_group_likelihood[g_id][k] += log_record_likelihood.get()[b*n_components + k];
    }
  }
  return true;
}

bool LstmLCRModel::_estimate_log_record_likelihood(float x[], float y[], int l[],
    float *log_record_likelihood, int num_of_data, int t_len, int i_len) {
  bool flag = true;
  shared_ptr<float> y_pred = shared_ptr<float>(new float[num_of_data], default_delete<float[]>());
  for (int k=0; k<n_components; k++) {
#ifdef DEBUG
      cout << k << "-th model log_record_likelihood" << endl;
#endif
    int ret = this->models[k]->predict(x, l, y_pred.get(), num_of_data, t_len, i_len);
    if (ret != 0) {
      flag = false;
#ifdef DEBUG
      cout << "predict was failed" << endl;
#endif
      break;
    }
    for (int b=0; b<num_of_data; b++) {
      if (y_pred.get()[b] <= 0 || y_pred.get()[b] >= 1) {
        flag = false;
#ifdef DEBUG
        cout << "prediction result was invalid" << endl;
#endif
        break;
      }
      float log_likelihood = (1-y[b]) * log(1-y_pred.get()[b]) + y[b] * log(y_pred.get()[b]);
#ifdef DEBUG
      cout << b << " : " << log_likelihood << endl;
#endif
      log_record_likelihood[b*n_components + k] = log_likelihood;
    }
  }
  return flag;
}

void LstmLCRModel::_estimate_log_group_prior(vector<float> &log_group_weights) {
  vector<float> group_weights(global_weights);
  for (int k = 0; k<n_components; k++) {
    group_weights[k] *= beta;
  }

  for (unordered_map<string, int>::iterator it = cluster_mapping.begin();
       it != cluster_mapping.end(); ++it) {
    string g_id = it->first;
    int cluster_id = it->second;

    group_weights[cluster_id]++;
  }

  for (int k = 0; k<n_components; k++) {
    log_group_weights[k] = log(group_weights[k]);
  }
}

bool LstmLCRModel::_update_parameter(float x[], float y[], int l[], int record_labels[], int k,
                                      int num_of_data, int t_len, int i_len) {
  float *x_batch = new float[batch_size * t_len * i_len];
  float *y_batch = new float[batch_size];
  int *l_batch = new int[batch_size];

  int b = 0;
  for (int n = 0; n < num_of_data; n++) {
    if (record_labels[n] == k) {
      std::memcpy(x_batch + b * t_len * i_len, x + n * t_len * i_len, sizeof(float) * t_len * i_len);
      y_batch[b] = y[n];
      l_batch[b] = l[n];
      b++;
    }

    if (b == batch_size || n == num_of_data - 1) {
      float mean_loss;
      this->models[k]->train(x_batch, l_batch, y_batch, &mean_loss, b, t_len, i_len);
      loss += mean_loss * b;
#ifdef DEBUG
      cout << "mean_loss: " << mean_loss << endl;
#endif
    }

    b = b%batch_size;
  }

  delete[] x_batch;
  delete[] y_batch;
  delete[] l_batch;

  return true;
}

int LstmLCRModel::initialize(int n_components, vector<string> &nntxt_files, vector<string> &protobuf_files,
                             vector<float> &global_weights, unordered_map<string, int> &cluster_mapping,
                             int max_len, int n_features) {

  if (n_components < MIN_N_COMPONENTS || n_components > MAX_N_COMPONENTS) {
#ifdef DEBUG
    cout << "n_components is invalid : " << n_components << endl;
#endif
    return -1;
  }

  if (nntxt_files.size() != n_components || protobuf_files.size() != n_components || global_weights.size() != n_components) {
#ifdef DEBUG
    cout << "Size of vector is invalid." << endl;
#endif
    return -1;
  }

  if (max_len < MIN_MAX_LEN || max_len > MAX_MAX_LEN) {
#ifdef DEBUG
    cout << "max_len is invalid: " << max_len << endl;
#endif
    return -1;    
  }

  if (n_features < MIN_N_FEATURES || n_features > MAX_N_FEATURES) {
#ifdef DEBUG
    cout << "n_features is invalid : " << n_features << endl;
#endif
    return -1;    
  }

  for (int i=0;i<n_components;i++) {
    if (global_weights[i] <= 0) {
#ifdef DEBUG
      cout << i << "-th global weight is invalid : " << global_weights[i] << endl;
#endif
      return -1;
    }
  }

  this->n_components = n_components;
  this->cluster_mapping = cluster_mapping;
  this->global_weights = global_weights;
  this->max_len = max_len;
  this->n_features = n_features;
  this->local_nk.resize(n_components);

  // TODO: delete
  //this->batch_size = 1;

  this->models.resize(n_components);
  for (int c = 0; c < n_components; c++) {
    this->models[c] = shared_ptr<LstmModel>(new LstmModel(this->batch_size, this->max_len, this->n_features));
    int ret = this->models[c]->load_model_from_nnp(nntxt_files[c], protobuf_files[c]);
    if (ret != 0) {
#ifdef DEBUG
      cout << "load model from nnp " << nntxt_files[c] << " is failed." << endl;
#endif
      return -1;
    }
    /*
    ret = this->models[c]->load_trainer_from_nnp(nntxt_files[c], protobuf_files[c]);
    if (ret != 0) {
#ifdef DEBUG
      cout << "load model from nnp " << nntxt_files[c] << " is failed." << endl;
#endif
      return -1;
    }
    */
  }
  return 0;
}

// TODO : check value
int LstmLCRModel::set_parameters(float alpha, float beta, float delta, float sigma,
                                  int max_iter, int batch_size, float learning_rate) {
  this->alpha = alpha;
  this->beta = beta;
  this->delta = delta;
  this->sigma = sigma;
  this->max_iter = max_iter;
  this->batch_size = batch_size;
  this->learning_rate = learning_rate;
  for (int k = 0; k < n_components;k++) {
    models[k]->set_parameters(learning_rate);
  }
  return 0;
}

int LstmLCRModel::train(float x[], float y[], string g[], string u[], int l[],
    int num_of_data, int t_len, int i_len) {
  unordered_map<string, vector<float>> log_group_posterior{};
  _estimate_log_group_posterior(x, y, g, u, l, log_group_posterior,
    num_of_data, t_len, i_len);
  
  _gibbs_sampling(log_group_posterior);

  shared_ptr<int> record_labels = shared_ptr<int>(new int[num_of_data], default_delete<int[]>());
  _assign_record_labels(g, u, num_of_data, record_labels.get());

  loss = 0.0;
  for (int k = 0; k < n_components; k++) {
    _update_parameter(x, y, l, record_labels.get(), k, num_of_data, t_len, i_len);
  }
  loss = loss / num_of_data;

  if (!_update_local_nk()) {
    return false;
  }
  
  return 0;
}

int LstmLCRModel::predict(float x[], string g[],
    string u[], int l[], float y_pred[],
    int num_of_data, int t_len, int i_len) {

  for (int b = 0; b < num_of_data; b++) {
    int index = _getIndexFromClusterMap(g[b]);
    if (index < 0 || index >= this->n_components) {
#ifdef DEBUG
      cout << "index is invalid : " << index << endl;
#endif
      return -1;
    }
#ifdef DEBUG
    cout << index << "-th model starts prediction." << endl;
#endif

    if (models[index]->predict(x + b*t_len*i_len, l + b, y_pred + b, 1, t_len, i_len) != 0) {
#ifdef DEBUG
      cout << "predict error : " << endl;
#endif
      return -1;
    }
  }
  return 0;
}

int LstmLCRModel::update_cluster(float x[], float y[], string g[],
    string u[], int l[], int num_of_data, int t_len, int i_len) {

  bool flag = _update_cluster(x, y, g, u, l, num_of_data, t_len, i_len);
  if (!flag) {
#ifdef DEBUG
    cout << "_update_cluster was failed." << endl;
#endif
    return -1;
  }
  return 0;
}

void LstmLCRModel::finalize() {}

int LstmLCRModel::_getIndexFromClusterMap(string group_label) {
  if (cluster_mapping.find(group_label) != cluster_mapping.end()) {
    return cluster_mapping[group_label];
  }
  int arg_max = 0;
  float max_weight = -1e8;
  for (int i=0;i<n_components;i++) {
    if (global_weights[i] > max_weight) {
      arg_max = i;
      max_weight = global_weights[i];
    }
  }
  return arg_max;
}

bool LstmLCRModel::saveNNModels(vector<string> file_names) {
  for (int i = 0;i < n_components; i++) {
    bool flag = models[i]->saveNNModel(file_names[i]);
    if (!flag) return false;
  }
  return true;
}
bool LstmLCRModel::saveLCRParams(string file_name) {
  ofstream ofs(file_name);
  ofs << n_components;
  for (int i = 0; i < n_components; i++) {
    ofs << "\n" << local_nk[i];
  }
  if (!ofs) return false;
  return true;
}
bool LstmLCRModel::saveClusterMap(string file_name) {
  ofstream ofs(file_name);
  if (!ofs) return false;
  ofs << cluster_mapping.size() << endl;
  for (auto p=cluster_mapping.begin(); p!=cluster_mapping.end(); p++) {
      ofs << p->first << " " << p->second << endl;
  }
  if (!ofs) return false;
  return true;
}
