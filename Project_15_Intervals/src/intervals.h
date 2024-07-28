#ifndef INTERVALS_H
#define INTERVALS_H

#include <vector>
#include <string>
#include <stack>
#include "intervalBlock.h"

class Intervals
{
public:
    Intervals();
    Intervals(const std::string&);
    Intervals(const Intervals&);
    ~Intervals();

    Intervals& operator=(const Intervals&);
    Intervals operator+(const Intervals&);
    Intervals operator-(const Intervals&);

    void printIntervals();
    friend std::ostream& operator<<(std::ostream&, const Intervals&);
private:
    bool parseIntervals(const std::string&);
    bool parseBlocks(const std::string&);

    class pImplIntervals;
    pImplIntervals* m_Impl;
};

#endif