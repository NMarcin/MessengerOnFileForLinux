#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ncurses.h>
#include <memory>


#include <RegisterUser.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>
#include <SHA1.hpp>


SHA1 sha1;
std::string user = getenv("USER");

using namespace ::testing;
class MockRegister : public std::basic_istream{
  public:
    MOCK_CONST_METHOD0(enterThePassword, std::string());
    //MOCK_CONST_METHOD0(registerNewUser, bool());
   // MOCK_CONST_METHOD0(isUserRegistered, bool());

};

TEST(RegisterUserTest, registerNewUser)
{
    MockRegister mock;

    EXPECT_CALL(mock, enterThePassword()).Times(2).WillRepeatedly(Return(std::string{"1"}));
    //EXPECT_CALL(mock, enterThePassword()).Times(2).WillOnce(Return(std::string{"1"})).WillOnce(Return(std::string{"2"}));

    mock.registerNewUser();
    FileInterface::Modification::removeRow(ENVIRONMENT_PATH::TO_FILE::REGISTERED ,user);
//mock.registerNewUser();

    //endwin();
}

/*
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

*/
