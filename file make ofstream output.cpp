#include<fstream> //!to include ofstream and ifstream for writin and reading files
#include<iostream>

int main()
{
	//!ofstream is for writing files
	// we will make a file called sample.txt
	std::ofstream outf{ "Sample.txt" };

	//If we couldn't open the output file stream for writing
	if (!outf)
	{
		//Print an error and exit
		std::cerr << "Sample.txt could not be opened for writing!\n";
		return 1;
	}
	// we'll write two lines into this file
	//!Remember insertion operator to input/insert anything to a buffer
	outf << "This is line 1\n";
	outf << "This is line 2\n";
	return 0;
	//? when outf goes out of scope the , 
	//? the ofstream destructor will close the file
	//? Named file autmatically created in project directory

	
	
}