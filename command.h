#pragma once
#include "mem.h"

#define NO_PARAMS 0
#define HAS_DD 1
#define HAS_SS 2
#define HAS_NN 4
#define HAS_R 8
#define HAS_B 16

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
word get_nn(word w);
word get_opcode_r(word w);

extern const Command command[];
extern struct Argument ss, dd;
extern word nn, opcode_r;
extern byte is_b;

void do_add();
void do_sub();
void do_mov();
void do_movb();
void do_inc();
void do_sob();
void do_halt();
void do_nothing();
