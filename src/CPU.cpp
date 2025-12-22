#include "CPU.h"

#include <iostream>

CPU::CPU() {


}

CPU::~CPU() {
}

void CPU::connect(MMU *mmu) {
    this->mmu = mmu;
}

void CPU::execute() {
    uint8_t opcode = mmu->read8(pc);

    std::cout << "opcode: " << opcode << "\n";

    executeInstruction(opcode);

    
}

void CPU::executeInstruction(uint8_t opcode) {
    pc++;

    // Instructions Done 51/256
    switch (opcode) {
        case 0xCB: // 0xCB Prefixed
            break;

        /**
         * Misc Instructions
         */
        case 0x00: // NOP
            // Do nothing
            break;
        case 0x27: // DAA
            uint8_t adjustment = 0x00;
            if (getN()) {
                if (getH()) {
                    adjustment += 0x06;
                }

                if (getC()) {
                    adjustment += 0x60;
                }

                registers[REG_A] -= adjustment;


            } else {
                if (getH() || (registers[REG_A] & 0x0F > 0x09)) adjustment += 0x06;

                if (getC() || (registers[REG_A] > 0x99))  {
                    adjustment += 0x60;
                    setC(true);
                }
                
                registers[REG_A] += adjustment;
            }

            setH(false);
            setZ(registers[REG_A] == 0);

            break;

        case 0x10: // STOP - NOTES: As per pandocs: licensed roms do not use STOP outside of GCB speed switching. So implementing DMG slow mode might not be necessary/can be implemented later as a TODO

            // Only used for CGB
            if (!CGBMode) {
                return;
            }
            uint8_t key1 = mmu->read8(0xFF4D);

            // If armed switch to other mode
            if ((key1 & 0x01) == 0x01) {
                doubleSpeed = !doubleSpeed;

                // Clear bit0 and set speed
                ((key1 & 0x80) == 0x80) ? mmu->write8(0xFF4D, 0x00) : mmu->write8(0xFF4D, 0x80);   
            }

            pc++;
            break;

        /**
         * Load Instructions
         */
        case 0x40: // LD B, B
            registers[REG_B] = registers[REG_B];
            break;

        case 0x41: // LD B, C
            registers[REG_B] = registers[REG_C];
            break;

        case 0x42: // LD B, D
            registers[REG_B] = registers[REG_D];
            break;

        case 0x43: // LD B, E
            registers[REG_B] = registers[REG_E];
            break;
        
        case 0x44: // LD B, H
            registers[REG_B] = registers[REG_H];
            break;

        case 0x45: // LD B, L
            registers[REG_B] = registers[REG_L];
            break;

        case 0x46: // LD B, (HL)
            registers[REG_B] = mmu->read8(getHL());
            break;

        case 0x47: // LD B, A
            registers[REG_B] = registers[REG_A];
            break;
        
        case 0x48: // LD C, B
            registers[REG_C] = registers[REG_B];
            break;

        case 0x49: // LD C, C
            registers[REG_C] = registers[REG_C];
            break;

        case 0x4A: // LD C, D
            registers[REG_C] = registers[REG_D];
            break;

        case 0x4B: // LD C, E
            registers[REG_C] = registers[REG_E];
            break;

        case 0x4C: // LD C, H
            registers[REG_C] = registers[REG_H];
            break;

        case 0x4D: // LD C, L
            registers[REG_C] = registers[REG_L];
            break;

        case 0x4E: // LD C, (HL)
            registers[REG_C] = mmu->read8(getHL());
            break;

        case 0x4F: // LD C, A
            registers[REG_C] = registers[REG_A];
            break;

        case 0x50: // LD D, B
            registers[REG_D] == registers[REG_B];
            break;

        case 0x51: // LD D, C
            registers[REG_D] = registers[REG_C];
            break;

        case 0x52: // LD D, D
            registers[REG_D] = registers[REG_D];
            break;

        case 0x53: // LD D, E
            registers[REG_D] = registers[REG_E];
            break;

        case 0x54: // LD D, H
            registers[REG_D] = registers[REG_H];
            break;

        case 0x55: // LD D, L
            registers[REG_D] = registers[REG_L];
            break;


        case 0x56: // LD D, (HL)
            registers[REG_D] = mmu->read8(getHL());
            break;

        case 0x57: // LD D, A
            registers[REG_D] = registers[REG_A];
            break;

        case 0x58: // LD E, B
            registers[REG_E] = registers[REG_B];
            break;

        case 0x59: // LD E, C
            registers[REG_E] = registers[REG_C];
            break;

        case 0x5A: // LD E, D
            registers[REG_E] = registers[REG_D];
            break;

        case 0x5B: // LD E, E
            registers[REG_E] = registers[REG_E];
            break;

        case 0x5C: // LD E, H
            registers[REG_E] = registers[REG_H];
            break;

        case 0x5D: // LD E, L
            registers[REG_E] = registers[REG_L];
            break;

        case 0x5E: // LD E, (HL)
            registers[REG_E] = mmu->read8(getHL());
            break;

        case 0x5F: // LD E, A
            registers[REG_E] = registers[REG_A];
            break;

        case 0x60: // LD H, B
            registers[REG_H] = registers[REG_B];
            break;

        case 0x61: // LD H, C
            registers[REG_H] = registers[REG_C];
            break;

        case 0x62: // LD H, D
            registers[REG_H] = registers[REG_D];
            break;

        case 0x63: // LD H, E
            registers[REG_H] = registers[REG_E];
            break;

        case 0x64: // LD H, H
            registers[REG_H] = registers[REG_H];
            break;

        case 0x65: // LD H, L
            registers[REG_H] = registers[REG_L];
            break;

        case 0x66: // LD H, (HL)
            registers[REG_H] = mmu->read8(getHL());
            break;

        case 0x67: // LD H, A
            registers[REG_H] = registers[REG_A];
            break;

        case 0x68: // LD L, B
            registers[REG_L] = registers[REG_B];
            break;


        case 0x69: // LD L, C
            registers[REG_L] = registers[REG_C];
            break;

        case 0x6A: // LD L, D
            registers[REG_L] = registers[REG_D];
            break;

        case 0x6B: // LD L, E
            registers[REG_L] = registers[REG_E];
            break;


        case 0x6C: // LD L, H
            registers[REG_L] = registers[REG_E];
            break;

        case 0x6D: // LD L, L
            registers[REG_L] = registers[REG_L];
            break;

        case 0x6E: // LD L, (HL)
            registers[REG_L] = mmu->read8(getHL());
            break;

        case 0x6F: // LD L, A
            registers[REG_L] = registers[REG_A];
            break;


        




        // 8-bit Arithmetic Instructions




        // 16-bit Arithmetic Instructions



        // Bitwise Logic Instructions



        // Bit Flag Instructions



        // Bit Shift Instructions


        // Jumps and Subroutine Instructions


        // Carry Flag Instructions

        // Stack Manipulation Instructions

        // IE Instructions




        default:
            std::cerr << "Bad instruction | Opcode: " << opcode << " PC: " << pc << "\n";
            break;
    }
}


void CPU::setState(int mode)
{
    CGBMode = mode;

    if (!mode) {
        resetGB();
        
    } else {
        resetCGB();
    }
}

void CPU::resetGB()
{
    registers[REG_A] = 0x01;
    registers[REG_F] = 0xB0;
    registers[REG_B] = 0x00;
    registers[REG_C] = 0x13;
    registers[REG_D] = 0x00;
    registers[REG_E] = 0xD8;
    registers[REG_H] = 0x01;
    registers[REG_L] = 0x4D;
    pc = 0x100;
    sp = 0xFFFE;
    doubleSpeed = false;
}

void CPU::resetCGB()
{
    registers[REG_A] = 0x11;
    registers[REG_F] = 0x80;
    registers[REG_B] = 0x00;
    registers[REG_C] = 0x00;
    registers[REG_D] = 0xFF;
    registers[REG_E] = 0x56;
    registers[REG_H] = 0x00;
    registers[REG_L] = 0x0D;
    pc = 0x100;
    sp = 0xFFFE;
    doubleSpeed = false;
}

void CPU::setZ(bool set) {
    if (set) {
        registers[REG_F] |= 0x80;
    } else {
        registers[REG_F] &= 0x7F;
    }
}

void CPU::setN(bool set) {
    if (set) {
        registers[REG_F] |= 0x40;
    } else {
        registers[REG_F] &= 0xBF;
    }
}

void CPU::setH(bool set) {
    if (set) {
        registers[REG_F] |= 0x20;
    } else {
        registers[REG_F] &= 0xDF;
    }
}

void CPU::setC(bool set) {
    if (set) {
        registers[REG_F] |= 0x10;
    } else {
        registers[REG_F] &= 0xEF;
    }
}

bool CPU::getZ() {
    return (registers[REG_F] & 0x80) != 0;
}

bool CPU::getN()
{
    return (registers[REG_F] & 0x40) != 0;
}

bool CPU::getH()
{
    return (registers[REG_F] & 0x20) != 0;
}

bool CPU::getC()
{
    return (registers[REG_F] & 0x10) != 0;
}


uint16_t CPU::getBC() {
    return registers[REG_B] << 8 | registers[REG_C];
}

uint16_t CPU::getDE() {
    return registers[REG_D] << 8 | registers[REG_E];
}

uint16_t CPU::getHL() {
    return registers[REG_H] << 8 | registers[REG_L];
}


void CPU::RET(bool condition) {
    if (condition) {
        uint8_t low = mmu->read8(sp++);
        uint8_t high = mmu->read8(sp++);
        pc = (high << 8) | low;
        
        // pc = mmu->read8(sp++);
        // sp += 2;
    }
}

void CPU::CALL(bool condition) {
    uint16_t address = mmu->read16(pc);
    pc += 2;
    if (condition) {
        mmu->write8(--sp, (pc >> 8) & 0xFF);
        mmu->write8(--sp, pc & 0xFF);

        // Impliciet jump
        pc = address;
    }
}

void CPU::RST(uint8_t vec) {
    mmu->write8(--sp, (pc >> 8) & 0xFF);
    mmu->write8(--sp, pc & 0xFF);
    pc = vec;
}

void CPU::JP(bool condition) {
    if (condition) {
        pc = mmu->read16(pc);
    } else {
        pc += 2;
    }
}

uint8_t CPU::INC8(uint8_t val) {
    setN(false);
    setH((val & 0xF) + (1 & 0xF) > 0xF);
    
    uint8_t res = val + 1;
    setZ(res == 0);

    return res;
}


uint8_t CPU::DEC8(uint8_t val) {
    setN(true);
    setH((val & 0xF) < (1 & 0xF));
    
    uint8_t res = val - 1;
    setZ(res == 0);

    return res;
}

void CPU::ADD8(uint8_t val) {
    setN(false);
    setH((registers[REG_A] & 0xF) + (val & 0xF) > 0xF);
    setC((registers[REG_A] + val) > 0xFF);
    
    registers[REG_A] += val;

    setZ(registers[REG_A] == 0);
}

void CPU::ADD16(uint16_t val) {
    uint32_t res = getHL() + val;
    setN(false);
    setC((res > 0xFFFF));
    setH((getHL() & 0x0FFF) + (val & 0x0FFF) > 0x0FFF);

    // Set H and L registers
    registers[REG_H] = (res >> 8) & 0xFF; 
    registers[REG_L] = res & 0xFF;

}

void CPU::ADC(uint8_t val) {
    setN(false);
    uint8_t carry = getC();
    setH((registers[REG_A] & 0xF) + (val & 0xF) + carry > 0xF);
    setC((registers[REG_A] + val + carry) > 0xFF);

    registers[REG_A] += carry;

    setZ(registers[REG_A] == 0);
}

void CPU::SUB(uint8_t val) {
    setN(true);

    setH((registers[REG_A] & 0xF) < (val & 0xF));
    setC(registers[REG_A] < val);

    registers[REG_A] -= val;


    setZ(registers[REG_A] == 0);
}

void CPU::SBC(uint8_t val) {
    setN(true);

    uint8_t carry = getC();

    setH((registers[REG_A] & 0xF) < ((val & 0xF) + carry));
    setC(registers[REG_A] < (val + carry));

    registers[REG_A] -= carry;

    setZ(registers[REG_A] == 0);
}


void CPU::XOR(uint8_t val) {
    setN(false);
    setC(false);
    setH(false);

    uint8_t res = registers[REG_A] ^ val;

    setZ(res == 0);
    registers[REG_A] = res;
}

void CPU::OR(uint8_t val) {
    setN(false);
    setC(false);
    setH(false);

    uint8_t res = registers[REG_A] | val;

    setZ(res == 0);

    registers[REG_A] = res;
}

void CPU::CP(uint8_t val) {
    setN(true);
    setC(registers[REG_A] < val);
    setH((registers[REG_A] & 0xF) < (val & 0xF));
    setZ(registers[REG_A] == val);
}

// void CPU::setHAdd(uint8_t left, uint8_t right) {
//     setH((left & 0xF) + (right & 0xF) > 0xF);
// }

// void CPU::setHAdc(uint8_t left, uint8_t right, uint8_t carry) {
//     setH((left & 0xF) + (right & 0xF) + carry > 0xF);
// }

// void CPU::setHSub(uint8_t left, uint8_t right) {
//     setH((left & 0xF) < (right & 0xF));
// }

// void CPU::setHSbc(uint8_t left, uint8_t right, uint8_t carry) {
//     setH((left & 0xF) < ((right & 0xF) + carry));
// }

// void CPU::setCAdd(uint8_t left, uint8_t right) {
//     setC((left + right) > 0xFF);
// }

// void CPU::setCAdc(uint8_t left, uint8_t right, uint8_t carry) {
//     setC((left + right + carry) > 0xFF);
// }

// void CPU::setCSub(uint8_t left, uint8_t right) {
//     setC(left < right);
// }

// void CPU::setCSbc(uint8_t left, uint8_t right, uint8_t carry) {
//     setC(left < (right + carry));
// }

uint8_t CPU::RES(uint8_t pos, uint8_t reg) {
    uint8_t mask = ~(1 << pos);
    
    return reg &= mask;
}

uint8_t CPU::RLC(uint8_t val) {
    uint8_t carry = (val & 0x80) >> 7;
    uint8_t res = (val << 1) | carry;

    setC((val & 0x80) != 0);
    setN(false);
    setH(false);
    setZ(res == 0);
    return res;
}

uint8_t CPU::RRC(uint8_t val) {
    uint8_t carry = (val & 0x01);
    uint8_t res = (val >> 1) | (carry << 7);

    setC(carry != 0);
    setN(false);
    setH(false);
    setZ(res == 0);
    return res;
}

uint8_t CPU::RL(uint8_t val) {
    uint8_t cFlag = (uint8_t)getC();
    uint8_t carry = (val & 0x80);
    uint8_t res = (val << 1) | cFlag;

    setC(carry != 0);
    setN(false);
    setH(false);
    setZ(res == 0);
    return res;
}

uint8_t CPU::RR(uint8_t val) {
    uint8_t cFlag = (uint8_t)getC();
    uint8_t carry = (val & 0x01);
    uint8_t res = (val >> 1) | (cFlag << 7);

    setC(carry != 0);
    setN(false);
    setH(false);
    setZ(res == 0);
    return res;
}

uint8_t CPU::SRA(uint8_t val) {
    uint8_t sign = (val & 0x80);
    uint8_t carry = (val & 0x01);
    uint8_t res = (val >> 1) | sign;
    setC(carry != 0);
    setN(false);
    setH(false);
    setZ(res == 0);
    return res;
}

uint8_t CPU::SLA(uint8_t val) {
    uint8_t res = val << 1;

    setC((val & 0x80) != 0);
    setN(false);
    setH(false);
    setZ(res == 0);
    return res;
}

uint8_t CPU::SRL(uint8_t val)
{
    uint8_t carry = (val & 0x01);
    uint8_t res = (val >> 1);

    setC(carry != 0);
    setN(false);
    setH(false);
    setZ(res == 0);
    return res;
}

uint8_t CPU::SET(uint8_t pos, uint8_t reg) {
    return reg | (0x01 << pos);
}

void CPU::BIT(uint8_t pos, uint8_t reg) {
    setN(false);
    setH(true);
    setZ((reg & (0x01 << pos)) == 0);
}


