#include <stdio.h>
#include <string.h>
#include "file_functions.h"
#include "list_functions.h"

void organizeFile(const char* file_dir);
const char *get_file_extension(const char *file);
int is_valid_file(const char *file_dir);

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








