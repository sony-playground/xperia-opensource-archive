#include "tensor.h"

#include "FLException.h"

namespace fl {

Tensor::Tensor(void) {
    std::shared_ptr<TensorShape> new_shape(TensorShape::createShape("default", {0}));
    this->shape = new_shape;
}

template <typename T>
Tensor::Tensor(std::vector<T>& value, std::shared_ptr<TensorShape> shape, host_vector_tag tag) {
    this->shape = shape;
    this->json_ = value;
}

template <typename T>
Tensor::Tensor(T value, host_scalar_tag tag) {
    std::shared_ptr<TensorShape> new_shape(TensorShape::createShape("shape(scalar)", {1}));
    this->shape = new_shape;
    std::vector<T> new_value {value};
    this->json_ = new_value;
}

Tensor* Tensor::newTensor(int scalar_value) {
    return new Tensor(scalar_value, host_scalar_tag{});
}
Tensor* Tensor::newTensor(long scalar_value) {
    return new Tensor(scalar_value, host_scalar_tag{});
}
// Tensor* Tensor::newTensor(std::int64_t scalar_value) {
//     return new Tensor(scalar_value, host_scalar_tag{});
// }
Tensor* Tensor::newTensor(float scalar_value) {
    return new Tensor(scalar_value, host_scalar_tag{});
}
Tensor* Tensor::newTensor(double scalar_value) {
    return new Tensor(scalar_value, host_scalar_tag{});
}
Tensor* Tensor::newTensor(std::string scalar_value) {
    return new Tensor(scalar_value, host_scalar_tag{});
}
Tensor* Tensor::newTensor(std::vector<int>& vector_value, std::shared_ptr<TensorShape> shape) {
    if (vector_value.size() != shape->size()) { THROW_FL_EXCEPTION(str_format("Failed to create tensor. unmatch size. (%d != %d)", vector_value.size(), shape->size())); }
    return new Tensor(vector_value, shape, host_vector_tag{});
}
Tensor* Tensor::newTensor(std::vector<long>& vector_value, std::shared_ptr<TensorShape> shape) {
    if (vector_value.size() != shape->size()) { THROW_FL_EXCEPTION(str_format("Failed to create tensor. unmatch size. (%d != %d)", vector_value.size(), shape->size())); }
    return new Tensor(vector_value, shape, host_vector_tag{});
}
// Tensor* Tensor::newTensor(std::vector<std::int64_t>& vector_value, std::shared_ptr<TensorShape> shape) {
//     if (vector_value.size() != shape->size()) { THROW_FL_EXCEPTION(str_format("Failed to create tensor. unmatch size. (%d != %d)", vector_value.size(), shape->size())); }
//     return new Tensor(vector_value, shape, host_vector_tag{});
// }
Tensor* Tensor::newTensor(std::vector<float>& vector_value, std::shared_ptr<TensorShape> shape) {
    if (vector_value.size() != shape->size()) { THROW_FL_EXCEPTION(str_format("Failed to create tensor. unmatch size. (%d != %d)", vector_value.size(), shape->size())); }
    return new Tensor(vector_value, shape, host_vector_tag{});
}
Tensor* Tensor::newTensor(std::vector<double>& vector_value, std::shared_ptr<TensorShape> shape) {
    if (vector_value.size() != shape->size()) { THROW_FL_EXCEPTION(str_format("Failed to create tensor. unmatch size. (%d != %d)", vector_value.size(), shape->size())); }
    return new Tensor(vector_value, shape, host_vector_tag{});
}
Tensor* Tensor::newTensor(std::vector<std::string>& vector_value, std::shared_ptr<TensorShape> shape) {
    if (vector_value.size() != shape->size()) { THROW_FL_EXCEPTION(str_format("Failed to create tensor. unmatch size. (%d != %d)", vector_value.size(), shape->size())); }
    return new Tensor(vector_value, shape, host_vector_tag{});
}

int Tensor::intValue() const {
//  return this->getValue<int>();
    return this->intVector().at(0);
}

long Tensor::longValue() const {
//  return this->getValue<long>();
    return this->longVector().at(0);
}

// std::int64_t Tensor::longValue() const {
// //  return this->getValue<std::int64_t>();
//     return this->longVector().at(0);
// }

float Tensor::floatValue() const {
//  return this->getValue<float>();
    return this->floatVector().at(0);
}

double Tensor::doubleValue() const {
//  return this->getValue<double>();
    return this->doubleVector().at(0);
}

std::string Tensor::textValue() const {
//  return this->getValue<std::string>();
    return this->textVector().at(0);
}

std::vector<int> Tensor::intVector() const {
    return this->getValue<std::vector<int>>();
}

std::vector<long> Tensor::longVector() const {
    return this->getValue<std::vector<long>>();
}

// std::vector<std::int64_t> Tensor::longVector() const {
//     return this->getValue<std::vector<std::int64_t>>();
// }

std::vector<float> Tensor::floatVector() const {
    return this->getValue<std::vector<float>>();
}

std::vector<double> Tensor::doubleVector() const {
    return this->getValue<std::vector<double>>();
}

std::vector<std::string> Tensor::textVector() const {
    return this->getValue<std::vector<std::string>>();
}

template <typename T>
T Tensor::getValue() const {
    return this->json_.get<T>();
}

std::string Tensor::toJsonString() const {
    return this->toJson().dump();
}

json Tensor::toJson() const {
    json ret;
    ret = {
        { "shape", this->shape->getDims() },
        { "value", this->json_ }
    };
    return ret;
}

Tensor* Tensor::fromJsonString(std::string jsonString) {
    return Tensor::fromJson(json::parse(jsonString));
}

Tensor* Tensor::fromJson(json jsonObject) {
    std::shared_ptr<TensorShape> shape(TensorShape::createShape(jsonObject["shape"]));
    json value = jsonObject["value"];
    Tensor* tensor = NULL;
    if (value.is_array()) {
//      if (value.size() == 1) {
//          if (value[0].is_number_integer()) {
//              auto scalar = value[0].get<int>();
//              tensor = new Tensor(scalar);
//          } else
//          if (value[0].is_number_float()) {
//              auto scalar = value[0].get<float>();
//              tensor = new Tensor(scalar);
//          } else
//          if (value[0].is_string()) {
//              auto scalar = value[0].get<std::string>();
//              tensor = new Tensor(scalar);
//          }
//      } else {
            if (value[0].is_number_integer()) {
                auto vector = value.get<std::vector<std::int64_t>>();
                tensor = newTensor(vector, shape);
            } else
            if (value[0].is_number_float()) {
                auto vector = value.get<std::vector<double>>();
                tensor = newTensor(vector, shape);
            } else
            if (value[0].is_string()) {
                auto vector = value.get<std::vector<std::string>>();
                tensor = newTensor(vector, shape);
            }
//      }
    }
    
    if (tensor == NULL) {
        std::cerr << "failed to create tensor instance" << std::endl;
        THROW_FL_EXCEPTION(str_format("Failed to create tensor. Unknown json string. (%s)", jsonObject.dump().c_str()));
    }

    return tensor;
}

int Tensor::dims() const {
    return this->shape.get()->dims();
}

int Tensor::getDim(const int d) const {
    return this->shape.get()->getDim(d);
}

bool Tensor::isSameSize(const Tensor& other) const {
    return this->shape.get()->isSameSize(*(other.shape.get()));
}

bool Tensor::isSameSize(const TensorShape& other) const {
    return this->shape.get()->isSameSize(other);
}

int Tensor::size() const {
    return this->shape.get()->size();
}

std::vector<int> Tensor::getDims() const {
    return this->shape.get()->getDims();
}

}  // namespace fl
