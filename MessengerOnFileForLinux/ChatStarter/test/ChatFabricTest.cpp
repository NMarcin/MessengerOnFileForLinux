#include <gtest/gtest.h>
#include <ChatFabric.hpp>
#include <string>

#include <GlobalVariables.hpp>
#include <FileHandling.hpp>

std::string chatPath = ENVIRONMENT_PATH::TO_FOLDER::CHATS + "0inviterU_receiver/";
std::string fileName = "inviterU_receiver";

void folderDeleter()
{
    system(("rm -rf " + ENVIRONMENT_PATH::TO_FOLDER::CHATS + "*inviterU*").c_str());
}

TEST(ChatFileTest, isFolderCreated)
{

    ChatFabric chatFabric;
    chatFabric.createChatStructure("inviterU", "receiver");

    bool isEmpty = FileInterface::Accesor::getFilenamesFromFolder(chatPath)->empty();

    EXPECT_FALSE(isEmpty);
    folderDeleter();
}

TEST(ChatFileTest, isFileCreated)
{
    ChatFabric chatFabric;
    chatFabric.createChatStructure("inviterU", "receiver");

    bool isFileExists = FileInterface::Managment::isFileExist(chatPath + fileName);

    EXPECT_TRUE(isFileExists);
    folderDeleter();
}

TEST(ChatFileTest, canWeWriteToFile)
{
    ChatFabric chatFabric;
    chatFabric.createChatStructure("inviterU", "receiver");

    bool writingToFile = FileInterface::Modification::addRow(chatPath + fileName, "Test row");

    EXPECT_TRUE(writingToFile);
    folderDeleter();
}

TEST(ChatFileTest, canWeReadFromFile)
{
    ChatFabric chatFabric;
    chatFabric.createChatStructure("inviterU", "receiver");

    bool writingToFile = FileInterface::Modification::addRow(chatPath + fileName, "Test row");

    ASSERT_TRUE(writingToFile);

    bool readingFromFile = !FileInterface::Accesor::getFileContent(chatPath + fileName, AccesMode::withGuardian)->empty();

    EXPECT_TRUE(readingFromFile);
    folderDeleter();
}

TEST(ChatFileTest, canWeCreateFilesInFolder)
{
    ChatFabric chatFabric;
    chatFabric.createChatStructure("inviterU", "receiver");

    bool createFileSucces = FileInterface::Managment::createFile(chatPath + "test_file");
    EXPECT_TRUE(createFileSucces);
    folderDeleter();

}
