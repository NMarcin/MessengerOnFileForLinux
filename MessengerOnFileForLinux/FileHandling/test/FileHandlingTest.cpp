#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include <FileHandling.hpp>
#include <GlobalVariables.hpp>

std::string filename = "test.txt";

TEST(FileHandlingTest, createFile)
{
    FileInterface::Managment::createFile(filename);
    int isFileExist = access(filename.c_str(), F_OK );
    ASSERT_TRUE(-1 != isFileExist);
    std::string command = "rm " + filename;
    system(command.c_str());
}

TEST(FileHandlingTest, isFileExist)
{
    EXPECT_FALSE(FileInterface::Managment::isFileExist(filename));
    FileInterface::Managment::createFile(filename);
    EXPECT_TRUE(FileInterface::Managment::isFileExist(filename));
    std::string command = "rm " + filename;
    system(command.c_str());
}

TEST(FileHandlingTest, removeFile)
{
    FileInterface::Managment::createFile(filename);
    EXPECT_TRUE(FileInterface::Managment::isFileExist(filename));
    FileInterface::Managment::removeFile(filename);
    EXPECT_FALSE(FileInterface::Managment::isFileExist(filename));
}

/*
TEST(FileHandlingTest, getFileContent)
{
    //TODO testowy plik
    FileInterface::Managment::createFile(filename);
    std::string firstRow = "[marcin][13][323]";
    std::string secondRow = "[nurzyn][4][23aa]";
    std::string command_1 = "echo " + firstRow + " >> " + ENIVRONMENT_PATH::PATH_TO_FILE::LOGGED_FILE;
    std::string command_2 = "echo " + secondRow + " >> " + ENIVRONMENT_PATH::PATH_TO_FILE::LOGGED_FILE;
    system(command_1.c_str());
    system(command_2.c_str());
    auto  fileContent = FileInterface::Accesor::getFileContent(ENIVRONMENT_PATH::PATH_TO_FILE::LOGGED_FILE);
    EXPECT_EQ(fileContent->at(0), firstRow);
    EXPECT_EQ(fileContent->at(1), secondRow);
    FileInterface::Managment::removeFile(filename);
}
*/
