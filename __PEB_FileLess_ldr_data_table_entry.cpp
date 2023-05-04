#include<Windows.h>
#include<intrin.h>
#include<winternl.h>//!//! for undocumented structures like PROCESSINFOCLASS or TEB or PEB ::A_MUST_INCLUDE
#include<ntstatus.h>
#include<iostream>
#include<string>

//! Non coventional GetProcAddress








// Read Peb and module base internally without using windows api.

//! Read the value of TIB or _TEB Linear address from FS/GS segment base offset
//! The TIB of the current thread can be accessed as an offset of segment register FS (x86) or GS (x64).

TEB* getTIBFileLess()
{
	//! _WIN64 is defined on every platform/CPU architecture where sizeof(void*) >= 8
#ifdef _WIN64 //? this macro needs only one undrscore
	TEB* teb = (TEB*) __readgsqword( 0x30 );//?always put double underscore before internall structure command
	//xreturn (void*) __readgsqword( 0x30 ); 
#else 
	TEB* teb = (TEB*) __readfsdword( 0x18 );
	//xreturn (void*) __readfsdword( 0x18 );
#endif
	return teb;
}

//! Read the value of _PEB  Linear address from FS/GS segment base offset
//! The PEB of the current thread can be accessed as an offset of segment register FS (x86) or GS (x64).

PEB* getPEBFileLess()
{
	//! _WIN64 is defined on every platform/CPU architecture where sizeof(void*) >= 8
#ifdef _WIN64 //? this macro needs only one undrscore

	PEB* peb = (PEB*) __readgsqword( 0x60 ); //?always put double underscore before internall structure command
#else 
	PEB* peb = (PEB*) __readfsdword( 0x30 );
#endif
	return peb;
}

//!Once we have got the PEB we can access the PEB_LDR_DATA linked list
//! LDR_DATA_ENTRY LIST_ENTRY a stable structure which list various loaded modules properties
//! WINTERNL.H presents a modified LDR_DATA_TABLE_ENTRY that has just the InMemoryOrderLinks, DllBase, FullDllName, CheckSum and TimeDateStamp members, plus padding that gets these members to the same offsets as in the true structure.

LDR_DATA_TABLE_ENTRY* GetLdrDatTableEntryInternal( const wchar_t* modName )
{
	LDR_DATA_TABLE_ENTRY* modLdtEntry = nullptr;

	//!Getting PEB structure using NtQueryInformationProcess() function
	PEB* peb = getPEBFileLess();

	//!Using the PEB structure to get member Ldr( PEB_LDR_DATA) structure
	//! PEB_LDR_DATA structure in turn contains the LIST_ENTRY linked list structure
	//! LIST_ENTRY structure is named InMemoryOrderModuleList which contains list of loaded modules
	LIST_ENTRY head = peb->Ldr->InMemoryOrderModuleList;

	//?  the links in these lists are not safe to follow while modules might be loaded and unloaded. That this can’t happen at the time can be hard enough to ensure even for the current process.
	//? So we obtain LDR_DATA_TABLE_ENTRY structure WHICH IS MORE STABLE

	LIST_ENTRY current = head;

	//!Parsing the LIST_ENTRY structure to get the required 
	for (auto current = head; current.Flink != &peb->Ldr->InMemoryOrderModuleList; current = *current.Flink)
	{
		//!The CONTAINING_RECORD macro returns the base address of an instance of a structure given the type of the structure and the address of a field within the containing structure.
		//! this is used to return the address of variable 
		LDR_DATA_TABLE_ENTRY* ldtEntry = (LDR_DATA_TABLE_ENTRY*) CONTAINING_RECORD( current.Flink, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks );
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

intptr_t FindModuleHandle(std::wstring moduleName)
{ 
	//!To convert wstring to  const wchar_t* use member function .c_str() 
	return {(intptr_t) (GetLdrDatTableEntryInternal( moduleName.c_str()))->DllBase };

}

int main()
{
	std::wcout << " Enter the full path name of module to get LDR_DATA_TABLE_ENTRY structure.\n";
	//? Note full actual path of dll has to be entered here as 
	//! wininternl.h has only defined FullDllName member for LDR_DATA_TABLE_ENTRY structure
	std::wstring modName;
	std::wcin >> modName;
	//!To convert wstring to  const wchar_t* use member function .c_str() 
	std::cout << " The base address of module is: " << GetLdrDatTableEntryInternal( modName.c_str() )->DllBase << '\n';
	//Function version of GetModuleHandle()
	std::cout << " The base address of module is: " << std::hex<<FindModuleHandle(modName) << '\n';

	return 0;
}