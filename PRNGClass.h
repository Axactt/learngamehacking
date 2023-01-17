#ifndef PRNGCLASS_H
#define PRNGCLASS_H
#include<random>
#include<chrono>

class PRNGClass
{
private:
	
	 int64_t seedTime { std::chrono::steady_clock::now().time_since_epoch().count() };
     int64_t seedRand { std::random_device{}()};
	
public:
	
		
	 int operator()(int min,int max)
	{
		std::mt19937 mT { static_cast<unsigned int>(seedTime) };
		std::uniform_int_distribution dieMinMax { min,max };
		return dieMinMax( mT ); // to intialize a set of uniform distribution number	
	}

}; 

#endif
