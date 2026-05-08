#include "StringHelper.hpp"
#include "ConversionHelper.hpp"

bool StringHelper::isNullOrEmpty(const char *str)
{
    return str == nullptr || str[0] == '\0';
}

bool StringHelper::textEquals(const char *left, const char *right)
{
    int i;

    if (left == nullptr || right == nullptr)
    {
        return left == right;
    }

    i = 0;
    while (left[i] != '\0' && right[i] != '\0')
    {
        if (left[i] != right[i])
        {
            return false;
        }
        i++;
    }

    return left[i] == '\0' && right[i] == '\0';
}

bool StringHelper::textEqualsIgnoreCase(const char *left, const char *right)
{
    int i;

    if (left == nullptr || right == nullptr)
    {
        return left == right;
    }

    i = 0;
    while (left[i] != '\0' && right[i] != '\0')
    {
        if (toLowerASCII(left[i]) != toLowerASCII(right[i]))
        {
            return false;
        }
        i++;
    }

    return left[i] == '\0' && right[i] == '\0';
}

int StringHelper::stringLength(const char *str)
{
    int length;

    if (str == nullptr)
    {
        return 0;
    }

    length = 0;
    while (str[length] != '\0')
    {
        length++;
    }

    return length;
}

void StringHelper::stringCopy(char *destination, const char *source, int maxLength)
{
    int i;

    if (destination == nullptr || source == nullptr)
    {
        return;
    }

    i = 0;
    while (i < maxLength && source[i] != '\0')
    {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

void StringHelper::copyTextDynamic(char *&destination, const char *source)
{
    int i;
    int length;

    delete[] destination;
    destination = nullptr;

    if (source == nullptr)
    {
        return;
    }

    length = 0;
    while (source[length] != '\0')
    {
        length++;
    }

    destination = new char[length + 1];

    i = 0;
    while (i < length)
    {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

char StringHelper::toLowerASCII(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return static_cast<char>(c + ('a' - 'A'));
    }

    return c;
}

void StringHelper::copyPreviewText(char *destination, int destinationSize, const char *source, int previewLimit)
{
    int index;

    if (destination == nullptr || destinationSize <= 0)
    {
        return;
    }

    destination[0] = '\0';
    if (source == nullptr)
    {
        return;
    }

    index = 0;
    while (source[index] != '\0' && index < previewLimit && index < destinationSize - 1)
    {
        destination[index] = source[index];
        index++;
    }

    if (source[index] != '\0' && index < destinationSize - 4)
    {
        destination[index] = '.';
        destination[index + 1] = '.';
        destination[index + 2] = '.';
        index += 3;
    }

    destination[index] = '\0';
}

void StringHelper::appendTextField(char *destination, int destinationSize, const char *text)
{
    int len;

    if (destination == nullptr || destinationSize <= 0 || text == nullptr)
    {
        return;
    }

    len = StringHelper::stringLength(destination);
    StringHelper::stringCopy(destination + len, text, destinationSize - len);
}

void StringHelper::appendIntField(char *destination, int destinationSize, int value)
{
    char buffer[32];

    ConversionHelper::intToString(value, buffer);
    appendTextField(destination, destinationSize, buffer);
}

void StringHelper::appendDoubleField(char *destination, int destinationSize, double value)
{
    char buffer[32];

    ConversionHelper::doubleToString(value, buffer);
    appendTextField(destination, destinationSize, buffer);
}
