#define BUILD_WINDOWS

#include<Windows.h>
#include<stdio.h>

#pragma comment(lib, "ntdll.lib")

int main() {
    STARTUPINFO si = { sizeof(si) };
    // memset(&si, 0, sizeof(si));
    // si.cb = sizeof(si);
    PROCESS_INFORMATION pi;
    WCHAR name[] = L"notepad";
    BOOL success = CreateProcess(NULL, name, NULL, NULL, FALSE, HIGH_PRIORITY_CLASS, NULL, NULL, &si, &pi);

    if(success) {
        printf("PID: %u  TID: %u\n", pi.dwProcessId, pi.dwThreadId);
       
        if(WAIT_TIMEOUT == WaitForSingleObject(pi.hProcess, 10000)) {
            printf("Notepad is still running.\n");
        } else { 
            DWORD code;
            GetExitCodeProcess(pi.hProcess, &code);
            printf("Notepad has terminated with code: %u\n", code);
        }
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        printf("[!] ERror creating process: %u\n", GetLastError());
    }
    return 0;
}
