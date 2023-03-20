#include<iostream>
#include<memory>

class Resource
{
public:
	Resource()
	{
		std::cerr << "Resource acquired\n";
	}
	~Resource()
	{
		std::cerr << "Resource destroyed\n";
	}
};
// Returns a std::weak_ptr to an invalid object
std::weak_ptr <Resource> getWeakPtr()
{
	auto ptr{ std::make_shared<Resource>() };
	return std::weak_ptr{ ptr }; // create a weak pointer directly from constructor
} // ptr goes out of scope, resource destroyed
//Returns a dumb pointer to an invalid object
Resource* getDumbPtr()
{
	auto ptr{ std::make_unique<Resource>() };
	return ptr.get();
}  // ptr goes out of scope., resource destroyed

int main()
{
	auto dumb{ getDumbPtr() };
	std::cout << " Our dumb ptr is: " << ((dumb == nullptr) ? "nullptr\n" : "non-null\n");
	auto weak{ getWeakPtr() };
	std::cout << "our weak ptr is: " << ((weak.expired()) ? "expired\n" : "valid\n");

	return 0;  
}