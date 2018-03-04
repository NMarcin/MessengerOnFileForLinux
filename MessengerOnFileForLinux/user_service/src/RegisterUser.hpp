#pragma once
#include <string>
#include "User.hpp"

class RegisterUser
{
public:
    RegisterUser(){} // wyrzucic ?
    bool registerUser(std::string password, std::string repeatedPassword);
private:
    bool isUserRegistered(std::string username);
    bool saveUserDataInRegisteredFile(const User & user);
    void setUsernamePassword(std::string password, std::string repeatedPassword,
                             User & user);
};
