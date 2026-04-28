#pragma once

class StringHelper {
public:
    static bool textEquals(const char* left, const char* right);
    static bool textEqualsIgnoreCase(const char* left, const char* right);
    static int stringLength(const char* str);
    static void stringCopy(char* destination, const char* source, int maxLength);
    static void copyTextDynamic(char*& destination, const char* source);
    static char toLowerASCII(char c);
};
