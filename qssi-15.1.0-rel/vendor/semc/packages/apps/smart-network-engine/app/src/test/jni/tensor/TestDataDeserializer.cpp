#include <fstream>
#include <sys/stat.h>
#include <stdio.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tensor/data_serializer.h"
#include "tensor/data_deserializer.h"
#include "FLException.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#define FL_TEST_DATA_DIR   "Testing/Temporary/"

class TestDataDeserializer: public ::testing::Test
{
public:
    std::string data1file;
    std::string data2file;

    std::string case_name;
    std::string test_suite_name;
    std::string name;

private:
    void cleanup() {
        system((std::string("/bin/rm -f ") + std::string(FL_TEST_DATA_DIR) + this->case_name + std::string(".*")).c_str());
    }

protected:
    virtual void SetUp() {
        const testing::TestInfo* ti = testing::UnitTest::GetInstance()->current_test_info();

        this->case_name = std::string(ti->test_suite_name()) + "." + std::string(ti->name());
        this->test_suite_name = std::string(ti->test_suite_name());
        this->name = std::string(ti->name());

        std::string testDir = FL_TEST_DATA_DIR + this->case_name;
        this->data1file = testDir + ".jsonl";
        this->data2file = testDir + ".txt";

        this->cleanup();
    }
    virtual void TearDown() {
        this->cleanup();
    }
};

void createTensorMapFiles(json data1, json data2, std::string data1file, std::string data2file) {
    {
        std::ofstream d(data1file);
        std::ofstream i(data2file);
        std::string data;
        int size;
        data = data1.dump();
        size = data.size();
        d << data << std::endl;
        i << "000000000" << std::endl;
        data = data2.dump();
        d << data << std::endl;
        i << "000000" << (size + 1) << std::endl;
    }
}

TEST_F(TestDataDeserializer, Success)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);
    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    try {
        std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
        tensor_map = data_deserializer.get(2);
    } catch (...) {
        FAIL();
    }
}

TEST_F(TestDataDeserializer, NotExistsTensorMapFile)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);
    std::remove(this->data1file.c_str());

    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    try {
        std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
        FAIL();
    } catch (json::parse_error& e){
        ASSERT_STREQ(e.what(), "[json.exception.parse_error.101] parse error at line 1, column 2: syntax error while parsing value - unexpected number literal; expected end of input");
    }
}

TEST_F(TestDataDeserializer, NotExistsTensorMapIndexFile)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);
    std::remove(this->data2file.c_str());

    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    try {
        std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
        FAIL();
    } catch (FLException ex){
        ASSERT_THAT(ex.what(), testing::MatchesRegex("input num \\(1\\) is grater than num of data \\(0\\) \\[tensor/data_deserializer\\.cc:[0-9]+\\]"));
    }
    try {
        std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(2);
        FAIL();
    } catch (FLException ex){
        ASSERT_THAT(ex.what(), testing::MatchesRegex("input num \\(2\\) is grater than num of data \\(0\\) \\[tensor/data_deserializer\\.cc:[0-9]+\\]"));
    }
}

TEST_F(TestDataDeserializer, NotExistsTensorMapBothFile)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);
    std::remove(this->data1file.c_str());
    std::remove(this->data2file.c_str());

    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    try {
        std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
        FAIL();
    } catch (FLException ex){
        ASSERT_THAT(ex.what(), testing::MatchesRegex("input num \\(1\\) is grater than num of data \\(0\\) \\[tensor/data_deserializer\\.cc:[0-9]+\\]"));
    }
}

TEST_F(TestDataDeserializer, EmptyTensorMapFile)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);

    std::ofstream d(this->data1file);
    std::ofstream i(this->data2file);
    std::string data;
    int size;
    // data = data1.dump();
    data = "";
    size = data.size();

    d << data;
    i << "000000000" << std::endl;

    // data = data2.dump();
    // d << data << std::endl;
    // i << "000000" << (size + 1) << std::endl;

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);
    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    try {
        std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
        FAIL();
    } catch (json::parse_error& e){
        ASSERT_STREQ(e.what(), "[json.exception.parse_error.101] parse error at line 1, column 1: syntax error while parsing value - unexpected end of input; expected '[', '{', or a literal");
    }
}

TEST_F(TestDataDeserializer, EmptyTensorMapIndexFile)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);

    std::ofstream d(this->data1file);
    std::ofstream i(this->data2file);
    std::string data;
    int size;
    data = data1.dump();
    // size = data.size();

    d << data << std::endl;
    i << "";

    data = data2.dump();
    d << data << std::endl;
    // i << "000000" << (size + 1) << std::endl;

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);
    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    try {
        std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
        FAIL();
    } catch (FLException ex){
        ASSERT_THAT(ex.what(), testing::MatchesRegex("input num \\(1\\) is grater than num of data \\(0\\) \\[tensor/data_deserializer\\.cc:[0-9]+\\]"));
    }
}

TEST_F(TestDataDeserializer, EmptyTensorMapBothFile)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);

    std::ofstream d(this->data1file);
    std::ofstream i(this->data2file);
    d << "";
    i << "";

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);
    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    try {
        std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
        FAIL();
    } catch (FLException ex){
        ASSERT_THAT(ex.what(), testing::MatchesRegex("input num \\(1\\) is grater than num of data \\(0\\) \\[tensor/data_deserializer\\.cc:[0-9]+\\]"));
    }
}

TEST_F(TestDataDeserializer, NotJsonFormat)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);

    std::ofstream d(this->data1file, std::ios::app);
    std::ofstream i(this->data2file, std::ios::app);
    std::string data = R"(#{"g":{"shape":[1],"value":["group1"]},"x":{"shape":[2],"value":[2.0,2.0]},"y":{"shape":[1],"value":[0.6]}})";
    int size;
    // data = data1.dump();
    size = data1.dump().size() + data2.dump().size();
    d << data << std::endl;
    i << "000000" << (size + 2) << std::endl;

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);
    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
    tensor_map = data_deserializer.get(2);
    try {
        tensor_map = data_deserializer.get(3);
        FAIL();
    } catch (json::exception& ex){
        ASSERT_STREQ(ex.what(), "[json.exception.parse_error.101] parse error at line 1, column 1: syntax error while parsing value - invalid literal; last read: '#'");
    }
}

TEST_F(TestDataDeserializer, InvalidIndexValue)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    std::ofstream d(this->data1file);
    std::ofstream i(this->data2file);
    std::string data;
    int size;
    data = data1.dump();
    size = data.size();
    d << data << std::endl;
    i << "000000000" << std::endl;
    data = data2.dump();
    d << data << std::endl;
    // i << "000000" << (size + 1) << std::endl;
    i << "000000" << size << std::endl;

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);
    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
    try {
        tensor_map = data_deserializer.get(2);
        FAIL();
    } catch (json::exception& ex){
        ASSERT_STREQ(ex.what(), "[json.exception.parse_error.101] parse error at line 1, column 1: syntax error while parsing value - unexpected end of input; expected '[', '{', or a literal");
    }
}

TEST_F(TestDataDeserializer, IndexIsFewerThanTensorMap)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    std::ofstream d(this->data1file);
    std::ofstream i(this->data2file);
    std::string data;
    int size;
    data = data1.dump();
    size = data.size();
    d << data << std::endl;
    i << "000000000" << std::endl;
    data = data2.dump();
    d << data << std::endl;
    // i << "000000" << (size + 1) << std::endl;

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);
    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
    try {
        tensor_map = data_deserializer.get(2);
        FAIL();
    } catch (FLException ex){
        ASSERT_THAT(ex.what(), testing::MatchesRegex("input num \\(2\\) is grater than num of data \\(1\\) \\[tensor/data_deserializer\\.cc:[0-9]+\\]"));
    }
}

TEST_F(TestDataDeserializer, TensorMapIsFewerThanIndex)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    std::ofstream d(this->data1file);
    std::ofstream i(this->data2file);
    std::string data;
    int size;
    data = data1.dump();
    size = data.size();
    d << data << std::endl;
    i << "000000000" << std::endl;
    data = data2.dump();
    // d << data << std::endl;
    i << "000000" << (size + 1) << std::endl;

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);
    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
    try {
        tensor_map = data_deserializer.get(2);
        FAIL();
    } catch (json::exception& ex){
        ASSERT_STREQ(ex.what(), "[json.exception.parse_error.101] parse error at line 1, column 1: syntax error while parsing value - unexpected end of input; expected '[', '{', or a literal");
    }
}

TEST_F(TestDataDeserializer, NotReadableTensorMapFile)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);

    chmod(this->data1file.c_str(), 0200);
    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);

    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    try {
        std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
        FAIL();
    } catch (json::parse_error& e){
        ASSERT_STREQ(e.what(), "[json.exception.parse_error.101] parse error at line 1, column 2: syntax error while parsing value - unexpected number literal; expected end of input");
    }
}

TEST_F(TestDataDeserializer, NotReadableIndexFile)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);
    chmod(this->data2file.c_str(), 0200);
    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);

    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    try {
        std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
        FAIL();
    } catch (FLException ex){
        ASSERT_THAT(ex.what(), testing::MatchesRegex("input num \\(1\\) is grater than num of data \\(0\\) \\[tensor/data_deserializer\\.cc:[0-9]+\\]"));
    }
}

TEST_F(TestDataDeserializer, NotReadableBothFile)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);

    chmod(this->data1file.c_str(), 0200);
    chmod(this->data2file.c_str(), 0200);

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);

    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    try {
        std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
        FAIL();
    } catch (FLException ex){
        ASSERT_THAT(ex.what(), testing::MatchesRegex("input num \\(1\\) is grater than num of data \\(0\\) \\[tensor/data_deserializer\\.cc:[0-9]+\\]"));
    }
}

// ### Invalid Tensor data Test
TEST_F(TestDataDeserializer, NoTensorMapShape)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);

    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
    try {
        tensor_map = data_deserializer.get(2);
        FAIL();
    } catch (json::exception& ex){
        ASSERT_STREQ(ex.what(), "[json.exception.type_error.302] type must be array, but is null");
    }
}

TEST_F(TestDataDeserializer, NoTensorMapValue)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"shape":[1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);
    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
    try {
        tensor_map = data_deserializer.get(2);
        FAIL();
    } catch (FLException e){
        ASSERT_THAT(e.what(), testing::MatchesRegex("Failed to create tensor\\. Unknown json string\\. \\(\\{\"shape\":\\[1\\],\"value\":null\\}\\) \\[tensor/tensor\\.cc:[0-9]+\\]"));
    }
}

TEST_F(TestDataDeserializer, TensorShapeIsNotArray)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":1}, "g":{"value":["group1"], "shape":[1]}})"_json;

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);
    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
    try {
        tensor_map = data_deserializer.get(2);
        FAIL();
    } catch (json::exception& ex){
        ASSERT_STREQ(ex.what(), "[json.exception.type_error.302] type must be array, but is number");
    }
}

TEST_F(TestDataDeserializer, TensorValueIsNotArray)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":0.6, "shape":[1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);
    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
    try {
        tensor_map = data_deserializer.get(2);
        FAIL();
    } catch (FLException e){
        ASSERT_THAT(e.what(), testing::MatchesRegex("Failed to create tensor\\. Unknown json string\\. \\(\\{\"shape\":\\[1\\],\"value\":0.6\\}\\) \\[tensor/tensor\\.cc:[0-9]+\\]"));
    }
}

TEST_F(TestDataDeserializer, InvalidTensorShapeSizeLarge)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[5]}, "g":{"value":["group1"], "shape":[1]}})"_json;  // y.shape 5 is invalid

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);
    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);

    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
    try {
        tensor_map = data_deserializer.get(2);
        FAIL();
    } catch (FLException ex){
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Failed to create tensor. unmatch size. \\(1 != 5\\) \\[tensor/tensor\\.cc:[0-9]+\\]"));
    }
}

TEST_F(TestDataDeserializer, InvalidTensorShapeSizeSmall)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[0]}, "g":{"value":["group1"], "shape":[1]}})"_json;  // y.shape 0 is invalid

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);

    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
    try {
        tensor_map = data_deserializer.get(2);
        FAIL();
    } catch (FLException ex){
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Incorrect number of elements\\. \\(dims:0 \\[0/1\\]\\) \\[tensor/tensor_shape\\.cc:[0-9]+\\]"));
    }
}

TEST_F(TestDataDeserializer, TensorShapeIsNotInt)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[0.1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);

    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
    try {
        tensor_map = data_deserializer.get(2);
        FAIL();
    } catch (FLException ex){
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Incorrect number of elements\\. \\(dims:0 \\[0/1\\]\\) \\[tensor/tensor_shape\\.cc:[0-9]+\\]"));
    }
}

TEST_F(TestDataDeserializer, InvalidLineNo)
{
    auto data1 = R"({"x":{"value":[1.0,1.0], "shape":[2]}, "y":{"value":[0.8], "shape":[1]}, "g":{"value":["group0"], "shape":[1]}})"_json;
    auto data2 = R"({"x":{"value":[2.0,2.0], "shape":[2]}, "y":{"value":[0.6], "shape":[1]}, "g":{"value":["group1"], "shape":[1]}})"_json;

    createTensorMapFiles(data1, data2, this->data1file, this->data2file);

    fl::DataSerializer data_serializer = fl::DataSerializer::createFor(this->data1file, this->data2file);

    fl::DataMetadata data_metadata = data_serializer.getMetadata();
    fl::DataDeserializer data_deserializer = fl::DataDeserializer::createFor(data_metadata);
    std::shared_ptr<fl::TensorMap> tensor_map = data_deserializer.get(1);
    try {
        tensor_map = data_deserializer.get(0);
        FAIL();
    } catch (FLException ex){
        ASSERT_THAT(ex.what(), testing::MatchesRegex("input num \\(0\\) must be greater than 1\\. \\[tensor/data_deserializer\\.cc:[0-9]+\\]"));
    }
}
