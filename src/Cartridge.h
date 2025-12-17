#ifndef CARTRIDGE_H
#define CARTRIDGE_H

#include <vector>

#include "constants.h"

class Cartridge {
    public:
        Cartridge();
        ~Cartridge();

    private:
        // ROM Banks
        std::vector<std::vector<uint8_t>> romBank;
        uint8_t mbcType;

        // Catridge External Ram Banks
        std::vector<std::vector<uint8_t>> ramBank;

        
};






#endif