#include "gb.h"
#include <iostream>

gb::gb() {
    cpu = CPU();
    apu = APU();
    gpu = GPU();
    joypad = Joypad();
    mmu = MMU();
    timer = Timer();

    cpu.connect(&mmu);
    mmu.connect(&gpu, &joypad, &timer, &apu);
}

gb::~gb()
{
}

void gb::run(const char *filename) {
    int mode = mmu.loadRom(filename);

    std::cout << "--------------------------------\n";
    cpu.setState(mode);
    while (1)
        cpu.execute();
}

