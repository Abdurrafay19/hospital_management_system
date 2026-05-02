#pragma once

class Person
{
protected:
    int id;
    char *name;
    char *password;

public:
    Person();
    Person(int personID, const char *personName, const char *personPassword);
    Person(const Person &other);
    virtual ~Person();

    Person &operator=(const Person &other);

    int getID() const;
    const char *getName() const;
    const char *getPassword() const;

    void setID(int personID);
    void setName(const char *personName);
    bool setPassword(const char *personPassword);

    virtual void displayDashboard() = 0;
    virtual void showProfile() const = 0;
};
