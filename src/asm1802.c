// asm1802.c - copyright 1998-2007 Bruce Tomlin

#define versionName "RCA 1802 assembler"
#include "asmx.h"

enum
{
    o_None,         // No operands
    o_Register,     // register operand (with optional "R" in front)
    o_Immediate,    // 8-bit immediate operand
    o_Branch,       // short branch
    o_LBranch,      // long branch
    o_INPOUT        // INP/OUT instruction

//  o_Foo = o_LabelOp,
};

struct OpcdRec RCA1802_opcdTab[] =
{
    {"IDL", o_None,     0x00},
    {"LDN", o_Register, 0x00},  // note: LDN R0 not allowed
    {"INC", o_Register, 0x10},
    {"DEC", o_Register, 0x20},
    {"BR",  o_Branch,   0x30},
    {"BQ",  o_Branch,   0x31},
    {"BZ",  o_Branch,   0x32},
    {"BDF", o_Branch,   0x33},
    {"BPZ", o_Branch,   0x33}, // duplicate opcode
    {"BGE", o_Branch,   0x33}, // duplicate opcode
    {"B1",  o_Branch,   0x34},
    {"B2",  o_Branch,   0x35},
    {"B3",  o_Branch,   0x36},
    {"B4",  o_Branch,   0x37},
    {"SKP", o_None,     0x38},
    {"NBR", o_Branch,   0x38}, // duplicate opcode
    {"BNQ", o_Branch,   0x39},
    {"BNZ", o_Branch,   0x3A},
    {"BNF", o_Branch,   0x3B},
    {"BM",  o_Branch,   0x3B}, // duplicate opcode
    {"BL",  o_Branch,   0x3B}, // duplicate opcode
    {"BN1", o_Branch,   0x3C},
    {"BN2", o_Branch,   0x3D},
    {"BN3", o_Branch,   0x3E},
    {"BN4", o_Branch,   0x3F},
    {"LDA", o_Register, 0x40},
    {"STR", o_Register, 0x50},
    {"IRX", o_None,     0x60},
    {"OUT", o_INPOUT,   0x60},
    // no opcode for 0x68
    {"INP", o_INPOUT,   0x68},
    {"RET", o_None,     0x70},
    {"DIS", o_None,     0x71},
    {"LDXA",o_None,     0x72},
    {"STXD",o_None,     0x73},
    {"ADC", o_None,     0x74},
    {"SDB", o_None,     0x75},
    {"SHRC",o_None,     0x76},
    {"RSHR",o_None,     0x76}, // duplicate opcode
    {"SMB", o_None,     0x77},
    {"SAV", o_None,     0x78},
    {"MARK",o_None,     0x79},
    {"REQ", o_None,     0x7A},
    {"SEQ", o_None,     0x7B},
    {"ADCI",o_Immediate,0x7C},
    {"SDBI",o_Immediate,0x7D},
    {"SHLC",o_None,     0x7E},
    {"RSHL",o_None,     0x7E}, // duplicate opcode
    {"SMBI",o_Immediate,0x7F},
    {"GLO", o_Register, 0x80},
    {"GHI", o_Register, 0x90},
    {"PLO", o_Register, 0xA0},
    {"PHI", o_Register, 0xB0},
    {"LBR", o_LBranch,  0xC0},
    {"LBQ", o_LBranch,  0xC1},
    {"LBZ", o_LBranch,  0xC2},
    {"LBDF",o_LBranch,  0xC3},
    {"NOP", o_None,     0xC4},
    {"LSNQ",o_None,     0xC5},
    {"LSNZ",o_None,     0xC6},
    {"LSNF",o_None,     0xC7},
    {"LSKP",o_None,     0xC8},
    {"NLBR",o_LBranch,  0xC8}, // duplicate opcode
    {"LBNQ",o_LBranch,  0xC9},
    {"LBNZ",o_LBranch,  0xCA},
    {"LBNF",o_LBranch,  0xCB},
    {"LSIE",o_None,     0xCC},
    {"LSQ", o_None,     0xCD},
    {"LSZ", o_None,     0xCE},
    {"LSDF",o_None,     0xCF},
    {"SEP", o_Register, 0xD0},
    {"SEX", o_Register, 0xE0},
    {"LDX", o_None,     0xF0},
    {"OR",  o_None,     0xF1},
    {"AND", o_None,     0xF2},
    {"XOR", o_None,     0xF3},
    {"ADD", o_None,     0xF4},
    {"SD",  o_None,     0xF5},
    {"SHR", o_None,     0xF6},
    {"SM",  o_None,     0xF7},
    {"LDI", o_Immediate,0xF8},
    {"ORI", o_Immediate,0xF9},
    {"ANI", o_Immediate,0xFA},
    {"XRI", o_Immediate,0xFB},
    {"ADI", o_Immediate,0xFC},
    {"SDI", o_Immediate,0xFD},
    {"SHL", o_None,     0xFE},
    {"SMI", o_Immediate,0xFF},

    {"",    o_Illegal,  0}
};


// --------------------------------------------------------------


int Get_1802_Reg(void)
{
    Str255  word;
    int     token;
    char    *oldLine;

    oldLine = linePtr;
    token = GetWord(word);

    if (word[0]=='R')
    {
        // R0-R9
        if ('0'<=word[1] && word[1]<='9' && word[2]==0)
            return word[1] - '0';
        // RA-RF
        if ('A'<=word[1] && word[1]<='F' && word[2]==0)
            return word[1] - 'A' + 10;
        // R10-R15
        if (word[1]=='1' && '0'<=word[2] && word[2]<='5' && word[3]==0)
            return word[2] - '0' + 10;
    }

    // otherwise evaluate an expression
    linePtr = oldLine;
    return Eval();
}


int RCA1802_DoCPUOpcode(int typ, int parm)
{
    int     val;
//  Str255  word;
//  char    *oldLine;
//  int     token;

    switch(typ)
    {

        case o_None:
            InstrB(parm);
            break;

        case o_Register:
            val = Get_1802_Reg();
            if (val < 0 || val > 15)
                IllegalOperand();
            else if (val == 0 && parm == 0x00)
                IllegalOperand();   // don't allow LDN R0
            else
                InstrB(parm+val);
            break;

        case o_Immediate:
            val = EvalByte();
            InstrBB(parm,val);
            break;

        case o_Branch:
            val = Eval();
            // branch must go to same page as second byte of instruction
            if (((locPtr + 1) & 0xFF00) != (val & 0xFF00))
                Error("Branch out of range");
            InstrBB(parm,val);
            break;

        case o_LBranch:
            val = Eval();
            InstrBW(parm,val);
            break;

        case o_INPOUT:
            val = Eval();
            if (val < 1 || val > 7)
                IllegalOperand();
            else
                InstrB(parm+val);
            break;

        default:
            return 0;
            break;
    }
    return 1;
}


void Asm1802Init(void)
{
    char *p;

    p = AddAsm(versionName, &RCA1802_DoCPUOpcode, NULL, NULL);
    AddCPU(p, "1802", 0, BIG_END, ADDR_16, LIST_24, 8, 0, RCA1802_opcdTab);
}