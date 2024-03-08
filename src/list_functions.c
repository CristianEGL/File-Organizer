#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include "list_functions.h"
#include "file_functions.h"
#pragma comment(lib, "User32.lib")

void DisplayErrorBox(LPTSTR lpszFunction);
const char *list_files(const char *file_dir);
int sortDirListAlpha(conditionDirectory *dirList);
const char *get_user(void);

const int MAX_USER_LENGTH = 256 + 1;

const char *list_files(const char *file_dir) {
    WIN32_FIND_DATA file_data;
    LARGE_INTEGER filesize;
    TCHAR szDir[MAX_PATH];
    size_t length_of_path;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError = 0;

    StringCchLength(file_dir, MAX_PATH, &length_of_path);

    if (length_of_path > (MAX_PATH - 3)) {
      _tprintf(TEXT("\nDirectory path is too long.\n"));
       return NULL; 
    }

    StringCchCopy(szDir, MAX_PATH, file_dir);
    StringCchCat(szDir, MAX_PATH, TEXT("\\*"));

    hFind = FindFirstFile(szDir, &file_data);

    if (INVALID_HANDLE_VALUE == hFind) {
       DisplayErrorBox(TEXT("FindFirstFile"));
       return NULL; 
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
    return file_dir; //temporary return value
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

void DisplayErrorBox(LPTSTR lpszFunction) { 
    // Retrieve the system error message for the last-error code

    LPVOID lpMsgBuf;
    LPVOID lpDisplayBuf;
    DWORD dw = GetLastError(); 

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL );

    // Display the error message and clean up

    lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, 
        (lstrlen((LPCTSTR)lpMsgBuf)+lstrlen((LPCTSTR)lpszFunction)+40)*sizeof(TCHAR)); 
    StringCchPrintf((LPTSTR)lpDisplayBuf, 
        LocalSize(lpDisplayBuf) / sizeof(TCHAR),
        TEXT("%s failed with error %d: %s"), 
        lpszFunction, dw, lpMsgBuf); 
    MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK); 

    LocalFree(lpMsgBuf);
    LocalFree(lpDisplayBuf);
}

int sortDirListAlpha(conditionDirectory *dirList) {

    return 0;
}