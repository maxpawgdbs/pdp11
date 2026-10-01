#pragma once
#include <stdint.h>

typedef uint8_t byte;
typedef uint16_t word;
typedef word address;
#define MEMSIZE (64*1024) 
byte mem[MEMSIZE];
word reg[8];

void b_write(address adr, byte val);
byte b_read(address adr);
void w_write(address adr, word val);
word w_read(address adr);