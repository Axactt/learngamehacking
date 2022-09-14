#include<iostream>
#include<cassert>
int binarySearch(const int* array,int target,int min,int max)
{
	assert(array);

	int midPoint {min+(max-min)/2};

	if (min>max)
		return -1;

	if (array[midPoint]>target)
		return binarySearch(array,target,min,midPoint-1);
	else if (array[midPoint]<target)
		return binarySearch(array,target,midPoint+1,max);
	else if (array[midPoint]==target)
		return midPoint;

}
int main()
{
	constexpr int array[] {3,6,8,12,14,17,20,21,26,32,36,37,42,44,48};

	int target {99};

	std::cout<<" target value index found: "<<binarySearch(array,target,0,14);

	return 0;

}