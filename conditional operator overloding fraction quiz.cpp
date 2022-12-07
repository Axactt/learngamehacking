#include <iostream>
#include <numeric> // for std::gcd

class Fraction
{
private:
	int m_numerator {};
	int m_denominator {};

public:
	Fraction( int numerator = 0, int denominator = 1 ) :
		m_numerator { numerator }, m_denominator { denominator }
	{
		// We put reduce() in the constructor to ensure any new fractions we make get reduced!
		// Any fractions that are overwritten will need to be re-reduced
		reduce();
	}

	void reduce()
	{
		int gcd { std::gcd( m_numerator, m_denominator ) };
		if (gcd)
		{
			m_numerator /= gcd;
			m_denominator /= gcd;
		}
	}

	friend std::ostream& operator<<( std::ostream& out, const Fraction& f1 );
	friend bool operator==( const Fraction& f1, const Fraction& f2 );
	friend bool operator!=( const Fraction& f1, const Fraction& f2 );
	friend bool operator<( const Fraction& f1, const Fraction& f2 );
	friend bool operator>( const Fraction& f1, const Fraction& f2 );
	friend bool operator>=( const Fraction& f1, const Fraction& f2 );
	friend bool operator<=( const Fraction& f1, const Fraction& f2 );
};
// All conditional operator can be expressed in terms of operator== and operator<
//operator!= can be implemented as !(operator==)
//operator> can be implemented as operator< with the order of the parameters flipped
	//operator>= can be implemented as !(operator<)
	//operator<= can be implemented as !(operator>)
// only implement logic for operator== and opeartor<
// Other four comparison operators can be defined in terms of those two
std::ostream& operator<<( std::ostream& out, const Fraction& f1 )
{
	out << f1.m_numerator << '/' << f1.m_denominator;
	return out;
}
bool operator==( const Fraction& f1, const Fraction& f2 )
{
	return (f1.m_numerator == f2.m_numerator) && (f1.m_denominator == f2.m_denominator);
}
bool operator!=( const Fraction& f1, const Fraction& f2 )
{
	return !(operator==( f1, f2 ));
}
bool operator<( const Fraction& f1, const Fraction& f2 )
{
	
	int transNumf1 { f1.m_numerator * f2.m_denominator };
	int transNumf2 { f2.m_numerator * f1.m_denominator };
	return ((transNumf1 - transNumf2) < 0);
}
bool operator>( const Fraction& f1, const Fraction& f2 )
{
	return (operator<( f2, f1 ));// changed the prarmeter order;used opeartor<
}
bool operator>=( const Fraction& f1, const Fraction& f2 )
{
	return !(operator<( f1, f2 ));

 }

bool operator<=(const Fraction & f1, const Fraction & f2)
{
	return !(operator>( f1, f2 ));
}
int main()
{
	Fraction f1 { 3, 7 };
	Fraction f2 {2, 5 };

	std::cout << f1 << ((f1 == f2) ? " == " : " not == ") << f2 << '\n';
	std::cout << f1 << ((f1 != f2) ? " != " : " not != ") << f2 << '\n';
	std::cout << f1 << ((f1 < f2) ? " < " : " not < " )<< f2 << '\n';
	std::cout << f1 << ((f1 > f2) ? " > " : " not > ") << f2 << '\n';
	std::cout << f1 << ((f1 >= f2) ? " >= " : " not >= ") << f2 << '\n';
	std::cout << f1 << ((f1 <= f2) ? " <= " : " not <= ") << f2 << '\n';
	return 0;
}