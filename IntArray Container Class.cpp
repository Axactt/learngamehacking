#include<iostream>
#include"IntArray.h"

int main()
{
	// Declare an array with 10 elements
	IntArray array(10);

	//Fill the array with numbers 1 through 10
	for (int i { 0 }; i < 10; ++i)
		array[i] = i + 1;

	// Resize the array with eight 8  elements
	array.resize(8);

	//Insert the number 20 before element with index 5
	array.insertBefore(20, 5);

	// remove the element with index 3
	array.remove(3);
	// add 30 and  40 at the beginning and end
	array.insertAtEnd(30);
	array.insertAtBeginning(40);

	// a few more tests  that ensure copy constructing/assigning arrays
	//doesn't break things
	{
		IntArray b { array };
		b = array;
		b = b;
		array = array;
	}

	//Print out all the numbers
	for (int i { 0 }; i < array.getLength(); ++i)
		std::cout << array[i] << ' ';

	std::cout << '\n';

	return 0;

}