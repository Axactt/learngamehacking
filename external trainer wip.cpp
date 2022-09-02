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
	DWORD procId;

	HWND handle = FindWindow( NULL, (L"DOOM 3: BFG Edition") );
	if (!handle)
	{
		std::cerr << "error finding window";
		return 0;
	}


	// procId = 15440 ;// GetWindowThreadProcessId( handle, &procId ); // needs to be corrected

	std::cout << " process Id: " << GetWindowThreadProcessId( handle, &procId ); //procId;  
	

	uintptr_t modebase =   GetModuleBaseAddress(15440, (wchar_t*) (  "Doom3BFG.exe")); // equals to 0x59aeb7b4

	std::cout << " Modebase: " << modebase << '\n';

	
	HANDLE hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, procId );


	std::vector<unsigned int> offsets { 0xd44 };
	
	
	// hProc parameters receives "HWND handle" and not " hProcess HANDLE"-- this was mistake

	uintptr_t ammoAddr = FindDMAAddy( handle, 0x59aeb7b4, {0XD44 } ); // GetModuleBaseAddress still has to be corrected so putting direct value for base address(0x59aeb7b4)
	

	std::cout << " the player current dynamic address is: " << ammoAddr;
	

	DWORD newa = 99999 ;

	WriteProcessMemory( hProcess, (LPVOID) ammoAddr, &newa, sizeof( newa ), 0 );


	return 0;



}