#include "NOMBC.h"

NOMBC::NOMBC(std::vector<uint8_t> romData, int romSize) {
    this->romData = romData;
    this->romSize = romSize;
}

NOMBC::~NOMBC()
{
}

