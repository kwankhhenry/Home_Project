#include <iostream>

using namespace std;

class Point
{
    private:
        int* X;
        int* Y;

    public:    
        Point(): X(0), Y(0) 
        {
            X = new int;
            Y = new int;

            *X = 0;
            *Y = 0;

            cout << "Point is Construct and initialized to (0,0)!" << endl;
        }

        Point(int x, int y){
            X = new int;
            Y = new int;

            *X = x;
            *Y = y;

            cout << "Point (" << *X << "," << *Y << ") is Construct at address " << X << " and " << Y << "!" << endl;
        }

        Point(const Point& other){
            X = new int;
            Y = new int;

            *X = *other.X+10;
            *Y = *other.Y+10;

            cout << "Point Deep Copy on (" << *other.X << "," << *other.Y << ") at address " << X << " and " << Y << "!" << endl;      
        }

        Point(Point&& other) noexcept{
            X = other.X;
            Y = other.Y;

            other.X = NULL;
            other.Y = NULL;

            cout << "Point Moved (" << *X << "," << *Y << ") at address " << X << " and " << Y << "!" << endl;
        }

        ~Point(){
            if (X == nullptr && Y==nullptr)
                cout << "Empty pointer destruct!" << endl;
            else
                cout << "Point (" << *X << "," << *Y << ") Destruct!" << endl;

            delete X;
            delete Y;
        }

        Point& operator=(const Point& other)
        {
            if(this == &other) return *this;

            *X = *other.X;
            *Y = *other.Y;

            cout << "Operator = invoke to assign (" << *other.X << "," << *other.Y << ")" << endl;
            return *this;
        }

        Point& operator=(Point&& other) noexcept
        {
            if(this == &other) return *this;

            X = other.X;
            Y = other.Y;

            other.X = nullptr;
            other.Y = nullptr;

            cout << "Operator = moved (" << *X << "," << *Y << ")" << endl;
            return *this;
        }

        Point CreatePoint(int x, int y)
        {
            return Point(x, y);
        }

        void SetPoint(int x, int y)
        {
            *X = x;
            *Y = y;
        }

        void PrintPointString(char name)
        {
            cout << "Point_" << name << " is: (" << *X << "," << *Y << ") at address " << X << " and " << Y << "!" << endl;
            cout << "----------------------------------------------------" << endl;
        }
    
        void PrintPoint()
        {
            cout << "(" << *X << "," << *Y << ")";
        }

        friend ostream& operator<< (ostream& oss, const Point& rhs)
        {
            oss << "(" << *rhs.X << "," << *rhs.Y << ")";
            return oss;
        }
};

class Shape
{
private:
    int mVertex;
    Point* pointPtr;
public:
    Shape(): mVertex(0), pointPtr(nullptr){}

    Shape(int vertex, Point Array[]): mVertex(vertex){
        cout << "Shape Create!" << endl;
        pointPtr = Array;
    }

    /*Shape(Point&& p): point((Point &&)p){
        cout << "Shape Moved!" << endl;
    }*/

    ~Shape(){
        cout << "Shape Destruct!" << endl;
    }

    friend ostream& operator<<(ostream& oss, const Shape& s)
    {
        oss << "Shape has " << s.mVertex << " vertices. ";
        
        if(s.mVertex > 0)
        {
            oss << "With points: ";
            for(int i = 0; i < s.mVertex; i++)
            {
                s.pointPtr[i].PrintPoint();
            }
        }
        return oss;
    };
};

int main()
{
    {
    Point Point_A(2,3);         // Constructor
    Point_A.PrintPointString('A');
    Point Point_B = {6,1};      // Constructor
    Point_B.PrintPointString('B');

    Point Point_C = Point_A;    // Deep Copy Constructor (l-value)
    Point_C.PrintPointString('C');

    Point Point_D(Point_B);     // Deep Copy Constructor (l-value)
    Point_D.PrintPointString('D');

    // Only the default constructor will be called, because the move
    // constructor will be elided (Copy elision).  
    // Compile with -fno-elide-constructors to see the move constructor called.
    Point Point_E = Point(9,9); // Move Copy Constructor semantics (r-value)
    Point_E.PrintPointString('E');

    Point Point_F(Point(1,1));  // Move Copy Constructor semantics (r-value)
    Point_F.PrintPointString('F');

    Point Point_G(9,2);         // Constructor
    Point Point_H;              // Constructor
    Point_H = Point_G;          // Assignment = operator (l-value)
    Point_H.PrintPointString('H');

    Point Point_I;              // Constructor
    Point_I = Point(10,3);      // Move Assignment = operator (r-value)
    Point_I.PrintPointString('I');
    }
    cout << "------------------------------------------------------\n";

    {
    Point PointArr[4];
    for(int i = 0; i < 4; i++)
    {
        //cout << "PointArray at: " << &PointArr[i] << endl;
        PointArr[i] = Point(i+1,i+1);
    }

    Shape Square(4, PointArr);
    cout << Square << endl;
    }
    cout << "------------------------------------------------------\n";
    {
    Point Point_Triangle[1] = {std::move(Point(5,5))};
    Shape Triangle(1, Point_Triangle);
    cout << Triangle << endl;
    }
    cout << "------------------------------------------------------\n";
    
    return 0;
}
