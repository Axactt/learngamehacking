#include<iostream>

int main()
{ /*
  Lambda function signature
                       
					   [capture list] (paramters) ->  return_type
					   {
					    // body of lambda function

                        }(arguments to function);
  
  
  
  */
	[]()
	{
		std::cout << "Hello good world!\n";
	}();  // lambda function called without handle identifier directly (single use function)

	// To call a lambda function we need to give handle identifier and use it through handle

	auto funky = []()
	{
		std::cout << "Hello good world!\n";
	};

	// call to lambda funtion using handle (note parenthesis at end)
	funky(); 


	// to get a return from lambda function 
	auto func =  [](double a,double b) ->double //return type double is optional
		{
		return (a + b); // return from lambda function

		}(13.3,19.7); // semicolon at end of lambda function declartion, arguments declared
	
		std::cout << " result (a+b): " << func; // while returning result from lambda function drop the parenthesis

	return 0;
}

