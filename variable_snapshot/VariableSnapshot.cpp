#include <iostream>
#include "VariableSnapshot.h"

VariableSnapshot::VariableSnapshot(double w, double x, double y, double z)
{
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
}

void VariableSnapshot::print()
{
    std::cout << "Result:" << std::endl;
    std::cout << "x = " << this->x << ", "
              << "y = " << this->y << ", "
              << "w = " << this->w << " and "
              << "z = " << this->z
              << "" << std::endl;
}