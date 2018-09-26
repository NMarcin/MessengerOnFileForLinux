#include <gtest/gtest.h>
#include <ncurses.h>

#include <RegisterUser.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <SHA1.hpp>

RegisterUser registerUser;
SHA1 sha1;
std::string user = getenv("USER");

TEST(RegisterUserTest, registerNewUser)
{
    std::istringstream stream("1\n1");
    std::cin.rdbuf(stream.rdbuf());
    FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED ,user);

    EXPECT_TRUE(registerUser.registerNewUser());
    endwin();
}

TEST(RegisterUserTest, registerRegisteredUser)
{

    std::istringstream stream("1\n1\n1\n1");
    std::cin.rdbuf(stream.rdbuf());
    FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED ,user);

    EXPECT_TRUE(registerUser.registerNewUser());
    EXPECT_FALSE(registerUser.registerNewUser());

}

TEST(RegisterUserTest, registerUserWithDifferentPasswords)
{

    std::istringstream stream("1\n0\n2\n1\n1\n1");
    std::cin.rdbuf(stream.rdbuf());
    FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED ,user);

    EXPECT_TRUE(registerUser.registerNewUser());

}

TEST(RegisterUserTest, isUserCorrectlyAddedRegisterededFile)
{

    std::istringstream stream("1\n1");
    std::cin.rdbuf(stream.rdbuf());
    sha1.update("1");
    std::string hashedPassword = sha1.final();

    FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED ,user);
    auto rowFromRegisteredFile = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED ,user);
    EXPECT_EQ(nullptr, rowFromRegisteredFile);

    registerUser.registerNewUser();
    rowFromRegisteredFile = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED ,user);
    std::string expectedRow = "[" + user +"][" + hashedPassword + "]";
    EXPECT_EQ(expectedRow, *rowFromRegisteredFile);

}
