#pragma once

class Person {
protected:
    int id;
    char name[50];
    char password[50];

    void copyText(char* destination, const char* source, int maxLength);

public:
    Person();
    Person(int personID, const char* personName, const char* personPassword);
    virtual ~Person();

    int getID() const;
    const char* getName() const;
    const char* getPassword() const;

    void setID(int personID);
    void setName(const char* personName);
    bool setPassword(const char* personPassword);

    virtual void displayDashboard() = 0;
    virtual void showProfile() const = 0;
};
