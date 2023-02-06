#include<cstddef> // for std::size_t
#include<exception>// for std::exception
#include<iostream>
#include<limits>
#include<string> // for this example

int main()
{
	try
	{
		// Your code using standard library goes here
	   // We'll trigger one of these exceptions intentionally for the sake of the example
		std::string s;
		//will trigger std::length error or allocation exception
		s.resize( std::numeric_limits<std::size_t>::max() );
	}
	//this handler will catch std::exception and all the derived exceptions too
	catch (const std::exception& exception)
	{
		//what() method gives the name of exception
		std::cerr << "Standard exception: " << exception.what() << '\n';
	}
	return 0;
	//
}
