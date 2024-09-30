#include <iostream>
#include <array>
#include <vector>

using namespace std;

class lifetime
{
public:
    lifetime(){cout << "Ctor called\n";};

    lifetime(const lifetime&){cout << "Copy tor called\n";};
    lifetime(lifetime&&){cout << "Move Ctor called\n";};

    lifetime& operator=(const lifetime&){cout << "Assignment called\n"; return *this;};
    lifetime& operator=(lifetime&&){cout << "Move assignment called\n"; return *this;};
    ~lifetime(){cout << "Dtor called\n";};

    int member_data;
};

/*auto do_lifetime(const int value)
{
    lifetime l;
    l.member_data = value;
    return l;
}*/

int main()
{
    auto make_lifetime = [](const int value)
    {
        lifetime l;
        l.member_data = value;
        return l;
    };

    /*lifetime l1;
    l1.member_data = 42;

    lifetime l2;
    l2.member_data = 42;*/

    //std::array<lifetime,2> a{lifetime(42), lifetime(42)};
    std::array<lifetime,2> a{make_lifetime(42), make_lifetime(42)};
    //std::vector<lifetime> a{std::move(l1),std::move(l2)};
    //std::vector<lifetime> a{make_lifetime(42),make_lifetime(42)};

    /*std::vector<lifetime> a;
    a.push_back(make_lifetime(42));
    a.push_back(make_lifetime(42));*/
    cout << "Array gets destroyed.\n";
    return 0;
}

