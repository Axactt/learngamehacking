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
	// Class object defined in locl scope or instantiated on heap/stack cant be used as expression parametrs
	MyData localData {};
	localData.value = 6;
	/*======================================================================================*/
	//Local object variable  localData can't be used as compile-time expression parametrs
	///  Myclass<&localData>myClass1;   <----------------------
	/*======================================================================================*/
	// On the other hand static variables even though defined in local scope have 
	//Have their address known at compile-time as compile-time constant
	// so pointer and refernces to static variables of class objects have copile-time known address
	// so pointers and refernces to static variable of class object used as expression parameters.

	static MyData staticData {};
	staticData.value = 7;
	Myclass<&staticData>myClass2;
	myClass2.printValue();

	return 0;
}