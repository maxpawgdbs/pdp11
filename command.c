#include <endian.h>
#include <stdlib.h>

#include "log.h"
#include "mem.h"
#include "command.h"

const Command command[] = {
    {0xF000, 0x6000, "add", do_add, HAS_SS | HAS_DD},
    {0xF000, 0xE000, "sub", do_sub, HAS_SS | HAS_DD},
    {0xF000, 0x1000, "mov", do_mov, HAS_SS | HAS_DD},
    {0xFFC0, 0x0A80, "inc", do_inc, HAS_DD},
    {0xFE00, 0x7E00, "sob", do_sob, HAS_R | HAS_NN}, // временно
    {0xFFFF, 0x0000, "halt", do_halt, NO_PARAMS},
    {0x0000, 0x0000, "unknown", do_nothing, NO_PARAMS},
};

struct Argument ss, dd;
word nn, opcode_r;

struct Argument get_mr(word w) {
    struct Argument out;

    int r = w & 0x0007, m = (w >> 3) & 0x0007;
    word x;
    out.reg = r;
    out.mode = m;
    switch (m) {
        case (0):
            out.adr = r;
            out.value = reg[out.adr];
            trace(TRACE, "R%d ", r);
            break;
        case (1):
            out.adr = reg[r];
            out.value = w_read(out.adr);
            trace(TRACE, "(R%d) ", r);
            break;
        case (2):
            out.adr = reg[r];
            out.value = w_read(out.adr);
            reg[r] += 2;
            trace(TRACE, "(R%d)+ ", r);
            break;
        case (3):
            out.adr = reg[r];
            out.adr = w_read(out.adr);
            out.value = w_read(out.adr);
            reg[r] += 2;
            trace(TRACE, "@(R%d)+ ", r);
            break;
        case (4):
            // reg[r]--;
            // if (r >= 6) reg[r]--;
            reg[r] -= 2; // оставим определение байтовых команд до самих байтовых команд))
            out.adr = reg[r];
            out.value = w_read(out.adr);
            trace(TRACE, "-(R%d) ", r);
            break;
        case (5):
            reg[r] -= 2;
            out.adr = reg[r];
            out.adr = w_read(out.adr);
            out.value = w_read(out.adr);
            trace(TRACE, "@-(R%d) ", r);
            break;
        case (6):
            x = w_read(pc);
            pc += 2;
            out.adr = reg[r] + x; // интересно что благодаря переполнению можно забить на преобразование и считать в беззнаковых типах
            out.value = w_read(out.adr);
            trace(TRACE, "%d(R%d) ", x, r);
            break;
        case (7):
            x = w_read(pc);
            pc += 2;
            out.adr = reg[r] + x;
            out.adr = w_read(out.adr);
            out.value = w_read(out.adr);
            trace(TRACE, "@%d(R%d) ", x, r);
            break;
        default:
            trace(ERROR, "Mode %d not implented yet!\n", m);
    }
    return out;
}

word get_nn(word w) {
    trace(TRACE, "%d ", w & 0x003F);
    return w & 0x003F;
}

word get_opcode_r(word w) {
    trace(TRACE, "R%d ", (w >> 6) & 0x0007);
    return (w >> 6) & 0x0007;
}

void do_add() {
    switch (dd.mode) {
        case 0:
            reg[dd.adr] = ss.value + dd.value;
            break;
        default:
            w_write(dd.adr, ss.value + dd.value);
    }
}
void do_sub() {
    switch (dd.mode) {
        case 0:
            reg[dd.adr] -= ss.value;
            break;
        default:
            w_write(dd.adr, dd.value - ss.value);
    }
}
void do_mov() {
    switch (dd.mode) {
        case 0:
            reg[dd.adr] = ss.value;
            break;
        default:
            w_write(dd.adr, ss.value);
    }
}
void do_inc() {
    switch (dd.mode) {
        case 0:
            reg[dd.adr]++;
            break;
        default:
            w_write(dd.adr, dd.value + 1);
    }
}
void do_sob() {
    if (--reg[opcode_r] != 0) {
        pc -= nn * 2;
    }
}
void do_halt()
{
    trace(TRACE,
        "\nr0:%ho r1:%ho r2:%ho r3:%ho "
        "r4:%ho r5:%ho r6:%ho r7:%ho\n",
        reg[0], reg[1], reg[2], reg[3],
        reg[4], reg[5], reg[6], reg[7]);
    trace(INFO, "THE END!!!\n");
    exit(0);
}
void do_nothing() {}