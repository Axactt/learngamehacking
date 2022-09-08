#include<iostream>

// capture list by value and by reference fo use objects outside scope of lambda fumntions

int main()
{
	double a {10};
	double b {20};

	
	auto func = [a,b ]() // capture by value 
	{
		std::cout<<"Inner value: "<<a+b<<'\n';

	}; // without parenthesis lambda function won't print


	// capture by value 
	int c {42};
	auto func1 = [c]() // capture by value, a copy of original value,
	{
		std::cout<<"Inner value: "<<c<<" &inner value: "<<&c<<'\n';

	}; 

	// address of inner and outer value different so inner value passed is a copy
	for (size_t i {0}; i<5; ++i)
	{
		std::cout<<"Outer value: "<<c<<" &outer value: "<<&c<<'\n';
		func1(); // calling lambda function here through handle func1
		c=c+1;
	}

	std::cout<<'\n'<<'\n'<<"--------------------"<<'\n';


	// Capture by refernce using only ampersand
	int d {26};
	auto func2 = [&d]() // capture by referrence is a true reference to outer value

	{
		std::cout<<"Inner value: "<<d<<" &inner value: "<<&d<<'\n';

	};

	// address of inner and outer value same
	for (size_t i {0}; i<5; ++i)
	{
		std::cout<<"Outer value: "<<d<<" &outer value: "<<&d<<'\n';
		func2(); // calling lambda function here through handle func2
		d = d+1;
	}

	std::cout<<'\n'<<'\n'<<"--------------------"<<'\n';

	// capture everying outside context of lambda expression by value(copy)
	int c1 {13};
	double d1 {26.13};

	auto func3 = [=]() // syntax [=] used to capture everything outside scope of lambda function by value
	{
		std::cout<<" Inner value: "<<c1<<" &innervalue: "<<&c1<<'\n';
		std::cout<<" Inner value: "<<d1<<" &innervalue: "<<&d1<<"\n";

	};
	for (size_t i {0}; i<5; ++i)
	{
		std::cout<<"Outer value: "<<c1<<" &outer value: "<<&c1<<'\n';
		std::cout<<"Outer value: "<<d1<<" &outer value: "<<&d1<<'\n';
		func3(); // calling lambda function here through handle func3
		c1 = c1+1;
		d1 = d1+1;
	}

	std::cout<<'\n'<<'\n'<<"--------------------"<<'\n';

	// capture everying outside context of lambda expression by reference(&), not a copy
	int c2 {37};
	double d2 {89.13};

	auto func4 = [&]() // syntax [&] used to capture everything outside scope of lambda function by refernce
	{
		std::cout<<" Inner value: "<<c2<<" &innervalue: "<<&c2<<'\n';
		std::cout<<" Inner value: "<<d2<<" &innervalue(d2): "<<&d2<<"\n";

	};
	for (size_t i {0}; i<5; ++i)
	{
		std::cout<<"Outer value: "<<c2<<" &outer value: "<<&c2<<'\n';
		std::cout<<"Outer value: "<<d2<<" &outer value: "<<&d2<<'\n';
		func4(); // calling lambda function here through handle func4
		c2 = c2+1;
		d2 = d2+1;
	}


	return 0;
}