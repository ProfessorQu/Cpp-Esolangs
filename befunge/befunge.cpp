#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <math.h>
#include "../files.h"

#define ROWS 25
#define COLS 80

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    // Open file
    std::fstream file = openFile(argv[1]);

    // If file is not open, print error message and exit
    if (!file.is_open())
    {
        std::cout << "File not found" << std::endl;
        return 0;
    }

    // Set the position of the cursor to the top left corner
    int cursor_x = 0;
    int cursor_y = 0;

    // Set the direction of the cursor
    int direction_x = 1;
    int direction_y = 0;

    // Create the stack
    std::stack<int> stack = std::stack<int>();

    // Create the grid
    char grid[ROWS][COLS];

    // Fill the grid with spaces
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            grid[i][j] = ' ';
        }
    }

    // Fill the grid by reading the file
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            file.get(grid[i][j]);

            // Go to the next line if the character is a newline
            if (grid[i][j] == '\n')
            {
                grid[i][j] = ' ';
                break;
            }
        }
    }

    // Display grid if the user wants to
    if (argc == 3 && std::string(argv[2]) == "-d")
    {
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                std::cout << grid[i][j];
            }
            std::cout << std::endl;
        }
    }

    bool string_mode = false;
    bool running = true;

    int a;
    int b;
    int random_dir;

    // Execute the program
    while(running)
    {
        // If we are in string mode,
        // push characters to the stack
        if (string_mode)
        {
            if (grid[cursor_y][cursor_x] == '"')
            {
                string_mode = false;
            }
            else
            {
                stack.push(grid[cursor_y][cursor_x]);
            }

        }
        else
        {
            switch (grid[cursor_y][cursor_x])
            {
// ######################################## Move the cursor ########################################
                // Move cursor right
                case '>':
                    direction_x = 1;
                    direction_y = 0;
                    break;
                // Move cursor left
                case '<':
                    direction_x = -1;
                    direction_y = 0;
                    break;
                // Move cursor up
                case '^':
                    direction_x = 0;
                    direction_y = -1;
                    break;
                // Move cursor down
                case 'v':
                    direction_x = 0;
                    direction_y = 1;
                    break;
                case '?':
                    random_dir = rand() % 4;
                    if (random_dir == 0)
                    {
                        direction_x = 1;
                        direction_y = 0;
                    }
                    else if (random_dir == 1)
                    {
                        direction_x = -1;
                        direction_y = 0;
                    }
                    else if (random_dir == 2)
                    {
                        direction_y = -1;
                        direction_x = 0;
                    }
                    else if (random_dir == 3)
                    {
                        direction_y = 1;
                        direction_x = 0;
                    }
                    break;

// ######################################## Calculations ########################################
                // Addition
                case '+':
                    // Get int a
                    a = stack.top();
                    stack.pop();
                    // Get int b
                    b = stack.top();
                    stack.pop();

                    // Push a + b
                    stack.push(a + b);
                    break;
                // Subtraction
                case '-':
                    // Get int a
                    a = stack.top();
                    stack.pop();
                    // Get int b
                    b = stack.top();
                    stack.pop();

                    // Push b - a
                    stack.push(b - a);
                    break;
                // Multiplication
                case '*':
                    // Get int a
                    a = stack.top();
                    stack.pop();
                    // Get int b
                    b = stack.top();
                    stack.pop();

                    // Push a * b
                    stack.push(a * b);
                    break;
                // Division
                case '/':
                    // Get int a
                    a = stack.top();
                    stack.pop();
                    // Get int b
                    b = stack.top();
                    stack.pop();

                    // Push b / a
                    stack.push(floor(b / a));
                    break;
                // Modulus
                case '%':
                    // Get int a
                    a = stack.top();
                    stack.pop();
                    // Get int b
                    b = stack.top();
                    stack.pop();

                    // Push b % a
                    stack.push(b % a);
                    break;
                
// ######################################## Comparison ########################################
                // Logical not
                case '!':
                    // Get int a
                    a = stack.top();
                    stack.pop();

                    if (a == 0)
                    {
                        stack.push(1);
                    }
                    else
                    {
                        stack.push(0);
                    }
                    break;
                // Greater than
                case '`':
                    // Get int a
                    a = stack.top();
                    stack.pop();
                    // Get int b
                    b = stack.top();
                    stack.pop();

                    if (b > a)
                    {
                        stack.push(1);
                    }
                    else
                    {
                        stack.push(0);
                    }
                    break;
                
// ######################################## If ########################################
                // Horizontal if
                case '_':
                    // Get int a
                    a = stack.top();
                    stack.pop();
                    
                    // Go right if a is 0
                    if (a == 0)
                    {
                        direction_x = 1;
                        direction_y = 0;
                    }
                    // Go left if a is not 0
                    else
                    {
                        direction_x = -1;
                        direction_y = 0;
                    }
                    break;
                // Vertical if
                case '|':
                    // Get int a
                    a = stack.top();
                    stack.pop();
                    
                    // Go down if a is 0
                    if (a == 0)
                    {
                        direction_x = 0;
                        direction_y = 1;
                    }
                    // Go up if a is not 0
                    else
                    {
                        direction_x = 0;
                        direction_y = -1;
                    }
                    break;
                
// ######################################## String ########################################
                // Enter string mode
                case '"':
                    string_mode = true;
                    break;

// ######################################## Stack ########################################
                // Duplicate the top element
                case ':':
                    stack.push(stack.top());
                    break;
                // Swap the top two elements
                case '\\':
                    // Get int a
                    a = stack.top();
                    stack.pop();
                    // Get int b
                    b = stack.top();
                    stack.pop();

                    // Push a
                    stack.push(a);
                    // Push b
                    stack.push(b);
                    break;
                // Pop the top element
                case '$':
                    stack.pop();
                    break;
// ######################################## Output ########################################
                // Output top element as integer
                case '.':
                    std::cout << stack.top();
                    stack.pop();
                    break;
                // Output top element as character
                case ',':
                    std::cout << (char)stack.top();
                    stack.pop();
                    break;
                
// ######################################## Input ########################################
                // Input integer
                case '&':
                    std::cin >> a;
                    stack.push(a);
                    break;
                // Input character
                case '~':
                    std::cin >> a;
                    stack.push((int)a);
                    break;

                // Stop the program
                case '@':
                    std::cout << "Program stopped" << std::endl;
                    running = false;
                    break;
            }
        }

        // Move the cursor
        cursor_x += direction_x;
        cursor_y += direction_y;
    }

    if (running == true)
    {
        std::cout << "Error: Program did not stop" << std::endl;
    }

    return 0;
}