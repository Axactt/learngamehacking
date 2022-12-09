#include <iostream>
#include <string>
#include <string_view>
#include<algorithm>
#include<vector>

class Car
{
private:
	std::string m_make;
	std::string m_model;

public:
	Car( std::string_view make, std::string_view model )
		: m_make { make }, m_model { model }
	{
	}
/*
	friend bool operator== ( const Car& c1, const Car& c2 );
	friend bool operator!= ( const Car& c1, const Car& c2 );  */
	friend std::ostream& operator<<( std::ostream& out, const Car& car )
	{
		out << "(" << car.m_make << " , " << car.m_model << ")" << '\n';
		return out; 
	}

	//  operator< is used inherently by std::sort algorithm to arrange elements of container in ascending order
	// We overloaded operator<() to take Car class object as operand
	// The comparison and sorting is done as per our requirements
	friend bool operator<( const Car& c1, const Car& c2 )
	{ 
		//if ((c1.m_make < c2.m_make) )
			//return true;
		if (c1.m_make == c2.m_make)
			return(c1.m_model < c2.m_model);
		else
			return(c1.m_make < c2.m_make);
	}
};
int main()
{
	std::vector<Car> cars {
	  { "Toyota", "Corolla" },
	  { "Honda", "Accord" },
	  { "Toyota", "Camry" },
	  { "Honda", "Civic" },
		{"Ford","Endeavour"},
		{"Ford","Eco-Sport"},
		{"LandRover","RangeRover"},
		{"LandRover","Defender"}
	};

	std::sort( cars.begin(), cars.end() ); // requires an overloaded operator<

	for (const auto& car : cars)
		std::cout << car << '\n'; // requires an overloaded operator<<

	return 0;
}