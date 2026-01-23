#include "SquareSweepChannel.h"

SquareSweepChannel::SquareSweepChannel()
{
}

SquareSweepChannel::~SquareSweepChannel()
{
}

uint8_t SquareSweepChannel::read(uint16_t address) {
    uint8_t res = 0xFF;
    if (address == 0xFF10) {
        res = NR10 | 0x80;
    } else if (address == 0xFF11) {
        res = NR11 | 0x3F;
    } else if (address == 0xFF12) {
        res = NR12;
    } else if (address == 0xFF13) {
        res = 0xFF;
    } else if (address == 0xFF14) {
        // Only Length Enable can be read
        res = NR14 | 0xBF;
    }
    return res;
}

void SquareSweepChannel::write(uint16_t address, uint8_t data) {
    if (address == 0xFF10) {
        NR10 = data | 0x80;
    } else if (address == 0xFF11) {
        NR11 = data;

    } else if (address == 0xFF12) {
        NR12 = data;
        if ((data & 0xF8) == 0) active = false;
    } else if (address == 0xFF13) {
        NR13 = data;
    } else if (address == 0xFF14) {
        NR14 = data | 0x38;
        // TODO Trigger event, reset timers and registers
        if ((data == 0x80) == 0x80) {
            active = true;
        }

    }
}

void SquareSweepChannel::clear() {
    NR10 = 0x00;
    NR11 = 0x00;
    NR12 = 0x00;
    NR13 = 0x00;
    NR14 = 0x00;
}
