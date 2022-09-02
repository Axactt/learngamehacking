#include<iostream>
#include<cstdarg> // for using std::va_list and using ellipsis

// the ellipsis must be last parameter
// count is how many additional arguments we are passing

double findAverage( int count, ... ) // three dots to represent ellipsis additional parameters
{
	int sum { 0 };
	// we access elipssis through a va_list so we declare it

	std::va_list list;
	// we initialize the va_list using va_start. the first parameter is
	   // the list to initialize. the second parameter is last non-ellipsis 
	   // parameter 

	va_start( list, count );

	// loop through all the ellipsis arguments
	for (int arg { 0 }; arg < count; ++arg)
	{
		// we use va_arg to get parameters out of our elipssis
		// the first parameter is va_list we are using
		// the second parameter is the type of the parameter
		sum += va_arg( list, int );

	}
	// cleanup the va_list when we're done
	va_end( list );

	return static_cast<double>(sum) / count;
}



int main()
{
	std::cout << findAverage( 5, 1, 2, 3, 4, 5 ) << '\n';
	std::cout << findAverage( 6, 1, 2, 3, 4, 5, 6 ) << '\n';
	return 0;
}