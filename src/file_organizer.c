#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <psapi.h>
#include <tchar.h> 
#include <strsafe.h>
#include "list_functions.h"
#include "file_functions.h"
#pragma comment(lib, "User32.lib")

const char *get_user(void); 
const char *get_file_extension(const char *file);
int is_valid_file(const char *file_dir);
int list_files(const char *file_dir);
void DisplayErrorBox(LPTSTR lpszFunction);

const int MAX_USER_LENGTH = 256 + 1;

int main (int argc, char *argv[]) {
    const char *user = get_user();

    printf("Hello, %s!\n", user);

    return 0;
}

const char *get_user(void) {
    char *username = malloc(sizeof(char) * (MAX_USER_LENGTH));
    if (username == NULL) { 
        printf("Memory allocation for user failed.\n");
        return NULL;
    }

    DWORD username_length = sizeof(username);

    if (GetUserName(username, &username_length)) { 
        return username;
    } else {
        free(username);
        printf("User could not be found. Please try again.\n");

        return NULL;
    }
}











































