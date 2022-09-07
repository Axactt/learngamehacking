#include<algorithm>
#include<array>
#include<iostream>
#include<string_view>

struct Student
{
	std::string_view name;
	int points;
};
// predicate function taking const refence to array elements which are struct
bool compare(const Student& lhs,const Student& rhs) 
{
	if(lhs.points!=rhs.points) // comparing if two random member are equal or not
		return lhs.points<rhs.points;
}

int main()
{
	// extra pair of braces for list initialization of array of struct
	std::array<Student,8>arr =
	{{
	 { "Albert",3 },
	 {"Ben,5"},
	 {"Christine,2"},
	 {"Dan",8},
	 {"Enchilada",4},
	 {"Francis",1},
	 {"Greg",3},
	 {"Hagrid",5}
	}};
	 
	// here compare is function pointer to a predicate function 
	// to which array elements are passed by const refernce
	// generate the required iterator as per algorithm
	auto maxPoints {std::max_element(arr.begin(),arr.end(),compare) };
	
	// dereferencing the iterator and then applying member selection operator to it  
    std::cout<<(*maxPoints).name<<" is the best student.\n"; 
	return 0;
}


