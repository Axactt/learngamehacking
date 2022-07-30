#include<string>
#include<cstdint>
#include<cstring>
#include<iostream>
#include<iterator>




int main()
{
	std::string hexString{"63727970746f7b596f755f77696c6c5f62655f776f726b696e675f776974685f6865785f737472696e67735f615f6c6f747d"};

	int length{ static_cast<int>(hexString.length()) };

	for (int i{ 0 }; i < length; i+=2)
	{
		std::string stringPortion{ hexString.substr(i,2) };
		char* toConvert{ stringPortion.data() };
		int final{static_cast<int> (std::strtol(toConvert,nullptr,10)) };
		char cryptoHavk{ static_cast<int8_t>(final) };
		std::cout << cryptoHavk;
	
	}

	return 0;
}