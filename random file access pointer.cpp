#include<fstream>
#include<iostream>
#include<string>

int main()
{
	std::ifstream inf{ "Sample.txt" };
	//If we  couldn,t open file for reading
	if (!inf)
	{
		//Print an error and exit'
		std::cerr << "Uh oh, Sample.txt could not be opened for reading!\n";
		return 1;
	}

	std::string strData;

	inf.seekg( 5 ); //move to 5th character from beginning as 
	//Get the rest of the line and print it,moving to line 2
	std::getline( inf, strData );
	std::cout << strData << '\n';

	inf.seekg( 8, std::ios::cur ); //move 8 more bytes into file
	//get the rest of line and print it
	std::getline( inf, strData );
	std::cout << strData << '\n';

	inf.seekg( -14, std::ios::end );//move 14 bytes before end of file
	//get the rest of line and print it
	std::getline( inf, strData );
	std::cout << strData << '\n';

	inf.seekg( 0, std::ios::end ); // move to end of file

	//! return absolute positon of file pointer
	std::cout << inf.tellg();

	//!to get current postion of file pointer using fstream class 
	//! While changing between simultaneous read and write operation
	//? iofile.seekg(0,std::ios::cur) may be used but may be optimized aawy by compiler

	std::fstream iofile; // and object of type fstream

	iofile.seekg( iofile.tellg(), std::ios::beg ); // seek to current file position
	return 0;

}