#include<iostream>
#include<random> // std::mt19337 and std::random_device
#include<vector>
#include<functional>

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

	for (int i {0}; i<listCount; ++i)
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

	
	

	while (true)
	{
		std::cout<<" guess the number in list";
		int guess {};
		std::cin>>guess;
		auto found {std::find(vecky.begin(),vecky.end(),guess)};
	

		if (found!=vecky.end())
		{
			vecky.erase(found); // std::vector.erase() to delete element from vector at irterator found
			
			if (std::size(vecky)>=1)
			{
				std::cout<<" Nice! "<<std::size(vecky)<<" numbers are left. ";
				continue;
			}
			else
				break;
		}
		else
		{
			auto closest {std::min_element(vecky.begin(),vecky.end(),[](int a,int b)
										   {
											   return a<b;
										   })};

			if ((*closest-guess)>4)
				std::cout<<guess<<"is wrong\n";
			break;
		}
		

	}
	
	

	
	return 0;
}