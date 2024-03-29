#include<cassert>
#include<iostream>
class Fraction
{
private:
	int m_numerator { 0 };
	int m_denominator { 1 };
public:
	// Deafault constructor
	Fraction(int numerator = 0, int denominator = 1)
		:m_numerator { numerator }, m_denominator { denominator }
	{
		assert(denominator != 0);
	}
	// Copy constructor
	Fraction(const Fraction& copy) = delete;
	// Overloaded assignemnet
	Fraction& operator= (const Fraction& fraction) = delete;//no copies through assignement
	friend std::ostream& operator<<(std::ostream& out, const Fraction& f1);
};

std::ostream& operator<<(std::ostream& out, const Fraction& f1)
{
	out << f1.m_numerator << '/' << f1.m_denominator;
	return out;
}
int main()
{
	Fraction fiveThirds { 5,3 };
	Fraction f;
	f = fiveThirds; // compile error, operator= has been deleted
	std::cout << f;
	return 0;
}