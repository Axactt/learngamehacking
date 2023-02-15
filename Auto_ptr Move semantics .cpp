#include<iostream>
template <typename T>
class Auto_ptr1
{
	T* m_ptr;
public:
	//Pass in a pointer to "own" via the constructor
	Auto_ptr1( T* ptr = nullptr )
		:m_ptr { ptr }
	{

	}
	//The destructor will make sure it gets deallocated
	~Auto_ptr1()
	{
		delete m_ptr;
	}
	// A copy constructor that implements move semantics
	Auto_ptr1( Auto_ptr1& a ) // note: not const
	{
	m_ptr = a.m_ptr;// transfer our dumb pointer from source to local object
	a.m_ptr = nullptr;//make sure the source no longer owns the nullptr
	}
	//an assignement operator taht implements move semantics
	Auto_ptr1& operator=( Auto_ptr1& a ) // note: not const
	{
		if (&a == this) // self-assignement check
			return *this;
	delete m_ptr;//make sure we dealloacte any pointer the destination is already holding first
	m_ptr = a.m_ptr;//then transfer our dumb pointer from the source to the loacl object
	a.m_ptr = nullptr;// make sure the source no longer owns the pointer
	return *this;
	}
	//OverLoad dereference and opeartor-> so we can use Auto_ptr1 like m_ptr
	T& operator* ()const
	{
		return *m_ptr;
	}
	T* operator->()const
	{
		return m_ptr;
	}
	bool isNull()const
	{
		return  m_ptr == nullptr;
	}
};
// a sample class to prove the above works
class Resource
{
public:
	Resource()
	{
		std::cout << "resource acquired\n";
	}
	~Resource()
	{
		std::cout << "resource destroyed\n";
	}
	void sayHi()
	{
		std::cout << " Hi\n";
	}
};
void someFunction()
{
	Auto_ptr1<Resource> res1 { new Resource() }; // ptr now owns the resource
	Auto_ptr1<Resource>res2;

}
int main()
{
//Auto_ptr1<Resource> res( new Resource() );//Note the alocation of memory here
//... but no explicit delete needed
//Also note that the Resource in angled braces doesn't need a * symbol, since that is supplied by the template

	Auto_ptr1<Resource>res1( new Resource() );
	Auto_ptr1<Resource> res2; // start as nullptr

	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

	res2 = res1; // res2 assumes ownership, res1 is set to null

	std::cout << "Ownership transfeered\n";
	
	std::cout << "res1 is " << (res1.isNull() ? "null\n" : "not null\n");
	std::cout << "res2 is " << (res2.isNull() ? "null\n" : "not null\n");

return 0;

}// Resource goes out of scope here and destroys the allocated Resource for us