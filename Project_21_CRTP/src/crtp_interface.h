#pragma once

#include <iostream>
#include <stdint.h>

#include "icecream.hpp"

template <typename Derived>
class CRTPInterface
{
public:
    constexpr void Count(uint64_t n)
    {
        static_cast<Derived*>(this)->Count(n);
    }

    constexpr uint64_t GetValue()
    {
        return static_cast<Derived*>(this)->GetValue();
    }
private:
    constexpr CRTPInterface() = default;
    friend Derived;
};

class CRTPImplemented : public CRTPInterface<CRTPImplemented>
{
public:
    constexpr CRTPImplemented() : counter(0) {}
    constexpr inline void Count(uint64_t n)
    {
        counter += n;
    }

    constexpr inline uint64_t GetValue()
    {
        return counter;
    }
private:
    uint64_t counter;
};

template <typename T, uint64_t N>
constexpr uint64_t loop(){
    T obj;
    CRTPInterface<T>* objptr = &obj;
    for(uint64_t i = 0; i < N; ++i)
    {
        for(uint64_t j = 0; j < i; ++j)
        {
            objptr->Count(j);
        }
    }
    return objptr->GetValue();
}

template <typename T, uint64_t N>
constexpr void RunCRTP()
{
    constexpr uint64_t result = loop<T,N>();
    IC(result);
    //std::cout << "CRTP value: " << obj->GetValue() << std::endl;
}

