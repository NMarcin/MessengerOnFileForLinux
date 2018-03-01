#include "User.hpp"
#include "FileHandling.hpp"

User::User() : username_(getEnviromentalVariable("USER"))
{

}
