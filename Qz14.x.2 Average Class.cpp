#include<iostream>
#include<cstdint>
class Average
{
private:
	std::int32_t m_sum {};
	std::int8_t m_count {};
	//double m_result {};
public:
	Average() = default;
	Average(std::int32_t sum, std::int8_t count = 0)
		:m_sum { sum }, m_count { count }
	{

	}
	Average& operator+=(const Average& average)
	{
		m_sum += average.m_sum;
		++m_count;
		//m_result = static_cast<double>( m_sum )/ m_count;
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& out, const Average& avg);
};

std::ostream& operator<<(std::ostream& out, const Average& avg)
{
	out << ((static_cast<double>(avg.m_sum)) / avg.m_count);
	return out;
}
int main()
{
	Average avg {};

	avg += 4;
	std::cout << avg << '\n'; // 4 / 1 = 4

	avg += 8;
	std::cout << avg << '\n'; // (4 + 8) / 2 = 6

	avg += 24;
	std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

	avg += -10;
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

	(avg += 6) += 10; // 2 calls chained together
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

	Average copy { avg };
	std::cout << copy << '\n';

	return 0;
}