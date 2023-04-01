#include<iostream>
#include<string>


int main()
{
	//operator+=() and append() function
	std::string sString{ "one" };
	sString += std::string{ " two" };
	std::string sThree{ " three " };
	sString.append( sThree );

	// appending a substring
	//string& string::append(const string& str,size_type index, size_type num)
	//Returns *this so it can be "chained"
	//Throws and out_of_range if index is out of bounds
	// Throws a length_error_exception if the result exceeds the max number of characters
	const std::string sTemp{ "twothreefour" };
	sString.append( sTemp, 3, 5 );//append substring of sTemp starting at index 3 of length 5
	std::cout << sString << '\n';

	// string& string::opeartor+=(const char* str)
	//string& string::append(const char* str)

	std::string sString1{ "one" };

	sString1 += " two";
	sString1.append( " three" );
	std::cout << sString1 << '\n'; 

	// appending first len characters of str to the string
	//Returns *this so they can be chained,a length_error exception if result exceeds max  no. of characters
	//Ignores special characters including ", use dangerous not recommended

	std::string sString2{ "one " };
	sString.append( "threefour", 5 );
	std::cout << sString << '\n';

	// Name of the non-operator function to append a character is push_back() not append()
	//string& string::operator+=(char c), returns *this so it can be chained
	//string& string::push_back(char c)
	//throws a length_error_exception if the result exceeds the max number of characters

	std::string sString3{ "one" };
	sString3 += ' ';
	sString3.push_back( '2' );
	std::cout << sString3 << '\n';

	//string& string::append(size_type num,char c)
	// add num occurences of the character c to the string
	//returns *this so it can be "chained".
	//throws a lenth_error exception if the result exceeds max no. of charaters 

	std::string sString4{ "aaa" };
	sString4.append( 4, 'b' );
	std::cout << sString4 << '\n';
	
	//string& string::append(InputIterator start, InputIterator end)
//Appends all char from the range[start,end)(including start upto but not including end)
	//Returns *this so it can be "chained"
	//throws a length_error exception if result exceeds the max number of characters

}