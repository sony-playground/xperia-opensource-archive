#include "MatrixAndVector.h"
#include "FLException.h"

namespace linear_hlcr {

SymmetricMatrix::SymmetricMatrix(const std::vector<double>& vec, int d) {
    this->_dim = d;
    this->_matrix = vec; // if we need to avoid this copy, it is good to use pointer of vector.
}

SymmetricMatrix SymmetricMatrix::fromTensor(const fl::Tensor& tensor) {
    std::vector<int> dims = tensor.getDims();
    if (dims.size() != 2) {
        THROW_FL_EXCEPTION(str_format("Invalid tensor dimension. must be 2 (!= %d).", dims.size()));
    }
    if (dims[0] != dims[1]) {
        THROW_FL_EXCEPTION(str_format("Different size of row and column. (%d != %d).", dims[0], dims[1]));
    }
    std::vector<double> data = tensor.doubleVector(); // it may throw json exception

    for (int i = 0; i < dims[0]; i++) {
        for (int j = i+1; j < dims[1]; j++) {
            if (data[i*dims[0]+j] != data[j*dims[0]+i]) {
                THROW_FL_EXCEPTION(str_format("Value does not match. (%f != %f)(i:%d j:%d dims[0]:%d", data[i*dims[0]+j], data[j*dims[0]+i], i, j, dims[0]));
            }
        }
    }
    return SymmetricMatrix(data, dims[0]);
}

SymmetricMatrix SymmetricMatrix::create(const std::vector<double>& data, int dim) {
    if (data.size() != dim * dim) {
        THROW_FL_EXCEPTION(str_format("Data size does not match. (data:%d dim:%d^2).", data.size(), dim));
    }
    for (int i = 0; i < dim; i++) {
        for (int j = i+1; j < dim; j++) {
            if (data[i*dim+j] != data[j*dim+i]) {
                THROW_FL_EXCEPTION(str_format("Value does not match. (%f != %f)(i:%d j:%d dim:%d", data[i*dim+j], data[j*dim+i], i, j, dim));
            }
        }
    }
    return SymmetricMatrix(data, dim);
}

std::unique_ptr<fl::Tensor> SymmetricMatrix::toTensor() {
    std::shared_ptr<fl::TensorShape> shape(
        std::shared_ptr<fl::TensorShape>(
            fl::TensorShape::createShape(
                std::vector<int>{_dim, _dim}
            )
        )
    );
    return std::unique_ptr<fl::Tensor>(
        fl::Tensor::newTensor(this->_matrix, shape)
    ); 
}

SymmetricMatrix SymmetricMatrix::add(const SymmetricMatrix& input) const {
    if (input.getDim() != this->_dim) {
        THROW_FL_EXCEPTION(str_format("Dimension does not match. (input:%d this:%d).", input.getDim(), this->_dim));
    }
    int size = this->_dim * this->_dim;
    std::vector<double> input_matrix = input.getMatrix();
    std::vector<double> output_matrix(size);
    for (int i = 0; i < size; i++) {
        output_matrix[i] = input_matrix[i] + this->_matrix[i];
    }
    return SymmetricMatrix(output_matrix, this->_dim);
}

std::vector<double> SymmetricMatrix::getMatrix() const {
    return this->_matrix;
}

int SymmetricMatrix::getDim() const {
    return this->_dim;
}

IntVector::IntVector(const std::vector<int>& input_vector) {
    this->_vector = input_vector; // if we need to avoid this copy, it is good to use pointer of vector.
    this->_dim = input_vector.size();
}

IntVector IntVector::fromTensor(const fl::Tensor& tensor) {
    std::vector<int> dims = tensor.getDims();
    if (dims.size() != 1) {
        THROW_FL_EXCEPTION(str_format("Invalid tensor dimension. must be 1 (!= %d).", dims.size()));
    }
    std::vector<int> data = tensor.intVector(); // it may throw json type error
    return IntVector(data);
}

std::unique_ptr<fl::Tensor> IntVector::toTensor() {
    std::shared_ptr<fl::TensorShape> shape(
        std::shared_ptr<fl::TensorShape>(
            fl::TensorShape::createShape(
                std::vector<int>{_dim}
            )
        )
    );
    return std::unique_ptr<fl::Tensor>(
        fl::Tensor::newTensor(this->_vector, shape)
    );    
}

std::vector<int> IntVector::getVector() const {
    return this->_vector;
}

int IntVector::getDim() const {
    return this->_dim;
}

DoubleVector::DoubleVector(const std::vector<double>& input_vector) {
    this->_vector = input_vector; // if we need to avoid this copy, it is good to use pointer of vector.
    this->_dim = input_vector.size();
}

DoubleVector DoubleVector::fromTensor(const fl::Tensor& tensor) {
    std::vector<int> dims = tensor.getDims();
    if (dims.size() != 1) {
        THROW_FL_EXCEPTION(str_format("Invalid tensor dimension. must be 1 (!= %d).", dims.size()));
    }
    std::vector<double> data = tensor.doubleVector(); // it may throw json type error.
    return DoubleVector(data);
}

std::unique_ptr<fl::Tensor> DoubleVector::toTensor() {
    std::shared_ptr<fl::TensorShape> shape(
        std::shared_ptr<fl::TensorShape>(
            fl::TensorShape::createShape(
                std::vector<int>{_dim}
            )
        )
    );
    return std::unique_ptr<fl::Tensor>(
        fl::Tensor::newTensor(this->_vector, shape)
    );    
}

DoubleVector DoubleVector::add(const DoubleVector& input) const {
    if (this->_dim != input.getDim()) {
        THROW_FL_EXCEPTION(str_format("Dimension does not match. (input:%d this:%d).", input.getDim(), this->_dim));
    }
    std::vector<double> input_vector = input.getVector();
    std::vector<double> output_vector(this->_dim);
    for (int i = 0; i < this->_dim; i++) {
        output_vector[i] = this->_vector[i] + input_vector[i];
    }
    return DoubleVector(output_vector);
}

DoubleVector DoubleVector::add(const IntVector& input) const {
    if (this->_dim != input.getDim()) {
        THROW_FL_EXCEPTION(str_format("Dimension does not match. (input:%d this:%d).", input.getDim(), this->_dim));
    }
    std::vector<int> input_vector = input.getVector();
    std::vector<double> output_vector(this->_dim);
    for (int i = 0; i < this->_dim; i++) {
        output_vector[i] = this->_vector[i] + input_vector[i];
    }
    return DoubleVector(output_vector);
}

DoubleVector DoubleVector::add(const double input) const {
    std::vector<double> output_vector(this->_dim);
    for (int i = 0; i < this->_dim; i++) {
        output_vector[i] = this->_vector[i] + input;
    }
    return DoubleVector(output_vector);
}

double DoubleVector::dot(const DoubleVector& input_vector) const {
    if (this->_dim != input_vector.getDim()) {
        THROW_FL_EXCEPTION(str_format("Dimension does not match. (input:%d this:%d).", input_vector.getDim(), this->_dim));
    }
    double ret = 0.0;
    std::vector<double> input = input_vector.getVector();
    for (int i=0; i<this->_dim; i++) {
        ret += this->_vector[i] * input[i];
    }
    return ret;
}

DoubleVector DoubleVector::mul(const SymmetricMatrix& input) const {
    if (this->_dim != input.getDim()) {
        THROW_FL_EXCEPTION(str_format("Dimension does not match. (input:%d this:%d).", input.getDim(), this->_dim));
    }
    std::vector<double> input_matrix = input.getMatrix();
    std::vector<double> output_vector(this->_dim, 0);
    for (int i = 0; i < this->_dim; i++) {
        for (int j = 0; j < this->_dim; j++) {
            output_vector[i] += input_matrix[i*this->_dim+j] * this->_vector[j];
        }
    }
    return DoubleVector(output_vector);
}

DoubleVector DoubleVector::mul(const double input) const {
    std::vector<double> output_vector(this->_dim);
    for (int i = 0; i < this->_dim; i++) {
        output_vector[i] = this->_vector[i] * input;
    }
    return DoubleVector(output_vector);
}

double DoubleVector::sum() const {
    double sum = 0;
    for (int i = 0; i < this->_dim; i++) {
        sum += this->_vector[i];
    }
    return sum;
}

double DoubleVector::logsumexp() const {
    double max_value = this->max();
    double ret = 0.0;
    for (auto p : this->_vector) {
        ret += std::exp(p - max_value);
    }
    ret = std::log(ret);
    return ret + max_value;
}


SymmetricMatrix DoubleVector::selfOuterProduct() const {
    std::vector<double> result_vetor(this->_dim*this->_dim, 0);
    for (int i = 0; i < this->_dim; i++) {
        for (int j = 0; j < this->_dim; j++) {
            result_vetor[i*this->_dim+j] = this->_vector[i] * this->_vector[j];
        }
    }
    return SymmetricMatrix::create(result_vetor, this->_dim);
}

int DoubleVector::argmax() const {
    auto maxIt = std::max_element(this->_vector.begin(), this->_vector.end());
    return std::distance(this->_vector.begin(), maxIt);
}

double DoubleVector::max() const {
    auto maxIt = std::max_element(this->_vector.begin(), this->_vector.end());
    return *maxIt;
}

std::vector<double> DoubleVector::getVector() const {
    return this->_vector;
}

int DoubleVector::getDim() const {
    return this->_dim;
}

DoubleVector DoubleVector::log(const DoubleVector& input) {
    std::vector<double> input_vector = input.getVector();
    int D = input_vector.size();
    std::vector<double> output_vector(D);
    for (int i = 0; i < D; i++) {
        output_vector[i] = std::log(input_vector[i]);
    }
    return DoubleVector(output_vector);
} 

DoubleVector DoubleVector::exp(const DoubleVector& input) {
    std::vector<double> input_vector = input.getVector();
    int D = input_vector.size();
    std::vector<double> output_vector(D);
    for (int i = 0; i < D; i++) {
        output_vector[i] = std::exp(input_vector[i]);
    }
    return DoubleVector(output_vector);
} 


} // namespace linear_hlcr
