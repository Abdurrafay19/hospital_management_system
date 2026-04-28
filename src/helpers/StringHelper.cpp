#include "StringHelper.hpp"

bool StringHelper::textEquals(const char* left, const char* right) {
    int i;

    if (left == nullptr || right == nullptr) {
        return left == right;
    }

    i = 0;
    while (left[i] != '\0' && right[i] != '\0') {
        if (left[i] != right[i]) {
            return false;
        }
        i++;
    }

    return left[i] == '\0' && right[i] == '\0';
}

bool StringHelper::textEqualsIgnoreCase(const char* left, const char* right) {
    int i;

    if (left == nullptr || right == nullptr) {
        return left == right;
    }

    i = 0;
    while (left[i] != '\0' && right[i] != '\0') {
        if (toLowerASCII(left[i]) != toLowerASCII(right[i])) {
            return false;
        }
        i++;
    }

    return left[i] == '\0' && right[i] == '\0';
}

int StringHelper::stringLength(const char* str) {
    int length;

    if (str == nullptr) {
        return 0;
    }

    length = 0;
    while (str[length] != '\0') {
        length++;
    }

    return length;
}

void StringHelper::stringCopy(char* destination, const char* source, int maxLength) {
    int i;

    if (destination == nullptr || source == nullptr) {
        return;
    }

    i = 0;
    while (i < maxLength && source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

void StringHelper::copyTextDynamic(char*& destination, const char* source) {
    int i;
    int length;

    delete[] destination;
    destination = nullptr;

    if (source == nullptr) {
        return;
    }

    length = 0;
    while (source[length] != '\0') {
        length++;
    }

    destination = new char[length + 1];

    i = 0;
    while (i < length) {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

char StringHelper::toLowerASCII(char c) {
    if (c >= 'A' && c <= 'Z') {
        return static_cast<char>(c + ('a' - 'A'));
    }

    return c;
}
