#include <gtest/gtest.h>
#include <StringSum.hpp>

TEST(StringSumTest, isStringsAreSummedWithBrackets)
{
    StringSumSquareBrackets summedString;
    const std::string expectedString = "[This ][string ][is][ summed.]";
    summedString.sum("This ");
    summedString.sum("string ");
    summedString.sum("is");
    summedString.sum(" summed.");

    EXPECT_EQ(summedString.getSumedString(), expectedString);
}
