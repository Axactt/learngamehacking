#include<algorithm> //std::all_of
#include<cctype> // std::isalpha,std::isspace
#include<iostream>
#include<ranges>
#include<string>
#include<algorithm> // std::equal
#include<cctype>//std::isdigit,std::isspace,std::isalpha
#include<iostream>
#include<map>
#include<ranges>
#include<string>
#include<string_view>

bool inputMatches( std::string_view input, std::string_view pattern )
{
	if (input.length() != pattern.length())
	{
		return false;
	}
//This table defines all special symbols that can match a range of user input
// Each symbol is mapped to a function that determines whether the input is valid for that symbol
	static const std::map<char, int(*)(int)>validators{
		{'#',&std::isdigit},
		{'_',&std::isspace},
		{'@',&std::isalpha},
		{'?',[]( int ){return 1;}}// note lambda expression can be mapped to function pointer
	};
	//Before C+20,use
//return std::equal(input.begin(),input.end(),pattern.begin(),[](char ch,char mask)->bool{
	return std::ranges::equal( input, pattern, []( char ch, char mask )->bool 
	{ //lambda body here
		if (auto found{ validators.find( mask ) }; found != validators.end())
		{
			//The pattern's current element was found in the validators,
			//Call the second memeber of map which is corresponding checking function
			return (*found->second)(ch);
		}
		else
		{
			//The pattern's current element was not found in the validators
			//The characters need to have an exact match
			return (ch == mask);
		}
	});
}

int main()
{
	std::string phoneNumber{};
	do
	{
		std::cout << "Enter a phone numeber(###) ###-####: ";
		std::getline( std::cin, phoneNumber );
	} while (!inputMatches( phoneNumber, "(###)###-####" ));
	std::cout << "You entered: " << phoneNumber << '\n';
}