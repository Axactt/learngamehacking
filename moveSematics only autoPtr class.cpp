#include <iostream>

template<typename T>
class Auto_ptr5
{
	T* m_ptr;
public:
	Auto_ptr5( T* ptr = nullptr )
		:m_ptr( ptr )
	{
	}

	~Auto_ptr5()
	{
		delete m_ptr;
	}

	// Copy constructor disabled for only move-sematics
	// Do deep copy of a.m_ptr to m_ptr
	Auto_ptr5( const Auto_ptr5& a ) = delete;
	/* {
		m_ptr = new T;
		*m_ptr = *a.m_ptr;
	}  */
	// move constructor introduced C++11 using R-value reference
	//transfer ownership of a.m_ptr to m_ptr
	Auto_ptr5( Auto_ptr5&& a ) noexcept
		:m_ptr { a.m_ptr }
	{
		a.m_ptr = nullptr; // setting temporary object bound to nullptr
	}


	// Copy assignment
	// Do deep copy of a.m_ptr to m_ptr
	Auto_ptr5& operator=( const Auto_ptr5& a ) = delete;
/* {
		// Self-assignment detection
		if (&a == this)
			return *this;

		// Release any resource we're holding
		delete m_ptr;

		// Copy the resource
		m_ptr = new T;
		*m_ptr = *a.m_ptr;

		return *this;
	}  */

	//Move assignement
	//Transfer ownership of a.m_ptr to m_ptr
	Auto_ptr5& operator=( Auto_ptr5&& a )noexcept
	{
		// self assignement detection
		if (&a == this)
			return *this;
		//Release any resource we're holding
		delete m_ptr;

		//transfer ownership of a.m_ptr to m_ptr
		m_ptr = a.m_ptr;
		// move semantics here original resource original resource no longer owns the pointer
		a.m_ptr = nullptr;
		return *this;
	}

	T& operator*() const
	{
		return *m_ptr;
	}
	T* operator->() const
	{
		return m_ptr;
	}
	bool isNull() const
	{
		return m_ptr == nullptr;
	}
};

class Resource
{
public:
	Resource()
	{
		std::cout << "Resource acquired\n";
	}
	~Resource()
	{
		std::cout << "Resource destroyed\n";
	}
};

Auto_ptr5<Resource> generateResource()
{
	Auto_ptr5<Resource> res { new Resource };
	return res; // this return value will invoke the copy constructor
}

int main()
{
	Auto_ptr5<Resource> mainres;
	mainres = generateResource(); // this assignment will invoke the copy assignment
	return 0;
}