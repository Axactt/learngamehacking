#include<functional>
#include<iostream>

int foo(int z)
{
	return z;
}

int goo( int x )
{
	return x;
}

int zoo( int x )
{
	return x;
}

int main()
{ 
	// std::function can only call function through pointer by implicit dereference
	using fcnptrAlias = std::function<int( int )>; // usinf alias of std::function<int(int,int)>
	using fcnptrAliasRaw = int(*)(int); // using raw original syntax of function pointer int(*)(int) alias
	fcnptrAliasRaw fcnPtr { foo };
	fcnPtr = goo;

	auto fcnPtr1 { &zoo }; //auto type inferences used in function pointer variable


	std::cout << (*fcnPtr)( 5 );

	std::cout << (*fcnPtr)( 6);

	std::cout <<  ( * fcnPtr1)(8); // implicit and explicit both dereferencing can be done

	return 0;


}