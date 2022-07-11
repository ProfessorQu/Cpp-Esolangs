#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../files.h"

#define TAPE_SIZE 30000

int main(int argc, char const *argv[])
{
    // Initialize tape and pointer
    int tape[TAPE_SIZE];
    int pointer = 0;

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
        for (int i = 0; i < line.size(); i++)
        {
            switch (line[i])
            {
            // Move pointer right
            case '>':
                pointer++;
                break;
            // Move pointer left
            case '<':
                pointer--;
                break;
            // Increment
            case '+':
                tape[pointer]++;
                break;
            // Decrement
            case '-':
                tape[pointer]--;
                break;
            // Output in ascii
            case '.':
                std::cout << (char)tape[pointer];
                break;
            // Input from stdin
            case ',':
                std::cin >> tape[pointer];
                break;
            // Loop start
            case '[':
                if (tape[pointer] == 0)
                {
                    // Count number of loops
                    int count = 1;
                    while (count > 0)
                    {
                        // Read next character
                        i++;
                        // If loop start, increment count
                        if (line[i] == '[')
                            count++;
                        // If loop end, decrement count
                        else if (line[i] == ']')
                            count--;
                    }
                }
                break;
            // Loop end
            case ']':
                if (tape[pointer] != 0)
                {
                    // Count number of loops
                    int count = 1;
                    while (count > 0)
                    {
                        // Read previous character
                        i--;
                        // If loop start, decrement count
                        if (line[i] == '[')
                            count--;
                        // If loop end, increment count
                        else if (line[i] == ']')
                            count++;
                    }
                }
                break;
            }

            // If 
        }
    }

    return 0;
}
