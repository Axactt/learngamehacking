#include<algorithm>// std::min_element and std::max_element
#include<iostream>
#include<list>
#include<numeric> // std::iota
#include<vector>

int main()
{
	std::list<int> li( 6 );
	// Fill li with numbers starting with 0.
	std::iota( li.begin(), li.end(), 0 );
	std::cout << *std::min_element( li.begin(), li.end() ) << ' ' << *std::max_element( li.begin(), li.end() ) << '\n';

	auto it{ std::find( li.begin(),li.end(),3 ) };
    // insert 8 right before 3
	li.insert( it, 8 );
	for (int i : li) // for loop with iterators
		std::cout << i << ' ';
	std::cout << '\n';

	std::vector<int>vect{ 7, -3, 6, 2, -5, 0, 4 };
	//sort the vector
	std::sort( vect.begin(), vect.end() );
	for (int i : vect)
	{
		std::cout << i << '\n';
	}
	//reverse the vector
	std::reverse( vect.begin(), vect.end() );
	for (int i : vect)
	{
		std::cout << i << ' ';
	}
	std::cout << '\n';
	return 0;
}