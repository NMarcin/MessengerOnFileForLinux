#pragma once
#include <User.hpp>

class LocalUser : public User
{
public:
    static LocalUser & getLocalUser();

private:
    LocalUser();
    ~LocalUser();
    LocalUser(const LocalUser &) = delete;
    LocalUser& operator=(const LocalUser &) = delete;
};

