#include <gtest/gtest.h>

#include <SignOut.hpp>
#include <SignIn.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>

TEST(SignOutTest, isUserSignOutCorrectly)
{
    std::string USER = getenv("USER");
    auto rowFromFile = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, USER);
    EXPECT_TRUE(nullptr == rowFromFile);

    std::string rowInLoggedFile = "[" + USER + "][0]";
    FileInterface::Modification::addRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, rowInLoggedFile);

    rowFromFile = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, USER);
    std::string username = *FileInterface::Accesor::getRowField(*rowFromFile, FileStructure::LoggedFile::username);
    EXPECT_EQ(username, USER);

    SignOut signOut;
    signOut.signOutUser();

    rowFromFile = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, USER);
    EXPECT_TRUE(nullptr == rowFromFile);
}
