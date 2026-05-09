#include "Admin.hpp"

#include <iostream>

Admin::Admin() : Person()
{
}

Admin::Admin(int adminID, const char *adminName, const char *adminPassword)
    : Person(adminID, adminName, adminPassword)
{
}

Admin::~Admin()
{
}
