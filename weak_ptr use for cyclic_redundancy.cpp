#include<iostream>
#include<memory> // for std::shared_ptr
#include<string>
class Person
{
	std::string m_name;
	std::weak_ptr<Person> m_partner;
public:
	Person( const std::string& name )
		:m_name{ name }
	{
		std::cout << m_name << " created\n";
	}
	~Person()
	{
		std::cout << m_name << " destroyed\n";
	}
	friend bool partnerUp( std::shared_ptr<Person>& p1, std::shared_ptr<Person>& p2 )
	{
		if (!p1 || !p2)
			return false;
		p1->m_partner = p2;
		p2->m_partner = p1;

		std::cout << p1->m_name << "is now partnered with " << p2->m_name << '\n';
		return true;
	}
	//use lock() to convert weak_ptr to shared_ptr to make it usable
	const std::shared_ptr<Person>getPartner() const
	{
		return m_partner.lock();
	}
	const std::string& getName() const
	{
		return m_name;
	}
};

int main()
{
	auto lucy{ std::make_shared<Person>( "Lucy" ) };
	auto ricky{ std::make_shared<Person>( "Ricky" ) };

	partnerUp( lucy, ricky );
	//don't have to worry about circular dependencies with std::shared_ptr variable "partner"
	//since this is just a local variable inside a function
	auto partner = ricky->getPartner(); //Get shared_ptr to ricky's partner
	std::cout << ricky->getName() << " 's partner is: " << partner->getName() << '\n';
	return 0;
}