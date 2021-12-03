#pragma once

#include <string>
#include <vector>

class Expression
{
public:
    std::string expression;
    int line_number;
    char var;
    char assigner;
    std::string arg1;
    std::string arg2;
    std::string arg3;
    Expression(const std::string expression, const std::string line_number, const std::string var, const std::string assigner, const std::vector<std::string> *args);
    Expression(Expression *other);
    void print();
};