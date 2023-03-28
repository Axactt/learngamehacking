#include<iostream>
#include<string>
#include<sstream>
#include<ctime>
#include<random>
/*
namespace std 
{
	template<class charT,class traits = char_traits<charT>,class Allocator=allocator<charT>>
	class basic_string;
}

namespace std
{
	typedef basic_string<char>string; // standard ascii and utf-8 strings
	typedef basic_string<wchar_t>wstring; // wide character/unicode(utf-16) strings
}  */
template<typename T>
 std::string ToString(  T& tX )
{
	std::ostringstream oStream;
	oStream << tX;
	return oStream.str();
}
int main()
{
	std::string sSource{ "my string" };
	//string::string(const string& strString,size_type unIndex,size_type unLength)
	std::string sOutput{ sSource,3 };
	std::cout << sOutput << '\n';

	std::string sOutput2( sSource, 3, 4 );
	std::cout << sOutput2 << '\n';

	//string::string(const char* szCString,size_type unLength)
	const char* szSource{ "my string" };
	std::string sOutput3{ szSource,4 };
	std::cout << sOutput3 << '\n';

	//string::string(size_type nNum, char chChar)
	std::string sOutput4( 4, 'X' );
	std::cout << sOutput4 << '\n';

	//empty() function
	std::string string1{ "Not empty" };
	std::cout << (string1.empty() ? "true" : "false") << '\n';
	std::string string2; //empty
	std::cout << (string2.empty() ? "true" : "false");

	//max_size(),length() and capacity()
	std::string s{ "MyString" }; 
	std::cout <<'\n'<< s.max_size()<<'\n';
	std::cout << "Length: " << s.length() << '\n';
	std::cout << "Capacity: " << s.capacity() << '\n';

	std::string s1{ "0123456789abcde" };
	std::cout << "Length: " << s1.length() << '\n';
	std::cout << "capacity: " << s1.capacity() << '\n';
	//if one more caharacter added capacity reallocated
	s1 += "f";
	std::cout << "Length: " << s1.length() << '\n';
	std::cout << "Capacity: " << s1.capacity() << '\n';

	// size_type string::reserve() and string::reserve(size_type unSize)
	std::srand( std::time( nullptr ) ); // sed random number generator
	std::string s3{}; // length 0
	s3.reserve( 64 ); // reserve 64 characters

	//fill string up with random lower case characters
	for (int count{ 0 }; count < 64; ++count)
		s3 += 'a' + std::rand() % 26;
	std::cout << s3;

	return 0;

}