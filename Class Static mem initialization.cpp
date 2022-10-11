#include<iostream>
#include<vector>
class MyClass
{
public:
	static std::vector<char> s_myChars;
};
// Initializing a static member variable which reqires code_execution to initialize
// As C++ does not have concept of static constructors
// Lambda function used to initialize static member variables
std::vector<char> MyClass::s_myChars =
	
[]()// lambda without capture-clause and parameter list

	{
		std::vector<char> v {};
		for (char ch {'a'}; ch<='z'; ++ch)
			v.push_back(ch);
		return v;

}(); // Call Lambda right away to do initialization with return_type same as "v";

int main()
{
	return 0;
}