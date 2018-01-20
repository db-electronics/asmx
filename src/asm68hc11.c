// asm68HC11.c - copyright 1998-2007 Bruce Tomlin

#define versionName "68HC11 assembler"
#include "asmx.h"

enum
{
    o_Inherent,     // implied instructions
    o_Inherent_01,  // implied instructions, 6801/6803/6811
    o_Inherent_03,  // implied instructions, 6803 only
    o_Inherent_11,  // implied instructions, 6811 only
    o_Relative,     // branch instructions
    o_Bit_03,       // 6303 AIM OIM EIM TIM instructions
    o_Bit,          // 6811 BSET/BCLR
    o_BRelative,    // 6811 BRSET/BRCLR
    o_Logical,      // instructions with multiple addressing modes
    o_Arith,        // arithmetic instructions with multiple addressing modes
    o_LArith,       // o_Arith instructions with 16-bit immediate modes
    o_LArith_01,    // o_Arith instructions with 16-bit immediate modes, 6801/6803/6811
    o_LArith_11,    // o_Arith instructions with 16-bit immediate modes, 6811 only

//  o_Foo = o_LabelOp,
};

enum cputype
{
    CPU_6800, CPU_6801, CPU_68HC11, CPU_6303
};

struct OpcdRec M68HC11_opcdTab[] =
{
    {"TEST",  o_Inherent_11, 0x00}, // 68HC11
    {"NOP",   o_Inherent,    0x01},
    {"IDIV",  o_Inherent_11, 0x02}, // 68HC11
    {"FDIV",  o_Inherent_11, 0x03}, // 68HC11
    {"LSRD",  o_Inherent_01, 0x04}, // 68HC11 6801 6303
    {"ASLD",  o_Inherent_01, 0x05}, // 68HC11 6801 6303
    {"TAP",   o_Inherent, 0x06},
    {"TPA",   o_Inherent, 0x07},
    {"INX",   o_Inherent, 0x08},
    {"DEX",   o_Inherent, 0x09},
    {"CLV",   o_Inherent, 0x0A},
    {"SEV",   o_Inherent, 0x0B},
    {"CLC",   o_Inherent, 0x0C},
    {"SEC",   o_Inherent, 0x0D},
    {"CLI",   o_Inherent, 0x0E},
    {"SEI",   o_Inherent, 0x0F},
    {"SBA",   o_Inherent, 0x10},
    {"CBA",   o_Inherent, 0x11},
    {"TAB",   o_Inherent, 0x16},
    {"TBA",   o_Inherent, 0x17},
    {"DAA",   o_Inherent, 0x19},
    {"ABA",   o_Inherent, 0x1B},
    {"TSX",   o_Inherent, 0x30},
    {"INS",   o_Inherent, 0x31},
    {"PULA",  o_Inherent, 0x32},
    {"PULB",  o_Inherent, 0x33},
    {"DES",   o_Inherent, 0x34},
    {"TXS",   o_Inherent, 0x35},
    {"PSHA",  o_Inherent, 0x36},
    {"PSHB",  o_Inherent, 0x37},
    {"PULX",  o_Inherent_01, 0x38}, // 68HC11 6801 6303
    {"RTS",   o_Inherent,    0x39},
    {"ABX",   o_Inherent_01, 0x3A}, // 68HC11 6801 6303
    {"RTI",   o_Inherent,    0x3B},
    {"PSHX",  o_Inherent_01, 0x3C}, // 68HC11 6801 6303
    {"MUL",   o_Inherent_01, 0x3D}, // 68HC11 6801 6303
    {"WAI",   o_Inherent, 0x3E},
    {"SWI",   o_Inherent, 0x3F},
    {"NEGA",  o_Inherent, 0x40},
    {"COMA",  o_Inherent, 0x43},
    {"LSRA",  o_Inherent, 0x44},
    {"RORA",  o_Inherent, 0x46},
    {"ASRA",  o_Inherent, 0x47},
    {"ASLA",  o_Inherent, 0x48},
    {"ROLA",  o_Inherent, 0x49},
    {"DECA",  o_Inherent, 0x4A},
    {"INCA",  o_Inherent, 0x4C},
    {"TSTA",  o_Inherent, 0x4D},
    {"CLRA",  o_Inherent, 0x4F},
    {"NEGB",  o_Inherent, 0x50},
    {"COMB",  o_Inherent, 0x53},
    {"LSRB",  o_Inherent, 0x54},
    {"RORB",  o_Inherent, 0x56},
    {"ASRB",  o_Inherent, 0x57},
    {"ASLB",  o_Inherent, 0x58},
    {"ROLB",  o_Inherent, 0x59},
    {"DECB",  o_Inherent, 0x5A},
    {"INCB",  o_Inherent, 0x5C},
    {"TSTB",  o_Inherent, 0x5D},
    {"CLRB",  o_Inherent, 0x5F},
    {"XGDX",  o_Inherent_11, 0x8F}, // 0x8F for 68HC11, 0x18 for 6303
    {"STOP",  o_Inherent_11, 0xCF}, // 68HC11
    {"SLP",   o_Inherent_03, 0x1A}, // 6303 only
    {"INY",   o_Inherent_11, 0x1808}, // 68HC11
    {"DEY",   o_Inherent_11, 0x1809}, // 68HC11
    {"TSY",   o_Inherent_11, 0x1830}, // 68HC11
    {"TYS",   o_Inherent_11, 0x1835}, // 68HC11
    {"PULY",  o_Inherent_11, 0x1838}, // 68HC11
    {"ABY",   o_Inherent_11, 0x183A}, // 68HC11
    {"PSHY",  o_Inherent_11, 0x183C}, // 68HC11
    {"XGDY",  o_Inherent_11, 0x188F}, // 68HC11

    {"BRA",   o_Relative, 0x20},
    {"BRN",   o_Relative, 0x21}, // 68HC11 6801 6303 (but probably works on 6800 anyhow)
    {"BHI",   o_Relative, 0x22},
    {"BLS",   o_Relative, 0x23},
    {"BCC",   o_Relative, 0x24},
    {"BHS",   o_Relative, 0x24},
    {"BCS",   o_Relative, 0x25},
    {"BLO",   o_Relative, 0x25},
    {"BNE",   o_Relative, 0x26},
    {"BEQ",   o_Relative, 0x27},
    {"BVC",   o_Relative, 0x28},
    {"BVS",   o_Relative, 0x29},
    {"BPL",   o_Relative, 0x2A},
    {"BMI",   o_Relative, 0x2B},
    {"BGE",   o_Relative, 0x2C},
    {"BLT",   o_Relative, 0x2D},
    {"BGT",   o_Relative, 0x2E},
    {"BLE",   o_Relative, 0x2F},
    {"BSR",   o_Relative, 0x8D},

    {"NEG",   o_Logical,  0x00}, // o_Logical: indexed,X = $60; extended = $70; indexed,Y = $1860
    {"COM",   o_Logical,  0x03},
    {"LSR",   o_Logical,  0x04},
    {"ROR",   o_Logical,  0x06},
    {"ASR",   o_Logical,  0x07},
    {"ASL",   o_Logical,  0x08},
    {"LSL",   o_Logical,  0x08},
    {"ROL",   o_Logical,  0x09},
    {"DEC",   o_Logical,  0x0A},
    {"INC",   o_Logical,  0x0C},
    {"TST",   o_Logical,  0x0D},
    {"JMP",   o_Logical,  0x0E},
    {"CLR",   o_Logical,  0x0F},

    {"SUBA",  o_Arith,    0x80}, // o_Arith: immediate = $00, direct = $10, indexed,X = $20, indexed,Y = $1820
    {"CMPA",  o_Arith,    0x81}, //           extended = $30
    {"SBCA",  o_Arith,    0x82},
    {"SUBD",  o_LArith_01,0x83}, // 68HC11 6801 6303
    {"ANDA",  o_Arith,    0x84},
    {"BITA",  o_Arith,    0x85},
    {"LDAA",  o_Arith,    0x86},
    {"STAA",  o_Arith,    0x97},
    {"EORA",  o_Arith,    0x88},
    {"ADCA",  o_Arith,    0x89},
    {"ORAA",  o_Arith,    0x8A},
    {"ADDA",  o_Arith,    0x8B},
    {"CPX",   o_LArith,   0x8C},
    {"JSR",   o_Arith,    0x9D}, // 9D is 68HC11 6801 6303 only
    {"LDS",   o_LArith,   0x8E},
    {"STS",   o_Arith,    0x9F},
    {"SUBB",  o_Arith,    0xC0},
    {"CMPB",  o_Arith,    0xC1},
    {"SBCB",  o_Arith,    0xC2},
    {"ADDD",  o_LArith_01,0xC3}, // 68HC11 6801 6303
    {"ANDB",  o_Arith,    0xC4},
    {"BITB",  o_Arith,    0xC5},
    {"LDAB",  o_Arith,    0xC6},
    {"STAB",  o_Arith,    0xD7},
    {"EORB",  o_Arith,    0xC8},
    {"ADCB",  o_Arith,    0xC9},
    {"ORAB",  o_Arith,    0xCA},
    {"ADDB",  o_Arith,    0xCB},
    {"LDD",   o_LArith_01,0xCC}, // 68HC11 6801 6303
    {"STD",   o_LArith_01,0xDD}, // 68HC11 6801 6303
    {"LDX",   o_LArith,   0xCE},
    {"STX",   o_Arith,    0xDF},
    {"CPD",   o_LArith_11,0x1A83}, // 68HC11
    {"CPY",   o_LArith_11,0x188C}, // 68HC11
    {"LDY",   o_LArith_11,0x18CE}, // 68HC11
    {"STY",   o_LArith_11,0x18DF}, // 68HC11

    {"BSET",  o_Bit,      0},
    {"BCLR",  o_Bit,      1},
    {"BRSET", o_BRelative,0},
    {"BRCLR", o_BRelative,1},

    {"AIM", o_Bit_03, 0x61},
    {"OIM", o_Bit_03, 0x62},
    {"EIM", o_Bit_03, 0x65},
    {"TIM", o_Bit_03, 0x6B},

    {"",     o_Illegal, 0}
};


// --------------------------------------------------------------


int M68HC11_DoCPUOpcode(int typ, int parm)
{
    int     val,val2,val3;
    Str255  word;
    char    *oldLine;
    int     token;
    char    force;
    char    reg;

    switch(typ)
    {
        case o_Inherent_01: // implied instructions, 6801/6803/6811
            if (typ == o_Inherent_01 && curCPU == CPU_6800) return 0;
        case o_Inherent_03: // implied instructions, 6803 only
            if (typ == o_Inherent_03 && curCPU != CPU_6303) return 0;
        case o_Inherent_11: // implied instructions, 6811 only
            if (parm == 0x8F && curCPU == CPU_6303)    // 6303 XGDX
                parm = 0x18;
            else if (typ == o_Inherent_11 && curCPU != CPU_68HC11) return 0;
        case o_Inherent:
            InstrX(parm);
            break;

        case o_Relative:
            if (parm == 0x21 && curCPU == CPU_6800) return 0;  // BRN
            val = EvalBranch(2);
            InstrXB(parm,val);
            break;

        case o_Logical:
            val = Eval();

            oldLine = linePtr;
            token = GetWord(word);
            if (token == 0)
                InstrXW(parm + 0x70, val);
            else if (token == ',')
            {
                GetWord(word);
                if (word[1] == 0) switch(word[0])
                {
                    case 'X':
                        InstrXB(parm + 0x60, val);
                        break;

                    case 'Y':
                        if (curCPU == CPU_68HC11)
                        {
                            InstrXB(0x1800 + parm + 0x60, val);
                            break;
                        }

                    default:
                        BadMode();
                        break;
                }
            }
            else
            {
                linePtr = oldLine;
                Comma();
            }
            break;

        case o_LArith_01:
            if (typ == o_LArith_01 && curCPU == CPU_6800) return 0;
        case o_LArith_11:
            if (typ == o_LArith_11 && curCPU != CPU_68HC11) return 0;
        case o_Arith:
        case o_LArith:
            oldLine = linePtr;
            token = GetWord(word);
            if (token == '#')
            {
                if (parm & 0x10)    // immediate
                    Error("Invalid addressing mode");
                else
                {
                    val = Eval();
                    if (typ == o_Arith) InstrXB(parm & ~0x10, val);
                                else    InstrXW(parm & ~0x10, val);
                }
            }
            else
            {
                force = 0;
                parm = parm & ~0x10;

                if (token == '<' || token == '>')
                    force = token;
                else
                    linePtr = oldLine;


                val = Eval();

                oldLine = linePtr;
                token = GetWord(word);
                if (token == 0)
                {
                    if (((force != '>' && evalKnown && (val & 0xFF00) >> 8 == 0) || force == '<')
                                && (curCPU != CPU_6800 || parm != 0x8D))
                        InstrXB(parm + 0x10, val);  // <$xx
                    else
                        InstrXW(parm + 0x30, val);   // >$xxxx
                }
                else if (token == ',')
                {
                    GetWord(word);
                    if (word[1] == 0) switch(word[0])
                    {
                        case 'X':
                            if (parm >> 8 == 0x18)
                                InstrXB(0x1A00 + parm + 0x20, val);
                            else
                                InstrXB(         parm + 0x20, val);
                            break;

                        case 'Y':
                            if (curCPU == CPU_68HC11)
                            {
                                if (parm == 0x8C || parm == 0xCE || parm == 0xCF || (parm >> 8 == 0x1A))
                                    InstrXB(0xCD00 + parm + 0x20, val);
                                else
                                    InstrXB(0x1800 + parm + 0x20, val);
                                break;
                            }

                        default:
                            BadMode();
                            break;
                    }
                }
                else
                {
                    linePtr = oldLine;
                    Comma();
                }
            }
            break;

        case o_Bit_03:
            if (curCPU != CPU_6303) return 0;
            // AIM/OIM/EIM/TIM
            // opcode #,ofs,X (3 bytes)
            // opcode #,dir  (3 bytes)

            if (GetWord(word) != '#')
                BadMode();
            else
            {
                val = Eval();   // get immediate value
                Comma();
                val2 = Eval();  // get offset/address
                if (GetWord(word) == ',')
                {
                    GetWord(word);
                    if (word[0] != 'X' || word[1] != 0)
                        BadMode();
                    else
                        InstrXBB(parm, val, val2);
                }
                else // direct mode = +0x10
                    InstrXBB(parm + 0x10, val, val2);
            }
            break;

        case o_Bit:
            if (curCPU != CPU_68HC11) return 0;

            val = Eval();   // direct page address or offset
            reg = 0;

            oldLine = linePtr;  // if comma present, may signal ,X or ,Y
            if (GetWord(word) == ',')
            {
                oldLine = linePtr;
                GetWord(word);
                if (word[1] == 0 && (word[0] == 'X' || word[0] == 'Y'))
                {
                    reg = word[0];

                    oldLine = linePtr;  // eat optional comma after ,X or ,Y
                    if (GetWord(word) != ',')
                        linePtr = oldLine;
                }
                else linePtr = oldLine; // not ,X or ,Y so reposition to after comma
            }
            else linePtr = oldLine; // optional comma not present, bit comes next



            val2 = Eval();  // mask

            switch(reg)
            {
                case 'X':
                    InstrXBB(parm +   0x1C, val, val2);
                    break;

                case 'Y':
                    InstrXBB(parm + 0x181C, val, val2);
                    break;

                default:
                    InstrXBB(parm +   0x14, val, val2);
                    break;

            }
            break;

        case o_BRelative:
            if (curCPU != CPU_68HC11) return 0;

            val = Eval();   // direct page address or offset
            reg = 0;

            oldLine = linePtr;  // if comma present, may signal ,X or ,Y
            if (GetWord(word) == ',')
            {
                oldLine = linePtr;;
                GetWord(word);
                if (word[1] == 0 && (word[0] == 'X' || word[0] == 'Y'))
                {
                    reg = word[0];

                    oldLine = linePtr;  // eat optional comma after ,X or ,Y
                    if (GetWord(word) != ',')
                        linePtr = oldLine;
                }
                else linePtr = oldLine; // not ,X or ,Y so reposition to after comma
            }
            else linePtr = oldLine; // optional comma not present, bit comes next

            val2 = Eval();  // bit mask

            oldLine = linePtr;  // eat optional comma after bit mask
            if (GetWord(word) != ',')
                linePtr = oldLine;

            val3 = EvalBranch(4 + (reg == 'Y'));  // offset

            switch(reg)
            {
                case 'X':
                    InstrXBBB(parm +   0x1E, val, val2, val3);
                    break;

                case 'Y':
                    InstrXBBB(parm + 0x181E, val, val2, val3);
                    break;

                default:
                    InstrXBBB(parm +   0x12, val, val2, val3);
                    break;
            }
            break;

        default:
            return 0;
            break;
    }
    return 1;
}


void Asm68HC11Init(void)
{
    char *p;

    p = AddAsm(versionName, &M68HC11_DoCPUOpcode, NULL, NULL);
    AddCPU(p, "6800",    CPU_6800,   BIG_END, ADDR_16, LIST_24, 8, 0, M68HC11_opcdTab);
    AddCPU(p, "6801",    CPU_6801,   BIG_END, ADDR_16, LIST_24, 8, 0, M68HC11_opcdTab);
    AddCPU(p, "6802",    CPU_6800,   BIG_END, ADDR_16, LIST_24, 8, 0, M68HC11_opcdTab);
    AddCPU(p, "6803",    CPU_6801,   BIG_END, ADDR_16, LIST_24, 8, 0, M68HC11_opcdTab);
    AddCPU(p, "6808",    CPU_6801,   BIG_END, ADDR_16, LIST_24, 8, 0, M68HC11_opcdTab);
    AddCPU(p, "6303",    CPU_6303,   BIG_END, ADDR_16, LIST_24, 8, 0, M68HC11_opcdTab);
    AddCPU(p, "6811",    CPU_68HC11, BIG_END, ADDR_16, LIST_24, 8, 0, M68HC11_opcdTab);
    AddCPU(p, "68HC11",  CPU_68HC11, BIG_END, ADDR_16, LIST_24, 8, 0, M68HC11_opcdTab);
    AddCPU(p, "68HC711", CPU_68HC11, BIG_END, ADDR_16, LIST_24, 8, 0, M68HC11_opcdTab);
    AddCPU(p, "68HC811", CPU_68HC11, BIG_END, ADDR_16, LIST_24, 8, 0, M68HC11_opcdTab);
    AddCPU(p, "68HC99",  CPU_68HC11, BIG_END, ADDR_16, LIST_24, 8, 0, M68HC11_opcdTab);
}