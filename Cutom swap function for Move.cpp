#include<iostream>
#include<string>

class Name
{
private:
	std::string m_name;//std::string is move capabled
public:
	Name( std::string name )
		:m_name{ name }
	{

	}
	Name( const Name& name ) = delete;
	Name& operator=( const Name& name ) = delete;
	//Do not use default std::swap as it will cause infinite recursion as it implements move-semantics inherently
	//implement our own swap() function to carry-out move-semantics
	friend void swap( Name& a, Name& b ) noexcept
	{
		//we avoid recursive calls by invoking std::Swap on member and not class object Name
		std::swap( a.m_name, b.m_name );

	}


	Name( Name&& name ) noexcept
	{
		std::cout << "Move ctor\n";
		swap( *this, name ); //Now calling our swap not std::SWAP

	}
	Name& operator=( Name&& name ) noexcept
	{
		std::cout << "Move assign\n";
		swap( *this, name ); // calling our swap which works on members not std::swap
		return *this;
	}
	const std::string& get()
	{
		return m_name;
	}
};
int main()
{
	Name n1{ "Alex" };
	n1 = Name{ "Joe" }; //invokes move assignement

	std::cout << n1.get() << '\n';
	return 0;
}