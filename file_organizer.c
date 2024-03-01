#include <stdio.h>
#include <windows.h>

const char *get_user(void);
const char *get_file_extension(const char *file);

int main (int argc, char *argv) {
    const char *user = get_user();
    char *dir_list[MAX_PATH + 1];

    printf("%s", get_file_extension("something"));

    return 0;
}

const char *get_user(void) {
    char* username = NULL;
    const DWORD username_length = 256 + 1;
    username = GetUserName(username, &username_length);

    if (username != NULL) {
        const char *username = username;
        return username;
    } else {
        printf("Could not retrieve username.");
        return 1;
    }
}

void organizeFile(const char* file_dir) {
    printf("Organizing files...");
    if (file_dir )
    printf("Files organized!");  
}

const char *get_file_extension(const char *file) {
    char *extension = strrchr(file, ".");

    if (!extension || extension == file) {
        printf("File does not contain a file extension.");
        return 1;
    } else {
        const char *extension = extension + 1;
        return extension;
    }
}