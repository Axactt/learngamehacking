#include<iostream>
class Digit
{
private:
	int m_digit;
public:
	Digit (int digit=0)
		:m_digit{digit}{ }
	// Unary overloaded operator implemented as member function
	//Modification of class object is done.
	Digit& operator++(); // return by reference employed,prefix has no parameter
	Digit& operator--();// return by reference, prefix has no prameter

	Digit operator++( int ); // return by value, postfix has int parameter
	Digit operator--( int ); // return by value, postfix has int parameter
	friend std::ostream& operator<<( std::ostream& out, const Digit& d );

};
// Class object retured as non-const l-value reference 
// So we return a derefenced *this as the non-const and modified class object
// so a return by (non-const  l-value refernce)
Digit& Digit::operator++() 
{
	if (m_digit == 9)
		m_digit = 0;
	else
	++m_digit;

	return *this; 
}


// overloaded operator being member takes Class instance pointer implicitly
Digit& Digit::operator--()
{
	// If number is already zero, wrap around to 9
	if (m_digit == 0)
		m_digit = 9;
	//otherwise just decrement to next number
	else
	--m_digit;

	return *this;
}

//int parameter means this is postfix operator++
Digit Digit::operator++( int )
{
	// Create a temporary variable with our current digit
	Digit temp { *this };

	//Use prefix operator to incement this digit
	++(*this); // apply operator

	// return temporary result
	return temp;// return saved state

}
//int parameter means this is postfix operator++
Digit Digit::operator--( int )
{
	// Create a temporary variable with our current digit
	Digit temp { *this };

	//Use prefix operator to decrement this digit
	--(*this); // apply operator

	// return temporary result
	return temp;// return saved state

}



std::ostream& operator<<( std::ostream& out, const Digit& d )
{
	out << d.m_digit ;
	return out;

}

int main()
{
	Digit digit(5 );

	std::cout << digit;
	std::cout << ++digit;// calls Digit& Digit::operator++();

	std::cout << digit++; // calls Digit Digit::operator++(int);

	std::cout << digit;
	std::cout << --digit;// Calls Digit& Digit::operator--();

	std::cout << digit--;// calls Digit::operator--(int);

	std::cout << digit;

	return 0;
}