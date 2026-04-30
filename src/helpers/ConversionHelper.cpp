#include "ConversionHelper.hpp"
#include <fstream>

int ConversionHelper::toInt(const char* text) {
    int value;
    int index;

    if (text == nullptr) {
        return 0;
    }

    value = 0;
    index = 0;
    while (text[index] >= '0' && text[index] <= '9') {
        value = (value * 10) + (text[index] - '0');
        index++;
    }

    return value;
}

int ConversionHelper::stringToInt(const char* str) {
    int result;
    int i;
    int isNegative;

    if (str == nullptr) {
        return 0;
    }

    result = 0;
    isNegative = 0;
    i = 0;

    if (str[0] == '-') {
        isNegative = 1;
        i = 1;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return isNegative ? -result : result;
}

double ConversionHelper::stringToDouble(const char* str) {
    double result;
    double decimalPlace;
    int i;
    int isNegative;
    int foundDot;

    if (str == nullptr) {
        return 0.0;
    }

    result = 0.0;
    isNegative = 0;
    foundDot = 0;
    decimalPlace = 1.0;
    i = 0;

    if (str[0] == '-') {
        isNegative = 1;
        i = 1;
    }

    while (str[i] != '\0') {
        if (str[i] == '.' && !foundDot) {
            foundDot = 1;
            decimalPlace = 0.1;
        } else if (str[i] >= '0' && str[i] <= '9') {
            if (foundDot) {
                result = result + (double)(str[i] - '0') * decimalPlace;
                decimalPlace = decimalPlace * 0.1;
            } else {
                result = result * 10.0 + (double)(str[i] - '0');
            }
        }
        i++;
    }

    return isNegative ? -result : result;
}

void ConversionHelper::intToString(int value, char* buffer) {
    int i;
    int length;
    int temp;

    if (buffer == nullptr) {
        return;
    }

    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    if (value < 0) {
        buffer[0] = '-';
        value = -value;
        i = 1;
    } else {
        i = 0;
    }

    length = 0;
    temp = value;
    while (temp > 0) {
        length++;
        temp = temp / 10;
    }

    temp = value;
    int originalLength = length;
    while (temp > 0) {
        buffer[i + length - 1] = static_cast<char>('0' + (temp % 10));
        temp = temp / 10;
        length--;
    }

    buffer[i + originalLength] = '\0';
}

void ConversionHelper::doubleToString(double value, char* buffer) {
    int intPart;
    double decPart;
    int i;
    int digits;

    if (buffer == nullptr) {
        return;
    }

    if (value < 0.0) {
        buffer[0] = '-';
        value = -value;
        i = 1;
    } else {
        i = 0;
    }

    intPart = static_cast<int>(value);
    decPart = value - intPart;

    // Write integer part manually to avoid intToString inconsistencies
    int idx = i;
    if (intPart == 0) {
        buffer[idx++] = '0';
    } else {
        int tempInt = intPart;
        char rev[32];
        int revLen = 0;
        while (tempInt > 0 && revLen < 32) {
            rev[revLen++] = static_cast<char>('0' + (tempInt % 10));
            tempInt = tempInt / 10;
        }
        // reverse
        int k;
        for (k = revLen - 1; k >= 0; k--) {
            buffer[idx++] = rev[k];
        }
    }

    buffer[idx++] = '.';

    digits = 0;
    while (digits < 2) {
        decPart = decPart * 10.0;
        int digit = static_cast<int>(decPart + 1e-9);
        if (digit < 0) digit = 0;
        if (digit > 9) digit = 9;
        buffer[idx++] = static_cast<char>('0' + digit);
        decPart = decPart - digit;
        digits++;
    }

    buffer[idx] = '\0';

}

int ConversionHelper::toIntFromDigits(const char* text, int startIndex, int digitCount) {
    int value = 0;
    int i = 0;

    while (i < digitCount) {
        value = (value * 10) + (text[startIndex + i] - '0');
        i++;
    }

    return value;
}
