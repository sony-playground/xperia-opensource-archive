#include <iostream>
#include <fstream>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "data_metadata.h"

using namespace fl;

#define LINE_SEPARATOR '\n'

const std::string DataMetadata::SAVE_RESULT_KEY = "save_result";
const std::string DataMetadata::SAVE_RESULT_VALUE_SUCCESS = "success";
const std::string DataMetadata::SAVE_RESULT_VALUE_FAILED = "failed";

const std::string DataMetadata::DATA_FILE_KEY = "tensor_map_file";
const std::string DataMetadata::INDEX_FILE_KEY = "tensor_map_index_file";
const int DataMetadata::INDEX_LENGTH = 9 + sizeof(LINE_SEPARATOR);

DataMetadata::DataMetadata() {
}

std::string DataMetadata::get(const std::string& key) const {
    std::string value;
    try {
        value = this->metadata.at(key);
    }
    catch(std::out_of_range&) {
        std::cout << "exception std::out_of_range" << std::endl;
    }
    return value;
}

void DataMetadata::set(const std::string& key, const std::string& value) {
    this->metadata[key] = value;
}

std::string DataMetadata::toJsonString() const {
    json j_map(this->metadata);
    return j_map.dump();
}

DataMetadata DataMetadata::fromJsonString(const std::string& json_data) {
    json data = json::parse(json_data);
    DataMetadata metadata = DataMetadata();
    for (auto& el : data.items()) {
        metadata.set(el.key(), el.value());
    }

    return metadata;
}


