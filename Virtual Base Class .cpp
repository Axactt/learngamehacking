#include <iostream>

class PoweredDevice
{
public:
	PoweredDevice( int power )
	{
		std::cout << "PoweredDevice: " << power << '\n';
	}
};
class Scanner :virtual public PoweredDevice//note:powerdDevice is now a virtual base class
{
public:
	Scanner( int scanner, int power )
		:PoweredDevice { power }//this line is required to create scanner objects , but ignored in thsi case
	{
		std::cout << "Scanner: " << scanner << '\n';
	}
};
class Printer :virtual  public PoweredDevice // note: PoweredDevice is now a virtual base class
{
public:
	Printer( int printer, int power )
		:PoweredDevice { power } // This line is required to create printer objects, but ignored  in this case
	{
		std::cout << "printer: " << printer << '\n';
	}
};

class Copier : public Scanner, public Printer
{
public:
	Copier( int scanner, int printer, int power )
		:PoweredDevice{power},// Powered Device constructed here
		Scanner { scanner,power }, Printer { printer,power }
	{
		// In multiple inheritance of virtual base class
		// constructor of virtual base class has to be provided separately 
		//for most-derived class as shown above 
		// virtual base class will,be constructed only once
		//Most-derived class responsible for construction virtual base class
		//1. all class inheriting virtual base classs would have a virtual Table
		//even if they normally wouldn,t have one.Instances larger by a pointer
		//IMP:: As scannera nd printer derive virtually from PoweredDevice, Copier
		//Will only be one PoweredDevice subobject. Scannera and Printer both need to
		//know how to find that "single PowerdDevice sub-object", so they can access
		//its memebers(because after all they are drived from it)
		//This is done through virtual-table arrangement which stores the offset 
		//From each sub-Class to the powered device Sub-object.

	}
};

int main()
{
	Copier c { 1,2,3 };
	return 0;
}