#include "intervalBlock.h"

IntervalBlock::IntervalBlock()
{
    m_LowerBound = 0.0;
    m_UpperBound = 0.0;
    m_LowerCoverage = '(';
    m_UpperCoverage = ')';
}

IntervalBlock::IntervalBlock(double LowerBound, double UpperBound, int LowerCoverage, int UpperCoverage)
{
    m_LowerBound = LowerBound;
    m_UpperBound = UpperBound;
    m_LowerCoverage = LowerCoverage;
    m_UpperCoverage = UpperCoverage;
}

std::vector<IntervalBlock> IntervalBlock::operator+(IntervalBlock& rhs)
{
    // Determine if there are overlapping intervals
    // Scenarios:
    // 1.) Overlapped but not at border 
    //          e.g. [1,3] + (2,4) = [1,4)
    //          e.g. [1,6) + (2,4) = [1,6]
    // 2.) Overlapped but at border 
    //          e.g. [1,3) + (3,6) = {[1,3), (3,6)}
    //          e.g. [1,3] + (3,6) = [1,6)
    //          e.g. [1,3] + [3,6) = [1,6)
    //          e.g. [1,3) + [3,6) = [1,6)
    //          e.g. [1,6) + [3,6] = [1,6] -- Edge case
    //          e.g. [1,6] + (1,3) = [1,6] -- Edge case
    // 3.) No overlapping at all
    //          e.g. [1,3) + [4,6) = {[1,3), [4,6)}
    // ** Intervals can be multi-intervals
    //          e.g. {(1,3],(4,6)} + {[2,4),([6,8])} = {(1,4),(4,8]}

    std::vector<IntervalBlock> result;

    // Scenario 1 - Overlapping but not at border
    if((this->m_LowerBound < rhs.m_UpperBound && this->m_UpperBound > rhs.m_LowerBound) &&
       (this->m_LowerBound != rhs.m_LowerBound && this->m_UpperBound != rhs.m_UpperBound))
    {
        //std::cout << "Scenario 1 is called.\n";
        int LowerCoverage = (this->m_LowerBound < rhs.m_LowerBound) ? this->m_LowerCoverage : rhs.m_LowerCoverage;
        int UpperCoverage = (this->m_UpperBound > rhs.m_UpperBound) ? this->m_UpperCoverage : rhs.m_UpperCoverage;
        IntervalBlock block_result(std::min(this->m_LowerBound, rhs.m_LowerBound),
                                   std::max(this->m_UpperBound, rhs.m_UpperBound),
                                   LowerCoverage, UpperCoverage); 
        result.push_back(block_result);
    }
    // Scenario 2 - Overlapping but at border
    else if((this->m_UpperBound == rhs.m_LowerBound) || (this->m_LowerBound == rhs.m_UpperBound) ||
            (this->m_LowerBound == rhs.m_LowerBound) || (this->m_UpperBound == rhs.m_UpperBound))
    {
        //std::cout << "Scenario 2 is called.\n";
        if(this->m_UpperBound == rhs.m_LowerBound && this->m_UpperCoverage ==')' && rhs.m_LowerCoverage == '(')
        {
                result.push_back(*this);
                result.push_back(rhs);
        }
        else if(this->m_LowerBound == rhs.m_UpperBound && this->m_LowerCoverage =='(' && rhs.m_UpperCoverage == ')')
        {
                result.push_back(rhs);
                result.push_back(*this);
        }
        else
        {
            int LowerCoverage = (this->m_LowerBound < rhs.m_LowerBound) ? this->m_LowerCoverage : rhs.m_LowerCoverage;
            int UpperCoverage = (this->m_UpperBound > rhs.m_UpperBound) ? this->m_UpperCoverage : rhs.m_UpperCoverage;

            // Special case handle. E.g. [1,6) + (1,3) = [1,6)
            if(this->m_LowerBound == rhs.m_LowerBound)
                LowerCoverage = std::max(this->m_LowerCoverage, rhs.m_LowerCoverage);
            if(this->m_UpperBound == rhs.m_UpperBound)
                UpperCoverage = std::max(this->m_UpperCoverage, rhs.m_UpperCoverage);

            IntervalBlock block_result(std::min(this->m_LowerBound, rhs.m_LowerBound),
                                       std::max(this->m_UpperBound, rhs.m_UpperBound),
                                       LowerCoverage, UpperCoverage); 
            result.push_back(block_result);
        }
    }
    // Scenario 3 - No overlapping at all
    else 
    {
        //std::cout << "Scenario 3 is called.\n";
        (this->m_LowerBound < rhs.m_LowerBound) ? result.push_back(*this): result.push_back(rhs);
        (this->m_LowerBound > rhs.m_LowerBound) ? result.push_back(*this): result.push_back(rhs);
    }
    return result;
}

std::vector<IntervalBlock> IntervalBlock::operator-(IntervalBlock& rhs)
{
    // Determine if there are overlapping intervals
    // Scenarios:
    // 1.) Overlapped but not at border
    //          e.g. [1,3] - [2,4] = [1,2) -- 1a
    //          e.g. [2,5] - [1,3] = (3,5] -- 1b
    //          e.g. [1,6) - (2,4) = {[1,2],[4,6)} -- 1c
    // 2.) Overlapped but at border 
    //          e.g. [1,3) - (3,6) = [1,3)
    //          e.g. [1,3] - (3,6) = [1,3]
    //          e.g. [1,3] - [3,6) = [1,3)
    //          e.g. [1,3) - [3,6) = [1,3)
    //          e.g. [1,6] - [3,6) = {[1,3),[6,6]} -- Edge case
    //          e.g. [1,6] - (3,6) = {[1,3],[6,6]} -- Edge case
    //          e.g. [1,6] - [3,6] = [1,3)
    //          e.g. [1,6) - [3,6] = [1,3)
    //          e.g. [1,6) - [3,6) = [1,3)
    //          e.g. [1,6) - (3,6) = [1,3]
    //          e.g. [1,6] - (1,3) = {[1,1],[3,6]} -- Edge case
    // 3.) No overlapping at all (meaningless subtraction)
    //          e.g. [1,3) - [4,6) = [1,3)
    // ** Intervals can be multi-intervals
    //          e.g. {(1,3],(4,6)} - {[2,4),([6,8])} = {(1,4),(4,8]}
    std::vector<IntervalBlock> result;

    // Scenario 1 - Overlapping but not at border
    if((this->m_LowerBound < rhs.m_UpperBound && this->m_UpperBound > rhs.m_LowerBound) &&
       (this->m_LowerBound != rhs.m_LowerBound && this->m_UpperBound != rhs.m_UpperBound))
    {
        IntervalBlock block_result;
        //std::cout << "Scenario 1 is called.\n";
        if(this->m_UpperBound < rhs.m_UpperBound && this->m_LowerBound < rhs.m_LowerBound)
        {   // Case 1a
            int LowerCoverage = this->m_LowerCoverage;
            int UpperCoverage = (rhs.m_LowerCoverage == '[') ? ')' : ']';
            block_result = IntervalBlock(this->m_LowerBound, rhs.m_LowerBound, LowerCoverage, UpperCoverage);
            result.push_back(block_result);
        }
        else if(this->m_UpperBound > rhs.m_UpperBound && this->m_LowerBound > rhs.m_LowerBound)
        {
            // Case 1b
            int LowerCoverage = (rhs.m_UpperCoverage == ']') ? '(' : '[';
            int UpperCoverage = this->m_UpperCoverage;
            block_result = IntervalBlock(rhs.m_UpperBound, this->m_UpperBound, LowerCoverage, UpperCoverage);
            result.push_back(block_result);
        }
        else
        {
            // Case 1c
            int LowerCoverage_a = this->m_LowerCoverage;
            int UpperCoverage_a = (rhs.m_LowerCoverage == '[') ? ')' : ']';
            IntervalBlock block_result_a = IntervalBlock(this->m_LowerBound, rhs.m_LowerBound, LowerCoverage_a, UpperCoverage_a);
            result.push_back(block_result_a);

            int LowerCoverage_b = (rhs.m_UpperCoverage == ']') ? '(' : '[';
            int UpperCoverage_b = this->m_UpperCoverage;
            IntervalBlock block_result_b = IntervalBlock(rhs.m_UpperBound, this->m_UpperBound, LowerCoverage_b, UpperCoverage_b);
            result.push_back(block_result_b);            
        } 
    }
    // Scenario 2 - Overlapping but at border
    else if((this->m_UpperBound == rhs.m_LowerBound) || (this->m_LowerBound == rhs.m_UpperBound) ||
            (this->m_LowerBound == rhs.m_LowerBound) || (this->m_UpperBound == rhs.m_UpperBound))
    {
        //std::cout << "Scenario 2 is called.\n";
        if(this->m_UpperBound == rhs.m_LowerBound)
        {
            int LowerCoverage = this->m_LowerCoverage;
            int UpperCoverage = (this->m_UpperCoverage ==']' && rhs.m_LowerCoverage == '[') ? ')' : this->m_UpperCoverage;
            IntervalBlock block_result(this->m_LowerBound, this->m_UpperBound, LowerCoverage, UpperCoverage); 
            result.push_back(block_result);
        }
        else if(this->m_LowerBound == rhs.m_UpperBound)
        {
            int LowerCoverage = (this->m_LowerCoverage =='[' && rhs.m_UpperCoverage == ']') ? '(' : this->m_LowerCoverage;
            int UpperCoverage = this->m_UpperCoverage;
            IntervalBlock block_result(this->m_LowerBound, this->m_UpperBound, LowerCoverage, UpperCoverage); 
            result.push_back(block_result);
        }
        else
        {
            if(this->m_UpperBound == rhs.m_UpperBound ||
                (this->m_LowerBound == rhs.m_LowerBound && this->m_LowerCoverage == '[' && rhs.m_LowerCoverage == '('))
            {
            int LowerCoverage_a = this->m_LowerCoverage;
            int UpperCoverage_a = (rhs.m_LowerCoverage == '[') ? ')' : ']';
            IntervalBlock block_result_a = IntervalBlock(this->m_LowerBound, rhs.m_LowerBound, LowerCoverage_a, UpperCoverage_a);
            result.push_back(block_result_a);
            }

            if(this->m_LowerBound == rhs.m_LowerBound || 
                (this->m_UpperBound == rhs.m_UpperBound && this->m_UpperCoverage == ']' && rhs.m_UpperCoverage == ')'))
            {
                int LowerCoverage_b = (rhs.m_UpperCoverage == ']') ? '(' : '[';
                int UpperCoverage_b = this->m_UpperCoverage;
                IntervalBlock block_result_b = IntervalBlock(rhs.m_UpperBound, this->m_UpperBound, LowerCoverage_b, UpperCoverage_b);
                result.push_back(block_result_b);
            }
        }
    }
    // Scenario 3 - No overlapping at all
    else 
    {
        //std::cout << "Scenario 3 is called.\n";
        result.push_back(*this);
    }
    return result;
}

double IntervalBlock::getLowerBound()
{
    return m_LowerBound;
}

double IntervalBlock::getUpperBound()
{
    return m_UpperBound;
}

int IntervalBlock::getLowerCoverage()
{
    return m_LowerCoverage;
}

int IntervalBlock::getUpperCoverage()
{
    return m_UpperCoverage;
}

void IntervalBlock::printBlockRange()
{
    // Coverage values: '(' = 40, ')' = 41, '[' = 91, ']' = 93
    // Expected values: () = 81, [) = 132, (] = 133, [] = 184
    int coverage = m_LowerCoverage + m_UpperCoverage;
    switch(coverage)
    {
        case 81:
            std::cout << "(" << m_LowerBound << ", " << m_UpperBound << ")";
            break;
        case 132:
            std::cout << "[" << m_LowerBound << ", " << m_UpperBound << ")";
            break;
        case 133:
            std::cout << "(" << m_LowerBound << ", " << m_UpperBound << "]";
            break;
        case 184:
            std::cout << "[" << m_LowerBound << ", " << m_UpperBound << "]";
            break;
        default:
            std::cout << "(" << m_LowerBound << ", " << m_UpperBound << ")";
            break;
    }
}

std::ostream& operator<<(std::ostream& os, const IntervalBlock& output)
{
    // Coverage values: '(' = 40, ')' = 41, '[' = 91, ']' = 93
    // Expected values: () = 81, [) = 132, (] = 133, [] = 184
    int coverage = output.m_LowerCoverage + output.m_UpperCoverage;
    switch(coverage)
    {
        case 81:
            os << "(" << output.m_LowerBound << ", " << output.m_UpperBound << ")";
            break;
        case 132:
            os << "[" << output.m_LowerBound << ", " << output.m_UpperBound << ")";
            break;
        case 133:
            os << "(" << output.m_LowerBound << ", " << output.m_UpperBound << "]";
            break;
        case 184:
            os << "[" << output.m_LowerBound << ", " << output.m_UpperBound << "]";
            break;
        default:
            os << "(" << output.m_LowerBound << ", " << output.m_UpperBound << ")";
            break;
    }
    return os;
}