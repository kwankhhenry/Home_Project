#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

int add(int x, int y)
{
    return x+y;
}

int subtract(int x, int y)
{
    return x-y;
}

int multiply(int x, int y)
{
    return x*y;
}

int divide(int x, int y)
{
    return x/y;
}

// Function pointer
void printAnswer(int& x, int& y, int (*operation)(int, int))
{
    cout << "Answer is: " << operation(x, y) << endl;
}

int main() 
{
    int x, y, z, temp;
    x = 3;
    y = 5;
    z = 45;

    // Void pointer
    temp = divide(z, y);
    void* ptr = &temp;

    printAnswer(*(static_cast<int*>(ptr)), x, multiply);

    return 0;
}