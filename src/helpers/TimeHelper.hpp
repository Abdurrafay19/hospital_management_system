#pragma once
#include <ctime>

class TimeHelper
{
public:
    static void getTodayDate(char *buffer, int bufferSize);
    static bool isDateAfterToday(const char *date);
    static int compareDates(const char *date1, const char *date2);
    static int compareTimeSlotsAscending(const char *left, const char *right);
    static bool normalizeToYMD(const char *input, char *outBuffer, int outSize);
    static bool parseDateToTime(const char *dateText, time_t &value);
    static bool isBillOverdueByMoreThan7Days(const char *billDate);
};
