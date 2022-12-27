#include <iostream>
#include<cassert>
class IntArray
{
private:
	int* m_elem {};
	int m_length {};
public:
	IntArray(int length)
		:m_elem { new int [length]{} },
		m_length { length }//dynamically allocating array length	 
	{
		
	}
	~IntArray()
	{
		delete[]m_elem;
	}
	// Custom copy constructor with deep-copy
	IntArray(const IntArray& array)
	{
		deepCopy(array);
	}
	IntArray& operator=(const IntArray& array);
	void deepCopy(const IntArray& array);
	int& operator()(int length);
	int& operator[](int index);
	friend std::ostream& operator<<(std::ostream& out, const IntArray& array);
};

// DeepCopy function
void IntArray::deepCopy(const IntArray& array)
{
	//first we need to deallocate any value that array is holding
	delete[]m_elem;
	//because m-length is not a pointer,we can shallow copy it
	m_length = array.m_length;
	//m_elem is a dynamically allocated array pointer,so need to deep-copy if it is non-null
	if (array.m_elem)
	{
		//allocate memory for our copy
		m_elem = new int[m_length];
		//do the deep-copy of each individual element
		for (int i { 0 }; i < m_length; ++i)
			m_elem[i] = array.m_elem[i];
	}
	else
		m_elem = nullptr;
}
IntArray& IntArray::operator=(const IntArray& array)
{
	//self-assignement check
	if (this != &array)		
	{
		//now do the deep copy
		deepCopy(array);
	}
	return *this;
}
int& IntArray::operator()(int length)
{
	assert(length > 0);
	return m_elem[length];
}
int& IntArray::operator[](int index)
{
	assert(index >= 0);
	assert(index < m_length);
	return m_elem[index];
	// TODO: insert return statement here
}
std::ostream& operator<<(std::ostream& out, const IntArray& array)
{
	for (int i = 0; i < array.m_length; ++i)
	{
		out << array.m_elem[i] << ' ';
	}
	return out;
}

IntArray fillArray()
{
	IntArray a(5);
	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;
	return a;
}

int main()
{
	IntArray a { fillArray() };
	std::cout << a << '\n';
	auto& ref { a }; // we're using this reference to avoid compiler self-assignement errors
	a = ref;
	IntArray b(1);
	b = a;
	std::cout << b << '\n';
	return 0;
}

