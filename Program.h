#include <vector>
#include <string>
#include "Instruction.h"
#include "expression/Expression.h"
#include "variable_snapshot/VariableSnapshot.h"

class Program : Instruction
{
private:
    int loopCounter;
    bool stopLoop;

    std::vector<Expression> loadData();
    void run();
    VariableSnapshot eval(Expression &expression, VariableSnapshot &prev_state, std::vector<Expression> &expressions, size_t expression_position);
    VariableSnapshot handleAssign(Expression &expression, VariableSnapshot &state);
    VariableSnapshot handleLoop(Expression &expression, VariableSnapshot &state, std::vector<Expression> &expressions, size_t expression_position);

public:
    Program();
    void startProgram();
};