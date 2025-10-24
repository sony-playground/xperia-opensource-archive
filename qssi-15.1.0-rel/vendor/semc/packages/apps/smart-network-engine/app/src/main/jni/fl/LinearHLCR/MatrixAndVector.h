#include "tensor/tensor.h"

#include <array>
#include <memory>
#include <cmath>
#include <exception>

namespace linear_hlcr {

    class SymmetricMatrix {
        private:
            SymmetricMatrix(const std::vector<double>&, int);
            std::vector<double> _matrix;
            int _dim; // size = _dim * _dim
        public:
            static SymmetricMatrix fromTensor(const fl::Tensor&);
            static SymmetricMatrix create(const std::vector<double>&, int);
            std::unique_ptr<fl::Tensor> toTensor();
            SymmetricMatrix add(const SymmetricMatrix&) const;
            std::vector<double> getMatrix() const;
            int getDim() const;
    };

    class IntVector {
        private:
            std::vector<int> _vector;
            int _dim;
        public:
            IntVector(const std::vector<int>&);
            std::unique_ptr<fl::Tensor> toTensor();
            std::vector<int> getVector() const;
            int getDim() const;
        public:
            static IntVector fromTensor(const fl::Tensor&);
    };

   class DoubleVector {
        private:
            std::vector<double> _vector;
            int _dim;
        public:
            DoubleVector(const std::vector<double>&);
            std::unique_ptr<fl::Tensor> toTensor();
            DoubleVector add(const DoubleVector&) const;
            DoubleVector add(const IntVector&) const;
            DoubleVector add(const double) const;
            double dot(const DoubleVector&) const;
            DoubleVector mul(const SymmetricMatrix&) const;
            DoubleVector mul(const double) const;
            double sum() const;
            double logsumexp() const;
            SymmetricMatrix selfOuterProduct() const;
            int argmax() const;
            double max() const;
            std::vector<double> getVector() const;
            int getDim() const;
        public:
            static DoubleVector fromTensor(const fl::Tensor&);
            static DoubleVector log(const DoubleVector&);
            static DoubleVector exp(const DoubleVector&);
    };


} // namespace linear_hlcr