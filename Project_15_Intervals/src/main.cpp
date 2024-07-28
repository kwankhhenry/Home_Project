#include <iostream>
#include <iomanip>
#include "Timer.h"
#include "intervals.h"

using namespace std;

int main() 
{
	Timer t;
	Intervals s0("[1,3)");
	Intervals s1("(2,5]");
	Intervals s2("(4,6]");
	Intervals s3("{(1,2],(4,5)}");
	Intervals s4("{[3,4),[5,6),(7,10]}");
	Intervals s5("[1.5,4.6)");
	Intervals s6(s1);
	Intervals s7 = s2 + s3;

	Intervals s8("{[1,6],(9,12]}");
	Intervals s9("{(1,3),(5,6],[7,10]}");
	Intervals s10 = s8 - s1;
	Intervals s11("[2,4]");
	Intervals s12("[1,6]");
	Intervals s13("(3,6)");

	std::cout << "\n------- Sample Test Scenarios ---------\n";
	std::cout << "*Note: Assume input interval blocks do not overlap each other. E.g. {[1,3),(2,5]} is an invalid input\n";
	std::cout << "\n------- 1. Interval Additions ---------\n";	
	std::cout << "Scenario 1: " << s0 << " + " << s2 << " = " << s0+s2 << std::setw(68) << "...Expected: {[1,3),(4,6)}" << std::endl;	
	std::cout << "Scenario 2: " << s1 << " + " << s2 << " = " << s1+s2 << std::setw(69) << "...Expected: (2,6]" << std::endl;
	std::cout << "Scenario 3: " << s1 << " + " << s3 << " = " << s1+s3 << std::setw(60) << "...Expected: (1,5]" << std::endl;
	std::cout << "Scenario 4: " << s3 << " + " << s4 << " = " << s3+s4 << std::setw(40) << "...Expected: {(1,2],[3,4),(4,6),(7,10)}" << std::endl;
	std::cout << "Scenario 5: " << s5 << " = " << s5 << std::setw(74) << "...Expected: [1.5,4.6)" << std::endl;

	std::cout << "\n------- 2. Interval Subtractions ---------\n";	
	std::cout << "Scenario 6: " << s1 << " - " << s2 << " = " << s1-s2 << std::setw(69) << "...Expected: (2,4]" << std::endl;
	std::cout << "Scenario 7: " << s8 << " - " << s1 << " = " << s8-s1 << std::setw(57) << "...Expected: {[1,2],(5,6],(9,12]}" << std::endl;
	std::cout << "Scenario 8: " << s8 << " - " << s9 << " = " << s8-s9 << std::setw(40) << "...Expected: {(1,1],[3,5],(10,12]}" << std::endl;
	std::cout << "Scenario 9: " << s2 << " - " << s5 << " = " << s2-s5 << std::setw(66) << "...Expected: [4.6, 6]" << std::endl;
	std::cout << "Scenario 10: " << s12 << " - " << s11 << " = " << s12-s11 << std::setw(67) << "...Expected: {[1,2],(4,6]}" << std::endl;
	std::cout << "Scenario 11: " << s12 << " - " << s13 << " = " << s12-s13 << std::setw(67) << "...Expected: {[1,3],[6,6]}" << std::endl;

	std::cout << "\nDuration: " << t.elapsed()*1000.0f << " milliseconds." << std::endl;
	return 0;
}