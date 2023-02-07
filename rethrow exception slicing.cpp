#include<iostream>
#include<string>
class Base
{
public:
	Base(){ }
	virtual void print()
	{
		std::cout << "Base";
	}
};
class Derived :public Base
{
public:
	Derived(){ }
	void print()override
	{
		std::cout << "Derived";
	}
};
int main()
{
	try
	{
		try{
			
			throw Derived {};

		   }
		catch (Base& b)
		{
			std::cout << "Caught Base b, whcih is actually a ";
			b.print();
			std::cout << "\n";
			//throw b; // the derived gets sliced here==shouldn't be done
			//but if we remove object identifier(b) and just use "throw"
			throw; //note: we're now rethrowind an object here
/*When rethrowing the same exception, use the throw keyword by itself*/
		}
	}
	catch (Base& b)
	{
		std::cout << "Caught base b, whcih is actually a ";
		b.print();
		std::cout << '\n';
	}
	return 0;
}