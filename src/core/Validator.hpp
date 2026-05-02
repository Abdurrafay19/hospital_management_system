#pragma once

class Validator
{
public:
    static bool isValidID(int id);
    static bool isValidDate(const char *date);
    static bool isValidContact(const char *contact);
    static bool isValidPassword(const char *password);
    static bool isValidPositiveIntegerText(const char *text);
    static bool isValidPositiveNumberText(const char *text);
};
