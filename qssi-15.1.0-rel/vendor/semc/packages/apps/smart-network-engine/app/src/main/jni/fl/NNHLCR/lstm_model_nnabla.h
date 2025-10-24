#ifndef LSTM_MODEL_NNABLA_HPP_
#define LSTM_MODEL_NNABLA_HPP_
#include <nbla_utils/nnp.hpp>
//#include <nbla/solver/adam.hpp>
#include <nbla/solver/sgd.hpp>

//#define DEBUG

#ifdef WITH_CUDA
#include <nbla/cuda/cudnn/init.hpp>
#include <nbla/cuda/init.hpp>
#endif

#include <string>

using namespace std;

class LstmModel {
  static const int MIN_B = 1;
  static const int MAX_B = 256;
  static const int MIN_T = 1;
  static const int MAX_T = 1000;
  static const int MIN_I = 1;
  static const int MAX_I = 10000;
private:
  int B=64;
  int T=30;
  int I=18;
  float learning_rate=0.01;

  shared_ptr<nbla::utils::nnp::Executor> executor;
  shared_ptr<nbla::utils::nnp::Network> network;
  nbla::Context cpu_ctx{{"cpu:float"}, "CpuCachedArray", "0"};
  unique_ptr<nbla::utils::nnp::Nnp> nnp;

  float *x_data = NULL;
  int *l_data = NULL;
  float *y_data = NULL;
  const float *y_pred_data = NULL;

  int B_model = 0; // batch size of Lstm Model

public:
  LstmModel();
  LstmModel(int B, int T, int I);
  ~LstmModel();

  int initialize(int B, int T, int I);
  int load_model_from_nnp(string nntxt_file, string protobuf_file);
  int predict(float x_array[], int l_array[], float y_pred[], int batch_size, int t_len, int i_len);
  int train(float x_array[], int l_array[], float y_array[], float *mean_loss, int num_of_data, int t_len, int i_len);
  int set_parameters(float learning_rate);

  bool load_x(float* x_array, int sp, int ep);
  bool load_l(int* l_array, int sp, int ep);
  bool load_y(float* y_array, int sp, int ep);
  bool saveNNModel(string file_name);
};
#endif  // LSTM_MODEL_NNABLA_HPP_
