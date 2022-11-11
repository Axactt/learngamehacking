#include <array>
#include <chrono> // for std::chrono functions
#include <cstddef> // for std::size_t
#include <iostream>
#include <numeric> // for std::iota

const int g_arrayElements {10000};
class Timer
{
private:
	// Type aliases to make accessing nested types easier
	using Clock = std::chrono::steady_clock;
	using Second = std::chrono::duration<double,std::ratio<1>>;

	std::chrono::time_point<Clock>m_beg {Clock::now()};

public:
	void reset()
	{
		m_beg = Clock::now();
	}
	double elapsed()const
	{
		return std::chrono::duration_cast<Second>(Clock::now()-m_beg).count();
	}
};
/*
void sortArray(std::array<int,g_arrayElements>& array)
{
	// Step through each elemnt of the array
	// (except the last one, which will already be sorted by the time we get there
	for(std::size_t startIndex {0}; startIndex<(g_arrayElements-1);            ++startIndex)
	{
		// smallestIndex is the index of the smallest element we've encountered this iteration
		//start by assuming the smallest element is the first element of this iteartion
		std::size_t smallestIndex {startIndex};
		// then look for a smaller element in the rest of the array
		for(std::size_t currentIndex {startIndex+1}; currentIndex<g_arrayElements; ++currentIndex)
		{
			// if we've found an element that is smaller than our previoulsy found smallest

			if(array[currentIndex] < array[smallestIndex])

			{
				smallestIndex = currentIndex;
			}

		}
		// smallestIndex is now the smallest element in the remaining array
			//swap our start element with our smallest element(this sorts it into correct place)
		std::swap(array[startIndex],array[smallestIndex]);

	}


}  
*/

int main()
{
	std::array<int,g_arrayElements>array;
	std::iota(array.rbegin(),array.rend(),1);// fill the array with values 10000 to 1


	Timer t;
	 //sortArray(array);
	std::ranges::sort(array);// Sice c++20
	//If your compiler isn't c++20 - capable
	// std::sort(array.begin(),array.end());

	std::cout<<"Time elapsed: "<<t.elapsed()<<" seconds\n";
	return 0;
}