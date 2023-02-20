#include<iostream>
template<typename T>
class Auto_ptr3
{
	T* m_ptr;
public:
	Auto_ptr3(T* ptr = nullptr)
		:m_ptr{ptr}{}
	~Auto_ptr3()
	{
		delete m_ptr;
	}
	//copy constructor
	//Do deep copy of a.m_ptr to m_ptr
	Auto_ptr3( const Auto_ptr3& a )
	{
		//allocate a new memory from os worth T and 
		// assign its address to m_ptr
		// deep copy the contents of a.m_ptr to this->m_ptr by derefrerencing pointers
		this->m_ptr = new T; 
		*m_ptr = *a.m_ptr;

	}
	//copy asignement
	// Do deep copy of a.m_ptr to m_ptr
	Auto_ptr3& operator=( const Auto_ptr3& a )
	{
		//self assignemnet detection
		if ( &a == this)
			return *this;
		//Release any resource we are holding
		// Ok to delete nullptr
		delete m_ptr;

		//allocate a new memory from os worth T and 
		// assign its address to m_ptr
		// deep copy the contents of a.m_ptr to this->m_ptr
		m_ptr = new T;
		*m_ptr = *a.m_ptr;
		return *this;
	}
	T& operator*()const
	{
		return *m_ptr;
	}
	T* operator->()const
	{
		return m_ptr;
	}
	bool isNull()const
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
		puts( "Resource destroyed" );
	}
};

Auto_ptr3 <Resource> generateResource()
{
	Auto_ptr3<Resource>res{new Resource};
	return res; // this return value will invoke the copy constructor
}
int main()
{
	Auto_ptr3<Resource>mainres;
	mainres = generateResource(); // thii assignement will invoke the copy assignement
	return 0;
}