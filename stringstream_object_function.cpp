#include<iostream>
#include<sstream>
#include<string>

int main()
{
	std::stringstream os1;
	os1 << "en garde\n"; //insert "en garde" into the stringstream using insertion opeartor

	std::stringstream os2;
	os2.str( "en garde!" );// use the str(string) function to set the value of buffer

	//To get data out of a stringstream
	std::stringstream os;
	os << "12345 67.89\n";
	std::cout << os.str(); // use .str() to retrieve results of the buffer

	//use the extraction opeartor
	std::stringstream os3;
	os3 << "12345 67.89";

	std::string strValue;
	os3 >> strValue;

	std::string strValue2;
	os3 >> strValue2;

	//print the numbers separated by dash
	std::cout << strValue << " - " << strValue2 << '\n';

	//extraction and insertion operator know how to work with all builtin types
	//used to convert strings to number and vice-versa
	std::stringstream os4;
	int nValue{ 12345 };
	double dValue{ 67.89 };
	os << nValue << ' ' << dValue;

	std::string strValue1, strValue3;
	os >> strValue1 >> strValue3;

	std::cout << strValue1 << ' ' << strValue2 << '\n';

	//convert a numerical string to a number
	std::stringstream os6;
	os6 << "12345 67.89"; //insert a string of numbers into the stream
	int nValue1;
	double dValue1;

	os6 >> nValue1 >> dValue1;
	std::cout << nValue1 << ' ' << dValue1 << '\n';

	//Emptying the string buffer by using str() function
	//1) setting it to empty blank c-style string
	std::stringstream os7; // stringstream object to hold buffer defined
	os7 << "Hello ";
	os7.str( "" );//erase the buffer

	os7 << "World!";
	std::cout << os7.str();

	//2) setting the buffer(through stringstream defined object identfier)to empty std::string
	std::stringstream os8;
	os8 << "Hello ";
	os8.str( std::string{} ); // erase the buffer

	os8 << "World!";
	std::cout << os8.str();

	os8.str( "" );// erase the buffer
	os8.clear(); // use of clear tyo reset various error flags
//clear() resets any error flag that may have been set and returns the steam back to ok state
	os8 << "Hello ";
	std::cout << os8.str();
}