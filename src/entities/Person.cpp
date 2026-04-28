#include "Person.hpp"
#include "../helpers/StringHelper.hpp"

#include "../core/Validator.hpp"

Person::Person() {
    id = 0;
    name = 0;
    password = 0;
}

Person::Person(int personID, const char* personName, const char* personPassword) {
    id = 0;
    name = 0;
    password = 0;

    setID(personID);
    setName(personName);
    setPassword(personPassword);
}

Person::Person(const Person& other) {
    id = 0;
    name = 0;
    password = 0;

    id = other.id;
    StringHelper::copyTextDynamic(name, other.name);
    StringHelper::copyTextDynamic(password, other.password);
}

Person::~Person() {
    delete[] name;
    delete[] password;
    name = 0;
    password = 0;
}

Person& Person::operator=(const Person& other) {
    if (this != &other) {
        id = other.id;
        StringHelper::copyTextDynamic(name, other.name);
        StringHelper::copyTextDynamic(password, other.password);
    }

    return *this;
}


int Person::getID() const {
    return id;
}

const char* Person::getName() const {
    return name;
}

const char* Person::getPassword() const {
    return password;
}

void Person::setID(int personID) {
    if (Validator::isValidID(personID)) {
        id = personID;
    }
}

void Person::setName(const char* personName) {
    StringHelper::copyTextDynamic(name, personName);
}

bool Person::setPassword(const char* personPassword) {
    if (!Validator::isValidPassword(personPassword)) {
        return false;
    }

    StringHelper::copyTextDynamic(password, personPassword);
    return true;
}
