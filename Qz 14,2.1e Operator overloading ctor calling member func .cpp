#include<iostream>
#include<numeric> //for std::gcd greatest common divisor
class Fraction
{
private:
	int m_num {};
	int m_den { 1 };
	// a normal member function to do additional setup-task inside constructor
	void reduce()
	{
		int factor { std::gcd( m_num, m_den ) };
		if (factor)// to make sure no division by zero
		{
			m_num /= factor;
			m_den /= factor;
		}

	}
public:
	Fraction( int num, int den = 1 ) :m_num { num }, m_den { den }
	{
		// Constructor calling a set-up type normal -NON-Constructor member function 
		//Non-constructor member function is called inside constructor body
		// If another constructor had been delegated or called by a constructor 
		// This should have been done in member initialization list of constructor 
		// This function is not a constructor so can only do assignement(not-INITIALIZATION)
		// Chapter 13.8 Learncpp
		reduce(); 

	}
	void print()const
	{
		std::cout << m_num << '/' << m_den << '\n';
	}
	

	friend Fraction operator*( const Fraction& f1, const Fraction& f2 );


		friend Fraction operator*( const Fraction& f, int value );

		friend Fraction operator*( int value, const Fraction& f );  


};
Fraction operator*(const  Fraction& f1, const Fraction& f2 )
{
	int numMultiply { f1.m_num * f2.m_num };
	int denMultiply { f1.m_den * f2.m_den };
	return { numMultiply,denMultiply };
}
Fraction operator*(const Fraction& f, int value)
{
	int numMultiply { f.m_num * value };
	int denMultiply { f.m_den };
	return { numMultiply,denMultiply };
}
Fraction operator*( int value, const Fraction& f )
{
	// using previoulsy overloded operator*(Fraction,int) definition
	return { f * value };
}  
int main()
{
	Fraction f1 { 2, 5 };
	f1.print();

	Fraction f2 { 3, 8 };
	f2.print();

	Fraction f3 { f1 * f2 };
	f3.print();

	Fraction f4 { f1 * 2 };
	f4.print();

	Fraction f5 { 2 * f2 };
	f5.print();

	Fraction f6 { Fraction{1, 2} *Fraction{2, 3} *Fraction{3, 4} };
	f6.print();

	Fraction f7 { 0, 6 };
	f7.print();

	return 0;
}