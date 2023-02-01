#include<iostream>
#include<string>
#include<string_view>

// first fully templated class Pair<T,U> is made to define a base class

template<typename T,typename U>
class Pair
{
protected:
	T m_str;
	U m_value {};

public:
	Pair(T& str, U& value )
		:m_str{str},m_value{value}{ }

	T & first()
	{
		return m_str;
	}
    U& second()
	{
		return m_value;
	}
	const T& first()const // for const objects
	{
		return m_str;
	}
	const U& second() const  // for const objects
	{
		return m_value;
	}
};
// above Base class partially specialized with std::string_view as specialized type parameter
// the second parameter can be any value as per template parameter declaration 
// Now the class Pair can be used as Pair<std::string_view,U> where one first parameter
//Is specialized for being std::string and second parameter can be anything
// Now whenever we declare a class named Pair<std::string,U> we will get this specialized version we just declared
// But if we declare a class identifier named Pair<double,float> which is npt having std::string we will get generic Pair<T,U> version
/*template<typename U>
class Pair<std::string,U>
{
protected:
	std::string m_str;
	U m_value {};

public:
	Pair( std::string str,  U& value )
		:m_str { str }, m_value { value }
	{
	}

	std::string& first()
	{
		return m_str;
	}
	U& second()
	{
		return m_value;
	}
	const std::string& first()const // for const objects
	{
		return m_str;
	}
	const U& second() const  // for const objects
	{
		return m_value;
	}
};  */
//Class template specialization allows us to specialize a template class for a
// particular data type( or data types, if there are multiple template parameters )
// Class Template specialization are treated as completely independent classes,
//This means we can change anything and everything about our specialization class
//Inluding the way it is implemented and the function it makes public, 
// JUST AS IF IT IS A INDEPENDENT CLASS

// As  we have declared a specialized(partially) version of templated clas Pair<T,U>
//The partially specialized version is now completely independent class 
//This specialized independent class is instantiated and referred as Pair<std::string,U>
// Being independent we can use this Pair<std::string,U> as a Base class 
//to inherit to other class which is having only one templated parameter(the non specialized one)
//No need to specify the specialized parameter std::string of base Pair class again
// In template parameter declaration of Derived class as all implementation deatils regarding std::string
//it will be taken care of by Base Pair<std::string,U> class.
// so in dependent name of derived class StringValuePair(and template parameter declaration) which is having different name
// only one parameter which non-specialized will be used.
//In this way inheritance helps in code reuse even though having different identifier names.

template<typename U>
class StringValuePair :public Pair<std::string, U>
{
public:
	StringValuePair(std::string str, U& value)
		: Pair<std::string, U>{str,U}{ }
/*
	std::string& first()
	{
		return this->m_str;
	}
	U& second()
	{
		return this->m_value;
	}
	const std::string& first()const // for const objects
	{
		return this->m_str;
	}
	const U& second() const  // for const objects
	{
		return this->m_value;
	}  */

};





int main()
{
	StringValuePair<int> svp{ "Hello", 5 };
	std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';
}
