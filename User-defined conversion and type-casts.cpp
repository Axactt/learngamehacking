#include<iostream>

class Cents
{
private:
	int m_cents;
public:
	Cents(int cents=0): m_cents{cents}{ }

	operator int() const // overloading int typecast
	{
		// Typename can be explicitly provided with brace-initializer brackets
		return int { m_cents };
	}

	int getCents()const
	{
		return m_cents;
	}
	void setCents(int cents)
	{
		m_cents = cents;
	}

};
class Dollars
{
private:
	int m_dollars;
public:
	Dollars(int dollars=0)
		:m_dollars{dollars}{ }
	// Allows us to convert Dollars into Cents
	operator Cents()const
	{
		// Cents type can be explicitly stated here
		return Cents { m_dollars * 100 }; // return Cents{}
	}
};

void printCents(Cents cents)
{
	std::cout << cents; // Cents will be implicitly cast to an int here
}
int main()
{
	Cents cents { 7 };
	int c { static_cast<int>(cents) };
	c;
	Dollars dollars { 9 };
	printCents(dollars); // dollars will be implicitly cast to a Cents here 
	std::cout << '\n';
	return 0;
}