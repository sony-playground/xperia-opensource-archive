#include "LinearHLCR/LinearHLCR_JNIF.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "FLException.h"
#include "tensor/tensor_map.h"
#include "evaluation/evaluation.h"

#ifdef DEBUG
#define DEBUG_MSG(str) { std::cerr << "file:" << __FILE__ << " line:" << __LINE__ << ":" << str << std::endl; }
#else
#define DEBUG_MSG(str) { } 
#endif

namespace linear_hlcr {

#define DESCRIPTION(s)  LinearHLCR_JNIF::description(s, __FILE__, __LINE__)

std::string LinearHLCR_JNIF::description(const std::string what, const std::string file, const int line)
{
    // return str_format("%s [%s:%d]", what, file, line);
    return what + ">>[" + file + ":" + std::to_string(line) + "]";
}

long LinearHLCR_JNIF::Initialize(const json jsonParams)
{
    try {
        DEBUG_MSG("##### LinearHLCR_JNIF::Initialize");
        DEBUG_MSG(std::string("##### Params\n") + jsonParams.dump(2));
        json global_model_json = jsonParams["parameters"]["server"];
        json internal_model_json = jsonParams["parameters"]["internal"];

        std::unique_ptr<linear_hlcr::LinearHLCRGlobalModel> global_model_ptr 
            = linear_hlcr::LinearHLCRGlobalModel::fromJson(global_model_json);

        std::unique_ptr<linear_hlcr::LinearHLCRInternalModel> internal_model_ptr;
        if (!internal_model_json["clusterMap"].is_null()) {
            internal_model_ptr 
                = linear_hlcr::LinearHLCRInternalModel::fromJson(internal_model_json);
        } else {
            internal_model_ptr
                = linear_hlcr::LinearHLCRInternalModel::createInitialInternalModel(global_model_ptr->getK());
        }

        linear_hlcr::LinearHLCR* model_ptr 
            = linear_hlcr::LinearHLCR::create(std::move(global_model_ptr), std::move(internal_model_ptr));

        return (long)(model_ptr);
    }
    catch (FLException& ex) {
        DEBUG_MSG(std::string("Caught FLException: ") + ex.what());
        return 0L;
    }
    catch (json::exception& ex) {
        DEBUG_MSG(std::string("Caught json::exception [") + ex.what() + std::string("]"));
        return 0L;
    }
    catch (...) {
        DEBUG_MSG("Caught unknown exception");
        return 0L;
    }
}

json LinearHLCR_JNIF::Training(linear_hlcr::LinearHLCR* model_ptr, const json jsonParams)
{
    try {
        DEBUG_MSG("##### LinearHLCR_JNIF::Training");
        DEBUG_MSG(std::string("##### Params\n") + jsonParams.dump(2));

    /*
--  {
--    "method": "Training",
--    "parameters": {
--      "server": {
--        "hyperParams": "aaa",
--        "output": "bbb"
--      },
--      "client": {
--        "dataSet": "{\"save_result\":\"eee\",\"tensor_map_file\":\"ccc\",\"tensor_map_index_file\":\"ddd\"}",
--        "output": "fff"
--      }
--    }
--  }
     */

        fl::DataMetadata data_metadata = fl::DataMetadata::fromJsonString(jsonParams["parameters"]["client"]["dataSet"]);

        json server_json = jsonParams["parameters"]["server"];
        std::unique_ptr<linear_hlcr::LinearHLCRTrainHyperParams> train_hyper_params_ptr 
            = linear_hlcr::LinearHLCRTrainHyperParams::fromJson(server_json);

        std::string server_output = jsonParams["parameters"]["server"]["output"].get<std::string>();
        std::string client_output = jsonParams["parameters"]["client"]["output"].get<std::string>();

        auto train_result = model_ptr->train(data_metadata, *train_hyper_params_ptr);
        std::shared_ptr<json> local_model_json = train_result.first->save(server_output);
        std::shared_ptr<json> cluster_map_json = train_result.second->save(client_output);
        auto loss = model_ptr->calcLoss(data_metadata);
        std::string validation_file_path = server_output + "/validation_metrix.dat"; // TODO : remove hard-coding
        std::ofstream ofs(validation_file_path);
        ofs << loss->toJsonString();

        auto jsonResults = R"(
            {
              "method": "Training",
              "results": {
                "state": 0,
                "server": {
                  "linearModels": [
                    "aaa",
                    "bbb"
                  ],
                  "localCount": "ccc",
                  "validationMetrix": "ddd"
                },
                "client": {
                  "clusterMap": "eee"
                }
              }
            }
        )"_json;
    
        jsonResults["results"]["server"] = *local_model_json;
        jsonResults["results"]["server"]["validationMetrix"] = validation_file_path;
        jsonResults["results"]["client"] = *cluster_map_json;
        DEBUG_MSG(std::string("##### Results\n") + jsonResults.dump(2));

        return jsonResults;
    }
    catch (FLException& ex) {
        DEBUG_MSG(std::string("Caught FLException: ") + ex.what());
        auto errorResults = R"({"method":"Training","results":{"state":1,"description":"unknown"}})"_json;
        errorResults["results"]["description"] = DESCRIPTION(ex.what());
        return errorResults;
    }
    catch (json::exception& ex) {
        DEBUG_MSG(std::string("Caught json::exception [") + ex.what() + std::string("]"));
        auto errorResults = R"({"method":"Training","results":{"state":1,"description":"unknown"}})"_json;
        errorResults["results"]["description"] = DESCRIPTION(ex.what());
        return errorResults;
    }
    catch (...) {
        DEBUG_MSG("Caught unknown exception");
        auto errorResults = R"({"method":"Training","results":{"state":1,"description":"unknown"}})"_json;
        return errorResults;
    }
}

json LinearHLCR_JNIF::Evaluation(linear_hlcr::LinearHLCR* model_ptr, const json jsonParams)
{
    try {
        DEBUG_MSG("##### LinearHLCR_JNIF::Evaluation");
        DEBUG_MSG(std::string("##### Params\n") + jsonParams.dump(2)); 

    /*
--  {
--    "method": "Evaluation",
--    "parameters": {
--      "server": {
--        "output": "ddd"
--      },
--      "client": {
--        "dataSet": "{\"save_result\":\"ccc\",\"tensor_map_file\":\"aaa\",\"tensor_map_index_file\":\"bbb\"}",
--      }
--    }
--  }
     */
        auto server_output = jsonParams["parameters"]["server"]["output"].get<std::string>();

        fl::DataMetadata data_metadata = fl::DataMetadata::fromJsonString(jsonParams["parameters"]["client"]["dataSet"]);
        fl::DataDeserializer deserializer = fl::DataDeserializer::createFor(data_metadata);
        int N = deserializer.getNumOfData();

        fl::Evaluator evaluator = fl::Evaluator::createFor(server_output);

        for (int n = 1; n <= N; n++) {
            std::shared_ptr<fl::TensorMap> tensor_map = deserializer.get(n);
            std::shared_ptr<fl::TensorMap> predict_result = model_ptr->predict(*tensor_map);
            evaluator.addResult(
                tensor_map->get(linear_hlcr::LinearHLCR::KEY_OF_TARGET), 
                predict_result->get(linear_hlcr::LinearHLCR::KEY_OF_PREDICTION_RESULT));
        }

        auto jsonResults = R"(
            {
              "method": "Evaluation",
              "results": {
                "state": 0,
                "server": {
                  "evaluationResult": "aaa"
                }
              }
            }
        )"_json;
        jsonResults["results"]["server"]["evaluationResult"] = evaluator.getRawResult().toJsonString();
        DEBUG_MSG(std::string("##### Results\n") + jsonResults.dump(2));

        return jsonResults;
    }
    catch (FLException& ex) {
        DEBUG_MSG(std::string("Caught FLException: ") + ex.what());
        auto errorResults = R"({"method":"Evaluation","results":{"state":1,"description":"unknown"}})"_json;
        errorResults["results"]["description"] = DESCRIPTION(ex.what());
        return errorResults;
    }
    catch (json::exception& ex) {
        DEBUG_MSG(std::string("Caught json::exception [") + ex.what() + std::string("]"));
        auto errorResults = R"({"method":"Evaluation","results":{"state":1,"description":"unknown"}})"_json;
        errorResults["results"]["description"] = DESCRIPTION(ex.what());
        return errorResults;
    }
    catch (...) {
        DEBUG_MSG("Caught unknown exception");
        auto errorResults = R"({"method":"Evaluation","results":{"state":1,"description":"unknown"}})"_json;
        return errorResults;
    }
}

json LinearHLCR_JNIF::Prediction(linear_hlcr::LinearHLCR* model_ptr, const json jsonParams)
{
    try {
        DEBUG_MSG("##### LinearHLCR_JNIF::Prediction");
        DEBUG_MSG(std::string("##### Params\n") + jsonParams.dump(2));

        std::shared_ptr<fl::TensorMap> data(fl::TensorMap::fromJsonString(jsonParams["parameters"]["application"]["data"]));
    /*
--  {
--    "method": "Prediction",
--    "parameters": {
--      "application": {
--        "data": "{\"actualTensor\":{\"shape\":[2,3],\"value\":[1.100000023841858,1.2000000476837158,1.2999999523162842,2.0999999046325684,2.200000047683716,2.299999952316284]}}"
--      }
--    }
--  }
     */

        std::shared_ptr<fl::TensorMap> result = model_ptr->predict(*data);

        auto jsonResults = R"(
            {
              "method": "Prediction",
              "results": {
                "state": 0,
                "application": {
                  "predictionResult": ""
                }
              }
            }
        )"_json;
        jsonResults["results"]["application"]["predictionResult"] = result->toJsonString();
        DEBUG_MSG(std::string("##### Results\n") + jsonResults.dump(2));

        return jsonResults;
    }
    catch (FLException& ex) {
        DEBUG_MSG(std::string("Caught FLException: ") + ex.what());
        auto errorResults = R"({"method":"Prediction","results":{"state":1,"description":"unknown"}})"_json;
        errorResults["results"]["description"] = DESCRIPTION(ex.what());
        return errorResults;
    }
    catch (json::exception& ex) {
        DEBUG_MSG(std::string("Caught json::exception [") + ex.what() + std::string("]"));
        auto errorResults = R"({"method":"Prediction","results":{"state":1,"description":"unknown"}})"_json;
        errorResults["results"]["description"] = DESCRIPTION(ex.what());
        return errorResults;
    }
    catch (...) {
        DEBUG_MSG("Caught unknown exception");
        auto errorResults = R"({"method":"Prediction","results":{"state":1,"description":"unknown"}})"_json;
        return errorResults;
    }
}

void LinearHLCR_JNIF::Finalize(linear_hlcr::LinearHLCR* model_ptr)
{
    if (model_ptr != 0) {
        delete model_ptr;
    }
}

json LinearHLCR_JNIF::UpdateInfo(linear_hlcr::LinearHLCR* model_ptr, const json jsonParams)
{
    try {
        DEBUG_MSG("##### LinearHLCR_JNIF::UpdateInfo");
        DEBUG_MSG(std::string("##### Params\n") + jsonParams.dump(2));

        fl::DataMetadata data_metadata = fl::DataMetadata::fromJsonString(jsonParams["parameters"]["client"]["dataSet"]);

        json update_hyper_params_json = jsonParams["parameters"]["server"];
        std::unique_ptr<linear_hlcr::LinearHLCRUpdateHyperParams> update_hyper_params_ptr 
            = linear_hlcr::LinearHLCRUpdateHyperParams::fromJson(update_hyper_params_json);

    /*
--  {
--    "method": "UpdateInfo",
--    "parameters": {
--      "client": {
--        "dataSet": "{\"save_result\":\"ccc\",\"tensor_map_file\":\"aaa\",\"tensor_map_index_file\":\"bbb\"}",
--        "hyperParams": "ddd",
--        "output": "eee"
--      }
--    }
--  }
     */

        std::unique_ptr<linear_hlcr::LinearHLCRInternalModel> new_internal_model_ptr 
            = model_ptr->updateInternalModel(data_metadata, *update_hyper_params_ptr);
        auto client_output = jsonParams["parameters"]["client"]["output"].get<std::string>();
        std::shared_ptr<json> save_result_ptr = new_internal_model_ptr->save(client_output);
        model_ptr->setInternalModel(std::move(new_internal_model_ptr));

        auto jsonResults = R"(
            {
              "method": "UpdateInfo",
              "results": {
                "state": 0,
                "client": {
                  "clusterMap": ""
                }
              }
            }
        )"_json;
        jsonResults["results"]["client"] = *save_result_ptr;
        DEBUG_MSG(std::string("##### Results\n") + jsonResults.dump(2));

        return jsonResults;
    }
    catch (FLException& ex) {
        DEBUG_MSG(std::string("Caught FLException: ") + ex.what());
        auto errorResults = R"({"method":"UpdateInfo","results":{"state":1,"description":"unknown"}})"_json;
        errorResults["results"]["description"] = DESCRIPTION(ex.what());
        return errorResults;
    }
    catch (json::exception& ex) {
        DEBUG_MSG(std::string("Caught json::exception [") + ex.what() + std::string("]"));
        auto errorResults = R"({"method":"UpdateInfo","results":{"state":1,"description":"unknown"}})"_json;
        errorResults["results"]["description"] = DESCRIPTION(ex.what());
        return errorResults;
    }
    catch (...) {
        DEBUG_MSG("Caught unknown exception");
        auto errorResults = R"({"method":"UpdateInfo","results":{"state":1,"description":"unknown"}})"_json;
        return errorResults;
    }
}
} // namespace linear_hlcr
