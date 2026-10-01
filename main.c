#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef word address;
#define MEMSIZE (64*1024) 
byte mem[MEMSIZE];

void b_write(address adr, byte val) {
    mem[adr] = val;
}

byte b_read(address adr) {
    return mem[adr];
}

void w_write(address adr, word val) {
    mem[adr] = val & 0xFF;
    mem[adr + 1] = val >> 8;
}

word w_read(address adr) {
    return (mem[adr] | (mem[adr + 1] << 8)) & 0xFFFF;
}

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
        printf("%06o: %06o %04x\n", adr + i, w_read(adr + i), w_read(adr + i));
    }
}

int main(int argc, char *argv[])
{   
    if (argc == 3 && !strcmp(argv[1], "-t")) {
        load_file(argv[2]);
    } else {
        load_data();
    }
    

    mem_dump(0x40, 20);
    printf("\n");
    mem_dump(0x200, 0x26);

    return 0;
}