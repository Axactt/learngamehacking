#include<algorithm>//std::all_of
#include<cctype>//std::isalpha.std::isspace
#include<iostream>
#include<ranges>
#include<string>
#include<string_view>


bool isValidName( std::string_view name )
{

	return std::ranges::all_of( name, []( char ch )
								{
									return (std::isalpha( ch ) || std::isspace( ch ));
								} );
	//Before c++20 withot ranges
	//return std::all_of(name.begin(),name.end(),[]char(ch){return(std::isalpha(ch)||std::isspace(ch));});
}

int main()
{
	std::string name{};
	do
	{
		std::cout << "enter your name: ";
		std::getline( std::cin, name );// get the entire line,including spaces newline character
	} while (!isValidName( name ));
	std::cout << "Hello " << name << '!n';
	return 0;
}