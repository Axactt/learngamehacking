#include<iostream>
#include"Point3d.h"
#ifndef VECTOR3D_h
#define VECTOR3D_h

class Vector3d
{
private:
	double m_x {};
	double m_y {};
	double m_z {};

public:
	Vector3d(double x = 0.0,double y = 0.0,double z = 0.0);
	

	void print() const;
	
	// friend function in Vector3d moveByVector(member of point3d) 
	// should see full definition of point3d before declared & defined oustside class Point3d

	friend void Point3d::moveByVector(const Vector3d& v);
};
#endif