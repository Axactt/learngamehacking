// Command line argument

#include<iostream>
#include<sstream> // for std::stringstream
#include<string>

int main(int argc,char* argv[])
{
	if (argc <= 1)
	{
		// on some os argv[0] can end up as empty string instead of program's name
		// we'll conditionalize our response on whether argv[0] is empty or not

		if (argv[0])
			std::cout << " Usage: " << argv[0] << " number " << '\n';
		else
			std::cout << " Usage: <program name> <number>" << '\n';

		return 1;

	}

	std::stringstream convert { argv[1] };// set up a stringstream variable convert, initialize with input from argv[1]

	int myInt {};
	if (!(convert >> myInt))// do the conversion, std::stringstream works as std::cin
		myInt = 0; // if conversion fails set myInt to a default value

	std::cout << " Got integer from input: " << myInt << '\n';
	
	return 0;

}