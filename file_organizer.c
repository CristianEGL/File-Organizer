#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>

const char *get_user(void);
const char *get_file_extension(const char *file);
int is_valid_file(const char *file_dir);

const int MAX_USER_LENGTH = 256 + 1;

int main (int argc, char **argv) {
    const char *user = get_user();
    char *dir_list[MAX_PATH + 1];

    printf("%s\n", get_file_extension("something.txt\n"));
    printf("%i\n", is_valid_file("C:\\Users\\crist\\Desktop\\does this work\\pretty_pl"));

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
        printf("Extension not found.\n");

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

    if (file_dir == NULL) {
        printf("File could not be opened/found.\n");

        return 0;
    }

    fclose(file);
    return 1;
}