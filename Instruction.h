#include <vector>
#include "expression/Expression.h"
#include "variable_snapshot/VariableSnapshot.h"

class Instruction
{
public:
    std::vector<std::string> getFileData(const std::string filename);
    std::vector<std::string> splitBySpace(std::string args);
    Expression parseLine(const std::string raw_line);
    VariableSnapshot setValue(char var, double value, VariableSnapshot &state);
    double getValue(char var, VariableSnapshot &state);
    double condense(double x, double y, std::string &op);
};