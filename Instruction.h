#include <vector>
#include "expression/Expression.h"

class Instruction
{
public:
    std::vector<std::string> getFileData(const std::string filename);
    std::vector<std::string> splitBySpace(std::string args);
    Expression parseLine(const std::string raw_line);
};