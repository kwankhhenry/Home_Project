#include <sstream>
#include "gtest/gtest.h"
#include "intervals.h"

TEST(Addition, TestCase_1)
{
	Intervals s0("[1,3)");
	Intervals s2("(4,6]");

	std::ostringstream os;
	os << s0+s2;
    EXPECT_EQ(os.str(), "{[1,3),(4,6]}") << "Testing";
}

TEST(Addition, TestCase_2)
{
	Intervals s1("(2,5]");
	Intervals s2("(4,6]");

	std::ostringstream os;
	os << s1+s2;
    EXPECT_EQ(os.str(), "(2,6]");
}

int main(int argc, char **argv) 
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}