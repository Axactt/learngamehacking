#include <iostream>
class Points
{
private:
	double m_x {};
	double m_y {};
	double m_z {};
public:
	Points(double x=0.0,double y=0.0,double z=0.0):m_x{x},m_y{y},m_z{z}{ }

	//convert point into its negative equivalent
	Points operator-()const;

	//Return true if Points is set at origin
	bool operator!()const;
	friend std::ostream& operator<<( std::ostream& out, const Points& point );

	double getX()const
	{
		return m_x;
	}
	double getY()const
	{
		return m_y;
	}
	double getZ()const
	{
		return m_z;
	}

};

Points Points::operator-()const
{
	// multiple variables can be returned in a single statement in form of class object by defining suitable/creative constructor in class definition
	// List initializtion sees the return type and initializes temporary object of form Points
	return { -m_x,-m_y,-m_z };

}
bool Points::operator!() const
{
	/*if (m_x == 0.0 && m_y == 0.0 && m_z == 0.0)
		return true;
	else
		return false;  */

	return (m_x == 0.0 && m_y == 0.0 && m_z == 0.0);

}

std::ostream& operator<<( std::ostream& out, const Points& point )
{
	out << "Points: (" << point.m_x << ',' << point.m_y << ',' << point.m_z << ')';
	return out;
}

int main()
{
	Points point1 {};
	Points point2 { 3.0,4.0,5.0 };
	if (!point1)
		std::cout << "point is set at the origin.\n";
	else
		std::cout << "point is not set at the origin.\n";
	if (!point2)
		std::cout << "point is set at the origin.\n";
	else
		std::cout << "point is not set at the origin.\n";
	// overloading ostream opertaor << and operator -
	std::cout << "The oppsosite end of point2 is: " << -point2 << '\n';

	return 0;

}