// asmarm.c - copyright 2007 Bruce Tomlin

#define versionName "ARM assembler"
#include "asmx.h"

enum
{
    o_Branch,       // Bcc / BLcc
    o_OneReg,       // Rm (only used for BX?)
    o_OneRegShift,  // Rd,shifter
    o_OneRegShiftS, // Rd,shifter with optional S
    o_TwoRegShiftS, // Rd,Rn,shifter with optional S
    o_SWI,          // SWI immed24
    o_BKPT,         // BKPT immed16
    o_BLX,          // BLX
    o_CLZ,          // CLZ
    o_MUL,          // MUL
    o_SWP,          // SWP
    o_LDM_STM,      // LDM/STM
    o_LDR_STR,      // LDR/STR
    o_MRS,          // MRS
    o_MSR,          // MSR
    o_MLA,          // MLA
    o_MLAL,         // SMLAL/SMULL/UMLAL/UMULL
    o_CDP,          // CDP
    o_MCR_MRC,      // MCR/MRC
    o_LDC_STC,      // LDC/STC
    o_ADR,          // ADR/ADRL
    o_Implied,      // NOP

//  o_Foo = o_LabelOp,
};

const char regs[] = "R0 R1 R2 R3 R4 R5 R6 R7 R8 R9 R10 R11 R12 R13 R14 R15 SP LR PC";
const char pregs[] = "P0 P1 P2 P3 P4 P5 P6 P7 P8 P9 P10 P11 P12 P13 P14 P15";
const char cregs[] = "CR0 CR1 CR2 CR3 CR4 CR5 CR6 CR7 CR8 CR9 CR10 CR11 CR12 CR13 CR14 CR15";
const char shifts[] = "LSL LSR ASR ROR RRX ASL";

struct OpcdRec ARM_opcdTab[] =
{
    // B and BL don't use wildcards to avoid false matches with BL, BLX, and BX
    {"B",       o_Branch,       0xEA000000},
    {"BEQ",     o_Branch,       0x0A000000},
    {"BNE",     o_Branch,       0x1A000000},
    {"BCS",     o_Branch,       0x2A000000},
    {"BHS",     o_Branch,       0x2A000000},
    {"BCC",     o_Branch,       0x3A000000},
    {"BLO",     o_Branch,       0x3A000000},
    {"BMI",     o_Branch,       0x4A000000},
    {"BPL",     o_Branch,       0x5A000000},
    {"BVS",     o_Branch,       0x6A000000},
    {"BVC",     o_Branch,       0x7A000000},
    {"BHI",     o_Branch,       0x8A000000},
    {"BLS",     o_Branch,       0x9A000000},
    {"BGE",     o_Branch,       0xAA000000},
    {"BLT",     o_Branch,       0xBA000000},
    {"BGT",     o_Branch,       0xCA000000},
    {"BLE",     o_Branch,       0xDA000000},
    {"BAL",     o_Branch,       0xEA000000},

    {"BL",      o_Branch,       0xEB000000},
    {"BLEQ",    o_Branch,       0x0B000000},
    {"BLNE",    o_Branch,       0x1B000000},
    {"BLCS",    o_Branch,       0x2B000000},
    {"BLHS",    o_Branch,       0x2B000000},
    {"BLCC",    o_Branch,       0x3B000000},
    {"BLLO",    o_Branch,       0x3B000000},
    {"BLMI",    o_Branch,       0x4B000000},
    {"BLPL",    o_Branch,       0x5B000000},
    {"BLVS",    o_Branch,       0x6B000000},
    {"BLVC",    o_Branch,       0x7B000000},
    {"BLHI",    o_Branch,       0x8B000000},
    {"BLLS",    o_Branch,       0x9B000000},
    {"BLGE",    o_Branch,       0xAB000000},
    {"BLLT",    o_Branch,       0xBB000000},
    {"BLGT",    o_Branch,       0xCB000000},
    {"BLLE",    o_Branch,       0xDB000000},
    {"BLAL",    o_Branch,       0xEB000000},

    {"BX*",     o_OneReg,       0x012FFF10}, // ARM5/ARM4T

    {"CMN*",    o_OneRegShift,  0x01700000},
    {"CMP*",    o_OneRegShift,  0x01500000},
    {"TEQ*",    o_OneRegShift,  0x01300000},
    {"TST*",    o_OneRegShift,  0x01100000},

    {"MOV*",    o_OneRegShiftS, 0x01A00000},
    {"MVN*",    o_OneRegShiftS, 0x01E00000},

    {"ADC*",    o_TwoRegShiftS, 0x00A00000},
    {"ADD*",    o_TwoRegShiftS, 0x00800000},
    {"AND*",    o_TwoRegShiftS, 0x00000000},
    {"BIC*",    o_TwoRegShiftS, 0x01C00000},
    {"EOR*",    o_TwoRegShiftS, 0x00200000},
    {"ORR*",    o_TwoRegShiftS, 0x01800000},
    {"RSB*",    o_TwoRegShiftS, 0x00600000},
    {"RSC*",    o_TwoRegShiftS, 0x00E00000},
    {"SBC*",    o_TwoRegShiftS, 0x00C00000},
    {"SUB*",    o_TwoRegShiftS, 0x00400000},

    {"SWI*",    o_SWI,          0x0F000000},

    {"BKPT",    o_BKPT,         0xE1200070},

    {"BLX*",    o_BLX,          0x012FFF30}, // ARM5

    {"CLZ*",    o_CLZ,          0x016F0F10}, // ARM5

    {"MUL*",    o_MUL,          0x00000090}, // ARM2

    {"SWP*",    o_SWP,          0x01000090}, // ARM2a/ARM3

    {"LDM*",    o_LDM_STM,      0x00100000},
    {"STM*",    o_LDM_STM,      0x00000000},

    {"LDR*",    o_LDR_STR,      0x00100000}, // LDRH/LDRSB/LDRSH = ARM4
    {"STR*",    o_LDR_STR,      0x00000000}, // STRH = ARM4

    {"MRS*",    o_MRS,          0x010F0000}, // ARM3

    {"MSR*",    o_MSR,          0x0120F000}, // ARM3

    {"MLA*",    o_MLA,          0x00200090}, // ARM2

    {"SMLAL*",  o_MLAL,         0x00E00090}, // ARM-M
    {"SMULL*",  o_MLAL,         0x00C00090}, // ARM-M
    {"UMLAL*",  o_MLAL,         0x00A00090}, // ARM-M
    {"UMULL*",  o_MLAL,         0x00800090}, // ARM-M

    {"CDP*",    o_CDP,          0x0E000000}, // ARM2/5

    {"MCR*",    o_MCR_MRC,      0x0E000010}, // ARM2/5
    {"MRC*",    o_MCR_MRC,      0x0E100010}, // ARM2/5

    {"LDC*",    o_LDC_STC,      0x0C100000}, // ARM2/5
    {"STC*",    o_LDC_STC,      0x0C000000}, // ARM2/5

    {"ADR*",    o_ADR,          0},          // pseudo-instruction

    {"NOP",     o_Implied,      0xE1A00000}, // pseudo-instruction = MOV R0,R0

    {"",        o_Illegal,      0}
};


// --------------------------------------------------------------


long ARMImmed(u_long val)
{
    // note: can't abort assembling instruction because it may cause phase errors

    if ((val & 0xFFFFFF00) == 0)
        return (val & 0xFF);
    else
    {
        // FIXME: need to handle shifts
        // bit 25 (I) = 1
        // bits 8-11 = rotate (immed8 is rotated right by 2 * this value)
        // bits 0-7 = immed8
        // the smallest value of rotate should be chosen
    }

    Error("Invalid immediate constant");
    return 0;
}


bool ARMShifter(u_long *shift)
{
    int     reg1,reg2,typ;
    Str255  word;
    char    *oldLine;
    int     token;
    int     val;

    *shift = 0;

    token = GetWord(word);
    if (token == '#')
    {
        val = Eval();
        *shift = (1 << 25) | ARMImmed(val);
    }
//  else if (token == '=')
//  {
//  }
    else
    {
        reg1 = FindReg(word,regs);
        if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
        if (CheckReg(reg1)) return 1;

        oldLine = linePtr;
        token = GetWord(word);
        if (token != ',')
        {
            linePtr = oldLine;
            *shift = reg1;
        }
        else
        {
            // shifts and rotates
            typ = GetReg(shifts);
            if (typ == 5) typ = 0; // ASL -> LSL
            if (typ < 0)
                IllegalOperand();
            else if (typ == 4)
            {
                *shift = 0x60 | reg1; // RRX
            }
            else
            {
                token = GetWord(word);
                if (token == '#')
                {
                    val = Eval();
                    // FIXME: need to range check immed5
                    *shift = (typ << 5) | reg1 | ((val & 0x1F) << 7);
                }
                else
                {
                    reg2 = FindReg(word,regs);
                    if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
                    if (CheckReg(reg2)) return 1;

                    *shift = (typ << 5) | (1 << 4) | reg1 | (reg2 << 8);
                }
            }
        }
    }

    return 0;
}


int ARMPlusMinus(void)
{
    Str255  word;
    char    *oldLine;
    int     token;

    oldLine = linePtr;
    token = GetWord(word);
    switch(token)
    {
        case '+':
            return 1;

        case '-':
            return 0;

        default:
            linePtr = oldLine;
            return 1;
    }
}


int ARMWriteback(void)
{
    Str255  word;
    char    *oldLine;
    int     token;

    oldLine = linePtr;
    token = GetWord(word);
    if (token == '!') return 1;

    linePtr = oldLine;
    return 0;
}


// addressing mode for LDR/STR/B/T/BT (post flag is TRUE for T opcode)
bool ARMAddrMode2(u_long *mode, bool post)
{
    int     reg1,reg2;
    Str255  word;
    char    *oldLine;
    int     token;
    int     sign;
    int     wb;
    int     val;
    int     typ;

    *mode = 0;

    if (Expect("[")) return 1;

    reg1 = GetReg(regs);
    if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
    if (CheckReg(reg1)) return 1;

    oldLine = linePtr;
    token = GetWord(word);
    if (token == ',')
    {
        if (post)
        {
            BadMode();
            return 1; // these modes not allowed for post-addrmode
        }

        oldLine = linePtr;
        token = GetWord(word);
        if (token == '#')
        {   // [Rn, #+/- ofs12
            val = Eval();
            if (Expect("]")) return 1;
            wb = ARMWriteback();

            // FIXME: need to check range

            if (val < 0)
                *mode = (reg1 << 16) | (1 << 24) | (wb << 21) | (-val & 0x0FFF);
            else
                *mode = (reg1 << 16) | (1 << 24) | (1 << 23) | (wb << 21) | (val & 0x0FFF);
        }
        else
        {
            linePtr = oldLine;
            sign = ARMPlusMinus();

            reg2 = GetReg(regs);
            if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg2)) return 1;

            oldLine = linePtr;
            token = GetWord(word);
            if (token == ',')
            {
                // FIXME ,shift #immed5
                typ = GetReg(shifts);
                if (typ == 5) typ = 0; // ASL -> LSL
                if (typ < 0)
                    IllegalOperand();
                else if (typ == 4)
                {
                    // RRX
                    if (Expect("]")) return 1;
                    wb = ARMWriteback();

                    *mode = (1 << 25) | (1 << 24) | (sign << 23) | (wb << 21) | (reg1 << 16) | (3 << 5) | reg2;
                }
                else
                {
                    Expect("#");
                    val = Eval();
                    // FIXME need to range check immed5, must be != 0
                    if (Expect("]")) return 1;
                    wb = ARMWriteback();

                    *mode = (1 << 25) | (1 << 24) | (sign << 23) | (wb << 21) | (reg1 << 16) | ((val & 31) << 7) | (typ << 5) | reg2;
                }
            }
            else
            {
                linePtr = oldLine;
                if (Expect("]")) return 1;
                wb = ARMWriteback();

                *mode = (1 << 25) | (1 << 24) | (sign << 23) | (wb << 21) | (reg1 << 16) | reg2;
            }


            // FIXME need to set bits
        }
    }
    else
    {
        linePtr = oldLine;
        if (Expect("]")) return 1;
        oldLine = linePtr;
        token = GetWord(word);
        if (!token)
        {
            // various possible ways of representing this
            // [Rn] => [Rn,#0]
            //*mode = (reg1 << 16) | (1 << 24) | (1 << 23);
            // [Rn] => [Rn],#0
            //*mode = (1 << 23) | (reg1 << 16);
            // [Rn] => [Rn,#-0]
            *mode = (reg1 << 16) | (1 << 24);
        }
        else if (token == '!')
        {
            if (post)
            {
                BadMode();
                return 1; // writeback modes not allowed for post-addrmode
            }

            // [Rn]! => [Rn,#0]!
            *mode = (1 << 24) | (1 << 23) | (1 << 21) | (reg1 << 16);
        }
        else
        {
            linePtr = oldLine;
            if (Comma()) return 1;

            oldLine = linePtr;
            token = GetWord(word);
            if (token == '#')
            {
                val = Eval();
                // FIXME: need to check range

                if (val < 0)
                    *mode = (reg1 << 16) | (-val & 0x0FFF);
                else
                    *mode = (1 << 23) | (reg1 << 16) | (val & 0x0FFF);
            }
            else
            {
                linePtr = oldLine;
                sign = ARMPlusMinus();

                reg2 = GetReg(regs);
                if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
                if (CheckReg(reg2)) return 1;

                oldLine = linePtr;
                token = GetWord(word);
                if (token == ',')
                {
                    // FIXME ,shift #immed5
                    typ = GetReg(shifts);
                    if (typ == 5) typ = 0; // ASL -> LSL
                    if (typ < 0)
                        IllegalOperand();
                    else if (typ == 4)
                    {
                        // RRX

                        *mode = (1 << 25) | (sign << 23) | (reg1 << 16) | (3 << 5) | reg2;
                    }
                    else
                    {
                        Expect("#");
                        val = Eval();
                        // FIXME need to range check immed5
                        *mode = (1 << 25) | (sign << 23) | (reg1 << 16) | ((val & 31) << 7) | (typ << 5) | reg2;
                    }
                }
                else
                {
                    linePtr = oldLine;

                    *mode = (1 << 25) | (sign << 23) | (reg1 << 16) | reg2;
                }

                // FIXME need to set bits
            }
        }
    }

    return 0;
}


// addressing mode for LDRH/LDRSB/LDRSH/STRH
bool ARMAddrMode3(u_long *mode)
{
    int     reg1,reg2;
    Str255  word;
    char    *oldLine;
    int     token;
    int     sign;
    int     wb;
    int     val;

    *mode = 0;

    if (Expect("[")) return 1;

    reg1 = GetReg(regs);
    if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
    if (CheckReg(reg1)) return 1;

    oldLine = linePtr;
    token = GetWord(word);
    if (token == ',')
    {
        oldLine = linePtr;
        token = GetWord(word);
        if (token == '#')
        {
            val = Eval();
            if (Expect("]")) return 1;
            wb = ARMWriteback();

            // FIXME: need to check range
            if (val < 0)
                *mode = (1 << 24) | (1 << 22) | (wb << 21) | (reg1 << 16) | ((-val & 0xF0) << 4) | (-val & 0x0F);
            else
                *mode = (1 << 24) | (1 << 23) | (1 << 22) | (wb << 21) | (reg1 << 16) | ((val & 0xF0) << 4) | (val & 0x0F);
        }
        else
        {
            linePtr = oldLine;
            sign = ARMPlusMinus();

            reg2 = GetReg(regs);
            if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg2)) return 1;

            if (Expect("]")) return 1;

            wb = ARMWriteback();

            *mode = (1 << 24) | (sign << 23) | (wb << 21) | (reg1 << 16) | reg2;
        }
    }
    else
    {
        linePtr = oldLine;
        if (Expect("]")) return 1;

        oldLine = linePtr;
        token = GetWord(word);
        if (!token)
        {
            // various possible ways of representing this
            // [Rn] => [Rn,#0]
            //*mode = (1 << 24) | (1 << 23) | (1 << 22) | (reg1 << 16);
            // [Rn] => [Rn],#0
            //*mode = (1 << 23) | (1 << 22) | (reg1 << 16);
            // [Rn] => [Rn,#-0]
            *mode = (1 << 24) | (1 << 22) | (reg1 << 16);
        }
        else if (token == '!')
        {
            // [Rn]! => [Rn,#0]!
            *mode = (1 << 24) | (1 << 23) | (1 << 22) | (1 << 21) | (reg1 << 16);
        }
        else
        {
            linePtr = oldLine;
            if (Comma()) return 1;

            oldLine = linePtr;
            token = GetWord(word);
            if (token == '#')
            {
                val = Eval();
                // FIXME: need to check range

                if (val < 0)
                    *mode = (1 << 22) | (reg1 << 16) | ((-val & 0xF0) << 4) | (-val & 0x0F);
                else
                    *mode = (1 << 23) | (1 << 22) | (reg1 << 16) | ((val & 0xF0) << 4) | (val & 0x0F);
            }
            else
            {
                linePtr = oldLine;
                sign = ARMPlusMinus();

                reg2 = GetReg(regs);
                if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
                if (CheckReg(reg2)) return 1;

                *mode =  (sign << 23) | (reg1 << 16) | reg2;
            }
        }
    }

    return 0;
}


// addressing mode for LDC/STC
bool ARMAddrMode5(u_long *mode)
{
    int     reg1;//,reg2;
    Str255  word;
    char    *oldLine;
    int     token;
//    int     sign;
    int     wb;
    int     val;

    *mode = 0;

    if (Expect("[")) return 1;

    reg1 = GetReg(regs);
    if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
    if (CheckReg(reg1)) return 1;

    oldLine = linePtr;
    token = GetWord(word);
    if (token == ',')
    {
        if (Expect("#")) return 1;

        val = Eval();
        if (Expect("]")) return 1;
        wb = ARMWriteback();

            // FIXME: need to check range
            if (val < 0)
                *mode = (1 << 24) | (wb << 21) | (reg1 << 16) | (((-val) >> 2) & 0xFF);
            else
                *mode = (1 << 24) | (1 << 23) | (wb << 21) | (reg1 << 16) | ((val >> 2) & 0xFF);
    }
    else
    {
        linePtr = oldLine;
        if (Expect("]")) return 1;

        oldLine = linePtr;
        token = GetWord(word);
        if (!token)
        {
            // various possible ways of representing this
            // [Rn] => [Rn],#0
            //*mode = (1 << 23) | (1 << 21) | (reg1 << 16);
            // [Rn] => [Rn],#-0
            //*mode = (1 << 21) | (reg1 << 16);
            // [Rn] => [Rn,#-0]
            *mode = (1 << 24) | (reg1 << 16);
        }
        else if (token == '!')
        {
            // [Rn]! => [Rn,#0]!
            *mode = (1 << 24) | (1 << 23) | (1 << 21) | (reg1 << 16);
        }
        else
        {
            linePtr = oldLine;

            if (Comma()) return 1;

            token = GetWord(word);
            if (token == '#')
            {
                val = Eval();
                // FIXME: need to check range
                if (val < 0)
                    *mode = (1 << 21) | (reg1 << 16) | ((-val >> 2) & 0xFF);
                else
                    *mode = (1 << 23) | (1 << 21) | (reg1 << 16) | ((val >> 2) & 0xFF);
            }
        else if (token == '{')
            {
                val = Eval();
                if (Expect("}")) return 1;

                // FIXME: need to check range
                *mode = (1 << 23) | (reg1 << 16) | (val & 0xFF);
            }
            else
            {
                Error("\"#\" or \"{\" expected");
                return 1;
            }
        }
    }

    return 0;
}


void SetARMMultiReg(int reg, u_short *regbits, bool *warned)
{
    if (!*warned && *regbits & (1 << reg))
    {
        Warning("register specified twice");
        *warned = TRUE;
    }
    *regbits |= 1 << reg;
}


int ARMGetMultiRegs(u_short *regbits)
{
    int     reg1,reg2,i;
    Str255  word;
    char    *oldLine;
    int     token;
    bool    warned;

    *regbits = 0;
    warned = FALSE;

    // looking for {r0,r2-r5,r6,lr}

    if (Expect("{")) return 1;

    // FIXME: at least one reg must be specified

    oldLine = linePtr;
    token = ',';
    while (token == ',')
    {
        reg1 = GetReg(regs);
        if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15

        if (reg1 < 0)
        {
            IllegalOperand();      // abort if not valid register
            break;
        }

        // set single register bit
        SetARMMultiReg(reg1, regbits, &warned);

        // check for - or ,
        oldLine = linePtr;
        token = GetWord(word);

        if (token == '-')       // register range
        {
            oldLine = linePtr;  // commit line position
            reg2 = GetReg(regs); // check for second register
            if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15

            if (reg2 < 0)
            {
                IllegalOperand();      // abort if not valid register
                break;
            }
            if (reg1 < reg2)
            {
                for (i = reg1 + 1 ; i <= reg2; i++)
                    SetARMMultiReg(i, regbits, &warned);
            }
            else if (reg1 > reg2)
            {
                for (i = reg1 - 1 ; i >= reg2; i--)
                    SetARMMultiReg(i, regbits, &warned);
            }
            oldLine = linePtr;  // commit line position
            token = GetWord(word);
        }
        if (token == ',')  // is there another register?
            oldLine = linePtr;  // commit line position
    }
    linePtr = oldLine;

    Expect("}");

    return 0;
}


// returns the LDM/STM type string
// returns -1 if invalid type string
// returns 0-3 for DA/IA/DB/IB, 4-7 for FAEA/FD/ED, (value & 3) << 23 to opcode
// if LDM and return >= 4, XOR result by 3 first
int ARMGetLDMType(char *word)
{
    char types[] = "DAIADBIBEDEAFDFA";
    int i,ofs;

    ofs = 0;

    if (!word[0] || !word[1]) // type string less than 2 bytes
        return -1;

    if (word[2] && word[3] && !word[4]) // 4-char type
        ofs = 2;
//    else if (word[2]) // not a 2-char type
//        return -1;

    for (i=0; i<8; i++)
        if (word[ofs] == types[i*2] && word[ofs+1] == types[i*2+1] && !word[ofs+2])
        {
            word[ofs] = 0; // remove LDM/STM type and leave condition code intact
            return i;
        }

    return -1;
}


enum { LDR_none, LDR_B, LDR_BT, LDR_H, LDR_SB, LDR_SH, LDR_T };

int ARMGetLDRType(char *word)
{
    char types[] = "B\000BTH\000SBSHT\000";
    int i,ofs;

    ofs = 0;

    if (!word[0]) return 0; // empty type string

    if (word[1] && word[2]) // 3- or 4-char type
        ofs = 2;

    for (i=0; i<6; i++)
        if (word[ofs] == types[i*2] && word[ofs+1] == types[i*2+1] && !(types[i*2+1] && word[ofs+2]))
        {
            word[ofs] = 0; // remove LDM/STM type and leave condition code intact
            return i+1;
        }

    return 0;
}


long ARMGetMSRReg(char *word)
{
    char *p;
    int  bit;
    long mask;

    if (word[0] != 'C' && word[0] != 'S') return -1;
    if (word[1] != 'P' || word[2] != 'S' || word[3] != 'R' || word[4] != '_' || !word[5]) return -1;

    mask = 0;
    p = word+5;
    while (*p)
    {
        switch(*p++)
        {
            case 'C': bit = 16; break;
            case 'X': bit = 17; break;
            case 'S': bit = 18; break;
            case 'F': bit = 19; break;
            default:  return -1;
        }
        if (mask & (1 << bit)) return -1; // don't allow repeated fields
        mask |= 1 << bit;
    }

    return ((word[0] == 'S') << 22) | mask;
}


bool ARMCond(int *cond, char *word)
{
    int reg1;

    *cond = 14; // default to ALways
    if (word[0])
    {
        reg1 = FindReg(word,"EQ NE CS CC MI PL VS VC HI LS GE LT GT LE AL HS LO");
        if (reg1 < 0) return TRUE;
        if (reg1 > 14) reg1 = reg1 - 14 + 2; // HS -> CS / LO -> CC
        *cond = reg1;
    }

    return FALSE;
}


bool ARMOpcodeFlag(char *word, char flag)
{
    if ((word[0]==flag) && (word[1]==0))
    {
        word[0] = 0;
        return 1;
    }

    if (word[0] && word[1] && (word[2]==flag) && (word[3]==0))
    {
        word[2] = 0;
        return 1;
    }

    if (word[0] && word[1] && word[2] && (word[3]==flag) && (word[4]==0))
    {
        word[2] = 0;
        return 1;
    }

    return 0;
}


int ARMEvalBranch(int width, int instrLen) // instrLen should be 8
{
    long val;
    long limit;

    limit = (1 << (width+1)) - 1;

    val = Eval();
    val = val - locPtr - instrLen;
    if (!errFlag && ((val & 3) || val < ~limit || val > limit))
        Error("Long branch out of range");

    return val;
}


int ARM_DoCPUOpcode(int typ, int parm)
{
    int     val,val2;
    int     i;
    Str255  word;
    char    *oldLine;
    int     token;
    int     reg1,reg2,reg3,reg4;
    int     cond;
    u_long  mode;
    u_short regbits;

    // get condition from opcode wildcard
    word[0]=0;
    if (isalnum(*linePtr))
        GetWord(word);

    switch(typ)
    {
        case o_Branch:       // Bcc / BLcc
            val = ARMEvalBranch(24,8);
            InstrL(parm | ((val >> 2) & 0x00FFFFFF));
            break;

        case o_OneReg:       // Rm
            if (ARMCond(&cond,word)) return 0;

            reg1 = GetReg(regs);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            InstrL(parm | (cond << 28) | reg1);
            break;

        case o_OneRegShiftS: // Rd,shifter with optional S
            val = ARMOpcodeFlag(word,'S');
            if (ARMCond(&cond,word)) return 0;

            reg1 = GetReg(regs);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            if (ARMShifter(&mode)) break;

            InstrL(parm | (cond << 28) | (val << 20) | (reg1 << 12) | mode);
            break;

        case o_OneRegShift:  // Rd,shifter
            if (ARMCond(&cond,word)) return 0;

            reg1 = GetReg(regs);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            if (ARMShifter(&mode)) break;

            InstrL(parm | (cond << 28) | (1 << 20) | (reg1 << 16) | mode);
            break;

        case o_TwoRegShiftS: // Rd,Rn,shifter with optional S
            val = ARMOpcodeFlag(word,'S');
            if (ARMCond(&cond,word)) return 0;

            reg1 = GetReg(regs);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            reg2 = GetReg(regs);
            if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg2)) break;

            if (Comma()) break;

            if (ARMShifter(&mode)) break;

            InstrL(parm | (cond << 28) | (val << 20) | (reg2 << 16) | (reg1 << 12) | mode);
            break;

        case o_SWI:          // SWI immed24
            if (ARMCond(&cond,word)) return 0;

            val = Eval();
            // FIXME: need to check immed24 range

            InstrL(parm | (cond << 28) | (val & 0x00FFFFFF));
            break;

        case o_BKPT:         // BKPT immed16
            val = Eval();
            // FIXME: need to check immed16 range

            InstrL(parm  | ((val << 4) & 0x000FFF00) | (val & 0x0F));
            break;

        case o_BLX:          // BLX
            if (ARMCond(&cond,word)) return 0;

            oldLine = linePtr;

            reg1 = GetReg(regs);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15

            if (reg1 >= 0)
            {
                InstrL(parm | (cond << 28) | reg1);
            }
            else
            {
                linePtr = oldLine;

                if (cond != 14) return 0; // this form of BLX is always unconditional

                val = ARMEvalBranch(25,8);
                InstrL(0xFA000000 | ((val << 23) & 0x01000000) | ((val >> 2) & 0x00FFFFFF));
            }

            break;

        case o_CLZ:          // CLZ
            if (ARMCond(&cond,word)) return 0;

            reg1 = GetReg(regs);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            reg2 = GetReg(regs);
            if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg2)) break;

            InstrL(parm | (cond << 28) | (reg1 << 12) | reg2);
            break;

        case o_MUL:          // MUL
            val = ARMOpcodeFlag(word,'S');
            if (ARMCond(&cond,word)) return 0;

            reg1 = GetReg(regs);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            reg2 = GetReg(regs);
            if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg2)) break;

            if (Comma()) break;

            reg3 = GetReg(regs);
            if (reg3 > 15) reg3 = reg3 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg3)) break;

            InstrL(parm | (cond << 28) | (val << 20) | (reg1 << 16) | (reg3 << 8) | reg2);
            break;

        case o_SWP:          // SWP
            val = ARMOpcodeFlag(word,'B');
            if (ARMCond(&cond,word)) return 0;

            reg1 = GetReg(regs);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            reg2 = GetReg(regs);
            if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg2)) break;

            if (Comma()) break;
            if (Expect("[")) break;

            reg3 = GetReg(regs);
            if (reg3 > 15) reg3 = reg3 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg3)) break;

            if (Expect("]")) break;

            InstrL(parm | (cond << 28) | (val << 22) | (reg3 << 16) | (reg1 << 12) | reg2);
            break;

        case o_LDM_STM:      // LDM/STM
            if ((reg2 = ARMGetLDMType(word)) < 0) return 0;
            if (ARMCond(&cond,word)) return 0;

            if (reg2 > 4 && parm) reg2 = reg2 ^ 3; // invert ED/FD/EA/MA for LDM
            reg2 = reg2 & 3; // mask off IB/IA/DB/DA bits

            val = 0; // clear ^ and ! bits

            reg1 = GetReg(regs);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            oldLine = linePtr;
            token = GetWord(word);
            if (token == '!')
                val = 1 << 21;
            else linePtr = oldLine;

            if (Comma()) break;

            if (ARMGetMultiRegs(&regbits)) break;

            oldLine = linePtr;
            token = GetWord(word);
            if (token == '^')
            {
                if (parm && (!val || (regbits & 0x8000)))
                    val |= (1 << 22);
                else
                {
                    IllegalOperand();
                    break;
                }
            }
            else linePtr = oldLine;

            InstrL(parm | 0x08000000 | (cond << 28) | (reg2 << 23) | (reg1 << 16) | val | regbits);

            break;

        case o_LDR_STR:      // LDR/STR
            if ((reg2 = ARMGetLDRType(word)) < 0) return 0;
            if (!parm && (reg2 == LDR_SB || reg2 == LDR_SH)) return 0; // STRSB and STRSH are invalid
            if (ARMCond(&cond,word)) return 0;

            reg1 = GetReg(regs);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            if (reg2 == LDR_H || reg2 == LDR_SB || reg2 == LDR_SH)
                val = ARMAddrMode3(&mode);
            else
                val = ARMAddrMode2(&mode,reg2 == LDR_BT || reg2 == LDR_T);
            if (val) break;

            switch(reg2)
            {
                case LDR_none:
                    InstrL(parm | (cond << 28) | 0x04000000 | (reg1 << 12) | mode);
                    break;

                case LDR_B:
                    InstrL(parm | (cond << 28) | 0x04400000 | (reg1 << 12) | mode);
                    break;

                case LDR_BT:
                    InstrL(parm | (cond << 28) | 0x04600000 | (reg1 << 12) | mode);
                    break;

                case LDR_H:
                    InstrL(parm | (cond << 28) | 0x000000B0 | (reg1 << 12) | mode);
                    break;

                case LDR_SB:
                    InstrL(parm | (cond << 28) | 0x000000D0 | (reg1 << 12) | mode);
                    break;

                case LDR_SH:
                    InstrL(parm | (cond << 28) | 0x000000F0 | (reg1 << 12) | mode);
                    break;

                case LDR_T:
                    InstrL(parm | (cond << 28) | 0x04200000 | (reg1 << 12) | mode);
                    break;
            }

            break;

        case o_MRS:          // MRS
            if (ARMCond(&cond,word)) return 0;

            reg1 = GetReg(regs);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            reg2 = GetReg("CPSR SPSR");
            if (CheckReg(reg2)) break;

            InstrL(parm | (cond << 28) | (reg2 << 22) | (reg1 << 12));
            break;

        case o_MSR:          // MSR
            if (ARMCond(&cond,word)) return 0;

            if (!GetWord(word))
            {
                MissingOperand();
                break;
            }
            reg1 = ARMGetMSRReg(word);
            if (reg1 < 0)
            {
                IllegalOperand();
                break;
            }

            if (Comma()) break;

            token = GetWord(word);
            if (token == '#')
            {
                val = Eval();
                InstrL(parm | (cond << 28) | (1 << 25) | reg1 | ARMImmed(val));
            }
            else
            {
                reg2 = FindReg(word,regs);
                if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
                if (CheckReg(reg2)) break;

                InstrL(parm | (cond << 28) | reg1 | reg2);
            }

            break;

        case o_MLA:          // MLA
            val = ARMOpcodeFlag(word,'S');
            if (ARMCond(&cond,word)) return 0;

            reg1 = GetReg(regs);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            reg2 = GetReg(regs);
            if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg2)) break;

            if (Comma()) break;

            reg3 = GetReg(regs);
            if (reg3 > 15) reg3 = reg3 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            reg4 = GetReg(regs);
            if (reg4 > 15) reg4 = reg4 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg2)) break;

            InstrL(parm | (cond << 28) | (val << 20) | (reg1 << 16) | (reg4 << 12) | (reg3 << 8) | reg2);
            break;

        case o_MLAL:         // MLAL
            val = ARMOpcodeFlag(word,'S');
            if (ARMCond(&cond,word)) return 0;

            reg1 = GetReg(regs);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            reg2 = GetReg(regs);
            if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg2)) break;

            if (Comma()) break;

            reg3 = GetReg(regs);
            if (reg3 > 15) reg3 = reg3 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            reg4 = GetReg(regs);
            if (reg4 > 15) reg4 = reg4 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg2)) break;

            InstrL(parm | (cond << 28) | (val << 20) | (reg2 << 16) | (reg1 << 12) | (reg4 << 8) | reg3);
            break;

        case o_CDP:          // CDP
            if (word[0] == '2' && !word[1])
                cond = 15;
            else
                if (ARMCond(&cond,word)) return 0;

            val = GetReg(pregs);
            if (CheckReg(val)) break;
            mode = val << 8;

            if (Comma()) break;

            val2 = Eval();
            if (val2 < 0 || val2 > 15)
                IllegalOperand();
            mode |= (val2 & 15) << 20;

            if (Comma()) break;

            reg1 = GetReg(cregs);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            reg2 = GetReg(cregs);
            if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg2)) break;

            if (Comma()) break;

            reg3 = GetReg(cregs);
            if (reg3 > 15) reg3 = reg3 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            val = Eval();
            if (val < 0 || val > 7)
                IllegalOperand();
            mode |= (val & 7) << 5;

            InstrL(parm | (cond << 28) | mode | (reg2 << 16) | (reg1 << 12) | reg3);
            break;

        case o_MCR_MRC:      // MCR/MRC
            if (word[0] == '2' && !word[1])
                cond = 15;
            else
                if (ARMCond(&cond,word)) return 0;

            val = GetReg(pregs);
            if (CheckReg(val)) break;
            mode = val << 8;

            if (Comma()) break;

            val2 = Eval();
            if (val2 < 0 || val2 > 7)
                IllegalOperand();
            mode |= (val2 & 7) << 21;

            if (Comma()) break;

            reg1 = GetReg(regs);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            reg2 = GetReg(cregs);
            if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg2)) break;

            if (Comma()) break;

            reg3 = GetReg(cregs);
            if (reg3 > 15) reg3 = reg3 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            oldLine = linePtr;
            token = GetWord(word);
            if (token == ',')
            {
                val = Eval();
                if (val < 0 || val > 7)
                    IllegalOperand();
                mode |= (val & 7) << 5;
            }
            else
            {
                linePtr = oldLine;
                if (token && Comma()) break;
            }

            InstrL(parm | (cond << 28) | mode | (reg2 << 16) | (reg1 << 12) | reg3);
            break;

        case o_LDC_STC:      // LDC/STC
            if (word[0] == '2')
            {
                val = 0;
                cond = 15;
                if (word[1] == 'L')
                {
                    val = 1;
                    if (word[2]) return 0;
                }
                else if (word[1]) return 0;
            }
            else
            {
                val = ARMOpcodeFlag(word,'L');
                if (ARMCond(&cond,word)) return 0;
            }

            reg1 = GetReg(pregs);
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            reg2 = GetReg(cregs);
            if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg2)) break;

            if (Comma()) break;

            if (ARMAddrMode5(&mode)) break;

            InstrL(parm | (cond << 28) | (val << 22) | (reg2 << 12) | (reg1 << 8) | mode);

            break;

        case o_ADR:          // ADR/ADRL
// ADRL Rn,address
            if (word[0] == 'L')
            {
                parm = 1;
                if (ARMCond(&cond,word+1)) return 0;
            }
            else
            {
                if (ARMCond(&cond,word)) return 0;
            }

            reg1 = GetReg(regs);
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            val = EvalLBranch(8);

            i = parm + 1; // number of longwords

            if (evalKnown && parm)
            {
                // *** determine auto size for ADRL
                if (-0xFF <= val && val <= 0xFF)
                    i = 1;
            }

            switch(i)
            {
                case 4:
                    break;

                case 3:
                    break;

                case 2:
                    if (val < 0)
                        InstrLL(0x028F0000 | (cond << 28) | (reg1 << 12) | (-val & 0xFF),
                                0x02800400 | (cond << 28) | (reg1 << 16) | (reg1 << 12) | ((-val >> 8) & 0xFF));
                    else
                        InstrLL(0x024F0000 | (cond << 28) | (reg1 << 12) | (val & 0xFF),
                                0x02400000 | (cond << 28) | (reg1 << 16) | (reg1 << 12) | ((val >> 8) & 0xFF));
                    break;

                default:
                    if (val < 0)
                        InstrL(0x028F0000 | (cond << 28) | (reg1 << 12) | (-val & 0xFF));
                    else
                        InstrL(0x024F0000 | (cond << 28) | (reg1 << 12) | (val & 0xFF));
                    break;
            }

// gets complicated because of offsets

//   ADR     R1,.            ; E24F1008
//   ADRL    R1,.            ; E24F1008
//   ADRL    R1,.+$1000      ; E28F1FFE E2811B03
//   ADRL    R1,.+$100000    ; E28F1FFE E2811BFF E2811703
//   ADRL    R1,.+$10000000  ; E28F1FFE E2811BFF E28117FF E2811303

if (pass == 2)
{
    printf("*** %.8X *** %s\n",val,line);
}

//            InstrL(   (cond << 28) | (val & 0x0FFF));
            break;

        case o_Implied:      // NOP
            InstrL(parm);
            break;

        default:
            return 0;
            break;
    }

    if (locPtr & 3)
    {
        Error("Code at non-longword-aligned address");
        // deposit extra bytes to reset alignment and prevent further errors
        for (i=locPtr & 3; i<4; i++)
            InstrAddB(0);
        // note: Inserting bytes in front won't work because offsets have already been assembled.
        // The line could be re-assembled by recursively calling DoCPUOpcode, but then
        // the label before the instruction would still be at the odd address.
    }

    return 1;
}


void AsmARMInit(void)
{
    char *p;

    p = AddAsm(versionName, &ARM_DoCPUOpcode, NULL, NULL);
    AddCPU(p, "ARM",    0, LITTLE_END, ADDR_24, LIST_24, 8, 0, ARM_opcdTab);
    AddCPU(p, "ARM_BE", 0, BIG_END,    ADDR_24, LIST_24, 8, 0, ARM_opcdTab);
    AddCPU(p, "ARM_LE", 0, LITTLE_END, ADDR_24, LIST_24, 8, 0, ARM_opcdTab);
}