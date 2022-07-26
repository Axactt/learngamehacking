#include<iterator> // for std::begin and std::end
#include<iostream>


auto* find(auto* ptr,auto* ptr1,auto x)
{
	for (auto* num{ ptr }; (num != ptr1); ++num)
	{
		if (( * num) == x)
		{
			return num;
		}
	}

	return ptr1;
	
}

int main()
{
	int arr[]{ 2,5,4,10,8,20,16,40 };
	
	std::cout << " enter a positive integer to check if being in array: ";
	int input{};
	std::cin >> input;
	int* found{ find(std::begin(arr),std::end(arr),input) };

	if (found != std::end(arr))
	{
		std::cout << "Element found in array: " <<* found << '\n';
	}

	else
		std::cout << " Element not found in array";
	
	return 0;
}
