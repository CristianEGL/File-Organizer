#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <psapi.h>
#include <tchar.h> 
#include <strsafe.h>
#pragma comment(lib, "User32.lib")

const char *get_user(void); 
const char *get_file_extension(const char *file);
int is_valid_file(const char *file_dir);
void DisplayErrorBox(LPTSTR lpszFunction);

const int MAX_USER_LENGTH = 256 + 1;

int main (int argc, char *argv[]) {
    const char *user = get_user();
    char *dir_list[MAX_PATH + 1];

    printf("%s\n", get_file_extension("something.txt\n"));
    printf("%i\n", is_valid_file("C:\\Users\\crist\\Downloads\\Y2meta.app - Honolulu Los 10 mejores lugares para visitar en Honolulu, Hawaii..mp4"));

    MessageBox(
        NULL,
        "I cooka da pizza",
        "Kill",
        MB_OK
    );

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

void organizeFile(const char* file_dir) {
    printf("Organizing files...\n");
    printf("Files organized!\n");
}

const char *get_file_extension(const char *file) {
    if (!is_valid_file) {
        printf("File is not valid. Please try again.\n");

        return NULL;    
    }

    const char *extension = strrchr(file, '.');

    if (!extension) {
        printf("File extension not found.\n");

        return NULL;
    } else if (extension == file) {
        printf("File name starts with '.'. Make sure it has a name before the extension.\n");

        return NULL;
    } else {
        return extension;
    }
}

int is_valid_file(const char *file_dir) {
    FILE *file = fopen(file_dir, "r");

    if (file == NULL) {
        printf("File could not be opened/found.\n");

        return 0;
    }

    fclose(file);
    return 1;
}

int list_files(const char *file_dir) {
    WIN32_FIND_DATA file_data;
    LARGE_INTEGER filesize;
    TCHAR szDir[MAX_PATH];
    size_t length_of_path;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD dwError=0;

    StringCchLength(file_dir, MAX_PATH, &length_of_path);

    if (length_of_path > (MAX_PATH - 3)) {
      _tprintf(TEXT("\nDirectory path is too long.\n"));
       return (-1);
    }

    StringCchCopy(szDir, MAX_PATH, file_dir);
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
    return dwError;
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