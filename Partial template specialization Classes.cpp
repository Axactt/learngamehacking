#include<iostream>
template<typename T,int size>// size is the expression parameter
class StaticArray
{
private:
	//The expression parameter controls the size of the array
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
};

template<typename T,int size>
void print( StaticArray<T, size>& array )
{
	for (int count { 0 }; count < size; ++count)
		std::cout << array[count] << ' ';
}
// Template specialization for non-member function print()
// non-type expression parameters has to be defined in specialized template
//overload of print() function for partially specialized StaticArray<char,size>
// This overloaded version of print function takes partially speacialized StaticArray class

template<int size>// this keyword tells compiler that what follows is a template
void print( StaticArray<char, size>& array )
{
	for (int count { 0 }; count < size; ++count)
		std::cout << array[count];
}

int main()
{
	//declare an int array
	StaticArray<int, 4>int4 {};
	int4[0] = 0;
	int4[1] = 1;
	int4[2] = 2;
	int4[3] = 3;
	// declare a char array
	StaticArray<char, 14>char14 {};

	std::strcpy( char14.getArray(), "Hello, world!" );

	//print the array
	print( int4 );
	print( char14 );  // a space will not be printed after each character
	std::cout << ' ';

	//Now declare a char array of size 12
	StaticArray<char, 13>char13 {};

	std::strcpy( char13.getArray(), "Hello, momy!" );
	//Print the array
	print( char13 );
	return 0;
}