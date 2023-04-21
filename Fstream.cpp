#include<fstream>
#include<iostream>
#include<string>

int main()
{
	//!Note we have to specify both in and out because we're using fstream
	std::fstream iofile{ "Sample.txt",std::ios::in | std::ios::out };

	//if we could not open iofile, print an error
	if (!iofile)
	{
		//Print an error and exit'
		std::cerr << "Sample.txt could not be opened!\n";
		return 1;
	}

	char chChar{}; // we re goig to do this character by character
	
	//While there's still data to choose
	while (iofile.get( chChar )) // get() function to find if still data to process
	{
		switch (chChar)
		{
			//If we find a vowel
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
			case 'A':
			case 'E':
			case 'I':
			case 'O':
			case 'U':

			//BAck up one character
			iofile.seekg( -1, std::ios::cur );

			//!because we did a seek after reading, we can now safely do a write, so
			//lets write a # over the vowel
			iofile << '#';
			
			//!Now we want to go back to read mode so the next call
			//to get() will perform correctly, we'll seekg() to the current
			//location because we dont want to move the file pointer
			iofile.seekg( iofile.tellg(), std::ios::beg );

			break;
		}
	}
	return 0;
}
