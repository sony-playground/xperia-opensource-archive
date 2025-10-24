#ifndef NNHLCR_JNIF_H_
#define NNHLCR_JNIF_H_

#include <string>

#include <nlohmann/json.hpp>

#include "NNHLCR/lstm_lcr_model_nnabla.h"

using json = nlohmann::json;

namespace nn_hlcr {

class NNHLCR_JNIF {
    public:
        static long Initialize(const char* modelInfo);
        static std::string Training(LstmLCRModel* mlObj, const char* metaDataJson, const char* trainInfo);
        static std::string Evaluation(LstmLCRModel* mlObj, const char* metaDataJson, const char* evaluationInfo);
        static float Prediction(LstmLCRModel* mlObj, const char* tensorMapJson);
        static void Finalize(LstmLCRModel* mlObj);

        static std::string UpdateInfo(LstmLCRModel* mlObj, const char* metaDataJson, const char* updateInfo);
};

} // namespace nn_hlcr
#endif  // NNHLCR_JNIF_H_
