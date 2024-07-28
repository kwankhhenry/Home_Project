#ifndef INTERVALBLOCK_H
#define INTERVALBLOCK_H

#include <iostream>
#include <vector>
#include <string>

class IntervalBlock
{
public:
    IntervalBlock();
    IntervalBlock(double LowerBound, double UpperBound, int UpperCoverage, int LowerCoverage);
    std::vector<IntervalBlock> operator+(IntervalBlock& rhs);
    std::vector<IntervalBlock> operator-(IntervalBlock& rhs);
    double getLowerBound();
    double getUpperBound();
    int getLowerCoverage();
    int getUpperCoverage();

    void printBlockRange();
    friend std::ostream& operator<<(std::ostream&, const IntervalBlock&);
private:
    double m_LowerBound;
    double m_UpperBound;
    int m_LowerCoverage;
    int m_UpperCoverage;
};

#endif