#ifndef FL_TENSOR_SHAPE_H_
#define FL_TENSOR_SHAPE_H_

#include <cstdint>
#include <iostream>
#include <string.h>
#include <vector>

namespace fl {

class TensorShape {
	private:
		std::vector<int> _dims;
		int _size;
		std::string _name;

		TensorShape() : _dims({}), _size(){};
		TensorShape(std::string mame, std::vector<int> dims);

	public:
		static TensorShape* createShape(std::vector<int> dims);
		static TensorShape* createShape(std::string name, std::vector<int> dims);
		int dims() const;
		int getDim(const int d) const;
		bool isSameSize(const TensorShape& other) const;
		int size() const;
		std::vector<int> getDims() const;
};

}  // namespace fl

#endif  // FL_TENSOR_SHAPE_H_
// vim: set ts=4:
