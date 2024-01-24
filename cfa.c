#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cfa.h"

CFAEntry *cfa_read(FILE *file) {
    unsigned int size;
    unsigned char name;
    unsigned char *data;

    if (fread(&size, 4, 1, file) != 1)
        return NULL;

    data = malloc(size);

    if (fread(&name, 1, 1, file) != 1)
        return NULL;

    if (fread(data, size, 1, file) != 1)
        return NULL;

    CFAEntry *entry = malloc(sizeof(CFAEntry));
    entry->size = size;
    entry->name = name;
    entry->data = data;

    return entry;
}

void cfa_write(CFAEntry *entry, FILE *file) {
    fwrite(&entry->size, 4, 1, file);
    fwrite(&entry->name, 1, 1, file);
    fwrite(entry->data, entry->size, 1, file);
}

