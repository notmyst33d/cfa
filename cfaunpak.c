#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "cfa.h"

int main(int argc, char **argv) {
    FILE *file;
    FILE *dump_file;
    char path[257];
    char header[5];
    CFAEntry *entry;

    if (argc < 3) {
        printf("Usage: cfaunpak [archive] [output folder]\n");
        return 0;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Cannot open archive\n");
        return 1;
    }

    if (mkdir(argv[2], S_IRWXU) != 0) {
        printf("Cannot create folder\n");
        return 1;
    }

    if (fread(header, 4, 1, file) != 1) {
        printf("Cannot read header\n");
        return 1;
    }

    if (strcmp(header, "CPAK") != 0) {
        printf("Not a cfapak archive\n");
        return 1;
    }

    while ((entry = cfa_read(file)) != NULL) {
        sprintf(path, "%s/%c.bin", argv[2], entry->name);
        dump_file = fopen(path, "w");

        printf("%c -> %s", entry->name, path);
        if (fwrite(entry->data, entry->size, 1, dump_file) != 1)
            printf(" err\n");
        else
            printf(" ok\n");

        fclose(dump_file);
        free(entry->data);
        free(entry);
    }

    fclose(file);

    return 0;
}
