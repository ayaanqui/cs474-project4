#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include "Instruction.h"
#include "variable_snapshot/VariableSnapshot.h"

/**
 * @brief Reads "pc_input.txt" and returns the contents of this
 * file a vector of strings, with each line as the element of the array
 * 
 * @return std::vector<std::string> 
 */
std::vector<std::string> Instruction::getFileData(const std::string filename)
{
    std::vector<std::string> data;
    std::string line;
    std::ifstream pc_input_file(filename);
    if (!pc_input_file.is_open())
        return data;

    while (std::getline(pc_input_file, line))
    {
        // Ignore lines starting with #
        if (line[0] == '#')
            continue;
        data.push_back(line);
    }
    pc_input_file.close();
    return data;
}

/**
 * @brief Given a string separates the args by space
 * 
 * @param args 
 * @return std::vector<std::string>
 */
std::vector<std::string> Instruction::splitBySpace(std::string args)
{
    std::vector<std::string> res;
    size_t i = 0;
    while (i < args.size())
    {
        if (args[i] == ' ')
        {
            res.push_back(args.substr(0, i));
            args = args.substr(i + 1);
            i = 0;
            continue;
        }
        i++;
    }
    res.push_back(args);
    return res;
}

Expression Instruction::parseLine(const std::string raw_line)
{
    std::string line = raw_line;
    // Find position of ":" and get line number
    const int colon = line.find(':');
    const std::string line_number = line.substr(0, colon);
    // trim to variable position ("0: X..." - line = "X...")
    line = line.substr(colon + 2);

    // Find variable
    const int var_space = line.find(' ');
    const std::string var = line.substr(0, var_space);
    line = line.substr(var_space + 1);

    // Find operator
    const int op_space = line.find(' ');
    const std::string op = line.substr(0, op_space);
    line = line.substr(op_space + 1);

    // Remove period if exists
    if (line.at(line.size() - 1) == '.')
        line = line.substr(0, line.size() - 1);

    std::vector<std::string> args = splitBySpace(line);
    Expression expression(raw_line, line_number, var, op, &args);
    return expression;
}

double Instruction::condense(double x, double y, std::string &op)
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
VariableSnapshot Instruction::setValue(char var, double value, VariableSnapshot &state)
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
double Instruction::getValue(char var, VariableSnapshot &state)
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