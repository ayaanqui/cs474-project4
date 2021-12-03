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
    VariableSnapshot handleAssign(Expression &expression, VariableSnapshot &state);

public:
    void startProgram();
};