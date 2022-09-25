#include<iostream>
#include<string>

class User
{
private:
	/* I set the values here for the purpose of brevity. In reality, we may
	 * use constructors or other methods to set these. */
	int id {12345};
	bool useDarkMode {false};
	char userName[255] {"Axat Tiwari"};
	char passWord[255] {"password1234"};
};

int main()
{
	User user {};
	// The compiler prevents us from grabbing the password being private access
   // const char* mypassWord {user.passWord}; // fails to compile

	// However we can try to get around this

	char* user_bytes = (char*) &user; // trick is c style cast, that is why these are so dangerous,probably
  /* print as far as Os kills the process*/
	while (true)
	{
		// std::flush forces std::cout to print its buffer without a newline
		std::cout<<*user_bytes<<std::flush;
		++user_bytes;

	}

	return 0;
}

