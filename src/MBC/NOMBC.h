#ifndef NOMBC_H
#define NOMBC_H

#include "../Cartridge.h"

class NOMBC : public Cartridge {
    public:
        NOMBC();
        ~NOMBC();

        uint8_t read(uint16_t address) override;
        void write(uint16_t address, uint8_t data) override;        
    private:
        int romSize = 32; // KB
};


#endif