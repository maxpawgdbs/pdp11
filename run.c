#include <string.h>

#include "mem.h"
#include "log.h"
#include "command.h"

void run() {
    pc = 01000;
    word w;
    while (1) {
        w = w_read(pc);
        trace(TRACE, "%06o %06o: ", pc, w);
        pc += 2;

        for (int i = 0; ; i++) {
            if ((w & command[i].mask) == command[i].opcode) {
                trace(TRACE, command[i].name);
                if (!strcmp("add", command[i].name) ||
                    !strcmp("mov", command[i].name)) {
                    ss = get_mr(w >> 6);
                    dd = get_mr(w);
                }
                command[i].do_command();
                trace(TRACE,
                    "\nr0:%ho r1:%ho r2:%ho r3:%ho "
                    "r4:%ho r5:%ho r6:%ho r7:%ho\n",
                    reg[0], reg[1], reg[2], reg[3],
                    reg[4], reg[5], reg[6], reg[7]);
                break; 
            }
        }
    }
}