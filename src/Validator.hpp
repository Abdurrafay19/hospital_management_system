#pragma once

class Validator {
public:
    static bool isValidID(int id);
    static bool isValidDate(const char* date);
    static bool isValidContact(const char* contact);
    static bool isValidPassword(const char* password);
};
