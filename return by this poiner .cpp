#include<iostream>

class Calc
{
private: 
	int m_value {0};
public:
	Calc& add(int value) // member functio return *this instead of void
	{
		m_value += value;
		return *this;
	}
	Calc& sub(int value)
	{
		m_value -= value;
		return *this;
	}
	Calc& mult(int value)
	{
		m_value *= value;
		return *this;
	}
	int getValue()
	{
		return m_value;
	}
};


int main()
{
	Calc calc {};
	std::cout<<calc.add(5).sub(3).mult(4).getValue()<<'\n'; // chaining non static member function by returning *this
	return 0;
}