#define BUILD_WINDOWS

#include<Windows.h>
#include<stdio.h>

#pragma comment(lib, "ntdll.lib")

int main() {
    HINSTANCE hInstDll = LoadLibrary(L"SimpleLibrary.dll");
    if(!hInstDll) {
        printf("[!] Error: %u\n", GetLastError());
        return 1;
    }

    typedef int (*PAdd)(int, int);

    PAdd add = (PAdd)GetProcAddress(hInstDll, "Add");
    if(add) { 
        int result = add(5, 6);
        printf("Result: %d\n", result);
    }
    return 0;
}
