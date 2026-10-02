#pragma once
#include "mem.h"

#define NO_PARAMS 0
#define HAS_DD 1
#define HAS_SS 2

typedef struct {
    word mask;
    word opcode;
    char *name;
    void (*do_command)(void);
    char params;
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
