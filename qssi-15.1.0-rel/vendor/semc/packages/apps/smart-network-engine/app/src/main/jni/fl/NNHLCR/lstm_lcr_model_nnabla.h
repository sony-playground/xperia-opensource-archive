#ifndef LSTM_LCR_MODEL_NNABLA_HPP_
#define LSTM_LCR_MODEL_NNABLA_HPP_
#include <vector>
#include <unordered_map>
#include <memory>

#include "lstm_model_nnabla.h"

//#define DEBUG

using namespace std;

class LstmLCRModel {
  static const int MIN_N_COMPONENTS = 1;
  static const int MAX_N_COMPONENTS = 100;
  static const int MIN_MAX_LEN = 1;
  static const int MAX_MAX_LEN = 1000;  
  static const int MIN_N_FEATURES = 1;
  static const int MAX_N_FEATURES = 10000;  
private:
  unordered_map<string, int> cluster_mapping;

  void _make_group_indices(string g[], string u[]);
  void _initialize_group_labels(string g[], string u[]);
  void _assign_record_labels(string g[], string u[], int num_of_data, int record_labels[]);

  bool _update_cluster(float x[], float y[], string g[], string u[], int l[],
    int batch_size, int t_len, int i_len);
  bool _gibbs_sampling(unordered_map<string, vector<float>> &log_group_posterior);
  bool _estimate_log_group_posterior(float x[], float y[], string g[], string u[], int l[],
    unordered_map<string, vector<float>> &log_group_posterior,
    int batch_size, int t_len, int i_len);
  bool _estimate_log_group_likelihood(float x[], float y[], string g[], string u[], int l[],
    unordered_map<string, vector<float>> &log_group_likelihood,
    int batch_size, int t_len, int i_len);
  bool _estimate_log_record_likelihood(float x[], float y[], int l[], float *log_record_likelihood,
    int batch_size, int t_len, int i_len);
  void _estimate_log_group_prior(vector<float> &log_group_weights);
  bool _update_parameter(float x[], float y[], int l[], int record_labels[], int k,
    int num_of_data, int t_len, int i_len);
  int _getIndexFromClusterMap(string group_label);
  bool _update_local_nk();


public:
  LstmLCRModel();
  LstmLCRModel(int n_components, float alpha, float beta, float delta, float sigma,
               int max_iter, int batch_size, int max_len, int n_features,
               vector<string> &nntxt_files, vector<string> &protobuf_files, 
               vector<float> &global_weights, unordered_map<string, int> &cluster_mapping);
  ~LstmLCRModel();

  int n_components = 0;
  float alpha = 0.0;
  float beta = 0.0;
  float delta = 0.0;
  float sigma = 0.0;
  int max_iter = 0;
  int batch_size = 64;
  float learning_rate = 0.0;
  int max_len = 0;
  int n_features = 0;

  vector<shared_ptr<LstmModel>> models;
  vector<float> global_weights;
  vector<int> local_nk;
  float loss = 0.0;

  int initialize(int n_components, vector<string> &nntxt_files, vector<string> &protobuf_files,
                 vector<float> &global_weights, unordered_map<string, int> &cluster_mapping,
                 int max_len, int n_features);
  int set_parameters(float alpha, float beta, float delta, float sigma,
                      int max_iter, int batch_size, float learning_rate);
  int train(float x[], float y[], string g[], string u[], int l[], int num_of_data, int t_len, int i_len);
  int predict(float x[], string g[],
    string u[], int l[], float y_pred[],
    int num_of_data, int t_len, int i_len);
  int update_cluster(float x[], float y[], string g[],
    string u[], int l[], int num_of_data, int t_len, int i_len);
  void finalize();
  unordered_map<string, int> getClusterMap() {return cluster_mapping;};
  bool saveNNModels(vector<string> file_names);
  bool saveLCRParams(string file_name);
  bool saveClusterMap(string file_name);
};
#endif  // LSTM_LCR_MODEL_NNABLA_HPP_
