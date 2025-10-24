#include <sys/stat.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tensor/data_deserializer.h"
#include "tensor/data_serializer.h"
#include "tensor/data_metadata.h"
#include "tensor/tensor.h"
#include "tensor/tensor_map.h"
#include "tensor/tensor_shape.h"
#include "FLException.h"

#define FL_TEST_DATA_DIR   "Testing/Temporary/"

class TestDataSerializer: public ::testing::Test
{
public:
    std::string jsonl_file;
    std::string index_file;

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

        this->jsonl_file = std::string(FL_TEST_DATA_DIR) + this->case_name + ".tensor_map.jsonl";
        this->index_file = std::string(FL_TEST_DATA_DIR) + this->case_name + ".tensor_map.index";

        this->test_suite_name = std::string(ti->test_suite_name());
        this->name = std::string(ti->name());

        this->cleanup();
    }
    virtual void TearDown() {
        this->cleanup();
    }

    bool is_inside_container() {
        std::ifstream dockerenv("/.dockerenv");
        return dockerenv.good();
    }
};

TEST_F(TestDataSerializer, createFor_once)
{
    ASSERT_NO_THROW({
        fl::DataSerializer serializer = fl::DataSerializer::createFor(this->jsonl_file, this->index_file);
    });
}

TEST_F(TestDataSerializer, createFor_twice)
{
    ASSERT_NO_THROW({
        fl::DataSerializer serializerA = fl::DataSerializer::createFor(this->jsonl_file, this->index_file);
        fl::DataSerializer serializerB = fl::DataSerializer::createFor(this->jsonl_file, this->index_file);
    });
}

TEST_F(TestDataSerializer, createFor___not_exists_parent_directory)
{
    if (!(this->is_inside_container())) {
        std::cerr << "SKIP: " << this->case_name << std::endl;
        SUCCEED();
        return;
    }

    std::string root_jsonl_file = std::string(FL_TEST_DATA_DIR) + this->case_name + "/not_exists/tensor_map.jsonl";
    std::string root_index_file = std::string(FL_TEST_DATA_DIR) + this->case_name + "/not_exists/tensor_map.index";

    try {
        // createFor
        fl::DataSerializer serializer = fl::DataSerializer::createFor(root_jsonl_file, root_index_file);
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("failed to open data file: " + root_jsonl_file + " \\[tensor/data_serializer\\.cc:[0-9]+\\]"));
    }
}

TEST_F(TestDataSerializer, createFor___no_write_permission_to_directory)
{
    if (!(this->is_inside_container())) {
        std::cerr << "SKIP: " << this->case_name << std::endl;
        SUCCEED();
        return;
    }

    std::string root_jsonl_file = std::string(FL_TEST_DATA_DIR) + "root.d/tensor_map.jsonl";
    std::string root_index_file = std::string(FL_TEST_DATA_DIR) + "root.d/tensor_map.index";

    try {
        // createFor
        fl::DataSerializer serializer = fl::DataSerializer::createFor(root_jsonl_file, root_index_file);
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("failed to open data file: " + root_jsonl_file + " \\[tensor/data_serializer\\.cc:[0-9]+\\]"));
    }
}

TEST_F(TestDataSerializer, createFor___no_write_permission_to_jsonl_file)
{
    if (!(this->is_inside_container())) {
        std::cerr << "SKIP: " << this->case_name << std::endl;
        SUCCEED();
        return;
    }

    std::string root_jsonl_file = std::string(FL_TEST_DATA_DIR) + "tensor_map.root.jsonl";

    try {
        // createFor
        fl::DataSerializer serializer = fl::DataSerializer::createFor(root_jsonl_file, this->index_file);
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("failed to open data file: " + root_jsonl_file + " \\[tensor/data_serializer\\.cc:[0-9]+\\]"));
    }
}

TEST_F(TestDataSerializer, createFor___no_write_permission_to_index_file)
{
    if (!(this->is_inside_container())) {
        std::cerr << "SKIP: " << this->case_name << std::endl;
        SUCCEED();
        return;
    }

    std::string root_index_file = std::string(FL_TEST_DATA_DIR) + "tensor_map.root.index";

    try {
        // createFor
        fl::DataSerializer serializer = fl::DataSerializer::createFor(this->jsonl_file, root_index_file);
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("failed to open index file: " + root_index_file + " \\[tensor/data_serializer\\.cc:[0-9]+\\]"));
    }
}

TEST_F(TestDataSerializer, save_tensor_map___success)
{
    std::vector<std::string> vector_string { this->test_suite_name, this->name, "#1" };

    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({3}));

    std::shared_ptr<fl::TensorMap> tensor_map(fl::TensorMap::newInstance());
    std::shared_ptr<fl::Tensor> tensor_string(fl::Tensor::newTensor(vector_string, shape));
    tensor_map->set("vector_string", tensor_string);

    ASSERT_NO_THROW({
        // createFor
        fl::DataSerializer serializer = fl::DataSerializer::createFor(this->jsonl_file, this->index_file);

        // save
        serializer.save(*(tensor_map.get()));

        fl::DataMetadata meta = serializer.getMetadata();
        ASSERT_EQ("success", meta.get("save_result"));
        ASSERT_EQ(jsonl_file, meta.get("tensor_map_file"));
        ASSERT_EQ(index_file, meta.get("tensor_map_index_file"));
        std::cout << "Metadata:" << meta.toJsonString() << std::endl;

        fl::DataDeserializer deserializer = fl::DataDeserializer::createFor(meta);

        ASSERT_EQ(1, deserializer.getNumOfData());
        std::shared_ptr<fl::TensorMap> tm1 = deserializer.get(1);
        std::shared_ptr<fl::Tensor> t1 = tm1->get("vector_string");
        ASSERT_EQ(this->test_suite_name, t1->textVector()[0]);
        ASSERT_EQ(this->name, t1->textVector()[1]);
        ASSERT_EQ("#1", t1->textVector()[2]);
    });
}

TEST_F(TestDataSerializer, save_the_tensor_map_twice_in_a_row___success_x2)
{
    std::vector<std::string> vector_stringA { this->test_suite_name, this->name, "#1" };
    std::vector<std::string> vector_stringB { this->test_suite_name, this->name, "#2" };

    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({3}));

    std::shared_ptr<fl::TensorMap> tensor_mapA(fl::TensorMap::newInstance());
    std::shared_ptr<fl::Tensor> tensor_stringA(fl::Tensor::newTensor(vector_stringA, shape));
    tensor_mapA->set("vector_string", tensor_stringA);

    std::shared_ptr<fl::TensorMap> tensor_mapB(fl::TensorMap::newInstance());
    std::shared_ptr<fl::Tensor> tensor_stringB(fl::Tensor::newTensor(vector_stringB, shape));
    tensor_mapB->set("vector_string", tensor_stringB);

    ASSERT_NO_THROW({
        // createFor
        fl::DataSerializer serializer = fl::DataSerializer::createFor(this->jsonl_file, this->index_file);

        // save #1
        serializer.save(*(tensor_mapA.get()));

        fl::DataMetadata metaA = serializer.getMetadata();
        ASSERT_EQ("success", metaA.get("save_result"));
        ASSERT_EQ(jsonl_file, metaA.get("tensor_map_file"));
        ASSERT_EQ(index_file, metaA.get("tensor_map_index_file"));

        // save #2
        serializer.save(*(tensor_mapB.get()));

        fl::DataMetadata metaB = serializer.getMetadata();
        ASSERT_EQ("success", metaB.get("save_result"));
        ASSERT_EQ(jsonl_file, metaB.get("tensor_map_file"));
        ASSERT_EQ(index_file, metaB.get("tensor_map_index_file"));

        fl::DataDeserializer deserializer = fl::DataDeserializer::createFor(metaB);

        ASSERT_EQ(2, deserializer.getNumOfData());
        std::shared_ptr<fl::TensorMap> tm1 = deserializer.get(1);
        std::shared_ptr<fl::Tensor> t1 = tm1->get("vector_string");
        ASSERT_EQ(this->test_suite_name, t1->textVector()[0]);
        ASSERT_EQ(this->name, t1->textVector()[1]);
        ASSERT_EQ("#1", t1->textVector()[2]);
        std::shared_ptr<fl::TensorMap> tm2 = deserializer.get(2);
        std::shared_ptr<fl::Tensor> t2 = tm2->get("vector_string");
        ASSERT_EQ(this->test_suite_name, t2->textVector()[0]);
        ASSERT_EQ(this->name, t2->textVector()[1]);
        ASSERT_EQ("#2", t2->textVector()[2]);
    });
}

TEST_F(TestDataSerializer, save_the_tensor_map_twice_in_a_row___success_x2_but_no_permit)
{
    std::vector<std::string> vector_stringA { this->test_suite_name, this->name, "#1" };
    std::vector<std::string> vector_stringB { this->test_suite_name, this->name, "#2" };

    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({3}));

    std::shared_ptr<fl::TensorMap> tensor_mapA(fl::TensorMap::newInstance());
    std::shared_ptr<fl::Tensor> tensor_stringA(fl::Tensor::newTensor(vector_stringA, shape));
    tensor_mapA->set("vector_string", tensor_stringA);

    std::shared_ptr<fl::TensorMap> tensor_mapB(fl::TensorMap::newInstance());
    std::shared_ptr<fl::Tensor> tensor_stringB(fl::Tensor::newTensor(vector_stringB, shape));
    tensor_mapB->set("vector_string", tensor_stringB);

    ASSERT_NO_THROW({
        // createFor
        fl::DataSerializer serializer = fl::DataSerializer::createFor(this->jsonl_file, this->index_file);

        // chmod 0400 -r--------
        chmod(this->jsonl_file.c_str(), S_IRUSR);

        // DO NOT CALL serializer.close()

        // save #1
        serializer.save(*(tensor_mapA.get()));

        fl::DataMetadata metaA = serializer.getMetadata();
        ASSERT_EQ("success", metaA.get("save_result"));
        ASSERT_EQ(jsonl_file, metaA.get("tensor_map_file"));
        ASSERT_EQ(index_file, metaA.get("tensor_map_index_file"));

        // save #2
        serializer.save(*(tensor_mapB.get()));

        fl::DataMetadata metaB = serializer.getMetadata();
        ASSERT_EQ("success", metaB.get("save_result"));
        ASSERT_EQ(jsonl_file, metaB.get("tensor_map_file"));
        ASSERT_EQ(index_file, metaB.get("tensor_map_index_file"));

        // chmod 0600 -rw-------
        chmod(this->index_file.c_str(), S_IWUSR|S_IRUSR);

        fl::DataDeserializer deserializer = fl::DataDeserializer::createFor(metaB);

        ASSERT_EQ(2, deserializer.getNumOfData());
        std::shared_ptr<fl::TensorMap> tm1 = deserializer.get(1);
        std::shared_ptr<fl::Tensor> t1 = tm1->get("vector_string");
        ASSERT_EQ(this->test_suite_name, t1->textVector()[0]);
        ASSERT_EQ(this->name, t1->textVector()[1]);
        ASSERT_EQ("#1", t1->textVector()[2]);
        std::shared_ptr<fl::TensorMap> tm2 = deserializer.get(2);
        std::shared_ptr<fl::Tensor> t2 = tm2->get("vector_string");
        ASSERT_EQ(this->test_suite_name, t2->textVector()[0]);
        ASSERT_EQ(this->name, t2->textVector()[1]);
        ASSERT_EQ("#2", t2->textVector()[2]);
    });
}

TEST_F(TestDataSerializer, save_the_tensor_map_twice_separately___success_x2)
{
    std::vector<std::string> vector_stringA { this->test_suite_name, this->name, "#1" };
    std::vector<std::string> vector_stringB { this->test_suite_name, this->name, "#2" };

    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({3}));

    std::shared_ptr<fl::Tensor> tensor_stringA(fl::Tensor::newTensor(vector_stringA, shape));

    std::shared_ptr<fl::TensorMap> tensor_mapA(fl::TensorMap::newInstance());
    tensor_mapA->set("vector_string", tensor_stringA);

    ASSERT_NO_THROW({
        // createFor #1
        fl::DataSerializer serializerA = fl::DataSerializer::createFor(this->jsonl_file, this->index_file);

        // save
        serializerA.save(*(tensor_mapA.get()));

        fl::DataMetadata metaA = serializerA.getMetadata();
        ASSERT_EQ("success", metaA.get("save_result"));
        ASSERT_EQ(jsonl_file, metaA.get("tensor_map_file"));
        ASSERT_EQ(index_file, metaA.get("tensor_map_index_file"));

        std::shared_ptr<fl::Tensor> tensor_stringB(fl::Tensor::newTensor(vector_stringB, shape));

        std::shared_ptr<fl::TensorMap> tensor_mapB(fl::TensorMap::newInstance());
        tensor_mapB->set("vector_string", tensor_stringB);

        // createFor #2
        fl::DataSerializer serializerB = fl::DataSerializer::createFor(this->jsonl_file, this->index_file);

        // save
        serializerB.save(*(tensor_mapB.get()));

        fl::DataMetadata metaB = serializerB.getMetadata();
        ASSERT_EQ("success", metaB.get("save_result"));
        ASSERT_EQ(jsonl_file, metaB.get("tensor_map_file"));
        ASSERT_EQ(index_file, metaB.get("tensor_map_index_file"));

        fl::DataDeserializer deserializer = fl::DataDeserializer::createFor(metaB);

        ASSERT_EQ(2, deserializer.getNumOfData());
        std::shared_ptr<fl::TensorMap> tm1 = deserializer.get(1);
        std::shared_ptr<fl::Tensor> t1 = tm1->get("vector_string");
        ASSERT_EQ(this->test_suite_name, t1->textVector()[0]);
        ASSERT_EQ(this->name, t1->textVector()[1]);
        ASSERT_EQ("#1", t1->textVector()[2]);
        std::shared_ptr<fl::TensorMap> tm2 = deserializer.get(2);
        std::shared_ptr<fl::Tensor> t2 = tm2->get("vector_string");
        ASSERT_EQ(this->test_suite_name, t2->textVector()[0]);
        ASSERT_EQ(this->name, t2->textVector()[1]);
        ASSERT_EQ("#2", t2->textVector()[2]);
    });
}

TEST_F(TestDataSerializer, save_the_tensor_map_twice_in_a_row___failed_x2)
{
    std::vector<std::string> vector_stringA { this->test_suite_name, this->name, "#1" };
    std::vector<std::string> vector_stringB { this->test_suite_name, this->name, "#2" };

    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({3}));

    std::shared_ptr<fl::TensorMap> tensor_mapA(fl::TensorMap::newInstance());
    std::shared_ptr<fl::Tensor> tensor_stringA(fl::Tensor::newTensor(vector_stringA, shape));
    tensor_mapA->set("vector_string", tensor_stringA);

    std::shared_ptr<fl::TensorMap> tensor_mapB(fl::TensorMap::newInstance());
    std::shared_ptr<fl::Tensor> tensor_stringB(fl::Tensor::newTensor(vector_stringB, shape));
    tensor_mapB->set("vector_string", tensor_stringB);

    ASSERT_NO_THROW({
        // createFor
        fl::DataSerializer serializer = fl::DataSerializer::createFor(this->jsonl_file, this->index_file);

        // close
        serializer.close();

        // chmod 0400 -r--------
        chmod(this->jsonl_file.c_str(), S_IRUSR);

        // save #1
        serializer.save(*(tensor_mapA.get()));

        fl::DataMetadata metaA = serializer.getMetadata();
        ASSERT_EQ("failed", metaA.get("save_result"));
        ASSERT_EQ(jsonl_file, metaA.get("tensor_map_file"));
        ASSERT_EQ(index_file, metaA.get("tensor_map_index_file"));

        // save #2
        serializer.save(*(tensor_mapB.get()));

        fl::DataMetadata metaB = serializer.getMetadata();
        ASSERT_EQ("failed", metaB.get("save_result"));
        ASSERT_EQ(jsonl_file, metaB.get("tensor_map_file"));
        ASSERT_EQ(index_file, metaB.get("tensor_map_index_file"));

        // chmod 0600 -rw-------
        chmod(this->index_file.c_str(), S_IWUSR|S_IRUSR);

        fl::DataDeserializer deserializer = fl::DataDeserializer::createFor(metaB);

        ASSERT_EQ(0, deserializer.getNumOfData());
    });
}

TEST_F(TestDataSerializer, save_the_tensor_map_twice_separately___success_x2_revoke_permit_after_createFor_1)
{
    std::vector<std::string> vector_stringA { this->test_suite_name, this->name, "#1" };
    std::vector<std::string> vector_stringB { this->test_suite_name, this->name, "#2" };

    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({3}));

    std::shared_ptr<fl::TensorMap> tensor_mapA(fl::TensorMap::newInstance());
    std::shared_ptr<fl::Tensor> tensor_stringA(fl::Tensor::newTensor(vector_stringA, shape));
    tensor_mapA->set("vector_string", tensor_stringA);

    std::shared_ptr<fl::TensorMap> tensor_mapB(fl::TensorMap::newInstance());
    std::shared_ptr<fl::Tensor> tensor_stringB(fl::Tensor::newTensor(vector_stringB, shape));
    tensor_mapB->set("vector_string", tensor_stringB);

    ASSERT_NO_THROW({
        // createFor #1
        fl::DataSerializer serializerA = fl::DataSerializer::createFor(this->jsonl_file, this->index_file);

        // chmod 0400 -r--------
        chmod(this->jsonl_file.c_str(), S_IRUSR);

        // DO NOT CALL serializerA.close()

        // save
        serializerA.save(*(tensor_mapA.get()));

        fl::DataMetadata metaA = serializerA.getMetadata();
        ASSERT_EQ("success", metaA.get("save_result"));
        ASSERT_EQ(jsonl_file, metaA.get("tensor_map_file"));
        ASSERT_EQ(index_file, metaA.get("tensor_map_index_file"));

        // chmod 0600 -rw-------
        chmod(this->jsonl_file.c_str(), S_IWUSR|S_IRUSR);

        // createFor #2
        fl::DataSerializer serializerB = fl::DataSerializer::createFor(this->jsonl_file, this->index_file);

        // chmod 0400 -r--------
        chmod(this->jsonl_file.c_str(), S_IRUSR);

        // DO NOT CALL serializerB.close()

        // save
        serializerB.save(*(tensor_mapB.get()));

        fl::DataMetadata metaB = serializerB.getMetadata();
        ASSERT_EQ("success", metaB.get("save_result"));
        ASSERT_EQ(jsonl_file, metaB.get("tensor_map_file"));
        ASSERT_EQ(index_file, metaB.get("tensor_map_index_file"));

        // chmod 0600 -rw-------
        chmod(this->jsonl_file.c_str(), S_IWUSR|S_IRUSR);

        fl::DataDeserializer deserializer = fl::DataDeserializer::createFor(metaB);

        ASSERT_EQ(2, deserializer.getNumOfData());
        std::shared_ptr<fl::TensorMap> tm1 = deserializer.get(1);
        std::shared_ptr<fl::Tensor> t1 = tm1->get("vector_string");
        ASSERT_EQ(this->test_suite_name, t1->textVector()[0]);
        ASSERT_EQ(this->name, t1->textVector()[1]);
        ASSERT_EQ("#1", t1->textVector()[2]);
        std::shared_ptr<fl::TensorMap> tm2 = deserializer.get(2);
        std::shared_ptr<fl::Tensor> t2 = tm2->get("vector_string");
        ASSERT_EQ(this->test_suite_name, t2->textVector()[0]);
        ASSERT_EQ(this->name, t2->textVector()[1]);
        ASSERT_EQ("#2", t2->textVector()[2]);
    });
}

TEST_F(TestDataSerializer, save_the_tensor_map_twice_in_a_row___success_failed)
{
    std::vector<std::string> vector_stringA { this->test_suite_name, this->name, "#1" };
    std::vector<std::string> vector_stringB { this->test_suite_name, this->name, "#2" };

    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({3}));

    std::shared_ptr<fl::TensorMap> tensor_mapA(fl::TensorMap::newInstance());
    std::shared_ptr<fl::Tensor> tensor_stringA(fl::Tensor::newTensor(vector_stringA, shape));
    tensor_mapA->set("vector_string", tensor_stringA);

    std::shared_ptr<fl::TensorMap> tensor_mapB(fl::TensorMap::newInstance());
    std::shared_ptr<fl::Tensor> tensor_stringB(fl::Tensor::newTensor(vector_stringB, shape));
    tensor_mapB->set("vector_string", tensor_stringB);

    ASSERT_NO_THROW({
        // createFor
        fl::DataSerializer serializer = fl::DataSerializer::createFor(this->jsonl_file, this->index_file);

        // save #1
        serializer.save(*(tensor_mapA.get()));

        fl::DataMetadata metaA = serializer.getMetadata();
        ASSERT_EQ("success", metaA.get("save_result"));
        ASSERT_EQ(jsonl_file, metaA.get("tensor_map_file"));
        ASSERT_EQ(index_file, metaA.get("tensor_map_index_file"));

        // chmod 0400 -r--------
        chmod(this->jsonl_file.c_str(), S_IRUSR);

        // close
        serializer.close();

        // save #2
        serializer.save(*(tensor_mapB.get()));

        fl::DataMetadata metaB = serializer.getMetadata();
        ASSERT_EQ("failed", metaB.get("save_result"));
        ASSERT_EQ(jsonl_file, metaB.get("tensor_map_file"));
        ASSERT_EQ(index_file, metaB.get("tensor_map_index_file"));

        // chmod 0600 -rw-------
        chmod(this->index_file.c_str(), S_IWUSR|S_IRUSR);

        fl::DataDeserializer deserializer = fl::DataDeserializer::createFor(metaB);

        ASSERT_EQ(1, deserializer.getNumOfData());
        std::shared_ptr<fl::TensorMap> tm1 = deserializer.get(1);
        std::shared_ptr<fl::Tensor> t1 = tm1->get("vector_string");
        ASSERT_EQ(this->test_suite_name, t1->textVector()[0]);
        ASSERT_EQ(this->name, t1->textVector()[1]);
        ASSERT_EQ("#1", t1->textVector()[2]);
    });
}

TEST_F(TestDataSerializer, save_the_tensor_map_twice_separately___success_x2_revoke_permit_after_createFor_2)
{
    std::vector<std::string> vector_stringA { this->test_suite_name, this->name, "#1" };
    std::vector<std::string> vector_stringB { this->test_suite_name, this->name, "#2" };

    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({3}));

    std::shared_ptr<fl::TensorMap> tensor_mapA(fl::TensorMap::newInstance());
    std::shared_ptr<fl::Tensor> tensor_stringA(fl::Tensor::newTensor(vector_stringA, shape));
    tensor_mapA->set("vector_string", tensor_stringA);

    std::shared_ptr<fl::TensorMap> tensor_mapB(fl::TensorMap::newInstance());
    std::shared_ptr<fl::Tensor> tensor_stringB(fl::Tensor::newTensor(vector_stringB, shape));
    tensor_mapB->set("vector_string", tensor_stringB);

    ASSERT_NO_THROW({
        // createFor #1
        fl::DataSerializer serializerA = fl::DataSerializer::createFor(this->jsonl_file, this->index_file);

        // save
        serializerA.save(*(tensor_mapA.get()));

        fl::DataMetadata metaA = serializerA.getMetadata();
        ASSERT_EQ("success", metaA.get("save_result"));
        ASSERT_EQ(jsonl_file, metaA.get("tensor_map_file"));
        ASSERT_EQ(index_file, metaA.get("tensor_map_index_file"));

        // createFor #2
        fl::DataSerializer serializerB = fl::DataSerializer::createFor(this->jsonl_file, this->index_file);

        // chmod 0400 -r--------
        chmod(this->jsonl_file.c_str(), S_IRUSR);

        // DO NOT CALL serializerB.close()

        // save
        serializerB.save(*(tensor_mapB.get()));

        fl::DataMetadata metaB = serializerB.getMetadata();
        ASSERT_EQ("success", metaB.get("save_result"));
        ASSERT_EQ(jsonl_file, metaB.get("tensor_map_file"));
        ASSERT_EQ(index_file, metaB.get("tensor_map_index_file"));

        // chmod 0600 -rw-------
        chmod(this->jsonl_file.c_str(), S_IWUSR|S_IRUSR);

        fl::DataDeserializer deserializer = fl::DataDeserializer::createFor(metaB);

        ASSERT_EQ(2, deserializer.getNumOfData());
        std::shared_ptr<fl::TensorMap> tm1 = deserializer.get(1);
        std::shared_ptr<fl::Tensor> t1 = tm1->get("vector_string");
        ASSERT_EQ(this->test_suite_name, t1->textVector()[0]);
        ASSERT_EQ(this->name, t1->textVector()[1]);
        ASSERT_EQ("#1", t1->textVector()[2]);
        std::shared_ptr<fl::TensorMap> tm2 = deserializer.get(2);
        std::shared_ptr<fl::Tensor> t2 = tm2->get("vector_string");
        ASSERT_EQ(this->test_suite_name, t2->textVector()[0]);
        ASSERT_EQ(this->name, t2->textVector()[1]);
        ASSERT_EQ("#2", t2->textVector()[2]);
    });
}

TEST_F(TestDataSerializer, save_the_tensor_map_twice_in_a_row___success_failed_success)
{
    std::vector<std::string> vector_stringA { this->test_suite_name, this->name, "#1" };
    std::vector<std::string> vector_stringB { this->test_suite_name, this->name, "#2" };
    std::vector<std::string> vector_stringC { this->test_suite_name, this->name, "#3" };

    std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({3}));

    std::shared_ptr<fl::TensorMap> tensor_mapA(fl::TensorMap::newInstance());
    std::shared_ptr<fl::Tensor> tensor_stringA(fl::Tensor::newTensor(vector_stringA, shape));
    tensor_mapA->set("vector_string", tensor_stringA);

    std::shared_ptr<fl::TensorMap> tensor_mapB(fl::TensorMap::newInstance());
    std::shared_ptr<fl::Tensor> tensor_stringB(fl::Tensor::newTensor(vector_stringB, shape));
    tensor_mapB->set("vector_string", tensor_stringB);

    std::shared_ptr<fl::TensorMap> tensor_mapC(fl::TensorMap::newInstance());
    std::shared_ptr<fl::Tensor> tensor_stringC(fl::Tensor::newTensor(vector_stringC, shape));
    tensor_mapC->set("vector_string", tensor_stringC);

    ASSERT_NO_THROW({
        // createFor
        fl::DataSerializer serializer = fl::DataSerializer::createFor(this->jsonl_file, this->index_file);

        // save #1
        serializer.save(*(tensor_mapA.get()));

        fl::DataMetadata metaA = serializer.getMetadata();
        ASSERT_EQ("success", metaA.get("save_result"));
        ASSERT_EQ(jsonl_file, metaA.get("tensor_map_file"));
        ASSERT_EQ(index_file, metaA.get("tensor_map_index_file"));

        // close
        serializer.close();

        // chmod 0400 -r--------
        chmod(this->jsonl_file.c_str(), S_IRUSR);

        // save #2
        serializer.save(*(tensor_mapB.get()));

        fl::DataMetadata metaB = serializer.getMetadata();
        ASSERT_EQ("failed", metaB.get("save_result"));
        ASSERT_EQ(jsonl_file, metaB.get("tensor_map_file"));
        ASSERT_EQ(index_file, metaB.get("tensor_map_index_file"));

        // chmod 0600 -rw-------
        chmod(this->jsonl_file.c_str(), S_IWUSR|S_IRUSR);

        // save #3
        serializer.save(*(tensor_mapC.get()));

        fl::DataMetadata metaC = serializer.getMetadata();
        ASSERT_EQ("failed", metaC.get("save_result"));
        ASSERT_EQ(jsonl_file, metaC.get("tensor_map_file"));
        ASSERT_EQ(index_file, metaC.get("tensor_map_index_file"));

        fl::DataDeserializer deserializer = fl::DataDeserializer::createFor(metaC);

        ASSERT_EQ(2, deserializer.getNumOfData());
        std::shared_ptr<fl::TensorMap> tm1 = deserializer.get(1);
        std::shared_ptr<fl::Tensor> t1 = tm1->get("vector_string");
        ASSERT_EQ(this->test_suite_name, t1->textVector()[0]);
        ASSERT_EQ(this->name, t1->textVector()[1]);
        ASSERT_EQ("#1", t1->textVector()[2]);
        std::shared_ptr<fl::TensorMap> tm2 = deserializer.get(2);
        std::shared_ptr<fl::Tensor> t2 = tm2->get("vector_string");
        ASSERT_EQ(this->test_suite_name, t2->textVector()[0]);
        ASSERT_EQ(this->name, t2->textVector()[1]);
        ASSERT_EQ("#3", t2->textVector()[2]);
    });
}

TEST_F(TestDataSerializer, getMetadata_before_save)
{
    ASSERT_NO_THROW({
        fl::DataSerializer serializer = fl::DataSerializer::createFor(this->jsonl_file, this->index_file);
        fl::DataMetadata meta = serializer.getMetadata();
        ASSERT_EQ("", meta.get("save_result"));
        ASSERT_EQ(jsonl_file, meta.get("tensor_map_file"));
        ASSERT_EQ(index_file, meta.get("tensor_map_index_file"));
    });
}
