#include<memory> // for std::uinique_ptr
#include<iostream>
#include<utility> // for std::move

/*Example of std::unique_ptr passed by value to a function .  std::make_unique() function used to create a unique_ptr for Resource() object. this unique_ptr is passed to function be value by first applying std::move(). evoking move-semantics. The function to which it is passed takes the onership.*/
class Resource
{
public:
	Resource()
	{
		std::cout << "Resource acquired\n";
	}
	~Resource()
	{
		std::cout << "Resource destroyed\n";
	}
	friend std::ostream& operator<<( std::ostream& out, const Resource& res )
	{
		out << "I am a resource";
		return out;
	}
};
void takeOwnership( std::unique_ptr<Resource>res )
{
	if (res)
		std::cout << *res << '\n';
}// the Resource is destroyed here

int main()
{
	auto ptr{std::make_unique<Resource>()};
	// ptr is a variable and is type l-value
	//takeOwnership(ptr); //This pass by value uses copy & doesn't work need to use move semantics
	takeOwnership( std::move( ptr ) ); // ok to use move-semantics bu std::move here
	std::cout << "Ending program\n";
	return 0;
}