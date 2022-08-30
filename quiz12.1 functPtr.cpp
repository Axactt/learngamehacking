#include<iostream>
#include<limits>
#include<functional> // for std::function

using ArithmeticFunction = std::function<int( int, int )>; // defining type alias for function pointer of function with return_typ int and two parameters int

void ignoreLine()
{
	std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
}

int getInt()
{
		while (true) // loop untill user enters a valid input
		{
			std::cout << " Enter an integer value: ";
			int x {};
			std::cin >> x;

			if (std::cin.fail())
			{
				std::cin.clear();
				ignoreLine();
				std::cerr << " Oops invalid input! \n";
			}
			else
			{
				ignoreLine();
				return x;
			}
		}
}

char getOperator()
{
	while (true) // loop untill user enters valid input
	{
		std::cout << " Enter one of the following: +,-,* or / : ";
		char op {};
		std::cin >> op;
		ignoreLine();
	

		switch (op)
		{
			case '+':
			case '_':
			case '*':
			case '/' :
			return op; // return operator to caller
			default: // or tell user what went wrong
			std::cerr << " Opps that input is invalid. please enter again.\n";

		}

	}
}
int add( int x, int y )
{
	return x + y;

}

int subtract( int x, int y )
{
	return x - y;

}

int multiply(int x,int y)
{
	return x * y;
}

int divide( int x, int y )
{
	return x / y;
}

ArithmeticFunction getArithmeticFuntion( char operation )
{

	switch (operation)
	{
		case '+':
		return &add;

		case '-':
		return &subtract;

		case '*':
		return &multiply;

		case '/':
		return &divide;

	}

	return nullptr;
}




int main()
{
	// using ArithmeticFunction = std::function<int( int, int )>;
	int x { getInt() };
	char operation { getOperator() }; 
	int y { getInt() };

	ArithmeticFunction  desiredOperation { getArithmeticFuntion(operation ) }; // the call to getArithmeticFuction which returns a function pointer to
	// any of the operator desirable functions(e.g add,multiply..) iS Now initialized to function pointer identifier desiredOperation of type
	// ArithmeticFunction i.e. std::function<int(int,int) which is a pointer to function return type int and parameter type (int,int).
	// This extra initialization is done to directly call any of these underlying  functions using this function pointer desireOperation
	// the call syntax with implicit dereference looks exactly like call to normal function
	
	std::cout<<" ANSWER: "<<desiredOperation(x, y);
  
	return 0;
}