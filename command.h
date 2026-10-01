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

const Command command[] = {
    {0xF000, 0x6000, "add", do_add},
    {0xF000, 0x1000, "mov", do_mov},
    {0xFFC0, 0x0A80, "inc", do_inc},
    {0xFE00, 0x7E00, "sob", do_sob},
    {0xFFFF, 0x0000, "halt", do_halt},
    {0x0000, 0x0000, "unknown", do_nothing},
};