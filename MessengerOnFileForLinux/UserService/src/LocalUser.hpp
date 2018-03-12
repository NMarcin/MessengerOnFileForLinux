#pragma once
#include <User.hpp>

class LocalUser : public User
{
public:
    virtual std::string getUsername() const override;
    static LocalUser & getLocalUser();

private:
    LocalUser();
    ~LocalUser();
    LocalUser(const LocalUser &) = delete;
    LocalUser& operator=(const LocalUser &) = delete;
};

