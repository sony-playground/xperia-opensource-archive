#include "LinearRegression.h"
#include "FLException.h"

namespace linear_hlcr {

LinearRegressionGlobalModel::LinearRegressionGlobalModel(const SymmetricMatrix& H, const DoubleVector& w, const double b) {
    _H = std::shared_ptr<SymmetricMatrix>(new SymmetricMatrix(H));
    _w = std::shared_ptr<DoubleVector>(new DoubleVector(w));
    _b = b;
}

std::shared_ptr<SymmetricMatrix> LinearRegressionGlobalModel::getH() const {
    return this->_H;
}

std::shared_ptr<DoubleVector> LinearRegressionGlobalModel::getW() const {
    return this->_w;
}

double LinearRegressionGlobalModel::getB() const {
    return this->_b;
}

std::unique_ptr<LinearRegressionGlobalModel> LinearRegressionGlobalModel::fromJson(const json& json_obj) {
    try {
        int D = json_obj[LinearRegressionGlobalModel::KEY_OF_DIM].get<int>();
        std::vector<double> H = json_obj[LinearRegressionGlobalModel::KEY_OF_H].get<std::vector<double>>();
        std::vector<double> w = json_obj[LinearRegressionGlobalModel::KEY_OF_W].get<std::vector<double>>();
        double b = json_obj[LinearRegressionGlobalModel::KEY_OF_B].get<double>();
        if (D != w.size() + 1 || D * D != H.size()) THROW_FL_EXCEPTION(str_format("D, w, and H are not matched. (D:%d w.size:%d H.size:%d)", D, w.size(), H.size()));
        return std::unique_ptr<LinearRegressionGlobalModel>(
                new LinearRegressionGlobalModel(
                        SymmetricMatrix::create(H, D), DoubleVector(w), b));
    }
    catch (json::exception& ex) {
        THROW_FL_EXCEPTION(str_format("Caught: json exception [%s]", ex.what()));
    }
}

LinearRegressionLocalModel::LinearRegressionLocalModel(const SymmetricMatrix& D, const DoubleVector& c) { 
    _D = std::shared_ptr<SymmetricMatrix>(new SymmetricMatrix(D));
    _c = std::shared_ptr<DoubleVector>(new DoubleVector(c));
}

std::unique_ptr<LinearRegressionLocalModel> LinearRegressionLocalModel::create(const SymmetricMatrix& D, const DoubleVector& c) {
    if (D.getDim() != c.getDim()) THROW_FL_EXCEPTION(str_format("Dimensions D and c do not match. (D:%d c:%d)", D.getDim(), c.getDim()));
    return std::unique_ptr<LinearRegressionLocalModel>(new LinearRegressionLocalModel(D, c));
}

std::shared_ptr<json> LinearRegressionLocalModel::save() {
    std::shared_ptr<json> json_ptr(new json());
    (*json_ptr)[LinearRegressionLocalModel::KEY_OF_D] = this->_D->getMatrix();
    (*json_ptr)[LinearRegressionLocalModel::KEY_OF_C] = this->_c->getVector();
    (*json_ptr)[LinearRegressionLocalModel::KEY_OF_DIM] = this->_c->getDim();
    return json_ptr;
}


const std::string LinearRegressionGlobalModel::KEY_OF_H = "H";
const std::string LinearRegressionGlobalModel::KEY_OF_W = "w";
const std::string LinearRegressionGlobalModel::KEY_OF_B = "b";
const std::string LinearRegressionGlobalModel::KEY_OF_DIM = "d";

const std::string LinearRegressionLocalModel::KEY_OF_D = "D";
const std::string LinearRegressionLocalModel::KEY_OF_C = "c";
const std::string LinearRegressionLocalModel::KEY_OF_DIM = "d";

} // namespace linear_hlcr
