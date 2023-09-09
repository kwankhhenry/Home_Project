#include "SmartPtr.h"
#include "Resource.h"

// ** Need to explicitly tell definition cpp file the template type, unless we move all below definition to header file.
// ** Recommend moving definition to header file.
// https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
template class smart_ptr<Resource>;

// Constructor
template<typename T> smart_ptr<T>::smart_ptr(T* ptr)
		:m_ptr(ptr)
{
	std::cout << "Constructor invoked." << std::endl;
}

// Destructor
template<typename T> smart_ptr<T>::~smart_ptr()
{
	delete m_ptr;
}

// l-value copy constructor (Deep copy)
template<typename T> smart_ptr<T>::smart_ptr(const smart_ptr& obj)
{
    m_ptr = new T;
    *m_ptr = *obj.m_ptr;
    std::cout << "Copy constructor invoked." << std::endl;
}

// l-value Assignment operator= overload (Deep copy)
template<typename T> smart_ptr<T>& smart_ptr<T>::operator=(const smart_ptr& obj)
{
    // Self assignment handling
    if(this == &obj) return *this;

    // Clear existing content in this object
    delete m_ptr;

    // Assignment
    m_ptr = new T;
    *m_ptr = *obj.m_ptr;
    std::cout << "Asssignment= invoked." << std::endl;

    return *this;
}

// r-value Copy constructor
template<typename T> smart_ptr<T>::smart_ptr(smart_ptr&& obj)
{
    m_ptr = obj.m_ptr;
    obj.m_ptr = nullptr;
    std::cout << "Move Copy constructor invoked." << std::endl;
}

// r-value assignment= operator overload
template<typename T> smart_ptr<T>& smart_ptr<T>::operator=(smart_ptr&& obj)
{
    // Self assignment handling
    if(this == &obj) return *this;

    // Clear existing content in this object
    delete m_ptr;

    // Assignment
    m_ptr = obj.m_ptr;
    obj.m_ptr = nullptr;
    std::cout << "Move Asssignment= invoked." << std::endl;

    return *this;
}