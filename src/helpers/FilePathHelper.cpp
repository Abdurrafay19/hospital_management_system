#include "FilePathHelper.hpp"

void FilePathHelper::joinPath(const char *prefix, const char *fileName, char *output, int maxLength)
{
    int index;
    int p;

    index = 0;
    p = 0;
    while (prefix[p] != '\0' && index < maxLength)
    {
        output[index] = prefix[p];
        index++;
        p++;
    }

    p = 0;
    while (fileName[p] != '\0' && index < maxLength)
    {
        output[index] = fileName[p];
        index++;
        p++;
    }

    output[index] = '\0';
}

bool FilePathHelper::openInputDataFile(std::ifstream &file, const char *fileName)
{
    char path[300];

    joinPath("data/", fileName, path, 299);
    file.open(path);
    if (file.is_open())
    {
        return true;
    }

    file.clear();
    joinPath("../../../data/", fileName, path, 299);
    file.open(path);
    return file.is_open();
}

bool FilePathHelper::openOutputDataFile(std::ofstream &file, const char *fileName, std::ios::openmode mode)
{
    char path[300];

    joinPath("data/", fileName, path, 299);
    file.open(path, mode);
    if (file.is_open())
    {
        return true;
    }

    file.clear();
    joinPath("../../../data/", fileName, path, 299);
    file.open(path, mode);
    return file.is_open();
}
