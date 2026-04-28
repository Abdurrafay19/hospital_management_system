#pragma once

class ConversionHelper {
public:
    static int toInt(const char* text);
    static int stringToInt(const char* str);
    static double stringToDouble(const char* str);
    static void intToString(int value, char* buffer);
    static void doubleToString(double value, char* buffer);
    static int toIntFromDigits(const char* text, int startIndex, int digitCount);
};
