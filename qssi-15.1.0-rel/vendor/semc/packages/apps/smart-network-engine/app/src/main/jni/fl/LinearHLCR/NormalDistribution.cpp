#include "LinearHLCR/NormalDistribution.h"

#include <cmath>

namespace linear_hlcr {

double NormalDistribution::log_probability(const double x, const double loc, const double scale) {
    double var = std::pow(scale, 2);
    return -std::pow(x-loc, 2) / (2 * var) - std::log(2 * M_PI * var) / 2;
}

}