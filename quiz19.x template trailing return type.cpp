#include<iostream>
template<typename T>
class Pair1
{
private:
	T m_first {};
	T m_second {};
public:
	Pair1 ( T first, T second ) // Constructor should have same name as class
		:m_first { first }, m_second { second }
	{

	}
	// trailing return type + decltype() alongwith auto to deduce the return types of template automatically
	// Trailing return type should come at the extreme last
	auto  first()const->decltype(m_first) 
	{
		return m_first;
	}
	auto second()const ->decltype(m_second) 
	{
		return m_second;
	}
};

int main()
{
	Pair1 <int> p1 { 5,8 };
	std::cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';
	const Pair1 <double> p2 { 2.3,4.5 };
	std::cout<< "Pair: " << p2.first() << ' ' << p2.second() << '\n';

	return 0;

}