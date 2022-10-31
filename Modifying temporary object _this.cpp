#include <iostream>
class Cents
{
private:
	int m_cents {};
public:
	// explicit use of this can be done to find address of anonymous objects and manipulate it
	Cents(int cents): m_cents {cents}
	{
		std::cout<<"Constructing cents with address "<<this<<'\n';
	}
	int getCents()const
	{
		return m_cents;
	}
	int incrementCents()
	{
		(this->m_cents)++;
		return getCents();
	}
	
};


int main()
{
	Cents cents1 {6};
	Cents cents2 {8};
	std::cout<<Cents(9).getCents()<<'\n';// print address and value
	std::cout<<Cents(13).incrementCents()<<'\n';// increments cents and print address and new value 6
	return 0;
}
