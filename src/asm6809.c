// asm6809.c - copyright 1998-2007 Bruce Tomlin

#define versionName "6809 assembler"
#include "asmx.h"

enum cputype
{
    CPU_6809,        // 6809 instructions only
    CPU_6309         // 6309 instructions enabled
};

enum
{
    o_Inherent,     // implied instructions
    o_Immediate,    // immediate instructions
    o_Relative,     // branch instructions
    o_LRelative,    // 16-bit branch instructions
    o_Indexed,      // indexed-only instructions
    o_PshPul,       // PSHS/PULS instructions
    o_ExgTfr,       // EXG/TFR instructions
    o_Logical,      // logical instructions with multiple addressing modes
    o_Arith,        // arithmetic instructions with multiple addressing modes
    o_LArith,       // o_Arith instructions with 16-bit immediate modes
    o_QArith,       // 6309 o_Arith with 4-byte immediate
    o_TFM,          // 6309 TFM instruction
    o_Bit,          // 6309 bit manipulation instructions

    o_6309 = 0x8000, // add to parm value for 6309 opcodes

    o_SETDP = o_LabelOp // SETDP pseudo-op
};

struct OpcdRec M6809_opcdTab[] =
{
    {"NOP" ,  o_Inherent, 0x12},
    {"SYNC",  o_Inherent, 0x13},
    {"DAA" ,  o_Inherent, 0x19},
    {"SEX" ,  o_Inherent, 0x1D},
    {"RTS" ,  o_Inherent, 0x39},
    {"ABX" ,  o_Inherent, 0x3A},
    {"RTI" ,  o_Inherent, 0x3B},
    {"MUL" ,  o_Inherent, 0x3D},
    {"SWI" ,  o_Inherent, 0x3F},
    {"NEGA",  o_Inherent, 0x40},
    {"COMA",  o_Inherent, 0x43},
    {"LSRA",  o_Inherent, 0x44},
    {"RORA",  o_Inherent, 0x46},
    {"ASRA",  o_Inherent, 0x47},
    {"ASLA",  o_Inherent, 0x48},
    {"LSLA",  o_Inherent, 0x48},
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
    {"LSLB",  o_Inherent, 0x58},
    {"ROLB",  o_Inherent, 0x59},
    {"DECB",  o_Inherent, 0x5A},
    {"INCB",  o_Inherent, 0x5C},
    {"TSTB",  o_Inherent, 0x5D},
    {"CLRB",  o_Inherent, 0x5F},
    {"SWI2",  o_Inherent, 0x103F},
    {"SWI3",  o_Inherent, 0x113F},

    {"ORCC",  o_Immediate, 0x1A},
    {"ANDCC", o_Immediate, 0x1C},
    {"CWAI",  o_Immediate, 0x3C},

    {"BRA",   o_Relative, 0x20},
    {"BRN",   o_Relative, 0x21},
    {"BHI",   o_Relative, 0x22},
    {"BLS",   o_Relative, 0x23},
    {"BCC",   o_Relative, 0x24},
    {"BCS",   o_Relative, 0x25},
    {"BHS",   o_Relative, 0x24},
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

    {"LBRA",  o_LRelative, 0x16},
    {"LBSR",  o_LRelative, 0x17},
    {"LBRN",  o_LRelative, 0x1021},
    {"LBHI",  o_LRelative, 0x1022},
    {"LBLS",  o_LRelative, 0x1023},
    {"LBCC",  o_LRelative, 0x1024},
    {"LBCS",  o_LRelative, 0x1025},
    {"LBHS",  o_LRelative, 0x1024},
    {"LBLO",  o_LRelative, 0x1025},
    {"LBNE",  o_LRelative, 0x1026},
    {"LBEQ",  o_LRelative, 0x1027},
    {"LBVC",  o_LRelative, 0x1028},
    {"LBVS",  o_LRelative, 0x1029},
    {"LBPL",  o_LRelative, 0x102A},
    {"LBMI",  o_LRelative, 0x102B},
    {"LBGE",  o_LRelative, 0x102C},
    {"LBLT",  o_LRelative, 0x102D},
    {"LBGT",  o_LRelative, 0x102E},
    {"LBLE",  o_LRelative, 0x102F},

    {"LEAX",  o_Indexed, 0x30},
    {"LEAY",  o_Indexed, 0x31},
    {"LEAS",  o_Indexed, 0x32},
    {"LEAU",  o_Indexed, 0x33},

    {"PSHS",  o_PshPul, 0x34},
    {"PULS",  o_PshPul, 0x35},
    {"PSHU",  o_PshPul, 0x36},
    {"PULU",  o_PshPul, 0x37},
    {"EXG",   o_ExgTfr, 0x1E},
    {"TFR",   o_ExgTfr, 0x1F},

    {"NEG",   o_Logical, 0x00}, // o_Logical: direct = 00; indexed = 60; extended = 70
    {"COM",   o_Logical, 0x03},
    {"LSR",   o_Logical, 0x04},
    {"ROR",   o_Logical, 0x06},
    {"ASR",   o_Logical, 0x07},
    {"ASL",   o_Logical, 0x08},
    {"LSL",   o_Logical, 0x08},
    {"ROL",   o_Logical, 0x09},
    {"DEC",   o_Logical, 0x0A},
    {"INC",   o_Logical, 0x0C},
    {"TST",   o_Logical, 0x0D},
    {"JMP",   o_Logical, 0x0E},
    {"CLR",   o_Logical, 0x0F},

    {"SUBA",  o_Arith, 0x80},   // iArith: immediate = 00, direct = 10, indexed = 20, extended = 30
    {"CMPA",  o_Arith, 0x81},
    {"SBCA",  o_Arith, 0x82},
    {"ANDA",  o_Arith, 0x84},
    {"BITA",  o_Arith, 0x85},
    {"LDA",   o_Arith, 0x86},
    {"STA",   o_Arith, 0x97},   // * 0x10 = no immediate
    {"EORA",  o_Arith, 0x88},
    {"ADCA",  o_Arith, 0x89},
    {"ORA",   o_Arith, 0x8A},
    {"ADDA",  o_Arith, 0x8B},
    {"JSR",   o_Arith, 0x9D},   // *
    {"STX",   o_Arith, 0x9F},   // *
    {"SUBB",  o_Arith, 0xC0},
    {"CMPB",  o_Arith, 0xC1},
    {"SBCB",  o_Arith, 0xC2},
    {"ANDB",  o_Arith, 0xC4},
    {"BITB",  o_Arith, 0xC5},
    {"LDB",   o_Arith, 0xC6},
    {"STB",   o_Arith, 0xD7},   // *
    {"EORB",  o_Arith, 0xC8},
    {"ADCB",  o_Arith, 0xC9},
    {"ORB",   o_Arith, 0xCA},
    {"ADDB",  o_Arith, 0xCB},
    {"JSR",   o_Arith, 0x9D},   // *
    {"STX",   o_Arith, 0x9F},   // *
    {"STD",   o_Arith, 0xDD},   // *
    {"STU",   o_Arith, 0xDF},   // *
    {"STY",   o_Arith, 0x109F}, // *
    {"STS",   o_Arith, 0x10DF}, // *

    {"SUBD" , o_LArith, 0x83},
    {"ADDD" , o_LArith, 0xC3},
    {"CMPX" , o_LArith, 0x8C},
    {"LDX"  , o_LArith, 0x8E},
    {"LDD"  , o_LArith, 0xCC},
    {"LDU"  , o_LArith, 0xCE},
    {"CMPD" , o_LArith, 0x1083},
    {"CMPY" , o_LArith, 0x108C},
    {"LDY"  , o_LArith, 0x108E},
    {"LDS"  , o_LArith, 0x10CE},
    {"CMPU" , o_LArith, 0x1183},
    {"CMPS" , o_LArith, 0x118C},

    {"SETDP",o_SETDP,0},

// 6800 compatiblity opcodes

    {"CLC",  o_Inherent, 0x1CFE},   // ANDCC #$FE
    {"CLI",  o_Inherent, 0x1CEF},   // ANDCC #$EF
    {"CLV",  o_Inherent, 0x1CFD},   // ANDCC #$FD
    {"SEC",  o_Inherent, 0x1A01},   // ORCC  #$01
    {"SEI",  o_Inherent, 0x1A10},   // ORCC  #$10
    {"SEV",  o_Inherent, 0x1A02},   // ORCC  #$02
    {"DEX",  o_Inherent, 0x301F},   // LEAX -1,X
    {"DES",  o_Inherent, 0x337F},   // LEAS -1,S
    {"INX",  o_Inherent, 0x3001},   // LEAX  1,X
    {"INS",  o_Inherent, 0x3361},   // LEAS  1,S
    {"PSHA", o_Inherent, 0x3402},   // PSHS A
    {"PSHB", o_Inherent, 0x3504},   // PSHS B
    {"PULA", o_Inherent, 0x3402},   // PULS A
    {"PULB", o_Inherent, 0x3504},   // PULS B
    {"ABA",  o_Inherent, 0xABE0},   // 3504 ABE0 = PSHS B / ADDA ,S+
    {"CBA",  o_Inherent, 0xA1E0},   // 3504 A1E0 = PSHS B / CMPA ,S+
    {"SBA",  o_Inherent, 0xA0E0},   // 3504 A0E0 = PSHS B / SUBA ,S+
    {"TAB",  o_Inherent, 0x1F89},   // TFR A,B
    {"TAP",  o_Inherent, 0x1F8A},   // TFR A,CC
    {"TBA",  o_Inherent, 0x1F98},   // TFR B,A
    {"TPA",  o_Inherent, 0x1FA8},   // TFR CC,A
    {"TSX",  o_Inherent, 0x1F41},   // TFR S,X
    {"TXS",  o_Inherent, 0x1F14},   // TFR X,S
    {"WAI",  o_Inherent, 0x3CFF},   // CWAI #$FF
    {"LDAA", o_Arith,    0x86},     // alternate mnemonic for LDA
    {"STAA", o_Arith,    0x97},     // alternate mnemonic for STA
    {"LDAB", o_Arith,    0xC6},     // alternate mnemonic for LDB
    {"STAB", o_Arith,    0xD7},     // alternate mnemonic for STB
    {"ORAA", o_Arith,    0x8A},     // alternate mnemonic for ORA
    {"ORAB", o_Arith,    0xCA},     // alternate mnemonic for ORB

// 6801 compatibility opcodes

    {"LSRD", o_Inherent, 0x4456},   // LSRA / RORB
    {"ASLD", o_Inherent, 0x5849},   // ASLB / ROLA
    {"LSLD", o_Inherent, 0x5849},   // ASLB / ROLA
    {"PULX", o_Inherent, 0x3410},   // PULS X
    {"PSHX", o_Inherent, 0x3510},   // PSHS X
    {"LDAD", o_LArith,   0xCC},     // alternate mnemonic for LDD
    {"STAD", o_Arith,    0xDD},     // alternate mnemonic for STD

// 6309 opcodes

    {"ASLD",  o_Inherent, 0x1048 | o_6309},
    {"ASRD",  o_Inherent, 0x1047 | o_6309},
    {"CLRD",  o_Inherent, 0x104F | o_6309},
    {"CLRE",  o_Inherent, 0x114F | o_6309},
    {"CLRF",  o_Inherent, 0x115F | o_6309},
    {"CLRW",  o_Inherent, 0x105F | o_6309},
    {"COMD",  o_Inherent, 0x1043 | o_6309},
    {"COME",  o_Inherent, 0x1143 | o_6309},
    {"COMF",  o_Inherent, 0x1153 | o_6309},
    {"COMW",  o_Inherent, 0x1053 | o_6309},
    {"DECD",  o_Inherent, 0x104A | o_6309},
    {"DECE",  o_Inherent, 0x114A | o_6309},
    {"DECF",  o_Inherent, 0x115A | o_6309},
    {"DECW",  o_Inherent, 0x105A | o_6309},
    {"INCD",  o_Inherent, 0x104C | o_6309},
    {"INCE",  o_Inherent, 0x114C | o_6309},
    {"INCF",  o_Inherent, 0x115C | o_6309},
    {"INCW",  o_Inherent, 0x105C | o_6309},
    {"LSLD",  o_Inherent, 0x1048 | o_6309},
    {"LSRD",  o_Inherent, 0x1044 | o_6309},
    {"LSRW",  o_Inherent, 0x1054 | o_6309},
    {"NEGD",  o_Inherent, 0x1040 | o_6309},
    {"PSHSW", o_Inherent, 0x1038 | o_6309},
    {"PSHUW", o_Inherent, 0x103A | o_6309},
    {"PULSW", o_Inherent, 0x1039 | o_6309},
    {"PULUW", o_Inherent, 0x103B | o_6309},
    {"ROLD",  o_Inherent, 0x1049 | o_6309},
    {"ROLW",  o_Inherent, 0x1059 | o_6309},
    {"RORD",  o_Inherent, 0x1046 | o_6309},
    {"RORW",  o_Inherent, 0x1056 | o_6309},
    {"SEXW",  o_Inherent, 0x14   | o_6309},
    {"TSTD",  o_Inherent, 0x104D | o_6309},
    {"TSTE",  o_Inherent, 0x114D | o_6309},
    {"TSTF",  o_Inherent, 0x115D | o_6309},
    {"TSTW",  o_Inherent, 0x105D | o_6309},

    {"BITMD", o_Immediate, 0x113C | o_6309},
    {"LDMD",  o_Immediate, 0x113D | o_6309},

    {"AIM",  o_Logical, 0x02 | o_6309},
    {"EIM",  o_Logical, 0x05 | o_6309},
    {"OIM",  o_Logical, 0x01 | o_6309},
    {"TIM",  o_Logical, 0x0B | o_6309},

    {"ADDE",  o_Arith, 0x118B | o_6309},
    {"ADDF",  o_Arith, 0x11CB | o_6309},
    {"CMPE",  o_Arith, 0x1181 | o_6309},
    {"CMPF",  o_Arith, 0x11C1 | o_6309},
    {"DIVD",  o_Arith, 0x118D | o_6309},
    {"LDE" ,  o_Arith, 0x1186 | o_6309},
    {"LDF" ,  o_Arith, 0x11C6 | o_6309},
    {"STE" ,  o_Arith, 0x1197 | o_6309},
    {"STF" ,  o_Arith, 0x11D7 | o_6309},
    {"STQ" ,  o_Arith, 0x10DD | o_6309},
    {"STS" ,  o_Arith, 0x10DF | o_6309},
    {"SUBE",  o_Arith, 0x1180 | o_6309},
    {"SUBF",  o_Arith, 0x11C0 | o_6309},

    {"ADCD",  o_LArith, 0x1089 | o_6309},
    {"ADDW",  o_LArith, 0x108B | o_6309},
    {"ANDD",  o_LArith, 0x1084 | o_6309},
    {"BITD",  o_LArith, 0x1085 | o_6309},
    {"CMPW",  o_LArith, 0x1081 | o_6309},
    {"DIVQ",  o_LArith, 0x118E | o_6309},
    {"EORD",  o_LArith, 0x1088 | o_6309},
    {"LDW" ,  o_LArith, 0x1086 | o_6309},
    {"MULD",  o_LArith, 0x118F | o_6309},
    {"ORD" ,  o_LArith, 0x108A | o_6309},
    {"SBCD",  o_LArith, 0x1082 | o_6309},
    {"STW" ,  o_LArith, 0x1097 | o_6309},
    {"SUBW",  o_LArith, 0x1080 | o_6309},

    {"LDQ" ,  o_QArith, 0x10CC | o_6309}, // special: immed is 0xCD

    {"ADCR",  o_ExgTfr, 0x1031 | o_6309},
    {"ADDR",  o_ExgTfr, 0x1030 | o_6309},
    {"ANDR",  o_ExgTfr, 0x1034 | o_6309},
    {"CMPR",  o_ExgTfr, 0x1037 | o_6309},
    {"EORR",  o_ExgTfr, 0x1036 | o_6309},
    {"ORR" ,  o_ExgTfr, 0x1035 | o_6309},
    {"SBCR",  o_ExgTfr, 0x1033 | o_6309},
    {"SUBR",  o_ExgTfr, 0x1032 | o_6309},

    {"TFM" ,  o_TFM, 0x1138 | o_6309},

    {"BAND",  o_Bit, 0x1130 | o_6309},
    {"BIAND", o_Bit, 0x1131 | o_6309},
    {"BOR" ,  o_Bit, 0x1132 | o_6309},
    {"BIOR",  o_Bit, 0x1133 | o_6309},
    {"BEOR",  o_Bit, 0x1134 | o_6309},
    {"BIEOR", o_Bit, 0x1135 | o_6309},
    {"LDBT",  o_Bit, 0x1136 | o_6309},
    {"STBT",  o_Bit, 0x1137 | o_6309},

    {"",     o_Illegal, 0}
};


const char tfrRegs[] = "D X Y U S PC X X A B CC DP"; // extra X's are placeholders
const char tfrRegs6309[] = "D X Y U S PC W V A B CC DP 0 00 E F";
const char pshRegs[] = "CC A B DP X Y U PC D S";
const char idxRegs[] = "X Y U S";
const char idxRegsW[] = "X Y U S W";

u_char dpReg;


// --------------------------------------------------------------


static void M6809_Indexed(int idxOp, int dirOp, int extOp)
{
//  idxOp is required
//  if dirOp == 0, use extOp
//  if extOp == 0, use idxOp

    int     indirect;
    char    *oldLine;
    int     token;
    Str255  word;
    int     reg;
    int     val;
    char    force;

    indirect = 0;
    force = 0;

    oldLine = linePtr;
    token = GetWord(word);
    if (token == '[')
    {
        indirect = 0x10;
        oldLine = linePtr;
        token = GetWord(word);
    }

    // handle A, B, D as tokens
    if (token == -1 && word[1] == 0 && (word[0] == 'A' || word[0] == 'B' || word[0] == 'D'))
    {
        token = word[0];
    }

    // handle E, F, W as tokens
    if (curCPU == CPU_6309 &&
        token == -1 && word[1] == 0 && (word[0] == 'E' || word[0] == 'F' || word[0] == 'W'))
    {
        token = word[0];
    }

    switch(token)
    {
        case ',':
            token = GetWord(word);
            if (token == '-')
            {
                if (*linePtr == '-')
                {
                    linePtr++;
                    GetWord(word);
                    reg = FindReg(word, idxRegsW);
                    if (curCPU == CPU_6309 && reg == 4)
                    {
                        // ,--W
                        InstrXB(idxOp, 0xEF + !!indirect);  // ,--X
                    }
                    else if (reg < 0 || reg > 3)
                        BadMode();
                    else
                        InstrXB(idxOp, reg * 0x20 + 0x83 + indirect);  // ,--X
                }
                else
                {
                    GetWord(word);
                    reg = FindReg(word, idxRegs);
                    if (reg < 0)
                        BadMode();
                    else
                        InstrXB(idxOp, reg * 0x20 + 0x82 + indirect);  // ,-X
                }
            }
            else
            {
                reg = FindReg(word, idxRegsW);
                if (curCPU == CPU_6309 && reg == 4)
                {
                    // ,W / ,W++
                    oldLine = linePtr;
                    token = GetWord(word);
                    switch(token)
                    {
                        case ']':
                            linePtr = oldLine;
                        case 0: // ,W
                            InstrXB(idxOp, 0x8F + !!indirect);  // ,X
                            break;
                        case '+': // ,W++
                            if (*linePtr == '+')
                            {
                                linePtr++;
                                InstrXB(idxOp, 0xCF + !!indirect);  // ,W++
                                break;
                            }
                        default:
                            BadMode();
                            break;
                    }
                }
                else if (reg < 0 || reg > 3)
                    BadMode();
                else
                {
                    oldLine = linePtr;
                    token = GetWord(word);
                    switch(token)
                    {
                        case ']':
                            linePtr = oldLine;
                        case 0:
                            InstrXB(idxOp, reg * 0x20 + 0x84 + indirect);  // ,X
                            break;
                        case '+':
                            if (*linePtr == '+')
                            {
                                linePtr++;
                                InstrXB(idxOp, reg * 0x20 + 0x81 + indirect);  // ,X++
                            }
                            else
                                InstrXB(idxOp, reg * 0x20 + 0x80 + indirect);  // ,X+
                            break;
                        default:
                            BadMode();
                            break;
                    }
                }
            }
            break;

        case 'A':
        case 'B':
        case 'D':
        case 'E':
        case 'F':
        case 'W':
            Comma();
            GetWord(word);
            reg = FindReg(word, idxRegs);
            if (reg < 0)
                BadMode();
            else
            {
                switch(token)
                {
                    case 'A':   InstrXB(idxOp, reg * 0x20 + 0x86 + indirect); break;        // A,X
                    case 'B':   InstrXB(idxOp, reg * 0x20 + 0x85 + indirect); break;        // B,X
                    case 'D':   InstrXB(idxOp, reg * 0x20 + 0x8B + indirect); break;        // D,X
                    case 'E':   InstrXB(idxOp, reg * 0x20 + 0x87 + indirect); break;        // A,X
                    case 'F':   InstrXB(idxOp, reg * 0x20 + 0x8A + indirect); break;        // B,X
                    case 'W':   InstrXB(idxOp, reg * 0x20 + 0x8E + indirect); break;        // D,X
                    default:    BadMode();
                }
            }
            break;

        case '<':
        case '>':
            force = token;
        default:
            if (!force)
                linePtr = oldLine;
            val = Eval();
            oldLine = linePtr;
            token = GetWord(word);
            switch(token)
            {
                case ']':
                    linePtr = oldLine;
                case 0:     // value
                    if (!indirect && (dirOp >= 0 || extOp >= 0))
                    {
                        if (((force != '>' && evalKnown && (val & 0xFF00) >> 8 == dpReg) || force == '<') && dirOp >= 0)
                        {
//                          if ((val & 0xFF00) >> 8 != 0 && (val & 0xFF00) >> 8 != dpReg && force == '<')
//                              Warning("High byte of operand does not match SETDP value");
                            InstrXB(dirOp, val);    // <$xx
                        }
                        else
                            InstrXW(extOp, val);   // >$xxxx
                    }
                    else
                        InstrXBW(idxOp, 0x8F + indirect, val);  // $xxxx
                    break;
                case ',':   // value,
                    GetWord(word);
                    reg = FindReg(word, idxRegsW);
                    if (curCPU == CPU_6309 && reg == 4)
                    {
                        // nnnn,W
                        if (force == '<')
                            BadMode();
                        else
                            InstrXBW(idxOp, 0xAF + !!indirect, val); // nnnn,W
                    }
                    else if (reg < 0 || reg > 3)
                    {
                        if (strcmp(word,"PC") == 0 || strcmp(word,"PCR") == 0)
                        {
                            val = val - locPtr - 3 - (idxOp > 255);
                            if ((force != '>' && evalKnown && -128 <= val && val <= 127) || force == '<')
                                InstrXBB(idxOp, 0x8C + indirect, val);       // nn,PCR
                            else
                                InstrXBW(idxOp, 0x8D + indirect, val - 1); // nnnn,PCR
                        }
                        else
                            BadMode();
                    }
                    else
                    {
                        if (force != '>' && evalKnown && !indirect && -16 <= val && val <= 15)
                            InstrXB(idxOp, reg * 0x20 + (val & 0x1F));  // n,X
                        else if (evalKnown && -128 <= val && val <= 127)
                            InstrXBB(idxOp, reg * 0x20 + 0x88 + indirect, val);  // nn,X
                        else
                            InstrXBW(idxOp, reg * 0x20 + 0x89 + indirect, val); // nnnn,X
                    }
                    break;

                default:
                    BadMode();
            }
    }

    if (indirect)
        if (!errFlag) Expect("]");  // if we've already had an error, don't bother checking
}


int M6809_DoCPUOpcode(int typ, int parm)
{
    int     val;
    int     reg1,reg2;
    Str255  word;
    char    *oldLine;
    const char *regs;
    int     token;

    // verify that 6309 instructions are allowed
    if ((parm & o_6309) && curCPU != CPU_6309) return 0;
    parm &= ~o_6309;

    switch(typ)
    {
        case o_Inherent:
            if ((parm & 0xF0FF) == 0xA0E0)  InstrXW(0x3504,parm);
                                    else    InstrX (parm);
            break;

        case o_Immediate:
            oldLine = linePtr;
            token = GetWord(word);
            if (token == '#')
            {
                val = Eval();
                InstrXB(parm, val);
            }
            else
            {
                linePtr = oldLine;
                Expect("#");
            }
            break;

        case o_Relative:
            val = EvalBranch(2);
            InstrXB(parm,val);
            break;

        case o_LRelative:
            val = Eval();
            if (parm < 256) val = val - locPtr - 3;
                    else    val = val - locPtr - 4;
            InstrXW(parm, val);
            break;

        case o_Indexed:
            M6809_Indexed(parm, -1, -1);
            break;

        case o_PshPul:
            reg1 = 0;

            token = GetWord(word);
            while (token)
            {
                reg2 = FindReg(word, pshRegs);
                if (reg2 < 0 || ((parm & 0xFE) == 0x34 && reg2 == 9)
                             || ((parm & 0xFE) == 0x36 && reg2 == 6))
                {
                    Error("Invalid register");
                    break;
                }
                else
                {
                         if (reg2 == 8) reg2 = 0x06;    // D
                    else if (reg2 == 9) reg2 = 0x40;    // S
                    else                reg2 = 1 << reg2;
                    if (reg1 & reg2)
                        Warning("Repeated register");
                    reg1 = reg1 | reg2;
                }

                token = GetWord(word);
                if (token)
                {
                    if (token != ',')
                    {
                        Error("\",\" expected");
                        token = 0;
                    }
                    else
                        token = GetWord(word);
                }
            }

            InstrXB(parm, reg1);
            break;

        case o_ExgTfr:
            regs = tfrRegs;
            if (curCPU == CPU_6309)
                regs = tfrRegs6309;

            // get first register
            GetWord(word);
            reg1 = FindReg(word,regs);
            if (reg1 < 0)
            {
                Error("Invalid register");
                break;
            }

            if (Comma()) break;

            // get second register
            GetWord(word);
            reg2 = FindReg(word,regs);
            if (reg2 < 0)
            {
                Error("Invalid register");
                break;
            }

            if (curCPU != CPU_6309 && (reg1 & 8) != (reg2 & 8))
            {
                Error("Register size mismatch");
                break;
            }

            InstrXB(parm, reg1 * 16 + reg2);
            break;

        case o_Logical:
            M6809_Indexed(parm | 0x60, parm, parm | 0x70);
            break;

        case o_Arith:
        case o_LArith:
        case o_QArith:
            oldLine = linePtr;
            token = GetWord(word);
            if (token == '#')
            {
                if (parm & 0x10)    // immediate
                {
                    Error("Invalid addressing mode");
                    break;
                }

                val = Eval();
                switch(typ)
                {
                    default:
                    case o_Arith:   InstrXB(parm & ~0x10, val);    break;
                    case o_LArith:  InstrXW(parm & ~0x10, val);    break;
                    case o_QArith:  InstrX(0xCD); InstrAddL(val);  break;
                }
            }
            else
            {
                linePtr = oldLine;
                M6809_Indexed((parm & ~0x10) | 0x20, (parm & ~0x10) | 0x10, (parm & ~0x10) | 0x30);
            }
            break;

        case o_TFM: // works like o_ExgTfr except for allowing + and - after registers
            regs = tfrRegs;
            if (curCPU == CPU_6309)
                regs = tfrRegs6309;

            // get first register
            GetWord(word);
            reg1 = FindReg(word,regs);
            if (reg1 < 0)
            {
                Error("Invalid register");
                break;
            }

            val = -1;

            token = GetWord(word);
            switch(token)
            {
                case '+': // R+,R+ and R+,R
                    val = 0;
                    if (Comma()) return 1;
                    break;

                case '-': // R-,R- only
                    val = 1;
                    if (Comma()) return 1;
                    break;

                case ',': // R,R+ only
                    val = 3;
                    break;

                default:
                    IllegalOperand();
                    return 1;
            }


            // get second register
            GetWord(word);
            reg2 = FindReg(word,regs);
            if (reg2 < 0)
            {
                Error("Invalid register");
                break;
            }

            token = GetWord(word);
            switch(token)
            {
                case '+': // R,R+ and R+,R+
                    switch(val)
                    {
                        case 0: // R+,R+
                        case 3: // R,R+
                            break;

                        default:
                            IllegalOperand();
                            return 1;
                    }
                    break;

                case '-': // R-,R- only
                    if (val != 1)
                    {
                        IllegalOperand();
                        return 1;
                    }
                    break;

                case 0: // R+,R only
                    if (val != 0)
                    {
                        IllegalOperand();
                        return 1;
                    }
                    val = 2;
                    break;
                
                default:
                    IllegalOperand();
                    return 1;
            }

            InstrXB(parm + val, reg1 * 16 + reg2);
            break;

        case o_Bit:
            // first register = CC, A, B
            token = GetWord(word);
            val = FindReg(word,pshRegs);
            if (val < 0 || val > 2)
            {
                Error("Invalid register");
                break;
            }
            reg1 = val << 6;

            if (Comma()) break;

            // source bit = 0..7
            val = Eval();
            if (val < 0 || val > 7)
            {
                IllegalOperand();
                break;
            }
            reg1 |= val << 3;

            if (Comma()) break;

            // destination bit = 0..7
            val = Eval();
            if (val < 0 || val > 7)
            {
                IllegalOperand();
                break;
            }
            reg1 |= val;

            if (Comma()) break;

            // allow '<' force character for direct addressing mode
            oldLine = linePtr;
            token = GetWord(word);
            if (token != '<')
                linePtr = oldLine;

            // direct page address
            val = Eval() & 0xFF;

            InstrXBB(parm, reg1, val);
            break;

        default:
            return 0;
            break;
    }
    return 1;
}


int M6809_DoCPULabelOp(int typ, int parm, char *labl)
{
//  int     i;
    int     val;
//  Str255  word;
    char    *p;

    switch(typ)
    {
        case o_SETDP:
            if (labl[0])
                Error("Label not allowed");

            val = Eval();
            if (!errFlag)
            {
                if ((val & 0xFF) == 0)
                    val = val >> 8;     // handle $XX00 as $00XX
                if (val < 0 || val > 255)
                    Error("Operand out of range");
                else
                {
                    dpReg = val;

                    if (pass == 2)
                    {
                        p = listLine + 2;
                        p = ListByte(p,val);
                    }
                }
            }
            break;

        default:
            return 0;
            break;
    }
    return 1;
}


void M6809_PassInit(void)
{
    dpReg = 0;
}


void Asm6809Init(void)
{
    char *p;

    p = AddAsm(versionName, &M6809_DoCPUOpcode, &M6809_DoCPULabelOp, &M6809_PassInit);
    AddCPU(p, "6809", CPU_6809, BIG_END, ADDR_16, LIST_24, 8, 0, M6809_opcdTab);
    AddCPU(p, "6309", CPU_6309, BIG_END, ADDR_16, LIST_24, 8, 0, M6809_opcdTab);
}
