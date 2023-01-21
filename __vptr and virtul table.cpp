class Base
{
public:
	virtual void function1()
	{
	}
	virtual void function2()
	{

	}
}; 
class D1 :public Base
{
public:
	void function1()override
	{
	}
};
class D2 :public Base
{
public:
	void function2()override
	{
	} 
};
int main()
{
	D1 d1 {}; 
	Base* dPtr = &d1; //Base pointer set to d1 derived object
	//As dPtr is a base pointer, it only points to Base portion of D1
	//however: __vptr is in the Base portion of the class, 
	//sp dptr has access to this pointer
	//Finally note that dPtr->__vptr points to D1 virtual table
	//Consequently even though dPtr is of type Base,
	//it still has access to D1's virtual table (through __vptr)
	// D1 virtual table contains most-derived version of virtual functions
	//Which class object D1 can access when class object D1 is constructed
	dPtr->function1(); 
	return 0; 
}