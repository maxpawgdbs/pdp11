#pragma once
#include "mem.h"

typedef struct {
    word mask;
    word opcode;
    char *name;
    void (*do_command)(void);
} Command;

struct Argument {
    word value;
    address adr;
    byte mode;
    byte reg;
};

struct Argument get_mr(word w);

extern const Command command[];
extern struct Argument ss, dd;

void do_add();
void do_sub();
void do_mov();
void do_inc();
void do_sob();
void do_halt();
void do_nothing();

enum Opcode {
    OP_HALT = 0x0000,
    OP_ADD = 0x6000,
    OP_SUB = 0xE000,
    OP_MOV = 0x1000,
    OP_INC = 0x0A80,
    OP_SOB = 0x7E00,
};