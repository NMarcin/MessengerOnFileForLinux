#include "RegisterUserTestCore.hpp"
#include "FileHandling.hpp"
#include "GlobalVariables.hpp"

TEST_F(RegisterUserTestFixture, registerNewUser)
{
    std::istringstream stream("1\n1");
    std::cin.rdbuf(stream.rdbuf());
    FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED ,_user);

    EXPECT_TRUE(_registerUser.registerNewUser());
}

TEST_F(RegisterUserTestFixture, registerRegisteredUser)
{
    std::istringstream stream("1\n1\n1\n1");
    std::cin.rdbuf(stream.rdbuf());
    FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED ,_user);

    EXPECT_TRUE(_registerUser.registerNewUser());
    EXPECT_FALSE(_registerUser.registerNewUser());

}

TEST_F(RegisterUserTestFixture, registerUserWithDifferentPasswords)
{
    std::istringstream stream("1\n0\n2\n1\n1\n1");
    std::cin.rdbuf(stream.rdbuf());
    FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED ,_user);

    EXPECT_TRUE(_registerUser.registerNewUser());

}

TEST_F(RegisterUserTestFixture, isUserCorrectlyAddedRegisterededFile)
{
    std::istringstream stream("1\n1");
    std::cin.rdbuf(stream.rdbuf());
    _sha1.update("1");
    std::string hashedPassword = _sha1.final();

    FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED ,_user);
    auto rowFromRegisteredFile = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED ,_user);
    EXPECT_EQ(nullptr, rowFromRegisteredFile);

    _registerUser.registerNewUser();
    rowFromRegisteredFile = FileInterface::Accesor::getRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED ,_user);
    std::string expectedRow = "[" + _user +"][" + hashedPassword + "]";
    EXPECT_EQ(expectedRow, *rowFromRegisteredFile);

}

