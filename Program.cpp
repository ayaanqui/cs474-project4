#include <iostream>
#include <string>
#include <vector>
#include "expression/Expression.h"
#include "Program.h"

void Program::startProgram()
{
    std::vector<std::string> file_data = this->getFileData("pc_input.txt");
    std::vector<Expression> parsed_data;
    for (std::string &line : file_data)
        parsed_data.push_back(this->parseLine(line));

    for (Expression &exp : parsed_data)
    {
        exp.print();
        std::cout << std::endl;
    }
}