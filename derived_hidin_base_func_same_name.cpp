#include<iostream>
class Base
{
public:
	int fun()
	{
		std::cout << "Base::fun() called";
	}
	int fun(int i)
	{
		std::cout << "Base::fun(int i) called";
	}
};
class Derived :public Base
{
public:
	int fun()
	{
		std::cout << "Derived::fun() called";
	}
};
int main()
{
	Derived d;
	d.fun(5);
	return 0;

}