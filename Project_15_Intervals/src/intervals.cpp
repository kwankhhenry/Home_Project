#include "intervals.h"

class Intervals::pImplIntervals
{
public:
    pImplIntervals(): m_interval_size(0){};
    size_t m_interval_size;
    std::vector<IntervalBlock> m_interval_buffer;
};

Intervals::Intervals()
{
    this->m_Impl = new pImplIntervals;
}

Intervals::~Intervals()
{
    delete m_Impl;
}

Intervals::Intervals(const std::string& interval) : Intervals()
{
    if(!parseIntervals(interval))
        std::cout << "Parse " << interval << " error!\n";
}

Intervals::Intervals(const Intervals& operand) : Intervals()
{
    //std::cout << "Copied constructor is called.\n";
    this->m_Impl->m_interval_size = operand.m_Impl->m_interval_size;
    this->m_Impl->m_interval_buffer = operand.m_Impl->m_interval_buffer;
}

Intervals& Intervals::operator=(const Intervals& rhs)
{
    //std::cout << "Assignment operator is called.\n";
    this->m_Impl->m_interval_size = rhs.m_Impl->m_interval_size;
    this->m_Impl->m_interval_buffer = rhs.m_Impl->m_interval_buffer;
    return *this;
}

Intervals Intervals::operator+(const Intervals& rhs)
{
    std::vector<IntervalBlock>::iterator ita = this->m_Impl->m_interval_buffer.begin();
    std::vector<IntervalBlock>::iterator itb = rhs.m_Impl->m_interval_buffer.begin();
    std::vector<IntervalBlock> result_m_intervals;
    while(ita != this->m_Impl->m_interval_buffer.end() || itb != rhs.m_Impl->m_interval_buffer.end())
    {
        if(result_m_intervals.empty())
        {
            (ita->getLowerBound() <= itb->getLowerBound()) ? result_m_intervals.push_back(*ita++): result_m_intervals.push_back(*itb++);
        }
        else
        {
            IntervalBlock targetBuffer;
            if(itb == rhs.m_Impl->m_interval_buffer.end() 
                || (ita != this->m_Impl->m_interval_buffer.end() && ita->getLowerBound() <= itb->getLowerBound()))
                targetBuffer = *(ita++);
            else if(ita == this->m_Impl->m_interval_buffer.end() 
                || (itb != rhs.m_Impl->m_interval_buffer.end() && itb->getLowerBound() <= ita->getLowerBound()))
                targetBuffer = *(itb++);
            
            std::vector<IntervalBlock> temp = result_m_intervals.back() + targetBuffer;
            result_m_intervals.pop_back();
            result_m_intervals.insert(result_m_intervals.end(), temp.begin(), temp.end());
        }
    }
    Intervals results;
    results.m_Impl->m_interval_buffer = result_m_intervals;
    results.m_Impl->m_interval_size = result_m_intervals.size();
    return results;
}

Intervals Intervals::operator-(const Intervals& rhs)
{
    std::vector<IntervalBlock>::iterator ita = this->m_Impl->m_interval_buffer.begin();
    std::vector<IntervalBlock>::iterator itb = rhs.m_Impl->m_interval_buffer.begin();
    std::vector<IntervalBlock> result_m_intervals;
    while(ita != this->m_Impl->m_interval_buffer.end() || itb != rhs.m_Impl->m_interval_buffer.end())
    {
        // Note: subtraction is meaningless if there are no overlapping intervals, therefore the right operand needs to overlap
        // with the left operand otherwise have no impact to the subtraction
        if(result_m_intervals.empty())
        {
            //std::cout << "a called.\n";
            result_m_intervals.push_back(*ita++);
        }
        else
        {
            if((ita != this->m_Impl->m_interval_buffer.end() && itb == rhs.m_Impl->m_interval_buffer.end()) || 
                (ita != this->m_Impl->m_interval_buffer.end() && result_m_intervals.back().getUpperBound() < itb->getLowerBound()))
            {
                //std::cout << "b called.\n";
                result_m_intervals.push_back(*ita++);
            }                   
            else 
            {
                //std::cout << "c called.\n";
                std::vector<IntervalBlock> temp = result_m_intervals.back() - *(itb++);
                result_m_intervals.pop_back();
                result_m_intervals.insert(result_m_intervals.end(), temp.begin(), temp.end());
            }
        }
    }
    Intervals results;
    results.m_Impl->m_interval_buffer = result_m_intervals;
    results.m_Impl->m_interval_size = result_m_intervals.size();
    return results;
}

void Intervals::printIntervals()
{
    if(this->m_Impl->m_interval_size <= 0) return;
    if(this->m_Impl->m_interval_size == 1) this->m_Impl->m_interval_buffer.front().printBlockRange();
    else
    {
        std::cout << "{";
        for(size_t i = 0; i < this->m_Impl->m_interval_size; i++)
        {
            this->m_Impl->m_interval_buffer[i].printBlockRange();
            if(i != this->m_Impl->m_interval_size - 1) std::cout << ",";
        }
        std::cout << "}";
    }
    std::cout << "\n";
}

std::ostream& operator<<(std::ostream& os, const Intervals& output)
{
    if(output.m_Impl->m_interval_size <= 0)
        os << "";
    if(output.m_Impl->m_interval_size == 1) 
        os << output.m_Impl->m_interval_buffer.front();
    else
    {
        os << "{";
        for(size_t i = 0; i < output.m_Impl->m_interval_size; i++)
        {
            os << output.m_Impl->m_interval_buffer[i];
            if(i != output.m_Impl->m_interval_size - 1) 
                os << ",";
        }
        os << "}";
    }

    return os;
}

bool Intervals::parseIntervals(const std::string& strInput)
{
    if(strInput.length() == 0) return false;

    // Check if multi-interval
    std::size_t OpenCurly = strInput.find_first_of('{');
    std::size_t CloseCurly = strInput.find_last_of('}');

    if(OpenCurly != std::string::npos && CloseCurly != std::string::npos)
    {
        int strLength = CloseCurly - OpenCurly - 1;
        std::string strIntervals = std::string(strInput, OpenCurly+1, strLength);
        //std::cout << "StrIntervals: " << strIntervals << std::endl;

        std::size_t OpenBlock = 0, CloseBlock = 0;
        // Tokenize each interval (Separated by ',' delimiter)
        OpenBlock = strIntervals.find_first_of("([", CloseBlock);
        CloseBlock = strIntervals.find_first_of(")]", CloseBlock);
        while(strIntervals.length() > 0 && OpenBlock != std::string::npos && CloseBlock != std::string::npos)
        {
            size_t BlockLength = CloseBlock - OpenBlock +1;
            std::string token = strIntervals.substr(OpenBlock, BlockLength);
            //std::cout << "Token: " << token << std::endl;
            if(!parseBlocks(token))
                return false;

            // Parse next block in the multi-interval
            if(strIntervals.length() - CloseBlock > 0)
            {
                strIntervals = strIntervals.substr(CloseBlock+1, strIntervals.length() - CloseBlock);
                //std::cout << "Next strIntervals: " << strIntervals << std::endl;
                OpenBlock = strIntervals.find_first_of("([");
                CloseBlock = strIntervals.find_first_of(")]");
                //std::cout << "Next block position: " << OpenBlock << ", " << CloseBlock << std::endl;
            }
        }
        return true;
    }
    else
        return parseBlocks(strInput);
    return false;
}

// Str Input should be in the form single block e.g. [2, 3], (3, 5]...
bool Intervals::parseBlocks(const std::string& strInput)
{
    // Analyze bracket combinations
    std::string OpenBrackets = "([";
    std::string CloseBrackets = "])";
    std::size_t OpenPos = strInput.find_first_of(OpenBrackets);
    std::size_t ClosePos = strInput.find_last_of(CloseBrackets);
    
    if(OpenPos == std::string::npos || ClosePos == std::string::npos)
        return false;

    if(strInput.length() == 0) return false;

    std::stack<char> bracketStack;
    std::string stream, left, right;
    int leftBracketNum = 0, rightBracketNum = 0;
    for(size_t i = 0; i < strInput.length(); i++)
    {
        if(strInput[i] == '(' || strInput[i] == '[')
        {
            bracketStack.push(strInput[i]);
            leftBracketNum += strInput[i];
        }
        else if(strInput[i] == ')' || strInput[i] == ']')
        {
            bracketStack.pop();
            rightBracketNum += strInput[i];
        }
        else if(strInput[i] == ',')
        {
            left = stream;
            stream.clear();
        }
        else
            stream += strInput[i];
    }
    right = stream;

    if(!bracketStack.empty()) return false;

    double leftVal = std::atof(left.c_str());
    double rightVal = std::atof(right.c_str());

    if(leftVal > rightVal) return false;
    this->m_Impl->m_interval_buffer.push_back(IntervalBlock(leftVal, rightVal, leftBracketNum, rightBracketNum));
    this->m_Impl->m_interval_size++;
    return true;
}
