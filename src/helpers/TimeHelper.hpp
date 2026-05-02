#pragma once

class TimeHelper
{
public:
    static void getTodayDate(char *buffer, int bufferSize);
    static bool isDateAfterToday(const char *date);
    static int compareDates(const char *date1, const char *date2);
    static bool normalizeToYMD(const char *input, char *outBuffer, int outSize);
};
