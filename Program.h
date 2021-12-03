#include <vector>
#include <string>
#include "Instruction.h"
#include "expression/Expression.h"
#include "variable_snapshot/VariableSnapshot.h"

class Program : Instruction
{
private:
    int loopCounter;

    std::vector<Expression> loadData();
    void run();
    VariableSnapshot eval(Expression &expression, VariableSnapshot &prev_strate, std::vector<Expression> &expressions, size_t expression_position);
    VariableSnapshot setValue(char var, double value, VariableSnapshot &state);
    double getValue(char var, VariableSnapshot &state);
    double condense(double x, double y, std::string &op);
    VariableSnapshot handleAssign(Expression &expression, VariableSnapshot &state);

public:
    void startProgram();
};