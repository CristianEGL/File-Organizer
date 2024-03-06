#include "list_functions.h"
#include <windows.h>


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
         tprintf(TEXT("  %s   <DIR>\n"), file_data.cFileName);
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