#include<iostream>
#include<memory>
#include<utility> // std::move

/* it’s better to just pass the resource itself (by pointer or reference, depending on whether null is a valid argument). This allows the function to remain agnostic of how the caller is managing its resources. To get a raw resource pointer from a std::unique_ptr, you can use the get() member function:

*/
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

void useResource( Resource* res )
{
	if (res)
		std::cout << *res << '\n';
	else
		std::cout << "No resource\n";
}
int main()
{
	auto ptr{ std::make_unique<Resource>() };

	useResource( ptr.get() ); //note get() used here to get a pointer to the Resource

	std::cout << "Ending program\n";
	return 0;

} // the resoutce is destroyed here