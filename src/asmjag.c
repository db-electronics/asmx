// asmjag.c - copyright 1998-2007 Bruce Tomlin

#define versionName "Atari Jaguar GPU/DSP assembler"
#include "asmx.h"

enum instrType
{
    o_None,     // no operands - NOP
    o_One,      // one operand - Rd - ABS/NEG/etc
    o_Two,      // two operands - Rs,Rd - most instructions
    o_Num_15,   // numeric operand - n,Rd - n=-16..+15 - CMPQ
    o_Num_31,   // numeric operand - n,Rd - n=0..31 - BCLR/BSET/BTST/MOVEQ
    o_Num_32,   // numeric operand - n,Rd - n=1..32 - ADDQ/SUBQ
    o_JR,       // jump relative - cc,n - n=-16..+15 words, reg2=cc
    o_JUMP,     // jump absolute - cc,(Rs) - reg2=cc
    o_MOVEI,    // move immediate - n,Rn - n in second word
    o_MOVE,     // MOVE instruction - PC,Rn / Rn,Rn
    o_LOAD,     // LOAD instruction - various forms
    o_LOADn,    // LOADB/LOADP/LOADW - (Rs),Rd
    o_STORE,    // STORE instruction - various forms
    o_STOREn,   // STOREB/STOREP/STOREM - Rs,(Rd)

//  o_Foo = o_LabelOp,
};

enum
{
    CPU_TOM,    // GPU
    CPU_JERRY   // DSP
};

enum
{
    SUB32   = 0x2000, // n = 32-n
    TOMONLY = 0x4000, // opcode is Tom-only
    JERONLY = 0x8000  // opcode is Jerry-only
};

struct OpcdRec Jag_opcdTab[] =
{
    {"ADD",     o_Two,     0},
    {"ADDC",    o_Two,     1},
    {"ADDQ",    o_Num_32,  2},
    {"ADDQT",   o_Num_32,  3},
    {"SUB",     o_Two,     4},
    {"SUBC",    o_Two,     5},
    {"SUBQ",    o_Num_32,  6},
    {"SUBQT",   o_Num_32,  7},
    {"NEG",     o_One,     8},
    {"AND",     o_Two,     9},
    {"OR",      o_Two,    10},
    {"XOR",     o_Two,    11},
    {"NOT",     o_One,    12},
    {"BTST",    o_Num_31, 13},
    {"BSET",    o_Num_31, 14},
    {"BCLR",    o_Num_31, 15},

    {"MULT",    o_Two,    16},
    {"IMULT",   o_Two,    17},
    {"IMULTN",  o_Two,    18},
    {"RESMAC",  o_One,    19},
    {"IMACN",   o_Two,    20},
    {"DIV",     o_Two,    21},
    {"ABS",     o_One,    22},
    {"SH",      o_Two,    23},
    {"SHLQ",    o_Num_32, 24 + SUB32}, // encodes 32-n!
    {"SHRQ",    o_Num_32, 25 + SUB32}, // encodes 32-n!
    {"SHA",     o_Two,    26},
    {"SHARQ",   o_Num_32, 27 + SUB32}, // encodes 32-n!
    {"ROR",     o_Two,    28},
    {"RORQ",    o_Num_32, 29},
    {"ROLQ",    o_Num_32, 29 + SUB32}, // same as RORQ 32-n,Rn
    {"CMP",     o_Two,    30},
    {"CMPQ",    o_Num_15, 31},

    {"SAT8",    o_One,    32 + TOMONLY},
    {"SUBQMOD", o_Num_32, 32 + JERONLY},
    {"SAT16",   o_One,    33 + TOMONLY},
    {"SAT16S",  o_One,    33 + JERONLY},
//  {"MOVE",    o_MOVE,   34},
    {"MOVEQ",   o_Num_31, 35},
    {"MOVETA",  o_Two,    36},
    {"MOVEFA",  o_Two,    37},
    {"MOVEI",   o_MOVEI,  38},
    {"LOADB",   o_LOADn,  39},
    {"LOADW",   o_LOADn,  40},
//  {"LOAD",    o_LOAD,   41},
    {"LOADP",   o_LOADn,  42 + TOMONLY},
    {"SAT32S",  o_One,    42 + JERONLY},
//  {"LOAD",    o_LOAD,   43}, // (R14+n),Rn
//  {"LOAD",    o_LOAD,   44}, // (R15+n),Rn
    {"STOREB",  o_STOREn, 45},
    {"STOREW",  o_STOREn, 46},
//  {"STORE",   o_STORE,  47},

    {"STOREP",  o_STOREn, 48 + TOMONLY},
    {"MIRROR",  o_One,    48 + JERONLY},
//  {"STORE",   o_STORE,  49}, // Rn,(R14+n)
//  {"STORE",   o_STORE,  50}, // Rn,(R15+n)
//  {"MOVE",    o_MOVE,   51},
    {"JUMP",    o_JUMP,   52},
    {"JR",      o_JR,     53},
    {"MMULT",   o_Two,    54},
    {"MTOI",    o_Two,    55},
    {"NORMI",   o_Two,    56},
    {"NOP",     o_None,   57},
//  {"LOAD",    o_LOAD,   58}, // (R14+Rn),Rn
//  {"LOAD",    o_LOAD,   59}, // (R15+Rn),Rn
//  {"STORE",   o_STORE,  60}, // Rn,(R14+Rn)
//  {"STORE",   o_STORE,  61}, // Rn,(R15+Rn)
    {"SAT24",   o_One,    62},
    {"UNPACK",  o_One,    63 + TOMONLY},
    {"PACK",    o_One,    63 + TOMONLY + (1<<6)},
    {"ADDQMOD", o_Num_32, 63 + JERONLY},

    {"MOVE",    o_MOVE,    0},
    {"LOAD",    o_LOAD,    0},
    {"STORE",   o_STORE,   0},

    {"",        o_Illegal, 0}
};


char jag_regs[] = "R0 R1 R2 R3 R4 R5 R6 R7 R8 R9 R10 R11 R12 R13 R14 R15 R16 "
                  "R17 R18 R19 R20 R21 R22 R23 R24 R25 R26 R27 R28 R29 R30 R31";

char jag_conds[] = "NZ Z NC NCNZ NCZ C CNZ CZ NN NNNZ NNZ N N_NZ N_Z "
                   "T A NE EQ CC HS HI CS LO PL MI F";
char jag_cond[]  = { 1,2, 4,   5,  6,8,  9,10,20,  21, 22,24, 25, 26,
                    0,0, 1, 2, 4, 4, 5, 8, 8,20,24,31};

// --------------------------------------------------------------


void InstrJag(u_short parm, u_short reg1, u_short reg2)
{
    InstrW(((parm & 0x3F) << 10) + ((reg1 & 0x1F) << 5) + (reg2 & 0x1F));
}


int Jag_DoCPUOpcode(int typ, int parm)
{
    int     val;
    int     reg1;
    int     reg2;
    Str255  word;
    char    *oldLine;
    int     token;

    if ((parm & TOMONLY) && curCPU == CPU_JERRY) return 0;
    if ((parm & JERONLY) && curCPU == CPU_TOM)   return 0;

    switch(typ)
    {
        case o_None:
            InstrJag(parm, 0, 0);
            break;


        case o_One:
            switch((reg2 = GetReg(jag_regs)))
            {
                case reg_None:
                    IllegalOperand();
                case reg_EOL:
                    break;

                default:
                    InstrJag(parm, parm>>6, reg2);
                    break;
            }
            break;

        case o_Two:
            switch((reg1 = GetReg(jag_regs)))
            {
                case reg_None:
                    IllegalOperand();
                case reg_EOL:
                    break;

                default:
                    if (Comma()) break;

                    switch((reg2 = GetReg(jag_regs)))
                    {
                        case reg_None:
                            IllegalOperand();
                        case reg_EOL:
                            break;

                        default:
                            InstrJag(parm,reg1,reg2);
                            break;
                    }
            }
            break;

        case o_Num_15:
        case o_Num_31:
        case o_Num_32:
            switch(typ)
            {
                case o_Num_15: reg1 = -16; reg2 = 15; break;
                default:
                case o_Num_31: reg1 =   0; reg2 = 31; break;
                case o_Num_32: reg1 =   1; reg2 = 32; break;
            }
            val = Eval();
            if (val < reg1 || val > reg2)
                Error("Constant out of range");
            if (parm & SUB32) reg1 = 32 - val;
                         else reg1 = val;
            if (Comma()) break;
            switch((reg2 = GetReg(jag_regs)))
            {
                case reg_None:
                    IllegalOperand();
                case reg_EOL:
                    break;

                default:
                    InstrJag(parm, reg1, reg2);
                    break;
            }
            break;

        case o_JR:
        case o_JUMP:
            // get the condition code
            oldLine = linePtr;
            switch((reg1 = GetReg(jag_conds)))
            {
                case reg_EOL:
                    val = -1;
                    break;

                case reg_None:
                    linePtr = oldLine;
                    val = Eval();
                    if (val < 0 || val > 31)
                    {
                        Error("Constant out of range");
                        val = 0;
                    }
                    break;

                default:
                    val = jag_cond[reg1];
                    break;
            }
            if (val < 0) break;

            reg1 = val;
            if (Comma()) break;
            if (typ == o_JR)
            {
                // JR cc,n
                val = Eval();
#if 0
                // the old way before WORDWIDTH
                reg2 = (val - locPtr - 2)/2;
#else
                // the new way after WORDWIDTH
                reg2 = val - (locPtr + 2)/2;
#endif
                if (!errFlag && (val < -16 || val > 15))
                    Error("Branch out of range");
                InstrJag(parm,reg2,reg1);
            }
            else
            {
                // JUMP cc,(Rn)
                if (Expect("(")) break;
                switch((reg2 = GetReg(jag_regs)))
                {
                    case reg_None:
                        IllegalOperand();
                    case reg_EOL:
                        break;

                    default:
                        if (RParen()) break;
                        InstrJag(parm,reg2,reg1);
                        break;
                }
            }
            break;

        case o_MOVEI:
            val = Eval();
            if (Comma()) break;
            switch((reg2 = GetReg(jag_regs)))
            {
                case reg_None:
                    IllegalOperand();
                case reg_EOL:
                    break;

                default:
                    InstrWL(((parm & 0x3F) << 10) + reg2,
                            (val >> 16) | (val << 16));
                    break;
            }
            break;

        case o_MOVE: // PC,Rd or Rs,Rd
            switch((reg1 = GetReg("R0 R1 R2 R3 R4 R5 R6 R7 R8 R9 R10 R11 R12 R13 R14 R15 R16 "
                                  "R17 R18 R19 R20 R21 R22 R23 R24 R25 R26 R27 R28 R29 R30 R31 PC")))
            {
                case reg_None:
                    IllegalOperand();
                case reg_EOL:
                    break;

                default:
                    if (Comma()) break;

                    switch((reg2 = GetReg(jag_regs)))
                    {
                        case reg_None:
                            IllegalOperand();
                        case reg_EOL:
                            break;

                        default:
                            parm = 34;
                            if (reg1 == 32) parm = 51;
                            InstrJag(parm,reg1,reg2);
                            break;
                    }
            }
            break;

        case o_LOAD: // (Rn),Rn = 41 / (R14/R15+n),Rn = 43/44 / (R14/R15+Rn),Rn = 58/59
            if (Expect("(")) break;
            switch((reg1 = GetReg(jag_regs)))
            {
                case reg_None:
                    IllegalOperand();
                case reg_EOL:
                    break;

                case 14:
                case 15:
                    oldLine = linePtr;
                    token = GetWord(word);
                    if (token == '+')
                    {
                        parm = reg1 - 14 + 58;
                        oldLine = linePtr;
                        switch((reg1 = GetReg(jag_regs)))
                        {
                        case reg_EOL:
                            break;

                        case reg_None:
                            // (R14/R15 + n)
                            parm = parm - 58 + 43;
                            linePtr = oldLine;
                            val = Eval();
                            if (val < 1 || val > 32)
                                Error("Constant out of range");
                            reg1 = val;

                        default:
                            if (RParen()) break;
                            if (Comma()) break;
                            switch((reg2 = GetReg(jag_regs)))
                            {
                                case reg_None:
                                    IllegalOperand();
                                case reg_EOL:
                                    break;

                                default:
                                    InstrJag(parm,reg1,reg2);
                                    break;
                            }
                            break;
                        }
                        break;
                    }
                    linePtr = oldLine;

                default:
                    parm = 41;
                    if (RParen()) break;
                    if (Comma()) break;

                    switch((reg2 = GetReg(jag_regs)))
                    {
                        case reg_None:
                            IllegalOperand();
                        case reg_EOL:
                            break;

                        default:
                            InstrJag(parm,reg1,reg2);
                            break;
                    }
            }
            break;

        case o_LOADn: // LOADB/LOADP/LOADW (Rn),Rn
            if (Expect("(")) break;
            switch((reg1 = GetReg(jag_regs)))
            {
                case reg_None:
                    IllegalOperand();
                case reg_EOL:
                    break;

                default:
                    if (RParen()) break;
                    if (Comma()) break;

                    switch((reg2 = GetReg(jag_regs)))
                    {
                        case reg_None:
                            IllegalOperand();
                        case reg_EOL:
                            break;

                        default:
                            InstrJag(parm,reg1,reg2);
                            break;
                    }
            }
            break;

        case o_STORE: // Rn,(Rn) = 47 / Rn,(R14/R15+n) = 49/50 / Rn,(R14/R15+Rn) = 60/61
            switch((reg1 = GetReg(jag_regs)))
            {
                case reg_None:
                    IllegalOperand();
                case reg_EOL:
                    break;

                default:
                    if (Comma()) break;
                    if (Expect("(")) break;
                    switch((reg2 = GetReg(jag_regs)))
                    {
                        case reg_None:
                            IllegalOperand();
                        case reg_EOL:
                            break;

                        case 14:
                        case 15:
                            oldLine = linePtr;
                            token = GetWord(word);
                            if (token == '+')
                            {
                                parm = reg2 - 14 + 60;
                                oldLine = linePtr;
                                switch((reg2 = GetReg(jag_regs)))
                                {
                                    case reg_EOL:
                                        break;

                                    case reg_None:
                                        // (R14/R15 + n)
                                        parm = parm - 60 + 49;
                                        linePtr = oldLine;
                                        val = Eval();
                                        if (val < 1 || val > 32)
                                            Error("Constant out of range");
                                        reg2 = val;

                                    default:
                                        if (RParen()) break;
                                        InstrJag(parm,reg1,reg2);
                                    break;
                                }
                                break;
                            }
                            linePtr = oldLine;

                        default:
                            parm = 47;
                            if (RParen()) break;
                            InstrJag(parm,reg1,reg2);
                            break;
                    }
            }
            break;

        case o_STOREn: // STOREB/STOREP/STOREW Rn,(Rn)
            switch((reg1 = GetReg(jag_regs)))
            {
                case reg_None:
                    IllegalOperand();
                case reg_EOL:
                    break;

                default:
                    if (Comma()) break;
                    if (Expect("(")) break;
                    switch((reg2 = GetReg(jag_regs)))
                    {
                        case reg_None:
                            IllegalOperand();
                        case reg_EOL:
                            break;

                        default:
                            if (RParen()) break;
                            InstrJag(parm,reg1,reg2);
                            break;
                    }
            }
            break;

        default:
            return 0;
            break;
    }
    return 1;
}


void AsmJagInit(void)
{
    char *p;

    p = AddAsm(versionName, &Jag_DoCPUOpcode, NULL, NULL);
    AddCPU(p, "TOM",   CPU_TOM,   BIG_END, ADDR_16, LIST_24, 16, 0, Jag_opcdTab);
    AddCPU(p, "JERRY", CPU_JERRY, BIG_END, ADDR_16, LIST_24, 16, 0, Jag_opcdTab);
}