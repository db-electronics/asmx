// asm68000.c - copyright 1998-2007 Bruce Tomlin

#define versionName "68000 assembler"
#include "asmx.h"

enum
{
    CPU_68000,
    CPU_68010
};

enum
{
    o_Inherent,     // implied instructions
    o_DBcc,         // DBcc instructions
    o_Branch,       // relative branch instructions
    o_TRAP,         // TRAP
    o_BKPT,         // BKPT
    o_Imm16,        // 16-bit immediate
    o_LEA,          // LEA opcode
    o_JMP,          // JMP/JSR/PEA (load-EA allowed except for immediate)
    o_OneEA,        // single operand store-EA
    o_DIVMUL,       // DIVS/DIVU/MULS/MULU
    o_MOVE,         // MOVE opcode, two EAs
    o_Bit,          // BCHG/BCLR/BSET/BTST
    o_MOVEQ,        // MOVEQ
    o_ArithA,       // MOVEA/ADDA/CMPA/SUBA
    o_Arith,        // ADD/AND/CMP/EOR/OR/SUB
    o_ArithI,       // ADDI/CMPI/SUBI
    o_LogImm,       // ANDI/EORI/ORI
    o_MOVEM,        // MOVEM
    o_ADDQ,         // ADDQ/SUBQ
    o_Shift,        // ASx/LSx/ROx/ROXx
    o_CHK,          // CHK
    o_CMPM,         // CMPM
    o_MOVEP,        // MOVEP
    o_EXG,          // EXG
    o_ABCD,         // ABCD,SBCD
    o_ADDX,         // ADDX,SUBX
    o_LINK,         // LINK
    o_OneA,         // UNLK
    o_OneD,         // SWAP/EXT
    o_MOVEC,        // 68010 MOVEC
    o_MOVES,        // 68010 MOVES

//  o_Foo = o_LabelOp,
};

enum
{
    WID_B, WID_W, WID_L, WID_X // byte, word, long, or auto
};

typedef struct EArec
{
    u_short         mode;       // 6 bits for the opcode
    u_short         len;        // number of extra words
    u_short         extra[5];   // storage for extra words
} EArec;

const char addr_regs[] = "A0 A1 A2 A3 A4 A5 A6 A7 SP";
const char data_regs[] = "D0 D1 D2 D3 D4 D5 D6 D7";
const char   DA_regs[] = "D0 D1 D2 D3 D4 D5 D6 D7 A0 A1 A2 A3 A4 A5 A6 A7 SP";
const char A_PC_regs[] = "A0 A1 A2 A3 A4 A5 A6 A7 SP PC";


struct OpcdRec M68K_opcdTab[] =
{
    {"ILLEGAL", o_Inherent, 0x4AFC},
    {"NOP",     o_Inherent, 0x4E71},
    {"RESET",   o_Inherent, 0x4E70},
    {"RTE",     o_Inherent, 0x4E73},
    {"RTR",     o_Inherent, 0x4E77},
    {"RTS",     o_Inherent, 0x4E75},
    {"TRAPV",   o_Inherent, 0x4E76},

    {"DBT",     o_DBcc,     0x50C8},
    {"DBRA",    o_DBcc,     0x51C8},
    {"DBF",     o_DBcc,     0x51C8},
    {"DBHI",    o_DBcc,     0x52C8},
    {"DBLS",    o_DBcc,     0x53C8},
    {"DBCC",    o_DBcc,     0x54C8},
    {"DBHS",    o_DBcc,     0x54C8},
    {"DBCS",    o_DBcc,     0x55C8},
    {"DBLO",    o_DBcc,     0x55C8},
    {"DBNE",    o_DBcc,     0x56C8},
    {"DBEQ",    o_DBcc,     0x57C8},
    {"DBVC",    o_DBcc,     0x58C8},
    {"DBVS",    o_DBcc,     0x59C8},
    {"DBPL",    o_DBcc,     0x5AC8},
    {"DBMI",    o_DBcc,     0x5BC8},
    {"DBGE",    o_DBcc,     0x5CC8},
    {"DBLT",    o_DBcc,     0x5DC8},
    {"DBGT",    o_DBcc,     0x5EC8},
    {"DBLE",    o_DBcc,     0x5FC8},

    {"BRA",     o_Branch,   0x6000 + WID_X},
    {"BRA.B",   o_Branch,   0x6000 + WID_B},
    {"BRA.W",   o_Branch,   0x6000 + WID_W},
    {"BSR",     o_Branch,   0x6100 + WID_X},
    {"BSR.B",   o_Branch,   0x6100 + WID_B},
    {"BSR.W",   o_Branch,   0x6100 + WID_W},
    {"BHI",     o_Branch,   0x6200 + WID_X},
    {"BHI.B",   o_Branch,   0x6200 + WID_B},
    {"BHI.W",   o_Branch,   0x6200 + WID_W},
    {"BLS",     o_Branch,   0x6300 + WID_X},
    {"BLS.B",   o_Branch,   0x6300 + WID_B},
    {"BLS.W",   o_Branch,   0x6300 + WID_W},
    {"BCC",     o_Branch,   0x6400 + WID_X},
    {"BCC.B",   o_Branch,   0x6400 + WID_B},
    {"BCC.W",   o_Branch,   0x6400 + WID_W},
    {"BHS",     o_Branch,   0x6400 + WID_X},
    {"BHS.B",   o_Branch,   0x6400 + WID_B},
    {"BHS.W",   o_Branch,   0x6400 + WID_W},
    {"BCS",     o_Branch,   0x6500 + WID_X},
    {"BCS.B",   o_Branch,   0x6500 + WID_B},
    {"BCS.W",   o_Branch,   0x6500 + WID_W},
    {"BLO",     o_Branch,   0x6500 + WID_X},
    {"BLO.B",   o_Branch,   0x6500 + WID_B},
    {"BLO.W",   o_Branch,   0x6500 + WID_W},
    {"BNE",     o_Branch,   0x6600 + WID_X},
    {"BNE.B",   o_Branch,   0x6600 + WID_B},
    {"BNE.W",   o_Branch,   0x6600 + WID_W},
    {"BEQ",     o_Branch,   0x6700 + WID_X},
    {"BEQ.B",   o_Branch,   0x6700 + WID_B},
    {"BEQ.W",   o_Branch,   0x6700 + WID_W},
    {"BVC",     o_Branch,   0x6800 + WID_X},
    {"BVC.B",   o_Branch,   0x6800 + WID_B},
    {"BVC.W",   o_Branch,   0x6800 + WID_W},
    {"BVS",     o_Branch,   0x6900 + WID_X},
    {"BVS.B",   o_Branch,   0x6900 + WID_B},
    {"BVS.W",   o_Branch,   0x6900 + WID_W},
    {"BPL",     o_Branch,   0x6A00 + WID_X},
    {"BPL.B",   o_Branch,   0x6A00 + WID_B},
    {"BPL.W",   o_Branch,   0x6A00 + WID_W},
    {"BMI",     o_Branch,   0x6B00 + WID_X},
    {"BMI.B",   o_Branch,   0x6B00 + WID_B},
    {"BMI.W",   o_Branch,   0x6B00 + WID_W},
    {"BGE",     o_Branch,   0x6C00 + WID_X},
    {"BGE.B",   o_Branch,   0x6C00 + WID_B},
    {"BGE.W",   o_Branch,   0x6C00 + WID_W},
    {"BLT",     o_Branch,   0x6D00 + WID_X},
    {"BLT.B",   o_Branch,   0x6D00 + WID_B},
    {"BLT.W",   o_Branch,   0x6D00 + WID_W},
    {"BGT",     o_Branch,   0x6E00 + WID_X},
    {"BGT.B",   o_Branch,   0x6E00 + WID_B},
    {"BGT.W",   o_Branch,   0x6E00 + WID_W},
    {"BLE",     o_Branch,   0x6F00 + WID_X},
    {"BLE.B",   o_Branch,   0x6F00 + WID_B},
    {"BLE.W",   o_Branch,   0x6F00 + WID_W},
    {"BRA.S",   o_Branch,   0x6000 + WID_B},
    {"BSR.S",   o_Branch,   0x6100 + WID_B},
    {"BHI.S",   o_Branch,   0x6200 + WID_B},
    {"BLS.S",   o_Branch,   0x6300 + WID_B},
    {"BCC.S",   o_Branch,   0x6400 + WID_B},
    {"BHS.S",   o_Branch,   0x6400 + WID_B},
    {"BCS.S",   o_Branch,   0x6500 + WID_B},
    {"BLO.S",   o_Branch,   0x6500 + WID_B},
    {"BNE.S",   o_Branch,   0x6600 + WID_B},
    {"BEQ.S",   o_Branch,   0x6700 + WID_B},
    {"BVC.S",   o_Branch,   0x6800 + WID_B},
    {"BVS.S",   o_Branch,   0x6900 + WID_B},
    {"BPL.S",   o_Branch,   0x6A00 + WID_B},
    {"BMI.S",   o_Branch,   0x6B00 + WID_B},
    {"BGE.S",   o_Branch,   0x6C00 + WID_B},
    {"BLT.S",   o_Branch,   0x6D00 + WID_B},
    {"BGT.S",   o_Branch,   0x6E00 + WID_B},
    {"BLE.S",   o_Branch,   0x6F00 + WID_B},

    {"STOP",    o_Imm16,    0x4E72},
    {"RTD",     o_Imm16,    0x4E74}, // *** 68010 and up

    {"TRAP",    o_TRAP,     0x4E40},
    {"BKPT",    o_BKPT,     0x4848}, // *** 68010 and up

    {"LEA",     o_LEA,      0x41C0}, // load-EA but no immediate
    {"LEA.L",   o_LEA,      0x41C0}, // load-EA but no immediate

    {"JMP",     o_JMP,      0x4EC0}, // load-EA but no immediate
    {"JSR",     o_JMP,      0x4E80}, // load-EA but no immediate
    {"PEA",     o_JMP,      0x4840}, // load-EA but no immediate
    {"PEA.L",   o_JMP,      0x4840}, // load-EA but no immediate

    {"CLR",     o_OneEA,    0x4240}, // store-EA
    {"CLR.B",   o_OneEA,    0x4200},
    {"CLR.W",   o_OneEA,    0x4240},
    {"CLR.L",   o_OneEA,    0x4280},
    {"NBCD",    o_OneEA,    0x4800},
    {"NBCD.B",  o_OneEA,    0x4800},
    {"NEG",     o_OneEA,    0x4440},
    {"NEG.B",   o_OneEA,    0x4400},
    {"NEG.W",   o_OneEA,    0x4440},
    {"NEG.L",   o_OneEA,    0x4480},
    {"NEGX",    o_OneEA,    0x4040},
    {"NEGX.B",  o_OneEA,    0x4000},
    {"NEGX.W",  o_OneEA,    0x4040},
    {"NEGX.L",  o_OneEA,    0x4080},
    {"NOT",     o_OneEA,    0x4640},
    {"NOT.B",   o_OneEA,    0x4600},
    {"NOT.W",   o_OneEA,    0x4640},
    {"NOT.L",   o_OneEA,    0x4680},
    {"ST",      o_OneEA,    0x50C0},
//  {"ST.B",    o_OneEA,    0x50C0},
    {"SF",      o_OneEA,    0x51C0},
//  {"SF.B",    o_OneEA,    0x51C0},
    {"SHI",     o_OneEA,    0x52C0},
//  {"SHI.B",   o_OneEA,    0x52C0},
    {"SLS",     o_OneEA,    0x53C0},
//  {"SLS.B",   o_OneEA,    0x53C0},
    {"SCC",     o_OneEA,    0x54C0},
//  {"SCC.B",   o_OneEA,    0x54C0},
    {"SHS",     o_OneEA,    0x54C0},
//  {"SHS.B",   o_OneEA,    0x54C0},
    {"SCS",     o_OneEA,    0x55C0},
//  {"SCS.B",   o_OneEA,    0x55C0},
    {"SLO",     o_OneEA,    0x55C0},
//  {"SLO.B",   o_OneEA,    0x55C0},
    {"SNE",     o_OneEA,    0x56C0},
//  {"SNE.B",   o_OneEA,    0x56C0},
    {"SEQ",     o_OneEA,    0x57C0},
//  {"SEQ.B",   o_OneEA,    0x57C0},
    {"SVC",     o_OneEA,    0x58C0},
//  {"SVC.B",   o_OneEA,    0x58C0},
    {"SVS",     o_OneEA,    0x59C0},
//  {"SVS.B",   o_OneEA,    0x59C0},
    {"SPL",     o_OneEA,    0x5AC0},
//  {"SPL.B",   o_OneEA,    0x5AC0},
    {"SMI",     o_OneEA,    0x5BC0},
//  {"SMI.B",   o_OneEA,    0x5BC0},
    {"SGE",     o_OneEA,    0x5CC0},
//  {"SGE.B",   o_OneEA,    0x5CC0},
    {"SLT",     o_OneEA,    0x5DC0},
//  {"SLT.B",   o_OneEA,    0x5DC0},
    {"SGT",     o_OneEA,    0x5EC0},
//  {"SGT.B",   o_OneEA,    0x5EC0},
    {"SLE",     o_OneEA,    0x5FC0},
//  {"SLE.B",   o_OneEA,    0x5FC0},
    {"TAS",     o_OneEA,    0x4AC0},
    {"TAS.B",   o_OneEA,    0x4AC0},
    {"TST",     o_OneEA,    0x4A40},
    {"TST.B",   o_OneEA,    0x4A00},
    {"TST.W",   o_OneEA,    0x4A40},
    {"TST.L",   o_OneEA,    0x4A80},

    {"DIVS",    o_DIVMUL,   0x81C0},
    {"DIVS.W",  o_DIVMUL,   0x81C0},
    {"DIVU",    o_DIVMUL,   0x80C0},
    {"DIVU.W",  o_DIVMUL,   0x80C0},
    {"MULS",    o_DIVMUL,   0xC1C0},
    {"MULS.W",  o_DIVMUL,   0xC1C0},
    {"MULU",    o_DIVMUL,   0xC0C0},
    {"MULU.W",  o_DIVMUL,   0xC0C0},

    {"MOVE",    o_MOVE,     0x3000 + WID_X},
    {"MOVE.B",  o_MOVE,     0x1000 + WID_B},
    {"MOVE.W",  o_MOVE,     0x3000 + WID_W},
    {"MOVE.L",  o_MOVE,     0x2000 + WID_L},

    {"BCHG",    o_Bit,      0x0040 + WID_X},
    {"BCHG.B",  o_Bit,      0x0040 + WID_B},
    {"BCHG.L",  o_Bit,      0x0040 + WID_L},
    {"BCLR",    o_Bit,      0x0080 + WID_X},
    {"BCLR.B",  o_Bit,      0x0080 + WID_B},
    {"BCLR.L",  o_Bit,      0x0080 + WID_L},
    {"BSET",    o_Bit,      0x00C0 + WID_X},
    {"BSET.B",  o_Bit,      0x00C0 + WID_B},
    {"BSET.L",  o_Bit,      0x00C0 + WID_L},
    {"BTST",    o_Bit,      0x0000 + WID_X},
    {"BTST.B",  o_Bit,      0x0000 + WID_B},
    {"BTST.L",  o_Bit,      0x0000 + WID_L},

    {"MOVEQ",   o_MOVEQ,    0},
    {"MOVEQ.L", o_MOVEQ,    0},

    {"MOVEA",   o_ArithA,   0x3040 + WID_W},
    {"MOVEA.W", o_ArithA,   0x3040 + WID_W},
    {"MOVEA.L", o_ArithA,   0x2040 + WID_L},
    {"ADDA",    o_ArithA,   0xD0C0 + WID_W},
    {"ADDA.W",  o_ArithA,   0xD0C0 + WID_W},
    {"ADDA.L",  o_ArithA,   0xD1C0 + WID_L},
    {"CMPA",    o_ArithA,   0xB0C0 + WID_W},
    {"CMPA.W",  o_ArithA,   0xB0C0 + WID_W},
    {"CMPA.L",  o_ArithA,   0xB1C0 + WID_L},
    {"SUBA",    o_ArithA,   0x90C0 + WID_W},
    {"SUBA.W",  o_ArithA,   0x90C0 + WID_W},
    {"SUBA.L",  o_ArithA,   0x91C0 + WID_L},

    // a_Arith special parm bits:
    // 8000 = EOR
    // 0004 = CMP
    // 0008/0010/0020 = bits for immediate
    {"ADD",     o_Arith,    0xD040 + WID_X + 0x18},
    {"ADD.B",   o_Arith,    0xD000 + WID_B + 0x18},
    {"ADD.W",   o_Arith,    0xD040 + WID_W + 0x18},
    {"ADD.L",   o_Arith,    0xD080 + WID_L + 0x18},
    {"AND",     o_Arith,    0xC040 + WID_X + 0x08},
    {"AND.B",   o_Arith,    0xC000 + WID_B + 0x08},
    {"AND.W",   o_Arith,    0xC040 + WID_W + 0x08},
    {"AND.L",   o_Arith,    0xC080 + WID_L + 0x08},
    {"CMP",     o_Arith,    0xB040 + WID_X + 0x30 + 4}, // EA,Dn only
    {"CMP.B",   o_Arith,    0xB000 + WID_B + 0x30 + 4},
    {"CMP.W",   o_Arith,    0xB040 + WID_W + 0x30 + 4},
    {"CMP.L",   o_Arith,    0xB080 + WID_L + 0x30 + 4},
    {"EOR",     o_Arith,    0xB040 + WID_X + 0x28 - 0x8000}, // Dn,EA only
    {"EOR.B",   o_Arith,    0xB000 + WID_B + 0x28 - 0x8000},
    {"EOR.W",   o_Arith,    0xB040 + WID_W + 0x28 - 0x8000},
    {"EOR.L",   o_Arith,    0xB080 + WID_L + 0x28 - 0x8000},
    {"OR",      o_Arith,    0x8040 + WID_X + 0x00},
    {"OR.B",    o_Arith,    0x8000 + WID_B + 0x00},
    {"OR.W",    o_Arith,    0x8040 + WID_W + 0x00},
    {"OR.L",    o_Arith,    0x8080 + WID_L + 0x00},
    {"SUB",     o_Arith,    0x9040 + WID_X + 0x10},
    {"SUB.B",   o_Arith,    0x9000 + WID_B + 0x10},
    {"SUB.W",   o_Arith,    0x9040 + WID_W + 0x10},
    {"SUB.L",   o_Arith,    0x9080 + WID_L + 0x10},
/*
1100 rrrm mm00 0000 -> 0000 0010 SS00 0000 AND -> ANDI
1011 rrr1 mm00 0000 -> 0000 1010 SS00 0000 EOR -> EORI
1000 rrrm mm00 0000 -> 0000 0000 SS00 0000 OR  -> ORI

1101 rrrm mm00 0000 -> 0000 0110 SS00 0000 ADD -> ADDI
1011 rrr0 mm00 0000 -> 0000 1100 SS00 0000 CMP -> CMPI
1001 rrrm mm00 0000 -> 0000 0100 SS00 0000 SUB -> SUBI
 ^^^                        ^^^
*/
    {"ADDI",    o_ArithI,   0x0640 + WID_W},
    {"ADDI.B",  o_ArithI,   0x0600 + WID_B},
    {"ADDI.W",  o_ArithI,   0x0640 + WID_W},
    {"ADDI.L",  o_ArithI,   0x0680 + WID_L},
    {"CMPI",    o_ArithI,   0x0C40 + WID_W},
    {"CMPI.B",  o_ArithI,   0x0C00 + WID_B},
    {"CMPI.W",  o_ArithI,   0x0C40 + WID_W},
    {"CMPI.L",  o_ArithI,   0x0C80 + WID_L},
    {"SUBI",    o_ArithI,   0x0440 + WID_W},
    {"SUBI.B",  o_ArithI,   0x0400 + WID_B},
    {"SUBI.W",  o_ArithI,   0x0440 + WID_W},
    {"SUBI.L",  o_ArithI,   0x0480 + WID_L},

    {"ANDI",    o_LogImm,   0x0200 + WID_X},
    {"ANDI.B",  o_LogImm,   0x0200 + WID_B},
    {"ANDI.W",  o_LogImm,   0x0200 + WID_W},
    {"ANDI.L",  o_LogImm,   0x0200 + WID_L},
    {"EORI",    o_LogImm,   0x0A00 + WID_X},
    {"EORI.B",  o_LogImm,   0x0A00 + WID_B},
    {"EORI.W",  o_LogImm,   0x0A00 + WID_W},
    {"EORI.L",  o_LogImm,   0x0A00 + WID_L},
    {"ORI",     o_LogImm,   0x0000 + WID_X},
    {"ORI.B",   o_LogImm,   0x0000 + WID_B},
    {"ORI.W",   o_LogImm,   0x0000 + WID_W},
    {"ORI.L",   o_LogImm,   0x0000 + WID_L},

    {"MOVEM",   o_MOVEM,    0x4880 + WID_W},
    {"MOVEM.W", o_MOVEM,    0x4880 + WID_W},
    {"MOVEM.L", o_MOVEM,    0x48C0 + WID_L},

    {"ADDQ",    o_ADDQ,     0x5040 + WID_W},
    {"ADDQ.B",  o_ADDQ,     0x5000 + WID_B},
    {"ADDQ.W",  o_ADDQ,     0x5040 + WID_W},
    {"ADDQ.L",  o_ADDQ,     0x5080 + WID_L},
    {"SUBQ",    o_ADDQ,     0x5140 + WID_W},
    {"SUBQ.B",  o_ADDQ,     0x5100 + WID_B},
    {"SUBQ.W",  o_ADDQ,     0x5140 + WID_W},
    {"SUBQ.L",  o_ADDQ,     0x5180 + WID_L},

    {"ASL",     o_Shift,    0xE100 + WID_X}, // E100 E1C0
    {"ASL.B",   o_Shift,    0xE100 + WID_B},
    {"ASL.W",   o_Shift,    0xE100 + WID_W},
    {"ASL.L",   o_Shift,    0xE100 + WID_L},
    {"ASR",     o_Shift,    0xE000 + WID_X}, // E000 E0C0
    {"ASR.B",   o_Shift,    0xE000 + WID_B},
    {"ASR.W",   o_Shift,    0xE000 + WID_W},
    {"ASR.L",   o_Shift,    0xE000 + WID_L},
    {"LSL",     o_Shift,    0xE108 + WID_X}, // E108 E3C0
    {"LSL.B",   o_Shift,    0xE108 + WID_B},
    {"LSL.W",   o_Shift,    0xE108 + WID_W},
    {"LSL.L",   o_Shift,    0xE108 + WID_L},
    {"LSR",     o_Shift,    0xE008 + WID_X}, // E008 E2C0
    {"LSR.B",   o_Shift,    0xE008 + WID_B},
    {"LSR.W",   o_Shift,    0xE008 + WID_W},
    {"LSR.L",   o_Shift,    0xE008 + WID_L},
    {"ROL",     o_Shift,    0xE118 + WID_X}, // E118 E7C0
    {"ROL.B",   o_Shift,    0xE118 + WID_B},
    {"ROL.W",   o_Shift,    0xE118 + WID_W},
    {"ROL.L",   o_Shift,    0xE118 + WID_L},
    {"ROR",     o_Shift,    0xE018 + WID_X}, // E018 E6C0
    {"ROR.B",   o_Shift,    0xE018 + WID_B},
    {"ROR.W",   o_Shift,    0xE018 + WID_W},
    {"ROR.L",   o_Shift,    0xE018 + WID_L},
    {"ROXL",    o_Shift,    0xE110 + WID_X}, // E110 E5C0
    {"ROXL.B",  o_Shift,    0xE110 + WID_B},
    {"ROXL.W",  o_Shift,    0xE110 + WID_W},
    {"ROXL.L",  o_Shift,    0xE110 + WID_L},
    {"ROXR",    o_Shift,    0xE010 + WID_X}, // E010 E4C0
    {"ROXR.B",  o_Shift,    0xE010 + WID_B},
    {"ROXR.W",  o_Shift,    0xE010 + WID_W},
    {"ROXR.L",  o_Shift,    0xE010 + WID_L},

    {"CHK",     o_CHK,      0x4180 + WID_W},
    {"CHK.W",   o_CHK,      0x4180 + WID_W},

    {"CMPM",    o_CMPM,     0xB148},
    {"CMPM.B",  o_CMPM,     0xB108},
    {"CMPM.W",  o_CMPM,     0xB148},
    {"CMPM.L",  o_CMPM,     0xB188},

    {"MOVEP",   o_MOVEP,    0x0108},
    {"MOVEP.W", o_MOVEP,    0x0108},
    {"MOVEP.L", o_MOVEP,    0x0148},

    {"EXG",     o_EXG,      0},
    {"EXG.L",   o_EXG,      0},

    {"ABCD",    o_ABCD,     0xC100},
    {"ABCD.B",  o_ABCD,     0xC100},
    {"SBCD",    o_ABCD,     0x8100},
    {"SBCD.B",  o_ABCD,     0x8100},

    {"ADDX",    o_ADDX,     0xD140},
    {"ADDX.B",  o_ADDX,     0xD100},
    {"ADDX.W",  o_ADDX,     0xD140},
    {"ADDX.L",  o_ADDX,     0xD180},
    {"SUBX",    o_ADDX,     0x9140},
    {"SUBX.B",  o_ADDX,     0x9100},
    {"SUBX.W",  o_ADDX,     0x9140},
    {"SUBX.L",  o_ADDX,     0x9180},

    {"LINK",    o_LINK,     0x4E50},
    {"LINK.W",  o_LINK,     0x4E50},

    {"UNLK",    o_OneA,     0x4E58},

    {"SWAP",    o_OneD,     0x4840},
    {"SWAP.W",  o_OneD,     0x4840},
    {"EXT",     o_OneD,     0x4880},
    {"EXT.W",   o_OneD,     0x4880},
    {"EXT.L",   o_OneD,     0x48C0},

    {"MOVEC",   o_MOVEC,    0x4E7A},
    {"MOVES",   o_MOVES,    0x0E00 + WID_W},
    {"MOVES.B", o_MOVES,    0x0E00 + WID_B},
    {"MOVES.W", o_MOVES,    0x0E00 + WID_W},
    {"MOVES.L", o_MOVES,    0x0E00 + WID_L},

    {"",     o_Illegal,     0}
};


// --------------------------------------------------------------


// add extra words from an EA spec to the instruction
void InstrAddE(EArec *ea)
{
    int     i;

    // detect longwords for proper hex spacing in listing
    if (ea->len == 2 && ((ea->mode & 0x38) == 0x28 || ea->mode == 0x39 || ea->mode == 0x3A || ea->mode == 0x3C))
        InstrAddL(ea -> extra[0] * 65536 + ea -> extra[1]);
    else for (i = 0; i < ea -> len; i++)
        InstrAddW(ea -> extra[i]);
}


void InstrWE(u_short op, EArec *ea)
{

    InstrClear();

    InstrAddW((op & 0xFFC0) | ea -> mode);
    InstrAddE(ea);
}


void InstrWWE(u_short op, u_short w1, EArec *ea)
{

    InstrClear();

    InstrAddW((op & 0xFFC0) | ea -> mode);
    InstrAddW(w1);
    InstrAddE(ea);
}


void InstrWLE(u_short op, u_long l1, EArec *ea)
{

    InstrClear();

    InstrAddW((op & 0xFFC0) | ea -> mode);
#if 1 // zero to space out longwords as two words
    InstrAddL(l1);
#else
    InstrAddW(l1 >> 16);
    InstrAddW(l1);
#endif
    InstrAddE(ea);
}


void InstrWEE(u_short op, EArec *srcEA, EArec *dstEA)
{
    // OP dstEA srcEA
    // srcext - up to 2 words on 68000, 5 words on 68020
    // dstext - up to 2 words on 68000, 5 words on 68020

    InstrClear();

    InstrAddW((op & 0xF000) | srcEA -> mode | (((dstEA -> mode) & 0x07) << 9) |
                                              (((dstEA -> mode) & 0x38) << 3));
    InstrAddE(srcEA);
    InstrAddE(dstEA);
}


void CheckSize(int size, u_long val)
{
    switch(size)
    {
        case WID_B:
            CheckByte(val);
            break;

        case WID_X:
        case WID_W:
            CheckWord(val);
            break;

        case WID_L:
        default:
            break;
    }
}


bool GetEA(bool store, int size, EArec *ea)
{
    Str255  word;
    char    *oldLine,*oldLine0;
    int     token;
    int     val;
    int     width;
    int     reg1,reg2;

//if (pass == 2 && locPtr == 0x02B6)
//{
//    token = 0;
//}

    oldLine = linePtr;
    oldLine0 = linePtr;
    token = GetWord(word);

    ea -> mode = 0;
    ea -> len = 0;

    // 000nnn = Dn
    if (word[0] == 'D' && '0' <= word[1] && word[1] <= '7' && word[2] == 0)
    {
        ea -> mode = word[1] - '0';
        return TRUE;
    }

    // 001nnn = An
    else if (word[0] == 'A' && '0' <= word[1] && word[1] <= '7' && word[2] == 0)
    {
        ea -> mode = 8 + word[1] - '0';
        return TRUE;
    }
    else if (word[0] == 'S' && word[1] == 'P' && word[2] == 0)
    {
        ea -> mode = 0x0F;
        return TRUE;
    }

    // 111100 = #imm - load-EA only
    else if (token == '#')
    {
        if (store || size < 0)
            BadMode();
        else
        {
            ea -> mode = 0x3C;
            val = Eval();
            CheckSize(size,val);
            switch(size)
            {
                case WID_B:
                    val = val & 0xFF;
                case WID_W:
                    ea -> len = 1;
                    ea -> extra[0] = val;
                    break;
                case WID_L:
                    ea -> len = 2;
                    ea -> extra[0] = val >> 16;
                    ea -> extra[1] = val;
                    break;
                default: // shouldn't get here
                    BadMode();
            }
        }
        return TRUE;
    }

    // 100 -(An)
    else if (token == '-')
    {
        if (GetWord(word) == '(')
        {
            reg1 = GetReg(addr_regs);
            if (reg1 == 8) reg1 = 7;
            if (reg1 >= 0)
            {
                if (GetWord(word) == ')')
                {
                    ea -> mode = 0x20 + reg1;
                    return TRUE;
                }
            }
        }
    }

    // 010nnn (An)
    // 011nnn (An)+
    // 101nnn (d16,An)
    // 110nnn (d8,An,Xn)
    // 111010 (d16,PC) - load only
    // 111011 (d8,PC,Xn) - load only
    else if (token == '(')
    {
        oldLine = linePtr; // in case this is just an expression in parens for absolute

        reg1 = GetReg(A_PC_regs);
        if (reg1 == 8) reg1 = 7;
        if (reg1 >= 0)
        {
            // (An
            token = GetWord(word);
            if (token == ')')
            {
                oldLine = linePtr;
                if (GetWord(word) == '+')
                {
                    // 011 (An)+
                    ea -> mode = 0x18 + reg1;
                    return TRUE;
                }
                else
                {
                    // 010 (An)
                    linePtr = oldLine;
                    ea -> mode = 0x10 + reg1;
                    return TRUE;
                }
            }
            else if (token == ',')
            { // 0(PC,Xn) 0(An,Xn)
            // FIXME: reg1 can't be PC here?
                val = 0;
                reg2 = GetReg(DA_regs);
                if (reg2 == 16) reg2 = 15; // SP -> A7
                if (reg2 >= 0)
                {
                    // get Xn forced size if any
                    width = WID_W;
                    if (linePtr[0] == '.' && toupper(linePtr[1]) == 'L')
                    {
                        linePtr = linePtr + 2;
                        width = WID_L;
                    }
                    else if (linePtr[0] == '.' && toupper(linePtr[1]) == 'W')
                        linePtr = linePtr + 2;

                    //CheckByte(val); // zero IS a byte
                    if (RParen()) return FALSE;

                    if (reg1 == 9)
                    {
                        // (PC,Xn)
                        if (!store)
                        {
                            // val = val - locPtr - 2; // don't offset from PC
                            ea -> mode = 0x3B;
                            ea -> len = 1;
                            ea -> extra[0] = (reg2 << 12) + (val & 0xFF);
                            if (width == WID_L)
                                ea -> extra[0] |= 0x0800;
                            return TRUE;
                        }
                    }
                    else
                    {
                        // (An,Xn)
                        ea -> mode = 0x30 + reg1;
                        ea -> len = 1;
                        ea -> extra[0] = (reg2 << 12) + (val & 0xFF);
                        if (width == WID_L)
                            ea -> extra[0] |= 0x0800;
                        return TRUE;
                    }
                }
            }
        }
        else
        {
            // (value
            linePtr = oldLine;

            // look for "(ofs,reg"
            val = Eval(); // get offset

            oldLine = linePtr;
            token = GetWord(word);
            if (token == ')') // (expr) which may be followed by more expr: (foo)*(bar)
            {
                oldLine = oldLine0; // completely back up to start of EA
            }
            else
            {
                if (token == '.')
                {
                    // abs.w/abs.l with forced size
                    width = WID_X;
                    if      (toupper(*linePtr) == 'W')
                    {
                        width = WID_W;
                        linePtr = linePtr + 1;
                    }
                    else if (toupper(*linePtr) == 'L')
                    {
                        width = WID_L;
                        linePtr = linePtr + 1;
                    }
                    if (RParen()) return FALSE;

                    goto ABSOLUTE;
                }
//                else if (token == ')')
//                {
//                    // abs
//                    width = WID_X;
//                    goto ABSOLUTE;
//                }

                linePtr = oldLine;
                if (Comma()) return FALSE;

                reg1 = GetReg(A_PC_regs);
                if (reg1 == 8) reg1 = 7;

                if (reg1 >= 0)
                {
                    // look for rparen or Xn
                    switch(GetWord(word))
                    {
                        case ')':
                            // (ofs,An) or (ofs,PC)
                            if (reg1 == 9)
                            {
                                // (d16,PC)
                                if (!store)
                                {
                                    val = val - locPtr - 2;
                                    if (!errFlag && (val < -128 || val > 127))
                                        Error("Offset out of range");
                                    ea -> mode = 0x3A;
                                    ea -> len = 1;
                                    ea -> extra[0] = val;
                                    return TRUE;
                                }
                            }
                            else
                            {
                                if (evalKnown && val == 0)
                                {
                                    // 010 (An)
                                    ea -> mode = 0x10 + reg1;
                                return TRUE;
                                }

                                // (d16,An)
                                CheckWord(val);
                                ea -> mode = 0x28 + reg1;
                                ea -> len = 1;
                                ea -> extra[0] = val;
                                return TRUE;
                            }
                            break;

                        case ',': // (d8,An,Xn) or (d8,PC,Xn)
                            reg2 = GetReg(DA_regs);
                            if (reg2 == 16) reg2 = 15; // SP -> A7
                            if (reg2 >= 0)
                            {
                                width = WID_W;
                                if (linePtr[0] == '.' && toupper(linePtr[1]) == 'L')
                                {
                                    linePtr = linePtr + 2;
                                    width = WID_L;
                                }
                                else if (linePtr[0] == '.' && toupper(linePtr[1]) == 'W')
                                    linePtr = linePtr + 2;

                                if (RParen()) break;

                                if (reg1 == 9)
                                {
                                    // (d8,PC,Xn)
                                    if (!store)
                                    {
                                        val = val - locPtr - 2;
                                        if (!errFlag && (val < -128 || val > 127))
                                            Error("Offset out of range");
                                        ea -> mode = 0x3B;
                                        ea -> len = 1;
                                        ea -> extra[0] = (reg2 << 12) + (val & 0xFF);
                                        if (width == WID_L)
                                            ea -> extra[0] |= 0x0800;
                                        return TRUE;
                                    }
                                }
                                else
                                {
                                    // (d8,An,Xn)
                                    CheckByte(val);
                                    ea -> mode = 0x30 + reg1;
                                    ea -> len = 1;
                                    ea -> extra[0] = (reg2 << 12) + (val & 0xFF);
                                    if (width == WID_L)
                                        ea -> extra[0] |= 0x0800;
                                    return TRUE;
                                }
                            }
                            break;
                    }
                }
            }
        }
    }

    linePtr = oldLine;
    token = 0;

    // 111000 abs.W
    // 111001 abs.L
    // 101nnn d16(An)
    // 110nnn d8(An,Xn)
    // 111010 d16(PC) - load only
    // 111011 d8(PC,Xn) - load only
    {
        // get address/offset and forced size if any
        val = Eval();
        width = WID_X;
        if      (linePtr[0] == '.' && toupper(linePtr[1]) == 'W')
        {
            width = WID_W;
            linePtr = linePtr + 2;
        }
        else if (linePtr[0] == '.' && toupper(linePtr[1]) == 'L')
        {
            width = WID_L;
            linePtr = linePtr + 2;
        }

        oldLine = linePtr;
        switch(GetWord(word))
        {
            case '(':
                // offset indexed
                reg1 = GetReg(A_PC_regs);
                if (reg1 == 8) reg1 = 7;
                if (reg1 >= 0)
                {
                    // now look for ) or ,
                    switch(GetWord(word))
                    {
                        case ')':
                            if (reg1 == 9)
                            {
                                // d16(PC)
                                if (!store)
                                {
                                    val = val - locPtr - 2;
                                    if (!errFlag && (val < -32768 || val > 32767))
                                        Error("Offset out of range");
                                    ea -> mode = 0x3A;
                                    ea -> len = 1;
                                    ea -> extra[0] = val;
                                    return TRUE;
                                }
                            }
                            else
                            {
                                if (evalKnown && val == 0)
                                {
                                    // 010 (An)
                                    ea -> mode = 0x10 + reg1;
                                    return TRUE;
                                }

                                // d16(An)
                                CheckWord(val);
                                ea -> mode = 0x28 + reg1;
                                ea -> len = 1;
                                ea -> extra[0] = val;
                                return TRUE;
                            }
                            break;

                        case ',': // d8(An,Xn) or d8(PC,Xn)
                            reg2 = GetReg(DA_regs);
                            if (reg2 == 16) reg2 = 15; // SP -> A7
                            if (reg2 >= 0)
                            {
                                // get Xn forced size if any
                                width = WID_W;
                                if (linePtr[0] == '.' && toupper(linePtr[1]) == 'L')
                                {
                                    linePtr = linePtr + 2;
                                    width = WID_L;
                                }
                                else if (linePtr[0] == '.' && toupper(linePtr[1]) == 'W')
                                    linePtr = linePtr + 2;

                                if (RParen()) break;

                                if (reg1 == 9)
                                {
                                    // d8(PC,Xn)
                                    if (!store)
                                    {
                                        val = val - locPtr - 2;
                                        if (!errFlag && (val < -128 || val > 127))
                                            Error("Offset out of range");
                                        ea -> mode = 0x3B;
                                        ea -> len = 1;
                                        ea -> extra[0] = (reg2 << 12) + (val & 0xFF);
                                        if (width == WID_L)
                                            ea -> extra[0] |= 0x0800;
                                        return TRUE;
                                    }
                                }
                                else
                                {
                                    // d8(An,Xn)
                                    CheckByte(val);
                                    ea -> mode = 0x30 + reg1;
                                    ea -> len = 1;
                                    ea -> extra[0] = (reg2 << 12) + (val & 0xFF);
                                    if (width == WID_L)
                                        ea -> extra[0] |= 0x0800;
                                    return TRUE;
                                }
                            }
                            break;
                    }
                }
                break;

            default:
                // abs.W / abs.L
                linePtr = oldLine;
ABSOLUTE:
                reg2 = val & 0xFFFFFF; // 68000/68010: truncate to 24 bits for range checks
                if (reg2 & 0x800000) reg2 = reg2 | 0xFF000000; // 68000/68010: sign extend from 24 bits
                if ((evalKnown && width == WID_X && -0x8000 <= reg2 && reg2 <= 0x7FFF) || width == WID_W)
                {
                    // abs.w
                    if (reg2 < -0x8000 || reg2 > 0x7FFF)
                        Error("Absolute word addressing mode out of range");
                    ea -> mode = 0x38;
                    ea -> len = 1;
                    ea -> extra[0] = val;
                    return TRUE;
                }
                else
                {
                    // abs.l
                    ea -> mode = 0x39;
                    ea -> len = 2;
                    ea -> extra[0] = val >> 16;
                    ea -> extra[1] = val;
                    return TRUE;
                }
                break;

        }
    }

    BadMode();
    return FALSE;

    // p2-2
    // D/A R-R-R W/L SC-ALE 0 dddddddd
    // D/A R-R-R W/L SC-ALE 1 BS IS BD-SIZE - I/-I-S + base disp + outer disp
}


void Set68KMultiReg(int reg, int *regs, bool *warned)
{
    if (!*warned && *regs & (1 << reg))
    {
        Warning("MOVEM register specified twice");
        *warned = TRUE;
    }
    *regs |= 1 << reg;
}


int Get68KMultiRegs(void)
{
    int     reg1,reg2,regs,i;
    Str255  word;
    char    *oldLine;
    int     token;
    bool    warned;

    regs = 0;
    warned = FALSE;

    oldLine = linePtr;
    token = '/';
    while (token == '/')
    {
        reg1 = GetReg(DA_regs);
        if (reg1 == 16) reg1 = 15; // SP -> A7
        if (reg1 < 0)
        {
            IllegalOperand();      // abort if not valid register
            break;
        }

        // set single register bit
        Set68KMultiReg(reg1, &regs, &warned);

        // check for - or /
        oldLine = linePtr;
        token = GetWord(word);

        if (token == '-')       // register range
        {
            oldLine = linePtr;  // commit line position
            reg2 = GetReg(DA_regs); // check for second register
            if (reg2 == 16) reg2 = 15; // SP -> A7
            if (reg2 < 0)
            {
                IllegalOperand();      // abort if not valid register
                break;
            }
            if (reg1 < reg2)
            {
                for (i = reg1 + 1 ; i <= reg2; i++)
                    Set68KMultiReg(i, &regs, &warned);
            }
            else if (reg1 > reg2)
            {
                for (i = reg1 - 1 ; i >= reg2; i--)
                    Set68KMultiReg(i, &regs, &warned);
            }
            oldLine = linePtr;  // commit line position
            token = GetWord(word);
        }
        if (token == '/')  // is there another register?
            oldLine = linePtr;  // commit line position
    }
    linePtr = oldLine;

    return regs;
}


// get a MOVEC register name
// GetMOVECreg returns:
//      -2 (aka reg_EOL) and reports a "missing operand" error if end of line
//      -1 (aka reg_None) if no register found
//      else the actual 12-bit register code
// 000 = SFC   68010+
// 001 = DFC   68010+
// 002 = CACR  020/030/040
// 003 = TC    040/LC040
// 004 = ITT0  040/LC040
// 005 = ITT1  040/LC040
// 006 = DTT0  040/LC040
// 007 = DTT1  040/LC040
// 004 = IACR0 EC040
// 005 = IACR1 EC040
// 006 = DACR0 EC040
// 007 = DACR1 EC040
// 800 = USP   68010+
// 801 = VBR   68010+
// 802 = CAAR  020/030 but NOT 040
// 803 = MSP   020/030/040
// 804 = ISP   020/030/040
// 805 = MMUSR 040/LC040
// 806 = URP   040/LC040
// 807 = SRP   040/LC040
int GetMOVECreg(void)
{
    int     reg;

    reg = GetReg("SFC DFC USP VBR"); // 68010 MOVEC registers
    switch(reg)
    {
        case 0: // SFC = 000
        case 1: // DFC = 000
            break;

        case 2:
            reg = 0x800; // USP
            break;

        case 3:
            reg = 0x801; // VBR
            break;

        default: // unknown or GetReg error
            break;
    }

    return reg;
}


int M68K_DoCPUOpcode(int typ, int parm)
{
    int     val; // ,val2,val3;
    EArec   ea1,ea2;
    int     size;
    Str255  word;
    char    *oldLine;
//  int     token;
    int     reg1,reg2;
    bool    skipArithI;

    skipArithI = FALSE;

    switch(typ)
    {
        case o_Inherent:
            InstrW(parm);
            break;

        case o_DBcc:
            reg1 = GetReg(data_regs);
            if (reg1 >= 0)
            {
                if (Comma()) break;
                val = EvalWBranch(2);
                InstrWW(parm + reg1,val);
            }
            else IllegalOperand();
            break;

        case o_Branch:
            switch(parm & 3)
            {
                case WID_B:
                    val = EvalBranch(2);
                    if (val == 0)
                    {
                        Warning("Short branch can not have zero offset!");
                        InstrW(0x4E71); // assemble a NOP instead of a zero branch
                    }
                    else InstrW((parm & 0xFF00) + (val & 0x00FF));
                    break;

                case WID_X:
#if 1 // to enable optimized branches
#if 0 // long branch for 68020+
                    // if not a forward reference, can choose L, W, or B branch
                    val = EvalLBranch(2);
                    if (evalKnown && -128 <= val && val <= 127 && val != 0 && val != 0xFF)
                         InstrW((parm & 0xFF00) + (val & 0x00FF));
                    else if (evalKnown && -32768 <= val && val <= 32767)
                         InstrWW(parm & 0xFF00,val);
                    else InstrWL(parm & 0xFF00 + 0xFF,val);
#else
                    // if not a forward reference, can choose W or B branch
                    val = EvalWBranch(2);
                    if (evalKnown && -128 <= val && val <= 127 && val != 0 && val != 0xFF)
                         InstrW((parm & 0xFF00) + (val & 0x00FF));
                    else
                    {
                        if (val != 0 && -128 <= val && val <= 129) // max is +129 because short branch saves 2 bytes
                            Warning("Short branch could be used here");
                        InstrWW(parm & 0xFF00,val);
                    }
#endif
                    break;
#endif
                case WID_W:
                    val = EvalWBranch(2);
                    if (val != 0 && -128 <= val && val <= 129) // max is +129 because short branch saves 2 bytes
                        Warning("Short branch could be used here");
                    InstrWW(parm & 0xFF00,val);
                    break;

                case WID_L:
#if 0 // long branch for 68020+
                    val = EvalLBranch(2);
                    if (val != 0 && -128 <= val && val <= 131) // max is +131 because short branch saves 4 bytes
                        Warning("Short branch could be used here");
                    else if (-32768 <= val && val <= 32769) // max is +32769 because word branch saves 2 bytes
                        Warning("Word branch could be used here");
                    InstrWL(parm & 0xFF00 + 0xFF,val);
                    break;
#endif
                default:
                    BadMode();
                    break;
            }
            break;

        case o_Imm16:
            if (curCPU == CPU_68000 && parm == 0x4E74) return 0; // RTD

            if (Expect("#")) break;
            val = Eval();
            InstrWW(parm, val);
            break;

        case o_TRAP:
        case o_BKPT:
            if (Expect("#")) break;
            val = Eval();
            if (val < 0 || val > 15 || (typ == o_BKPT && val > 7))
            {
                IllegalOperand();
                InstrW(parm); // to avoid potential phase errors
            }
            else
                InstrW(parm + val);
            break;

        case o_LEA:
            if (GetEA(FALSE, -1, &ea1))
            {
                reg1 = ea1.mode & 0x38; // don't allow Dn An (An)+ or -(An)
                if (reg1 == 0x00 || reg1 == 0x08 || reg1 == 0x18 || reg1 == 0x20)
                    BadMode();
                else
                {
                    if (Comma()) break;
                    reg1 = GetReg(addr_regs);
                    if (reg1 == 8) reg1 = 7;
                    if (reg1 >= 0)
                        InstrWE(parm + (reg1 << 9), &ea1);
                    else IllegalOperand();
                }
            }
            break;

        case o_JMP:
            if (GetEA(FALSE, -1, &ea1))
            {
                reg1 = ea1.mode & 0x38; // don't allow Dn An (An)+ or -(An)
                if (reg1 == 0x00 || reg1 == 0x08 || reg1 == 0x18 || reg1 == 0x20)
                    BadMode();
                else
                    InstrWE(parm, &ea1);
            }
            break;

        case o_OneEA:
            if (GetEA(TRUE, -1, &ea1))
            {
                InstrWE(parm, &ea1);
            }
            break;

        case o_DIVMUL:
            if (GetEA(FALSE, WID_W, &ea1))
            {
                if (Comma()) break;
                reg1 = GetReg(data_regs);
                if (0 <= reg1 && reg1 <= 7)
                    InstrWE(parm + (reg1 << 9), &ea1);
                else IllegalOperand();
            }
            break;

        case o_MOVE:
            size = parm & 3;

            oldLine = linePtr;
            reg1 = GetReg("CCR SR USP");
            if (reg1 == reg_EOL) break;
            if (reg1 >= 0)
            {
                if (Comma()) break;
                if (GetEA(TRUE, size, &ea1))
                    switch(reg1)
                    {
                        case 0: // from CCR
                            if (curCPU == CPU_68010)
                            {
                                if (size == WID_B || size == WID_L)
                                    BadMode();
                                else
                                    InstrWE(0x42C0, &ea1);
                            }
                            else
                                BadMode();
                            break;

                        case 1: // from SR
                            if (size == WID_B || size == WID_L)
                                BadMode();
                            else
                                InstrWE(0x40C0, &ea1);
                            break;

                        case 2: // from USP
                            if ((ea1.mode & 0x38) != 0x08 || // An
                                size == WID_B || size == WID_W)
                                BadMode();
                            else
                                InstrW(0x4E68 + (ea1.mode & 0x0007));
                            break;
                    }
            }
            else
            {
                linePtr = oldLine;
                reg1 = size;
                if (reg1 == WID_X) reg1 = WID_W;
                if (GetEA(FALSE, reg1, &ea1))
                {
                    if (Comma()) break;

                    oldLine = linePtr;
                    switch(GetReg("CCR SR USP"))
                    {
                        case 0: // CCR
                            if (size == WID_B || size == WID_L)
                                BadMode();
                            else
                                InstrWE(0x44C0, &ea1);
                            break;

                        case 1: // SR
                            if (size == WID_B || size == WID_L)
                                BadMode();
                            else
                                InstrWE(0x46C0, &ea1);
                            break;

                        case 2: // USP
                            if ((ea1.mode & 0x38) != 0x08 || // An
                                size == WID_B || size == WID_W)
                                BadMode();
                            else
                            {
                                InstrW(0x4E60 + (ea1.mode & 0x0007));
                            }
                            break;

                        case reg_EOL:
                            break;

                        default:
                            linePtr = oldLine;

                            if (size == WID_X) size = WID_W;
                            if (GetEA(TRUE, size, &ea2))
                                InstrWEE(parm, &ea1, &ea2);
                            break;
                    }
                }
            }
            break;

        case o_Bit:
            size = parm & 3;
            parm = parm & 0xFFFC;

            oldLine = linePtr;
            reg1 = GetReg("D0 D1 D2 D3 D4 D5 D6 D7 #");
            if (reg1 >= 0)
            {
                val = 0; // to avoid unitialized use
                if (reg1 == 8) // immediate
                    val = Eval();
                if (Comma()) break;
                if (GetEA(TRUE, -1, &ea1))
                {
                    reg2 = (ea1.mode & 0x38);
                    if (reg2 == 0x08)                  { BadMode(); break; } // An not allowed
                    if (reg2 == 0x00 && size == WID_B) { BadMode(); break; } // Bxxx.B Dn
                    if (reg2 >= 0x10 && size == WID_L) { BadMode(); break; } // Bxxx.L everything else
                    // mask out 0x07 immediate if non-data reg EA
                    if (reg1 == 8 && reg2 != 0) val = val & 0x07;
                    if (reg1 == 8) InstrWWE(parm + 0x0800, val & 0x1F, &ea1);
                              else InstrWE (parm + 0x0100 + (reg1 << 9), &ea1);
                }
            }
            else IllegalOperand();
            break;

        case o_MOVEQ:
            if (Expect("#")) break;
            val = EvalByte();
            if (Comma()) break;
            reg1 = GetReg(data_regs);
            if (0 <= reg1 && reg1 <= 7)
                InstrW(0x7000 + (reg1 << 9) + val);
            else IllegalOperand();
            break;

        case o_ArithA:
            size = parm & 3;
            parm = parm & 0xFFFC;
            if (GetEA(FALSE, size, &ea1))
            {
                if (Comma()) break;
                reg1 = GetReg(addr_regs);
                if (reg1 == 8) reg1 = 7;
                if (reg1 >= 0)
                    InstrWE(parm + (reg1 << 9), &ea1);
                else IllegalOperand();
            }
            break;

        case o_Arith:
            size =  parm & 3;
            reg1 =  parm & 0x0038;
            reg2 =  parm & 0x8004;
            val = parm >> 12;
            parm = (parm & 0xFFC0) | 0x8000;
            oldLine = linePtr;
            if (GetWord(word) != '#'  // let immediate fall through
#if 0 // <-- set to 1 to convert ADD/CMP/SUB immediate to ADDI/CMPI/SUBI
                                    )
#else
                || val == 0xD || val == 0x9 || (val == 0xB && reg2 == 0x8004)) // except for ADD/CMP/SUB
#endif
            {
                linePtr = oldLine;
                if (size == WID_X) size = WID_W;
                reg1 = GetReg(data_regs);
                if (reg1 >= 0)
                {
                    // Dn,EA
                    if (Comma()) break;
                    if (GetEA(TRUE, size, &ea1))
                    {
                        if ((ea1.mode & 0x38) == 8) // An
                        {
                            // Dn,EA is not allowed except that ADD/CMP/SUB can become ADDA/CMPA/SUBA
                            switch(parm & 0xF000)
                            {
                                case 0xB000: // CMP
                                    if ((reg2 & 4) == 0) // EOR
                                    {
                                        BadMode();
                                        break;
                                    }
                                case 0xD000: // ADD
                                case 0x9000: // SUB
                                    if (size != WID_B)
                                    {
                                        parm = (parm & 0xF000) | 0xC0;
                                        if (size == WID_L) parm = parm | 0x100;
                                        InstrW(parm + (((ea1.mode & 7) << 9) + reg1));
                                        break;
                                    }

                                default:
                                    BadMode();
                            }
                            break;
                        }
                        if (reg2 & 4) // CMP Dn,EA is invalid unless EA is Dn
                        {   // dest must be a data register
                            if ((ea1.mode & 0x38) != 0) { BadMode(); break; }
                        }
                        if ((ea1.mode & 0x38) == 0 && (reg2 & 0x8000)) // Dn,Dn, except for EOR
                        {
                            // Dn,Dn needs the dest to be a register for CMP
                            InstrW(parm + (ea1.mode << 9) + reg1);
                            break;
                        }
                        InstrWE(parm + (reg1 << 9) + 0x0100, &ea1);
                    }
                }
                else
                {
                    // EA,Dn
                    linePtr = oldLine;
                    if (GetEA(FALSE, size, &ea1))
                    {
                        if (Comma()) break;
                        reg1 = GetReg(DA_regs);
                        if (reg1 == 16) reg1 = 15; // SP -> A7
                        if (0 <= reg1 && reg1 <= 7)
                        {   // EA,Dn
                            if (reg2 == 0) { BadMode(); break; } // EOR EA,Dn is invalid
                            if ((reg2 & 4) && (ea1.mode & 0x38) == 8 && size == WID_B)
                                { BadMode(); break; } // CMP.B An,Dn is invalid
                            InstrWE(parm + (reg1 << 9), &ea1);
                        }
                        else if (8 <= reg1 && reg1 <= 15 && size != WID_B)
                        {   // EA,An - for ADD/SUB/CMP only!
                            reg1 = reg1 - 8;
                            switch(parm & 0xF000)
                            {
                                case 0xD000: // AND
                                case 0x9000: // SUB
                                case 0xB000: // CMP/EOR
                                    if (reg2 & 0x8000) // disallow EOR
                                    {
                                        InstrWE((parm & 0xF000) + (reg1 << 9) + (size << 7) + 0x40, &ea1);
                                    //    IllegalOperand();
                                        break;
                                    }
                                default:
                                    IllegalOperand();
                            }
                        }
                        else IllegalOperand();
                    }
                }
                break;
            }
            linePtr = oldLine;

            // if immediate, set up parm for o_ArithI or o_LogImm
            if (!(reg1 & 0x0100))
            {
                skipArithI = TRUE; // do o_LogImm
                parm = (reg1 << 6) + size;
            }
            else
            {
                if (size == WID_X) size = WID_W;
                parm = (reg1 << 6) + (size << 6) + size;
            }

        case o_ArithI:
            if (!skipArithI)
            {
                size = parm & 3;
                parm = parm & 0xFFFC;
                if (Expect("#")) break;
                val = Eval();
                CheckSize(size,val);
                if (Comma()) break;
                if (GetEA(TRUE, -1, &ea1))
                {
                    if ((ea1.mode & 0x38) == 0x08) // arith immediate does not support An as dest
                    {
                        if ((parm & 0x0400) && size != WID_B) // SUBI/ADDI/CMPI = 04xx/06xx/0Cxx
                        {
                            switch(parm & 0x0F00)
                            {
                                default:
                                case 0x0400: parm = 0x9000; break; // SUBI
                                case 0x0600: parm = 0xD000; break; // ADDI
                                case 0x0C00: parm = 0xB000; break; // CMPI
                            }
                            if (size == WID_L) InstrWL(parm + ((ea1.mode & 7) << 9) + (size << 7) + 0x007C, val);
                                          else InstrWW(parm + ((ea1.mode & 7) << 9) + (size << 7) + 0x007C, val);
                            break;
                        }
                        BadMode();
                    }
                    else if (size == WID_L) InstrWLE(parm, val, &ea1);
                                       else InstrWWE(parm, val, &ea1);
                }
                break;
            }

        case o_LogImm:
            size = parm & 3;
            parm = parm & 0xFFFC;
            if (GetWord(word) != '#')
                BadMode();
            else
            {
                val = Eval();
                if (Comma()) break;
                oldLine = linePtr;
                reg1 = GetReg("CCR SR");
                if (reg1 == 0) // CCR
                {
                    CheckByte(val);
                    if (size != WID_X && size != WID_B)
                        BadMode();
                    else InstrWW((parm & 0xFF00) + 0x003C, val & 0xFF);
                }
                else if (reg1 == 1) // SR
                {
                    CheckSize(size,val);
                    if (size != WID_X && size != WID_W)
                        BadMode();
                    else InstrWW((parm & 0xFF00) + 0x007C, val);
                }
                else
                {
                    linePtr = oldLine;
                    if (size == WID_X) size = WID_W;
                    CheckSize(size,val);
                    if (GetEA(TRUE, -1, &ea1))
                    {
                        if ((ea1.mode & 0x38) == 0x08) // logical immediate does not support An as dest
                            BadMode();
                        else if (size == WID_L) InstrWLE(parm + (size << 6), val, &ea1);
                                           else InstrWWE(parm + (size << 6), val, &ea1);
                    }
                }
            }
            break;

        case o_MOVEM:
            size = (parm & 3) >> 1;
            parm = parm & 0xFFFC;

            oldLine = linePtr;
            reg1 = GetReg(DA_regs);
            if (reg1 == 16) reg1 = 15; // SP -> A7
            linePtr = oldLine;

            if (reg1 >= 0) // register-to-memory
            {
                reg2 = Get68KMultiRegs();
                if (Comma()) break;
                if (GetEA(TRUE, -1, &ea1))
                {
                    val = ea1.mode & 0x38;
                    if (val == 0x00 || val == 0x08 || val == 0x18)
                        BadMode();
                    else if (val == 0x20)
                    {
                        reg1 = 0;
                        for (val=0; val<=15; val++)
                        {
                            reg1 = (reg1 << 1) + (reg2 & 1);
                            reg2 = reg2 >> 1;
                        }
                        reg2 = reg1;
                    }
                    InstrWWE(parm, reg2, &ea1);
                }
            }
            else // memory-to-register
            {
                if (GetEA(TRUE, -1, &ea1))
                {
                    if (Comma()) break;
                    reg2 = Get68KMultiRegs();
                    val = ea1.mode & 0x38;
                    if (val == 0x00 || val == 0x08 || val == 0x20)
                        BadMode();
                    else InstrWWE(parm + 0x0400, reg2, &ea1);
                }
            }

            break;

        case o_ADDQ:
            size = parm & 3;
            parm = parm & 0xFFFC;

            if (GetWord(word) == '#')
            {
                val = Eval();
                if (Comma()) break;
                if (GetEA(TRUE, -1, &ea1))
                {
                    if ((ea1.mode & 0x38) == 0x08 && size == WID_B) // byte add to An is invalid
                        { BadMode(); break; }
                    if (val < 1 || val > 8) IllegalOperand();
                    val = val & 7;
                    InstrWE(parm + (val << 9), &ea1);
                }
            }
            else BadMode();
            break;

        case o_Shift: // bits 3,4 -> bits 9,10 for EA
            size = parm & 3;
            parm = parm & 0xFFFC;

            oldLine = linePtr;
            if (GetWord(word) == '#')
            {
                // #data,Dy
                val = Eval();
                if (Comma()) break;
                reg1 = GetReg(data_regs);
                if (reg1 >= 0)
                {
                    if (size == WID_X) size = WID_W;
                    if (val < 1 || val > 8) IllegalOperand();
                    val = val & 7;
                    InstrW(parm + (val << 9) + (size << 6) + reg1);
                }
            }
            else
            {
                linePtr = oldLine;
                if (GetEA(TRUE, -1, &ea1))
                {
                    val = ea1.mode & 0x38;
                    if (val == 0x00)
                    {
                        // Dx,Dy
                        if (Comma()) break;
                        if (size == WID_X) size = WID_W;
                        reg1 = GetReg(data_regs);
                        if (reg1 >= 0)
                            InstrW(parm + (ea1.mode << 9) + (size << 6) + reg1 + 0x20);
                        else IllegalOperand();
                    }
                    else if (val == 0x08)
                    {
                        // Ax
                        BadMode();
                    }
                    else
                    {
                        // EA
                        if (size != WID_W && size != WID_X) // memory shifts can't be .B or .L!
                            Error("Invalid size in opcode");
                        else InstrWE((parm & 0xF100) + ((parm & 0x18) << 6) + 0xC0, &ea1);
                    }
                }
            }
            break;

        case o_CHK:
            size = parm & 3;
            parm = parm & 0xFFFC;

            if (GetEA(FALSE, size, &ea1))
            {
                if ((ea1.mode & 0x38) == 0x08)
                    BadMode(); // address register not allowed
                else
                {
                    if (Comma()) break;
                    reg1 = GetReg(data_regs);
                    if (reg1 >= 0)
                        InstrWE(parm + (reg1 << 9), &ea1);
                }
            }
            break;

        case o_CMPM:
            if (GetEA(TRUE, -1, &ea1))
            {
                if (Comma()) break;
                if (GetEA(TRUE, -1, &ea2))
                {
                    reg1 = ea1.mode & 7;
                    reg2 = ea2.mode & 7;
                    if ((ea1.mode & 0x38) != 0x18 || (ea2.mode & 0x38) != 0x18)
                        BadMode();
                    else
                        InstrW(parm + (reg2 << 9) + reg1);
                }
            }
            break;

        case o_MOVEP:
            if (GetEA(TRUE, -1, &ea1))
            {
                if (Comma()) break;
                if (GetEA(TRUE, -1, &ea2))
                {
                    reg1 = ea1.mode & 7;
                    reg2 = ea2.mode & 7;
                    if ((ea1.mode & 0x38) == 0x00 && (ea2.mode & 0x38) == 0x28)
                        InstrWW(parm + (reg1 << 9) + reg2 + 0x0080, ea2.extra[0]); // Dx,(d16,Ay)
                    else if ((ea1.mode & 0x38) == 0x28 && (ea2.mode & 0x38) == 0x00)
                        InstrWW(parm + (reg2 << 9) + reg1, ea1.extra[0]); // (d16,Ay),Dx
                    else BadMode();
                }
            }
            break;

        case o_EXG:
            reg1 = GetReg(DA_regs);
            if (reg1 == 16) reg1 = 15; // SP -> A7
            if (reg1 >= 0)
            {
                if (Comma()) break;
                reg2 = GetReg(DA_regs);
                if (reg2 == 16) reg2 = 15; // SP -> A7
                if (reg2 >= 0)
                {
                    if (reg1 <= 7) // Dn
                    {
                        if (reg2 <= 7) // Dn,Dn
                            InstrW(0xC140 + (reg1 << 9) + reg2);
                        else // Dn,An
                            InstrW(0xC188 + (reg1 << 9) + (reg2 & 7));
                    }
                    else // An
                    {
                        reg1 = reg1 & 7;
                        if (reg2 <= 7) // An,Dn
                            InstrW(0xC188 + (reg2 << 9) + reg1);
                        else // An,An
                            InstrW(0xC148 + (reg1 << 9) + (reg2 & 7));
                    }
                }
                else IllegalOperand();
            }
            else IllegalOperand();
            break;

        case o_ABCD:
        case o_ADDX:
            if (GetEA(TRUE, -1, &ea1))
            {
                if (Comma()) break;
                if (GetEA(TRUE, -1, &ea2))
                {
                    reg1 = ea1.mode & 7;
                    reg2 = ea2.mode & 7;
                    if ((ea1.mode & 0x38) == 0x00 && (ea2.mode & 0x38) == 0x00)
                        InstrW(parm + (reg2 << 9) + reg1); // Dy,Dx
                    else if ((ea1.mode & 0x38) == 0x20 && (ea2.mode & 0x38) == 0x20)
                        InstrW(parm + (reg2 << 9) + reg1 + 8); // -(Ay),-(Ax)
                    else BadMode();
                }
            }
            break;

        case o_LINK:
            reg1 = GetReg(addr_regs);
            if (reg1 == 8) reg1 = 7;
            if (reg1 >= 0)
            {
                if (Comma()) break;
                if (Expect("#")) break;
                val = Eval();
                if (val > 0)
                    Warning("LINK opcode with positive displacement");
                CheckWord(val);
                InstrWW(parm + reg1, val);
            }
            else IllegalOperand();
            break;


        case o_OneA:
            reg1 = GetReg(addr_regs);
            if (reg1 == 8) reg1 = 7;
            if (reg1 >= 0)
                InstrW(parm + reg1);
            else IllegalOperand();
            break;

        case o_OneD:
            reg1 = GetReg(data_regs);
            if (reg1 == 8) reg1 = 7;
            if (reg1 >= 0)
                InstrW(parm + reg1);
            else IllegalOperand();
            break;

        case o_MOVEC:
            if (curCPU == CPU_68000) return 0;

            oldLine = linePtr;
            reg2 = GetMOVECreg();
            if (reg2 >= 0)
            {
                // Rc,Rn
                if (Comma()) break;
                reg1 = GetReg(DA_regs);
                if (reg1 == 16) reg1 = 15; // SP -> A7
                if (reg1 < 0) { IllegalOperand(); break; }
                val = 0;
            }
            else
            {
                // Rn,Rc
                linePtr = oldLine;
                reg1 = GetReg(DA_regs);
                if (reg1 == 16) reg1 = 15; // SP -> A7
                if (reg1 < 0) { IllegalOperand(); break; }
                if (Comma()) break;
                reg2 = GetMOVECreg();
                if (reg2 < 0) { IllegalOperand(); break; }
                val = 1;
            }
            InstrWW(parm + val,(reg1 << 12) + reg2);
            break;

        case o_MOVES:
            if (curCPU == CPU_68000) return 0;

            size = parm & 3;
            parm = parm & 0xFFFC;
            oldLine = linePtr;
            reg1 = GetReg(DA_regs);
            if (reg1 == 16) reg1 = 15; // SP -> A7
            if (reg1 >= 0)
            {
                // Rn,ea
                reg2 = 0x0800;  // direction = general register to ea
                if (Comma()) break;
                if (!GetEA(TRUE,size,&ea1)) break;
                if ((ea1.mode & 0x30) == 0) { BadMode(); break; }
            }
            else
            {
                // ea,Rn
                linePtr = oldLine;
                reg2 = 0x0000;  // direction = ea to general register
                if (!GetEA(TRUE,size,&ea1)) break;
                if (Comma()) break;
                if ((ea1.mode & 0x30) == 0) { BadMode(); break; }
                reg1 = GetReg(DA_regs);
                if (reg1 == 16) reg1 = 15; // SP -> A7
                if (reg1 < 0) break;
            }
            InstrWWE(parm + (size << 6), (reg1 << 12) + reg2, &ea1);
            break;

        default:
            return 0;
            break;
    }

    if (locPtr & 1)
    {
        Error("Code at non-word-aligned address");
        // deposit an extra byte to reset alignment and prevent further errors
        InstrAddB(0);
        // note: Inserting bytes in front won't work because offsets have already been assembled.
        // The line could be re-assembled by recursively calling DoCPUOpcode, but then
        // the label before the instruction would still be at the odd address.
    }

    return 1;
}


void Asm68KInit(void)
{
    char *p;

    p = AddAsm(versionName, &M68K_DoCPUOpcode, NULL, NULL);
    AddCPU(p, "68K",    CPU_68000, BIG_END, ADDR_24, LIST_24, 8, 0, M68K_opcdTab);
    AddCPU(p, "68000",  CPU_68000, BIG_END, ADDR_24, LIST_24, 8, 0, M68K_opcdTab);
    AddCPU(p, "68010",  CPU_68010, BIG_END, ADDR_24, LIST_24, 8, 0, M68K_opcdTab);
}