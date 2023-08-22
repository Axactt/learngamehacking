#include<iostream>
//!extern "C" namespace prevents name-mangling by the c++ compiler
extern "C"
{

	
	void asmFunc(void);

}

int main()
{

	printf( "Calling assembly gadget asmFunc:\n" );
	asmFunc();
	printf( "Returned successfully from asmFunc!\n" );
	return 0;
}