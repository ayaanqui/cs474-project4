#include <string>
#include <vector>
#include "Expression.h"
#include <iostream>

Expression::Expression(const std::string expression, const std::string line_number, const std::string var, const std::string assigner, const std::vector<std::string> *args)
{
    this->expression = expression;
    // parse line number to int
    this->line_number = std::stoi(line_number);
    this->var = var[0];
    this->assigner = assigner[0];

    this->arg1 = args->at(0);
    if (args->size() == 3)
    {
        this->arg2 = args->at(1);
        this->arg3 = args->at(2);
    }
}

void Expression::print()
{
    std::cout << "Expression: " << this->expression << std::endl;
    std::cout << "Line number: " << this->line_number << std::endl;
    std::cout << "Left hand side: " << this->var << std::endl;
    std::cout << "Assigner: " << this->assigner << std::endl;
    std::cout << "Arg 1: " << this->arg1 << std::endl;

    if (this->arg2 != "")
        std::cout << "Arg 2: " << this->arg2 << std::endl;
    if (this->arg3 != "")
        std::cout << "Arg 3: " << this->arg3 << std::endl;
}