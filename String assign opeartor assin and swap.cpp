#include<iostream>
#include<string>
//string& string::operator=(const string& str)
//string& string::assign(const string& str)
//string& string::operator=(const char* str)
//string& string::assign(const char* str)
//string& string::operator=(char c)
// no assign function that takess a signle char
int main()
{
	std::string sString;

   // assign a string value
	sString = std::string( "One" );
	std::cout << sString << '\n';

	const std::string sTwo( "Two" );
	sString.assign( sTwo );
	std::cout << sString << '\n';

	//assign a C-style string
	sString = "Three";
	std::cout << sString << '\n';

	sString.assign( "Four" );
	std::cout << sString << '\n';

	// assign a char using operator=();no assign function that takess a signle char
	sString = '5';
	std::cout << sString << '\n';

	//Chain assignement
	std::string sOther;
	sString = sOther = "Six";
	std::cout << sString << ' ' << sOther << '\n';

	//string& string::assign(const string& str,size_type index,size_type len)
	//assign a substring of str, starting frm index, and of length len
	//Throws an out_of_range exception if index is out of bounds
	//returns *this so it can be chained

	const std::string sSource( "abcdefg" );
	std::string sDest;
	//assign a substring of source from index 2 of length 4
	sDest.assign( sSource, 2, 4 );
	std::cout << sDest << '\n';

	//assign len characters from c-style array chars
	//return this so it can be chained
	std::string sDest1;
	sDest1.assign( "abcdefg", 4 );
	std::cout << sDest1 << '\n';
	

	// string& string::assign(size_type len, char c)
	//Assign len occurences of the character c, returns *this for chaining
	std::string sDest2;
	sDest2.assign( 4, 'g' );
	std::cout << sDest2 << '\n';

	//void string::swap(string& str)
	//void swap(string& str1,string& str2)

	std::string sStr3( "red" );
	std::string sStr4( "blue" );
	std::cout << sStr3 << ' ' << sStr4 << '\n';
	swap( sStr3, sStr4 ); // swap function swaps strings
	std::cout << sStr3 << ' ' << sStr4 << '\n';
	sStr3.swap( sStr4 );
	std::cout << sStr3 << ' ' << sStr4 << '\n';
	return 0;
}