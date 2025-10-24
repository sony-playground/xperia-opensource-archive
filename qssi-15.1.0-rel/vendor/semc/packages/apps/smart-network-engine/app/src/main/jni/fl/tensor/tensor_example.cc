#include <fstream>
#include <iostream>
#include <memory>

#include "tensor.h"
#include "tensor_map.h"
#include "tensor_shape.h"
#include "data_serializer.h"
#include "data_deserializer.h"

int main()
{
    {
        int scalar_int = 1;
        std::shared_ptr<fl::Tensor> tensor_int(fl::Tensor::newTensor(scalar_int));
        auto value_int = tensor_int.get()->intValue();
        std::cout << "tensor(1): " << value_int << std::endl;
        std::cout << "tensor(1): " << tensor_int.get()->toJsonString() << std::endl;

        float scalar_float = 2.1;
        std::shared_ptr<fl::Tensor> tensor_float(fl::Tensor::newTensor(scalar_float));
        auto value_float = tensor_float.get()->floatValue();
        std::cout << "tensor(2.1): " << value_float << std::endl;
        std::cout << "tensor(2.1): " << tensor_float.get()->toJsonString() << std::endl;

        std::string scalar_string = "hello";
        std::shared_ptr<fl::Tensor> tensor_string(fl::Tensor::newTensor(scalar_string));
        auto value_string = tensor_string.get()->textValue();
        std::cout << "tensor(\"hello\"): " << value_string << std::endl;
        std::cout << "tensor(\"hello\"): " << tensor_string.get()->toJsonString() << std::endl;
    }

    {
        std::shared_ptr<fl::TensorShape> shape1(fl::TensorShape::createShape("shape#102", {2}));
        std::cout << "build shared_ptr 102" << std::endl;

        std::vector<int> vector_int { 101, 102 };
        std::shared_ptr<fl::Tensor> tensor_int(fl::Tensor::newTensor(vector_int, shape1));
        auto output_int = tensor_int.get()->intVector();
        std::cout << "tensor(101, 102): {" << output_int[0] << ", " << output_int[1] << "}" << std::endl;
        std::cout << "tensor(101, 102): " << tensor_int.get()->toJsonString() << std::endl;

        std::vector<float> vector_float { 101.1, 101.2 };
        std::shared_ptr<fl::Tensor> tensor_float(fl::Tensor::newTensor(vector_float, shape1));
        auto output_float = tensor_float.get()->floatVector();
        std::cout << "tensor(101.1, 101.2): {" << output_float[0] << ", " << output_float[1] << "}" << std::endl;
        std::cout << "tensor(101.1, 101.2): " << tensor_float.get()->toJsonString() << std::endl;

        std::vector<std::string> vector_string { "hello", "everyone" };
        std::shared_ptr<fl::Tensor> tensor_string(fl::Tensor::newTensor(vector_string, shape1));
        auto output_string = tensor_string.get()->textVector();
        std::cout << "tensor(\"hello\", \"everyone\"): {" << output_string[0] << ", " << output_string[1] << "}" << std::endl;
        std::cout << "tensor(\"hello\", \"everyone\"): " << tensor_string.get()->toJsonString() << std::endl;
    }

    {
        std::shared_ptr<fl::TensorShape> shape2(fl::TensorShape::createShape("shape#102", {2, 3}));
        std::vector<std::string> vector_string { "r1c1", "r1c2", "r1c3", "r2c1", "r2c2", "r2c3" };
        std::shared_ptr<fl::Tensor> tensor_string(fl::Tensor::newTensor(vector_string, shape2));

        std::vector<float> vector_float { 1.1, 1.2, 1.3, 2.1, 2.2, 2.3 };
        std::shared_ptr<fl::Tensor> tensor_float(fl::Tensor::newTensor(vector_float, shape2));

        std::cout << "### tensor_string.dims(): " << tensor_string.get()->dims() << std::endl;
        std::cout << "### tensor_string.getDim(0): " << tensor_string.get()->getDim(0) << std::endl;
        std::cout << "### tensor_string.getDim(1): " << tensor_string.get()->getDim(1) << std::endl;
        if (tensor_string.get()->isSameSize(*tensor_float.get())) {
            std::cout << "### tensor_string.size == tensor_float.size" << std::endl;
        } else {
            std::cout << "### tensor_string.size != tensor_float.size" << std::endl;
        }
        std::cout << "### tensor_string.size(): " << tensor_string.get()->size() << std::endl;
        for (auto dim: tensor_string.get()->getDims()) {
            std::cout << "### tensor_string.getDims(): " << dim << std::endl;
        }
    }

    {
        std::string jsonString;
        std::ifstream input_file("tensor/sample.json");
        std::getline(input_file, jsonString);
        // std::cout << jsonString << std::endl;

        std::shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::fromJsonString(jsonString));
        //  std::shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::newInstance());

        float scalar_float = 1.23;
        std::shared_ptr<fl::Tensor> tensor_scalar_float(fl::Tensor::newTensor(scalar_float));
        tensor_map->set("float_value", tensor_scalar_float);
	auto dims1 = tensor_scalar_float->dims();
        std::cerr << "float_value: dims: " << dims1 << std::endl;

        std::shared_ptr<fl::TensorShape> shape2(fl::TensorShape::createShape({2, 3}));

        std::vector<float> vector_float { 111.1, 111.2, 111.3, 222.1, 222.2, 222.3 };
        std::shared_ptr<fl::Tensor> tensor_vector_float(fl::Tensor::newTensor(vector_float, shape2));
        tensor_map->set("float_array", tensor_vector_float);
	auto dims2 = tensor_vector_float->dims();
        std::cerr << "float_array: dims: " << dims2 << std::endl;

        std::shared_ptr<fl::Tensor> tensorA = tensor_map->get("float_value");
        if (tensorA) {
            auto output_scalar_float = tensorA->floatValue();
            std::cerr << "tensorA(\"float_value\"): " << output_scalar_float << std::endl;
	    auto dims = tensorA->dims();
            std::cerr << "tensorA(\"float_value\"): dims: " << dims << std::endl;
        }

        std::shared_ptr<fl::Tensor> tensorB = tensor_map->get("float_array");
        if (tensorB) {
            auto output_vector_float = tensorB->floatVector();
            std::cerr << "tensorB(111.1, 111.2): {" << output_vector_float[0] << ", " << output_vector_float[1] << "}" << std::endl;
	    auto dims = tensorB->dims();
            std::cerr << "tensorB(111.1, 111.2): dims: " << dims << std::endl;
        }

        auto notfound = tensor_map->get("notfound");
        if (notfound == NULL) {
            std::cerr << "notfound notfound!!! success" << std::endl;
        } else {
            std::cerr << "notfound found!!! failed" << std::endl;
        }

        std::cout << tensor_map->toJsonString() << std::endl;

        std::cout << "########## DataSerializer START" << std::endl;
        fl::DataSerializer data_serializer = fl::DataSerializer::createFor("/tmp/data.jsonl", "/tmp/index.txt");
        fl::DataMetadata data_metadata = data_serializer.getMetadata();
        fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
        if (data_deserializer.wasSaved(data_metadata)) {
            std::cout << "was saved" << std::endl;
        } else {
            std::cout << "was not saved" << std::endl;
        }
        data_serializer.save(*(tensor_map.get()));
        data_metadata = data_serializer.getMetadata();
        data_deserializer = fl::DataDeserializer::createFor(data_metadata);
        if (data_deserializer.wasSaved(data_metadata)) {
            std::cout << "was saved" << std::endl;
        } else {
            std::cout << "was not saved" << std::endl;
        }
        data_serializer.save(*(tensor_map.get()));
        data_serializer.close();
        data_metadata = data_serializer.getMetadata();
        std::string data_file = data_metadata.get("tensor_map_file");
        std::string index_file = data_metadata.get("tensor_map_index_file");
        std::string save_result = data_metadata.get("save_result");
        std::cout << "MetaData [" << data_file << "][" << index_file << "][" << save_result << "]" << std::endl;
        data_deserializer = fl::DataDeserializer::createFor(data_metadata);
        if (data_deserializer.wasSuccess(data_metadata)) {
            std::cout << "was success" << std::endl;
        } else {
            std::cout << "was failed" << std::endl;
        }
        if (data_deserializer.wasSaved(data_metadata)) {
            std::cout << "was saved" << std::endl;
        } else {
            std::cout << "was not saved" << std::endl;
        }

        fl::DataSerializer xxx = fl::DataSerializer::createFor("/foo/bar/data.jsonl", "/foo/bar/index.txt");
        std::cout << "########## DataSerializer END" << std::endl;

        std::cout << "########## DataDeserializer START" << std::endl;
        data_deserializer = fl::DataDeserializer::createFor(data_metadata);
        int num_of_data = data_deserializer.getNumOfData();
        std::cout << "getNumOfData: " << num_of_data << std::endl;
        tensor_map = data_deserializer.get(1);
        std::cout << "#1: " << tensor_map->toJsonString() << std::endl;
        tensor_map = data_deserializer.get(2);
        std::cout << "#2: " << tensor_map->toJsonString() << std::endl;
        std::cout << "########## DataDeserializer END" << std::endl;

        std::shared_ptr<fl::Tensor> X = tensor_map->get("x");
        std::cerr << "X" << " ";
        for (auto& v: X->floatVector()) {
            std::cerr << v << " ";
        }
        std::cerr << std::endl;
    }

    {
        std::cout << "================================================================================" << std::endl;
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape("shape#1", {2, 3}));
        std::cout << "= dims: " << shape->dims() << std::endl;
        std::cout << "= dims[0]: " << shape->getDim(0) << std::endl;
        std::cout << "= dims[1]: " << shape->getDim(1) << std::endl;
        std::cout << "= size: " << shape->size() << std::endl;

        std::cout << "================================================================================" << std::endl;
        std::shared_ptr<fl::TensorShape> otherA(fl::TensorShape::createShape("shape#2", {2, 3}));
        if (shape->isSameSize(*otherA))
            std::cout << "= same" << std::endl;
        else
            std::cout << "= not same" << std::endl;

        std::cout << "================================================================================" << std::endl;
        std::shared_ptr<fl::TensorShape> otherB(fl::TensorShape::createShape("shape#3", {3, 2}));
        if (shape->isSameSize(*otherB))
            std::cout << "= same" << std::endl;
        else
            std::cout << "= not same" << std::endl;
    }

    return 0;
}
