#include <stdio.h>
#include <windows.h>
#include <errno.h>
#include <stdlib.h>

const char *get_user(void);
const char *get_file_extension(const char *file);

int main (int argc, char **argv) {
    const char *user = get_user();
    char *dir_list[MAX_PATH + 1];

    printf("%s", get_file_extension("something"));

    return 0;
}

const char *get_user(void) {
    char *username = NULL;
    const DWORD username_length = 256 + 1;
    username = GetUserName(username, &username_length);

    if (username != NULL) {
        const char *username = username;
        return username;
    } else {
        perror("User could not be found. Please try again.");
    }
}

void organizeFile(const char* file_dir) {
    printf("Organizing files...");
    printf("Files organized!");
}

const char *get_file_extension(const char *file) {
    const char *extension = strrchr(file, ".");
    const char *file_extension = malloc(strlen(extension));

    if (!extension || extension == file) {
        free(file_extension);
        perror("Extension is not valid.");
    } else {
        file_extension = strcpy(file_extension, extension);
        return file_extension;
    }
}
