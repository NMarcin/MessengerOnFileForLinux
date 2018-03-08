#include "LocalUser.hpp"
#include "FileHandling.hpp"


LocalUser::LocalUser() : User(getEnviromentalVariable("USER"))
{

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
