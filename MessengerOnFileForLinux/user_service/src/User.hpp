#pragma once
#include <string>

class User
{
public:
    User();
    std::string getUsername() const {return username_;}
    std::string getPassword() const {return password_;}
    void setPassword(std::string password){password_ = password;}
private:
    std::string username_;
    std::string password_;
};

