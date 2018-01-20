// asm8051.c - copyright 1998-2007 Bruce Tomlin

#define versionName "8051 assembler"
#include "asmx.h"

enum instrType
{
    o_None,     // NOP RET RETI - no operands
    o_AJMP,     // ACALL AJMP - 11-bit jump with A11-A15 unchanged
    o_LJMP,     // LCALL LJMP - 16-bit jump
    o_Rel,      // JC JNC JNZ JZ SJMP - relative jump
    o_BitRel,   // JB JBC JNB - relative jump with bit
    o_DJNZ,     // DJNZ - decrement and relative jump if not zero
    o_Arith,    // ADD ADDC SUBB - imm, @R0, @R1, R0-R7, dir
    o_Logical,  // ANL ORL XRL - imm, @R0, @R1, R0-R7, dir, C-bit, dir-imm, dir-A
    o_AccA,     // DA RL RLC RR RRC SWAP - only accepts A as parameter (should also have o_None aliases)
    o_AccAB,    // DIV MUL - only accepts AB as parameter
    o_MOV,      // MOV - mucho complicated
    o_INC_DEC,  // INC DEC - @R0, @R1, A, R0-R7, dir, and DPTR for INC only
    o_XCHD,     // XCHD A,@R0/@R1
    o_PushPop,  // POP PUSH - parameter is direct address
    o_A_bit_C,  // SETB CLR CPL - accepts A, bit, C, except SETB does not accept A
    o_JMP,      // JMP @A+DPTR
    o_MOVC,     // MOVC A,@A+DPTR/PC
    o_MOVX,     // MOVX A to or from @DPTR, @R0, @R1
    o_CJNE,     // CJNE @R0, @R1, A, R0-R7, dir with immediate and relative operands
    o_XCH       // XCH A with @R0, @R1, R0-R7, dir

//  o_Foo = o_LabelOp,
};

struct OpcdRec I8051_opcdTab[] =
{
    {"NOP",  o_None,  0x00},
    {"RET",  o_None,  0x22},
    {"RETI", o_None,  0x32},

    {"ACALL",o_AJMP,  0x11},
    {"AJMP", o_AJMP,  0x01},
    {"LCALL",o_LJMP,  0x12},
    {"LJMP", o_LJMP,  0x02},

    {"JC",   o_Rel,   0x40},
    {"JNC",  o_Rel,   0x50},
    {"JNZ",  o_Rel,   0x70},
    {"JZ",   o_Rel,   0x60},
    {"SJMP", o_Rel,   0x80},

    {"JB",   o_BitRel, 0x20},
    {"JBC",  o_BitRel, 0x10},
    {"JNB",  o_BitRel, 0x30},

    {"DJNZ", o_DJNZ,  0x00},

    {"ADD",  o_Arith, 0x20},
    {"ADDC", o_Arith, 0x30},
    {"SUBB", o_Arith, 0x90},

    {"ANL",  o_Logical, 0x8050},
    {"ORL",  o_Logical, 0x7040},
    {"XRL",  o_Logical, 0x0060},

    {"DA",   o_AccA,  0xD4},
    {"RL",   o_AccA,  0x23},
    {"RLC",  o_AccA,  0x33},
    {"RR",   o_AccA,  0x03},
    {"RRC",  o_AccA,  0x13},
    {"SWAP", o_AccA,  0xC4},

    // aliases for o_AccA instructions
//    {"DAA",  o_None, 0xD4},
//    {"RLA",  o_None, 0x23},
//    {"RLCA", o_None, 0x33},
//    {"RRA",  o_None, 0x03},
//    {"RRCA", o_None, 0x13},
//    {"SWAPA",o_None, 0xC4},

    {"DIV",  o_AccAB, 0x84},
    {"MUL",  o_AccAB, 0xA4},

    {"MOV",  o_MOV,   0x00},

    {"INC",  o_INC_DEC, 0xA300},
    {"DEC",  o_INC_DEC, 0x0010},

    {"XCHD", o_XCHD,    0x00},

    {"POP",  o_PushPop, 0xD0},
    {"PUSH", o_PushPop, 0xC0},

    {"CLR",  o_A_bit_C, 0xE4C2},
    {"CPL",  o_A_bit_C, 0xF4B2},
    {"SETB", o_A_bit_C, 0x00D2},

    {"JMP",  o_JMP,  0x00},

    {"MOVC", o_MOVC, 0x00},

    {"MOVX", o_MOVX, 0x00},

    {"CJNE", o_CJNE, 0x00},

    {"XCH",  o_XCH,  0x00},

    {"",    o_Illegal,  0}
};


// --------------------------------------------------------------


int Get_8051_Reg(const char *regList)
{
    Str255  word;
    int     token;

    if (!(token = GetWord(word)))
    {
        MissingOperand();
        return reg_EOL;
    }

    // 8051 needs to handle '@' symbols as part of a register name
    if (token == '@')
        GetWord(word+1);

    return FindReg(word,regList);
}


int EvalBitReg()
{
    int     val1,val2;
    Str255  word;
    char    *oldLine;

    val1 = Eval();
    oldLine = linePtr;
    if (GetWord(word) == '.')
    {
        // bit number must be 0..7
        val2 = Eval();
        if (val2 < 0 || val2 > 7)
        {
            IllegalOperand();
            return -1;
        }

        // compute bit index for each range
        if (0x20 <= val1 && val1 <= 0x2F)
            return (val1 & 0x1F) * 8 + val2;
        if ((val1 & 0x87) == 0x80)
            return (val1 & 0xF8) + val2;

        IllegalOperand();
        return -1;
    }

    // resulting bit index must be 0..255
    linePtr = oldLine;
    if (val1 & 0xFFFFFF00)
    {
        IllegalOperand();
        return -1;
    }
    return val1;
}

int I8051_DoCPUOpcode(int typ, int parm)
{
    int     val;
    int     reg1;
    int     reg2;
    Str255  word;
    char    *oldLine;
    int     token;

    switch(typ)
    {
        case o_None:
            InstrB(parm);
            break;

        case o_AJMP:
            val = Eval();
            if ((val & 0xF800) != ((locPtr + 2) & 0xF800))
            {
                if (parm == 0x01) Warning("AJMP out of range");
                             else Warning("ACALL out of range");
            }
            InstrBB(parm + ((val & 0x0700) >> 3),val & 0xFF);
            break;

        case o_LJMP:
            val = Eval();
            InstrBW(parm,val);
            break;

        case o_Rel:
            val = EvalBranch(2);
            InstrBB(parm,val);
            break;

        case o_BitRel:
            reg1 = EvalBitReg();
            if (reg1 < 0) break;
            Comma();
            val = EvalBranch(3);
            InstrBBB(parm,reg1,val);
            break;

        case o_DJNZ:
            oldLine = linePtr;
            switch((reg1 = Get_8051_Reg("R0 R1 R2 R3 R4 R5 R6 R7")))
            {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                    Comma();
                    val = EvalBranch(2);
                    InstrBB(0xD8+reg1,val);
                    break;

                case reg_None:
                    linePtr = oldLine;
                    reg1 = EvalByte();
                    Comma();
                    val = EvalBranch(3);
                    InstrBBB(0xD5,reg1,val);
                    break;

                default:
                    IllegalOperand();
                    break;
            }
            break;

        case o_Arith:
            switch(Get_8051_Reg("A"))
            {
                default:
                case reg_None:
                    IllegalOperand();
                case reg_EOL:
                    break;

                case 0:
                    Comma();
                    oldLine = linePtr;
                    switch((reg1 = Get_8051_Reg("@R0 @R1 R0 R1 R2 R3 R4 R5 R6 R7 #")))
                    {
                        default:
                            IllegalOperand();
                        case reg_EOL: // EOL
                            break;

                        case reg_None: // dir
                            linePtr = oldLine;
                            val = EvalByte();
                            InstrBB(parm + 0x05, val);
                            break;

                        case 0:     // @Rn
                        case 1:
                        case 2:     // Rn
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                            InstrB(parm + 0x06 + reg1);
                            break;

                        case 10:    // #imm
                            val = EvalByte();
                            InstrBB(parm + 0x04, val);
                            break;
                    }
                    break;
            }
            break;

        case o_Logical:
            oldLine = linePtr;
            switch ((Get_8051_Reg("A C")))
            {
                default:
                    IllegalOperand();
                case reg_EOL:
                    break;

                case reg_None: // dir
                    linePtr = oldLine;
                    val = EvalByte();

                    Comma();
                    switch (Get_8051_Reg("A #"))
                    {
                        default:
                        case reg_None:
                            IllegalOperand();
                        case reg_EOL:
                            break;

                        case 0:     // dir,A
                            InstrBB((parm & 0xFF) + 0x02, val);
                            break;

                        case 1:     // dir,#imm
                            reg1 = val;
                            val = EvalByte();
                            InstrBBB((parm & 0xFF) + 0x03, reg1, val);
                            break;
                    }
                    break;

                case 0:     // A
                    Comma();
                    oldLine = linePtr;
                    switch((reg1 = Get_8051_Reg("@R0 @R1 R0 R1 R2 R3 R4 R5 R6 R7 #")))
                    {
                        default:
                            IllegalOperand();
                        case reg_EOL:
                            break;

                        case reg_None: // dir
                            linePtr = oldLine;
                            val = EvalByte();
                            InstrBB((parm & 0xFF) + 0x05, val);
                            break;

                        case 0:     // @Rn
                        case 1:
                        case 2:     // Rn
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                            InstrB((parm & 0xFF) + 0x06 + reg1);
                            break;

                        case 10:    // #imm
                            val = EvalByte();
                            InstrBB((parm & 0xFF) + 0x04, val);
                            break;
                    }
                    break;

                case 1:     // C
                    if ((parm & 0xFF00) == 0)
                    {   // XRL C,bit
                        IllegalOperand();
                        break;
                    }
                    Comma();
                    // "bit" or "/bit"
                    val = 0x02;
                    oldLine = linePtr;
                    token = GetWord(word);
                    if (token == '/') val = 0x30;
                                 else linePtr = oldLine;

                    reg1 = EvalBitReg();
                    if (reg1 < 0) break;
                    InstrBB((parm >> 8) + val, reg1);
                    break;


            }
            break;

        case o_AccA:
            switch(Get_8051_Reg("A"))
            {
                default:
                case reg_None:
                    IllegalOperand();
                case reg_EOL:
                    break;
                case 0:
                    InstrB(parm);
            }
            break;

        case o_AccAB:
            switch(Get_8051_Reg("AB"))
            {
                default:
                case reg_None:
                    IllegalOperand();
                case reg_EOL:
                    break;
                case 0:
                    InstrB(parm);
            }
            break;

        case o_MOV:
            oldLine = linePtr;
            switch((reg1 = Get_8051_Reg("@R0 @R1 R0 R1 R2 R3 R4 R5 R6 R7 A C DPTR")))
            {
                case reg_EOL: // EOL
                    break;

                case reg_None:    // dir or bit
                    linePtr = oldLine;
                    reg1 = EvalByte();
                    oldLine = linePtr;
                    token = GetWord(word);
                    if (token == '.')   // bit.b,C
                    {
                        if (0x20 <= reg1 && reg1 <= 0x2F)
                            reg1 = (reg1 & 0x1F) * 8;
                        else if ((reg1 & 0x87) != 0x80)
                        {
                            IllegalOperand();
                            break;
                        }

                        reg2 = EvalByte();
                        if (reg2 < 0 || reg2 > 7)
                        {
                            IllegalOperand();
                            break;
                        }
                        Comma();
                        switch (Get_8051_Reg("C"))
                        {
                            default:
                            case reg_None:
                                IllegalOperand();
                            case reg_EOL:
                                break;

                            case 0:
                                InstrBB(0x92,reg1 + reg2);
                        }
                        break;
                    }
                    else if (token != ',')
                    {
                        oldLine = linePtr;
                        Expect(",");
                        break;
                    }
                    oldLine = linePtr;  // dir,Rn or bit,C
                    switch((reg2 = Get_8051_Reg("@R0 @R1 R0 R1 R2 R3 R4 R5 R6 R7 A # C")))
                    {
                        default:
                            IllegalOperand();
                        case reg_EOL:
                            break;

                        case reg_None: // dir
                            linePtr = oldLine;
                            val = EvalByte();
                            InstrBBB(0x85, val, reg1);
                            break;

                        case 0:     // @Rn
                        case 1:
                        case 2:     // Rn
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                            InstrBB(0x86 + reg2, reg1);
                            break;

                        case 10:    // A
                            InstrBB(0xF5, reg1);
                            break;

                        case 11:    // #imm
                            val = EvalByte();
                            InstrBBB(0x75, reg1, val);
                            break;

                        case 12:    // bit,C
                            InstrBB(0x92,reg1);
                            break;
                    }
                    break;

                case 0:     // @R0 @R1
                case 1:
                case 2:     // Rn
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                    Comma();
                    oldLine = linePtr;
                    switch (Get_8051_Reg("A #"))
                    {
                        default:
                            IllegalOperand();
                        case reg_EOL:
                            break;

                        case reg_None: // dir
                            linePtr = oldLine;
                            val = EvalByte();
                            InstrBB(0xA6 + reg1, val);
                            break;

                        case 0:     // A
                            InstrB(0xF6 + reg1);
                            break;

                        case 1:     // #imm
                            val = EvalByte();
                            InstrBB(0x76 + reg1, val);
                            break;
                    }
                    break;

                case 10:     // A
                    Comma();
                    oldLine = linePtr;
                    switch((reg1 = Get_8051_Reg("@R0 @R1 R0 R1 R2 R3 R4 R5 R6 R7 #")))
                    {
                        default:
                            IllegalOperand();
                        case reg_EOL:
                            break;

                        case reg_None: // dir
                            linePtr = oldLine;
                            val = EvalByte();
                            InstrBB(0xE5, val);
                            break;

                        case 0:     // @Rn
                        case 1:
                        case 2:     // Rn
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                            InstrB(0xE6 + reg1);
                            break;

                        case 10:     // #imm
                            val = EvalByte();
                            InstrBB(0x74, val);
                            break;
                    }
                    break;

                case 11:    // C
                    Comma();
                    reg1 = EvalBitReg();
                    if (reg1 < 0) break;
                    InstrBB(0xA2,reg1);
                    break;

                case 12:    // DPTR
                    Comma();
                    Expect("#");
                    val = Eval();
                    InstrBW(0x90,val);
                    break;

                default:
                    IllegalOperand();
            }
            break;

        case o_INC_DEC:
            oldLine = linePtr;
            switch((reg1 = Get_8051_Reg("A DPTR @R0 @R1 R0 R1 R2 R3 R4 R5 R6 R7")))
            {
                case reg_EOL: // EOL
                    break;

                case reg_None: // dir
                    linePtr = oldLine;
                    val = EvalByte();
                    InstrBB(parm + 0x05, val);
                    break;

                case 0:     // A
                case 2:     // @Rn
                case 3:
                case 4:     // Rn
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                    InstrB((parm & 0xFF) + 0x04 + reg1);
                    break;

                case 1:     // DPTR
                    if (parm & 0xFF00) InstrB(parm >> 8);
                                  else IllegalOperand();
                    break;

                default:
                    IllegalOperand();
            }
            break;

        case o_XCHD:
            switch(Get_8051_Reg("A"))
            {
                default:
                case reg_None:
                    IllegalOperand();
                case reg_EOL:
                    break;
                case 0:
                    Comma();
                    switch((reg1 = Get_8051_Reg("@R0 @R1")))
                    {
                        default:
                        case reg_None:
                            IllegalOperand();
                        case reg_EOL:
                            break;
                        case 0:
                        case 1:
                            InstrB(0xD6 + reg1);
                            break;
                    }
                    break;
            }
            break;

        case o_PushPop:
            val = Eval();
            InstrBB(parm,val);
            break;

        case o_A_bit_C:
            oldLine = linePtr;
            switch((reg1 = Get_8051_Reg("A C")))
            {
                case 0:     // A
                    if ((parm & 0xFF00) == 0)
                        IllegalOperand();
                    else
                        InstrB(parm >> 8);
                    break;

                case 1:     // C
                    InstrB((parm & 0xFF) + 1);
                    break;

                case reg_None: // bit
                    linePtr = oldLine;
                    reg1 = EvalBitReg();
                    if (reg1 < 0) break;
                    InstrBB(parm & 0xFF, reg1);
                    break;

                default:
                    break;
            }
            break;

        case o_JMP:
            switch (Get_8051_Reg("@A"))
            {
                default:
                case reg_None:
                    IllegalOperand();
                case reg_EOL:
                    break;

                case 0:
                    Expect("+");
                    switch (Get_8051_Reg("DPTR"))
                    {
                        default:
                        case reg_None:
                            IllegalOperand();
                        case reg_EOL:
                            break;

                        case 0:
                            InstrB(0x73);
                            break;
                    }
                    break;
            }
            break;

        case o_MOVC:
            switch (Get_8051_Reg("A"))
            {
                default:
                case reg_None:
                    IllegalOperand();
                case reg_EOL:
                    break;

                case 0:
                    Comma();
                    switch (Get_8051_Reg("@A"))
                    {
                        default:
                        case reg_None:
                            IllegalOperand();
                        case reg_EOL:
                            break;

                        case 0:
                            Expect("+");

                            switch (Get_8051_Reg("PC DPTR"))
                            {
                                default:
                                case reg_None:
                                    IllegalOperand();
                                case reg_EOL:
                                    break;

                                case 0:
                                    InstrB(0x83);
                                    break;
                                case 1:
                                    InstrB(0x93);
                                    break;
                            }
                            break;
                    }
                    break;
            }
            break;

        case o_MOVX:
            switch ((reg1 = Get_8051_Reg("@DPTR A @R0 @R1")))
            {
                default:
                case reg_None:
                    IllegalOperand();
                case reg_EOL:
                    break;

                case 1:     // A
                    Comma();
                    switch ((reg1 = Get_8051_Reg("@DPTR A @R0 @R1")))
                    {
                        case 1:     // A,A
                        default:
                        case reg_None:
                            IllegalOperand();
                        case reg_EOL:
                            break;

                        case 0:     // A,@DPTR
                        case 2:     // A,@R0
                        case 3:     // A,@R1
                            InstrB(0xE0 + reg1);
                            break;
                    }
                    break;

                case 0:     // @DPTR
                case 2:     // @R0
                case 3:     // @R1
                    Comma();
                    switch (Get_8051_Reg("A"))
                    {
                        default:
                        case reg_None:
                            IllegalOperand();
                        case reg_EOL:
                            break;
                        case 0:
                            break;
                    }
                    InstrB(0xF0 + reg1);
                    break;
            }
            break;

        case o_CJNE:
            oldLine = linePtr;
            switch((reg1 = Get_8051_Reg("A A @R0 @R1 R0 R1 R2 R3 R4 R5 R6 R7")))
            {
                case reg_None:
                    linePtr = oldLine;
                    reg1 = EvalByte();
                    Comma();
                    val = EvalBranch(3);
                    InstrBBB(0xB5,reg1,val);
                    break;

                case 0:     // A
                case 2:     // @Rn
                case 3:
                case 4:     // Rn
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                    Comma();
                    Expect("#");
                    reg2 = EvalByte();
                    Comma();
                    val = EvalBranch(3);
                    InstrBBB(0xB4+reg1,reg2,val);
                    break;

                default:
                    break;
            }
            break;

        case o_XCH:
            switch (Get_8051_Reg("A"))
            {
                default:
                case reg_None:
                    IllegalOperand();
                case reg_EOL:
                    break;

                case 0:
                    Comma();
                    oldLine = linePtr;
                    switch ((reg1 = Get_8051_Reg("@R0 @R1 R0 R1 R2 R3 R4 R5 R6 R7")))
                    {
                        default:
                            IllegalOperand();
                        case reg_EOL:
                            break;

                        case reg_None: // dir
                            linePtr = oldLine;
                            val = EvalByte();
                            InstrBB(0xC5, val);
                            break;

                        case 0:     // @R0
                        case 1:
                        case 2:     // Rn
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                            InstrB(0xC6 + reg1);
                            break;
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


int I8051_DoCPULabelOp(int typ, int parm, char *labl)
{
    int     i,val,val2;
    char    *oldLine;
    Str255  word;

    switch(typ)
    {
        case o_EQU:
            if (labl[0] == 0)
                Error("Missing label");
            else
            {
                val = Eval();

                // allow EQU to 8051 register bit references
                oldLine = linePtr;
                if (GetWord(word) == '.')
                {
                    // bit number must be 0..7
                    val2 = Eval();
                    if (val2 < 0 || val2 > 7)
                    {
                        IllegalOperand();
                        break;
                    }

                    // compute bit index for each range
                    if (0x20 <= val && val <= 0x2F)
                        val = (val & 0x1F) * 8 + val2;
                    else if ((val & 0x87) == 0x80)
                        val = (val & 0xF8) + val2;
                    else
                    {
                        IllegalOperand();
                        break;
                    }
                }

                sprintf(word,"---- = %.4X",val & 0xFFFF);
                for (i=5; i<11; i++)
                    listLine[i] = word[i];
                DefSym(labl,val,parm==1,parm==0);
            }
            break;

        default:
            return 0;
            break;
    }
    return 1;
}


void Asm8051Init(void)
{
    char *p;

    p = AddAsm(versionName, &I8051_DoCPUOpcode, &I8051_DoCPULabelOp, NULL);
    AddCPU(p, "8051", 0, LITTLE_END, ADDR_16, LIST_24, 8, 0, I8051_opcdTab);
}