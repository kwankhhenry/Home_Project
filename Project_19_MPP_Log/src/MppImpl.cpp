#include "MppImpl.h"

MppImpl::MppImpl(const char* filename)
{
    p_MppLogObj = new MppLog(filename);
}

MppImpl::~MppImpl()
{
    delete p_MppLogObj;
}

void MppImpl::printSummary()
{
    std::cout << "Printing file summary...\n";
    p_MppLogObj->getSummary();
}