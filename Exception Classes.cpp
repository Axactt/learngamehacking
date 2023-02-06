#include<iostream>
#include<string>
#include<string_view>
#include <cassert> // for assert()

class ArrayException
{
private:
	std::string m_error;
public:
	ArrayException( std::string_view error )
		:m_error { error }{ }

	const std::string& getError()const
	{
		return m_error;
	}

};

class IntArray
{
private:
	int m_length {};
	int* m_data {};

public:
	IntArray() = default;

	IntArray( int length ) :
		m_length { length }
	{
		assert( length >= 0 );

		if (length > 0)
			m_data = new int[length]
		{};
	}

	~IntArray()
	{
		delete[] m_data;
		// we don't need to set m_data to null or m_length to 0 here, since the object will be destroyed immediately after this function anyway
	}

	void erase()
	{
		delete[] m_data;
		// We need to make sure we set m_data to nullptr here, otherwise it will
		// be left pointing at deallocated memory!
		m_data = nullptr;
		m_length = 0;
	}

	int& operator[]( int index )
	{
		if (index < 0 || index >= getLength())
	// Exception classs constructed in throw stement and caught by try block
			throw ArrayException { " Invalid index " }; 
		
		return m_data[index];
	}

	int getLength() const
	{
		return m_length;
	}
};

int main()
{
	IntArray array(3); // parenthesis used for container classes
	try
	{
int value { array[5] }; // out of range , exception thrown observed here here
	}
	catch (const ArrayException& exception) // exception of class type caught
	{
		std::cerr << " An array exception occurred (" << exception.getError() << ")\n";
	}
}