#include <iostream>
#include <fstream>
#include <string>
#include "../files.h"

int main(int argc, char const *argv[])
{
    int accumulator = 0;

    std::fstream file = openFile(argv[1]);

    if (!file.is_open())
    {
        std::cout << "File not found" << std::endl;
        return 0;
    }

    std::string line;
    while (std::getline(file, line))
    {
        for (int i = 0; i < line.length(); i++)
        {
            // Increment
            if (line[i] == 'i')
            {
                accumulator++;
            }
            // Decrement
            else if (line[i] == 'd')
            {
                accumulator--;
            }
            // Square
            else if (line[i] == 's')
            {
                accumulator *= accumulator;
            }
            // Print
            else if (line[i] == 'o')
            {
                std::cout << accumulator << std::endl;
            }

            if (accumulator < 0 || accumulator == 256)
            {
                accumulator = 0;
            }
        }
    }

    return 0;
}
