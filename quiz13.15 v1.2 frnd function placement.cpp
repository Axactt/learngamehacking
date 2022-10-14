#include <iostream>
// class declaration to satisfy use of parameter Vector3d& v in Point3d class memeber function
// This member function moveByvector is to be used as a friend function in class Vector3d
class Vector3d; 

class Point3d
{
private:
	double m_x {};
	double m_y {};
	double m_z {};

public:
	Point3d(double x = 0.0,double y = 0.0,double z = 0.0)
		: m_x {x},m_y {y},m_z {z}
	{

	}
	void print() const
	{
		std::cout<<"Point("<<m_x<<" , "<<m_y<<" , "<<m_z<<")\n";
	}

	void moveByVector(const Vector3d& v);
	
};
// Class Vector3d has to be placed below class Point3d as friend function from Point3d used with class Vector3d
// The declaration of friend function moveByVector should should see full class definition of class Point3d, of which it is originally part of
//Also definition of function moveByVector (declared friend of Vector3d) should see full class definition class definition of class Point3d, of which it is originally part of

class Vector3d
{
private:
	double m_x {};
	double m_y {};
	double m_z {};

public:
	Vector3d(double x = 0.0,double y = 0.0,double z = 0.0)
		: m_x {x},m_y {y},m_z {z}
	{

	}

	void print() const
	{
		std::cout<<"Vector("<<m_x<<" , "<<m_y<<" , "<<m_z<<")\n";
	}
	friend void Point3d::moveByVector(const Vector3d& v);

};

void Point3d::moveByVector(const Vector3d& v)
{
	m_x += v.m_x;
	m_y += v.m_y;
	m_z += v.m_z;

}

int main()
{
	Point3d p {1.0,2.0,3.0};
	Vector3d v {2.0,2.0,-3.0};

	p.print();
	p.moveByVector(v);
	p.print();

	return 0;
}