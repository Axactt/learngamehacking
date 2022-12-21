#include<cassert>
#include<iostream>
class Fraction
{
private:
	int m_numerator {};
	int m_denominator {};
public:
	//Default constructor
	Fraction(int numerator = 0, int denominator = 1)
		: m_numerator { numerator }, m_denominator { denominator }
	{
		assert(denominator != 0);
	}
	// copy constructor
	Fraction(const Fraction& copy)
		:m_numerator { copy.m_numerator },
		m_denominator { copy.m_denominator }
		// Note we acn access the private members of parameter copy directly,
		// because we're inside the copy class
	{
		// No need to check for a denominator of 0 here since copy must always be a vald fraction
		std::cout << " Copy constructor called\n";
	}

	friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);
	int getNumerator()
	{
		return m_numerator;
	}
	void setNumerator(int numerator)
	{
		m_numerator = numerator;
	}
};

std::ostream& operator<<(std::ostream& out, const Fraction& f1)
{
	out << f1.m_numerator << '/' << f1.m_denominator;
	return out;
}

Fraction makeNegative(Fraction f) // ideally we should do this by const refernce
{
	f.setNumerator(-f.getNumerator());
	return f;
}

int main()
{
	Fraction fiveThirds { 5,3 };// direct initialize ,calls Fraction(int,int) ctor

	// Copy constructor cannot be ellided, So copy constructor called twice
	// first copy constructor call happens fiveThirds pass as an argument into makeNegative() parameter f.
	// second copy constructor call happens when return value from makeNegative()is passed back to main().
	// Both arguments passed by value and return value cannot be ellided
	std::cout << makeNegative(fiveThirds);
	return 0;
	
}