#include <gtest/gtest.h>
#include <iostream>

#include <SignIn.hpp>
#include <SignOut.hpp>
#include <RegisterUser.hpp>
#include <FileHandling.hpp>
#include <GlobalVariables.hpp>

const std::string user = getenv("USER");
SignIn signIn;
SignOut signOut;
RegisterUser registerUser;



TEST(SignInTest, signInLoggedUser)
{
    std::istringstream stream("1\n1\n1\n1");
    std::cin.rdbuf(stream.rdbuf());
    registerUser.registerNewUser();
    EXPECT_TRUE(signIn.signInUser());
    EXPECT_FALSE(signIn.signInUser());
    signOut.signOutUser();
}

TEST(SignInTest, signInUnregisteredUser)
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

TEST(SignInTest, signInUnloggedUser)
{
    std::istringstream stream("1");
    std::cin.rdbuf(stream.rdbuf());
    EXPECT_TRUE(signIn.signInUser());
    signOut.signOutUser();
}

//TODO sprawdzanie hasel i czy dobrze dodalo do pliku. moze fixutrka ?
