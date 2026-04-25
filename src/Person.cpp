#include "Person.hpp"

#include "Validator.hpp"

Person::Person() {
    id = 0;
    name[0] = '\0';
    password[0] = '\0';
}

Person::Person(int personID, const char* personName, const char* personPassword) {
    id = 0;
    name[0] = '\0';
    password[0] = '\0';

    setID(personID);
    setName(personName);
    setPassword(personPassword);
}

Person::~Person() {
}

void Person::copyText(char* destination, const char* source, int maxLength) {
    int i;

    if (destination == 0 || maxLength <= 0) {
        return;
    }

    if (source == 0) {
        destination[0] = '\0';
        return;
    }

    i = 0;
    while (source[i] != '\0' && i < maxLength - 1) {
        destination[i] = source[i];
        i++;
    }

    destination[i] = '\0';
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
    copyText(name, personName, 50);
}

bool Person::setPassword(const char* personPassword) {
    if (!Validator::isValidPassword(personPassword)) {
        return false;
    }

    copyText(password, personPassword, 50);
    return true;
}
