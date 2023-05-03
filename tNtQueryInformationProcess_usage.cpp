#include<Windows.h>
#include<winternl.h> //! for undocumented structures like PROCESSINFOCLASS
#include<iostream>
#include<string>
#include <ntstatus.h>//! to inlude NTSTATUS for status returned bt api functions

//!Get the PEB using NtQueryInformationProcess() Externally

typedef NTSTATUS( __stdcall* tNtQUeryInformationProcess )
(
HANDLE ProcessHandle,
PROCESSINFOCLASS ProcessInformationClass, //! enum type to define ProcessBasicInformation
PVOID ProcessInformation,
ULONG ProcessInformationLength,
PULONG ReturnLength
);
//! function pointer prototype for NtQueryInformationProcess()
tNtQUeryInformationProcess NtQueryInfoProc = nullptr; 

//!this boolean function imports the function address for NtQueryInformationProcess() and assigns it 
//! to the earlier defined function pointer by help of GetProcAddress()
bool ImportNtQueryInfo()
{
	NtQueryInfoProc = (tNtQUeryInformationProcess)::GetProcAddress( GetModuleHandle( TEXT( "ntdll.dll" ) ), "NtQueryInformationProcess" );
	if (NtQueryInfoProc == nullptr)
	{
		return false;
	}
	else
		return true;

}

//!function to get the PEB(process environment block struct Extreenally without injection
PEB GetPebExternal()
{
	//todo Open/retrieve a process handle to current process with PROCESS_ALL_ACCESS rights
	//todo using GetCurrentProcess(),to be used later with ReadProcessMemory
	HANDLE hProcess = GetCurrentProcess();
	
	//!define an intial status variable
	NTSTATUS status = STATUS_SUCCESS;
	
	//!define a variable to PROCESS_BASIC_INFORMATION structure
	PROCESS_BASIC_INFORMATION pbi{};
	
	//!intialize peb struct with a nullptr
	PEB peb{};
	
	//! get NtQueryInformationProcess() function pointer with required address
	//! to fill up the PROCESS_BASIC_INFORMATION structure
	if (!NtQueryInfoProc)
		ImportNtQueryInfo();
	if (NtQueryInfoProc)
		 status = NtQueryInfoProc( hProcess, ProcessBasicInformation, &pbi, sizeof( pbi ), nullptr );
	//? Checking status of NtQueryInfoProc() function pointer call
	if (NT_SUCCESS( status )) 
	{
		ReadProcessMemory( hProcess, pbi.PebBaseAddress, &peb, sizeof( peb ), nullptr );

	}
	return peb;
}

//!Once we have got the PEB we can access the PEB_LDR_DATA linked list
//! LDR_DATA_ENTRY LIST_ENTRY a stable structure which list various loaded modules properties
//! WINTERNL.H presents a modified LDR_DATA_TABLE_ENTRY that has just the InMemoryOrderLinks, DllBase, FullDllName, CheckSum and TimeDateStamp members, plus padding that gets these members to the same offsets as in the true structure.

LDR_DATA_TABLE_ENTRY* GetLdrDatTableEntryExternal( const wchar_t* modName )
{
	LDR_DATA_TABLE_ENTRY* modLdtEntry = nullptr;

	//!Getting PEB structure using NtQueryInformationProcess() function
	PEB peb = GetPebExternal();

	//!Using the PEB structure to get member Ldr( PEB_LDR_DATA) structure
	//! PEB_LDR_DATA structure in turn contains the LIST_ENTRY linked list structure
	//! LIST_ENTRY structure is named InMemoryOrderModuleList which contains list of loaded modules
	LIST_ENTRY head = peb.Ldr->InMemoryOrderModuleList;

	//?  the links in these lists are not safe to follow while modules might be loaded and unloaded. That this can’t happen at the time can be hard enough to ensure even for the current process.
	//? So we obtain LDR_DATA_TABLE_ENTRY structure WHICH IS MORE STABLE

	LIST_ENTRY current = head;

	//!Parsing the LIST_ENTRY structure to get the required 
	for (auto current = head; current.Flink != &peb.Ldr->InMemoryOrderModuleList; current = *current.Flink)
	{
		//!The CONTAINING_RECORD macro returns the base address of an instance of a structure given the type of the structure and the address of a field within the containing structure.
		//! this is used to return the address of variable 
		LDR_DATA_TABLE_ENTRY* ldtEntry = (LDR_DATA_TABLE_ENTRY*) CONTAINING_RECORD( current.Flink, LDR_DATA_TABLE_ENTRY,InMemoryOrderLinks );
		//! full path address needs to be given FOR COMPARISON as it is only defined field in present definition of _LDR_DATA_TABLE_ENTRY
		//! BaseDllName member is nor defined so not showing up
		if (ldtEntry->FullDllName.Buffer)
		{
			if (_wcsicmp( modName, ldtEntry->FullDllName.Buffer ) == 0)
			{
				modLdtEntry = ldtEntry;
				break;
			}

		}


	}
	return modLdtEntry;
}

int main()
{
	std::wcout << " Enter the name of module to get LDR_DATA_TABLE_ENTRY structure.\n";
	std::wstring modName;
	std::wcin >> modName;
	//!To convert wstring to  const wchar_t* use member function .c_str() 
	std::cout << " The base address of module is: " << GetLdrDatTableEntryExternal( modName.c_str() )->DllBase<<'\n';
	return 0;
}