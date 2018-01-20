// asm8085.c - copyright 1998-2007 Bruce Tomlin

#define versionName "8085 assembler"
#include "asmx.h"

enum
{
    CPU_8080,
    CPU_8085,
    CPU_8085U
};

#define I_8085  0x100
#define I_8085U 0x200

enum instrType
{
    o_None,         // No operands

    o_Immediate,    // one-byte immediate operand
    o_LImmediate,   // two-byte immediate operand (mostly JMPs)
    o_MOV,          // MOV r,r opcode
    o_RST,          // RST instruction
    o_Arith,        // Arithmetic instructions
    o_PushPop,      // PUSH and POP instructions
    o_MVI,          // MVI instruction
    o_LXI,          // LXI instruciton
    o_INR,          // INR/DCR instructions
    o_INX,          // INX/DCX/DAD instructions
    o_STAX          // STAX/LDAX instructions

//  o_Foo = o_LabelOp,
};

const char I8085_regs1[]      = "B C D E H L M A";
const char I8085_regs2[]      = "B D H SP";

struct OpcdRec I8085_opcdTab[] =
{
    {"NOP", o_None, 0x00},
    {"RLC", o_None, 0x07},
    {"RRC", o_None, 0x0F},
    {"RAL", o_None, 0x17},
    {"RAR", o_None, 0x1F},
    {"RIM", o_None, 0x20 + I_8085}, // 8085-only
    {"DAA", o_None, 0x27},
    {"CMA", o_None, 0x2F},
    {"SIM", o_None, 0x30 + I_8085}, // 8085-only
    {"STC", o_None, 0x37},
    {"CMC", o_None, 0x3F},
    {"HLT", o_None, 0x76},
    {"RNZ", o_None, 0xC0},
    {"RZ",  o_None, 0xC8},
    {"RET", o_None, 0xC9},
    {"RNC", o_None, 0xD0},
    {"RC",  o_None, 0xD8},
    {"RPO", o_None, 0xE0},
    {"XTHL",o_None, 0xE3},
    {"RPE", o_None, 0xE8},
    {"PCHL",o_None, 0xE9},
    {"XCHG",o_None, 0xEB},
    {"RP",  o_None, 0xF0},
    {"DI",  o_None, 0xF3},
    {"RM",  o_None, 0xF8},
    {"SPHL",o_None, 0xF9},
    {"EI",  o_None, 0xFB},

    {"ADI", o_Immediate, 0xC6},
    {"ACI", o_Immediate, 0xCE},
    {"OUT", o_Immediate, 0xD3},
    {"SUI", o_Immediate, 0xD6},
    {"IN",  o_Immediate, 0xDB},
    {"SBI", o_Immediate, 0xDE},
    {"ANI", o_Immediate, 0xE6},
    {"XRI", o_Immediate, 0xEE},
    {"ORI", o_Immediate, 0xF6},
    {"CPI", o_Immediate, 0xFE},

    {"SHLD",o_LImmediate, 0x22},
    {"LHLD",o_LImmediate, 0x2A},
    {"STA", o_LImmediate, 0x32},
    {"LDA", o_LImmediate, 0x3A},
    {"JNZ", o_LImmediate, 0xC2},
    {"JMP", o_LImmediate, 0xC3},
    {"CNZ", o_LImmediate, 0xC4},
    {"JZ",  o_LImmediate, 0xCA},
    {"CZ",  o_LImmediate, 0xCC},
    {"CALL",o_LImmediate, 0xCD},
    {"JNC", o_LImmediate, 0xD2},
    {"CNC", o_LImmediate, 0xD4},
    {"JC",  o_LImmediate, 0xDA},
    {"CC",  o_LImmediate, 0xDC},
    {"JPO", o_LImmediate, 0xE2},
    {"CPO", o_LImmediate, 0xE4},
    {"JPE", o_LImmediate, 0xEA},
    {"CPE", o_LImmediate, 0xEC},
    {"JP",  o_LImmediate, 0xF2},
    {"CP",  o_LImmediate, 0xF4},
    {"JM",  o_LImmediate, 0xFA},
    {"CM",  o_LImmediate, 0xFC},

    {"MOV", o_MOV,     0},

    {"RST", o_RST,     0},

    {"ADD", o_Arith, 0x80},
    {"ADC", o_Arith, 0x88},
    {"SUB", o_Arith, 0x90},
    {"SBB", o_Arith, 0x98},
    {"ANA", o_Arith, 0xA0},
    {"XRA", o_Arith, 0xA8},
    {"ORA", o_Arith, 0xB0},
    {"CMP", o_Arith, 0xB8},

    {"PUSH",o_PushPop, 0xC5},
    {"POP", o_PushPop, 0xC1},

    {"MVI", o_MVI,   0x06},
    {"LXI", o_LXI,   0x01},
    {"INR", o_INR,   0x04},
    {"DCR", o_INR,   0x05},
    {"INX", o_INX,   0x03},
    {"DAD", o_INX,   0x09},
    {"DCX", o_INX,   0x0B},
    {"STAX",o_STAX,  0x02},
    {"LDAX",o_STAX,  0x0A},

//  Undocumented 8085 instructions:
//  These are in most "real" 8085 versions,
//  but are likely to not be found in VHDL cores, etc.

    {"DSUB",o_None,       0x08 + I_8085U}, // HL = HL - BC
    {"ARHL",o_None,       0x10 + I_8085U}, // arithmetic shift right HL
    {"RDEL",o_None,       0x18 + I_8085U}, // rotate DE left through carry
    {"LDHI",o_Immediate,  0x28 + I_8085U}, // DE = HL + imm
    {"LDSI",o_Immediate,  0x38 + I_8085U}, // DE = SP + imm
    {"RSTV",o_None,       0xCB + I_8085U}, // call 0x40 if overflow
    {"LHLX",o_None,       0xED + I_8085U}, // L = (DE), H = (DE+1)
    {"SHLX",o_None,       0xD9 + I_8085U}, // (DE) = L, (DE+1) = H
    {"JNX5",o_LImmediate, 0xDD + I_8085U},
    {"JX5", o_LImmediate, 0xFD + I_8085U},

    {"",    o_Illegal,  0}
};


// --------------------------------------------------------------


int I8085_DoCPUOpcode(int typ, int parm)
{
    int     val;
    int     reg1;
    int     reg2;
    Str255  word;
    char    *oldLine;
//  int     token;

    switch(typ)
    {
        case o_None:
            if ((parm & I_8085)  && curCPU == CPU_8080)  return 0;
            if ((parm & I_8085U) && curCPU != CPU_8085U) return 0;

            InstrB (parm & 255);
            break;

        case o_Immediate:
            if ((parm & I_8085U) && curCPU != CPU_8085U) return 0;

            val = Eval();
            InstrBB(parm & 0xFF,val);
            break;

        case o_LImmediate:
            if ((parm & I_8085U) && curCPU != CPU_8085U) return 0;

            val = Eval();
            InstrBW(parm,val);
            break;

        case o_MOV:
            GetWord(word);
            reg1 = FindReg(word,I8085_regs1);
            if (reg1 < 0)
                IllegalOperand();
            else
            {
                oldLine = linePtr;
                if (GetWord(word) != ',')
                {
                    linePtr = oldLine;
                    Comma();
                }
                else
                {
                    GetWord(word);
                    reg2 = FindReg(word,I8085_regs1);
                    if (reg2 < 0 || (reg1 == 6 && reg2 == 6))
                        IllegalOperand();
                    else
                        InstrB(0x40 + (reg1 << 3) + reg2);
                }
            }
            break;

        case o_RST:
            val = Eval();
            if (0 <= val && val <= 7)
                InstrB(0xC7 + val*8);
            else IllegalOperand();
            break;

        case o_Arith:
            GetWord(word);
            reg1 = FindReg(word,I8085_regs1);
            if (reg1 < 0)
                IllegalOperand();
            else
                InstrB(parm + reg1);
            break;

        case o_PushPop:
            GetWord(word);
            reg1 = FindReg(word,"B D H PSW");
            if (reg1 < 0)
                IllegalOperand();
            else
                InstrB(parm + (reg1 << 4));
            break;

        case o_MVI:
            GetWord(word);
            reg1 = FindReg(word,I8085_regs1);
            if (reg1 < 0)
                IllegalOperand();
            else
            {
                oldLine = linePtr;
                if (GetWord(word) != ',')
                {
                    linePtr = oldLine;
                    Comma();
                }
                else
                {
                    val = Eval();
                    InstrBB(parm + (reg1 << 3), val);
                }
            }
            break;

        case o_LXI:
            GetWord(word);
            reg1 = FindReg(word,I8085_regs2);
            if (reg1 < 0)
                IllegalOperand();
            else
            {
                oldLine = linePtr;
                if (GetWord(word) != ',')
                {
                    linePtr = oldLine;
                    Comma();
                }
                else
                {
                    val = Eval();
                    InstrBW(parm + (reg1 << 4), val);
                }
            }
            break;

        case o_INR:
            GetWord(word);
            reg1 = FindReg(word,I8085_regs1);
            if (reg1 < 0)
                IllegalOperand();
            else
                InstrB(parm + (reg1 << 3));
            break;

        case o_INX:
            GetWord(word);
            reg1 = FindReg(word,I8085_regs2);
            if (reg1 < 0)
                IllegalOperand();
            else
                InstrB(parm + (reg1 << 4));
            break;

        case o_STAX:
            GetWord(word);
            reg1 = FindReg(word,"B D");
            if (reg1 < 0)
                IllegalOperand();
            else
                InstrB(parm + (reg1 << 4));
            break;

        default:
            return 0;
            break;
    }
    return 1;
}


void Asm8085Init(void)
{
    char *p;

    p = AddAsm(versionName, &I8085_DoCPUOpcode, NULL, NULL);
    AddCPU(p, "8080",  CPU_8080,  LITTLE_END, ADDR_16, LIST_24, 8, 0, I8085_opcdTab);
    AddCPU(p, "8085",  CPU_8085,  LITTLE_END, ADDR_16, LIST_24, 8, 0, I8085_opcdTab);
    AddCPU(p, "8085U", CPU_8085U, LITTLE_END, ADDR_16, LIST_24, 8, 0, I8085_opcdTab);
}