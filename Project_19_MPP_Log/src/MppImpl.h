#pragma once
#include "MppLog.h"

class MppImpl
{
private:
    MppLog* p_MppLogObj;
public:
    MppImpl() = delete;
    MppImpl(const char* filename);
    ~MppImpl();

    void printSummary();
};