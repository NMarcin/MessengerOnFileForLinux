#include <gtest/gtest.h>
#include <StringSum.hpp>

TEST(StringSumTest, sumString)
{
    StringSumSquareBrackets summedString;
    std::string expectedString = "[This ][string ][is][ summed.]";
    summedString.sum("This ");
    summedString.sum("string ");
    summedString.sum("is");
    summedString.sum(" summed.");

    EXPECT_EQ(summedString.getSumedString(), expectedString);
}
