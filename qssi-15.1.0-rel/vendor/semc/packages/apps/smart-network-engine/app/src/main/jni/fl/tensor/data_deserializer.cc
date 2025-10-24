#include "data_deserializer.h"
#include "FLException.h"

using namespace fl;

DataDeserializer::DataDeserializer(const DataMetadata& metaData) {
    this->num_of_data = 0;
    this->metaData = metaData;
}

int DataDeserializer::getNumOfData() const {
    return this->num_of_data;
}

std::shared_ptr<fl::TensorMap> DataDeserializer::get(int num) const {
    if (num <= 0) {
        THROW_FL_EXCEPTION(str_format("input num (%d) must be greater than 1.", num));
    }
    if (this->num_of_data < num) {
        THROW_FL_EXCEPTION(str_format("input num (%d) is grater than num of data (%d)", num, this->num_of_data));
    }

    std::filebuf* data_buf = this->data_ifs.rdbuf();
    std::iostream data_ios(data_buf);

    std::filebuf* index_buf = this->index_ifs.rdbuf();
    std::iostream index_ios(index_buf);

    int index_offset = DataMetadata::INDEX_LENGTH * (num - 1);
    index_ios.seekg(index_offset, std::ios_base::beg);

    int data_offset = 0;
    std::string line;
    getline(index_ios, line);
    data_offset = stoi(line);
    data_ios.seekg(data_offset, std::ios_base::beg);

    getline(data_ios, line);
    std::shared_ptr<fl::TensorMap> tensorMap(fl::TensorMap::fromJsonString(line));

    return tensorMap;
}

// DataMetadata DataDeserializer::getMetadata() const {
//     return this->metaData;
// }

DataDeserializer DataDeserializer::createFor(const DataMetadata& metaData) {
    DataDeserializer dataDeserializer = DataDeserializer(metaData);
    dataDeserializer.data_file = metaData.get(DataMetadata::DATA_FILE_KEY);
    dataDeserializer.index_file = metaData.get(DataMetadata::INDEX_FILE_KEY);
    dataDeserializer.data_ifs.open(dataDeserializer.data_file);
    dataDeserializer.index_ifs.open(dataDeserializer.index_file);
    std::ifstream ifstr(dataDeserializer.index_file);
    if (ifstr) {
        ifstr.seekg(0, std::ios_base::end);
        size_t filesize = static_cast<size_t>(ifstr.tellg());
        dataDeserializer.num_of_data = filesize / (DataMetadata::INDEX_LENGTH);
    }
    return dataDeserializer;
}

// bool DataDeserializer::wasSuccess(DataMetadata& data_metadata) {
//     std::string save_result = data_metadata.get(DataMetadata::SAVE_RESULT_KEY);
//     return (save_result == DataMetadata::SAVE_RESULT_VALUE_SUCCESS);
// }

// bool DataDeserializer::wasSaved(DataMetadata& data_metadata) {
//     std::string save_result = data_metadata.get(DataMetadata::SAVE_RESULT_KEY);
//     return (save_result != "");
// }

