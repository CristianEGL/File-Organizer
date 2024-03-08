#include <windows.h>

const char *list_files(const char *file_dir);
void DisplayErrorBox(LPTSTR lpszFunction);

typedef struct {     
    char *file_dir;                                           
    char *conditions;
} conditionDirectory; 

