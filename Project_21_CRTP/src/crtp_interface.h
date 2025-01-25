#pragma once

#include <iostream>
#include <stdint.h>

#include "icecream.hpp"

template <typename Derived>
class CRTPInterface
{
public:
    void Count(uint64_t n)
    {
        static_cast<Derived*>(this)->Count(n);
    }

    uint64_t GetValue()
    {
        return static_cast<Derived*>(this)->GetValue();
    }
private:
    CRTPInterface() = default;
    friend Derived;
};

class CRTPImplemented : public CRTPInterface<CRTPImplemented>
{
public:
    CRTPImplemented() : counter(0) {}
    inline void Count(uint64_t n)
    {
        counter += n;
    }

    inline uint64_t GetValue() const
    {
        return counter;
    }
private:
    uint64_t counter;
};

template <typename T>
void RunCRTP(CRTPInterface<T>* obj)
{
    const unsigned N = 40000;
    for(unsigned i = 0; i < N; ++i)
    {
        for(unsigned j = 0; j < i; ++j)
        {
            obj->Count(j);
        }
    }
    IC(obj->GetValue());
    //std::cout << "CRTP value: " << obj->GetValue() << std::endl;
}