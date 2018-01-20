// asmf8.c - copyright 1998-2007 Bruce Tomlin

#define versionName "Fairchild F8 assembler"
#include "asmx.h"

enum
{
    o_None,         // No operands
    o_Immediate,    // 8-bit immediate operand
    o_Short,        // 4-bit immediate operand
    o_Register,     // Status register/indexed instruction
    o_Relative,     // Relative branch
    o_RegRel,       // Relative branch with embedded register
    o_Absolute,     // 16-bit absolute address
    o_SLSR,         // SL and SR instructions
    o_LR            // LR instruction

//  o_Foo = o_LabelOp,
};

const char F8_regs[] = "A W J H K Q KU KL QU QL IS DC0 PC0 PC1 DC P0 P1 P";

enum regType    // these are keyed to F8_regs[] above
{
    reg_0,          // 0..15 = scratchpad registers
    reg_A = 16,     // 16 - accumulator
    reg_W,          // 17 - status register
    reg_J,          // 18 - 09
    reg_H,          // 19 - 0A 0B
    reg_K,          // 20 - 0C 0D
    reg_Q,          // 21 - 0E 0F
    reg_KU,         // 22 - 0C
    reg_KL,         // 23 - 0D
    reg_QU,         // 24 - 0E
    reg_QL,         // 25 - 0F
    reg_IS,         // 26 - indirect scratchpad address register
    reg_DC0,        // 27 - memory index register
    reg_PC0,        // 28 - program counter
    reg_PC1,        // 29 - "stack pointer"
    reg_DC,         // 30 - alias for DC0
    reg_P0,         // 31 - alias for PC0
    reg_P1,         // 32 - alias for PC1
    reg_P           // 33 - alias for PC1
};

struct OpcdRec F8_opcdTab[] =
{
    {"PK",  o_None,     0x0C},
    {"LM",  o_None,     0x16},
    {"ST",  o_None,     0x17},
    {"COM", o_None,     0x18},
    {"LNK", o_None,     0x19},
    {"DI",  o_None,     0x1A},
    {"EI",  o_None,     0x1B},
    {"POP", o_None,     0x1C},
    {"INC", o_None,     0x1F},
    {"NOP", o_None,     0x2B},
    {"XDC", o_None,     0x2C},
    {"CLR", o_None,     0x70},
    {"AM",  o_None,     0x88},
    {"AMD", o_None,     0x89},
    {"NM",  o_None,     0x8A},
    {"OM",  o_None,     0x8B},
    {"XM",  o_None,     0x8C},
    {"CM",  o_None,     0x8D},
    {"ADC", o_None,     0x8E},

    {"LR",  o_LR,       0x00},  // LR handles lots of instructions

    {"SR",  o_SLSR,     0x12},
    {"SL",  o_SLSR,     0x13},

    {"LI",  o_Immediate,0x20},
    {"NI",  o_Immediate,0x21},
    {"OI",  o_Immediate,0x22},
    {"XI",  o_Immediate,0x23},
    {"AI",  o_Immediate,0x24},
    {"CI",  o_Immediate,0x25},
    {"IN",  o_Immediate,0x26},
    {"OUT", o_Immediate,0x27},

    {"PI",  o_Absolute, 0x28},
    {"JMP", o_Absolute, 0x29},
    {"DCI", o_Absolute, 0x2A},

    {"DS",  o_Register, 0x30},  // note: overrides default "DS" mnemonic
    {"LISU",o_Short,    0x60},  // reg must be 0..7
    {"LISL",o_Short,    0x68},  // reg must be 0..7
    {"LIS", o_Short,    0x70},
    {"INS", o_Short,    0xA0},
    {"OUTS",o_Short,    0xB0},
    {"AS",  o_Register, 0xC0},
    {"ASD", o_Register, 0xD0},
    {"XS",  o_Register, 0xE0},
    {"NS",  o_Register, 0xF0},

    {"BP",  o_Relative, 0x81},
    {"BC",  o_Relative, 0x82},
    {"BZ",  o_Relative, 0x84},
    {"BR7", o_Relative, 0x8F},
    {"BR",  o_Relative, 0x90},
    {"BM",  o_Relative, 0x91},
    {"BNC", o_Relative, 0x92},
    {"BNZ", o_Relative, 0x94},
    {"BNO", o_Relative, 0x98},

    {"BT",  o_RegRel,   0x80},  // reg must be 0..7
    {"BF",  o_RegRel,   0x90},

    {"",    o_Illegal,  0}
};


// --------------------------------------------------------------


int GetParenIS()
{
    Str255  word;
    char    *oldLine;

    GetWord(word);
    if (word[0] != 'I' || word[1] != 'S' || word[2] != 0) return 0;
    if (GetWord(word) != ')') return 0;

    oldLine = linePtr;
    switch(GetWord(word))
    {
        case '+':   return 13;
        case '-':   return 14;
        default:    break;
    }
    linePtr = oldLine;
    return 12;
}


int Get_S_Reg(void)
{
    Str255  word;
    int     token;
    char    *oldLine;
    int     reg;

    oldLine = linePtr;
    token = GetWord(word);

    // handle special names for registers 10-14
    if (word[0] == 'A' && word[1] == 0) return 10;
    if (word[0] == 'B' && word[1] == 0) return 11;
    if (word[0] == 'S' && word[1] == 0) return 12;
    if (word[0] == 'I' && word[1] == 0) return 13;
    if (word[0] == 'D' && word[1] == 0) return 14;

    // (IS) (IS+) (IS-) form for regs 12-14
    if (token == '(')
    {
        reg = GetParenIS();
        if (reg) return reg;
    }

    // handle numeric names for registers 0-9
    linePtr = oldLine;
    return Eval();
}


int Get_F8_Reg(void)
{
    Str255  word;
    int     token;
    char    *oldLine;
    int     reg;

    oldLine = linePtr;
    token = GetWord(word);

    // handle the random special registers
    reg = FindReg(word,F8_regs);
    if (reg >= 0) return reg + reg_A;

    // handle special names for registers 10-14
//  if (word[0] == 'A' && word[1] == 0) return 10; // can't use hexadecimal A here!
    if (word[0] == 'B' && word[1] == 0) return 11; // hexadecimal B
    if (word[0] == 'S' && word[1] == 0) return 12;
    if (word[0] == 'I' && word[1] == 0) return 13;
    if (word[0] == 'D' && word[1] == 0) return 14;

    // (IS) (IS+) (IS-) form for regs 12-14
    if (token == '(')
    {
        reg = GetParenIS();
        if (reg) return reg;
    }

    // handle numeric names for registers 0-9
    linePtr = oldLine;
    return Eval();
}


int F8_DoCPUOpcode(int typ, int parm)
{
    int     val;
    int     reg1;
    int     reg2;
//  Str255  word;
//  char    *oldLine;
//  int     token;

    switch(typ)
    {

        case o_None:
            InstrB(parm);
            break;

        case o_Immediate:
            val = EvalByte();
            InstrBB(parm,val);
            break;

        case o_Register:
            val = Get_S_Reg();
            if (val < 0 || val >= 15)
                IllegalOperand();
            else
                InstrB(parm+val);
            break;

        case o_Short:
            val = Eval();
            if (val < 0 || val > 15 || ((parm == 0x60 || parm == 0x68) && val > 7))
                IllegalOperand();
            else
                InstrB(parm+val);
            break;

        case o_Relative:
            val = EvalBranch(1);
            InstrBB(parm,val);
            break;

        case o_RegRel:
            reg1 = Eval();
            Comma();
            val = EvalBranch(1);
            if (parm == 0x80 && reg1 > 7)
                IllegalOperand();
            else
                InstrBB(parm+reg1,val);
            break;

        case o_Absolute:
            val = Eval();
            InstrBW(parm,val);
            break;

        case o_SLSR:
            val = Eval();
            if (val == 1)
                InstrB(parm);
            else if (val == 4)
                InstrB(parm+2);
            else
                IllegalOperand();
            break;

        case o_LR:
            val = -1;
            reg1 = Get_F8_Reg();
            Comma();
            reg2 = Get_F8_Reg();

            switch(reg1)
            {
                case reg_A:
                    if (reg2 == reg_KU)     val = 0x00; // LR A,KU
                    if (reg2 == reg_KL)     val = 0x01; // LR A,KL
                    if (reg2 == reg_QU)     val = 0x02; // LR A,QU
                    if (reg2 == reg_QL)     val = 0x03; // LR A,QL
                    if (reg2 == reg_IS)     val = 0x0A; // LR A,IS
                    if (reg_0 <= reg2 && reg2 <= reg_0+14)
                                            val = 0x40 + reg2; // LR A,n
                    break;

                case reg_K:
                    if (reg2 == reg_PC1)    val = 0x08; // LR K,PC1
                    if (reg2 == reg_P1)     val = 0x08; // LR K,PC1
                    if (reg2 == reg_P)      val = 0x08; // LR K,PC1
                    break;

                case reg_W:
                    if (reg2 == reg_J)      val = 0x1D; // LR W,J
                    break;

                case reg_J:
                    if (reg2 == reg_W)      val = 0x1E; // LR J,W
                    break;

                case reg_Q:
                    if (reg2 == reg_DC0)    val = 0x0E; // LR Q,DC0
                    if (reg2 == reg_DC)     val = 0x0E; // LR Q,DC0
                    break;

                case reg_H:
                    if (reg2 == reg_DC0)    val = 0x11; // LR H,DC0
                    if (reg2 == reg_DC)     val = 0x11; // LR H,DC0
                    break;

                case reg_KU:
                    if (reg2 == reg_A)      val = 0x04; // LR KU,A
                    break;

                case reg_KL:
                    if (reg2 == reg_A)      val = 0x05; // LR KL,A
                    break;

                case reg_QU:
                    if (reg2 == reg_A)      val = 0x06; // LR QU,A
                    break;

                case reg_QL:
                    if (reg2 == reg_A)      val = 0x07; // LR QL,A
                    break;

                case reg_IS:
                    if (reg2 == reg_A)      val = 0x0B; // LR IS,A
                    break;

                case reg_PC1:
                case reg_P1:
                case reg_P:
                    if (reg2 == reg_K)      val = 0x09; // LR PC1,K
                    break;

                case reg_PC0:
                case reg_P0:
                    if (reg2 == reg_Q)      val = 0x0D; // LR PC0,Q
                    break;

                case reg_DC0:
                case reg_DC:
                    if (reg2 == reg_Q)      val = 0x0F; // LR DC0,H
                    if (reg2 == reg_H)      val = 0x10; // LR DC0,H
                    break;

                default:
                    if (reg_0 <= reg1 && reg1 <= reg_0+14 && reg2 == reg_A)
                            val = 0x50 + reg1;          // LR n,A
            }

            if (val < 0)
                IllegalOperand();
            else
                InstrB(val);
            break;

        default:
            return 0;
            break;
    }
    return 1;
}


void AsmF8Init(void)
{
    char *p;

    p = AddAsm(versionName, &F8_DoCPUOpcode, NULL, NULL);
    AddCPU(p, "F8", 0, BIG_END, ADDR_16, LIST_24, 8, 0, F8_opcdTab);
}