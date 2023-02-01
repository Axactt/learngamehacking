#include<iostream>

class Base
{
public:
	virtual Base* clone() const
	{
		return new Base( *this );
	}
};

class Derived : public Base
{
public:
	virtual Derived* clone() const
	{
		return new Derived( *this );
	}
};

int main()
{
	Derived d;
	Base* b = &d;
	Derived* d2 = dynamic_cast<Derived*>(b->clone()); // To check if cast is valid 
	if (d2)
	{
		std::cout << "Cast is valid, use 'd2' as a pointer to 'Derived'" << '\n';
	}
	else
	{
		std::cout << "// Cast is invalid" << '\n';
	}
	return 0;
}