#include<cassert>
#include<iostream>

class Fraction
{
private:
	int m_numerator {};
	int m_denominator {};
public:
	// Default constructor
	Fraction(int numerator = 0, int denominator = 1)
		:m_numerator(numerator), m_denominator(denominator)
	{
		assert(denominator != 0);
	}
	// copy constructor
	Fraction(const Fraction& copy)
		:m_numerator(copy.m_numerator), m_denominator(copy.m_denominator)
	{
		//no need to check for a denominator of 0 here since copy must already be a valid Fraction
		std::cout << "Copy Constructor called\n";
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
void printFraction(const Fraction& f)
{
	std::cout << f;
}

std::ostream& operator<<(std::ostream& out, const Fraction& f1)
{
	out << f1.m_numerator << '/' << f1.m_denominator;
	return out;
}
int main()
{
	/*Although function printFraction() is expecting a Fraction, we’ve given it the integer literal 6 instead.Because Fraction has a constructor willing to take a single integer, the compiler will implicitly convert the literal 6 into a Fraction object.It does this by initializing printFraction() parameter f using the Fraction(int, int) constructor. */

	printFraction(6);
	return 0;
}