#include <iostream>
#include <vector>

using namespace std;

/* Question: There is a line chart consisting of N points (numbered from 0 to N-1) connected by line segments.  
The K-th point has coordinates x=K, y=Y[K].  There are no horizontal lines; that is, no two consecutive points has the same
y-coordinates.

We can draw an infinitely long horizontal line.  What is the maximum number of points of intersection of the line with the chart?
Write a function
    int solution(vector<int> &Y);

that, given array Y, returns the maximum number of common points between the horizontal line and our line chart if we draw 
the line optimally.

Example Y = [1,2,1,2,1,3,2], the function should return 5.  A horizontal line at y=1.5 intersects the chart at point
(0.5,1.5),(1.5,1.5),(2.5,1.5),(3.5,1.5), and (4.25,1.5).*/

int calculate(vector<int> &A)
{
    
}

int main()
{
    vector<int> vec = {1,2,1,2,1,3,2};
    int result = calculate(vec);
    cout << result << endl;

    return 0;
}