#include <fstream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <nlohmann/json.hpp>

#include "FLException.h"

using json = nlohmann::json;

TEST(TestFLException, testThrowFLException)
{
    ASSERT_THROW(THROW_FL_EXCEPTION("Test throw FLException"), FLException);
}

TEST(TestFLException, testFLExceptionMessage)
{
    try {
        THROW_FL_EXCEPTION(str_format("I'm %s. Pi is %f.", "FLException", 3.141592));
        FAIL();
    }
    catch (FLException ex) {
        ASSERT_THAT(ex.what(), testing::MatchesRegex("I'm FLException\\. Pi is 3\\.141592\\. \\[.+\\]"));
    }
}

TEST(TestFLException, test_nlohmann_json)
{
    ASSERT_THROW({
        try {
            json invalid = json::parse("{don't mind}");
            FAIL();
        }
        catch (json::exception& ex) {
            std::cerr << "caught exception: " << ex.what() << std::endl;
            THROW_FL_EXCEPTION(str_format("json parse error. [%s]", ex.what()));
        }
    }, FLException);
}
