#include <iostream>
#include<cmath>

class Point2d
{
private:
	double m_x {};
	double m_y {};
public:
	Point2d() = default;
	Point2d( double x, double y ) :m_x { x }, m_y { y } 
	{

	}
	void print() 
	{
		std::cout << "Point2d (" << m_x << ", " << m_y << ")" << '\n';

    }
	double distanceTo( const Point2d& source ) const;
	
	 friend double distanceFrom( const Point2d& source1, const Point2d& source2 ); // friend function declaration
};
double Point2d::distanceTo( const Point2d& source ) const
{
	double xDist { ((m_x) -source.m_x) * ((m_x) -source.m_x) };
	double yDist { ((m_y) -source.m_y) * ((m_y) -source.m_y) };
	double distanceTo { std::sqrt( xDist + yDist ) };
	return distanceTo;
}

double distanceFrom( const Point2d& source1,const Point2d& source2 ) // friend function for class point2d(no scope resolution operator)
{
	double xDist { (source1.m_x -source2.m_x) * (source1.m_x - source2.m_x) };
	double yDist { (source1.m_y - source2.m_y) * (source1.m_y - source2.m_y) };
	double distanceFrom { std::sqrt( xDist + yDist ) };
	return distanceFrom;
}

int main()
{
	Point2d first {};
	Point2d second { 3.0,4.0 };
	first.print();
	second.print();
	std::cout << "Distance between two points: " << first.distanceTo( second )<<'\n';
	std::cout << "Distance between two points: " << distanceFrom( first, second )<<'\n';
	return 0;
}