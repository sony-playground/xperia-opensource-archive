#include <memory>

#include "FLException.h"
#include "tensor_shape.h"

namespace fl {

TensorShape::TensorShape(std::string name, std::vector<int> dims) {
	int size = 1;
	for (int dim = 0; dim < dims.size(); dim++) { size *= dims.at(dim); }

	this->_dims = dims;
	this->_size = size;
	this->_name = name;
}

TensorShape* TensorShape::createShape(std::string name, std::vector<int> dims){
	if (dims.size() <= 0) {
		THROW_FL_EXCEPTION(str_format("dims are empty."));
	}
	for (int dim = 0; dim < dims.size(); dim++) {
		if (dims.at(dim) <= 0) {
			THROW_FL_EXCEPTION(str_format("Incorrect number of elements. (dims:%d [%d/%d])", dims.at(dim), dim, dims.size()));
		}
	}
	return new TensorShape(name, dims);
}

TensorShape* TensorShape::createShape(std::vector<int> dims){
	return TensorShape::createShape("n/a", dims);
}

int TensorShape::dims() const {
	return this->_dims.size();
}

int TensorShape::getDim(const int d) const {
	try {
	    return this->_dims.at(d);
	}
	catch (std::out_of_range& ex) {
        THROW_FL_EXCEPTION(str_format("Out of the range of Shape's dimensions. (d=%d)", d));
	}
}

bool TensorShape::isSameSize(const TensorShape& other) const {
	if (this->dims() != other.dims()) return false;
	int dims = this->dims();
	for (int dim = 0; dim < dims; dim++) if (this->getDim(dim) != other.getDim(dim)) return false;
	return true;
}

int TensorShape::size() const {
	return this->_size;
}

std::vector<int> TensorShape::getDims() const {
	return this->_dims;
}

}  // namespace fl
