#include<iostream>
#include<limits>

int main()
{
	int age{};
	while (true)
	{
		std::cout << "Enter your age: ";
		std::cin >> age;
		if (std::cin.fail()) // no extraction took place
		{
			std::cin.clear(); // reset the state bits back to goodbit so we can use ignore()
	std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );//clear out the bad input from the stream
	continue; // try again
		}
		//clear out any additional input from the stream
		std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
		if (std::cin.gcount() > 1)// if we clear more than one additional character
		{
			continue;//we'll consider this input to be invalid
		}
		if (age <= 0) // make sure age is 
			continue;
		break;
	}
	std::cout << " You entered: " << age << '\n';
}