#include<iostream>
#include<string>
template<typename T>
class Storage
{
private:
	T m_value {};
public:
	Storage( T value )
		:m_value { value }
	{

	}
	void print()
	{
		std::cout << m_value << '\n';
	}
	~Storage() // for specialzied template destructor--need an explicitly defined destructor
	{
	};
};
//template specialized constructor which will get used when we allocate variable of type Storage<char*>
template<>
Storage<char*>::Storage( char* const value )
{
	if (!value) 
		return;
	//Figure out how long the string in value is'
	int length { 0 };
	while (value[length] != '\0')
		++length;
	++length; // +1 to account for null terminator
	
	//Allocate memory to hold the value string
	m_value = new char[length];
	
	//Copy the actual value string into the m_value memory we just allocated(deep copy)
	for (int count = 0; count < length; ++count)
		m_value[count] = value[count];
}
// template-specialized destructor to prevent memory-leak
// This way memory allocated in specialized constructor will be deleted in specialized destructor
template<>
Storage<char*>::~Storage()
{
	delete[]m_value;
}

int main()
{
	// Dynamically allocate a temporary string
	std::string s;
	//Ask user for their name
	std::cout << " Enter your name: ";
	std::cin >> s;
	//store the name
	Storage<char*>storage( s.data() );
	storage.print();// prints our name
	s.clear(); // clear the std::string
	storage.print(); // Prints nothing
}