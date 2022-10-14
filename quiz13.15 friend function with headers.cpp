
#include"Point3d.h"
#include"Vector3d.h"

// for any member function declaration or definition to be valid
// It should have seen the full definition of class  if it is declared outside class
// using any scope resolution operator


int main()
{
	Point3d p {1.0,2.0,3.0};
	Vector3d v {2.0,2.0,-3.0};

	p.print();
	p.moveByVector(v);
	p.print();

	return 0;
}