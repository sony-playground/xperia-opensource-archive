#ifndef LINEARHLCR_JNIF_H_
#define LINEARHLCR_JNIF_H_

#include <nlohmann/json.hpp>

#include "LinearHLCR.h"

using json = nlohmann::json;

namespace linear_hlcr {

class LinearHLCR_JNIF {
    public:
        static long Initialize(const json jsonParams);
        static json Training(linear_hlcr::LinearHLCR* model_ptr, const json jsonParams);
        static json Evaluation(linear_hlcr::LinearHLCR* model_ptr, const json jsonParams);
        static json Prediction(linear_hlcr::LinearHLCR* model_ptr, const json jsonParams);
        static void Finalize(linear_hlcr::LinearHLCR* model_ptr);

        static json UpdateInfo(linear_hlcr::LinearHLCR* model_ptr, const json jsonParams);

    private:
        static std::string description(const std::string what, const std::string file, const int line);
};

} // namespace linear_hlcr
#endif  // LINEARHLCR_JNIF_H_
