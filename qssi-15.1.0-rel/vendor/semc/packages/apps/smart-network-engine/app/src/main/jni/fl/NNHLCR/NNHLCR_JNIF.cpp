/**
 * reference
 * https://docs.oracle.com/javase/jp/8/docs/technotes/guides/jni/spec/functions.html#Get_PrimitiveType_ArrayElements_routines
 **/

#include <float.h>
#include <vector>
#include <string>
#include "FLException.h"
#include "NNHLCR/NNHLCR_file_IO.h"
#include "NNHLCR/lstm_lcr_model_nnabla.h"
#include "NNHLCR/data_normalizer.h"
#include "tensor/tensor.h"
#include "tensor/tensor_map.h"
#include "tensor/data_metadata.h"

#include "NNHLCR/NNHLCR_JNIF.h"

//#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(str) { std::cerr << "file:" << __FILE__ << " line:" << __LINE__ << ":" << str << std::endl; }
#else
#define DEBUG_MSG(str) { } 
#endif

namespace nn_hlcr {

long NNHLCR_JNIF::Initialize(const char* modelInfo)
{
	try {
		DEBUG_MSG("##### NNHLCR_JNIF::Initialize");
		ConstructorInputs ci = ConstructorInputs(std::string(modelInfo));
		if (!(ci.isValid)) {
			DEBUG_MSG(std::string(modelInfo));
			DEBUG_MSG("jModelInfo is not parsed correctly.");
			return 0L;
		}
		int ret;
		LstmLCRModel* mlObj = NULL;
		try {
			mlObj = new LstmLCRModel();
			ret = mlObj->initialize(
					ci.K, ci.nntxt_files, ci.protobuf_files, ci.global_weights, ci.cluster_map,
					ci.max_length, ci.num_of_normalized_features);
		} catch (exception& ex) {
			ret = -1;
			DEBUG_MSG(ex.what());
		}
		if (ret != 0) {
			DEBUG_MSG("initialize is failed.");
			if (mlObj != NULL) delete mlObj;
			return 0L;
		}
		DEBUG_MSG(std::string("Pointer of mlObj is ") + std::to_string((long)mlObj));
		return (long)mlObj;
	}
//	catch (FLException& ex) {
//		DEBUG_MSG(std::string("Caught FLException: ") + ex.what());
//		return (long)-1;
//	}
//	catch (json::exception& ex) {
//		DEBUG_MSG(std::string("Caught json::exception [") + ex.what() + std::string("]"));
//		return (long)-1;
//	}
	catch (...) {
		DEBUG_MSG("Caught unknown exception");
		return 0L;
	}
}

std::string NNHLCR_JNIF::Training(LstmLCRModel* mlObj, const char* metaDataJson, const char* trainInfo)
{
	try {
		DEBUG_MSG("##### NNHLCR_JNIF::Training");

		DEBUG_MSG(std::string("DataMetadata: ") + std::string(metaDataJson));

		fl::DataMetadata metaData = fl::DataMetadata::fromJsonString(std::string(metaDataJson));

		DEBUG_MSG("deserialize complete");

		TrainInputs ti = TrainInputs(metaData, std::string(trainInfo), mlObj->n_components);
		if (!(ti.isValid)) {
			DEBUG_MSG("jTrainInfo is not parsed correctly.");
			return "";
		}

		if (mlObj->max_len < ti.getMaxLength()) {
			DEBUG_MSG(std::to_string(mlObj->max_len) + std::string(" < ") + std::to_string(ti.getMaxLength()));
			return "";
		}

		DataNormalizer dn;
		shared_ptr<float> normalized_data(new float[ti.num_of_data * mlObj->max_len * mlObj->n_features], default_delete<float[]>());
		for (int i=0;i < ti.num_of_data * mlObj->max_len * mlObj->n_features;i++) normalized_data.get()[i] = -1.0f;
		bool flag = true;
		for (int i = 0; i < ti.num_of_data; i++) {
			for (int j = 0; j <= ti.lengths.get()[i]; j++) {
				flag &= dn.normalize_all_features(
						ti.num_of_features,
						mlObj->n_features,
						ti.x.get() + (i * ti.getMaxLength() * ti.num_of_features + j * ti.num_of_features), 
						normalized_data.get() + (i * mlObj->max_len * mlObj->n_features + j * mlObj->n_features));
			}
		}

		if (!flag) {
			DEBUG_MSG("normalizeation is failed.");
			return "";
		}

		vector<std::string> u(ti.num_of_data);
		for (int i=0;i<ti.num_of_data;i++) u[i] = "";
		mlObj->set_parameters(ti.alpha, ti.beta, ti.delta, ti.sigma,
				ti.num_of_epoch, ti.batch_size, ti.learning_rate);
		int ret = 0;
		try {
			ret = mlObj->train(normalized_data.get(), ti.y.get(), 
					ti.groupLabel.get(), u.data(), ti.lengths.get(), 
					ti.num_of_data, ti.getMaxLength(), mlObj->n_features);
		} catch (exception& ex) {
			ret = -1;
			DEBUG_MSG(ex.what());
		}
	
		if (ret != 0) {
			DEBUG_MSG("train is failed.");
			return "";
		}

		mlObj->saveNNModels(ti.output_nn_files);
		mlObj->saveLCRParams(ti.output_lcr_file);
		mlObj->saveClusterMap(ti.output_cluster_map_file);
		TrainOutputs to;
		to.saveValidationResults(ti.output_valid_file, ti.num_of_data ,mlObj->loss);

		int K = mlObj->n_components;

		std::string msg = to_string(K) + "\n";
		for (int k = 0;k < K;k++) {
			msg += ti.NN_FILE_PREFIX + to_string(k+1) + ti.NN_FILE_EXTENSION + "\n";
		}
		msg += ti.LCR_FILE_NAME + "\n";
		msg += ti.VALIDATION_FILE_NAME + "\n";
		msg += ti.CLUSTER_MAP_FILE_NAME;

		DEBUG_MSG("train is finished.");
		DEBUG_MSG(msg);
		return msg;
	}
//	catch (FLException& ex) {
//		DEBUG_MSG(std::string("Caught FLException: ") + ex.what());
//		return "";
//	}
//	catch (json::exception& ex) {
//		DEBUG_MSG(std::string("Caught json::exception [") + ex.what() + std::string("]"));
//		return "";
//	}
	catch (...) {
		DEBUG_MSG("Caught unknown exception");
		return "";
	}
}

std::string NNHLCR_JNIF::Evaluation(LstmLCRModel* mlObj, const char* metaDataJson, const char* evaluationInfo)
{
	try {
		DEBUG_MSG("##### NNHLCR_JNIF::Evaluation");

		DEBUG_MSG(std::string("DataMetadata: ") + std::string(metaDataJson));

		fl::DataMetadata metaData = fl::DataMetadata::fromJsonString(std::string(metaDataJson));

		DEBUG_MSG("deserialize complete");

		EvaluationInputs ei = EvaluationInputs(metaData, std::string(evaluationInfo));
		if (!(ei.isValid)) {
			DEBUG_MSG("jEvaluationInfo is not parsed correctly.");
			return "";
		}

		if (mlObj->max_len < ei.getMaxLength()) {
			DEBUG_MSG(std::to_string(mlObj->max_len) + std::string(" < ") + std::to_string(ei.getMaxLength()));
			return "";
		}

		DataNormalizer dn;
		vector<float> normalized_data(ei.num_of_data * mlObj->max_len * mlObj->n_features);
		for (int i=0;i < ei.num_of_data * mlObj->max_len * mlObj->n_features;i++) normalized_data[i] = -1.0f;
		bool flag = true;
		for (int i = 0; i < ei.num_of_data; i++) {
			for (int j = 0; j <= ei.lengths.get()[i]; j++) {
				flag &= dn.normalize_all_features(
						ei.num_of_features,
						mlObj->n_features,
						ei.x.get() + (i * ei.getMaxLength() * ei.num_of_features + j * ei.num_of_features), 
						normalized_data.data() + (i * mlObj->max_len * mlObj->n_features + j * mlObj->n_features));
			}
		}

		if (!flag) {
			DEBUG_MSG("normalizeation is failed.");
			return "";
		}

		vector<float> ret(ei.num_of_data);
		vector<std::string> u(ei.num_of_data);
		for (int i=0;i<ei.num_of_data;i++) u[i] = "";
		int isSuccess;
		try {
			isSuccess = mlObj->predict(normalized_data.data(), ei.groupLabel.get(), u.data(), ei.lengths.get(), 
					ret.data(), ei.num_of_data, mlObj->max_len, mlObj->n_features);
		} catch (exception& ex) {
			isSuccess = -1;
			DEBUG_MSG(ex.what());
		}

		if (isSuccess != 0) {
			DEBUG_MSG("predict is failed.");
			return "";
		}

		EvaluationOutputs eo;
		if (!eo.saveEvaluationResults(ei.output_eval_file, ei.num_of_data , ei.y.get(), ret.data())) {
			DEBUG_MSG("saveEvaluationResults is faild.");
			return "";
		}
		return ei.EVALUATION_RESULT_FILE_NAME;
	}
//	catch (FLException& ex) {
//		DEBUG_MSG(std::string("Caught FLException: ") + ex.what());
//		return "";
//	}
//	catch (json::exception& ex) {
//		DEBUG_MSG(std::string("Caught json::exception [") + ex.what() + std::string("]"));
//		return "";
//	}
	catch (...) {
		DEBUG_MSG("Caught unknown exception");
		return "";
	}
}

float NNHLCR_JNIF::Prediction(LstmLCRModel* mlObj, const char* tensorMapJson)
{
	try {
		DEBUG_MSG("##### NNHLCR_JNIF::Prediction");
		//
		shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::fromJsonString(tensorMapJson));

		//
		shared_ptr<fl::Tensor> ts_num_of_features = tensor_map->get("num_of_features");
		if (!ts_num_of_features) {
			DEBUG_MSG("no num_of_features");
			return -FLT_MAX;
		}
		const int num_of_features = ts_num_of_features->intValue();

		//
		shared_ptr<fl::Tensor> ts_dataSequence = tensor_map->get("sequence_data");
		if (!ts_dataSequence) {
			DEBUG_MSG("no sequence_data");
			return -FLT_MAX;
		}
		const int num_of_dimensions = ts_dataSequence.get()->dims();
		if (num_of_dimensions != 2) {
			DEBUG_MSG(std::string("num of dimensions is invalid. ") + std::to_string(num_of_dimensions));
			return -FLT_MAX;
		}

		//
		const int data_size = ts_dataSequence->size();
		if (data_size < 0) {
			DEBUG_MSG("Integer over flow");
			return -FLT_MAX;
		}

		//
		int data_length = data_size / num_of_features;
		vector<float> floatVector = ts_dataSequence->floatVector();
		float dataSequence[data_size];
		copy(floatVector.begin(), floatVector.end(), dataSequence);

#ifdef DEBUG
		cout << "num_of_features: " << num_of_features << endl;
		cout << "num_of_dimensions: " << num_of_dimensions << endl;
		cout << "data_size: " << data_size << endl;
		cout << "data_length: " << data_length << endl;
#endif

		//
		shared_ptr<float> data(new float[data_size], default_delete<float[]>());
		for (int i=0;i<data_size;i++) data.get()[i] = dataSequence[i];
#ifdef DEBUG
		cout << "length : " << data_length << "  , raw features : " << num_of_features << endl;
		cout << "data )" << endl;
		for (int i=0;i<data_length;i++) {
			for (int j=0;j<num_of_features;j++) {
				cout << data.get()[i*num_of_features + j] << " ";
			}
			cout << endl;
		}
#endif

		DataNormalizer dn;
		int normalized_data_size = mlObj->max_len * mlObj->n_features;
		if (normalized_data_size < 0) {
			DEBUG_MSG("Integer over flow");
			return -FLT_MAX;
		}
		shared_ptr<float> normalized_data(new float[normalized_data_size], default_delete<float[]>());
		for (int i=0;i<normalized_data_size;i++) normalized_data.get()[i] = -1.0f;
		bool flag = true;
		for (int i = 0; i < data_length; i++) {
			flag &= dn.normalize_all_features(
					num_of_features,
					mlObj->n_features,
					data.get() + (i * num_of_features), 
					normalized_data.get() + (i * mlObj->n_features));
		}

		if (!flag) {
			DEBUG_MSG("Normalization is failed.");
			return -FLT_MAX;
		}

		shared_ptr<fl::Tensor> ts_groupLabel = tensor_map->get("group_label");
		if (!ts_groupLabel) {
			DEBUG_MSG("no group_label");
			return -FLT_MAX;
		}
		std::string gl[1] = {std::string(ts_groupLabel->textValue())};
		int dl[1] = {(data_length-1)};
		std::string ul[1] = {std::string("")};
		float ret[1];
		int isSuccess;
		try {
			isSuccess = mlObj->predict(normalized_data.get(), (std::string*)gl, (std::string*)ul, (int*)dl, 
					(float*)ret, 1, mlObj->max_len, mlObj->n_features);
		} catch (exception& ex) {
			isSuccess = -1;
			DEBUG_MSG(ex.what());
		}
		if (isSuccess != 0) {
			DEBUG_MSG("Prediction is failed.");
			return -FLT_MAX;
		}
		DEBUG_MSG(std::string("Predicted result is ") + std::to_string(ret[0]));
		return ret[0];
	}
//	catch (FLException& ex) {
//		DEBUG_MSG(std::string("Caught FLException: ") + ex.what());
//		return -FLT_MAX;
//	}
	catch (json::exception& ex) {
		DEBUG_MSG(std::string("Caught json::exception [") + ex.what() + std::string("]"));
		return -FLT_MAX;
	}
	catch (...) {
		DEBUG_MSG("Caught unknown exception");
		return -FLT_MAX;
	}
}

std::string NNHLCR_JNIF::UpdateInfo(LstmLCRModel* mlObj, const char* metaDataJson, const char* updateInfo)
{
	try {
		DEBUG_MSG("##### LinearHLCR_JNIF::UpdateInfo");

		DEBUG_MSG(std::string("DataMetadata: ") + std::string(metaDataJson));

		fl::DataMetadata metaData = fl::DataMetadata::fromJsonString(std::string(metaDataJson));

		DEBUG_MSG("deserialize complete");

		UpdateClusterMapInputs ui = UpdateClusterMapInputs(metaData, std::string(updateInfo));
		if (!(ui.isValid)) {
			DEBUG_MSG("jUpdateInfo is not parsed correctly.");
			return "";
		}

		if (mlObj->max_len < ui.getMaxLength()) {
			DEBUG_MSG(std::to_string(mlObj->max_len) + std::string(" < ") + std::to_string(ui.getMaxLength()));
			return "";
		}

		DataNormalizer dn;
		int normalized_data_size = ui.num_of_data * mlObj->max_len * mlObj->n_features;
		if (normalized_data_size < 0) {
			DEBUG_MSG("Integer over flow");
			return "";
		}
		shared_ptr<float> normalized_data(new float[normalized_data_size], default_delete<float[]>());
		for (int i=0;i < normalized_data_size;i++) normalized_data.get()[i] = -1.0f;
		bool flag = true;
		for (int i = 0; i < ui.num_of_data; i++) {
			for (int j = 0; j <= ui.lengths.get()[i]; j++) {
				flag &= dn.normalize_all_features(
						ui.num_of_features,
						mlObj->n_features,
						ui.x.get() + (i * ui.getMaxLength() * ui.num_of_features + j * ui.num_of_features), 
						normalized_data.get() + (i * mlObj->max_len * mlObj->n_features + j * mlObj->n_features));
			}
		}

		if (!flag) {
			DEBUG_MSG("normalizeation is failed.");
			return "";
		}

		shared_ptr<std::string> u = shared_ptr<std::string>(new std::string[ui.num_of_data], default_delete<std::string[]>());
		for (int i=0;i<ui.num_of_data;i++) u.get()[i] = "";
		int ret;
		try {
			ret = mlObj->update_cluster(normalized_data.get(), ui.y.get(), 
					ui.groupLabel.get(), u.get(), ui.lengths.get(), 
					ui.num_of_data, ui.getMaxLength(), mlObj->n_features);
		}  catch (exception& ex) {
			ret = -1;
			DEBUG_MSG(ex.what());
		}
		if (ret != 0) {
			DEBUG_MSG("update cluster map is failed.");
			return "";
		}

		// TODO  : fix
		UpdateClusterMapOutputs uo;
		uo.saveClusterMap(ui.output_file, mlObj->getClusterMap());

		DEBUG_MSG("update cluster map is finished.");
		DEBUG_MSG(ui.output_file);

		return "ClusterMap.dat";
	}
//	catch (FLException& ex) {
//		DEBUG_MSG(std::string("Caught FLException: ") + ex.what());
//		return "";
//	}
//	catch (json::exception& ex) {
//		DEBUG_MSG(std::string("Caught json::exception [") + ex.what() + std::string("]"));
//		return "";
//	}
	catch (...) {
		DEBUG_MSG("Caught unknown exception");
		return "";
	}
}

void NNHLCR_JNIF::Finalize(LstmLCRModel* mlObj)
{
	if (mlObj != 0) {
		((LstmLCRModel*)mlObj)->finalize();
		delete (LstmLCRModel*)mlObj;
	}
}
} // namespace nn_hlcr
