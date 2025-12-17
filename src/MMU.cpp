#include "MMU.h"
#include "MBC/NOMBC.h"

#include <fstream>
#include <iostream>
#include <ios>

// MMU::MMU()
// {
// }

// MMU::~MMU()
// {
// }

void MMU::connect(GPU *gpu, Joypad *joypad, Timer *timer, APU *apu) {
    this->gpu = gpu;
    this->joypad = joypad;
    this->timer = timer;
    this->apu = apu;

}

void MMU::loadRom(const char *filename) {

    std::ifstream file;
    std::ifstream stream(filename, std::ios::binary | std::ios::ate);
    int romSize;
    std::vector<uint8_t> romData;

    if (stream.is_open()) {
        char byte;
        romSize = (int)stream.tellg();
        std::cout << romSize << "\n";
        romData = std::vector<u_int8_t>(romSize);

        stream.seekg(0, std::ios::beg);
        for (int i = 0; i < romSize; i++) {
            char byte;
            stream.get(byte);
            romData[i] = byte;
        }
        stream.close();
    } else {
        std::cout << "Bad ROM" << "\n";
        exit(1);
    }

    // Sanity check - Title
	char title[17];
	title[16] = 0x00;
	for (int i = 0; i < 16; i++) {
		title[i] = (char)romData[0x134 + i];
	}
	std::cout << "Title: " << title << "\n";

    int cgb = (int)romData[0x143];

    std::cout << "CGB Flag: " << cgb << "\n";

    // Sanity Check - MBC type
    int type = (int)romData[0x147];
    std::cout << "Catridge Type: " << type << "\n";

    // Remember to save battery here as it is for save states

    // Sanity Check - SRAM Size
    int sRamSize = (int)romData[0x149];

    std::cout << "SRAM Size: " << sRamSize << "\n";

    // Sanity Check - ROM Size
	int headerRomSize = (int)romData[0x148];
	// Print
	std::cout << "ROM Size: " << 32 * (1 << headerRomSize) << "KB\n";


    // Determines MBC Type
    setMBC(type, romData, romSize);


}

void MMU::setMBC(int type, std::vector<uint8_t> romData, int romSize) {
    switch (type) {
        case 0x00: // ROM ONLY
            std::cout << "MBC Type: NOMBC\n";
            // this->rom = std::make_unique<NOMBC>(romData, romSize);
            break;





        default:
            std::cout << "No MBC type found, defaulting to MBC1\n";
            break;
    }
}
