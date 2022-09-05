#include<iostream>
#include<vector>
#include<Windows.h>


uintptr_t findPointerPath(HANDLE hProcess,  uintptr_t baseaddress, const std::vector<uintptr_t>& offsetVector)
{
	
	uintptr_t dynAddress = baseaddress;

	for (std::size_t i { 0 }; i < offsetVector.size(); ++i)
	{
		BOOL rpmReturn1=ReadProcessMemory( hProcess, (LPCVOID) dynAddress, &dynAddress, sizeof(dynAddress), NULL );
		if (rpmReturn1 == FALSE) // Failed to read process memory inside called function
		{
			std::cout << "ReadProcessMemory1 in readPointerpathFunc failed.GetLastError: " << std::dec << GetLastError() << '\n';
			system( "pause" );
			return EXIT_FAILURE;
		}
     	dynAddress += offsetVector.at(i);
	}
    return dynAddress;
}

int main()
{
	
	std::vector<uintptr_t>offsetVector { 0xD44 }; // vector array of offsets for pointer to desired modifiable value
	
	uintptr_t fixedOffset { 0x009126e4 }; // fixed offset of entity from module base address

	// section of code to be modified to get modeule Base address automatically
	uintptr_t moduleBaseAddres { 0x00400000 };
	
	uintptr_t baseAddress = moduleBaseAddres + fixedOffset;
	
	// section of code to be modified to get process id automatically
	std::cout << " Please enter process id: ";
	DWORD procId {};
	std::cin >> procId;

	HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, procId );
	
	if (hProcess == NULL) // failed to get a handle
	{
		std::cout << " Open process failed. GetLastError: " << std::dec << GetLastError() << '\n';
		system( "pause" );
		return EXIT_FAILURE;
	}

	uintptr_t ammoAddress = findPointerPath( hProcess, baseAddress, offsetVector );

	std::cout  << " ammo address is: " <<std::hex<<ammoAddress << '\n';

	int ammoValue {};
	// Reading ammo value
	BOOL rpmReturn = ReadProcessMemory( hProcess, (LPCVOID) ammoAddress, &ammoValue, 4, NULL );
	
	if (rpmReturn == FALSE)
	{
		std::cout << "ReadProcessMemory failed.GetLastError: " << std::dec << GetLastError() << '\n';
		system( "pause" );
		return EXIT_FAILURE;
	}
	
	std::cout << " Current ammo value is: " <<std::dec<< ammoValue << '\n';

	// Writing ammo value
	std::cout << " enter the value of Ammo to be updated: ";
	int newAmmoValue {};
	std::cin >> newAmmoValue;

	BOOL wpmReturn = WriteProcessMemory( hProcess, (LPVOID) ammoAddress, (LPCVOID) &newAmmoValue, (SIZE_T) sizeof( newAmmoValue ), NULL);
    if (wpmReturn == FALSE)
	{
		std::cout << " WriteProcessMemory failed.GetLastError: " << std::dec << GetLastError() << '\n';
		system( "pause" );
		return EXIT_FAILURE;
	}
	else
		std::cout << " ammo value successfully changed: " << '\n';
   
}
