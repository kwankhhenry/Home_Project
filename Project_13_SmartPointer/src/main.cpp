#include <iostream>
#include <memory>  // for std::unique_ptr
#include <utility> // for std::move

#include "SmartPtr.h"
#include "Resource.h"

int main()
{
	smart_ptr<Resource> res1{ new Resource{} }; // Resource created here
	smart_ptr<Resource> res2{ }; // Start as nullptr
	//smart_ptr<Resource> res2{ res1 }; // l-value copy constructor
	//smart_ptr<Resource> res2{ smart_ptr<Resource>{ new Resource{} }}; // provide r-value to copy constructor, uniform initializer
	//smart_ptr<Resource> res2{ smart_ptr<Resource>( new Resource )}; // provide r-value to copy constructor, initializer

	std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
	std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");

	//res2 = res1; // l-value. Won't compile: if copy assignment is disabled
	res2 = std::move(res1); // res2 assumes ownership, res1 is set to null, convert res1 l-value to r-value
	//res2 = smart_ptr<Resource>{ new Resource{} }; // provide r-value to move assignment

	std::cout << "Ownership transferred\n";

	std::cout << "res1 is " << (res1 ? "not null\n" : "null\n");
	std::cout << "res2 is " << (res2 ? "not null\n" : "null\n");
	
	return 0;
} // Resource destroyed here when res2 goes out of scope