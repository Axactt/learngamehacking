// OverLoading IO operators using friend function to class
//Overloading input operator(>>) and output operator(<<) using return by reference and passing left hand operand parameter by refernce.
// return of overload function operator>>() and operator<<() are refernces to ostream and istream objects respectively. (i.e std::ostream& out  and std::istream& in respectively)
#include<iostream>
class Point
{
private:
	double m_x {};
	double m_y {};
	double m_z {};
public:
	Point (double x=0.0,double y=0.0,double z=0.0)
		:m_x{x},m_y{y},m_z{z}{ }
	friend std::ostream& operator<<( std::ostream& out, const Point& point );
	friend std::istream& operator>>( std::istream& in, Point& point );
};

std::ostream& operator<<( std::ostream& out, const Point& point )
{
	// Since opertor<< is a friend of the Point class, we can access Point's members directly
	// actual output done in following line
	out << "Point(" << point.m_x << "," << point.m_y << "," << point.m_z << ')';
	return out;// return std::ostream so we can chain calls to operatot<<
}
std::istream& operator>>( std::istream& in, Point& point )
{
	// Since operator>> is a friend of the Point class, we can access Point's members diredctly
	// Note that parameter point must be non-const so we can modify the class members with the input values
	in >> point.m_x;
	in >> point.m_y;
	in >> point.m_z;
	return in;
}
int main()
{
	Point point1 {};
	std::cin >> point1;

	std::cout << point1 <<  '\n';
	return 0;
}