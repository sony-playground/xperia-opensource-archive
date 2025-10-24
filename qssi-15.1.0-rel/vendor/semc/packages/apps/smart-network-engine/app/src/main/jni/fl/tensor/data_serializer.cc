#include "data_serializer.h"

#include <memory>
#include <sstream>
#include <sys/stat.h>

#include "FLException.h"

using namespace fl;

void debug_out() { std::cerr << std::endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    std::cerr << " " << H;
    debug_out(T...);
}
#ifdef LOCAL
#define debug(...) std::cerr << "##### [" << #__VA_ARGS__ << "]", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

#define error(...) std::cerr << "##### [" << #__VA_ARGS__ << "]", debug_out(__VA_ARGS__)

DataSerializer DataSerializer::createFor(const std::string& data_file, const std::string& index_file) {
    debug("ENTER", "DataSerializer::createFor()", data_file, index_file);
    // NOTE: data_file and index_file must not exist. This means that additional writes are not supported.
    DataSerializer serializer(data_file, index_file);
    serializer.open();
    return serializer;
}

DataSerializer::DataSerializer(const std::string& data_file, const std::string& index_file) {
    debug("ENTER", "DataSerializer::DataSerializer()", data_file, index_file);
    this->data_file = data_file;
    this->index_file = index_file;
    this->was_success_ptr.reset();
    this->is_open = false;
}

void DataSerializer::open() {
    debug("ENTER", "DataSerializer::open()");
    if (this->is_open) {
        return;
    }

    try {
        this->data_ofs.open(this->data_file, std::ios_base::out|std::ios_base::app);
        this->data_ofs.exceptions(std::ofstream::badbit|std::ofstream::eofbit|std::ofstream::failbit);
    }
    catch (const std::ios_base::failure& ex) {
        error("DataSerializer::open()", "failed to open data file:", this->data_file);
        THROW_FL_EXCEPTION(str_format("failed to open data file: %s", this->data_file.c_str()));
    }
    if (!this->data_ofs) {
        error("DataSerializer::open()", "failed to open data file:", this->data_file);
        THROW_FL_EXCEPTION(str_format("failed to open data file: %s", this->data_file.c_str()));
    }

    try {
        this->index_ofs.open(this->index_file, std::ios_base::out|std::ios_base::app);
        this->index_ofs.exceptions(std::ofstream::badbit|std::ofstream::eofbit|std::ofstream::failbit);
    }
    catch (const std::ios_base::failure& ex) {
        error("DataSerializer::open()", "failed to open index file:", this->index_file);
        THROW_FL_EXCEPTION(str_format("failed to open index file: %s", this->index_file.c_str()));
    }
    if (!this->index_ofs) {
        this->data_ofs.close();
        error("DataSerializer::open()", "failed to open index file:", this->index_file);
        THROW_FL_EXCEPTION(str_format("failed to open index file: %s", this->index_file.c_str()));
    }

    this->is_open = true;
    return;
}

void DataSerializer::close() {
    debug("ENTER", "DataSerializer::close()");
    if (!(this->is_open)) {
        return;
    }

    try {
        this->index_ofs.close();
    }
    catch (const std::ios_base::failure& ex) {
        error("DataSerializer::close()", "Caught: std::ios_base::failure", ex.what());
        this->was_success_ptr.reset(new bool(false));
        // not return
    }

    try {
        this->data_ofs.close();
    }
    catch (const std::ios_base::failure& ex) {
        error("DataSerializer::close()", "Caught: std::ios_base::failure", ex.what());
        this->was_success_ptr.reset(new bool(false));
        // not return
    }

    this->is_open = false;
    return;
}

void DataSerializer::save(const TensorMap& tensor_map) {
    debug("ENTER", "DataSerializer::save()");

    if (!(this->is_open)) {
        try {
            this->open();
        }
        catch (FLException& ex) {
            this->was_success_ptr.reset(new bool(false));
            return;
        }
    }

    std::ostringstream index_format;
    index_format << std::setw(9) << std::setfill('0');
    index_format << this->data_ofs.tellp();

    try {
        this->index_ofs << index_format.str() << std::endl;
        this->index_ofs.flush();

        this->data_ofs << tensor_map.toJsonString() << std::endl;
        this->data_ofs.flush();
    }
    catch (const std::ios_base::failure& ex) {
        error("DataSerializer::save()", "Caught: std::ios_base::failure", ex.what());
        this->was_success_ptr.reset(new bool(false));
    }

    if (!this->was_success_ptr) {
        this->was_success_ptr.reset(new bool(true));
    }

    return;
}

DataMetadata DataSerializer::getMetadata() const {
    debug("ENTER", "DataSerializer::getMetadata()");
    DataMetadata data_metadata;
    data_metadata.set(DataMetadata::DATA_FILE_KEY, this->data_file);
    data_metadata.set(DataMetadata::INDEX_FILE_KEY, this->index_file);
    if (this->was_success_ptr) {
        std::string save_result;
        if (*(this->was_success_ptr.get()) == true) {
            save_result = DataMetadata::SAVE_RESULT_VALUE_SUCCESS;
        } else {
            save_result = DataMetadata::SAVE_RESULT_VALUE_FAILED;
        }
        data_metadata.set(DataMetadata::SAVE_RESULT_KEY, save_result);
    }
    return data_metadata;
}

