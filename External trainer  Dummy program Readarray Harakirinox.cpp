
#include<Windows.h>
#include<iostream>

int main()
{

	// prompting user to enter process id
	std::cout << " Enter the process id of targeted program: ";
	DWORD pid{}; // process id of our target process
	std::cin >> pid; // prompting user to enter process id


	HANDLE hProcess = OpenProcess(PROCESS_VM_READ, FALSE, pid);

	if (hProcess == NULL) // failed to get a handle
	{
		std::cout << " open process failed. GetLastError = " << std::dec << GetLastError() << '\n';
		system("pause");
		return EXIT_FAILURE;
	}

	// prompting user to enter value of pointer to array from which we have to read the value
	void* ptr2array{ 0 };
	std::cout << " Memory address of string to read (in hexadecimal): 0x";
	std::cin >> std::hex >> ptr2array;
	std::cout << '\n';

	/*void ptrInput(std::vector<void*>&ptr)
	{
		void* input{};
		while (std::cin >> input)
		{
			ptr.push_back(input);
		}
	}*/

	// Reading array from other process


	char arrayToRead[128]{}; // arrayToRead cast as C-style string from std::string to determine the maximumsize for storing 


	BOOL rpmReturn = ReadProcessMemory(hProcess, (LPCVOID) (ptr2array), (LPVOID) (&arrayToRead), sizeof(arrayToRead), NULL);

	if (rpmReturn == FALSE)
	{
		std::cout << "ReadProcessMemory failed.GetLastError: " << std::dec << GetLastError() << '\n';
		system("pause");
		return EXIT_FAILURE;
	}


	std::cout << "arrToREad = " << arrayToRead << '\n';

	CloseHandle((HANDLE) hProcess);
	std::cout << "Press enter to quit \n";
	std::cin.get();
	return 0;


}