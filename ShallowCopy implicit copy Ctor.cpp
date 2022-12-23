#include<cstring> // for strlen()
#include<cassert> // for assert
#include<iostream>
class MyString
{
private:
	char* m_data {};
	int m_length {};
public:
	//string constructor
	MyString(const char* source = "")
	{
		assert(source); //make sure source isn't a null string
		//Find length of the string
		// Plus one character for a terminator
		m_length = std::strlen(source) + 1;

		//allocate a buffer equal to this length
		m_data = new char[m_length];

		//Copy the parameter string into our internal buffer
		for (int i { 0 }; i < m_length; ++i)
			m_data[i] = source[i];
	}
	// Deafult implicit copy constructor maylike
	MyString(const MyString& source)
		//m_data is shallow pointer copy of source.m_data,both point to same thing
		:m_data {source.m_data },
		m_length { source.m_length }
	{
	}

	~MyString() //destructor
	{
		// we need to deallocate our string
		delete[]m_data;
	}
	char* getString()
	{
		return m_data;
	}
	int getLength()
	{
		return m_length;
	}
};
int main()
{
	MyString hello { "Hello, world!" };

	{
		MyString copy { hello };
		// use default copy constructor , copy is a local variable so gets destroyed here
		//The destructor deletes copy's string , but as shallow copy by copy ctor made a copy of pointer which accesses same address as original object
		// It leaves hello(original object) with a dangling pointer

	}
	std::cout << hello.getString() << '\n';

	return 0;

}
