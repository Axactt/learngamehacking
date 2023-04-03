#include<iostream>
#include<iomanip>
#include<string>


int main()
{
	/*
	char buff[10];
	std::cin >> std::setw( 10 ) >> buff; // setw(n) manipulator in <iomanip> to extract n-1 character and one newline from input stream/remaining left for next extraction

	//>> extraction operator ignores whitespaces(blanks,tabs and newlines)
	char ch;
	while (std::cin >> ch)
		std::cout << ch;

	char strBuff[11];
	std::cin.get( strBuff, 11 ); // string version of .get()takes max number of characters to read
	std::cout << strBuff << '\n';

	//.get() does not read a newline'\n' character, .getline() reads a '\n' newline charater
	char strBuff1[11];
	//Read upto 10 characters
	std::cin.getline( strBuff1, 11 );
	std::cout << strBuff << '\n';  */
	/*
	char strBuff[100];
	std::cin.getline( strBuff, 100 );
	std::cout << strBuff << '\n';
	std::cout << std::cin.gcount() << " characters were read" << '\n'; // gives number of character read by getline() func  */

	std::string strBuff;
	std::getline( std::cin, strBuff ); // included in string header
	std::cout << strBuff << '\n';

	return 0;

}

