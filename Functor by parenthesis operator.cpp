// Parenthesis opeartor for implementation of functors()
// Functors are classses that operate like functions to carry specific jobs

#include<iostream>
class Accumulator
{
private:
	int m_counter { 0 };
public:
	int operator()( int i )
	{
		return m_counter += i;
	}
};

int main()
{
	//Overloaded parenthesis operator() as functors (or function object)
	// These functors are classes that work as functions .
	// the advantage of a functor overa a normal function is  that // functors can store data in member variables(since they are classes)
	Accumulator acc {};
	// using accumulator looks just like normal function call, but our accumulator object is storing an accumulated value
	// Same can be done using static variables and normal global function calls BUT as normal functions only have one global instance, 
	// we'd be limited to using it //for one thing at a time. 
	//with functors we can instantiate as many separate functor objects we need and use them all simultaneously

	std::cout << acc( 10 ) << '\n';
	std::cout << acc( 20 ) << '\n';
	return 0;


}