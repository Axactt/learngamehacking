#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>



uintptr_t GetModuleBaseAddress( DWORD procId, const wchar_t* modName )
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(  TH32CS_SNAPALL, procId );
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof( modEntry );
		if (Module32First( hSnap, &modEntry ))
		{
			do
			{
				if (!_wcsicmp( modEntry.szModule, modName ))
				{
					modBaseAddr = (uintptr_t) modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next( hSnap, &modEntry ));
		}
	}
	CloseHandle( hSnap );
	return modBaseAddr;
}

uintptr_t FindDMAAddy( HANDLE hProc, uintptr_t ptr, std::vector<unsigned int> offsets ) // hProc parameters receives "HWND handle" and not " hProcess HANDLE"
{
	hProc;
	uintptr_t addr = ptr;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		 ReadProcessMemory( hProc, (LPVOID) addr, &addr, sizeof( addr ), 0 );
		addr += offsets[i];
		
	}
	return  addr;
}

int main()
{
	

	HWND handle = FindWindowEx( NULL, L"DOOM 3: BFG Edition" );
	if (!handle)
	{
		std::cout << " Finding window failed. GetLastError = " << std::dec << GetLastError() << '\n';
		return 0;
	}


	// procId = 19844 ;// GetWindowThreadProcessId( handle, &procId ); // needs to be corrected

	DWORD procId = GetProcessId( handle );

	if (!procId)
	{
		std::cout << " Finding procId failed. GetLastError = " << std::dec << GetLastError() << '\n';
		return 0;
	}

	std::cout << " process Id: " << procId; //procId;  19844
	

	uintptr_t modebase =   GetModuleBaseAddress(19844, ( L"Doom3BFG.exe")); // equals to 5961a744

	std::cout << " Modebase: " << modebase << '\n';

	
	HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, 19844 );


	std::vector<unsigned int> offsets { 0xd44 };
	
	
	// hProc parameters receives "HWND handle" and not " hProcess HANDLE"-- this was mistake

	uintptr_t ammoAddr = FindDMAAddy( hProcess, 0x5961a744, {0xd44 } ); // GetModuleBaseAddress still has to be corrected so putting direct value for base address(0x59aeb7b4)
	

	std::cout << " the player current dynamic address is: " << ammoAddr;
	

	DWORD newa = 1337 ;

	WriteProcessMemory( hProcess, (LPVOID) 0x5961B488, &newa, sizeof( newa ), 0 );


	return 0;



}