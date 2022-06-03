#include <iostream>

using namespace std;

class Coordinates
{
private:
    int x;
    int y;
public:
    Coordinates(): x(0), y(0) {}
    Coordinates(int X, int Y): x(X), y(Y) {};
    void print()
    {
        cout << "(" << x << "," << y << ")\n";
    }

    Coordinates operator+(Coordinates& operand)
    {
        Coordinates result;
        result.x = this->x + operand.x;
        result.y = this->y + operand.y;
        return result;
    }

    friend ostream& operator<<(ostream& oss, const Coordinates& operand);
};

ostream& operator<<(ostream& oss, const Coordinates& operand)
{
    oss << "(" << operand.x << "," << operand.y << ")";
    return oss;
}

int main()
{
    Coordinates point_A(2,3);
    point_A.print();

    Coordinates point_B(5,1);
    point_B.print();

    Coordinates point_C;
    point_C = point_A + point_B;
    point_C.print();
    cout << "Printing coordinates: " << point_C << endl;

    return 0;
}