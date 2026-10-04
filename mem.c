#include <stdint.h>
#include <assert.h>

#include "mem.h"
#include "log.h"

byte mem[MEMSIZE];
word reg[8];

void b_write(address adr, byte val) {
    mem[adr] = val;
}

byte b_read(address adr) {
    return mem[adr];
}

void w_write(address adr, word val) {
    if (adr & 1) trace(ERROR, "Odd address for word!!!\n");
    mem[adr] = val & 0xFF;
    mem[adr + 1] = val >> 8;
}

word w_read(address adr) {
    if (adr & 1) trace(ERROR, "Odd address for word!!!\n");
    return (mem[adr] | (mem[adr + 1] << 8)) & 0xFFFF;
}