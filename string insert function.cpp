#include<iostream>
#include<string>
//std::string inserting
int main()
{
	//string& string::insert(size_type index,const string& str)
	//string& string::insert(size_type index,const char* str)
	// insert the chaarcters of str into the string at index
	//returns *this so it can be chained, throw out_of_range if index is invalid
	//throw a length_error exception if result exceeds the max number of characters
	
	std::string sString{ "aaaa" };
	std::cout << sString << '\n';
	sString.insert( 2, std::string{ "bbbb" } );
	std::cout << sString << '\n';
	sString.insert( 4, "cccc" );
	std::cout << sString << '\n';

	//inserting a substring into a string at an arbitrary index
//string& string::insert(size_type index,const string& str,size_type startindex,size_type num)
//returns *this so it can be chained, throws out_of_range if index/startindex out of bounds
	std::string sString1{ "aaaa" };
	const std::string sInsert{ "01234567" };
	sString1.insert( 2, sInsert, 3, 4 );//insert substring of sInset from index[3,7) into sTring at index 2
	std::cout << sString1 << '\n';

	//inserting len characters of str into string at index
	//returns *this so it can be "chained"
	//throws an out_of_range exception if index is invalid
	//throws a length_error exception if the result exceeds max number of characters

	std::string sString2{ "aaaa" };
	sString2.insert( 2, "bcdef", 3 );
	std::cout << sString2 << '\n';

	//inserting same charaters for number of instances at a particular index
	//returns *this so it can be "chained"
	//throws an out_of_range exception if index is invalid
	//throws a length_error exception if the result exceeds max number of characters

	std::string sString3{ "aaaa" };
	sString3.insert( 2, 4, 'c' );
	std::cout << sString3 << '\n';

	//insert() function can use iterator 
	//void insert(iterator it,size_type num,char c);inserts num instances of the character c before the iterator it.
	// iterator string::insert(iterator it,char c);inserts a single character c before the iterator it, and returns an iterator to the position of the character inserted.
	//iterator string::insert(iterator it,InputIterator begin,InputIterator end); inserts all characters between [begin,end) before the iterator it.

}