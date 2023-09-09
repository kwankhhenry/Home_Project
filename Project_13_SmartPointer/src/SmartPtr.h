#ifndef SMARTPTR_H
#define SMARTPTR_H

#include <iostream>

template<typename T>
class smart_ptr
{
private:
    T* m_ptr;

public:
	smart_ptr(T* ptr  = nullptr);                     // Constructor
    /*		:m_ptr(ptr)
    {
	    std::cout << "Constructor invoked." << std::endl;
    }*/

	~smart_ptr();                                     // Destructor
    /*{
	    delete m_ptr;
    }*/

    smart_ptr(const smart_ptr& obj);                  // l-value Copy constructor
    /*{
        m_ptr = new T;
        *m_ptr = *obj.m_ptr;
        std::cout << "Copy constructor invoked." << std::endl;
    }*/

    smart_ptr& operator=(const smart_ptr& obj);       // l-value assignment= operator overload
    /*{
        // Self assignment handling
        if(this == &obj) return *this;

        // Clear existing content in this object
        delete m_ptr;

        // Assignment
        m_ptr = new T;
        *m_ptr = *obj.m_ptr;
        std::cout << "Asssignment= invoked." << std::endl;

        return *this;
    }*/

    smart_ptr(smart_ptr&& obj);                       // r-value Copy constructor
    /*{
        m_ptr = obj.m_ptr;
        obj.m_ptr = nullptr;
        std::cout << "Move Copy constructor invoked." << std::endl;
    }*/

    smart_ptr& operator=(smart_ptr&& obj);            // r-value assignment= operator overload
    /*{
        // Self assignment handling
        if(this == &obj) return *this;

        // Clear existing content in this object
        delete m_ptr;

        // Assignment
        m_ptr = obj.m_ptr;
        obj.m_ptr = nullptr;
        std::cout << "Move Asssignment= invoked." << std::endl;

        return *this;
    }*/

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
	bool isNull() const { return m_ptr == nullptr; }

    explicit operator bool() const { return m_ptr != nullptr; }
};
#endif