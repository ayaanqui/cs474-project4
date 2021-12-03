#include <vector>
#include <string>
#include "Instruction.h"

class Program : Instruction
{
private:
    int loopCounter, i;
    bool stopLoop;

public:
    void startProgram();
};