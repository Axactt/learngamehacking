#include<Windows.h>
#include<intrin.h>
#include"ReNtdll.h" //! imported ntdl.dll from x64dbg header to inlude all undocumented structures
//x#include<winternl.h>//!//! for undocumented structures like PROCESSINFOCLASS or TEB or PEB ::A_MUST_INCLUDE
#include<ntstatus.h>
#include<iostream>
#include<string>

//Declaration for non-conventional GetModuleHandle() address
ptrdiff_t FindModuleHandle( std::wstring moduleName );



//! Non coventional GetProcAddress to get address of exported function
ptrdiff_t get_module_export( const wchar_t* module_name, const char* export_name )
{
	if (!module_name || !export_name)
		return 0;
	auto module_base = reinterpret_cast<UCHAR*> (FindModuleHandle( module_name ));

	if (!module_base)
		return 0;
	//!Assigning a IMAGE_DOS_HEADER* variable to module_base_address
	auto pimage_dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module_base);
	//!Check for validity of image file using IMAGE_DOS_SIGNATURE(e_magic) defined in winnt.h
	if (pimage_dos_header->e_magic != IMAGE_DOS_SIGNATURE)
		return 0;
	//! e-elfanew offset added to module_base to get offset to IMAGE_NT_HEADERS,casted to its pointer
	auto pimage_nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(module_base + pimage_dos_header->e_lfanew);
	//!Again recheck for validity of signature by defn of IMAGE_NT_SIGNATURE
	if (pimage_nt_headers->Signature != IMAGE_NT_SIGNATURE)
		return 0;
	//!Get the datadirectory of EXport as per PE file format
	//! DataDirectory: end structure of the IMAGE_OPTIONAL_HEADER contains predefined 16 directories
	//! Export Table or IMAGE_DIRECTORY_ENTRY_EXPORT is the first directory at index 0 of DataDirectory array
	//! Each index of DataDirectory array contains a structure having RVa/ size fields
	//? This will give relative virtual address of Export_Directory(index 0)from module_base PE file
	auto export_directory_rva = pimage_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	//!check for relative cirtual address to be valid
	if (!export_directory_rva)
		return 0;
     //! adding export_directory_rva to module_base will give actual address in memory of IMAGE_DIRECTORY_ENTRY_EXPORT
	auto pimage_export_directory = reinterpret_cast<PIMAGE_EXPORT_DIRECTORY>(module_base + export_directory_rva);


	//!Now we get the various other structure in IMAGE_DIRECTORY_ENTRY_EXPORT and cast to PDWORD
	//? Note:: other structure fields within a directory e.g.(within IMAGE_EXPORT_DIRECTORY) 
	//? such as Export_address_table,ent,e_name_ordinale_table etc have value field
	//? are at offsets which ARE actually  at RVA from module_base_address(// RVA from base of image)   
	//!It is an array which hold DWORD RVAS which point to the start address of exported functions. So Casting done to DWORD*
	DWORD* pEAT = reinterpret_cast<PDWORD>(module_base + pimage_export_directory->AddressOfFunctions);


	//!The export name pointer table is an array of addresses (RVAs) into the export name table. The pointers are 32 bits each and are relative to the image base. The pointers are ordered lexically to allow binary searches.
	//? This is different from: The export name table which contains the actual string data that was pointed to by the export name pointer table
	//?In export name pointer table Every exported symbol has an ordinal value, which is just the index into the export address table.
	//!It is an array which hold DWORD RVAS which point to the string which specify function names. So Casting done to DWORD*
	DWORD* pENPT = reinterpret_cast<PDWORD>(module_base + pimage_export_directory->AddressOfNames);


	//!The export ordinal table is an array of 16-bit unbiased indexes into the export address table. 
	//? this was earlier casted to PDWORD which was wrong it should be LPWORD
	//! It is an array which hold WORD(UNSIGNED SHORT) sized ordinals. So casting done to UINT16* or unsigned short*
	//? VVIMP: As EXPORT_NAME_ORDINAL_TABLE is an array of UNSIGNED SHORT or UINT16, It has to be casted appropriately as UNSIGNED SHORT*
	//? So when array EXPORT_NAME_ORDINAL_TABLE is traversed/iterated it should give correct ordinal value of type unsigned short UINT16
    //! Entries of ordinal in this array are already ZER0-indexed indices into IAT,THerefore unaffected by field value of ORDINAL_BASE
	//xauto pEOT = (UINT16*)  (module_base + pimage_export_directory->AddressOfNameOrdinals);
	UINT16* pEOT = reinterpret_cast<LPWORD>(module_base + pimage_export_directory->AddressOfNameOrdinals); 
	
	UINT16 ordinal = 0;

	//!This for loop looks for the index in EXPORT_NAME_POINTER_TABLE which matches our searched function
	for (uintptr_t i{ 0 }; i < pimage_export_directory->NumberOfNames; ++i)
	{
		//! Export_ordinal_table array is indexed from the Base field value of IMAGE_EXPORT_DIRECTORY
		//!  Each ordinal is an index into the export address table.
		//! When another image file imports a symbol by name, the Win32 loader searches the name pointer table for a matching string. If a matching string is found, the associated ordinal is identified by looking up the corresponding member in the ordinal table (that is, the "MEMBER_VALUE" of the export_ordinal table with the same index as the string pointer found in the name pointer table). The resulting ordinal is an index into the export address table, which gives the actual location of the desired symbol. Every export symbol can be accessed by an ordinal.
		
		if (!stricmp( export_name, reinterpret_cast<const char*>(module_base + pENPT[i]) ))
		{
 //todo the "MEMBER_VALUE" of the export_ordinal table with the same index as the string pointer found in the name pointer table will give the actual ordinal/index to EAT
			//xordinal = (UINT16)pEOT[i];
		     ordinal = (pEOT[i]);
			break;
		}

	}
	//! this will give actual VA of exported symbol based RVA from Export_address_table["MEMBER_VALUE" of the export_ordinal table matched]
	//xreturn ordinal? (module_base + pEAT[ordinal]) : 0 ;
	return reinterpret_cast<ptrdiff_t>(module_base + pEAT[ordinal]);
}


uintptr_t get_module_export2( const wchar_t* module_name, const char* export_name )
{
	if (!module_name || !export_name)
		return 0;
	auto hModule = (FindModuleHandle( module_name ));

	//? Fixed defines: _WIN32 Defined as 1 when the compilation target is 32-bit ARM, 64-bit ARM, x86, or x64. Otherwise, undefined.
    //?_WIN64 Defined as 1 when the compilation target is 64 - bit ARM or x64.Otherwise, undefined.

#if defined( _WIN32 )   
	unsigned char* lpBase = reinterpret_cast<unsigned char*>(hModule);
	IMAGE_DOS_HEADER* idhDosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(lpBase);
	if (idhDosHeader->e_magic == 0x5A4D)
	{
#if defined( _M_IX86 ) //!Fixed Macro-defined only for x86 target 
		IMAGE_NT_HEADERS32* inhNtHeader = reinterpret_cast<IMAGE_NT_HEADERS32*>(lpBase + idhDosHeader->e_lfanew);
#elif defined( _M_AMD64 ) 
		IMAGE_NT_HEADERS64* inhNtHeader = reinterpret_cast<IMAGE_NT_HEADERS64*>(lpBase + idhDosHeader->e_lfanew);
#endif 
		if (inhNtHeader->Signature == 0x4550)
		{
			IMAGE_EXPORT_DIRECTORY* iedExportDirectory = reinterpret_cast<IMAGE_EXPORT_DIRECTORY*>(lpBase + inhNtHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
			for (register unsigned int uiIter = 0; uiIter < iedExportDirectory->NumberOfNames; ++uiIter)
			{
				char* szNames = reinterpret_cast<char*>(lpBase + reinterpret_cast<unsigned long*>(lpBase + iedExportDirectory->AddressOfNames)[uiIter]);
				if (!strcmp( szNames, export_name ))
				{
					//? VVIMP: As EXPORT_NAME_ORDINAL_TABLE is an array of UNSIGNED SHORT or UINT16, It has to be casted appropriately as UNSIGNED SHORT*
					//? So when array EXPORT_NAME_ORDINAL_TABLE is traversed/iterated it should give correct ordinal value of type unsigned short UINT16
					//! Entries of ordinal in this array are already ZER0-indexed indices into IAT,THerefore unaffected by field value of ORDINAL_BASE
					unsigned short usOrdinal = (reinterpret_cast<unsigned short*>(lpBase + iedExportDirectory->AddressOfNameOrdinals))[uiIter];
					
					return reinterpret_cast<uintptr_t>(lpBase + reinterpret_cast<unsigned long*>(lpBase + iedExportDirectory->AddressOfFunctions)[usOrdinal]);
				}
			}
		}
	}
#endif 
	return 0;
}


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
			if (_wcsicmp( modName, ldtEntry->BaseDllName.Buffer ) == 0)
			{
				modLdtEntry = ldtEntry;
				break;
			}
		}
	}
	return modLdtEntry;
}
//!alternative way to find Module address other then GetModuleHandle()
ptrdiff_t FindModuleHandle(std::wstring moduleName)
{ 
	//!To convert wstring to  const wchar_t* use member function .c_str() 
	return {(ptrdiff_t) (GetLdrDatTableEntryInternal( moduleName.c_str()))->DllBase };

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
	std::cout << " Enter name of exported symbol for function to be searched for its address: \n";
	std::string funcName;
	std::cin >> funcName;
	std::cout << "The address of exported symbol searched for is: " << std::hex << get_module_export( modName.c_str(), funcName.c_str() );
	return 0;
}