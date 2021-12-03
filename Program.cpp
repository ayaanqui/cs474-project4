#include <iostream>
#include <string>
#include <vector>
#include "expression/Expression.h"
#include "Program.h"

void Program::startProgram()
{
    while (true)
    {
        std::string input;
        std::cout << "> ";
        std::getline(std::cin, input);

        char input_command = input[0];
        switch (input_command)
        {
        case 'r':
            std::cout << "Run the entire program" << std::endl;
            break;
        case 's':
            std::cout << "Step by step program execution" << std::endl;
        case 'x':
            return;
        default:
            std::cout << "Unknown command" << std::endl;
            break;
        }

        // Blank line...
        std::cout << std::endl;
    }
}

std::vector<Expression> Program::loadData()
{
    std::vector<std::string> file_data = this->getFileData("pc_input.txt");
    std::vector<Expression> parsed_data;
    for (std::string &line : file_data)
        parsed_data.push_back(this->parseLine(line));
    return parsed_data;
}