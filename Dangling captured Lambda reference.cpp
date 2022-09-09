#include<algorithm>
#include<iostream>
#include<array>
#include<string>
// returns a lambda
auto makeWalrus(const std::string& name)
{
	// capture name by reference and return the lambda
	return [&]()
	{
		std::cout<<" i am a walrus, my name is "<<name<<'\n';// undefined behaviour
	};
}

int main()
{
	// Create new walrus whose name is rufus
	// sayName is the lambda returned by makeWalrus

	auto sayName {makeWalrus("rufus")};

	// Call the lambda function that walrus returned
	sayName();

	return 0;
}
