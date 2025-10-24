#include "evaluation/evaluation.h"

namespace fl {

Evaluator::Evaluator(const std::string& folder_path) :
 _serializer(DataSerializer::createFor(folder_path + Evaluator::JSON_LINES_FILE_NAME, folder_path + Evaluator::INDEX_FILE_NAME))
{
}

Evaluator Evaluator::createFor(const std::string& file_name) {
    return Evaluator(file_name);
}

void Evaluator::addResult(std::shared_ptr<Tensor> label, std::shared_ptr<Tensor> predict_result) {
    std::shared_ptr<fl::TensorMap> tensor_map 
            = std::shared_ptr<fl::TensorMap>(fl::TensorMap::newInstance());
    tensor_map->set(Evaluator::KEY_OF_TARGET, label);
    tensor_map->set(Evaluator::KEY_OF_PREDICTION_RESULT, predict_result);
    this->_serializer.save(*tensor_map);
}

DataMetadata Evaluator::getRawResult() const {
    return this->_serializer.getMetadata();
}

const std::string Evaluator::KEY_OF_TARGET = "y";
const std::string Evaluator::KEY_OF_PREDICTION_RESULT = "y_pred";
const std::string Evaluator::JSON_LINES_FILE_NAME = "/Evaluation_Result.jsonl";
const std::string Evaluator::INDEX_FILE_NAME = "/Evaluation_Result.txt";

}
