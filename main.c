#include <stdio.h>
#include <stdint.h>
#include <assert.h>

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

int main(void) {
    printf("Hello hammamamamamam\n");
    return 0;
}