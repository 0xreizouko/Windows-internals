#define BUILD_WINDOWS

#include<Windows.h>
#include<stdio.h>

#pragma comment(lib, "ntdll.lib")

extern "C" void __stdcall RtlGetVersion(OSVERSIONINFO*);

int main() {
    HANDLE hProcess;
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, 6820);
    return 0;
}
