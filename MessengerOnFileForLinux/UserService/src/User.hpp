#pragma once
#include <string>

class User
{
public:
    std::string getUsername() const;
    std::string getPassword() const;
    int getUserProcessID() const;
    void setPassword(const std::string & password);
    void setUsername(const std::string & password);
    void setUserPorcessID(const int userProcessID);
    int getUserProcessIdFromSystem() const;

    User(std::string username);
    User();
    ~User();

private:
    std::string username_;
    std::string password_;
    int userProcessID_;
};

