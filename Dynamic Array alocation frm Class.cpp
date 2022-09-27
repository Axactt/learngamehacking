#include<iostream>
#include<cassert>
#include<cstddef>

class IntArray
{
private:
	int* m_array {};
	int m_length {};
public:
	IntArray(int length) // constructor
	{
		assert(length>0);
		m_array = new int[static_cast<std::size_t>(length)]{};
		m_length = length;

	}

	~IntArray() // desturctor
	{
		// dynamically delete the aray we allocated earlier
		delete[]m_array;

	}

	void setValue(int index,int value)
	{
		assert(index<m_length&&"index out of bounds");
		m_array[index] = value;
	}
	int getValue(int index)
	{
		assert(index<m_length&& "index out of bounds");
		return m_array[index];
	}
	int getLength ()
	{
		return m_length;
	}

};

int main()
{
	// allocate 10 integers for IntArray a
	IntArray a(10); // cant use IntArray a(10) {};only default initialization possible

	for (int count {0}; count<a.getLength(); ++count)
		a.setValue(count,count+1);

	std::cout<<" the value of elemnet 0 is: "<<a.getValue(0)<<'\n';
	
	return 0;
}// a is destroyed here , so ~IntArray() desrtuctor function is called here