#define BUILD_WINDOWS

#include<Windows.h>
#include<stdio.h>
#include "..\..\mylib\headers\SimpleLibrary.h"

#pragma comment(lib, "ntdll.lib")


int main() {
    int result = Add(5, 6);
    printf("Result: %d\n", result);
    return 0;
}
