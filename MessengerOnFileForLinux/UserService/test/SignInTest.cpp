#include <gtest/gtest.h>

#include <SignInTestCore.hpp>

TEST_F(SignInTestFixture, signInLoggedUser)
{
    std::istringstream stream("1\n1");
    std::cin.rdbuf(stream.rdbuf());

    registerUser.registerNewUser();
    EXPECT_TRUE(signIn.signInUser());
    EXPECT_FALSE(signIn.signInUser());
    signOut.signOutUser();
}

TEST_F(SignInTestFixture, signInUnregisteredUser)
{
    std::istringstream stream("1\n1");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_TRUE(signIn.signInUser());
    std::string rowBuff = *FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED_FILE ,user);
    signOut.signOutUser();
    FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED_FILE ,user);
    EXPECT_FALSE(signIn.signInUser());
    FileInterface::Modification::addRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED_FILE, rowBuff);
}

TEST_F(SignInTestFixture, signInUnloggedUser)
{
    std::istringstream stream("1");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_TRUE(signIn.signInUser());
    signOut.signOutUser();
}

TEST_F(SignInTestFixture, signInWithUncorrectPassword)
{
    std::istringstream stream("2\n3\n0");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_FALSE(signIn.signInUser());
}

TEST_F(SignInTestFixture, signInWithoutPassword)
{
    std::istringstream stream("\n");
    std::cin.rdbuf(stream.rdbuf());

    EXPECT_FALSE(signIn.signInUser());
}

TEST_F(SignInTestFixture, isUserCorrectlyAddedToLoggedFile)
{
    std::istringstream stream("1");
    std::cin.rdbuf(stream.rdbuf());

    std::unique_ptr<std::string> userInfo = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::LOGGED_FILE, user);
    EXPECT_EQ(nullptr, userInfo);
    signIn.signInUser();
    userInfo = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::LOGGED_FILE, user);
    std::string expectedOutput = "[" + user + "][" + FileStructure::FieldValue::userActiveStatus + "]";
    EXPECT_EQ(expectedOutput, *userInfo);
    signOut.signOutUser();
}
