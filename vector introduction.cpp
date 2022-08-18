#include<vector>
#include<iostream>

void printLength(const std::vector<int>& array)
{
	std::cout << " the length is " << array.size() << '\n';
}


int main()
{

	std::vector<int> array{ 9,7,5,3,1 };
	
	printLength(array); // vector array remebers its length when passeed to a function
	
	std::cout << array[1] << '\n';
	std::cout << array.at(3) << '\n';
	
	array = { 1,2,3,4,5,6 }; // array assignement, length now 6 using initialization list
	array = { 0,12,13 }; // array assignement, length now 3 using initialization list
	
	printLength(array);

	std::vector<int> empty{};
	printLength(empty);
	
	
	
	// resizing a vector using .resize()

	empty.resize(6);
	printLength(empty);

	for (int i{ 0 }; i < 6; ++i)
		std::cout << empty[i] << ' ';

	std::cout << '\n';
	
	array.resize(6);
	for (const auto& element : array)
		std::cout << element << ' ';
	std::cout << '\n';

	// using direct initializtion to create an array of size 5 elements, each element is 0
	//If we had used brace initialization, vector would be only one element of intger 5

	std::vector<int>myArray(5); 
    std::cout << myArray.size() << '\n';

	for (const auto& el : myArray)
		std::cout << el << ' ';

	std::cout << '\n';


	return 0;
}