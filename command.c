#include <stdlib.h>

#include "log.h"
#include "command.h"

void do_add() {}
void do_mov() {}
void do_inc() {}
void do_sob() {}
void do_halt()
{
    trace(INFO, "\nTHE END!!!\n");
    exit(0);
}
void do_nothing() {}

const Command command[] = {
    {0xF000, 0x6000, "add", do_add},
    {0xF000, 0x1000, "mov", do_mov},
    {0xFFC0, 0x0A80, "inc", do_inc},
    {0xFE00, 0x7E00, "sob", do_sob},
    {0xFFFF, 0x0000, "halt", do_halt},
    {0x0000, 0x0000, "unknown", do_nothing},
};