#include<iostream>

struct House
{
	int number{};
	int stories{};
	int roomsPerStory{};

};

struct Array
{
	House value[3]{};
};
int main()
{

	// implementation of list initialization for std::array using struct data type

	Array houses{ {{13,4,30},{14,3,10},{15,3,40}} }; // note one extra pair of braces is put for initializing 

	for (const auto& house : houses.value) // array is accessed using "value" memeber sof struct "Array"
	{
		std::cout << " house number " << house.number
			<< " has " << house.stories * house.roomsPerStory
			<< " rooms\n";
	}


	return 0;
}