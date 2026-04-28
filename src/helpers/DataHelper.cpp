#include "DataHelper.hpp"

void DataHelper::splitByComma(const char* line, char** fields, int maxFields, int& fieldCount) {
    int currentField;
    int charIndex;
    int fieldCharIndex;
    char currentBuffer[300];

    if (line == nullptr) {
        fieldCount = 0;
        return;
    }

    currentField = 0;
    charIndex = 0;
    fieldCharIndex = 0;

    while (line[charIndex] != '\0' && currentField < maxFields) {
        if (line[charIndex] == ',') {
            currentBuffer[fieldCharIndex] = '\0';
            fields[currentField] = new char[fieldCharIndex + 1];
            int i = 0;
            while (currentBuffer[i] != '\0') {
                fields[currentField][i] = currentBuffer[i];
                i++;
            }
            fields[currentField][i] = '\0';

            currentField++;
            fieldCharIndex = 0;
        } else {
            currentBuffer[fieldCharIndex] = line[charIndex];
            fieldCharIndex++;
        }
        charIndex++;
    }

    if (currentField < maxFields && fieldCharIndex > 0) {
        currentBuffer[fieldCharIndex] = '\0';
        fields[currentField] = new char[fieldCharIndex + 1];
        int i = 0;
        while (currentBuffer[i] != '\0') {
            fields[currentField][i] = currentBuffer[i];
            i++;
        }
        fields[currentField][i] = '\0';
        currentField++;
    }

    fieldCount = currentField;
}

bool DataHelper::isLeapYear(int year) {
    if (year % 400 == 0) {
        return true;
    }

    if (year % 100 == 0) {
        return false;
    }

    if (year % 4 == 0) {
        return true;
    }

    return false;
}
