#include <iostream>
#include <string>

	int get_age(const std::string & she_said)
	{

		std::string intPortion{ she_said.substr(0,1) };
		int ageInInteger{ stoi(intPortion,nullptr,10) };
		return ageInInteger;


	}
