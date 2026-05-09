#include "TimeHelper.hpp"
#include <ctime>
#include "StringHelper.hpp"

void TimeHelper::getTodayDate(char *buffer, int bufferSize)
{
    time_t now;
    struct tm *timeInfo;
    char tempBuffer[11];

    now = time(nullptr);
    timeInfo = localtime(&now);
    // Return today's date in DD-MM-YYYY to match project date format
    strftime(tempBuffer, sizeof(tempBuffer), "%d-%m-%Y", timeInfo);
    StringHelper::stringCopy(buffer, tempBuffer, bufferSize);
}

bool TimeHelper::isDateAfterToday(const char *date)
{
    char todayDate[11];
    char normalized[11];

    if (!normalizeToYMD(date, normalized, sizeof(normalized)))
    {
        return false;
    }

    getTodayDate(todayDate, 11);
    int comparison = compareDates(normalized, todayDate);
    return comparison > 0;
}

bool TimeHelper::normalizeToYMD(const char *input, char *outBuffer, int outSize)
{
    // Accept loose formats and produce canonical DD-MM-YYYY
    if (input == nullptr || outBuffer == nullptr || outSize < 11)
    {
        return false;
    }

    // Tokenize by '-' only (no slashes)
    char tokens[3][8];
    int tokenIndex = 0;
    int charIndex = 0;
    int i = 0;

    while (input[i] != '\0' && tokenIndex < 3)
    {
        char c = input[i];
        if (c == '-')
        {
            if (charIndex == 0)
                return false; // empty token
            tokens[tokenIndex][charIndex] = '\0';
            tokenIndex++;
            charIndex = 0;
        }
        else if (c >= '0' && c <= '9')
        {
            if (charIndex < 7)
            {
                tokens[tokenIndex][charIndex++] = c;
            }
            else
            {
                return false;
            }
        }
        else if (c == ' ')
        {
            // ignore spaces
        }
        else
        {
            return false;
        }
        i++;
    }
    if (tokenIndex != 2)
        return false;
    tokens[tokenIndex][charIndex] = '\0';

    // Determine which token is year (length==4) or position
    const char *dayTok = nullptr;
    const char *monthTok = nullptr;
    const char *yearTok = nullptr;

    if ((int)StringHelper::stringLength(tokens[0]) == 4)
    {
        // YYYY-MM-DD or YYYY/M/D
        yearTok = tokens[0];
        monthTok = tokens[1];
        dayTok = tokens[2];
    }
    else if ((int)StringHelper::stringLength(tokens[2]) == 4)
    {
        // D-M-YYYY or D/M/YYYY
        dayTok = tokens[0];
        monthTok = tokens[1];
        yearTok = tokens[2];
    }
    else
    {
        return false;
    }

    // Zero-pad day and month to 2 digits
    char dayBuf[3] = "00";
    char monthBuf[3] = "00";
    int dlen = StringHelper::stringLength(dayTok);
    int mlen = StringHelper::stringLength(monthTok);
    int ylen = StringHelper::stringLength(yearTok);
    if (ylen != 4)
        return false;

    if (dlen == 1)
    {
        dayBuf[0] = '0';
        dayBuf[1] = dayTok[0];
        dayBuf[2] = '\0';
    }
    else if (dlen == 2)
    {
        dayBuf[0] = dayTok[0];
        dayBuf[1] = dayTok[1];
        dayBuf[2] = '\0';
    }
    else
    {
        return false;
    }

    if (mlen == 1)
    {
        monthBuf[0] = '0';
        monthBuf[1] = monthTok[0];
        monthBuf[2] = '\0';
    }
    else if (mlen == 2)
    {
        monthBuf[0] = monthTok[0];
        monthBuf[1] = monthTok[1];
        monthBuf[2] = '\0';
    }
    else
    {
        return false;
    }

    // Compose DD-MM-YYYY
    outBuffer[0] = dayBuf[0];
    outBuffer[1] = dayBuf[1];
    outBuffer[2] = '-';
    outBuffer[3] = monthBuf[0];
    outBuffer[4] = monthBuf[1];
    outBuffer[5] = '-';
    outBuffer[6] = yearTok[0];
    outBuffer[7] = yearTok[1];
    outBuffer[8] = yearTok[2];
    outBuffer[9] = yearTok[3];
    outBuffer[10] = '\0';

    return true;
}

int TimeHelper::compareDates(const char *date1, const char *date2)
{
    int i;
    int year1;
    int year2;
    int month1;
    int month2;
    int day1;
    int day2;
    int result;

    if (date1 == nullptr || date2 == nullptr)
    {
        return 0;
    }

    year1 = 0;
    year2 = 0;
    month1 = 0;
    month2 = 0;
    day1 = 0;
    day2 = 0;

    // Parse date1 (DD-MM-YYYY)
    if (date1 == nullptr || date2 == nullptr)
    {
        return 0;
    }

    for (i = 0; i < 2 && date1[i] != '\0'; i++)
    {
        day1 = day1 * 10 + (date1[i] - '0');
    }
    for (i = 3; i < 5 && date1[i] != '\0'; i++)
    {
        month1 = month1 * 10 + (date1[i] - '0');
    }
    for (i = 6; i < 10 && date1[i] != '\0'; i++)
    {
        year1 = year1 * 10 + (date1[i] - '0');
    }

    // Parse date2 (DD-MM-YYYY)
    for (i = 0; i < 2 && date2[i] != '\0'; i++)
    {
        day2 = day2 * 10 + (date2[i] - '0');
    }
    for (i = 3; i < 5 && date2[i] != '\0'; i++)
    {
        month2 = month2 * 10 + (date2[i] - '0');
    }
    for (i = 6; i < 10 && date2[i] != '\0'; i++)
    {
        year2 = year2 * 10 + (date2[i] - '0');
    }

    // Compare years
    if (year1 != year2)
    {
        return year1 > year2 ? 1 : -1;
    }

    // Compare months
    if (month1 != month2)
    {
        return month1 > month2 ? 1 : -1;
    }

    // Compare days
    if (day1 != day2)
    {
        return day1 > day2 ? 1 : -1;
    }

    return 0;
}

int TimeHelper::compareTimeSlotsAscending(const char *left, const char *right)
{
    int index;

    index = 0;
    while (left != nullptr && right != nullptr)
    {
        if (left[index] == '\0' && right[index] == '\0')
        {
            return 0;
        }
        if (left[index] == '\0')
        {
            return -1;
        }
        if (right[index] == '\0')
        {
            return 1;
        }
        if (left[index] < right[index])
        {
            return -1;
        }
        if (left[index] > right[index])
        {
            return 1;
        }
        index++;
    }

    if (left == nullptr && right == nullptr)
    {
        return 0;
    }
    if (left == nullptr)
    {
        return -1;
    }

    return 1;
}

bool TimeHelper::parseDateToTime(const char *dateText, time_t &value)
{
    struct tm dateInfo;
    int day;
    int month;
    int year;

    if (dateText == nullptr || StringHelper::stringLength(dateText) < 10)
    {
        return false;
    }

    day = (dateText[0] - '0') * 10 + (dateText[1] - '0');
    month = (dateText[3] - '0') * 10 + (dateText[4] - '0');
    year = (dateText[6] - '0') * 1000 + (dateText[7] - '0') * 100 + (dateText[8] - '0') * 10 + (dateText[9] - '0');

    dateInfo.tm_sec = 0;
    dateInfo.tm_min = 0;
    dateInfo.tm_hour = 12;
    dateInfo.tm_mday = day;
    dateInfo.tm_mon = month - 1;
    dateInfo.tm_year = year - 1900;
    dateInfo.tm_isdst = -1;
    dateInfo.tm_wday = 0;
    dateInfo.tm_yday = 0;

    value = mktime(&dateInfo);
    return value != (time_t)-1;
}

bool TimeHelper::isBillOverdueByMoreThan7Days(const char *billDate)
{
    time_t billTime;
    time_t todayTime;
    time_t now;

    if (!parseDateToTime(billDate, billTime))
    {
        return false;
    }

    now = time(nullptr);
    todayTime = now;
    return difftime(todayTime, billTime) > (7.0 * 24.0 * 60.0 * 60.0);
}
