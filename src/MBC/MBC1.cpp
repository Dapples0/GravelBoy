#include "MBC1.h"
#include <iostream>
MBC1::MBC1(std::vector<std::array<uint8_t, ROM_BANK_SIZE>> romData, int romSize, int sRamSize) {
    this->romBank = romData;
    this->romSize = romSize;
    this->ramSize = sRamSize;
    this->ramBank = getRamBank(sRamSize);
    this->bankingMode = false;
    this->ramWrite = false;
}

MBC1::~MBC1()
{
}

uint8_t MBC1::read(uint16_t address) {
    // Read from ROM Bank 0
    if (address >= 0x0000 && address <= 0x3FFF) {
        if (bankingMode) {
            return romBank[(ramBankNumber << 5) % romSize][address];
        } else {
            return romBank[0][address];
        }
    }
    // Read from ROM Bank 1-NN
    if (address >= 0x4000 && address <= 0x7FFF) {
        return romBank[romBankNumber][address % ROM_BANK_SIZE];
    }

    // Read from RAM
    if (address >= 0xA000 && address <= 0xBFFF) {
        if (ramSize == 0 || !ramWrite) {
            return 0xFF;
        }

        if (bankingMode) {
            return ramBank[ramBankNumber][address];
        } else {
            return ramBank[0][address];
        }
    }

    std::cout << "Bad Read\n";
    return 0x0;
    
}

void MBC1::write(uint16_t address, uint8_t data) {
    // RAM Enable (Write Only)
    if (address <= 0x1FFF) {
        if ((data & 0x0F) == 0x0A) {
            ramWrite = true;
        } else {
            ramWrite = false;
            // battery save here TODO
        }        
    } 
    // ROM Bank Number (Write Only) - Selects which ROM Bank to use
    if (address >= 0x2000 && address <= 0x3FFF) {
        romBankNumber = (data & 0x1F) == 0 ? 1 : (data & 0x1F);
    }
    // RAM Bank Number (Write Only) 
    if (address >= 0x4000 && address <= 0x5FFF) {
        ramBankNumber = data & 0x03;
        std::cout << "RAM Bank Number: " << ramBankNumber << "\n";
    }
    // Banking Mode Select (Write Only)
    if (address >= 0x6000 && address <= 0x7FFF) {
        bankingMode = (data & 1) == 1;
    }
    // Write
    if (address >= 0xA000 && address <= 0xBFFF) {
        if (ramSize == 0 || !ramWrite) {
            return;
        }

        if (bankingMode) {
            ramBank[ramBankNumber][address % SRAM_BANK_SIZE] = data;
        } else {
            ramBank[0][address % SRAM_BANK_SIZE] = data;
        }
    }
}
