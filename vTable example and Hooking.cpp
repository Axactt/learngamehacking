#include<iostream>
class cX
{
public:
	virtual void function1()
	{
		std::cout<<"Function1 Called"<<'\n';
	}

};
class cY
{
	public:
		virtual void function2()
		{
			std::cout<<"Function2 called "<<'\n';
		}
};

int main()
{
	cX* x = new cX {}; // creating new instance of class object X on heap

	cY* y = new cY {};// creating new instance of class Object Y on heap
	
	long addrVtable = *(long*) (x);
	addrVtable = *((long*) (addrVtable+0x0));

	long addrFunc2 = *((long*) (y));
	addrFunc2 = *((long*) (addrFunc2+0x0));
	
	// Hooking part : address of original addrVatable (funtion1) fetched
	//Address changed internally to point to addrFunc2 of new function

	long* address = &addrVtable; //getting address of class x vtable
	
	*address = addrFunc2; // changing address of class x vtable with address of new function
	// remaining part is setting a function pointer to vtable address of function1(i.e addrVtable)
	// using that function pointer of addrVtable to call function at that address
	// but as we have changed this address by dereferencing(at line 31) to point to new addrfuntion2 our function2 wiil be called instead

	int(*funcPtr)() = (int(*)())addrVtable;// setting function pointer for vTable address of virtual function1
	funcPtr();// calling the  function2 using function pointer set at addrVtable of function 1

	int z {}; // a way to pause the program with user input
	std::cin>>z;
	return 0;
}