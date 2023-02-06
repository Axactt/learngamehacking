#include<cstddef>
#include<exception>
#include<iostream>
#include<string>
#include<string_view>
#include<stdexcept>// for std::runtime error
class ArrayException : public std::exception
{
private:
	std::string m_error {};
public:
	ArrayException( std::string_view error )
		:m_error { error }
	{

	}
	// std::exception::what() returns a const char*, so we must as well
	//what()has specifier noexcept which means function promises not to throw 
	//exceptions itself. 
	const char* what() const noexcept override
	{
		return m_error.c_str();
	}
};

class IntArray
{
private:
	int m_data[3] {}; // assume array is length 3 
public:
	IntArray(){ }
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
