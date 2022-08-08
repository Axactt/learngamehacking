#include <string> // for std::string and std::getline
#include <algorithm> // for std::find and std::sort
#include<iterator> // for std::begin and std::end
#include<iostream> // for std::cout


void inputNames(std::string* arrNames,int length)
{
	std::cout << " Enter names of students:\n";
	for (int i{ 0 }; i < length; ++i)
	{
		std::getline(std::cin >> std::ws,arrNames[i]); // To input full name with spaces, 
		//std::ws as output manipulator for std::cin to ignore leading whitespaces 
	}

	std::cout << '\n';

}

void printSortedNames(std::string* arrNames, int length)
{
	for (int i{ 0 }; i < length; ++i)
		std::cout << arrNames[i] << '\n';
}


int main()
{
	    std::cout << " Enter number of student-names you want to enter:";
		int length{};
		std::cin >> length;

		std::string* arrNames{ new std::string[length]{} }; // dynamically allocate an array for names to be entered

		inputNames(arrNames, length);

		std::sort(arrNames,arrNames+length); // std::sort to sort arrNames in ascending order
		// note we cannot use std::begin(arrNames) instead of std::begin(arrNames[0]); 
		// error coming that argument of type std::string* cannot be taken by std::begin() or std::end()
		// std::string type can be compared directly using operator < or >
		// arrNames+length will deacy to a pointer pointing to object after end of array i.e. std::end()

		printSortedNames(arrNames,length);

		return 0;


}