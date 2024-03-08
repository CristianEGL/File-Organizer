#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <psapi.h>
#include <tchar.h> 
#include <strsafe.h>
#include "..\include\list_functions.h"
#include "..\include\file_functions.h"
#pragma comment(lib, "User32.lib")

int main (int argc, char **argv) {
    const char *user = get_user();

    printf("Hello, %s!\n", user);

    return 0;
}



