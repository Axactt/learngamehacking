#include<iostream>
class Base
{
private:
	int m_value {};
	
public:
	Base(int value)
		:m_value{value}{ }
	int getValue()const
	{
		return m_value;
	}
};
class Derived :public Base
{
private:
public:
	Derived(int value)
		:Base { value }
	{
	}
	int getValue() = delete;
	
};
int main()
{
	Derived derived { 7 };
	//std::cout << derived.getValue();// getValue() has been deleted!, cannot call
	// Base::getValue() function called directly
	std::cout << derived.Base::getValue();
	// We can upcast Derived to a Base reference and getValue() will resolve to Base::getValue()
	std::cout << static_cast<Base&>(derived).getValue();// okay m_value is public in Base
	
	return 0;
}