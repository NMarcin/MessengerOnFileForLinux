#include <gtest/gtest.h>
#include <ChatFabric.hpp>
#include <string>

#include <GlobalVariables.hpp>
#include <FileHandling.hpp>

std::string chatPath = ENIVRONMENT_PATH::PATH_TO_FOLDER::CHATS_FOLDER + "0inviterU_receiver/";
std::string fileName = "inviterU_receiver";

void folderDeleter()
{
    system(("rm -rf " + chatPath).c_str());
}

TEST(ChatFileTest, isFolderCreated)
{
    folderDeleter();
    ChatFabric chatFabric;
    chatFabric.createChatStructure("inviterU", "receiver");

    bool isEmpty = FileInterface::Accesor::getFilenamesFromFolder(chatPath)->empty();

    EXPECT_FALSE(isEmpty);
}

TEST(ChatFileTest, isFileCreated)
{
    folderDeleter();
    ChatFabric chatFabric;
    chatFabric.createChatStructure("inviterU", "receiver");

    bool isFileExists = FileInterface::Managment::isFileExist(chatPath + fileName);

    EXPECT_TRUE(isFileExists);
}

TEST(ChatFileTest, canWeWriteToFile)
{
    folderDeleter();
    ChatFabric chatFabric;
    chatFabric.createChatStructure("inviterU", "receiver");

    bool writingToFile = FileInterface::Modification::addRow(chatPath + fileName, "Test row");

    EXPECT_TRUE(writingToFile);
}

TEST(ChatFileTest, canWeReadFromFile)
{
    folderDeleter();
    ChatFabric chatFabric;
    chatFabric.createChatStructure("inviterU", "receiver");

    bool writingToFile = FileInterface::Modification::addRow(chatPath + fileName, "Test row");

    ASSERT_TRUE(writingToFile);

    bool readingFromFile = !FileInterface::Accesor::getFileContent(chatPath + fileName)->empty();

    EXPECT_TRUE(readingFromFile);
}

TEST(ChatFileTest, canWeCreateFilesInFolder)
{
    folderDeleter();
    ChatFabric chatFabric;
    chatFabric.createChatStructure("inviterU", "receiver");

    bool createFileSucces = FileInterface::Managment::createFile(chatPath + "test_file");

    EXPECT_TRUE(createFileSucces);
}