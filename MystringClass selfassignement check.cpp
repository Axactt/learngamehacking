#include<iostream>

class MyString
{
private:
	char* m_data {};
	int m_length {};
public:
	MyString(const char* data = nullptr, int length = 0)
		:m_length { length }
	{
		if (length)
		{
			m_data = new char[length];
			for (int i { 0 }; i < length; ++i)
				m_data[i] = data[i];
		}
	}
	~MyString()
	{
		delete[]m_data;
	}
	//OverLoaded assignement
	MyString& operator=(const MyString& str);

	friend std::ostream& operator<<(std::ostream& out, const MyString& s);
};
std::ostream& operator<<(std::ostream& out, const MyString& s)
{
	out << s.m_data;
	return out;
}
// Simplistic implementation of operator==(not to be used)
MyString& MyString::operator=(const MyString& str)
{
	// self-assignement check
	if (this == &str)
		return *this;
	//if data exists in the current string,delete it
	if (m_data)
		delete[]m_data;
	m_length = str.m_length;

	// copy the data from str to the implicit object
	m_data = new char[str.m_length];

	for (int i { 0 }; i < str.m_length; ++i)
		m_data[i] = str.m_data[i];

	// return the existing object so we can chain this operator
	return *this;
}

int main()
{
	MyString alex { "Alex",5 };
	//MyString employee {};
	//employee = alex; 
	//std::cout << employee;
	alex = alex;// calls alex.operator=(alex)
	std::cout << alex;
	return 0;
}

