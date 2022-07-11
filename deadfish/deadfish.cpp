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
            switch(line[i])
            {
                // Increment accumulator
                case '+':
                    accumulator++;
                    break;
                // Decrement accumulator
                case '-':
                    accumulator--;
                    break;
                // Move accumulator right
                case '>':
                    accumulator++;
                    break;
                // Move accumulator left
                case '<':
                    accumulator--;
                    break;
                // Output accumulator
                case '.':
                    std::cout << (char)accumulator;
                    break;
                // Input from stdin
                case ',':
                    std::cin >> accumulator;
                    break;
                // Loop start
                case '[':
                    if (accumulator == 0)
                    {
                        int loopCount = 0;
                        while (line[i] != ']')
                        {
                            i++;
                            loopCount++;
                        }
                        i -= loopCount;
                    }
                    break;
                // Loop end
                case ']':
                    break;
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
