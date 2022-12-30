#include<iostream>
#include<cstdint>
#include<cassert>
#include<cmath>
class FixedPoint2
{
private:
	std::int16_t m_nonFrac {};
	std::int8_t m_frac {};
public:
	
	FixedPoint2(std::int16_t nonFrac=0,std::int8_t frac=0 )
		:m_nonFrac{nonFrac}
	{ 
		assert(frac <= 99 && frac >= -99);
		m_frac = frac;
	}
	
	//overload the double cast
	operator double() const
	{
		if (m_frac < 0 || m_nonFrac < 0)
		{
			return   -(std::abs(static_cast<double>(m_nonFrac)) + (std::abs(static_cast<double>(m_frac) / 100)) ) ;
			
		}
		else
		{
			return static_cast<double>(m_nonFrac) + (static_cast<double>(m_frac) / 100);
			
		}
	} 
	friend std::ostream& operator << (std::ostream& out, const FixedPoint2& fixP);
	
};

std::ostream& operator<<(std::ostream& out, const FixedPoint2& fixP)
{
	if (fixP.m_frac < 0 || fixP.m_nonFrac < 0)
	{
		out << -(std::abs(static_cast<double>(fixP.m_nonFrac)) + (std::abs(static_cast<double>(fixP.m_frac) / 100))) << '\n';
		return out;
	}
	else
	{
		out << static_cast<double>(fixP.m_nonFrac) + (static_cast<double>(fixP.m_frac) / 100) << '\n';
		return out;
	}

}
int main()
{
	
	FixedPoint2 a { 34, 56 };
	std::cout << a << '\n';

	FixedPoint2 b { -2, 8 };
	std::cout << b << '\n';

	FixedPoint2 c { 2, -8 };
	std::cout << c << '\n';

	FixedPoint2 d { -2, -8 };
	std::cout << d << '\n';

	FixedPoint2 e { 0, -5 };
	std::cout << e << '\n';

	std::cout << static_cast<double>(e) << '\n';
	
	// Handle cases where the argument is representable directly
	/*FixedPoint2 a {0.01};
	std::cout << a << '\n';

	FixedPoint2 b { -0.01 };
	std::cout << b << '\n';

	// Handle cases where the argument has some rounding error
	FixedPoint2 c { 5.01 }; // stored as 5.0099999... so we'll need to round this
	std::cout << c << '\n';

	FixedPoint2 d { -5.01 }; // stored as -5.0099999... so we'll need to round this
	std::cout << d << '\n';

	// Handle case where the argument's decimal rounds to 100 (need to increase base by 1)
	FixedPoint2 e { 106.9978 }; // should be stored with base 107 and decimal 0
	std::cout << e << '\n';

	FixedPoint2 f { 1.9 }; // make sure we handle single digit decimal
	std::cout << f;*/


	return 0;
}