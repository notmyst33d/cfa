#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "cfa.h"

int main(int argc, char **argv) {
    FILE *file;
    FILE *dir_file;
    DIR *dir;
    struct dirent *dir_entry;
    char path[257];

    CFAEntry entry;
    unsigned int size;
    unsigned char name;
    unsigned char *data;

    if (argc < 3) {
        printf("Usage: cfapak [archive] [input folder]\n");
        return 0;
    }

    file = fopen(argv[1], "w");
    if (file == NULL) {
        printf("Cannot open archive\n");
        return 1;
    }

    dir = opendir(argv[2]);
    if (dir == NULL) {
        printf("Cannot open dir\n");
        return 1;
    }

    fwrite("CPAK", 4, 1, file);

    while ((dir_entry = readdir(dir)) != NULL) {
        if (strcmp(dir_entry->d_name, ".") == 0 || strcmp(dir_entry->d_name, "..") == 0)
            continue;

        sprintf(path, "%s/%s", argv[2], dir_entry->d_name);

        dir_file = fopen(path, "r");
        fseek(dir_file, 0, SEEK_END);
        size = ftell(dir_file);
        fseek(dir_file, 0, SEEK_SET);

        data = malloc(size);
        fread(data, size, 1, dir_file);

        name = dir_entry->d_name[0];
        entry = (CFAEntry) {
            .size = size,
            .name = name,
            .data = data,
        };

        printf("%s -> %c\n", path, name);

        cfa_write(&entry, file);
        fclose(dir_file);
        free(data);
    }

    closedir(dir);
    fclose(file);

    return 0;
}
