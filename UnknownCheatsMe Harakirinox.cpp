#include<string>
#include<Windows.h>
#include<iostream>

void printToConsole(int varInt,std::string* ptr2string,char* arrChar,int* ptr2int,int**ptr2ptr,int*** ptr2ptr2)
{
	std::cout << " Process Id: " << GetCurrentProcessId() << '\n' << '\n';

	std::cout << "varInt  " << '\t' << "(0x" << ptr2int << ')' << " = " << varInt << '\n';
	std::cout << "varString " << '\t' << "(0x" << ptr2string << ')' << " = " << *ptr2string << '\n';
	std::cout << "arrChar[128] " << '\t' << "(0x" << static_cast<void*>(arrChar) << ')' << " = " << arrChar << '\n';
	std::cout << "ptr2int " << '\t' << "(0x" << ptr2ptr << ')' << " = " << ptr2int << '\n';
	std::cout << "ptr2ptr " << '\t' << "(0x" << ptr2ptr2 << ')' << " = " << ptr2ptr << '\n';
	std::cout << "ptr2ptr2 " << '\t' << "(0x" << &ptr2ptr2 << ')' << " = " << ptr2ptr2 << '\n'<<'\n';
    
	std::cout << "Press enter to print again " << '\n'<<'\n';
	
}


int main()
{
	int varInt{ 123456 };
	std::string varString{ "Defaultstring" };
	std::string* ptr2string{ &varString };
	char arrChar[128]{ "Long char array right there ->" };
	int* ptr2int { &varInt };
	int** ptr2ptr { &ptr2int };
	int*** ptr2ptr2 { &ptr2ptr };

	while(true)
	{
		
		printToConsole(varInt, ptr2string, arrChar, ptr2int, ptr2ptr, ptr2ptr2);
        std::cin.get();
        std::cout << "--------------------------------------------------------------------\n" << '\n';
	} 

	
	return 0;
}