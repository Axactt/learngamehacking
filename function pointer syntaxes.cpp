#include <iostream>


int foo(int x)
{
	return x;
}
int goo(int x)
{
	return x;
 }


int main()
{
	int (*fcnPtr)(int) // fcnPtr a pointer to function of return type int initialized with function foo's address
	{
		&foo
	};
	if(fcnPtr) // conditionally testing if fcnPtr is a nullPtr before dereferncing it, otherwise undefined behaviour
	std::cout << (*fcnPtr)(5); // function foo() called through explicit dereference of fcnPtr using (*fcnPtr) i.e. dereference operator(*)

	fcnPtr = &goo; // fcnPtr now asigned the address of function goo which is haveing same return type and type of parameters

	std::cout << fcnPtr( 6 ); // function goo called through implicit dereference of fcnPtr without using (*) derefernce operator
	return 0;
}