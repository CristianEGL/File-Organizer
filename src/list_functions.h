#include <windows.h>

typedef struct conditionDirectory {
    char *dir;
    int condition;
} conditionDirectory;

void DisplayErrorBox(LPTSTR lpszFunction);
const char *list_files(const char *file_dir);
int sortDirListAlpha(conditionDirectory *dirList);
const char *get_user(void);



