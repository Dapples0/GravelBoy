#include "NOMBC.h"

NOMBC::NOMBC() {
}

NOMBC::~NOMBC()
{
}

uint8_t NOMBC::read(uint16_t address)
{
    return romBank[address / ROM_BANK_SIZE][address % ROM_BANK_SIZE];
}

void NOMBC::write(uint16_t address, uint8_t data)
{
}
