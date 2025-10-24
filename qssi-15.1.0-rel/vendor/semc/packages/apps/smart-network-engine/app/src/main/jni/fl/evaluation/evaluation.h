#include "tensor/data_deserializer.h"
#include "tensor/data_serializer.h"
#include "tensor/data_metadata.h"
#include "tensor/tensor_map.h"

#include <list>

namespace fl {
    class Evaluator {
        private:
            DataSerializer _serializer;
            Evaluator(const std::string&);
        public:
            static Evaluator createFor(const std::string&);
            void addResult(std::shared_ptr<Tensor>, std::shared_ptr<Tensor>);
            DataMetadata getRawResult() const;

        public:
            static const std::string KEY_OF_TARGET;
            static const std::string KEY_OF_PREDICTION_RESULT;
            static const std::string JSON_LINES_FILE_NAME;
            static const std::string INDEX_FILE_NAME;
    };
}