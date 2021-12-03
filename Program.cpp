#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <cmath>
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

        new_snapshot.print();
        std::cout << std::endl;
    }
}

VariableSnapshot Program::eval(Expression &expression, VariableSnapshot &prev_state)
{
    double arg1_value;
    switch (expression.assigner)
    {
    case '=':
        if (expression.arg2 == "" || expression.arg3 == "")
        {
            // Then arg1 must be a constant value
            double value = std::stod(expression.arg1);
            return this->setValue(expression.var, value, prev_state);
        }
        // arg1 must be a var, arg3 could be a var or a constant value
        arg1_value = this->getValue(expression.arg1[0], prev_state);

        // Try to convert arg3 to double otherwise catch because it's a variable and cannot be converted
        try
        {
            double arg3 = std::stod(expression.arg3);
            double value = this->condense(arg1_value, arg3, expression.arg2);
            return this->setValue(expression.var, value, prev_state);
        }
        catch (std::invalid_argument &e)
        {
            // arg3 must be a variable, so get the value first...
            double arg3_value = this->getValue(expression.arg3[0], prev_state);
            double value = this->condense(arg1_value, arg3_value, expression.arg2);
            return this->setValue(expression.var, value, prev_state);
        }
        break;
    case '?':
        std::cout << "Loop operator" << std::endl;
        break;
    }
    return VariableSnapshot(0, 0, 0, 0);
}

double Program::condense(double x, double y, std::string &op)
{
    if (op == "+")
        return x + y;
    else if (op == "-")
        return x - y;
    else if (op == "*")
        return x * y;
    else if (op == "/")
        return x / y;
    else if (op == "**")
        return std::pow(x, y);
    return 0;
}

/**
 * @brief Creates a VariableSnapshot object with the new value for the specified variable (w, x, y or z) writing the older values for the rest of the variables.
 * 
 * @param var Variable that needs to be assigned a new value
 * @param value Value that needs to be stored
 * @param state
 * @return VariableSnapshot 
 */
VariableSnapshot Program::setValue(char var, double value, VariableSnapshot &state)
{
    switch (var)
    {
    case 'w':
        return VariableSnapshot(value, state.x, state.y, state.z);
    case 'x':
        return VariableSnapshot(state.w, value, state.y, state.z);
    case 'y':
        return VariableSnapshot(state.w, state.x, value, state.z);
    case 'z':
        return VariableSnapshot(state.w, state.x, state.y, value);
    }
    return VariableSnapshot(0, 0, 0, 0);
}

/**
 * @brief Given a variable name return the value that it holds
 * 
 * @param var Variable name
 * @param state
 * @return double 
 */
double Program::getValue(char var, VariableSnapshot &state)
{
    switch (var)
    {
    case 'w':
        return state.w;
    case 'x':
        return state.x;
    case 'y':
        return state.y;
    case 'z':
        return state.z;
    }
    return 0;
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