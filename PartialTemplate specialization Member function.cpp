#include<iostream>
template<typename T, int size>// 4 is expression parameter
class StaticArray_Base
{
protected:
	// The expression parameter controls the 4 of the array
	T m_array[size] {};
public:
	T* getArray()
	{
		return m_array;
	}
	T& operator[]( int index )
	{
		return m_array[index];
	}
	void print()
	{
		for (int i { 0 }; i < size; ++i)
			std::cout << m_array[i] << ' ';
		std::cout << '\n';
	}
	virtual ~StaticArray_Base() = default;
};

// Had to partially specialize the whole class 
// to get a member function whcih is having partial specialization function
// As functions cannot be partially specialized
// Lot of code duplicacy occurred here
// So we can use inheritance from whcih new array is inheriting base non-speacialzied
template<typename T, int size>// sizee is expresion parameter

// note that the publlic base class should be mentioned with template argument-list
//not a parameter list with full typenames.
class StaticArray :public StaticArray_Base< T, size> 
{
};
// then this inherited class will have all members from Base interited generic template class
//So now   we will created a partially specilized templated  class from this derived class
// This will have specific partially specialized function inside.
template<int size>// size is the expression parameter
class StaticArray<double, size> :public StaticArray_Base<double, size>
{

public:

	void print()
	{
		for (int i { 0 }; i < size; ++i)
			std::cout << std::scientific << this->m_array[i] << ' ';
		std::cout << '\n';
		// this-> prefix is needed for non-dependendent name lookup members
	}
};


int main()
{// declare an integer array with room for 6 integers
	StaticArray<int, 6> intArray {};

	// Fill it up in order, then print it
	for (int count { 0 }; count < 6; ++count)
		intArray[count] = count;

	intArray.print();

	// declare a double buffer with room for 4 doubles
	StaticArray<double, 4> doubleArray {};

	for (int count { 0 }; count < 4; ++count)
		doubleArray[count] = (4.0 + 0.1 * count);

	doubleArray.print();

	return 0;
}