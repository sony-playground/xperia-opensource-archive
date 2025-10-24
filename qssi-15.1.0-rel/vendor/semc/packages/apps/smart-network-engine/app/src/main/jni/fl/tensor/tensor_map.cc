#include <fstream>
#include <iostream>

#include "tensor_map.h"
#include "tensor_shape.h"
#include "FLException.h"

namespace fl {

TensorMap* TensorMap::newInstance() {
    return new TensorMap();
}

TensorMap* TensorMap::fromJsonString(std::string jsonString) {
    TensorMap* me = new TensorMap();
    json json_ = json::parse(jsonString);
    for (json::iterator it = json_.begin(); it != json_.end(); ++it) {
        std::shared_ptr<Tensor> tensor(Tensor::fromJson(it.value()));
        me->set(it.key(), tensor);
    }
    return me;
}

std::string TensorMap::toJsonString() const {
    auto json_ = R"({})"_json;
    for (const auto &item : this->tensorMap) {
        std::shared_ptr<Tensor> tensor = item.second;
        if (tensor != NULL) {
            json_[item.first] = tensor->toJson();
        }
    }
    return json_.dump();
}

void TensorMap::set(const std::string& key, const std::shared_ptr<fl::Tensor>& tensor) {
    this->tensorMap[key] = tensor;
}

std::shared_ptr<fl::Tensor> TensorMap::get(const std::string& key) const {
    if (this->tensorMap.find(key) == this->tensorMap.end()) {
        return NULL;
    }
    return this->tensorMap.at(key);
}

}  // namespace fl
