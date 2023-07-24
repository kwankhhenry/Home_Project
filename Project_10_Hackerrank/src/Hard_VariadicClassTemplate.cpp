#include <iostream>
#include <string>

using namespace std;

// Define helper function
template<size_t idx, typename T>
struct GetHelper {};

template <typename... T>  // General empty definition
struct Tuple {};
		
template<typename T, typename... Rest>    // Template parameter pack
struct Tuple<T, Rest...> // Class parameter pack
{      
	T first;
	Tuple<Rest...> rest;        // Parameter pack expansion
			
	Tuple(const T& f, const Rest& ... r): first(f), rest(r...) {}  // constructor with initializer list
    
    template<size_t idx>
    auto get()
    {
        return GetHelper<idx, Tuple<T, Rest...>>::get(*this);
    }
};

template<typename T, typename ... Rest>
struct GetHelper<0, Tuple<T, Rest ...>>
{
    static T get(Tuple<T, Rest...>& data)
    {
        return data.first;
    }
};

template<size_t idx, typename T, typename ... Rest>
struct GetHelper<idx, Tuple<T, Rest ...>>
{
    static auto get(Tuple<T, Rest...>& data)
    {
        return GetHelper<idx-1, Tuple<Rest ...>>::get(data.rest);
    }
};

int main()
{
    Tuple<int, float, std::string> data(1, 2.1, "Hello");
        
    std::cout << data.get<0>() << std::endl;
    std::cout << data.get<1>() << std::endl;
    std::cout << data.get<2>() << std::endl;
    
    //Tuple<bool> t1(false);                 // Case 1
    //Tuple<int, char, std::string> t2(1, 'a', "ABC");   // Case 2

    //cout << t2.get<3>() << endl;
    //cout << t2.first << endl;
    //cout << t2.rest.first << endl;
    //cout << t2.rest.rest.first << endl;
    return 0;
}