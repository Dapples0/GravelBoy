#include "WaveChannel.h"

WaveChannel::WaveChannel()
{
}

WaveChannel::~WaveChannel()
{
}

uint8_t WaveChannel::read(uint16_t address)
{
    uint8_t res = 0xFF;
    if (address == 0xFF1A) {
        res = NR30 | 0x7F;
    } else if (address == 0xFF1B) {
        res = 0xFF;
    } else if (address == 0xFF1C) {
        res = NR32 | 0x9F;
    } else if (address == 0xFF1D) {
        res = 0xFF;
    } else if (address == 0xFF1E) {
        res = NR34 | 0xBF;
    } else if (address >= 0xFF30 && address <= 0xFF3F) {
        uint16_t relative_address = address & 0x000F;
        res = wavePatternRAM[relative_address];
    }
    return res;
}

void WaveChannel::write(uint16_t address, uint8_t data) {
    if (address == 0xFF1A) {
        NR30 = data | 0x7F;
        if ((NR30 & 0x80) == 0x80) dac = true;
        else dac = false;
    } else if (address == 0xFF1B) {
        NR31 = data;
    } else if (address == 0xFF1C) {
        NR32 = data | 0x9F;
    } else if (address == 0xFF1D) {
        NR33 = data;
    } else if (address == 0xFF1E) {
        NR34 = data | 0x9F;

        // TODO Trigger
        if ((data && 0x80) == 0x80 && dac) {
            active = true;
        }
    } else if (address >= 0xFF30 && address <= 0xFF3F) {
        uint16_t relative_address = address & 0x000F;
        wavePatternRAM[relative_address] = data;
    }
}

void WaveChannel::clear() {
    NR30 = 0x00;
    NR31 = 0x00;
    NR32 = 0x00;
    NR33 = 0x00;
    NR34 = 0x00;
}
