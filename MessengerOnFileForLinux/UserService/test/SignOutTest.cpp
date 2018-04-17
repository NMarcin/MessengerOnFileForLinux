#include <gtest/gtest.h>

#include <SignOut.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>

std::string getUsernameFormLoggedFileIfExist(const std::string& user)
{
    std::string username;
    auto loggedFileContent = FileInterface::Accesor::getFileContent(ENVIRONMENT_PATH::TO_FILE::LOGGED_FILE);

    for (auto row : *loggedFileContent)
    {
        username = *FileInterface::Accesor::getRowField(row, FileStructure::FileField::usernameFieldInLoggedFile);
        if (username == user)
        {
            return username;
        }
    }
    return "";
}

TEST(SignOutTest, isUserSignOut)
{
    std::string USER = getenv("USER");
    std::string username = getUsernameFormLoggedFileIfExist(USER);
    EXPECT_TRUE(username.empty());

    std::string rowInLoggedFile = "[" + USER + "][0]";
    FileInterface::Modification::addRow(ENVIRONMENT_PATH::TO_FILE::LOGGED_FILE, rowInLoggedFile);

    username = getUsernameFormLoggedFileIfExist(USER);
    EXPECT_EQ(username, USER);

    SignOut signOut;
    signOut.signOutUser();

    username = getUsernameFormLoggedFileIfExist(USER);
    EXPECT_TRUE(username.empty());
}
