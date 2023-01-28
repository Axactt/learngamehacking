#include<iostream>

class MyData
{
public:
	int value {};
};
// class object as global variable, address is known at compile-time
//Can be used as a expression non-type parametrs fo template classes.
MyData globalData; // globalData global variable

template<MyData* data>
class Myclass
{
public:
	void printValue()
	{
		std::cout << data->value << '\n';
	}
};

int main()
{
	globalData.value = 5;
	
	// here address to global class object variable used as expression non-type parameters.
	
	Myclass<&globalData>myClass; 
	myClass.printValue();
	return 0;
}