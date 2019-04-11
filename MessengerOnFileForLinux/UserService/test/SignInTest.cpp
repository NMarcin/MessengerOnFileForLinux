#include <gtest/gtest.h>

#include "SignInTestCore.hpp"

TEST_F(SignInTestFixture, signInLoggedUser)
{
    std::istringstream stream("1\n1");
    std::cin.rdbuf(stream.rdbuf());

    _registerUser.registerNewUser();
    EXPECT_TRUE(_signIn.signInUser());
    EXPECT_FALSE(_signIn.signInUser());
    _signOut.signOutUser();
}

TEST_F(SignInTestFixture, signInUnregisteredUser)
{
    std::istringstream stream("1\n1");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_TRUE(_signIn.signInUser());
    std::string rowBuff = *FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED , _user);
    _signOut.signOutUser();
    FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED, _user);
    EXPECT_FALSE(_signIn.signInUser());
    FileInterface::Modification::addRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED, rowBuff);
}

TEST_F(SignInTestFixture, signInUnloggedUser)
{
    std::istringstream stream("1");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_TRUE(_signIn.signInUser());
    _signOut.signOutUser();
}

TEST_F(SignInTestFixture, signInWithUncorrectPassword)
{
    std::istringstream stream("2\n3\n0");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_FALSE(_signIn.signInUser());
}

TEST_F(SignInTestFixture, signInWithoutPassword)
{
    std::istringstream stream("\n");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_FALSE(_signIn.signInUser());
}

TEST_F(SignInTestFixture, isUserCorrectlyAddedToLoggedFile)
{
    std::istringstream stream("1");
    std::cin.rdbuf(stream.rdbuf());

    std::unique_ptr<std::string> userInfo = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, _user);
    EXPECT_EQ(nullptr, userInfo);
    _signIn.signInUser();
    userInfo = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::LOGGED, _user);
    std::string expectedOutput = "[" + _user + "][" + UserStatus::activeStatus + "]";
    EXPECT_EQ(expectedOutput, *userInfo);
    _signOut.signOutUser();
}

