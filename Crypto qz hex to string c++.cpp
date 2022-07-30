#include<string> // for ".length()" , ".substr()" and ".data()" function
#include<cstring> // for std::strtol function to use a portion of c-style string
#include<iostream>


int main()
{
	// the hexString initialized as std::string type instead of c-style string
	// this is done to make ".substr()" function work to access and utilize a portion of string at a time with for loop
	std::string hexString{"63727970746f7b596f755f77696c6c5f62655f776f726b696e675f776974685f6865785f737472696e67735f615f6c6f747d"};

	//initialising integer using .length() function for hex string length calculation
	int length{ static_cast<int>(hexString.length()) };

	//for loop with iterator increased in block of 2 digits to get portion of hex string and its modification 
	for (int i{ 0 }; i < length; i+=2)
	{
		// .substr function to get a portion of string using iterator 'i' with increments of 2 digits
		std::string stringPortion{ hexString.substr(i,2) }; 

		// to convert stringPortion std::string type to c-style string(char*) type: using .data() function
		// if trying to use c_str() instead of .data() gives an error that a value of type "const char*" cannot be used to initialize an entity of type "char*"
		char* toConvert{ stringPortion.data()};
		 
		// strtol function to convert hex string to integer repesenting char byte code, 
		// Note that base radix 16 has to be used as an argument for proper conevrsion
		int final{static_cast<int> (std::strtol(toConvert,nullptr,16)) };

		// converting char from integer returned after using strtol function for hex string conversion
		char cryptoHavk{ static_cast<int8_t>(final) };
		std::cout << cryptoHavk;
	
	}
	std::cout << '\n';
	return 0;
}