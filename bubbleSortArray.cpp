#include<iostream>
#include<utility> // for std::swap function
#include<iterator>// for std::size function

int main()
{
	int array[]{101,45,6,3,2,9,59,5,7,1,5,11,98,37,21,39,41,67 };
	constexpr int length{ static_cast<int>(std::size(array)) };

	
	for (int i{ 0 }; i < length-1; ++i)
	{
		
		bool swapFlag{ false };

		// index<length-i-1 optimizes for loop to not check already sorted elements at end of array

		for (int index{ 0 }; index < (length -i- 1); ++index)
		{	
			
		
			if (array[index] > array[index + 1])
			{
				std::swap(array[index], array[index + 1]);
				swapFlag = true;
			}

			
		}

		if (!swapFlag)
		{
			std::cout << "Early termination on iteration: " << i << '\n';
			break;
		}
	}

	

	for (int index{ 0 }; index < length ; ++index)
		std::cout << array[index] << ' ';

	return 0;

}