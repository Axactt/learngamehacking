#include<iostream>
#include<exception>
#include<stdexcept>
class Fraction
{

private:
int	m_num {};
int	m_den {};
public:
	Fraction(int num,int den)
		:m_num{num},m_den{den}
	{ 
	
	}
	friend std::ostream& operator<<( std::ostream& out, const Fraction& frac )
	{
		out<<"Fraction: "<<frac.m_num<<"/"<< frac.m_den <<"\n";
		return out;
    }

};

int main()
{
	std::cout << "Enter the numerator: ";
	int num {};
	std::cin >> num;
	try
	{
		std::cout << "Enter a denominator: ";
		int den {};
		std::cin >> den;
		if (den == 0)
			throw std::runtime_error( "Invalid denominator" ); // cannot throw std::exception directly
		std::cout << Fraction { num,den } << '\n';

	}
	catch (const std::exception& exception)
	{
		std::cerr << "Standeard exception:" << exception.what();
	}
}