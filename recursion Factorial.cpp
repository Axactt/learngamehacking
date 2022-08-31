#include<iostream>

int factorial( int num )
{
	if (num == 1)
		return num; // base case(terminatiion condition)
	else if (num > 1) // recursion termination condition
		return num *= factorial( num - 1 ); // recursive function code to multiply number 'num' with function argument 'num-1'
}

int main()
{
	std::cout << factorial( 7 ) << ' ';
}