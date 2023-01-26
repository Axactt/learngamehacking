#include<iostream>

constexpr int moo()
{
	return 5;
}
//function-pointer non-type constexpr parameter
template<int(*T)()>
constexpr int boo()
{
	return T();
}

int main()
{
	// compiler doesn't have to know what the actual memory address is
	//as it can essentially  do all the substitutions at compile time
	constexpr int val { boo<moo>() };
	std::cout << val;
}