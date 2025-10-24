#include <fstream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "FLException.h"
#include "tensor/tensor_shape.h"

TEST(TestTensorShape, createShape_1D)                       // 正 dims{5}, dims, getDim, size, getDims
{
    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({5}));
    });
}

TEST(TestTensorShape, createShape_2D)                       // 正 dims{2,3}, dims, getDim, size, getDims
{
    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({2, 3}));
    });
}

TEST(TestTensorShape, createShape_3D)                       // 正 dims{2,3,4}, dims, getDim, size, getDims
{
    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({2, 3, 4}));
    });
}

TEST(TestTensorShape, createShape_named_1D)                 // 正 named dims{5}, dims, getDim, size, getDims
{
    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape("1D", {5}));
    });
}

TEST(TestTensorShape, createShape_named_2D)                 // 正 named dims{2,3}, dims, getDim, size, getDims
{
    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape("2D", {2, 3}));
    });
}

TEST(TestTensorShape, createShape_named_3D)                 // 正 named dims{2,3,4}, dims, getDim, size, getDims
{
    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape("3D", {2, 3, 4}));
    });
}

TEST(TestTensorShape, isSameSize_1D_match)                  // 正 {2}:{2}
{
    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorShape> shapeA(fl::TensorShape::createShape({2}));
        std::shared_ptr<fl::TensorShape> shapeB(fl::TensorShape::createShape({2}));
        shapeA->isSameSize(*shapeB);
    });
}

TEST(TestTensorShape, isSameSize_2D_match)                  // 正 {2,3}:{2,3}
{
    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorShape> shapeA(fl::TensorShape::createShape({2, 3}));
        std::shared_ptr<fl::TensorShape> shapeB(fl::TensorShape::createShape({2, 3}));
        shapeA->isSameSize(*shapeB);
    });
}

TEST(TestTensorShape, isSameSize_1D_size_does_not_match)    // 準 {2}:{3}
{
    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorShape> shapeA(fl::TensorShape::createShape({2}));
        std::shared_ptr<fl::TensorShape> shapeB(fl::TensorShape::createShape({2}));
        shapeA->isSameSize(*shapeB);
    });
    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorShape> shapeA(fl::TensorShape::createShape({2}));
        std::shared_ptr<fl::TensorShape> shapeB(fl::TensorShape::createShape({3}));
        ASSERT_FALSE(shapeA->isSameSize(*shapeB));
    });
}

TEST(TestTensorShape, isSameSize_2D_size_does_not_match)    // 準 {2,3}:{3,2}
{
    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorShape> shapeA(fl::TensorShape::createShape({2, 3}));
        std::shared_ptr<fl::TensorShape> shapeB(fl::TensorShape::createShape({2, 3}));
        shapeA->isSameSize(*shapeB);
    });
    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorShape> shapeA(fl::TensorShape::createShape({2, 3}));
        std::shared_ptr<fl::TensorShape> shapeB(fl::TensorShape::createShape({3, 2}));
        ASSERT_FALSE(shapeA->isSameSize(*shapeB));
    });
}

////////////////////////////////////////////////////////////////////////////////

TEST(TestTensorShape, createShape_0D)                           // 異 dims[0]
{
    try {
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({}));
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("dims are empty\\. \\[tensor/tensor_shape\\.cc:[0-9]+\\]"));
    }
}

TEST(TestTensorShape, createShape_named_0D)                     // 異 named dims[0]
{
    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({1}));
    });
    try {
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({}));
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("dims are empty\\. \\[tensor/tensor_shape\\.cc:[0-9]+\\]"));
    }
}

TEST(TestTensorShape, createShape_1D_contains_element_0)        // 異 dims[1] {0}
{
    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({1}));
    });
    try {
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({0}));
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Incorrect number of elements\\. \\(dims:0 \\[0/1\\]\\) \\[tensor/tensor_shape\\.cc:[0-9]+\\]"));
    }
}

TEST(TestTensorShape, createShape_2D_contains_element_0)        // 異 dims[2] {1, 0}
{
    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({1, 1}));
    });
    try {
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({1, 0}));
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Incorrect number of elements\\. \\(dims:0 \\[1/2\\]\\) \\[tensor/tensor_shape\\.cc:[0-9]+\\]"));
    }
}

TEST(TestTensorShape, createShape_1D_contains_element_negative) // 異 dims[1] {-1}
{
    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({1}));
    });
    try {
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({-1}));
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Incorrect number of elements\\. \\(dims:-1 \\[0/1\\]\\) \\[tensor/tensor_shape\\.cc:[0-9]+\\]"));
    }
}

TEST(TestTensorShape, createShape_2D_contains_element_negative) // 異 dims[2] {1, -1}
{
    ASSERT_NO_THROW({
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({1, 1}));
    });
    try {
        std::shared_ptr<fl::TensorShape> shape(fl::TensorShape::createShape({1, -1}));
        FAIL();
    }
    catch (FLException& ex) {
        const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
        std::cerr << "##### (" << test_info->test_suite_name() << ":" << test_info->name() << ")" << " Caught: " << ex.what() << std::endl;
        ASSERT_THAT(ex.what(), testing::MatchesRegex("Incorrect number of elements\\. \\(dims:-1 \\[1/2\\]\\) \\[tensor/tensor_shape\\.cc:[0-9]+\\]"));
    }
}
