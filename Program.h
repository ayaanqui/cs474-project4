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

public:
    void startProgram();
};