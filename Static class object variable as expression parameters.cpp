#include<iostream>
class MyData
{
public:
	int value;
};

template <MyData& data>
class MyClass
{
public:
	void printValue()
	{
		std::cout << data.value << std::endl;
	}
};

void foo()
{
	static MyData data;
	data.value = 5;
	MyClass<data> myClass;
	myClass.printValue();
}

int main()
{
	foo();
	return 0;
}
