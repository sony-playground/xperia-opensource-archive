#include <nbla_utils/nnp.hpp>
//#include <nbla/solver/adam.hpp>
#include <nbla/solver/sgd.hpp>

//#define DEBUG

#ifdef WITH_CUDA
#include <nbla/cuda/cudnn/init.hpp>
#include <nbla/cuda/init.hpp>
#endif

#include <string>

#include "NNHLCR/lstm_model_nnabla.h"

using namespace std;
// using std::ifstream;

LstmModel::LstmModel() : nnp(new nbla::utils::nnp::Nnp(cpu_ctx)) {
}

LstmModel::LstmModel(int B, int T, int I) : nnp(new nbla::utils::nnp::Nnp(cpu_ctx)) {
  // WARNING : check the return value!!!
  this->initialize(B, T, I);
}

LstmModel::~LstmModel() {

}

int LstmModel::initialize(int B, int T, int I) {
  if (B < MIN_B || B > MAX_B) return -1;
  if (T < MIN_T || T > MAX_T) return -1;
  if (I < MIN_I || I > MAX_I) return -1;
  this->B = B;
  this->T = T;
  this->I = I;
  return 0;
}

int LstmModel::set_parameters(float learning_rate) {
  if (learning_rate < 0) return -1;
  this->learning_rate = learning_rate;
  return 0;
}

int LstmModel::load_model_from_nnp(string nntxt_file, string protobuf_file) {

  // Set nnp file to Nnp object.
  if (!(nnp->add(nntxt_file))) {
#ifdef DEBUG
    cout << "load nntxt file " << nntxt_file << " is failed." << endl;
#endif
    return -1;
  }
  
  if (!(nnp->add(protobuf_file))) {
#ifdef DEBUG
    cout << "load protobuf file " << protobuf_file << " is failed." << endl;
#endif
    return -1;
  }
  
  // Get an executor instance.
  string executor_name("runtime");
  this->executor = nnp->get_executor(executor_name);
  if (this->executor == NULL) {
#ifdef DEBUG
    cout << "executor is NULL." << endl;
#endif
    return -1;
  }

  // Get an network instance.
  string network_name("training");
  this->network = nnp->get_network(network_name);
  if (this->network == NULL) {
#ifdef DEBUG
    cout << "network is NULL." << endl;
#endif
    return -1;
  }

  nbla::CgVariablePtr l = this->executor->get_data_variables().at(1).variable;
  this->B_model = l->variable()->size();
  this->B = this->B_model;
#ifdef DEBUG
  cout << "B_model = " << B_model << endl;
#endif
  return 0;
}

int LstmModel::predict(float x_array[],
    int l_array[], float y_pred[],
    int num_of_data, int t_len, int i_len) {
  
  nbla::CgVariablePtr x = this->executor->get_data_variables().at(0).variable;
  nbla::CgVariablePtr l = this->executor->get_data_variables().at(1).variable;
  nbla::CgVariablePtr y = this->executor->get_output_variables().at(0).variable;
  this->x_data = x->variable()->cast_data_and_get_pointer<float>(cpu_ctx);
  this->l_data = l->variable()->cast_data_and_get_pointer<int>(cpu_ctx);
  this->y_pred_data = y->variable()->get_data_pointer<float>(cpu_ctx);
  Size_t x_size = x->variable()->size();
  Size_t l_size = l->variable()->size();
  Size_t y_size = y->variable()->size();

  if (x_size != B_model * t_len * i_len) {
#ifdef DEBUG
    cout << "x_size is invalid. " << x_size << endl;
#endif
    return -1;  
  }

  if (l_size != B_model) {
#ifdef DEBUG
    cout << "l_size is invalid. " << l_size << endl;
#endif
    return -1;
  }

  if (y_size != B_model * 2) {
#ifdef DEBUG
    cout << "y_size is invalid. " << y_size << endl;
#endif
    return -1;
  }

  if (t_len != T) {
#ifdef DEBUG
    cout << "t_len is invalid. " << t_len << endl;
#endif
    return -1;
  }

  if (i_len != I) {
#ifdef DEBUG
    cout << "i_len is invalid. " << i_len << endl;
#endif
    return -1;
  }

#ifdef DEBUG
  cout << "data size : " << num_of_data << " " << t_len << " " << i_len << endl;
#endif

  for (int index = 0;index < num_of_data; index += B_model) {
    nbla::CgVariablePtr x = this->executor->get_data_variables().at(0).variable;
    nbla::CgVariablePtr l = this->executor->get_data_variables().at(1).variable;
    nbla::CgVariablePtr y = this->executor->get_output_variables().at(0).variable;
    this->x_data = x->variable()->cast_data_and_get_pointer<float>(cpu_ctx);
    this->l_data = l->variable()->cast_data_and_get_pointer<int>(cpu_ctx);
    this->y_pred_data = y->variable()->get_data_pointer<float>(cpu_ctx);
    Size_t x_size = x->variable()->size();
    Size_t l_size = l->variable()->size();
    Size_t y_size = y->variable()->size();

    int start_i = index;
    int end_i = index + B_model;
    if (end_i > num_of_data) end_i = num_of_data;

#ifdef DEBUG
    cout << "data : " << start_i << " ~ " << end_i << endl;
#endif

    // Load input data into the CPU array.
    bool valid_X = load_x(x_array, start_i, end_i);
    bool valid_L = load_l(l_array, start_i, end_i);
    if ((!valid_X) || (!valid_L)) {
  #ifdef DEBUG
      cout << "load data was failed."  << endl;
  #endif
      return -1;
    }

    // Execute prediction
    this->executor->execute();
  #ifdef DEBUG
    cout << "Prediction scores:" << endl;
  #endif
    for (int b = start_i; b < end_i; b++) {
      y_pred[b] = y_pred_data[(b-start_i)*2+1];
  #ifdef DEBUG
      cout << "y_pred[" << b << "] = " << y_pred_data[(b-start_i)*2+1] << " : " << y_pred_data[(b-start_i)*2] << endl;
  #endif
    }
  }
  return 0;
}

int LstmModel::train(float x_array[], int l_array[], float y_array[], float *mean_loss,
    int num_of_data, int t_len, int i_len) {
  // Setup solver and input learnable parameters
  shared_ptr<Solver> sgd = create_SgdSolver(cpu_ctx, learning_rate);
  sgd->set_parameters(nnp->get_parameters());

  // Get input data as a CPU array.
  nbla::CgVariablePtr x = this->network->get_variable("x");
  nbla::CgVariablePtr l = this->network->get_variable("l");
  nbla::CgVariablePtr y = this->network->get_variable("y");
  nbla::CgVariablePtr loss = this->network->get_variable("loss");
  nbla::CgVariablePtr y_pred = this->network->get_variable("y_pred");
  this->x_data = x->variable()->cast_data_and_get_pointer<float>(cpu_ctx);
  this->l_data = l->variable()->cast_data_and_get_pointer<int>(cpu_ctx);
  this->y_data = y->variable()->cast_data_and_get_pointer<float>(cpu_ctx);
  Size_t x_size = x->variable()->size();
  Size_t l_size = l->variable()->size();
  Size_t y_size = y->variable()->size();

  if (x_size != B * t_len * i_len) {
#ifdef DEBUG
    cout << "x_size is invalid. " << x_size << endl;
#endif
    return -1;  
  }

  if (l_size != B) {
#ifdef DEBUG
    cout << "l_size is invalid. " << l_size << endl;
#endif
    return -1;
  }

  if (y_size != B * t_len) {
#ifdef DEBUG
    cout << "y_size is invalid. " << y_size << endl;
#endif
    return -1;
  }

  if (t_len != T) {
#ifdef DEBUG
    cout << "t_len is invalid. " << t_len << endl;
#endif
    return -1;
  }

  if (i_len != I) {
#ifdef DEBUG
    cout << "i_len is invalid. " << i_len << endl;
#endif
    return -1;
  }

#ifdef DEBUG
  cout << "data size : " << num_of_data << " " << t_len << " " << i_len << endl;
#endif

  *mean_loss = 0.;
  for (int index = 0;index < num_of_data; index += B) {
    int start_i = index;
    int end_i = index + B;
    if (end_i > num_of_data) end_i = num_of_data;

#ifdef DEBUG
    cout << "data : " << start_i << " ~ " << end_i << endl;
#endif

    // Load input data into the CPU array.
    bool valid_x = load_x(x_array, start_i, end_i);
    bool valid_l = load_l(l_array, start_i, end_i);
    bool valid_y = load_y(y_array, start_i, end_i);
    if ((!valid_x) || (!valid_l) || (!valid_y)) {
  #ifdef DEBUG
      cout << "load data was failed."  << endl;
  #endif
      return -1;
    }

    // Execute forward, backward and update
    sgd->zero_grad();
    loss->forward(/*clear_buffer=*/false, /*clear_no_need_grad=*/true);
    loss->variable()->grad()->fill(1.0);
    loss->backward(/*NdArrayPtr grad =*/nullptr, /*bool clear_buffer = */ true);
    sgd->update();

    // Get and print the sum loss
    float *loss_d =
        loss->variable()->cast_data_and_get_pointer<float_t>(cpu_ctx);
    *mean_loss += loss_d[0];
  }
  
  return 0;
}

bool LstmModel::load_x(float* x_array, int sp, int ep) {
  // initialize all memory
  for (int b=0; b<B_model * T * I; b++) {
    x_data[b] = 1.0;
  }
  // set x_array
  for (int b=sp; b<ep; b++) {
    for (int t=0; t<T; t++) {
      for (int i=0; i<I; i++) {
        x_data[t*B_model*I + (b-sp)*I + i] = x_array[b*T*I + t*I + i];
#ifdef DEBUG
        cout << x_data[t*B_model*I + (b-sp)*I + i] << " ";
#endif
      }
#ifdef DEBUG
        cout << endl;
#endif
    }
#ifdef DEBUG
        cout << endl;
#endif
  }
  return true;
}

bool LstmModel::load_l(int* l_array, int sp, int ep) {
  // initialize add memory
  for (int i=0;i<B_model;i++) {
    l_data[i] = 0;
  }
  // set l_array
  for (int b=sp; b<ep; b++) {
    if (l_array[b] < 0 || l_array[b] >= T) {
#ifdef DEBUG
      cout << l_array[b] << " is out of bounds." << endl;
#endif
      return false;
    }
    l_data[b-sp] = l_array[b];
#ifdef DEBUG
    cout << l_data[b-sp] << " ";
#endif
  }
#ifdef DEBUG
  cout << endl;
#endif
  return true;
}

bool LstmModel::saveNNModel(string file_name) {
  return nnp->save_parameters(file_name);
}

bool LstmModel::load_y(float* y_array, int sp, int ep) {
  // initialize add memory
  for (int b=0;b<B_model;b++) {
    for (int t=0; t<T; t++) {
      y_data[t*B_model + b] = 0;
    }
  }
  // set y_array
  for (int b=sp; b<ep; b++) {
    if (y_array[b] < 0 || y_array[b] > 1) {
#ifdef DEBUG
      cout << y_array[b] << " is out of bounds." << endl;
#endif
      return false;
    }
    for (int t=0; t<T; t++) {
      y_data[t*B_model + (b-sp)] = y_array[b];
    }
#ifdef DEBUG
    cout << y_data[b-sp] << " ";
#endif
  }
#ifdef DEBUG
  cout << endl;
#endif
  return true;
}
