#include "Validator.hpp"
#include "../helpers/CharHelper.hpp"
#include "../helpers/ConversionHelper.hpp"
#include "../helpers/DataHelper.hpp"
#include "../helpers/StringHelper.hpp"

bool Validator::isValidID(int id)
{
    return id > 0;
}

bool Validator::isValidDate(const char *date)
{
    if (date == nullptr)
    {
        return false;
    }

    int i = 0;
    while (date[i] != '\0')
    {
        i++;
    }

    if (i != 10)
    {
        return false;
    }

    if (date[2] != '-' || date[5] != '-')
    {
        return false;
    }

    i = 0;
    while (i < 10)
    {
        if (i != 2 && i != 5 && !CharHelper::isDigitChar(date[i]))
        {
            return false;
        }
        i++;
    }

    int day = ConversionHelper::toIntFromDigits(date, 0, 2);
    int month = ConversionHelper::toIntFromDigits(date, 3, 2);
    int year = ConversionHelper::toIntFromDigits(date, 6, 4);

    if (year <= 0)
    {
        return false;
    }

    if (month < 1 || month > 12)
    {
        return false;
    }

    int maxDay;
    if (month == 1 || month == 3 || month == 5 || month == 7 ||
        month == 8 || month == 10 || month == 12)
    {
        maxDay = 31;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        maxDay = 30;
    }
    else
    {
        if (DataHelper::isLeapYear(year))
        {
            maxDay = 29;
        }
        else
        {
            maxDay = 28;
        }
    }

    if (day < 1 || day > maxDay)
    {
        return false;
    }

    return true;
}

bool Validator::isValidContact(const char *contact)
{
    if (contact == nullptr)
    {
        return false;
    }

    int i = 0;
    while (contact[i] != '\0')
    {
        if (!CharHelper::isDigitChar(contact[i]))
        {
            return false;
        }
        i++;
    }

    return i == 11;
}

bool Validator::isValidPassword(const char *password)
{
    if (password == nullptr)
    {
        return false;
    }

    int length = 0;
    while (password[length] != '\0')
    {
        length++;
    }

    return length >= 6;
}

bool Validator::isValidPositiveIntegerText(const char *text)
{
    if (StringHelper::isNullOrEmpty(text))
    {
        return false;
    }

    int i = 0;
    while (text[i] != '\0')
    {
        if (!CharHelper::isDigitChar(text[i]))
        {
            return false;
        }
        i++;
    }

    return text[0] != '0';
}

bool Validator::isValidPositiveNumberText(const char *text)
{
    if (StringHelper::isNullOrEmpty(text))
    {
        return false;
    }

    int i = 0;
    int dotCount = 0;
    int digitCount = 0;
    while (text[i] != '\0')
    {
        if (text[i] == '.')
        {
            dotCount++;
            if (dotCount > 1)
            {
                return false;
            }
        }
        else if (CharHelper::isDigitChar(text[i]))
        {
            digitCount++;
        }
        else
        {
            return false;
        }
        i++;
    }

    return digitCount > 0 && !(text[0] == '0' && text[1] == '\0');
}
