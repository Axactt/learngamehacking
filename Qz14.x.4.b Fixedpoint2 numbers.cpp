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
	FixedPoint2() = default;
	FixedPoint2(std::int16_t nonFrac,std::int8_t frac )
		:m_nonFrac{nonFrac}
	{ 
		assert(frac <= 99 && frac >= -99);
		m_frac = frac;
	}
	/*friend float operator+(const FixedPoint2& fixP)
	{
		return { (std::abs(fixP.m_nonFrac)) + (std::abs(static_cast<float>(fixP.m_frac) / 100)) };
	}*/
	//overload the double cast
	operator double() const
	{
		if (m_frac < 0 || m_nonFrac < 0)
		{
			return   -(std::abs(m_nonFrac) + (std::abs(static_cast<double>(m_frac) / 100)) ) ;
			
		}
		else
		{
			return m_nonFrac + (static_cast<double>(m_frac) / 100);
			
		}
	} 
	friend std::ostream& operator << (std::ostream& out, const FixedPoint2& fixP);
	
};

std::ostream& operator<<(std::ostream& out, const FixedPoint2& fixP)
{
	if (fixP.m_frac < 0 || fixP.m_nonFrac < 0)
	{
		out << -(std::abs(fixP.m_nonFrac) + (std::abs(static_cast<double>(fixP.m_frac) / 100))) << '\n';
		return out;
	}
	else
	{
		out << fixP.m_nonFrac + (static_cast<double>(fixP.m_frac) / 100) << '\n';
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

	return 0;
}