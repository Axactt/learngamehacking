#include<cstddef>
#include<iostream>
#include<string>
#include<stdexcept>// for std::runtime error
class ArrayException : public std::runtime_error
{
public:
// std::runt_time error takes a const char* null-terminated string
// std::string_view may not be nullterminate so not good choice here
//our array-exception will take a const std::string& instead
//which is guaranteed be null-terminated, and can be converted to constchar*

	ArrayException(const std::string& error )
		:std::runtime_error{error.c_str()}
		//std::runtime_error will handle the string
	{

	}
// no need to override what() since we can just use std::runtime_error::what()
};

class IntArray
{
private:
	int m_data[3] {}; // assume array is length 3 
public:
	IntArray()
	{
	}
	int getLength()const
	{
		return 3;
	}
	int& operator[]( const int index )
	{
		if (index < 0 || index >= getLength())
			throw ArrayException { "InvalidIndex" };
		return m_data[index];
	}
};


int main()
{
	IntArray array;
	try
	{
		int value { array[5] };
	}
	catch (const ArrayException& exception) // derived catch blocks go first
	{
		std::cerr << " an array exception has occurred (" << exception.what() << ")\n";
	}
	catch (const std::exception& exception)
	{
		std::cerr << " Some other std::exception has occurred (" << exception.what() << ")\n";
	}
	return 0;
}
