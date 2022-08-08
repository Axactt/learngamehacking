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

void bubbleSortFunction(std::string* ptr, int length)  // works in same way as std::sort of <algorithm> header
{
	for (int i{ 0 }; i < length-1; ++i)
	{
		for (int j{ 0 }; j < length-1; ++j)
		{
			if (ptr[j] > ptr[j + 1])
			{
				// instead of std::swap we are using a tempory std::string object 
				// array elements position replaced among each other by first assigning to std::string temp
				// works in same way as std::swap function of <utility> header
				std::string temp{ ptr[j] }; 
				ptr[j] = ptr[j + 1];
				ptr[j + 1] = temp;

			}
			
		}
	}
}


int main()
{
	    std::cout << " Enter number of student-names you want to enter:";
		int length{};
		std::cin >> length;

		std::string* arrNames{ new std::string[length]{} }; // dynamically allocate an array for names to be entered

		inputNames(arrNames, length);

		// std::sort(arrNames,arrNames+length); // std::sort to sort arrNames in ascending order
		// note we cannot use std::begin(arrNames) instead of std::begin(arrNames[0]); 
		// error coming that argument of type std::string* cannot be taken by std::begin() or std::end()
		// std::string type can be compared directly using operator < or >
		// arrNames+length will deacy to a pointer pointing to object after end of array i.e. std::end()

		bubbleSortFunction(arrNames, length); // WORKS in same way as std::sort function

		printSortedNames(arrNames,length);

		delete[] arrNames; // deleting a dynamically allocated array before program fimish to free memory used

		return 0;


}