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
                command[i].do_command();
                break;
            }
        }
        trace(TRACE, "\n");
    }
}