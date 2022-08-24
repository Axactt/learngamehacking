#include<iostream>
#include<utility> // for std::swap


void selectionSort( int* array, int size , bool (*comparisonFcn)(int,int))// function pointer argument named as comparisonFcn for being linked to diffent function
{
	// step through each element of array
	for (int startIndex { 0 }; startIndex < (size - 1); ++startIndex)
	{
		// bestIndex is the index of the smallest/largest element we've encountered so far	
		int bestIndex { startIndex };

		// look for bestIndex remaining in the array starting at (startIndex+1)
		for (int currentIndex { startIndex + 1 }; currentIndex < size; ++currentIndex)
		{ 
			// if current element is smaller/larger than previous element assigned to bestIndex
			if (comparisonFcn( array[bestIndex], array[currentIndex] ))// actual comparison done here
			{
				// this our newest smallest/largest index for this iteration
				bestIndex = currentIndex;
			}

		}
		// Swap our start elemnt with our smallest/largest element
		std::swap( array[startIndex], array[bestIndex] );
	}
}
 // here is our comparison function that sorts in ascending order
bool ascending( int x, int y )
{
	return x > y;
}
// comparison function that sorts in descending order
bool descending( int x, int y )
{
	return x < y;
}

void printArray( int* array, int size )
{
	for (int index { 0 }; index < size; ++index)
	{
		std::cout << array[index] << ' ';
	}
	std::cout << '\n';
}

int main()
{
	int array[9] {3,7,9,5,6,1,8,2,4};

	printArray( array, 9 );


	// sort the array using comparisonFcn pointer parameter initialised with argument "ascending"(==&ascending)
	selectionSort( array, 9, ascending );// function pointer argument is function name without parentheis
	printArray( array, 9 );

	// sort array in descending order calling descending function as argument to comparisonFcn pointer parameter
	selectionSort( array, 9, descending ); // function pointer argument is functionname without parenthesis
	printArray( array, 9 );


	return 0;

}