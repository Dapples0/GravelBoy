#include "Cartridge.h"

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
