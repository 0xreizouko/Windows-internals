#define BUILD_WINDOWS

#include<Windows.h>
#include<winternl.h>
#include<stdio.h>
#include<intrin.h>

#pragma comment(lib, "ntdll.lib")

extern "C" void SetSSN(DWORD ssn);

extern "C" NTSTATUS NtWriteFileSyscall(
    IN HANDLE FileHandle,
    IN HANDLE Event,
    IN PIO_APC_ROUTINE ApcRoutine,
    IN PVOID ApcContext,
    OUT PIO_STATUS_BLOCK IoStatusBlock,
    IN PVOID Buffer,
    IN ULONG Length,
    IN PLARGE_INTEGER ByteOffset,
    IN PULONG Key
);

int main() {
    HMODULE ntdllInstance;

    PPEB peb;
    peb = (PPEB)__readgsqword(0x60);

    PPEB_LDR_DATA ldr = peb->Ldr;
    LIST_ENTRY* moduleList = &(ldr->InMemoryOrderModuleList);
    LIST_ENTRY* currentEntry = moduleList->Flink;

    
    while(currentEntry != moduleList) {
        PLDR_DATA_TABLE_ENTRY entry = (PLDR_DATA_TABLE_ENTRY)(currentEntry - 1);
        WCHAR* moduleNameBuffer = entry->FullDllName.Buffer;
        WCHAR* dllName = wcsrchr(moduleNameBuffer, L'\\');

        if(dllName != NULL) dllName++;

       if(dllName == NULL) ntdllInstance = NULL;

       if(wcscmp(dllName, L"ntdll.dll") == 0) ntdllInstance = (HMODULE)entry->DllBase;

       currentEntry = currentEntry->Flink;
    }


    BYTE* NtWriteFileVA = NULL;

    PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)ntdllInstance;

    if(pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) return NULL;

    PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((BYTE*)ntdllInstance + pDosHeader->e_lfanew);

    if(pNtHeaders->Signature != IMAGE_NT_SIGNATURE) return NULL;

    PIMAGE_DATA_DIRECTORY pExportDirectory = &pNtHeaders->OptionalHeader.DataDirectory[0];

    if(pExportDirectory->Size == 0 || pExportDirectory->VirtualAddress == 0) return NULL;

    PIMAGE_EXPORT_DIRECTORY pExportDirAddr = (PIMAGE_EXPORT_DIRECTORY)((BYTE*)ntdllInstance + pExportDirectory->VirtualAddress);

    PDWORD pAddressOfFunctions = (PDWORD)((BYTE*)ntdllInstance + pExportDirAddr->AddressOfFunctions);
    PDWORD pAddressOfNames = (PDWORD)((BYTE*)ntdllInstance + pExportDirAddr->AddressOfNames);
    PWORD pAddressOfOrdinals = (PWORD)((BYTE*)ntdllInstance + pExportDirAddr->AddressOfNameOrdinals);


    for(DWORD i = 0; i < pExportDirAddr->NumberOfNames; i++) {
        LPCSTR currentName = (LPCSTR)((BYTE*)ntdllInstance + pAddressOfNames[i]);

        if(strcmp(currentName, "NtWriteFile") == 0) {
            WORD fnIndex = pAddressOfOrdinals[i];
            DWORD entryOffset = fnIndex * 4;
            PDWORD pEATEntry = (PDWORD)((BYTE*)ntdllInstance + (DWORD_PTR)pExportDirAddr->AddressOfFunctions + entryOffset);
            DWORD NtWriteFile_RVA = *pEATEntry;
            NtWriteFileVA = ((BYTE*)ntdllInstance + NtWriteFile_RVA);
        }
    }
 
    if(!NtWriteFileVA) return 1;

    DWORD SSN = 0;

    if(NtWriteFileVA[0] == 0x4C && NtWriteFileVA[1] == 0x8B && NtWriteFileVA[2] == 0xD1 && NtWriteFileVA[3] == 0xB8) {
        SSN = *(DWORD*)(NtWriteFileVA + 4);
    }

    SetSSN(SSN);

    const char* msg = "Hello, World\n";
    IO_STATUS_BLOCK StatusBlock = { 0 };
    NTSTATUS status = NtWriteFileSyscall(
        GetStdHandle(STD_OUTPUT_HANDLE),
        NULL,
        NULL,
        NULL,
        &StatusBlock,
        (PVOID)msg,
        (ULONG)strlen(msg),
        NULL,
        NULL
    );

    if(status != 0) return 1;
    return 0;
}
