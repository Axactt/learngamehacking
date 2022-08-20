#include<array>
#include<iostream>
#include<vector>
#include<cstddef>

int main()
{
	std::array data{ 0,1,2,3,4,5,6 };
	std::size_t length{ std::size(data) }; // std::size_t unsigned integral type, defined as type of std::size

	// while loop with explicit index
	// std::size_t used as index type to avoid signed unsigned conversion error
	std::size_t index{ 0 };
	while (index != length)
	{
		std::cout << data.at(index); // data[index] could also have been used
		++index;
	}

	std::cout << '\n';
	// for loop with explicit index

	for (index = 0; index != length; ++index)
		std::cout << data[index];

	std::cout << '\n';

	// for loop with pointer(note pointer cant be constant bcoz we increment it)
	for (auto* ptr{ &data[0] }; ptr !=( & data[0] +length);++ptr) // &data[0]+length(pointer arithmentic) used here otherwise out of bounds array index error  
		std::cout<<*ptr;

    std::cout << '\n';

    // range based for loop 
    for (auto& i : data)
        std::cout << i;
	
	return 0;
}


