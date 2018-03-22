#include <gtest/gtest.h>
#include <ChatFabric.hpp>
#include <string>

#include <GlobalVariables.hpp>
#include <FileHandling.hpp>

std::string chatPath = static_cast<std::string>(CHATS_PATH) + "0inviterU_receiver/";
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

    bool isEmpty = FileInterface::getFilesNames(chatPath)->empty();

    EXPECT_FALSE(isEmpty);
}

TEST(ChatFileTest, isFileCreated)
{
    folderDeleter();
    ChatFabric chatFabric;
    chatFabric.createChatStructure("inviterU", "receiver");

    bool isFileExists = FileInterface::isFileExists(chatPath + fileName);

    EXPECT_TRUE(isFileExists);
}

TEST(ChatFileTest, canWeWriteToFile)
{
    folderDeleter();
    ChatFabric chatFabric;
    chatFabric.createChatStructure("inviterU", "receiver");

    bool writingToFile = FileInterface::addRow(chatPath + fileName, "Test row");

    EXPECT_TRUE(writingToFile);
}

TEST(ChatFileTest, canWeReadFromFile)
{
    folderDeleter();
    ChatFabric chatFabric;
    chatFabric.createChatStructure("inviterU", "receiver");

    bool writingToFile = FileInterface::addRow(chatPath + fileName, "Test row");

    ASSERT_TRUE(writingToFile);

    bool readingFromFile = !FileInterface::getFileContent(chatPath + fileName)->empty();

    EXPECT_TRUE(readingFromFile);
}

TEST(ChatFileTest, canWeCreateFilesInFolder)
{
    folderDeleter();
    ChatFabric chatFabric;
    chatFabric.createChatStructure("inviterU", "receiver");

    bool createFileSucces = FileInterface::createFile(chatPath + "test_file");

    EXPECT_TRUE(createFileSucces);
}
