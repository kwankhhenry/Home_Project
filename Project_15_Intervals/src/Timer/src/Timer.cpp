// Reference: https://www.learncpp.com/cpp-tutorial/timing-your-code/
#include "Timer.h" // for std::chrono functions

void Timer::reset()
{
	m_beg = Clock::now();
}

double Timer::elapsed() const
{
	return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
}
