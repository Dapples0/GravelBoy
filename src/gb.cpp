#include "gb.h"

gb::gb() {
    cpu = CPU();
    apu = APU();
    gpu = GPU();
    joypad = Joypad();
    mmu = MMU();
    timer = Timer();

    // cpu.connect(&mmu);
    mmu.connect(&gpu, &joypad, &timer, &apu);
}

gb::~gb()
{
}

void gb::run(const char *filename) {
    mmu.loadRom(filename);
}

