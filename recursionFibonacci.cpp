#include<iostream>

int fibonacci( int count )
{
	if (count == 0 || count==1)
		return count; // base case( termination condition)
	else
		return fibonacci( count - 1 ) + fibonacci( count - 2 ); // recursive function call for fibonacci sequence
}
// And a main program to display the first 13 Fibonacci numbers
int main()
{
	for (int count { 0 }; count < 13; ++count)
		std::cout << fibonacci( count ) << ' ';

	return 0;
}