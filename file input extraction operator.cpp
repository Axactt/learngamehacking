#include<fstream>
#include<iostream>
#include <string>

int main()
{
	
	//!ifstream is used for reading from file buffer
		// reading from a file called Sample.txt
	std::ifstream inf{ "Sample.txt" };

	//If we couldn,t open the output file stream for reading
	if (!inf)
	{
		//Print an error and exit
		std::cerr << "Sample.txt cannot be opened for writing to some string buffer.\n";
		return 1;
	}

	/*
	
	//? ifstream return 0 if we've reached the End of file 
	//!use this to determine how much to read
	//While there's still stuff left to read
	while (inf)
	{
		//!read stuff from the file into a string and print it
		std::string strInput;
		//!use extraction opeartor to extract info from file buffer
		//! extraction opeartor will break on white spaces
		inf >> strInput;
		std::cout << strInput << '\n';

	}*/
	while (inf)
	{
		std::string strInput;
		std::getline( inf, strInput ); //!std::getline so that breaking on white space does not occur
		std::cout << strInput << '\n';
	 }

	return 0;
	//When inf goes out of scope, 
	//the ifstream destructor will close the file
}