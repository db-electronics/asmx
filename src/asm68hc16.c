// asm68HC16.c - copyright 1998-2007 Bruce Tomlin

#define versionName "68HC16 assembler"
#include "asmx.h"

enum
{
    o_Inherent,     // implied instructions
    o_Branch,       // short relative branch instructions
    o_LBranch,      // long relative branch instructions
    o_ImmediateW,   // immediate word instructions (ORP and ANDP)
    o_AIX,          // AIX/AIY/AIZ/AIS instructions
    o_MAC,          // MAC/RMAC instructions
    o_PSHM,         // PSHM instruction
    o_PULM,         // PULM instruction
    o_MOVB,         // MOVB/MOVW instructions
    o_Logical,      // byte-data logical instructions
    o_LogicalW,     // word-data logical instructions
    o_STE,          // STE instruction
    o_ADDE,         // ADDE instruction
    o_ArithE,       // arithmetic operations on register E
    o_BCLRW,        // BCLRW/BSETW instructions
    o_BCLR,         // BCLR/BSET instructions
    o_BRCLR,        // BRCLR/BRSET instructions
    o_STX,          // STX/STY/STZ/STS instructions
    o_LDX,          // LDX/LDY/LDZ/LDS instructions
    o_ArithX,       // arithmetic operations on X register
    o_JMP,          // JMP/JSR instructions
    o_STD,          // STD instruction
    o_StoreAB,      // STAA/STAB instructions
    o_ADDD,         // ADDD instruction
    o_ArithW,       // word-data arithmetic instructions
    o_Arith,        // byte-data arithmetic instructions

//  o_Foo = o_LabelOp,
};

struct OpcdRec M68HC16_opcdTab[] =
{
    {"ABA",   o_Inherent, 0x370B},
    {"ABX",   o_Inherent, 0x374F},
    {"ABY",   o_Inherent, 0x375F},
    {"ABZ",   o_Inherent, 0x376F},
    {"ACE",   o_Inherent, 0x3722},
    {"ACED",  o_Inherent, 0x3723},
    {"ADE",   o_Inherent, 0x2778},
    {"ADX",   o_Inherent, 0x37CD},
    {"ADY",   o_Inherent, 0x37DD},
    {"ADZ",   o_Inherent, 0x37ED},
    {"AEX",   o_Inherent, 0x374D},
    {"AEY",   o_Inherent, 0x375D},
    {"AEZ",   o_Inherent, 0x376D},
    {"ASLA",  o_Inherent, 0x3704},
    {"ASLB",  o_Inherent, 0x3714},
    {"ASLD",  o_Inherent, 0x27F4},
    {"ASLE",  o_Inherent, 0x2774},
    {"ASLM",  o_Inherent, 0x27B6},
    {"ASRA",  o_Inherent, 0x370D},
    {"ASRB",  o_Inherent, 0x371D},
    {"ASRD",  o_Inherent, 0x27FD},
    {"ASRE",  o_Inherent, 0x277D},
    {"ASRM",  o_Inherent, 0x27BA},
    {"BGND",  o_Inherent, 0x37A6},
    {"CBA",   o_Inherent, 0x371B},
    {"CLRA",  o_Inherent, 0x3705},
    {"CLRB",  o_Inherent, 0x3715},
    {"CLRD",  o_Inherent, 0x27F5},
    {"CLRE",  o_Inherent, 0x2775},
    {"CLRM",  o_Inherent, 0x27B7},
    {"COMA",  o_Inherent, 0x3700},
    {"COMB",  o_Inherent, 0x3710},
    {"COMD",  o_Inherent, 0x27F0},
    {"COME",  o_Inherent, 0x2770},
    {"DAA",   o_Inherent, 0x3721},
    {"DECA",  o_Inherent, 0x3701},
    {"DECB",  o_Inherent, 0x3711},
    {"DECE",  o_Inherent, 0x2771},
    {"EDIV",  o_Inherent, 0x3728},
    {"EDIVS", o_Inherent, 0x3729},
    {"EMUL",  o_Inherent, 0x3725},
    {"EMULS", o_Inherent, 0x3726},
    {"FDIV",  o_Inherent, 0x372B},
    {"FMULS", o_Inherent, 0x3727},
    {"IDIV",  o_Inherent, 0x372A},
    {"INCA",  o_Inherent, 0x3703},
    {"INCB",  o_Inherent, 0x3713},
    {"INCE",  o_Inherent, 0x2773},
    {"LDHI",  o_Inherent, 0x27B0},
    {"LPSTOP",o_Inherent, 0x27F1},
    {"LSRA",  o_Inherent, 0x370F},
    {"LSRB",  o_Inherent, 0x371F},
    {"LSRD",  o_Inherent, 0x27FF},
    {"LSRE",  o_Inherent, 0x277F},
    {"MUL",   o_Inherent, 0x3724},
    {"NEGA",  o_Inherent, 0x3702},
    {"NEGB",  o_Inherent, 0x3712},
    {"NEGD",  o_Inherent, 0x27F2},
    {"NEGE",  o_Inherent, 0x2772},
    {"NOP",   o_Inherent, 0x27CC},
    {"PSHA",  o_Inherent, 0x3708},
    {"PSHB",  o_Inherent, 0x3718},
    {"PSHMAC",o_Inherent, 0x27B8},
    {"PULA",  o_Inherent, 0x3709},
    {"PULB",  o_Inherent, 0x3719},
    {"PULMAC",o_Inherent, 0x27B9},
    {"ROLA",  o_Inherent, 0x370C},
    {"ROLB",  o_Inherent, 0x371C},
    {"ROLD",  o_Inherent, 0x27FC},
    {"ROLE",  o_Inherent, 0x277C},
    {"RORA",  o_Inherent, 0x370E},
    {"RORB",  o_Inherent, 0x371E},
    {"RORD",  o_Inherent, 0x27FE},
    {"RORE",  o_Inherent, 0x277E},
    {"RTI",   o_Inherent, 0x2777},
    {"RTS",   o_Inherent, 0x27F7},
    {"SBA",   o_Inherent, 0x370A},
    {"SDE",   o_Inherent, 0x2779},
    {"SWI",   o_Inherent, 0x3720},
    {"SXT",   o_Inherent, 0x27F8},
    {"TAB",   o_Inherent, 0x3717},
    {"TAP",   o_Inherent, 0x37FD},
    {"TBA",   o_Inherent, 0x3707},
    {"TBEK",  o_Inherent, 0x27FA},
    {"TBSK",  o_Inherent, 0x379F},
    {"TBXK",  o_Inherent, 0x379C},
    {"TBYK",  o_Inherent, 0x379D},
    {"TBZK",  o_Inherent, 0x379E},
    {"TDE",   o_Inherent, 0x277B},
    {"TDMSK", o_Inherent, 0x372F},
    {"TDP",   o_Inherent, 0x372D},
    {"TED",   o_Inherent, 0x27FB},
    {"TEDM",  o_Inherent, 0x27B1},
    {"TEKB",  o_Inherent, 0x27BB},
    {"TEM",   o_Inherent, 0x27B2},
    {"TMER",  o_Inherent, 0x27B4},
    {"TMET",  o_Inherent, 0x27B5},
    {"TMXED", o_Inherent, 0x27B3},
    {"TPA",   o_Inherent, 0x37FC},
    {"TPD",   o_Inherent, 0x372C},
    {"TSKB",  o_Inherent, 0x37AF},
    {"TSTA",  o_Inherent, 0x3706},
    {"TSTB",  o_Inherent, 0x3716},
    {"TSTD",  o_Inherent, 0x27F6},
    {"TSTE",  o_Inherent, 0x2776},
    {"TSX",   o_Inherent, 0x27CF},
    {"TSY",   o_Inherent, 0x275F},
    {"TSZ",   o_Inherent, 0x276F},
    {"TXKB",  o_Inherent, 0x37AC},
    {"TXS",   o_Inherent, 0x374E},
    {"TXY",   o_Inherent, 0x275C},
    {"TXZ",   o_Inherent, 0x276C},
    {"TYKB",  o_Inherent, 0x37AD},
    {"TYS",   o_Inherent, 0x375E},
    {"TYX",   o_Inherent, 0x27CD},
    {"TYZ",   o_Inherent, 0x276D},
    {"TZKB",  o_Inherent, 0x37AE},
    {"TZS",   o_Inherent, 0x376E},
    {"TZX",   o_Inherent, 0x27CE},
    {"TZY",   o_Inherent, 0x275E},
    {"WAI",   o_Inherent, 0x27F3},
    {"XGAB",  o_Inherent, 0x371A},
    {"XGDE",  o_Inherent, 0x277A},
    {"XGDX",  o_Inherent, 0x37CC},
    {"XGDY",  o_Inherent, 0x37DC},
    {"XGDZ",  o_Inherent, 0x37EC},
    {"XGEX",  o_Inherent, 0x374C},
    {"XGEY",  o_Inherent, 0x375C},
    {"XGEZ",  o_Inherent, 0x376C},

    {"BCC",   o_Branch,   0xB4}, // aka BHS
    {"BCS",   o_Branch,   0xB5}, // aka BLO
    {"BEQ",   o_Branch,   0xB7},
    {"BGE",   o_Branch,   0xBC},
    {"BGT",   o_Branch,   0xBE},
    {"BHI",   o_Branch,   0xB2},
    {"BLE",   o_Branch,   0xBF},
    {"BLS",   o_Branch,   0xB3},
    {"BLT",   o_Branch,   0xBD},
    {"BMI",   o_Branch,   0xBB},
    {"BNE",   o_Branch,   0xB6},
    {"BPL",   o_Branch,   0xBA},
    {"BRA",   o_Branch,   0xB0},
    {"BRN",   o_Branch,   0xB1},
    {"BSR",   o_Branch,   0x36},
    {"BVC",   o_Branch,   0xB8},
    {"BVS",   o_Branch,   0xB9},

    {"LBCC",  o_LBranch,  0x3784},    // aka LBHS
    {"LBCS",  o_LBranch,  0x3785},    // aka LBLO
    {"LBEQ",  o_LBranch,  0x3787},
    {"LBEV",  o_LBranch,  0x3791},
    {"LBGE",  o_LBranch,  0x378C},
    {"LBGT",  o_LBranch,  0x378E},
    {"LBHI",  o_LBranch,  0x3782},
    {"LBLE",  o_LBranch,  0x378F},
    {"LBLS",  o_LBranch,  0x3783},
    {"LBLT",  o_LBranch,  0x378D},
    {"LBMI",  o_LBranch,  0x378B},
    {"LBMV",  o_LBranch,  0x3790},
    {"LBNE",  o_LBranch,  0x3786},
    {"LBPL",  o_LBranch,  0x378A},
    {"LBRA",  o_LBranch,  0x3780},
    {"LBRN",  o_LBranch,  0x3781},
    {"LBSR",  o_LBranch,  0x27F9},
    {"LBVC",  o_LBranch,  0x3788},
    {"LBVS",  o_LBranch,  0x3789},

    {"ANDP",  o_ImmediateW, 0x373A},
    {"ORP",   o_ImmediateW, 0x373B},

    {"AIS",   o_AIX,     0x3F},
    {"AIX",   o_AIX,     0x3C},
    {"AIY",   o_AIX,     0x3D},
    {"AIZ",   o_AIX,     0x3E},

    {"AIS",   o_AIX,     0x3F},
    {"AIX",   o_AIX,     0x3C},
    {"AIY",   o_AIX,     0x3D},
    {"AIZ",   o_AIX,     0x3E},

    {"MAC",   o_MAC,     0x7B},
    {"RMAC",  o_MAC,     0xFB},

    {"PSHM",  o_PSHM,    0x34},
    {"PULM",  o_PULM,    0x35},

    {"MOVB",  o_MOVB,    0x00},
    {"MOVW",  o_MOVB,    0x01},

    {"ASLW", o_LogicalW, 0x04},
    {"ASRW", o_LogicalW, 0x0D},
    {"CLRW", o_LogicalW, 0x05},
    {"COMW", o_LogicalW, 0x00},
    {"DECW", o_LogicalW, 0x01},
    {"INCW", o_LogicalW, 0x03},
    {"LSRW", o_LogicalW, 0x0F},
    {"NEGW", o_LogicalW, 0x02},
    {"ROLW", o_LogicalW, 0x0C},
    {"RORW", o_LogicalW, 0x0E},
    {"TSTW", o_LogicalW, 0x06},

    {"STE",  o_STE,      0x0A},
    {"ADDE", o_ADDE,     0x01},
    {"ADCE", o_ArithE,   0x03},
    {"ANDE", o_ArithE,   0x06},
    {"CPE",  o_ArithE,   0x08},
    {"EORE", o_ArithE,   0x04},
    {"LDE",  o_ArithE,   0x05},
    {"ORE",  o_ArithE,   0x07},
    {"SBCE", o_ArithE,   0x02},
    {"SUBE", o_ArithE,   0x00},

    {"ASL",  o_Logical,  0x04},
    {"ASR",  o_Logical,  0x0D},
    {"CLR",  o_Logical,  0x05},
    {"COM",  o_Logical,  0x00},
    {"DEC",  o_Logical,  0x01},
    {"INC",  o_Logical,  0x03},
    {"LSR",  o_Logical,  0x0F},
    {"NEG",  o_Logical,  0x02},
    {"ROL",  o_Logical,  0x0C},
    {"ROR",  o_Logical,  0x0E},
    {"TST",  o_Logical,  0x06},

    {"BCLRW", o_BCLRW,   0x2708},
    {"BSETW", o_BCLRW,   0x2709},
    {"BCLR",  o_BCLR,    0x08},
    {"BSET",  o_BCLR,    0x09},

    {"BRCLR", o_BRCLR,   0x0A},
    {"BRSET", o_BRCLR,   0x0B},

    {"STS",   o_STX,     0x8F},
    {"STX",   o_STX,     0x8C},
    {"STY",   o_STX,     0x8D},
    {"STZ",   o_STX,     0x8E},
    {"LDX",   o_LDX,     0xCC},
    {"LDY",   o_LDX,     0xCD},
    {"LDZ",   o_LDX,     0xCE},
    {"CPS",   o_ArithX,  0x4F},
    {"CPX",   o_ArithX,  0x4C},
    {"CPY",   o_ArithX,  0x4D},
    {"CPZ",   o_ArithX,  0x4E},
    {"LDS",   o_ArithX,  0xCF},

    {"JMP",   o_JMP,     0x4B},
    {"JSR",   o_JMP,     0x89},

    {"STD",   o_STD,     0x378A},
    {"STAA",  o_StoreAB, 0x174A},
    {"STAB",  o_StoreAB, 0x17CA},
    {"ADDD",  o_ADDD,    0x3781},
    {"ADCD",  o_ArithW,  0x3783},
    {"ANDD",  o_ArithW,  0x3786},
    {"CPD",   o_ArithW,  0x3788},
    {"EORD",  o_ArithW,  0x3784},
    {"LDD",   o_ArithW,  0x3785},
    {"ORD",   o_ArithW,  0x3787},
    {"SBCD",  o_ArithW,  0x3782},
    {"SUBD",  o_ArithW,  0x3780},
    {"ADCA",  o_Arith,   0x1743},
    {"ADCB",  o_Arith,   0x17C3},
    {"ADDA",  o_Arith,   0x1741},
    {"ADDB",  o_Arith,   0x17C1},
    {"ANDA",  o_Arith,   0x1746},
    {"ANDB",  o_Arith,   0x17C6},
    {"BITA",  o_Arith,   0x1749},
    {"BITB",  o_Arith,   0x17C9},
    {"CMPA",  o_Arith,   0x1748},
    {"CMPB",  o_Arith,   0x17C8},
    {"EORA",  o_Arith,   0x1744},
    {"EORB",  o_Arith,   0x17C4},
    {"LDAA",  o_Arith,   0x1745},
    {"LDAB",  o_Arith,   0x17C5},
    {"ORAA",  o_Arith,   0x1747},
    {"ORAB",  o_Arith,   0x17C7},
    {"SBCA",  o_Arith,   0x1742},
    {"SBCB",  o_Arith,   0x17C2},
    {"SUBA",  o_Arith,   0x1740},
    {"SUBB",  o_Arith,   0x17C0},

    {"",     o_Illegal,  0}
};


// --------------------------------------------------------------

int GetIndex(void)
{
    Str255  word;
    char    *oldLine;
    int     token;

    oldLine = linePtr;
    token = GetWord(word);
    if (token == ',')
    {
        GetWord(word);
        if ((word[0]=='X' || word[0]=='Y' || word[0]=='Z') && word[1]==0)
            return word[0]-'X';
    }
    linePtr = oldLine;
    return -1;
}


int M68HC16_DoCPUOpcode(int typ, int parm)
{
    int     val,val2,val3;
    Str255  word;
    char    *oldLine;
    int     token;
//  char    force;
    char    reg;
    bool    known;

    switch(typ)
    {
        case o_Inherent:
            InstrX(parm);
            break;

        case o_Branch:
            val = EvalBranch(2);
            InstrXB(parm,val);
            break;

        case o_LBranch:
            if (parm < 256) val = EvalLBranch(3);
                    else    val = EvalLBranch(4);
            InstrXW(parm, val);
            break;

        case o_ImmediateW:
            Expect("#");
            val = Eval();
            InstrXW(parm, val);
            break;

        case o_AIX:
            Expect("#");
            val = Eval();
            if (evalKnown && -128 <= val && val <= 127) InstrXB(parm       ,val);
                                                   else InstrXW(parm+0x3700,val);
            break;

        case o_MAC:
            oldLine = linePtr;
            token = GetWord(word);
            if (token == '#')
            {
                val=Eval();
                InstrXB(parm,val);
            }
            else
            {
                linePtr = oldLine;
                val=Eval();
                Comma();
                val2=Eval();
                if (val < 0 || val > 15 || val2 < 0 || val2 > 15)
                    IllegalOperand();
                else
                    InstrXB(parm,val * 16 + val2);
            }
            break;

        case o_PSHM:
        case o_PULM:
            val = 0;

            token = GetWord(word);
            while (token)
            {
                reg = FindReg(word,"D E X Y Z K CCR");
                if (reg < 0) IllegalOperand();
                else
                {
                    if (typ == o_PULM) reg = 6 - reg;
                    reg = 1 << reg;
                    if (val & reg)
                        Error("PSHM/PULM register used twice");
                    else
                        val = val | reg;
                }

                token = GetWord(word);
                if (token == ',')
                {
                    val2 = GetWord(word);
                    if (val2 == 0)
                    {
                        MissingOperand();
                        break;
                    }
                }
            }

            if (val == 0)
            {
                Warning("PSHM/PULM with no registers");
            }
            else InstrXB(parm,val);

            break;

        case o_MOVB:
            // $xxxx,$yyyy = parm+$37FE
            // $xxxx,$yy,X = parm+$32
            // $xx,X,$yyyy = parm+$30

            val = Eval();
            reg = GetIndex();
            if (reg == 0)   // $xx,X,$yyyy
            {
                CheckByte(val);
                Comma();
                val2 = Eval();
                InstrXBW(parm+0x30,val,val2);
            }
            else if (reg < 0)
            {
                Comma();
                val2 = Eval();
                reg = GetIndex();
                if (reg == 0)   // $xxxx,$yy,X
                {
                    CheckByte(val2);
                    InstrXBW(parm+0x32,val2,val);
                }
                else if (reg < 0)   // $xxxx,$yyyy
                {
                    InstrXWW(parm+0x37FE,val,val2);
                    if (listWid == LIST_24)
                        hexSpaces = 0x14;
                    else
                        instrLen = -instrLen; // more than 5 bytes, so use long DB listing format
                }
                else IllegalOperand();
            }
            else IllegalOperand();
            break;

        case o_LogicalW:
            // $xxxx,X = parm+$2700
            // $xxxx,Y = parm+$2710
            // $xxxx,Z = parm+$2720
            // $xxxx   = parm+$2730

            val=Eval();
            reg=GetIndex();
            if (reg < 0)    // no index register
                InstrXW(parm+0x2730,val);
            else
                InstrXW(parm+0x2700+reg*16,val);
            break;

        case o_Logical:
            // $xx,X   = parm+$00
            // $xx,Y   = parm+$10
            // $xx,Z   = parm+$20
            // $xxxx,X = parm+$1700
            // $xxxx,Y = parm+$1710
            // $xxxx,Z = parm+$1720
            // $xxxx   = parm+$1730
            // A       = parm+$3700
            // B       = parm+$3710
            // D       = parm+$27F0
            // E       = parm+$2770
            // M: ASLM=27B6 ASRM=27BA CLRM=27B7

            val=Eval();
            reg=GetIndex();
            if (reg < 0)    // no index register
            {
                InstrXW(parm+0x1730,val);
            }
            else
            {
                if (evalKnown && 0 <= val && val <= 255) InstrXB(parm+reg*16       ,val);
                                                    else InstrXW(parm+0x1700+reg*16,val);
            }
            break;

        case o_STE:
        case o_ADDE:
        case o_ArithE:
            // #$xx    = 7C xx (only on o_ADDE)
            // #$xxxx  = parm+$3730 (not on o_StoreE)
            // $xxxx,X = parm+$3740
            // $xxxx,Y = parm+$3750
            // $xxxx,Z = parm+$3760
            // $xxxx   = parm+$3770

            oldLine = linePtr;
            token = GetWord(word);
            if (token == '#' && typ != o_STE)
            {
                val=Eval();
                if (evalKnown && typ == o_ADDE && -128 <= val && val <= 127) InstrXB(       0x7C,val);
                                                                        else InstrXW(parm+0x3730,val);
            }
            else
            {
                linePtr = oldLine;
                val = Eval();
                reg = GetIndex();
                if (reg < 0)    // no index register
                {
                    InstrXW(parm+0x3770,val);
                }
                else
                {
                    if (evalKnown && 0 <= val && val <= 255) InstrXB(parm+       reg*16,val);
                                                        else InstrXW(parm+0x3740+reg*16,val);
                }
            }
            break;

        case o_BCLRW:
        case o_BCLR:
            // $xxxx,X,#$mm = parm+$00
            // $xxxx,Y,#$mm = parm+$10
            // $xxxx,Z,#$mm = parm+$20
            // $xxxx,#$mm   = parm+$30
            // $xx,X,#$mm   = parm+$1700 (o_BCLR only)
            // $xx,Y,#$mm   = parm+$1710 (o_BCLR only)
            // $xx,Z,#$mm   = parm+$1720 (o_BCLR only)

        case o_BRCLR:
            // $xxxx,X,#$mm = parm+$00
            // $xxxx,Y,#$mm = parm+$10
            // $xxxx,Z,#$mm = parm+$20
            // $xxxx,#$mm   = parm+$30
            // $xx,X,#$mm   = (~parm & 0x01)*$40 + $8B
            // $xx,Y,#$mm   = (~parm & 0x01)*$40 + $9B
            // $xx,Z,#$mm   = (~parm & 0x01)*$40 + $AB

            val = Eval();
            known = evalKnown;
            reg = GetIndex();
            Comma();
            Expect("#");
            val2 = EvalByte();
            if (typ == o_BRCLR)
            {
                Comma();
                if (known && 0 <= val && val <= 255)
                {
                    val3 = EvalBranch(4);
                    if (reg<0) reg=3;
                    InstrXBBB((~parm & 0x01)*0x40 + 0x8B + reg*16,val2,val,val3);
                }
                else
                {
                    val3 = EvalBranch(5);
                    if (reg<0) reg=3;
                    InstrXBWB((parm&0xFF)+reg*16,val2,val,val3);
                }
            }
            else if (reg < 0)
            {
                InstrXBW(parm+0x30,val2,val);
            }
            else
            {
                if (known && typ == o_BCLR && 0 <= val && val <= 255) InstrXBB(parm+0x1700+reg*16,val2,val);
                                                                 else InstrXBW(parm+       reg*16,val2,val);
            }
            break;

        case o_STX:
        case o_LDX:
        case o_ArithX:
            // $xx,X   = parm+$00
            // $xx,Y   = parm+$10
            // $xx,Z   = parm+$20
            // $xxxx,X = parm+$1700
            // $xxxx,Y = parm+$1710
            // $xxxx,Z = parm+$1720
            // $xxxx   = parm+$1730
            // #$xxxx  = parm+$3730 (except o_STX o_LDX)
            // #$xxxx  = parm+$3730-$40 (o_LDX only)

            oldLine = linePtr;
            token = GetWord(word);
            if (token == '#' && typ != o_STX)
            {
                val=Eval();
                if (typ == o_LDX) InstrXW(parm+0x3730-0x40,val);
                             else InstrXW(parm+0x3730,val);
            }
            else
            {
                linePtr = oldLine;
                val = Eval();
                reg = GetIndex();
                if (reg < 0)    // no index register
                {
                    InstrXW(parm+0x1730,val);
                }
                else
                {
                    if (evalKnown && 0 <= val && val <= 255) InstrXB(parm+       reg*16,val);
                                                        else InstrXW(parm+0x1700+reg*16,val);
                }
            }
            break;

        case o_JMP:
            // JMP=$4B, JSR=$89
            // $xxxx    = $7A+(parm & $80)
            // $xxxxx,X = parm+$00
            // $xxxxx,Y = parm+$10
            // $xxxxx,Z = parm+$20

            val=Eval();
            reg=GetIndex();
            if (reg < 0)    // no index register
                InstrXW(0x7A+(parm & 0x80),val);
            else
                InstrX3(parm+reg*16,val & 0xFFFFF); // 20-bit address
            break;

        case o_STD:
        case o_StoreAB:
        case o_ADDD:
        case o_ArithW:
        case o_Arith:
            // #$xx     = $FC (ADDD only)
            // #$xxxx   = parm+$30 (o_ArithW only)
            // $xxxx,X  = parm+$00 (parm+$40 o_ArithW,o_ADDD,o_STD)
            // $xxxx,Y  = parm+$10 (parm+$50 o_ArithW,o_ADDD,o_STD)
            // $xxxx,Z  = parm+$20 (parm+$60 o_ArithW,o_ADDD,o_STD)
            // $xxxx    = parm+$30 (parm+$70 o_ArithW,o_ADDD,o_STD)
            // $xx,X    = (parm & 0xFF)+$00
            // $xx,Y    = (parm & 0xFF)+$10
            // $xx,Z    = (parm & 0xFF)+$20
            // #$xx     = (parm & 0xFF)+$30 (o_Arith only)
            // E,X      = (parm & 0xFF)+$2700
            // E,Y      = (parm & 0xFF)+$2710
            // E,Z      = (parm & 0xFF)+$2720

            oldLine = linePtr;
            token = GetWord(word);
            if (token == '#' && typ != o_StoreAB && typ != o_STD)
            {
                val=Eval();
                if      (evalKnown && typ == o_ADDD  && -128 <= val && val <= 127) InstrXB(            0xFC,val);
                else if (evalKnown && typ == o_Arith && -128 <= val && val <= 127) InstrXB((parm&0xFF)+0x30,val);
                                                                              else InstrXW( parm      +0x30,val);
            }
            else if (word[0]=='E' && word[1]==0)
            {
                reg=GetIndex();
                if (reg < 0) BadMode();
                        else InstrX((parm & 0xFF) + 0x2700 + reg*16);
            }
            else
            {
                linePtr = oldLine;
                val=Eval();
                reg=GetIndex();
                if (reg < 0)    // no index register
                {
                    if (typ == o_ArithW || typ == o_ADDD || typ == o_STD)
                        InstrXW(parm+0x70,val);
                    else
                        InstrXW(parm+0x30,val);
                }
                else
                {
                    if (evalKnown && 0 <= val && val <= 255)
                        InstrXB((parm & 0xFF) + reg*16,val);
                    else if (typ == o_ArithW || typ == o_ADDD || typ == o_STD)
                        InstrXW(parm + 0x40 + reg*16,val);
                    else
                        InstrXW(parm + reg*16,val);
                }
            }
            break;

        default:
            return 0;
            break;
    }
    return 1;
}


void Asm68HC16Init(void)
{
    char *p;

    p = AddAsm(versionName, &M68HC16_DoCPUOpcode, NULL, NULL);
    AddCPU(p, "68HC16", 0, BIG_END, ADDR_16, LIST_24, 8, 0, M68HC16_opcdTab);
}