#include<vector>
#include <iostream>

void printStack( const std::vector<int>& stack )
{
	for (auto& element : stack)
		std::cout << element << ' ';
	std::cout << "(cap " << stack.capacity() << " length " << stack.size() << ")\n";
}

int main()
{
	std::vector<int>stack {};

   stack.reserve( 5 ); // all0cate a certain amount of capacity upfront using reserve() function,resizing expensive

	printStack( stack );

	stack.push_back( 5 ); // push_back() pushes an element on stack
	printStack( stack );

	stack.push_back( 3 ); 
	printStack( stack );

	stack.push_back( 2 );
	printStack( stack );

	std::cout << " top: " << stack.back() << '\n'; // back returns the last element

	stack.pop_back(); // pop_back pops an element off the stack
	printStack( stack );

	stack.pop_back(); // pop_back pops an eleemnt off the stack
	printStack( stack );

	stack.pop_back();
	printStack( stack );


	return 0;
	
}