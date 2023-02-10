#include<iostream>
class A
{
private:
	int m_x {};
public:
	A( int x )
		:m_x { x }
	{
		if (x <= 0)
			throw 1; // exxception thrown here
	}
};

class B : public A
{
public:
	B( int x ) try:A { x } // note addition of try keyword here
	{
		// what happens if creation of A fails and we want to handle it here?
		if (x <= 0) // moved this from A to B
			throw 1;
	}
	catch (...)//note this is at same level of indentation as function itself
	{
//exceptions from member initializer list or constructor body are caught here
		std::cerr << " Exception caught\n";
		throw;// rethrow the existing exception
//If an exception isn't explicitly thrown here, current excptn will be implicitly rethrown
	}
};
int main()
{
	try
	{
		B b { 0 };
	}
	catch (int)
	{
		std::cout << " Oops\n";
	}
}