#include<cassert>
#include<iostream>
#include<vector>


class Stack
{
	
	std::vector<int>priArray{};

public:	
	void reset()
	{
		priArray.resize(0);
	}

	void print()
	{
		if (priArray.size()==0)
			std::cout<<"()";
		else
		{
			std::cout<<'(';
			for (std::size_t i {0};i<priArray.size();++i)
				std::cout<<priArray.at(i)<<' ';
			std::cout<<')';	
		}
		std::cout<<'\n';
	}

	bool push( int value)
	{
		if (priArray.size()==10)
			return false;
		else
		{
			priArray.push_back(value);
			return true;
		}

	}
	bool pop()
	{	
		assert(priArray.size()>0&&" Stack already deleted"); // stack returns true only when pop() operation is carried on non-zero vector
	
		if (priArray.size()>0)

		{
			priArray.pop_back();
			return true;
		}
	}
};

int main()
{
	Stack stack;
	stack.reset();

	stack.print();

	stack.push(5);
	stack.push(3);
	stack.push(8);
	stack.print();

	stack.pop();
	stack.print();

	stack.pop();
	stack.pop();
	//stack.pop();

	stack.print(); 

	return 0;
}