#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include "..\include\list_functions.h"
#include "..\include\file_functions.h"
#include "..\include\errorLogging.h"
#pragma comment(lib, "User32.lib")

const char *list_files(const char *file_dir);
int sortDirListAlpha(conditionDirectory *dirList);
const char *get_user(void);

const int MAX_USER_LENGTH = 260 + 1;

int getFileList(const char *destination, const char *source) {
    WIN32_FIND_DATA file_data;
    LARGE_INTEGER filesize;
    TCHAR szDir[MAX_PATH];
    size_t length_of_path;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError = 0;

    StringCchLength(source, MAX_PATH, &length_of_path);

    if (length_of_path > (MAX_PATH - 3)) {
      _tprintf(TEXT("\nDirectory path is too long.\n"));
       return -1; 
    }

    StringCchCopy(szDir, MAX_PATH, source);
    StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

    hFind = FindFirstFile(szDir, &file_data);

    if (INVALID_HANDLE_VALUE == hFind) {
       DisplayErrorBox(TEXT("FindFirstFile"));
       return dwError; 
    }
     
    do {
       if (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
         _tprintf(TEXT("  %s   <DIR>\n"), file_data.cFileName);
       } else {
          filesize.LowPart = file_data.nFileSizeLow;
          filesize.HighPart = file_data.nFileSizeHigh;
          _tprintf(TEXT("  %s   %ld bytes\n"), file_data.cFileName, filesize.QuadPart);
       }
    }
    while (FindNextFile(hFind, &file_data) != 0);
 
    dwError = GetLastError();
    if (dwError != ERROR_NO_MORE_FILES) {
       DisplayErrorBox(TEXT("FindFirstFile"));
    }

    FindClose(hFind);
    return dwError; //temporary return value
}

const char *get_user(void) {
    char *username = malloc(sizeof(char) * (MAX_USER_LENGTH));
    if (username == NULL) { 
        printf("Memory allocation for user failed.\n");
        return NULL;
    }

    DWORD username_length = sizeof(MAX_USER_LENGTH);

    if (GetUserName(username, &username_length)) { 
        return username;
    } else {
        free(username);
        printf("User could not be found. Please try again.\n");

        return NULL;
    }
}



































