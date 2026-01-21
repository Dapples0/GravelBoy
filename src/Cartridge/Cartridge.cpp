#include "Cartridge.h"

#include <iostream>
Cartridge::Cartridge()
{
}

// Does nothing -> let subclass override the function
uint8_t Cartridge::read(uint16_t address)
{
    return 0;
}

// Does nothing -> let subclass override the function
void Cartridge::write(uint16_t address, uint8_t data)
{
}

std::vector<std::vector<uint8_t>> Cartridge::getRamBank(int extRamSize) {
    int numBanks;
    uint16_t bankSize = SRAM_BANK_SIZE;
    switch (extRamSize) {
        case 0x00:
            numBanks = 0;
            ramSize = 0;
            break;

        case 0x01:
            numBanks = 1;
            bankSize = SRAM_UNUSED_BANK_SIZE;
            ramSize = SRAM_UNUSED_BANK_SIZE;
            break;

        case 0x02:
            numBanks = 1;
            ramSize = SRAM_BANK_SIZE;
            break;
        
        case 0x03:
            numBanks = 4;
            ramSize = SRAM_BANK_SIZE * numBanks;
            break;
        
        case 0x04:
            numBanks = 16;
            ramSize = SRAM_BANK_SIZE * numBanks;
            break;

        case 0x05:
            numBanks = 8;
            ramSize = SRAM_BANK_SIZE * numBanks;
            break;

        default: // Default to 0x02
            numBanks = 1;
            ramSize = SRAM_BANK_SIZE;
            break;
    }
    std::cout << "Number of RAM Banks: " << numBanks << "\n";
    std::cout << "Bank Size: " << bankSize / 1000 << " KB" << "\n";
    std::cout << "Total Ram Size: " << ramSize / 1000 << " KB" << "\n";
    return std::vector<std::vector<uint8_t>>(numBanks, std::vector<uint8_t>(bankSize));
}

void Cartridge::setBattery(std::string title, bool cgb) {
    path = title;

    // handles cases where cgb enhancement version of a game shares the same title of the dmg version
    if (cgb) path.append("cgb.sav");
    else path.append(".sav");
    path = "saves/" + path;
    std::cout << "Save filepath: " << path << "\n";
    std::string folder = "saves/";
    if (!std::filesystem::exists(folder)) std::filesystem::create_directories(folder);

    battery = loadSave();

    
}

// Does nothing -> let subclass override the function
bool Cartridge::loadSave() {
    return false;
}

// Does nothing -> let subclass override the function
void Cartridge::save() {
}