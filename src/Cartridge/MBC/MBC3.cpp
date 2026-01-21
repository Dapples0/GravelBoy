#include "MBC3.h"

MBC3::MBC3(std::vector<std::array<uint8_t, ROM_BANK_SIZE>> romData, int romSize, int extRamCode) {

}

MBC3::~MBC3() {

}

uint8_t MBC3::read(uint16_t address) {

    return 0xFF;
}

void MBC3::write(uint16_t address, uint8_t data) {
}

void MBC3::setBattery(std::string title, bool cgb) {

    
}