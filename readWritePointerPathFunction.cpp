#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>
#include<Windows.h>
#include<TlHelp32.h> // For CreateToolhelp32Snapshot function

// find process id by process name

DWORD findMyProc( const auto& procName )
{
	HANDLE hSnapShot{};
	PROCESSENTRY32 pe{}; //processentry32 struct describes an entry from a list of the process residing in the system address space when a snapshot was taken
	DWORD pid {};
	BOOL hResult{};

	// snapshot of all processes in system
	hSnapShot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS,0 );

	if (hSnapShot == INVALID_HANDLE_VALUE)
	{
		std::cout << "process snapshot failed. GetLastError: " << std::dec << GetLastError();
		system( "pause" );
		return EXIT_FAILURE;
	}
// initializing size of PROCESSENTRY32 struct of type DWORD dwSize
	pe.dwSize = sizeof( PROCESSENTRY32 );

	// info about first process encountered in a system snapshot
	hResult = Process32First( hSnapShot, &pe );
	// retrieve information about processes
	// and exit if unsuccessful

	while (hResult)
	{
		if (wcscmp( procName, pe.szExeFile ) == 0) // using wcscmp func(from std lib) instead of strcmp for use with wchar unicode system
		{
			pid = pe.th32ProcessID;
			break;
		}
		hResult = Process32Next( hSnapShot, &pe );
	}

	// closes an Open handle( CreateToolhelp32SnapShot)
	CloseHandle( hSnapShot );
	return pid;
}

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

	// Getting process id automatically
	DWORD procId {};
	procId = findMyProc( L"Doom3BFG.exe" );
	
	// section of code to be modified to get process id automatically
	std::cout << "  Process Id found by findMyProc function: "<<procId;


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
