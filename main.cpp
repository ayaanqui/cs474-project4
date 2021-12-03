#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "expression/Expression.h"

/**
 * @brief Reads "pc_input.txt" and returns the contents of this
 * file a vector of strings, with each line as the element of the array
 * 
 * @return std::vector<std::string> 
 */
std::vector<std::string> file_contents()
{
    std::vector<std::string> data;
    std::string line;
    std::ifstream pc_input_file("pc_input.txt");
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
std::vector<std::string> parse_args(std::string args)
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

Expression parse_line(const std::string raw_line)
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

    std::vector<std::string> args = parse_args(line);
    Expression expression(raw_line, line_number, var, op, &args);
    return expression;
}

int main()
{
    std::vector<std::string> file_data = file_contents();
    for (std::string &line : file_data)
    {
        Expression expression = parse_line(line);
        expression.print();
        std::cout << std::endl;
    }
    return 0;
}