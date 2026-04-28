#include "CharHelper.hpp"

bool CharHelper::isDigitChar(char c) {
    return c >= '0' && c <= '9';
}

bool CharHelper::isAlphaChar(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
