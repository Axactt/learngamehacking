#include<iostream>
#include<string>
#include<utility> // for std::pair,std::make_pair,std::move,std::move_if_no_except
#include<stdexcept> //std::runtime_error

//Example move-constructor definition for std::pair
//Take in an 'old' pair, and then move construct the new pair's 'first' and 'second' subobjects from old ones
/*
template<typename T1,typename T2>
pair<T1,T2>::pair(pair&&old)
	:first(std::move(old.first)),
	second(std::move(old.second)){ }  */

class MoveClass
{
private:
	int* m_resource{};
public:
	MoveClass() = default;
	MoveClass( int resource )
		:m_resource{ new int{resource} }
	{
	}
	//copy constructor
	MoveClass( const MoveClass& that )
	{
		//deep copy
		if (that.m_resource != nullptr)
		{
			m_resource = new int{ *that.m_resource };
		}
	}
	//Move constructor
	MoveClass( MoveClass&& that ) noexcept
		:m_resource{ that.m_resource }
	{
		that.m_resource = nullptr;
	}

	~MoveClass()
	{
		std::cout << "destroying " << *this << '\n';
		delete m_resource;

	}
	friend std::ostream& operator<<( std::ostream& out, const MoveClass& moveClass )
	{
		out << "MoveClass(";
		if (moveClass.m_resource == nullptr)
		{
			out << "empty";
		}
		else
		{
			out << *moveClass.m_resource;
		}
		out << ')';
		return out;
	}
};

class CopyClass
{
public:
	bool m_throw{};
	CopyClass() = default;
	//copy constructor throws an exception when copying from a CopyClass object where its m_throw is "true"
	CopyClass( const CopyClass& that )
		:m_throw{ that.m_throw }
	{
		if (m_throw)
		{
			throw std::runtime_error{ "abort!" };
		}
	}
};

int main()
{
	//We can make a std::pair wwithout any problems:
	std::pair my_pair{ MoveClass{13},CopyClass{} };
	std::cout << "my_pair.first: " << my_pair.first << '\n';
	//but the problem arises when we try to move that pair into another pair.

	try
	{
		my_pair.second.m_throw = true; // to trigger copy constructor exception
		//the following line will throw an exception
		std::pair moved_pair{ std::move( my_pair ) };//we'll comment out this line later
		//std::pair moved_pair{std::move_if_noexcept(my_pair)};//we'll uncommnet this later
		std::cout << "moved pair exists\n";//Nver prints

	}

	catch (const std::exception& ex)
	{
		std::cerr << "Error found: " << ex.what() << '\n';
	}
	std::cout << "my_pair.first: " << my_pair.first << '\n';

	return 0;
}
