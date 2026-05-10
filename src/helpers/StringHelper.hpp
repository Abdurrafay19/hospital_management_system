#pragma once

class StringHelper
{
public:
    static bool isNullOrEmpty(const char *str);
    static bool textEquals(const char *left, const char *right);
    static bool textEqualsIgnoreCase(const char *left, const char *right);
    static bool textContainsIgnoreCase(const char *text, const char *search);
    static int compareText(const char *left, const char *right);
    static int stringLength(const char *str);
    static void stringCopy(char *destination, const char *source, int maxLength);
    static void copyTextDynamic(char *&destination, const char *source);
    static char toLowerASCII(char c);
    static void copyPreviewText(char *destination, int destinationSize, const char *source, int previewLimit);
    static void appendTextField(char *destination, int destinationSize, const char *text);
};
