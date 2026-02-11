#define BUILD_WINDOWS

#include<Windows.h>
#include<stdio.h>
#include "framework.h"

#pragma comment(lib, "ntdll.lib")

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved
) {
    switch(ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
        case DLL_PROCESS_DETACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            break;
    }
    return TRUE;
}