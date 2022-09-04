#include<iostream>

int main()
{ /*
  Lambda function signature
                       
					   [capture list] (paramters) ->  return_type
					   {
					    // body of lambda function

                        }(arguments to function);
  
  */

  // lambda function called without handle identifier directly (single use function)
	[]()
	{
		std::cout << "Hello good world!\n";
	}();  // parentheis at end of expression to call lambda function
	     // semicolon at end as it is c++ statement

	// To call a lambda function we need to give handle identifier and use it through handle

	auto funky = []()
	{
		std::cout << "Hello good world!\n";
	};

	// call to lambda funtion using handle identifier (note parenthesis at end)
	funky(); 

	// Note for calling using handle funky1 argument parenthesis at end avoided
	auto funky1 = [](double a,double b)
	{
		std::cout << " a + b: " << a + b << '\n';
	};

	funky1( 13.1, 26.2 );
	funky1( 7.97, 8.65 );


	// Lambda function that returns something in lambda function body itself
	// return from lambda function used through handle by assigning return to the handle variable
	// otherwise lambda function just return something and it can't be used
	// Without handle also our lambda function returns value but that value can't be used meaningfully and get discarded

	auto func =  [](double a,double b) ->double //return type double is optional
		{
		return (a + b); // return from lambda function

		}(13.3,19.7); // semicolon at end of lambda function declartion, arguments declared, 
	
		std::cout << " result (a+b): " << func<<'\n'; // while returning result from lambda function drop the parenthesis

// Lambda function result without handle identifier variable 
   // whole return result put directly in std::cout to use the value

	std::cout<<	"result direct (a+b): "<<
		[]( double a, double b ) //return type double is optional
		{
			return (a + b); // return from lambda function

	}(33.3, 19.7); // semicolon at end of lambda function declartion, arguments declared, 

	std::wcout << '\n';


	// OMISSION of end- parenthesis at end of lambda expression and putting it besidesto handle
	// then lambda function can be called repeatedly like normal function call funky2(arg1,arg2)

	auto funky2 = []( double a, double b ) 
	{
		return (a + b); // return from lambda function

	}; // note there are no parenthesis at end

	std::cout << " result3: " << funky2( 1.3, 3.9 ) << '\n'; // parenthesis here with arguments next to handle identifier funky2
	std::wcout << " results4: " << funky2( 4.6, 8.9 ) << '\n';// parenthesis here with arguments next to handle identifier funky2

	// Explicitly specify the return type

	auto funky3=[]( double a, double b ) ->int //return type int given explicitly
	{
		return (a + b); // return from lambda function

	}; // note there are no parenthesis at end

	auto funky4 = []( double a, double b ) //return type  implicitly deduced double
	{
		return (a + b); // return from lambda function

	}; // note there are no parenthesis at end

	auto result5 = funky3( 3.8, 9.6 );
	auto result6 = funky4( 3.8, 9.6 );

	std::cout << " result5: " << result5 << '\n';
	std::cout << " result6: " << result6 << '\n';


	std::cout << "sizeof(result5): " << sizeof( result5 )<<'\n'; //4
	std::cout << "sizeof(result6): " << sizeof( result6 ) << '\n'; //8


	std::cout << " done ";
	std::cout << '\n';
	return 0;
}

