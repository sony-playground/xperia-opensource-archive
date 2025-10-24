#ifndef DATADESERIALIZER_H_
#define DATADESERIALIZER_H_

#include <fstream>
#include <iostream>
#include <string>

#include "data_metadata.h"
#include "tensor_map.h"

namespace fl {
    class DataDeserializer {
        private:
            DataDeserializer(const DataMetadata&);

        private:
            DataMetadata metaData;
            std::string data_file;
            std::string index_file;

            std::ifstream data_ifs;
            std::ifstream index_ifs;

            int num_of_data;

        public:
            int getNumOfData() const;
            std::shared_ptr<fl::TensorMap> get(int) const;
            // DataMetadata getMetadata() const;

        public:
            static DataDeserializer createFor(const DataMetadata&);
            // static bool wasSuccess(DataMetadata& data_metadata);
            // static bool wasSaved(DataMetadata& data_metadata);
    };
}

#endif

