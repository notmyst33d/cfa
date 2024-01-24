#include <stdio.h>

typedef struct {
    unsigned int size;
    unsigned char name;
    unsigned char *data;
} CFAEntry;

CFAEntry *cfa_read(FILE *file);

void cfa_write(CFAEntry *entry, FILE *file);

