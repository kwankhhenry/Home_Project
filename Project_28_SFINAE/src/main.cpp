#include <iostream>
#include "icecream.hpp"

// SFINAE: Substitution Failure Is Not An Error with enable_if
template<typename T>
using isIntegral = typename std::enable_if<std::is_integral<T>::value, T>::type;

template<typename T>
using isNotIntegral = std::enable_if_t<!std::is_integral<T>::value, T>;

template <typename T, typename = isIntegral<T>>
isIntegral<T> add(T a, T b) {
    std::cout << "int calls" << std::endl;
    return a + b;
}

template <typename T, typename = isNotIntegral<T>>
T add(T a, T b, isNotIntegral<T> = 0) {
    std::cout << "float calls" << std::endl;
    return a + b;
}

// Tag Dispatching
template<typename T>
T cat_impl(T a, std::true_type) {
    std::cout << "cat is arithmetic" << std::endl;
    return a;
}

template<typename T>
T cat_impl(T a, std::false_type) {
    std::cout << "cat is not arithmetic " << std::endl;
    return a;
}

template<typename T>
T cat(T a) {
    return cat_impl(a, std::is_arithmetic<T>());
}

// if constexpr (Compile-time if)
template<typename T>
T bar(T a) {
    if constexpr (std::is_arithmetic_v<T>) {
        std::cout << "bar is arithmetic" << std::endl;
    } else {
        std::cout << "bar is not arithmetic" << std::endl;
    }
    return a;
}

// Concept C++20
template<typename T>
concept Arithmetic = requires(){ std::is_arithmetic_v<T>; };

template<typename T>  // Specialized for arithmetic types
requires Arithmetic<T>
T foo(T a) {
    std::cout << "foo is arithmetic" << std::endl;
    return a;
}

template<typename T>    // Generalized for non-arithmetic types
T foo(T a) {
    std::cout << "foo is not arithmetic " << std::endl;
    return a;
}

int main() { 
    IC(add(1, 2));
    IC(add(3.0f, 4.5f));
    std::cout << "\n";
    IC(bar(2));
    IC(bar("yoyo"));
    std::cout << "\n";
    IC(foo(1));
    IC(foo("hello"));
    std::cout << "\n";
    IC(cat(2));
    IC(cat("television"));

    return 0;
}