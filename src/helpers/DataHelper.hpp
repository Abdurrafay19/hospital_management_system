#pragma once

class DataHelper {
public:
    static void splitByComma(const char* line, char** fields, int maxFields, int& fieldCount);
    static bool isLeapYear(int year);
};
