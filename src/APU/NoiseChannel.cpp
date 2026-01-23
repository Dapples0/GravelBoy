#include "NoiseChannel.h"

NoiseChannel::NoiseChannel()
{
}

NoiseChannel::~NoiseChannel()
{
}

uint8_t NoiseChannel::read(uint16_t address)
{
    uint8_t res = 0xFF;
    if (address == 0xFF20) {
        res = 0xFF;
    } else if (address == 0xFF21) {
        res = NR42;
    } else if (address == 0xFF22) {
        res = NR43;
    } else if (address == 0xFF23) {
        res = NR44 | 0xBF;
    }
    return res;
}

void NoiseChannel::write(uint16_t address, uint8_t data) {
    if (address == 0xFF20) {
        NR41 = data | 0xC0;
    } else if (address == 0xFF21) {
        NR42 = data;
        if ((data & 0xF8) == 0) active = false;
    } else if (address == 0xFF22) {
        NR43 = data;
    } else if (address == 0xFF23) {
        NR44 = data | 0x3F;
        // TODO trigger
        if ((data & 0x80) == 0x80) {
            active = true;
        }
    }
}

void NoiseChannel::clear() {
    NR41 = 0xFF;
    NR42 = 0x00;
    NR43 = 0x00;
    NR44 = 0xFB;
}
