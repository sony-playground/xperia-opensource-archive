#ifndef DATASERIALIZER_H_
#define DATASERIALIZER_H_

#include <fstream>
#include <iostream>
#include <string>

#include "data_metadata.h"
#include "tensor_map.h"

namespace fl {
    class DataSerializer {
        private:
            DataSerializer(const std::string& data_file, const std::string& index_file);

        private:
            std::string data_file;
            std::string index_file;

            std::ofstream data_ofs;
            std::ofstream index_ofs;

            std::unique_ptr<bool> was_success_ptr;

            bool is_open;

        private:
            void open();

        public:
            void save(const TensorMap& tensor_map);
            void close();
            DataMetadata getMetadata() const;

        public:
            static DataSerializer createFor(const std::string& data_file, const std::string& index_file);
    };
}

#endif  // DATASERIALIZER_H_

