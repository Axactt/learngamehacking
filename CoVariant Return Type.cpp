#include<iostream>
#include<string_view>

class Base
{
public:
	//This version of getThis() returns a pointer to a Base class
	Base()
	{
		std::cout << " Returned a BASE constructor frm this pointer.\n";
	}
	virtual Base* getThis()
	{
		std::cout << " called Base::getThis()\n";
		return this;
	}
	void printType()
	{
		std::cout << " Returned Base print-type\n ";
	}
};

class Derived :public Base
{
public:
	//Normally override functions have to return objects of the same type as the base function
	//However because Derived is derived from Base,it's okay to return Derived* instead of Base*
	Derived()
	{
		std::cout << " Returned a Derived constructor frm this pointer.\n";
	}
	Derived* getThis()override
	{
		std::cout << " called Derived::getThis()\n";
		return this;
	}
	void printType()
	{
		std::cout << "returned a Derived print-type\n";
	}
};

int main()
{
	Derived  d {};
	Base* b { &d };
	d.getThis()->printType();// Calls Derived::getThis(), returns a Derived*, calls Derived::printtype()

	b->getThis()->printType();// Calls Derived::getThis(), returns a Base*, calls Base::printType
	return 0;
}