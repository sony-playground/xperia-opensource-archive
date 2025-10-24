#ifndef FL_TENSOR_H_
#define FL_TENSOR_H_

#include <cstdint>
#include <iostream>
#include <string.h>
#include <vector>

#include <nlohmann/json.hpp>

#include "tensor_shape.h"

// for convenience
using json = nlohmann::json;

namespace fl {

class Tensor {
    private:
        json json_;
        std::shared_ptr<TensorShape> shape;

        struct host_vector_tag {};
        struct host_scalar_tag {};

    private:
        Tensor(void);

        template <typename T>
        Tensor(std::vector<T>& value, std::shared_ptr<TensorShape> shape, host_vector_tag tag);
        template <typename T>
        Tensor(T value, host_scalar_tag tag);

        // explicit Tensor(std::vector<int>& vector_value, std::shared_ptr<TensorShape> shape)
        //     : Tensor(vector_value, shape, host_vector_tag{}) {}
        // explicit Tensor(std::vector<long>& vector_value, std::shared_ptr<TensorShape> shape)
        //     : Tensor(vector_value, shape, host_vector_tag{}) {}
        explicit Tensor(std::vector<std::int64_t>& vector_value, std::shared_ptr<TensorShape> shape)
            : Tensor(vector_value, shape, host_vector_tag{}) {}
        // explicit Tensor(std::vector<float>& vector_value, std::shared_ptr<TensorShape> shape)
        //     : Tensor(vector_value, shape, host_vector_tag{}) {}
        explicit Tensor(std::vector<double>& vector_value, std::shared_ptr<TensorShape> shape)
            : Tensor(vector_value, shape, host_vector_tag{}) {}
        explicit Tensor(std::vector<std::string>& vector_value, std::shared_ptr<TensorShape> shape)
            : Tensor(vector_value, shape, host_vector_tag{}) {}

        // explicit Tensor(int scalar_value)
        //     : Tensor(scalar_value, host_scalar_tag{}) {}
        // explicit Tensor(long scalar_value)
        //     : Tensor(scalar_value, host_scalar_tag{}) {}
        explicit Tensor(std::int64_t scalar_value)
            : Tensor(scalar_value, host_scalar_tag{}) {}
        // explicit Tensor(float scalar_value)
        //     : Tensor(scalar_value, host_scalar_tag{}) {}
        explicit Tensor(double scalar_value)
            : Tensor(scalar_value, host_scalar_tag{}) {}
        explicit Tensor(std::string& scalar_value)
            : Tensor(scalar_value, host_scalar_tag{}) {}

        template <typename T> T getValue() const;

    public:
        static Tensor* newTensor(int scalar_value);
        static Tensor* newTensor(long scalar_value);
        // static Tensor* newTensor(std::int64_t scalar_value);
        static Tensor* newTensor(float scalar_value);
        static Tensor* newTensor(double scalar_value);
        static Tensor* newTensor(std::string scalar_value);

        static Tensor* newTensor(std::vector<int>& vector_value, std::shared_ptr<TensorShape> shape);
        static Tensor* newTensor(std::vector<long>& vector_value, std::shared_ptr<TensorShape> shape);
        // static Tensor* newTensor(std::vector<std::int64_t>& vector_value, std::shared_ptr<TensorShape> shape);
        static Tensor* newTensor(std::vector<float>& vector_value, std::shared_ptr<TensorShape> shape);
        static Tensor* newTensor(std::vector<double>& vector_value, std::shared_ptr<TensorShape> shape);
        static Tensor* newTensor(std::vector<std::string>& vector_value, std::shared_ptr<TensorShape> shape);

        int intValue() const;
        long longValue() const;
        // std::int64_t longValue() const;
        float floatValue() const;
        double doubleValue() const;
        std::string textValue() const;

        std::vector<int> intVector() const;
        std::vector<long> longVector() const;
        // std::vector<std::int64_t> longVector() const;
        std::vector<float> floatVector() const;
        std::vector<double> doubleVector() const;
        std::vector<std::string> textVector() const;

        static Tensor* fromJsonString(std::string jsonString);
        static Tensor* fromJson(json jsonObject);
        std::string toJsonString() const;
        json toJson() const;

		int dims() const;
		int getDim(const int d) const;
		bool isSameSize(const Tensor& other) const;
		bool isSameSize(const TensorShape& other) const;
		int size() const;
		std::vector<int> getDims() const;
};

}  // namespace fl

#endif  // FL_TENSOR_H_
