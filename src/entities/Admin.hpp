#pragma once

#include "Person.hpp"

class Admin : public Person
{
public:
    Admin();
    Admin(int adminID, const char *adminName, const char *adminPassword);
    ~Admin();

    void displayDashboard();
    void showProfile() const;
};
