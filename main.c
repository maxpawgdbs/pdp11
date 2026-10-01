#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

#include "log.h"
#include "mem.h"
#include "run.h"

void load_data() {
    address adr, size;
    while (scanf("%hx%hx", &adr, &size) == 2) {
        for (int i = 0; i < size; i++) {
            byte b;
            scanf("%hhx", &b);
            b_write(adr + i, b);
        }
    }
}

void load_file(const char * filename) {
    FILE *file = fopen(filename, "r");
    address adr, size;
    while (fscanf(file, "%hx%hx", &adr, &size) == 2) {
        for (int i = 0; i < size; i++) {
            byte b;
            fscanf(file, "%hhx", &b);
            b_write(adr + i, b);
        }
    }
    fclose(file);
}

void mem_dump(address adr, int size) {
    for (int i = 0; i < size; i += 2) {
        trace(INFO, "%06o: %06o %04x\n", adr + i, w_read(adr + i), w_read(adr + i));
    }
}

int main(int argc, char *argv[])
{   
    if (argc == 3 && !strcmp(argv[1], "-t")) {
        load_file(argv[2]);
    } else {
        load_data();
    }
    
    set_log_level(TRACE);
    run();

    return 0;
}

