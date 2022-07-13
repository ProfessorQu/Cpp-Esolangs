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

    // Variables for program arguments
    bool display_cursor = false;
    bool display_grid = false;
    bool display_stopped = false;

    // Arguments for the program
    if (argc > 1)
    {
        std::string arg;
        for (int i = 0; i < argc; i++)
        {
            // Get the argument
            arg = std::string(argv[i]);
            
            // Debug grid
            if (arg == "-grid")
            {
                display_grid = true;
            }

            // Debug cursor
            if (arg == "-cursor")
            {
                display_cursor = true;
            }

            // Debug stopped
            if (arg == "-stopped")
            {
                display_stopped = true;
            }

            if (arg == "-help")
            {
                std::cout << "Usage: befunge.exe [file]" << std::endl;
                std::cout << "Options:" << std::endl;
                std::cout << "-grid: Prints the grid" << std::endl;
                std::cout << "-cursor: Displays the cursor" << std::endl;
                std::cout << "-stopped: Displays the stopped state" << std::endl;
                std::cout << "-help: Prints this message" << std::endl;
                return 0;
            }
        }
    }

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
    std::stack<int> stack;
    std::stack<int> stack_wtf;  // NOTE: This isn't used, but if I remove it, it breaks the program

    // Create the grid
    char grid[ROWS][COLS];

    // Fill the grid with spaces
    for (int i = 0; i <= ROWS; i++)
    {
        for (int j = 0; j <= COLS; j++)
        {
            grid[i][j] = ' ';
        }
    }

    // Fill the grid by reading the file
    for (int i = 0; i <= ROWS; i++)
    {
        for (int j = 0; j <= COLS; j++)
        {
            file.get(grid[i][j]);

            // Go to the next line if the character is a newline
            if (grid[i][j] == '\n')
            {
                grid[i][j] = ' ';
                break;
            }

            if (display_grid)
            {
                std::cout << grid[i][j];
            }
        }
        if (display_grid)
        {
            std::cout << std::endl;
        }
    }

    bool string_mode = false;
    bool skip_next = false;
    bool running = true;

    int a;
    int b;
    int random_dir;

    // Execute the program
    while(running)
    {
        // Display the cursor
        if (display_cursor)
        {
            std::cout << "Cursor: " << cursor_x << " " << cursor_y << std::endl;
            std::cout << "Instruction: " << grid[cursor_y][cursor_x] << std::endl;
        }

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
        // If we have to skip the next instruction,
        // skip it
        else if (skip_next && (grid[cursor_y][cursor_x] != ' ' || grid[cursor_y][cursor_x] == '\n'))
        {
            skip_next = false;
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
                
// ######################################## Stack operations ########################################
                case '1':
                    stack.push(1);
                    break;
                case '2':
                    stack.push(2);
                    break;
                case '3':
                    stack.push(3);
                    break;
                case '4':
                    stack.push(4);
                    break;
                case '5':
                    stack.push(5);
                    break;
                case '6':
                    stack.push(6);
                    break;
                case '7':
                    stack.push(7);
                    break;
                case '8':
                    stack.push(8);
                    break;
                case '9':
                    stack.push(9);
                    break;
                case '0':
                    stack.push(0);
                    break;

// ######################################## Calculations ########################################
                // Addition
                case '+':
                    // Throw error if stack is too small
                    if (stack.size() < 2)
                    {
                        std::cout << "Stack underflow" << std::endl;
                        running = false;
                        break;
                    }
                    
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
                    // Throw error if stack is too small
                    if (stack.size() < 2)
                    {
                        std::cout << "Stack underflow" << std::endl;
                        running = false;
                        break;
                    }

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
                    // Throw error if stack is too small
                    if (stack.size() < 2)
                    {
                        std::cout << "Stack underflow" << std::endl;
                        running = false;
                        break;
                    }

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
                    // Throw error if stack is too small
                    if (stack.size() < 2)
                    {
                        std::cout << "Stack underflow" << std::endl;
                        running = false;
                        break;
                    }

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
                    // Throw error if stack is too small
                    if (stack.size() < 2)
                    {
                        std::cout << "Stack underflow" << std::endl;
                        running = false;
                        break;
                    }

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
                    // Go right if the stack is empty
                    if (stack.empty())
                    {
                        direction_x = 1;
                        direction_y = 0;
                        break;
                    }

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
                    // Go down if the stack is empty
                    if (stack.empty())
                    {
                        direction_x = 0;
                        direction_y = 1;
                        break;
                    }
                    
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
                    if (!stack.empty())
                    {
                        stack.push(stack.top());
                    }
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
                    if (!stack.empty())
                    {
                        std::cout << stack.top();
                        stack.pop();
                    }
                    break;
                // Output top element as character
                case ',':
                    if (!stack.empty())
                    {
                        std::cout << (char)stack.top();
                        stack.pop();
                    }
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
                    if (display_stopped)
                    {
                        std::cout << std::endl << "Program stopped" << std::endl;
                    }
                    running = false;
                    break;
            }
        }

        // Move the cursor
        cursor_x += direction_x;
        cursor_y += direction_y;

        // Wrap the cursor around the grid
        if (cursor_x < 0)
        {
            cursor_x = COLS - 1;
        }
        else if (cursor_x >= COLS)
        {
            cursor_x = 0;
        }

        if (cursor_y < 0)
        {
            cursor_y = ROWS - 1;
        }
        else if (cursor_y >= ROWS)
        {
            cursor_y = 0;
        }

    }

    if (running == true)
    {
        std::cout << "Error: Program did not stop" << std::endl;
    }

    return 0;
}