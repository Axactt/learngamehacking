#include<limits>
#include<Windows.h>
#include<iostream>

int main()
{

	// prompting user to enter process id
	std::cout << " Enter the process id of targeted program: ";
	DWORD pid{}; // process id of our target process
	std::cin >> pid; // prompting user to enter process id


	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	if (hProcess == NULL) // failed to get a handle
	{
		std::cout << " open process failed. GetLastError = " << std::dec << GetLastError() << '\n';
		system("pause");
		return EXIT_FAILURE;
	}

	// prompting user to enter value of pointer to integer from which we have to read the value
	void* ptr2int{ 0 };
	std::cout << " Memory address of integer  to write (in hexadecimal): 0x";
	std::cin >> std::hex >> ptr2int;
	std::cout << '\n';

	/*void ptrInput(std::vector<void*>&ptr)
	{
		void* input{};
		while (std::cin >> input)
		{
			ptr.push_back(input);
		}
	}*/

	// prompt user to enter value to be placed
	std::cout << " enter the int value for varInt to put in parent program.";
	int int2write{0}; 
    std::cin >> std::dec>>int2write;

	BOOL wpmReturn = WriteProcessMemory(hProcess, (LPVOID) (ptr2int), (LPCVOID) (&int2write), sizeof(int), NULL);

	if (wpmReturn == FALSE)
	{
		std::cout << "WriteProcessMemory failed.GetLastError: " << std::dec << GetLastError() << '\n';
		system("pause");
		return EXIT_FAILURE;
	}


	// std::cout << "arrToREad = " << arrayToRead << '\n';

	CloseHandle((HANDLE) hProcess);
	std::cout << "Press enter to quit \n";
	std::cin.get();
	return 0;


}