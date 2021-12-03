#include <iostream>
#include <string>
#include <vector>
#include "expression/Expression.h"
#include "variable_snapshot/VariableSnapshot.h"
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
            this->run();
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

/**
 * @brief Mehtod for the 'r' command. Runs the entire program all at once. Prints the state after each line is executed.
 */
void Program::run()
{
    std::vector<Expression> expressions = loadData();
    std::vector<VariableSnapshot> state_snapshot;
    // Insert first snapshot state
    state_snapshot.push_back(VariableSnapshot(0, 0, 0, 0));

    for (Expression &expression : expressions)
    {
        VariableSnapshot new_snapshot = this->eval(expression, state_snapshot.back());
        state_snapshot.push_back(new_snapshot);
    }
}

/**
 * @brief Loads and parses the data from 'pc_input.txt' file into a vector of Expression
 * 
 * @return std::vector<Expression> 
 */
std::vector<Expression> Program::loadData()
{
    std::vector<std::string> file_data = this->getFileData("pc_input.txt");
    std::vector<Expression> parsed_data;
    for (std::string &line : file_data)
        parsed_data.push_back(this->parseLine(line));
    return parsed_data;
}