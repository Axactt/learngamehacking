//Numeric validation as string

#include<charconv> //std::from_chars
#include<iostream>
#include<optional> // for maybe values
#include<string>
#include<string_view>

std::optional<int> extractAge( std::string_view age )
{
	int result{};
	//!end iterator is constructed here
	auto end{ age.data() + age.length() };
	//Try to parse an int from age
	//!std::from_chars for conversion of string to integer
	//? why is ().ptr used with !=end
	if (std::from_chars( age.data(), end, result ).ptr != end)
	{
		//? If an int is made why empty return
		return {};
	}
	if (result <= 0) // make sure age is positive
	{
		return {};
	}
	return result;

}

int main()
{
	int age{};
	while (true)
	{
		std::cout << "Enter your age: ";
		std::string strAge{};
		//? what is use of std::ws
		std::getline( std::cin >> std::ws, strAge );
		if (auto extracted{ extractAge( strAge ) })
		{
			age = *extracted;
			break;
		}
	}
	std::cout << "You entered: " << age << '\n';
}