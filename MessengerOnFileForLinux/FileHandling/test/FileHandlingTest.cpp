#include <gtest/gtest.h>
#include <fstream>

#include <FileHandling.hpp>

TEST(FileHandlingTest, createFile)
{
    FileInterface::Managment::createFile("test.txt");
    std::ifstream file("test.txt");
    EXPECT_TRUE(file.good());
}
