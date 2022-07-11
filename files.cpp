#include "files.h"
#include <fstream>
#include <string>

std::fstream openFile(std::string filename)
{
    std::fstream file;
    file.open(filename);

    return file;
}


int accumulator = 0;
