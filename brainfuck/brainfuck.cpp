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

    // Read file character by character
    char c;
    while (file.get(c))
    {
        // std::cout << "Character: " << c << std::endl;
        // // Print tape
        // std::cout << "Tape: " << tape[pointer] << std::endl;
        switch (c)
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
                int loopCount = 1;
                while (loopCount > 0)
                {
                    // Read next character
                    file.get(c);
                    // If loop start, increment loop count
                    if (c == '[')
                        loopCount++;
                    // If loop end, decrement loop count
                    else if (c == ']')
                        loopCount--;
                }
            }
            break;
        // Loop end
        case ']':
            if (tape[pointer] != 0)
            {
                // Count number of loops
                int loopCount = 1;
                while (loopCount > 0)
                {
                    // Read previous character
                    file.unget();
                    file.unget();
                    file.get(c);
                    // If loop start, decrement loop count
                    if (c == '[')
                        loopCount--;
                    // If loop end, increment loop count
                    else if (c == ']')
                        loopCount++;
                }
            }
            break;
        }
    }

    return 0;
}
