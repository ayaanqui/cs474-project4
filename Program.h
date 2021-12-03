#include <vector>
#include <string>
#include "Instruction.h"
#include "expression/Expression.h"

class Program : Instruction
{
private:
    int loopCounter, i;
    bool stopLoop;

    std::vector<Expression> loadData();
    void run();
    VariableSnapshot eval(Expression &expression, VariableSnapshot &prev_strate);

public:
    void startProgram();
};