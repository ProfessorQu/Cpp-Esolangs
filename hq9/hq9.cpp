#include <iostream>
#include <fstream>
#include <string>
#include "../files.h"

int main(int argc, char const *argv[])
{
    // Open file
    std::fstream file = openFile(argv[1]);

    // If file is not open, print error message and exit
    if (!file.is_open())
    {
        std::cout << "File not found" << std::endl;
        return 0;
    }

    // Create quine
    std::string quine;
    char c;
    while (file.get(c))
    {
        quine += c;
    }

    file = openFile(argv[1]);

    // Create accumulator
    unsigned int accumulator = 0;

    // Read file character by character
    while (file.get(c))
    {
        switch (c)
        {
        // Print "Hello, World!"
        case 'h': case 'H':
            std::cout << "Hello, World!" << std::endl;
            break;
        // Print the program's own source code
        case 'q': case 'Q':
            std::cout << quine << std::endl;
            break;
        // Print the lyrics of the song "99 bottles of beer"
        case '9':
            for (int i = 99; i > 1; i--)
            {
                std::cout << i << " bottles of beer on the wall, " << std::endl;
                std::cout << i << " bottles of beer." << std::endl;
                std::cout << "Take one down and pass it around, " << i - 1 << std::endl;
                std::cout << " bottles of beer on the wall." << std::endl;
            }

            std::cout << "1 bottle of beer on the wall, " << std::endl;
            std::cout << "1 bottle of beer." << std::endl;
            std::cout << "Take one down and pass it around, " << std::endl;
            std::cout << "no more bottles of beer on the wall." << std::endl;
            break;
        // Increment accumulator
        case '+':
            accumulator++;
            break;
        }
    }

    return 0;
}
