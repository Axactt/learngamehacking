#include<iostream>
#include<random> // std::mt19337 and std::random_device
#include<vector>
#include<cmath> // for std::abs

namespace Random // called by Random::get(2,4)
{
	std::mt19937 mt {std::random_device {}()};

	int get(int min,int max)
	{
		std::uniform_int_distribution die {min,max};
		return die(mt);
	}
}
// Custom predicate function passed as an argument to stl algorithm std::min-element
// Predicate function is passsed as a function pointer of form &compare
// Note parameters of compare should strictly be type of elements of container on which stl algorithm is used

/*bool compare(int lhs,int rhs)
{
	if (lhs!=rhs)
		return (lhs<rhs);

}*/

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
		auto playNum {[=]() mutable
					  {
						  startNum = startNum+i;
						  startNum *= startNum;
						  return startNum*rngNum;
		}};
		vecky.at(i) = playNum();
	}

	for (const auto& elem:vecky)
		std::cout<<elem<<'\n';

	for (std::size_t i {listCount}; i>=1; --i)
	{
		std::cout<<" guess the number in list:  ";
		int guess {};
		std::cin>>guess;
		auto found {std::find(vecky.begin(),vecky.end(),guess)};

		if (found==vecky.end())
		{
			//Custom predicate function is always a function pointer in call of form prepending ampersand operator(&)
			// prepending ampersand can be dropped of also in call as an argument, but better to show for understanding
			// Here lambda function is used instead of custom predicate function
			auto closest {std::min_element(vecky.begin(),vecky.end(),[](int a,int b)
										   {
											   return a<b;
										   })};

			if (std::abs(guess-*closest)>4) // to calculate the absolute value of difference for comparison
			{
				std::cout<<" Wrong \n";
				break;
			}
			else
			{
				std::cout<<guess<<'\n';
				break;
			}
		}
		else
		{
			vecky.erase(found); // std::vector.erase() to delete element from vector at irterator found	
			std::cout<<" Nice! "<<std::size(vecky)<<" numbers are left.\n";
		}
	}
	return 0;
}