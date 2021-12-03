#pragma once

class VariableSnapshot
{
public:
    double w;
    double x;
    double y;
    double z;

    VariableSnapshot(double w, double x, double y, double z);
    void print();
};