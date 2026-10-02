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
                trace(TRACE, " ");
                
                if (command[i].params & 8) opcode_r = get_opcode_r(w);
                if (command[i].params & 4) nn = get_nn(w);
                if (command[i].params & 2) ss = get_mr(w >> 6);
                if (command[i].params & 1) dd = get_mr(w);

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