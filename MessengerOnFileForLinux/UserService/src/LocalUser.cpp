#include <LocalUser.hpp>
#include <FileHandling.hpp>

#include <iostream>

LocalUser::LocalUser()
        : User(getEnviromentVariable("USER"))
{
    //NOOP
}

LocalUser::~LocalUser()
{
    //NOOP
}

LocalUser & LocalUser::getLocalUser()
{
    static LocalUser localUser;
    return localUser;
}

std::string LocalUser::getUsername() const
{
    if (User::getUsername().empty())
    {
        std::string username = getEnviromentVariable("USER");
        return username;
    }

    return User::getUsername();
}
