// asmthumb.c - copyright 2007 Bruce Tomlin

#define versionName "ARM Thumb assembler"
#include "asmx.h"

enum
{
    o_TwoOp,        // two-operand arithmetic/logical instructions
    o_ADD,          // ADD opcode
    o_SUB,          // SUB opcode
    o_Shift,        // ASR/LSL/LSR
    o_Immed8,       // BKPT/SWI
    o_Branch,       // B
    o_BranchCC,     // Bcc
    o_BLX,          // BLX
    o_BL,           // BL
    o_BX,           // BX
    o_CMP_MOV,      // CMP/MOV
    o_LDMIA,        // LDMIA/STMIA
    o_LDR,          // LDR/STR
    o_LDRBH,        // LDRB/LDRH/STRB/STRH
    o_LDRSBH,       // LDRSB/LDRSH
    o_PUSH_POP,     // PUSH/POP
    o_Implied,      // NOP

//  o_Foo = o_LabelOp,
};

const char regs_0_7 [] = "R0 R1 R2 R3 R4 R5 R6 R7";
const char regs_0_7L[] = "R0 R1 R2 R3 R4 R5 R6 R7 R14 LR"; // for PUSH/POP
const char regs_0_15[] = "R0 R1 R2 R3 R4 R5 R6 R7 R8 R9 R10 R11 R12 R13 R14 R15 SP LR PC";

struct OpcdRec Thumb_opcdTab[] =
{
    {"ADC",   o_TwoOp,      0x4140},
    {"AND",   o_TwoOp,      0x4000},
    {"BIC",   o_TwoOp,      0x4380},
    {"CMN",   o_TwoOp,      0x42C0},
    {"EOR",   o_TwoOp,      0x4040},
    {"MUL",   o_TwoOp,      0x4340},
    {"MVN",   o_TwoOp,      0x43C0},
    {"NEG",   o_TwoOp,      0x4240},
    {"ORR",   o_TwoOp,      0x4300},
    {"ROR",   o_TwoOp,      0x41C0},
    {"SBC",   o_TwoOp,      0x4180},
    {"TST",   o_TwoOp,      0x4200},

    {"ADD",   o_ADD,        0},
    {"SUB",   o_SUB,        0},

    {"ASR",   o_Shift,      0x10004100}, // immed5; two-reg
    {"ASL",   o_Shift,      0x00004080},
    {"LSL",   o_Shift,      0x00004080},
    {"LSR",   o_Shift,      0x080040C0},

    {"BKPT",  o_Immed8,     0xBE00},
    {"SWI",   o_Immed8,     0xDF00},

    {"B",     o_Branch,     0},

    {"BEQ",   o_BranchCC,   0xD000},
    {"BNE",   o_BranchCC,   0xD100},
    {"BCS",   o_BranchCC,   0xD200},
    {"BHS",   o_BranchCC,   0xD200},
    {"BCC",   o_BranchCC,   0xD300},
    {"BLO",   o_BranchCC,   0xD300},
    {"BMI",   o_BranchCC,   0xD400},
    {"BPL",   o_BranchCC,   0xD500},
    {"BVS",   o_BranchCC,   0xD600},
    {"BVC",   o_BranchCC,   0xD700},
    {"BHI",   o_BranchCC,   0xD800},
    {"BLS",   o_BranchCC,   0xD900},
    {"BGE",   o_BranchCC,   0xDA00},
    {"BLT",   o_BranchCC,   0xDB00},
    {"BGT",   o_BranchCC,   0xDC00},
    {"BLE",   o_BranchCC,   0xDD00},
    {"BAL",   o_BranchCC,   0xDE00},
//  {"BNV",   o_BranchCC,   0xDF00}, // ILLEGAL - opcode reused for SWI!

    {"BL",    o_BL,         0xF800},
    {"BLX",   o_BLX,        0xE800},

    {"BX",    o_BX,         0x4700},

    {"CMP",   o_CMP_MOV,    0x28428045}, // high bytes of immed8; two-reg; high-reg
    {"MOV",   o_CMP_MOV,    0x201C0046},

    {"LDMIA", o_LDMIA,      0xC800},
    {"STMIA", o_LDMIA,      0xC000},

    {"LDR",   o_LDR,        0x0800},
    {"STR",   o_LDR,        0x0000},

    {"LDRB",  o_LDRBH,      0x78005C00}, // immed offset; reg offset
    {"LDRH",  o_LDRBH,      0x88005A00},
    {"STRB",  o_LDRBH,      0x70005400},
    {"STRH",  o_LDRBH,      0x80005200},

    {"LDRSB", o_LDRSBH,     0x5600},
    {"LDRSH", o_LDRSBH,     0x5E00},

    {"PUSH",  o_PUSH_POP,   0xBC00},
    {"POP",   o_PUSH_POP,   0xB400},

    {"NOP",   o_Implied,    0x46C0},

    {"",      o_Illegal,    0}
};

// --------------------------------------------------------------


void SetThumbMultiReg(int reg, u_short *regbits, bool *warned)
{
    if (!*warned && *regbits & (1 << reg))
    {
        Warning("register specified twice");
        *warned = TRUE;
    }
    *regbits |= 1 << reg;
}


int ThumbGetMultiRegs(bool useLR, u_short *regbits)
{
    int     reg1,reg2,i;
    Str255  word;
    char    *oldLine;
    int     token;
    bool    warned;

    *regbits = 0;
    warned = FALSE;

    // looking for {r0,r2-r5,r6,lr}

    if (Expect("{")) return 1;

    // FIXME: at least one reg must be specified

    oldLine = linePtr;
    token = ',';
    while (token == ',')
    {
        reg1 = GetReg(regs_0_7L);
        if (reg1 == 9) reg1 = 8; // LR/R14 -> bit 8

        if ((reg1 > 7) && !useLR) // error if LR not allowed
        {
            IllegalOperand();
            break;
        }

        if (reg1 < 0)
        {
            IllegalOperand();      // abort if not valid register
            break;
        }

        // set single register bit
        SetThumbMultiReg(reg1, regbits, &warned);

        // check for - or ,
        oldLine = linePtr;
        token = GetWord(word);

        if (token == '-')       // register range
        {
            oldLine = linePtr;  // commit line position
            reg2 = GetReg(regs_0_7L); // check for second register
            oldLine = linePtr;  // commit line position
            if (reg2 == 9) reg2 = 8; // LR/R14 -> bit 8

            if ((reg2 > 7) && !useLR) // error if LR not allowed
            {
                IllegalOperand();
                break;
            }

            if (reg2 < 0)
            {
                IllegalOperand();      // abort if not valid register
                break;
            }
            if (reg1 < reg2)
            {
                for (i = reg1 + 1 ; i <= reg2; i++)
                    SetThumbMultiReg(i, regbits, &warned);
            }
            else if (reg1 > reg2)
            {
                for (i = reg1 - 1 ; i >= reg2; i--)
                    SetThumbMultiReg(i, regbits, &warned);
            }
            oldLine = linePtr;  // commit line position
            token = GetWord(word);
        }
        if (token == ',')  // is there another register?
            oldLine = linePtr;  // commit line position
    }
    linePtr = oldLine;

    Expect("}");

    return 0;
}


// get two registers R0-R7, returns -1 if error
u_long TwoRegs()
{
    int     reg1,reg2;

    reg1 = GetReg(regs_0_7);
    if (CheckReg(reg1)) return -1;
    
    if (Comma()) return -1;

    reg2 = GetReg(regs_0_7);
    if (CheckReg(reg2)) return -1;

    return (reg2 << 3) | reg1;
}


int ThumbEvalBranch(int width, int instrLen) // instrLen should be 4
{
    long val;
    long limit;

    limit = (1 << width) - 1;

    val = Eval();
    val = val - locPtr - instrLen;
    if (!errFlag && ((val & 1) || val < ~limit || val > limit))
        Error("Long branch out of range");

    return val;
}


int Thumb_DoCPUOpcode(int typ, int parm)
{
    int     val;
    Str255  word;
    char    *oldLine;
    int     token;
    int     reg1,reg2;
    u_short regbits;

    switch(typ)
    {
        case o_TwoOp:        // two-operand arithmetic/logical instructions
            if ((val=TwoRegs())<0) break;
            InstrW(parm | val);
            break;

        case o_ADD:          // ADD opcode
            reg1 = GetReg(regs_0_15);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            oldLine = linePtr;
            token = GetWord(word);
            if (token == '#')
            { // Rd,#immed8 / SP,#immed7
                if (reg1 <= 7)
                {
                    val = EvalByte();
                    InstrW(0x3000 | (reg1 << 8) | (val & 0xFF));
                }
                else
                {
                    val = Eval();
                    // FIXME: check immed7 range
                    InstrW(0xD000 | ((val >> 2) & 0x7F));
                }
            }
            else
            { // Rd,Rn,#immed3 / Rd,Rn,Rm / RD,RM / Rd,PC,#immed8 / Rd,PC/SP,#immed8
                linePtr = oldLine;

                reg2 = GetReg(regs_0_15);
                if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
                if (CheckReg(reg2)) break;

                oldLine = linePtr;
                token = GetWord(word);
                if (token == ',')
                {
                    token = GetWord(word);
                    if (token == '#')
                    {
                        val = Eval();
                        if (reg2 == 15) // PC
                        {
                            // FIXME: need to check immed8 range
                            InstrW(0xA000 | (reg1 << 8) | ((val >> 2) & 0xFF));
                        }
                        else if (reg2 == 13) // SP
                        {
                            // FIXME: need to check immed8 range
                            InstrW(0xA800 | (reg1 << 8) | ((val >> 2) & 0xFF));
                        }
                        else if (reg2 <= 7) // Rm
                        {
                            // FIXME: need to check immed3 range 0..7
                            InstrW(0x1C00 | ((val & 7) << 6) | (reg2 << 3) | reg1);
                        }
                        else IllegalOperand();
                    }
                    else
                    {
                        val = FindReg(word,regs_0_7);
                        if (CheckReg(val)) break;

                        InstrW(0x1800 | (val << 6) | (reg2 << 3) | reg1);
                    }
                }
                else // RD,RM
                    InstrW(0x4400 | ((reg1 << 4) & 0x80) | (reg2 << 3) | (reg1 & 0x03));
            }
            break;

        case o_SUB:          // SUB opcode
            reg1 = GetReg(regs_0_15);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (reg1 > 7 && reg1 != 13)    // only R0-R7 and SP are allowed here
            {
                IllegalOperand();
                break;
            }

            if (Comma()) break;

            oldLine = linePtr;
            token = GetWord(word);
            if (token == '#')
            { // Rd,#immed8 / SP,#immed7
                if (reg1 <= 7)
                {
                    val = EvalByte();
                    InstrW(0x3800 | (reg1 << 8) | (val & 0xFF));
                }
                else
                {
                    val = Eval();
                    // FIXME: check immed7 range
                    InstrW(0xB080 | ((val >> 2) & 0x7F));
                }
            }
            else
            { // Rd,Rn,#immed3 / Rd,Rn,Rm
                linePtr = oldLine;
                reg2 = GetReg(regs_0_7);
                if (CheckReg(reg2)) break;

                if (Comma()) break;

                token = GetWord(word);
                if (token == '#')
                {
                    val = Eval();
                    // FIXME: need to check immed3 range 0..7
                    InstrW(0x1E00 | ((val & 7) << 6) | (reg2 << 3) | reg1);
                }
                else
                {
                    val = FindReg(word,regs_0_7);
                    if (CheckReg(val)) break;

                    InstrW(0x1A00 | (val << 6) | (reg2 << 3) | reg1);
                }
            }
            break;

        case o_Shift:        // ASR/LSL/LSR
            reg1 = GetReg(regs_0_7);
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            reg2 = GetReg(regs_0_7);
            if (CheckReg(reg2)) break;

            oldLine = linePtr;
            token = GetWord(word);
            if (token == ',')
            {
                if (Expect("#")) break;
                val = EvalByte();
                // FIXME: need to confirm that EvalByte is sufficient here for immed8
                InstrW((parm >> 16) | ((val & 0x1F) << 6) | (reg2 << 3) | reg1);
            }
            else
            {
                linePtr = oldLine;
                InstrW((parm & 0xFFFF) | (reg2 << 3) | reg1);
            }

            break;

        case o_Immed8:       // BKPT/SWI
            val = EvalByte();
            InstrW(parm | (val & 0xFF));
            break;

        case o_Branch:       // B short=DE00 long=E000
            val = ThumbEvalBranch(11,4);
            if (evalKnown && (-256 <= val) && (val <= 255))
                InstrW(0xDE00 | ((val >> 1) & 0xFF));
            else
                InstrW(0xE000 | ((val >> 1) & 0x07FF));
            break;

        case o_BranchCC:     // Bcc
            val = ThumbEvalBranch(8,4);
            InstrW(parm | ((val >> 1) & 0xFF));
            break;

        case o_BLX:          // BLX
            oldLine = linePtr;
            reg1 = GetReg(regs_0_15);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (reg1 >= 0)
            {
                InstrW(0x4780 | (reg1 << 4));
                break;
            }
            linePtr = oldLine;
            // fall through to BL form

        case o_BL:           // BL
            val = ThumbEvalBranch(22,4);
            InstrWW(0xF000 | ((val >> 12) & 0x07FF), parm | ((val >> 1) & 0x07FF));
            break;

        case o_BX:           // BX
            reg1 = GetReg(regs_0_15);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            InstrW(parm | reg1 << 3);
            break;

        case o_CMP_MOV:      // CMP/MOV
            reg1 = GetReg(regs_0_15);
            if (reg1 > 15) reg1 = reg1 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg1)) break;

            if (Comma()) break;

            oldLine = linePtr;
            token = GetWord(word);
            if (token == '#')
            {
                if (reg1 > 7)
                {
                    IllegalOperand();
                    break;
                }
                val = EvalByte();
                // FIXME: need to confirm that EvalByte is sufficient here for immed8
                InstrW(((parm >> 16) & 0xFF00) | (reg1 << 8) | (val & 0xFF));
            }
            else
            {
                linePtr = oldLine;

                reg2 = GetReg(regs_0_15);
                if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
                if (CheckReg(reg2)) break;

                if ((reg1 < 8) && (reg2 < 8))
                {
                    InstrW(((parm >> 8) & 0xFFFF) | ((reg1 << 4) & 0x80) | (reg2 << 3) | (reg1 & 0x03));
                }
                else
                {
                    InstrW(((parm << 8) & 0xFF00) | ((reg1 << 4) & 0x80) | (reg2 << 3) | (reg1 & 0x03));
                }
            }

            break;

        case o_LDMIA:        // LDMIA/STMIA
            // FIXME: at least one reg must be specified
            reg1 = GetReg(regs_0_7);
            if (CheckReg(reg1)) break;

            if (Expect("!")) break;
            if (Comma()) break;

            if (ThumbGetMultiRegs(FALSE,&regbits)) break;

            InstrW(parm | (reg1 << 8) | regbits);
            break;

        case o_LDR:          // LDR/STR
//    {"LDR",   o_LDR,        0x0800},
//    {"STR",   o_LDR,        0x0000},
            reg1 = GetReg(regs_0_7);
            if (CheckReg(reg1)) break;

            if (Comma()) break;
            if (Expect("[")) break;

            reg2 = GetReg(regs_0_15);
            if (reg2 > 15) reg2 = reg2 - 3; // SP LR PC -> R13 R14 R15
            if (CheckReg(reg2)) break;

            if ((reg2 > 7) && (reg2 != 13) && (reg2 != 15))
            {
                IllegalOperand();
                break;
            }
            if (Comma()) break;

            if (reg2 == 15) // PC
            {
                if (!parm) // can't use PC relative on STR
                {
                    IllegalOperand();
                    break;
                }
                Expect("#");
                val = Eval();
                // FIXME: need to check immed8 range
                InstrW(0x4000 | parm | (reg1 << 8) | ((val >> 2) & 0xFF));
            }
            else if (reg2 == 13) // SP
            {
                Expect("#");
                val = Eval();
                // FIXME: need to check immed8 range
                InstrW(0x9000 | parm | (reg1 << 8) | ((val >> 2) & 0xFF));
            }
            else
            {
                token = GetWord(word);
                if (token == '#')
                { // #immed5
                    val = Eval();
                    // FIXME: need to check immed5 range
                    InstrW(0x6000 | parm | (((val >> 2) & 0x1F) << 6) | (reg2 << 3) | reg1);
                }
                else
                { // Rm
                    val = FindReg(word,regs_0_7);
                    if (CheckReg(val)) break;

                    InstrW(0x5000 | parm | (val << 6) | (reg2 << 3) | reg1);
                }
            }
            Expect("]");
            break;

        case o_LDRBH:        // LDRB/LDRH/STRB/STRH
            reg1 = GetReg(regs_0_7);
            if (CheckReg(reg1)) break;

            if (Comma()) break;
            if (Expect("[")) break;

            reg2 = GetReg(regs_0_7);
            if (CheckReg(reg2)) break;

            if (Comma()) break;

            token = GetWord(word);
            if (token == '#')
            {
                val = Eval();
                if (parm & 0x80000000)
                { // halfword
                    // FIXME: need to check immed5 range
                    InstrW((parm >> 16) | (((val >> 1) & 0x1F) << 6) | (reg2 << 3) | reg1);
                }
                else
                { // byte
                    // FIXME: need to check immed5 range
                    InstrW((parm >> 16) | ((val & 0x1F) << 6) | (reg2 << 3) | reg1);
                }
            }
            else
            {
                val = FindReg(word,regs_0_7);
                if (CheckReg(val)) break;

                InstrW((parm & 0xFFFF) | ((val & 0x1F) << 6) | (reg2 << 3) | reg1);
            }
            Expect("]");
            break;

        case o_LDRSBH:       // LDRSB/LDRSH
            reg1 = GetReg(regs_0_7);
            if (CheckReg(reg1)) break;

            if (Comma()) break;
            if (Expect("[")) break;

            reg2 = TwoRegs();
            if (reg2 < 0) break;

            InstrW(parm | (reg2 << 3) | reg1);

            Expect("]");

            break;

        case o_PUSH_POP:     // PUSH/POP
            // FIXME: at least one reg must be specified
            if (ThumbGetMultiRegs(TRUE,&regbits)) break;

            InstrW(parm | (regbits & 0x1FF));
            break;

        case o_Implied:      // NOP
            InstrW(parm);
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


void AsmThumbInit(void)
{
    char *p;

    p = AddAsm(versionName, &Thumb_DoCPUOpcode, NULL, NULL);
    AddCPU(p, "THUMB"   , 0, LITTLE_END, ADDR_24, LIST_24, 8, 0, Thumb_opcdTab);
    AddCPU(p, "THUMB_BE", 0, BIG_END,    ADDR_24, LIST_24, 8, 0, Thumb_opcdTab);
    AddCPU(p, "THUMB_LE", 0, LITTLE_END, ADDR_24, LIST_24, 8, 0, Thumb_opcdTab);
}