#include <iostream>
#include <string>
#include <vector>
#include <exception>
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

    for (size_t i = 0; i < expressions.size(); ++i)
    {
        Expression &expression = expressions[i];
        VariableSnapshot new_snapshot = this->eval(expression, state_snapshot.back(), expressions, i);
        state_snapshot.push_back(new_snapshot);

        new_snapshot.print();
        std::cout << std::endl;
    }
}

VariableSnapshot Program::eval(Expression &expression, VariableSnapshot &prev_state, std::vector<Expression> &expressions, size_t expression_position)
{
    VariableSnapshot new_state(prev_state.w, prev_state.x, prev_state.y, prev_state.z);
    double var_value;
    int goto_line;

    switch (expression.assigner)
    {
    case '=':
        new_state = handleAssign(expression, prev_state);
        return new_state;
    case '?':
        var_value = this->getValue(expression.var, prev_state);
        if (var_value == 0)
        {
            // Reset loop related member variables
            this->loopCounter = 0;
            return new_state;
        }

        // Otherwise append loop commands to expressions
        goto_line = stoi(expression.arg1);
        // copy commands to be looped
        std::vector<Expression> loop_commands;
        for (int i = goto_line - 1; i < expression.line_number; ++i)
        {
            Expression exp(&(expressions[i]));
            loop_commands.push_back(exp);
        }
        // add copied commands to expressions
        expressions.insert(expressions.begin() + expression_position + 1, loop_commands.begin(), loop_commands.end());
        this->loopCounter++;
        break;
    }
    return new_state;
}

/**
 * @brief Handles the '=' operator
 */
VariableSnapshot Program::handleAssign(Expression &expression, VariableSnapshot &state)
{
    if (expression.arg2 == "" || expression.arg3 == "")
    {
        // Then arg1 must be a constant value
        double value = std::stod(expression.arg1);
        return this->setValue(expression.var, value, state);
    }
    // arg1 must be a var, arg3 could be a var or a constant value
    double arg1_value = this->getValue(expression.arg1[0], state);

    // Try to convert arg3 to double otherwise catch because it's a variable and cannot be converted
    try
    {
        double arg3 = std::stod(expression.arg3);
        double value = this->condense(arg1_value, arg3, expression.arg2);
        return this->setValue(expression.var, value, state);
    }
    catch (std::invalid_argument &e)
    {
    }
    // arg3 must be a variable, so get the value first...
    double arg3_value = this->getValue(expression.arg3[0], state);
    double value = this->condense(arg1_value, arg3_value, expression.arg2);
    return this->setValue(expression.var, value, state);
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