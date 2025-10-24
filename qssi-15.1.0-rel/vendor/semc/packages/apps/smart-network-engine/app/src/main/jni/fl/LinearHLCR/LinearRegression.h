#include "MatrixAndVector.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace linear_hlcr {

class LinearRegressionGlobalModel {
    private:
         LinearRegressionGlobalModel(
            const linear_hlcr::SymmetricMatrix&, 
            const linear_hlcr::DoubleVector&,
            const double);
        std::shared_ptr<linear_hlcr::SymmetricMatrix> _H;
        std::shared_ptr<linear_hlcr::DoubleVector> _w;
        double _b;
    public:
        std::shared_ptr<linear_hlcr::SymmetricMatrix> getH() const;
        std::shared_ptr<linear_hlcr::DoubleVector> getW() const;
        double getB() const;
    public:
        static std::unique_ptr<linear_hlcr::LinearRegressionGlobalModel> fromJson(const json&);   
        static const std::string KEY_OF_H;
        static const std::string KEY_OF_W;
        static const std::string KEY_OF_B;
        static const std::string KEY_OF_DIM;
};

class LinearRegressionLocalModel {
    private:
        LinearRegressionLocalModel(
            const linear_hlcr::SymmetricMatrix&, 
            const linear_hlcr::DoubleVector&);
        std::shared_ptr<linear_hlcr::SymmetricMatrix> _D;
        std::shared_ptr<linear_hlcr::DoubleVector> _c;
    public:
        static std::unique_ptr<linear_hlcr::LinearRegressionLocalModel> create(
            const linear_hlcr::SymmetricMatrix&, 
            const linear_hlcr::DoubleVector&);
        std::shared_ptr<json> save();
        static const std::string KEY_OF_D;
        static const std::string KEY_OF_C;
        static const std::string KEY_OF_DIM;
};


} // linear_hlcr