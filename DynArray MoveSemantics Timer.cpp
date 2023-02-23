#include<iostream>
#include<chrono> // for std::chrono functions
//Uses the above DynamicArray class

class Timer
{
private:
	//Type aliases to make accessing Nested type easier
	using Clock = std::chrono::high_resolution_clock;
	using Second = std::chrono::duration<double, std::ratio<1>>;

	std::chrono::time_point<Clock>m_beg{ Clock::now() };

public:
	void reset()
	{
		m_beg = Clock::now();
	}
	double elapsed() const
	{
		return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
	}
};

//Return a copy of arr with all of the values doubled
template<typename T>
class DynamicArray
{
private:
	int m_length{};
	T* m_array{};
public:
	DynamicArray( int length )
		:m_length{ length }, m_array{ new T[length] }
	{

	}
	~DynamicArray()
	{
		delete[] m_array;
		m_array = nullptr;
	}
	//copy constructor doing deep copy
	DynamicArray( const DynamicArray& a ) = delete;


	DynamicArray& operator= ( const DynamicArray& a ) = delete;

	//Move Constructor
	DynamicArray( DynamicArray&& a ) noexcept
		:m_array{ a.m_array }, m_length{ a.m_length }
	{
		a.m_length = 0;
		a.m_array = nullptr;
	}

	//move assignements
	DynamicArray& operator=( DynamicArray&& a ) noexcept
	{
		//self assignement check
		if (&a == this)
			return *this;
		//deallocate existing resources
		delete[]m_array;
		
		//Transfer of resources 
		m_length = a.m_length;
		m_array = a.m_array;
		a.m_length = 0;
		a.m_array = nullptr;

		return *this;
	}
	
	int getLength()const
	{
		return m_length;
	}
	T& operator[]( int index )
	{
		return m_array[index];
	}
	const T& operator[]( int index )const
	{
		return m_array[index];
	}
};

//Return a copy of array with all of the values doubled
DynamicArray<int>cloneArrayandDouble( const DynamicArray<int>& arr )
{
	DynamicArray<int> dbl{ arr.getLength() };
	for (int i{ 0 }; i < arr.getLength(); ++i)
		dbl[i] = arr[i] * 2;
	return dbl;

}
int main()
{
	Timer t;
	DynamicArray<int> arr{ 1000000 };
	for (int i{ 0 }; i < arr.getLength(); ++i)
		arr[i] = i;
	arr = cloneArrayandDouble( arr );
	std::cout << t.elapsed();
}