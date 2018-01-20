// asm6805.c - copyright 1998-2007 Bruce Tomlin

#define versionName "6805 assembler"
#include "asmx.h"

enum
{
    o_Inherent,     // implied instructions
    o_Relative,     // branch instructions
    o_Bit,          // BCLR/BSET
    o_BRelative,    // BRSET/BRCLR
    o_Logical,      // instructions with multiple addressing modes
    o_Arith,        // arithmetic instructions with multiple addressing modes
    o_Store,        // STA/STX/JMP/JSR - same as o_Arith except no immediate allowed

    o_Inh08,        // 68HCS08 inherent instructions
    o_Rel08,        // 68HCS08 branch instructions and DBNZA/DBNZX
    o_AIS_AIX,      // 68HCS08 AIS and AIX instructions
    o_LDHX,         // 68HCS08 LDHX, STHX, CPHX instructions
    o_CBEQA,        // 68HCS08 CBEQA, CBEQX instructions
    o_CBEQ,         // 68HCS08 CBEQ, DBNZ instructions
    o_MOV,          // 68HCS08 MOV instruction

//  o_Foo = o_LabelOp,
};

enum cputype
{
    CPU_6805,
    CPU_68HCS08
};

struct OpcdRec M6805_opcdTab[] =
{

    {"NEGA",   o_Inherent, 0x40},
    {"COMA",   o_Inherent, 0x43},
    {"LSRA",   o_Inherent, 0x44},
    {"RORA",   o_Inherent, 0x46},
    {"ASRA",   o_Inherent, 0x47},
    {"ASLA",   o_Inherent, 0x48},
    {"LSLA",   o_Inherent, 0x48},
    {"ROLA",   o_Inherent, 0x49},
    {"DECA",   o_Inherent, 0x4A},
    {"INCA",   o_Inherent, 0x4C},
    {"TSTA",   o_Inherent, 0x4D},
    {"CLRA",   o_Inherent, 0x4F},

    {"NEGX",   o_Inherent, 0x50},
    {"COMX",   o_Inherent, 0x53},
    {"LSRX",   o_Inherent, 0x54},
    {"RORX",   o_Inherent, 0x56},
    {"ASRX",   o_Inherent, 0x57},
    {"ASLX",   o_Inherent, 0x58},
    {"LSLX",   o_Inherent, 0x58},
    {"ROLX",   o_Inherent, 0x59},
    {"DECX",   o_Inherent, 0x5A},
    {"INCX",   o_Inherent, 0x5C},
    {"TSTX",   o_Inherent, 0x5D},
    {"CLRX",   o_Inherent, 0x5F},

    {"MUL",   o_Inherent, 0x42},
    {"RTI",   o_Inherent, 0x80},
    {"RTS",   o_Inherent, 0x81},
    {"SWI",   o_Inherent, 0x83},
    {"STOP",  o_Inherent, 0x8E},
    {"WAIT",  o_Inherent, 0x8F},
    {"TAX",   o_Inherent, 0x97},
    {"CLC",   o_Inherent, 0x98},
    {"SEC",   o_Inherent, 0x99},
    {"CLI",   o_Inherent, 0x9A},
    {"SEI",   o_Inherent, 0x9B},
    {"RSP",   o_Inherent, 0x9C},
    {"NOP",   o_Inherent, 0x9D},
    {"TXA",   o_Inherent, 0x9F},

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
    {"BHCC",  o_Relative, 0x28},
    {"BHCS",  o_Relative, 0x29},
    {"BPL",   o_Relative, 0x2A},
    {"BMI",   o_Relative, 0x2B},
    {"BMC",   o_Relative, 0x2C},
    {"BMS",   o_Relative, 0x2D},
    {"BIL",   o_Relative, 0x2E},
    {"BIH",   o_Relative, 0x2F},

    {"BSR",   o_Relative, 0xAD},

    {"NEG",   o_Logical,  0x00}, // o_Logical: direct = $30; ix1 = $60, idx = $70
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
    {"CLR",   o_Logical,  0x0F},


    {"SUB",   o_Arith,    0x00}, // o_Arith: immediate = $80, direct = $90, ix2 = $A0
    {"CMP",   o_Arith,    0x01}, //           ix1 = $E0, extended = $F0
    {"SBC",   o_Arith,    0x02},
    {"CPX",   o_Arith,    0x03},
    {"AND",   o_Arith,    0x04},
    {"BIT",   o_Arith,    0x05},
    {"LDA",   o_Arith,    0x06},
    {"STA",   o_Store,    0x07},
    {"EOR",   o_Arith,    0x08},
    {"ADC",   o_Arith,    0x09},
    {"ORA",   o_Arith,    0x0A},
    {"ADD",   o_Arith,    0x0B},
    {"JMP",   o_Store,    0x0C},
    {"JSR",   o_Store,    0x0D},
    {"LDX",   o_Arith,    0x0E},
    {"STX",   o_Store,    0x0F},

    {"BSET",  o_Bit,      0x10},
    {"BCLR",  o_Bit,      0x11},
    {"BRSET", o_BRelative,0x00},
    {"BRCLR", o_BRelative,0x01},

    // 68HCS08 opcodes

    {"DIV",   o_Inh08,    0x52},
    {"NSA",   o_Inh08,    0x62},
    {"DAA",   o_Inh08,    0x72},
    {"BGND",  o_Inh08,    0x82},
    {"TAP",   o_Inh08,    0x84},
    {"TPA",   o_Inh08,    0x85},
    {"PULA",  o_Inh08,    0x86},
    {"PSHA",  o_Inh08,    0x87},
    {"PULX",  o_Inh08,    0x88},
    {"PSHX",  o_Inh08,    0x89},
    {"PULH",  o_Inh08,    0x8A},
    {"PSHH",  o_Inh08,    0x8B},
    {"CLRH",  o_Inh08,    0x8C},
    {"TXS",   o_Inh08,    0x94},
    {"TSX",   o_Inh08,    0x95},

    {"BGE",   o_Rel08,    0x90},
    {"BLT",   o_Rel08,    0x91},
    {"BGT",   o_Rel08,    0x92},
    {"BLE",   o_Rel08,    0x93},
    {"DBNZA", o_Rel08,    0x4B},
    {"DBNZX", o_Rel08,    0x5B},

    {"AIS",   o_AIS_AIX,  0xA7},
    {"AIX",   o_AIS_AIX,  0xAF},

    {"LDHX",  o_LDHX,     0x0E},
    {"STHX",  o_LDHX,     0x0F},
    {"CPHX",  o_LDHX,     0x03},
/*
45 nnnn   LDHX #imm
55 nn     LDHX dir
32 nnnn   LDHX ext
9EAE      LDHX ,X
9EBE nnnn LDHX nnnn,X
9ECE nn   LDHX nn,X
9EFE nn   LDHX nn,SP

35 nn     STHX dir
96 nnnn   STHX ext
9EFF nn   STHX nn,SP

3E nnnn   CPHX #imm
65 nnnn   CPHX nnnn,X
75 nn     CPHX nn,X
9EF3 nn   CPHX nn,SP
*/
    {"CBEQA", o_CBEQA, 0x41},
    {"CBEQX", o_CBEQA, 0x51},

    {"CBEQ",  o_CBEQ, 0x01},
    {"DBNZ",  o_CBEQ, 0x0B},

    {"MOV",   o_MOV,  0},

    {"",      o_Illegal, 0}
};


// --------------------------------------------------------------


int M6805_DoCPUOpcode(int typ, int parm)
{
    int     val,val2,val3;
    Str255  word;
    char    *oldLine;
    int     token;
    char    force;
    char    reg;

    switch(typ)
    {
        case o_Inh08:       // 68HCS08 inherent instructions
            if (curCPU != CPU_68HCS08) return 0;
        case o_Inherent:
            InstrB(parm);
            break;

        case o_Rel08:       // 68HCS08 branch instructions and DBNZA/DBNZX
            if (curCPU != CPU_68HCS08) return 0;
        case o_Relative:
            val = EvalBranch(2);
            InstrBB(parm,val);
            break;

        case o_Logical:
            oldLine = linePtr;
            token = GetWord(word);  // look for ",X"
            if (token == ',')
            {
                if (Expect("X")) break;
                InstrB(parm + 0x70);
                break;
            }

            linePtr = oldLine;
            val = Eval();

            oldLine = linePtr;
            token = GetWord(word);  // look for ",X"
            if (token == 0)
                InstrBB(parm + 0x30, val);  // no ",X", so must be direct
            else if (token == ',')
            {
                switch((reg = GetReg("X SP")))
                {
                    default:
                    case reg_None:
                        IllegalOperand();
                    case reg_EOL: // EOL
                        break;

                    case 1:
                        parm = parm + 0x9E00;
                    case 0:
                        if (evalKnown && val == 0 && parm < 256) // 0,X
                             InstrB(parm + 0x70);
                        else InstrXB(parm + 0x60, val); // ix1,X / sp1,SP
                }
            }
            else
            {
                linePtr = oldLine;
                Comma();
            }
            break;

        case o_Arith:
        case o_Store:
            oldLine = linePtr;
            token = GetWord(word);
            if (token == '#')   // immediate
            {
                if (typ == o_Store)
                    Error("Invalid addressing mode");
                else
                {
                    val = Eval();
                    InstrBB(parm + 0xA0, val);
                }
            }
            else if (token == ',') // ,X
            {
                if (Expect("X")) break;
                InstrB(parm + 0xF0);
                break;
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
                if (token == 0) // dir or ext
                {
                    if (((force != '>' && evalKnown && (val & 0xFF00) >> 8 == 0) || force == '<'))
                    {
                        CheckByte(val);
                        InstrBB(parm + 0xB0, val);  // <$xx
                    }
                    else
                        InstrBW(parm + 0xC0, val);   // >$xxxx
                }
                else if (token == ',') // ix1,X or ix2,X
                {
                    switch((reg = GetReg("X SP")))
                    {
                        default:
                        case reg_None:
                            IllegalOperand();
                        case reg_EOL: // EOL
                            break;

                        case 1:
                            if (parm == 0x0C || parm == 0x0D) // JMP / JSR
                            {
                                BadMode();
                                break;
                            }
                            parm = parm + 0x9E00;
                        case 0:
                            if (evalKnown && val == 0 && parm < 256) // 0,X
                                 InstrB(parm + 0xF0);
                            else if (((force != '>' && evalKnown && (val & 0xFF00) >> 8 == 0) || force == '<'))
                            {
                                 CheckByte(val);
                                 InstrXB(parm + 0xE0, val); // ix1,X / sp1,SP
                            }
                            else InstrXW(parm + 0xD0, val); // ix2,X / sp2,SP
                    }
                    break;
                }
                else
                {
                    linePtr = oldLine;
                    Comma();
                }
            }
            break;

        case o_Bit:
            val = Eval();   // bit number
            if (val < 0 || val > 7)
                Error("Bit number must be 0 - 7");

            oldLine = linePtr;  // eat optional comma after bit number
            if (GetWord(word) != ',')
                linePtr = oldLine;

            val2 = Eval();      // direct page address or offset
            reg = 0;

            InstrBB(parm + val * 2, val2);
            break;

        case o_BRelative:
            val = Eval();   // bit number
            if (val < 0 || val > 7)
                Error("Bit number must be 0 - 7");

            oldLine = linePtr;  // eat optional comma after bit number
            if (GetWord(word) != ',')
                linePtr = oldLine;

            val2 = Eval();      // direct page address or offset
            reg = 0;

            oldLine = linePtr;  // eat optional comma after direct page address
            if (GetWord(word) != ',')
                linePtr = oldLine;

            val3 = EvalBranch(2);  // offset

            InstrBBB(parm + val * 2, val2, val3);
            break;

        case o_AIS_AIX:      // 68HCS08 AIS and AIX instructions
            if (Expect("#")) break; // immediate only
            val = Eval();
            CheckStrictByte(val);
            InstrBB(parm, val);
            break;

        case o_LDHX:        // 68HCS08 LDHX, STHX, CPHX instructions
            oldLine = linePtr;
            token = GetWord(word);
            if (token=='#') // 45 LDHX #imm / 65 CPHX #imm
            {
                if (parm == 0x0F)
                    BadMode();
                else
                {
                    val = Eval();
                    InstrBW(0x45 + (parm & 0x01)*0x20,val);
                    break;
                }
            }
            else if (token == ',') // 9EAE LDHX ,X
            {
                if (parm != 0x0E)
                    BadMode();
                else
                {
                    if (Expect("X")) break;
                    InstrX(0x9EAE);
                    break;
                }
            }
            else
            {
                force = 0;

                if (token == '<' || token == '>')
                    force = token;
                else
                    linePtr = oldLine;

                val = Eval();

                oldLine = linePtr;
                token = GetWord(word);
                if (token == 0) // dir or ext
                {
//    {"LDHX",  o_LDHX,     0x0E},
//55 nn     LDHX dir
//32 nnnn   LDHX ext
//    {"STHX",  o_LDHX,     0x0F},
//35 nn     STHX dir
//96 nnnn   STHX ext
//    {"CPHX",  o_LDHX,     0x03},
//75 nn     CPHX dir
//3E nnnn   CPHX ext
                        if (((force != '>' && evalKnown && (val & 0xFF00) >> 8 == 0) || force == '<'))
                        {
                             CheckByte(val);
                             switch(parm)
                             {
                                 case 0x0E: parm = 0x55; break; // LDHX
                                 case 0x0F: parm = 0x35; break; // STHX
                                 default:   parm = 0x75; break; // CPHX
                             }
                             InstrBB(parm, val); // ix1,X / sp1,SP
                        }
                        else
                        {
                             switch(parm)
                             {
                                 case 0x0E: parm = 0x32; break; // LDHX
                                 case 0x0F: parm = 0x96; break; // STHX
                                 default:   parm = 0x3E; break; // CPHX
                             }
                             InstrBW(parm, val); // ix2,X / sp2,SP
                        }
                }
                else
                {
                    linePtr = oldLine;
                    if (Comma()) break;
//9EFE nn   LDHX nn,SP
//9EFF nn   STHX nn,SP
//9EF3 nn   CPHX nn,SP
//9ECE nn   LDHX nn,X
//9EBE nnnn LDHX nnnn,X
                    switch((reg = GetReg("X SP")))
                    {
                        default:
                        case reg_None:
                            IllegalOperand();
                        case reg_EOL: // EOL
                            break;

                        case 0: // X
                            if (parm != 0x0E) // LDHX
                            {
                                BadMode();
                                break;
                            }
                            if (((force != '>' && evalKnown && (val & 0xFF00) >> 8 == 0) || force == '<'))
                            {
                                 CheckByte(val);
                                 InstrXB(parm + 0x9EC0, val); // ix1,X
                            }
                            else InstrXW(parm + 0x9EB0, val); // ix2,X
                            break;

                        case 1: // SP
                            CheckByte(val);
                            InstrXB(parm + 0x9EF0, val); // sp1,SP
                            break;
                    }
                }
            }
            break;

        case o_CBEQA:       // 68HCS08 CBEQA, CBEQX instructions
            if (Expect("#")) break; // immediate only
            val = EvalByte();
            if (Comma()) break;
            val2 = EvalBranch(3);
            InstrBBB(parm,val,val2);
            break;

        case o_CBEQ:        // 68HCS08 CBEQ, DBNZ instructions
            oldLine = linePtr;
            if (GetWord(word) == ',')
            {
                if (Expect("X")) break;
                if (parm == 0x01 && Expect("+")) break;
                if (Comma()) break;
                val = EvalBranch(2);
                InstrBB(parm + 0x70,val);
            }
            else
            {
                linePtr = oldLine;
                val = EvalByte();
                if (Comma()) break;
                oldLine = linePtr;
                switch(reg=(GetReg("X SP")))
                {
                    case 0: // X
                        if (parm == 0x01 && GetWord(word) != '+')
                        {
                    case reg_None:
                            linePtr = oldLine;
                            val2 = EvalBranch(3);
                            InstrBBB(parm + 0x30,val,val2);
                            break;
                        }
                    case 1: // SP
                        {
                            if (reg == 1) parm = parm + 0x9E00;
                            if (Comma()) break;
                            if (reg == 1) val2 = EvalBranch(4);
                                     else val2 = EvalBranch(3);
                            InstrXBB(parm + 0x60,val,val2);
                            break;
                        }

                    default:
                        IllegalOperand();
                    case reg_EOL: // EOL
                        break;
                }
            }
            break;

        case o_MOV:         // 68HCS08 MOV instruction
            oldLine = linePtr;
            switch (GetWord(word))
            {
                case ',':
                    if (Expect("X")) break;
                    if (Expect("+")) break;
                    if (Comma()) break;
                    val = EvalByte();
                    InstrBB(0x7E,val); // MOV ,X+,dir
                    break;

                case '#':
                    val = EvalByte();
                    if (Comma()) break;
                    val2 = EvalByte();
                    InstrBBB(0x6E,val,val2); // MOV imm,dir
                    break;

                default:
                    linePtr = oldLine;
                    val = EvalByte();
                    if (Comma()) break;
                    oldLine = linePtr;
                    if (GetReg("X")==0 && (GetReg("+")==0))
                        InstrBB(0x5E,val); // 5E MOV dir,X+
                    else
                    {
                        linePtr = oldLine;
                        val2 = EvalByte();
                        InstrBBB(0x4E,val,val2); // 4E MOV dir,dir
                    }
                    break;
            }
            break;

        default:
            return 0;
            break;
    }
    return 1;
}


void Asm6805Init(void)
{
    char *p;

    p = AddAsm(versionName, &M6805_DoCPUOpcode, NULL, NULL);
    AddCPU(p, "6805",    CPU_6805,    BIG_END, ADDR_16, LIST_24, 8, 0, M6805_opcdTab);
    AddCPU(p, "68HCS08", CPU_68HCS08, BIG_END, ADDR_16, LIST_24, 8, 0, M6805_opcdTab);
}
