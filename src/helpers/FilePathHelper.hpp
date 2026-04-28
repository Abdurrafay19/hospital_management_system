#pragma once

#include <fstream>

class FilePathHelper {
public:
    static void joinPath(const char* prefix, const char* fileName, char* output, int maxLength);
    static bool openInputDataFile(std::ifstream& file, const char* fileName);
    static bool openOutputDataFile(std::ofstream& file, const char* fileName, std::ios::openmode mode);
};
