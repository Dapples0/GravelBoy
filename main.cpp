#include <iostream>

#include "src/gb.h"


int main() {
    gb gb;
    // 02-interrupts instr_timing interrupt_time interrupt_time
    // 01-read_timing  02-write_timing 03-modify_timing
    gb.run("rom/daa.gb");






    return 0;
}