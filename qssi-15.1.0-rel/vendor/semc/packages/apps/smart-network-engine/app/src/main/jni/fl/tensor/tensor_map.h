#ifndef FL_TENSOR_MAP_H_
#define FL_TENSOR_MAP_H_

#include <string>
#include <unordered_map>

#include "tensor.h"

namespace fl {

class TensorMap {
    private:
        std::unordered_map<std::string, std::shared_ptr<Tensor>> tensorMap{};

    public:
        void set(const std::string& key, const std::shared_ptr<fl::Tensor>& tensor);
        std::shared_ptr<fl::Tensor> get(const std::string& key) const;
        std::string toJsonString() const;

    public:
        static TensorMap* newInstance();
        static TensorMap* fromJsonString(std::string json);
};

}  // namespace fl

#endif  // FL_TENSOR_MAP_H_
