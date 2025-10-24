#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "LinearHLCR/NormalDistribution.h"


TEST(testNormalDistribution_log_probability, BasicAssertions) {
    // Used scipy.stats.norm.logpdf to create this test cases
    EXPECT_DOUBLE_EQ(-0.9189385332046727, 
                     linear_hlcr::NormalDistribution::log_probability(1,1,1));
    EXPECT_DOUBLE_EQ(-1.4189385332046727, 
                     linear_hlcr::NormalDistribution::log_probability(2,1,1));
    EXPECT_DOUBLE_EQ(-1.4189385332046727, 
                     linear_hlcr::NormalDistribution::log_probability(1,2,1));
    EXPECT_DOUBLE_EQ(-1.612085713764618, 
                     linear_hlcr::NormalDistribution::log_probability(1,1,2));
    EXPECT_DOUBLE_EQ(-2.111073215959838,
                     linear_hlcr::NormalDistribution::log_probability(1.1,0.128,3.14));
}