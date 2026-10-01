#pragma once
#include "mem.h"

void do_add();
void do_mov();
void do_inc();
void do_sob();
void do_halt();
void do_nothing();

typedef struct {
    word mask;
    word opcode;
    char *name;
    void (*do_command)(void);
} Command;

extern const Command command[];