#include<iostream>
#include<random> // std::mt19337 and std::random_device
#include<vector>

namespace Random // called by Random::get(2,4)
{
	std::mt19937 mt {std::random_device {}()};
	
	int get(int min,int max)
	{
		std::uniform_int_distribution die {min,max};
		return die(mt);
	}
}

int main()
{
	std::cout<<" Enter the number to generate square-list to start: ";
	int startNum {};
	std::cin>>startNum;
	std::cout<<" How many numbers to play with as a list of square: ";
	std::size_t listCount {};
	std::cin>>listCount;

	// intialize a list of square numbers
	std::vector<int> vecky(listCount);
	//Get random number between 2 and 4
	int rngNum {Random::get(2,4)};

	// generation of vector list to play with

	for (std::size_t i {0}; i<listCount; ++i)
	{
		auto playNum  {[=]() mutable
						{
							startNum = startNum+i;
							startNum *= startNum;
							return startNum*rngNum;
		}};
		vecky.at(i)=playNum();
	}

	for (const auto& elem:vecky)
		std::cout<<elem<<'\n';

	std::cout<<" guess number in list: ";
	int guess {};
	std::cin>>guess;

	return 0;
}