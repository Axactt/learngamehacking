#include <iostream>
#include <string>
#include <string_view>

class Ball
{
private:
	std::string m_color{"black"}; // for case 3: Ball{20}
	double m_radius;

public:
	

	// Constructor1 with only radius parameter (color will use default value) (
	Ball(double radius): m_radius{radius}
	{
		
	}

	// Deafult Constructor2 with both color and radius parameters and default initialized arguments(for case 1 and case 4)
	Ball(std::string_view color="black",double radius=10.0)
		:m_color {color},
		m_radius {radius}
	{

	}

	void print()
	{
		std::cout<<"color: "<<m_color<<", radius: "<<m_radius<<'\n';
	}
};

int main()
{
	Ball def;//Case1: calls default constructor with pre-initialized default argument values
	def.print();

	Ball blue {"blue"}; // case 2: second argument radius default initialzed from deafult constructor 2
	blue.print();

	Ball twenty {20.0}; // case 3: as default argument work only for rightmost one
	twenty.print();

	Ball blueTwenty {"blue",20.0}; // case 4
	blueTwenty.print();

	return 0;
}