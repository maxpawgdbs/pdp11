#include <stdlib.h>

#include "log.h"

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