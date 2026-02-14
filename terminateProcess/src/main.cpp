#define BUILD_WINDOWS

#include<Windows.h>
#include<stdio.h>

#pragma comment(lib, "ntdll.lib")


int main(int argc, const char* argv[]) {

    if(argc < 2) {
        printf("[*] Usage: kill <pid>\n");
    } 

    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, atoi(argv[1]));
    if(!hProcess) {
        printf("[!] Error: %u\n", GetLastError());
    }

    if(TerminateProcess(hProcess, 100)) printf("[+] Success! Have a nice day.");
    else printf("[!] Error: %u\n", GetLastError());

    CloseHandle(hProcess);
    return 0;
}
