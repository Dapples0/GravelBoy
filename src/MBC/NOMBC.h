#ifndef NOMBC_H
#define NOMBC_H

#include "../Cartridge.h"

class NOMBC : public Cartridge {
    public:
        NOMBC(std::vector<uint8_t> romData, int romSize);
        ~NOMBC();

    private:
        std::vector<uint8_t> romData;
        int romSize;
};


#endif