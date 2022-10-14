#include<iostream>

#ifndef POINT3D_H
#define POINT3D_H
// declaration provided to satisfy use of parameter moveByVector(const Vector3d& v);
//in function declaration  at line 26 otherwise won't know what is  type of Vector3d is???

class Vector3d;

class Point3d
{
private:
	double m_x {};
	double m_y {};
	double m_z {};

public:
	Point3d(double x = 0.0,double y = 0.0,double z = 0.0);
		

	void print() const;
	// use of any undefined class Type in any function declaration
	// can just be satisfied by declartion of class.
	// fulll definition not required
	void moveByVector(const Vector3d& v);

};

#endif
