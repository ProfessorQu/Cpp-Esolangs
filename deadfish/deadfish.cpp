#include <iostream>
#include <fstream>
#include <string>
#include "../files.h"

int main(int argc, char const *argv[])
{
    // Set accumulator to 0
    int accumulator = 0;

    // Open file
    std::fstream file = openFile(argv[1]);

    // If file is not open, print error message and exit
    if (!file.is_open())
    {
        std::cout << "File not found" << std::endl;
        return 0;
    }

    // Read file line by line
    std::string line;
    while (std::getline(file, line))
    {
        // Loop through each character in line
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

            // If accumulator is less than 0 or greater than 256, set to 0
            if (accumulator < 0 || accumulator == 256)
            {
                accumulator = 0;
            }
        }
    }

    return 0;
}
