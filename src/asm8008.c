// asm8085.c - copyright 1998-2007 Bruce Tomlin
// HRJ rewritten for 8008 1972 mnemonics as asm8008.c

#define versionName "8008 assembler"
#include "asmx.h"

enum
{
    CPU_8008
};

#define I_8008  0x100

enum instrType
{
    o_None,         // No operands

    o_Immediate,    // one-byte immediate operand
    o_LImmediate,   // two-byte immediate operand (mostly JMPs)
    o_RST,          // RST instruction
// rest are from INtel 8085
    o_MOV,          // MOV r,r opcode
    o_In,           // IN instructions
    o_Out,          // OUT instructions
    o_Arith,        // Arithmetic instructions
    o_PushPop,      // PUSH and POP instructions
    o_MVI,          // MVI instruction
    o_LXI,          // LXI instruciton
    o_INR,          // INR/DCR instructions
    o_INX,          // INX/DCX/DAD instructions
    o_STAX          // STAX/LDAX instructions

//  o_Foo = o_LabelOp,
};

const char I8008_regs1[]      = "A B C D E H L M";
const char I8008_regs2[]      = "B D H SP";

struct OpcdRec I8008_opcdTab[] =
{

    {"RLC", o_None, 0x02}, //rotate
    {"RRC", o_None, 0x0A},
    {"RAL", o_None, 0x12},
    {"RAR", o_None, 0x1A},
// 32 3A 42 4a not defined

    {"RET", o_None, 0x07},
//many other returns X7, XF

    {"RFZ", o_None, 0x0B},// return
    {"RZ",  o_None, 0x2B},
    {"RFC", o_None, 0x03},
    {"RC",  o_None, 0x23},
    {"RFP", o_None, 0x1B},
    {"RP",  o_None, 0x3B},
    {"RFS", o_None, 0x13},
    {"RS",  o_None, 0x33},

    {"RTZ",  o_None, 0x2B}, //alternate
    {"RTC",  o_None, 0x23},
    {"RTP",  o_None, 0x3B},
    {"RTS",  o_None, 0x33},



//    INA DCA are not accepted but 00, 10 are Intel-accepted halts
    {"INB", o_None, 0x08}, //increments
    {"DCB", o_None, 0x09},
    {"INC", o_None, 0x10},
    {"DCC", o_None, 0x11},
    {"IND", o_None, 0x18},
    {"DCD", o_None, 0x19},
    {"INE", o_None, 0x20},
    {"DCE", o_None, 0x21},
    {"INH", o_None, 0x28},
    {"DCH", o_None, 0x29},
    {"INL", o_None, 0x30},
    {"DCL", o_None, 0x31},
// INM DCM are not defined

    {"ADA",  o_None, 0x80}, // ADD
    {"ADB",  o_None, 0x81},
    {"ADC",  o_None, 0x82},
    {"ADD",  o_None, 0x83},
    {"ADE",  o_None, 0x84},
    {"ADH",  o_None, 0x85},
    {"ADL",  o_None, 0x86},
    {"ADM",  o_None, 0x87},
    {"ACA",  o_None, 0x88}, //add w carry
    {"ACB",  o_None, 0x89},
    {"ACC",  o_None, 0x8A},
    {"ACD",  o_None, 0x8B},
    {"ACE",  o_None, 0x8C},
    {"ACH",  o_None, 0x8D},
    {"ACL",  o_None, 0x8E},
    {"ACM",  o_None, 0x8F},

    {"SUA",  o_None, 0x90}, // Sub
    {"SUB",  o_None, 0x91},
    {"SUC",  o_None, 0x92},
    {"SUD",  o_None, 0x93},
    {"SUE",  o_None, 0x94},
    {"SUH",  o_None, 0x95},
    {"SUL",  o_None, 0x96},
    {"SUM",  o_None, 0x97},
    {"SBA",  o_None, 0x98}, //SUB with borrow
    {"SBB",  o_None, 0x99},
    {"SBC",  o_None, 0x9A},
    {"SBD",  o_None, 0x9B},
    {"SBE",  o_None, 0x9C},
    {"SBH",  o_None, 0x9D},
    {"SBL",  o_None, 0x9E},
    {"SBM",  o_None, 0x9F},

    {"NDA",  o_None, 0xA0}, // AND
    {"NDB",  o_None, 0xA1},
    {"NDC",  o_None, 0xA2},
    {"NDD",  o_None, 0xA3},
    {"NDE",  o_None, 0xA4},
    {"NDH",  o_None, 0xA5},
    {"NDL",  o_None, 0xA6},
    {"NDM",  o_None, 0xA7},
    {"XRA",  o_None, 0xA8}, //XOR
    {"XRB",  o_None, 0xA9},
    {"XRC",  o_None, 0xAA},
    {"XRD",  o_None, 0xAB},
    {"XRE",  o_None, 0xAC},
    {"XRH",  o_None, 0xAD},
    {"XRL",  o_None, 0xAE},
    {"XRM",  o_None, 0xAF},

    {"ORA",  o_None, 0xB0}, // OR
    {"ORB",  o_None, 0xB1},
    {"ORC",  o_None, 0xB2},
    {"ORD",  o_None, 0xB3},
    {"ORE",  o_None, 0xB4},
    {"ORH",  o_None, 0xB5},
    {"ORL",  o_None, 0xB6},
    {"ORM",  o_None, 0xB7},
    {"CPA",  o_None, 0xB8}, // compare
    {"CPB",  o_None, 0xB9},
    {"CPC",  o_None, 0xBA},
    {"CPD",  o_None, 0xBB},
    {"CPE",  o_None, 0xBC},
    {"CPH",  o_None, 0xBD},
    {"CPL",  o_None, 0xBE},
    {"CPM",  o_None, 0xBF},

    {"NOP",  o_None, 0xC0}, // LAA is NOP
    {"LAB",  o_None, 0xC1}, // move registers
    {"LAC",  o_None, 0xC2},
    {"LAD",  o_None, 0xC3},
    {"LAE",  o_None, 0xC4},
    {"LAH",  o_None, 0xC5},
    {"LAL",  o_None, 0xC6},
    {"LAM",  o_None, 0xC7},
    {"LBA",  o_None, 0xC8},
    {"LBB",  o_None, 0xC9},
    {"LBC",  o_None, 0xCA},
    {"LBD",  o_None, 0xCB},
    {"LBE",  o_None, 0xCC},
    {"LBH",  o_None, 0xCD},
    {"LBL",  o_None, 0xCE},
    {"LBM",  o_None, 0xCF},

    {"LCA",  o_None, 0xD0},
    {"LCB",  o_None, 0xD1},
    {"LCC",  o_None, 0xD2},
    {"LCD",  o_None, 0xD3},
    {"LCE",  o_None, 0xD4},
    {"LCH",  o_None, 0xD5},
    {"LCL",  o_None, 0xD6},
    {"LCM",  o_None, 0xD7},
    {"LDA",  o_None, 0xD8},
    {"LDB",  o_None, 0xD9},
    {"LDC",  o_None, 0xDA},
    {"LDD",  o_None, 0xDB},
    {"LDE",  o_None, 0xDC},
    {"LDH",  o_None, 0xDD},
    {"LDL",  o_None, 0xDE},
    {"LDM",  o_None, 0xDF},

    {"LEA",  o_None, 0xE0},
    {"LEB",  o_None, 0xE1},
    {"LEC",  o_None, 0xE2},
    {"LED",  o_None, 0xE3},
    {"LEE",  o_None, 0xE4},
    {"LEH",  o_None, 0xE5},
    {"LEL",  o_None, 0xE6},
    {"LEM",  o_None, 0xE7},
    {"LHA",  o_None, 0xE8},
    {"LHB",  o_None, 0xE9},
    {"LHC",  o_None, 0xEA},
    {"LHD",  o_None, 0xEB},
    {"LHE",  o_None, 0xEC},
    {"LHH",  o_None, 0xED},
    {"LHL",  o_None, 0xEE},
    {"LHM",  o_None, 0xEF},

    {"LLA",  o_None, 0xF0},
    {"LLB",  o_None, 0xF1},
    {"LLC",  o_None, 0xF2},
    {"LLD",  o_None, 0xF3},
    {"LLE",  o_None, 0xF4},
    {"LLH",  o_None, 0xF5},
    {"LLL",  o_None, 0xF6},
    {"LLM",  o_None, 0xF7},
    {"LMA",  o_None, 0xF8},
    {"LMB",  o_None, 0xF9},
    {"LMC",  o_None, 0xFA},
    {"LMD",  o_None, 0xFB},
    {"LME",  o_None, 0xFC},
    {"LMH",  o_None, 0xFD},
    {"HLT",  o_None, 0xFF},  //    LMM is halt

    {"ADI", o_Immediate, 0x04}, // immediate logic, mathc
    {"ACI", o_Immediate, 0x0C},
    {"SUI", o_Immediate, 0x14},
    {"SBI", o_Immediate, 0x1C},
    {"NDI", o_Immediate, 0x24},
    {"XRI", o_Immediate, 0x2C},
    {"ORI", o_Immediate, 0x34},
    {"CPI", o_Immediate, 0x3C},

    {"LAI", o_Immediate, 0x06}, // load immediate
    {"LBI", o_Immediate, 0x0E},
    {"LCI", o_Immediate, 0x16},
    {"LDI", o_Immediate, 0x1E},
    {"LEI", o_Immediate, 0x26},
    {"LHI", o_Immediate, 0x2E},
    {"LLI", o_Immediate, 0x36},
    {"LMI", o_Immediate, 0x3E},

    {"JMP", o_LImmediate, 0x44},  //many jumps

    {"JFC", o_LImmediate, 0x40}, // jump on conditions
    {"JFZ", o_LImmediate, 0x48},
    {"JFS", o_LImmediate, 0x50},
    {"JFP", o_LImmediate, 0x58},
    {"JC",  o_LImmediate, 0x60},
    {"JZ",  o_LImmediate, 0x68},
    {"JS",  o_LImmediate, 0x70},
    {"JP",  o_LImmediate, 0x78},
    {"JTC", o_LImmediate, 0x60}, //alternate
    {"JTZ", o_LImmediate, 0x68},
    {"JTS", o_LImmediate, 0x70},
    {"JTP", o_LImmediate, 0x78},

    {"CAL", o_LImmediate, 0x46}, //many CALLS

    {"CFC", o_LImmediate, 0x42}, // call on conditions
    {"CFZ", o_LImmediate, 0x4A},
    {"CFS", o_LImmediate, 0x52},
    {"CFP", o_LImmediate, 0x5A},
    {"CC",  o_LImmediate, 0x62},
    {"CZ",  o_LImmediate, 0x6A},
    {"CS",  o_LImmediate, 0x72},
    {"CP",  o_LImmediate, 0x7A},
    {"CTC", o_LImmediate, 0x62}, //alternate
    {"CTZ", o_LImmediate, 0x6A},
    {"CTS", o_LImmediate, 0x72},
    {"CTP", o_LImmediate, 0x7A},

    {"INP", o_In,      0}, //In, Out, Restarts
    {"OUT", o_Out,     0},
    {"RST", o_RST,     0},


    {"",    o_Illegal,  0}
};


// --------------------------------------------------------------


int I8008_DoCPUOpcode(int typ, int parm)
{
    int     val;

    switch(typ)
    {
        case o_None:
            //if ((parm & I_8008)  && curCPU == CPU_8008)  return 0;

            InstrB (parm & 255);
            break;

        case o_Immediate:
            // if ((parm & I_8085U) && curCPU != CPU_8085U) return 0;

            val = Eval();
            InstrBB(parm & 0xFF,val);
            break;

        case o_LImmediate:
            // if ((parm & I_8085U) && curCPU != CPU_8085U) return 0;

            val = Eval();
            InstrBW(parm,val);
            break;

        case o_In:
            val = Eval();
            if (0 <= val && val <= 7)
                InstrB(0x41 + val*2);
            else IllegalOperand();
            break;

        case o_Out:
            val = Eval();
            if (8 <= val && val <= 31)
                InstrB(0x51 + (val-8)*2);
            else IllegalOperand();
            break;


         case o_RST:  //restart to 0, 8, 10, 18,.....
            val = Eval();
            if (0 <= val && val <= 7)
                InstrB(0x05 + val*8);
            else IllegalOperand();
            break;

        default:
            return 0;
            break;
    }
    return 1;
}


void Asm8008Init(void)
{
    char *p;

    p = AddAsm(versionName, &I8008_DoCPUOpcode, NULL, NULL);
    AddCPU(p, "8008",  CPU_8008,  LITTLE_END, ADDR_16, LIST_24, 8, 0, I8008_opcdTab);
}
