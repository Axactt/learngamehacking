#include<iostream>
#include<algorithm>
#include<vector>
class Shape
{
public:
	virtual std::ostream& print( std::ostream& out ) const = 0;
	//Delegate responsibility for printing to virtual member function print
	//as Shape is a base class, the refrences of SHape to derived will be up-casted
	//but as print is a virtual function, most derived function version will be applied
	//Each derived class will be having its print version to handle its cases
	friend std::ostream& operator<<( std::ostream& out, const Shape& shape )
	{
		return  shape.print( out );
	}

	virtual ~Shape() = default;
};


class Point
{
private:
	int m_x {};
	int m_y {};
public:
	Point( int x, int y )
		:m_x { x }, m_y { y }
	{
	}


	friend std::ostream& operator<<( std::ostream& out, const Point& p )
	{
		return out << "Point(" << p.m_x << ", " << p.m_y << ')';
	}
};
class Triangle : public Shape
{
private:
	Point m_p1;
	Point m_p2;
	Point m_p3;
public:
	Triangle( const Point& p1, const Point& p2, const Point& p3 )
		:m_p1 { p1 }, m_p2 { p2 }, m_p3 { p3 }
	{
	}
	// Here our override print() function to handle the Derived case 
	//Note no need to overload operator<< again
	std::ostream& print( std::ostream& out ) const override
	{
		out << "Triangle(" << m_p1 << ", " << m_p2 << ", " << m_p3 << ')' << '\n';
		return out;
	}
	
};

class Circle : public Shape
{
private:
	Point m_center;
	int m_radius {};
public:
	Circle( const Point& center, int radius )
		:m_center { center }, m_radius { radius }
	{
	}
	int getRadius() const
	{
		return m_radius;
	}
	// Here our override print() function to handle the Derived case 
	//Note no need to overload operator<< again
	std::ostream& print( std::ostream& out ) const override
	{
		out << "Circle(Point(" << m_center << ", radius " << m_radius << ')' << '\n';
		return out;
	}
	
};
// Function to get max value out of the array of Base object pointer
int  getLargestRadius( const  std::vector<Shape*>& v )
{
	int maxRadius { 0 };
	// Loop through all the shapes in the vector
	for (const auto* element : v)
	{
		// Ensure that the pointer is of circle by doing null-pointer check
		if (auto * c { dynamic_cast<const Circle*>(element) })
		{
			// use of std::max algorithm to find largest element
			maxRadius = std::max( maxRadius, c->getRadius() );
		}
	}
	
	return maxRadius;
}

int main()
{
	// Upcasting of derived object* pointer to Base* pointer
	std::vector<Shape*> v {

		new Circle{Point{1,2},7},
		new Triangle{Point{1,2},Point{3,4},Point{5,6}},
		new Circle {Point{7,8},3}
	};

	for (const auto& s : v)
	{
		//if (s) // Null pointer check before derefernce
			//s->print( std::cout );// print function takes parameter //std::ostream& out
		std::cout << *s << '\n'; // s will be a shape*
	}

	std::cout << " The largest radius is: " << getLargestRadius( v ) << '\n';


	// deleting each of the dynamically allocated vector element here
	for (const auto& e : v)
		delete e;
	return 0;

}