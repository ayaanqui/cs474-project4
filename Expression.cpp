#include <string>
#include <vector>
#include "Expression.h"

Expression::Expression(const std::string expression, const std::string line_number, const std::string var, const std::string assigner, const std::vector<std::string> args)
{
    this->expression = expression;
    // parse line number to int
    this->line_number = std::stoi(line_number);
    this->var = var[0];
    this->assigner = assigner[0];

    this->arg1 = args[0];
    if (args.size() > 1)
    {
        this->arg2 = args[1];
        this->arg3 = args[2];
    }
}