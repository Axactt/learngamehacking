#include<iostream>
#include<string>

int main()
{

	std::string sSource{ "abcdefg" };
	std::cout << sSource[5] << '\n';
	sSource[5] = 'X';
	std::cout << sSource << '\n';

	std::cout << sSource.at( 5 ) << '\n';
	sSource.at( 5 ) = 'f';
	std::cout << sSource << '\n';
	
	//conversion to C-style with null termintor appended
	std::cout << std::strlen( sSource.c_str() );

	//memcmp comapares the first n character of two C-style strings and returns 0 if equal
	const char* szString{ "abcdefg" };
	if (std::memcmp( sSource.data(), szString, sSource.length() ) == 0)
		std::cout << "\nThe strings are equal\n";
	else
		std::cout << "\nThe strings are not equal\n";
	//size_type string::copy(char* szBuff, size_type nLength,size_type nIndex=0)const
	// Copy at most nLength characters of string to szBuff,beginning with chararceter nIndex
	//no. of characters copied is returned,no null is appended
	//upto caller to ensure copied char is initialized to NULL or terminate the string using returned length
	std::string sSource1{ "sphinx of black quartz, judge my vow" };
	char szBuff[20];
	int nLength{ static_cast<int>(sSource1.copy( szBuff,5,10 )) };
	szBuff[nLength] = '\0'; //make sure we terminate the string in the buffer

	std::cout << szBuff << '\n';

}