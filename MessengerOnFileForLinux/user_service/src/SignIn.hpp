#pragma once
#include "User.hpp"
#include <string>
#include <memory>

class SignIn
{
public:
    SignIn(){} //wyrzucic ?
    bool signIn(std::string password);
private:
    bool isUserLogged(User & user);
    bool isPasswordCorrect(std::string password, std::string correctPassword);
    std::unique_ptr< std::string> getPasswordFromDatabase(User & user);
    bool setUserDataInLoggedFile(User & user);

};
