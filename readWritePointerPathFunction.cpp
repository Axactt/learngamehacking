#include<iostream>
#include<cstring> // for strcmp function
#include<vector>
#include<Windows.h>
#include<TlHelp32.h> // For CreateToolhelp32Snapshot function
   

// currently console trainer works only as 32 bit application
// needs to sort out


// find process id by process name

DWORD findMyProc( const char* procName )
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
		if (strcmp( procName, pe.szExeFile ) == 0) 
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

// Finding module address by module/process id
uintptr_t findMyModuleAddress( DWORD procId,const char* procName)
{
	HANDLE hSnapShot {}; // initialization of snapshot handle frm CreateToolHelp32SnapShot function
	MODULEENTRY32 me {}; // initialization of MODULEENTRY32 struct
	uintptr_t moduleBaseAddress {}; // initialization of moduleBaseaddress to be found 
	BOOL hResult {}; // return value from MODULEENTRY32FIRST or MODULEENTRY32NEXT function in BOOL

	// SnapShot of  modules tied with the relevant procID
	hSnapShot= CreateToolhelp32Snapshot( TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId );

	if (hSnapShot == INVALID_HANDLE_VALUE)
	{
		std::cout << "Module snapshot failed. GetLastError: " << std::dec << GetLastError();
		system( "pause" );
		return EXIT_FAILURE;
	}

	// initiallizing size of MODULEENTRY32 struct of type (DWORD) dwSize before using MODULE32FIRST and MODULE32NEXT function
	//It is The size of the structure, in bytes. Before calling the Module32First function, set this member to 
	//sizeof(MODULEENTRY32). If you do not initialize dwSize, Module32First fails.

	me.dwSize = sizeof( MODULEENTRY32 );

	// info about first module encountered in a system snapshot
	hResult = Module32First( hSnapShot, &me );

	// retrieve information about the  modules
	// and exit if unsuccessful
	while (hResult)
	{
		// if we find the module: return module Base address from "me"struct member - *modBaseAddr which is of type BYTE*
		if (strcmp(procName,me.szModule)==0)
		{ 
			// me.modBaseAddr of type BYTE* c-style cast to uintptr_t
			moduleBaseAddress = (uintptr_t) (me.modBaseAddr); 
			break;
		}
		else
		hResult = Module32Next( hSnapShot, &me ); // search for next module in snapshot in me structure

	}
	
	return moduleBaseAddress;
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
	uintptr_t fixedOffset { 0x009125C4 }; // fixed offset of entity from module base address

	
	// Getting process id automatically
	DWORD procId {};
	procId = findMyProc( "Doom3BFG.exe" );
	std::cout << "  Process Id found by findMyProc function: "<<procId;

	// section of code to be modified to get modeule Base address automatically
	
	
	
	uintptr_t moduleBaseAddres = findMyModuleAddress(  procId, "Doom3BFG.exe" );
	uintptr_t baseAddress = moduleBaseAddres + fixedOffset;


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
