#include<iostream>

# define _(a,b)  a = (decltype(a))(b);  // crazy define macro

int func(int a,int b)
{
	return a+b;
}
int main()
{
	int a {6};
	int b {9};
	int (*Ptralias)(int,int) = nullptr;
	 _(Ptralias,&func);
	//using Ptralias = int(*)(int,int);
	 
	// Ptralias funcPtr = &func;

	std::cout<<Ptralias<<'\n'; // printing address through function pointer
	std::cout<<&func<<'\n'; // directly printing  address of function
	std::cout<<Ptralias(a,b)<<'\n'; // calling function through function pointer
	std::cout<<func(a,b)<<'\n'; // calling function directly

    return 0;
}