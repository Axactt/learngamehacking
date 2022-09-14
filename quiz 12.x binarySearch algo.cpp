#include<iostream>
#include<iterator>

// binarySearch should return index of target element found, -1 otherwise
int binarySearch(const int* array,int target,int min,int max)
{

		while (min<=max)
		{
			int midPoint {min+(max-min)/2};
			if (array[midPoint]>target)
			{
// if array[midPoint]>target,then we know that the number must be in lower half of array
//  we can use midpoint-1 as upper index,since we don't need to test array beyond midpoint next iteration
				max = midPoint-1;
			}
			else if (array[midPoint]<target)
			{
//if array[midPoint]<target, then we know that the number must be in upper half of array
// we acn use midpoint + 1 as min index, since we don't need to test array below and uptill midpoint next iteration
				min = midPoint+1;
			}
			else 
				return midPoint ;
			 
		}
	
		return -1;


}

int main()
{
	constexpr int array[] {3,6,8,12,14,17,20,21,26,32,36,37,42,44,48};

	// We're going to test a bunch of values to see if they produce the expected results
	constexpr int numTestValues {9};
	// Here are the test values
	constexpr int testValues[numTestValues] {0,3,12,13,22,26,43,44,49};
	// And here are the expected results for each value
	int expectedValues[numTestValues] {-1,0,3,-1,-1,8,-1,13,-1};

	// Loop through all of the test values
	for (int count {0}; count<numTestValues; ++count)
	{
		// See if our test value is in the array
		int index {binarySearch(array,testValues[count],0,static_cast<int>(std::size(array))-1)};
		// If it matches our expected value, then great!
		if (index==expectedValues[count])
			std::cout<<"test value "<<testValues[count]<<" passed!\n";
		else // otherwise, our binarySearch() function must be broken
			std::cout<<"test value "<<testValues[count]<<" failed.  There's something wrong with your code!\n";
	}

	return 0;
}