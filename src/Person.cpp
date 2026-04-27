#include "Person.hpp"

#include "Validator.hpp"

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
    copyText(name, other.name);
    copyText(password, other.password);
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
        copyText(name, other.name);
        copyText(password, other.password);
    }

    return *this;
}

void Person::copyText(char*& destination, const char* source) {
    int i;
    int length;

    // Delete existing memory
    delete[] destination;
    destination = 0;

    if (source == 0) {
        return;
    }

    // Calculate length
    length = 0;
    while (source[length] != '\0') {
        length++;
    }

    // Allocate memory
    destination = new char[length + 1];

    // Copy string
    i = 0;
    while (i < length) {
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
    copyText(name, personName);
}

bool Person::setPassword(const char* personPassword) {
    if (!Validator::isValidPassword(personPassword)) {
        return false;
    }

    copyText(password, personPassword);
    return true;
}
